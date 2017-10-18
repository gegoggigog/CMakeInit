#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <tuple>

using namespace std;
using namespace std::literals;
using namespace std::experimental::filesystem;
using OptionsMap = map<string, string>;
tuple<path, OptionsMap> init_defaults(const int argc,
                                      const char *const argv[]) {
  tuple<path, OptionsMap> result;
  path &template_path{get<0>(result)};
  OptionsMap &opts{get<1>(result)};
  // FIXME: Assumes executable path is in argv[0]..
  template_path = canonical(path{string{argv[0]}}.parent_path().parent_path());
  string generator{"default"s};
  {
    regex generator_match{"^(?:-G)(?:\\W*)(\\w*)(?:\\W*)"};
    cmatch match;
    for (int i{1}; i < argc; ++i) {
      if (regex_match(argv[i], match, generator_match)) {
        generator = match[1].str();
        break;
      }
    }
  }
  template_path.append("templates"s).append(generator);
  ifstream ifs{path(template_path).append("cmake_init_defaults.txt"s).string()};
  if (ifs) {
    // FIXME: Add ^ for regex?
    regex options_match{"(!@.*@!).*=\\W*(.*)"};
    smatch match;
    for (string line; getline(ifs, line);) {
      if (regex_match(line, match, options_match)) {
        opts[match[1].str()] = match[2].str();
      } else {
        cout << "Regex match failed\n";
      }
    }
    ifs.close();
  }
  return result;
}

void get_options(const int argc, const char *const argv[],
                 OptionsMap &options) {
  cout << "Raw input:\n";
  for (int i{0}; i < argc; ++i) {
    cout << argv[i] << "\n";
  }
  cout << "\n";
  // FIXME: Make sure the grups are well defined
  regex input_match{"^-D(.*)=(.*)"};
  cmatch match;
  for (int i{1}; i < argc; ++i) {
    if (regex_match(argv[i], match, input_match)) {
      options["!@"s + match[1].str() + "@!"s] = match[2].str();
    }
  }
  cout << "Mapped input:\n";
  for (const auto &o : options) {
    cout << o.first << " --> " << o.second << "\n";
  }
  cout << "\n";
}

string replace_with_options(const OptionsMap &options, const string &in) {
  string result{in};
  for (const auto &o : options) {
    auto getpos = [&o](const string &line, size_t &pos) {
      pos = line.find(o.first);
      return pos != string::npos;
    };
    for (size_t pos; getpos(result, pos);) {
      result.replace(pos, o.first.length(), o.second);
    }
  }
  return result;
}

path get_out_path(const path &in_path, const path &template_dir,
                  const OptionsMap &options) {
  const string base{template_dir.string()};
  string file{in_path.string()};
  file.erase(file.find(base), base.length());
  file = replace_with_options(options, file);
  return current_path().append(file);
}

int main(int argc, const char *const argv[]) {
  OptionsMap options;
  path template_dir;
  tie(template_dir, options) = init_defaults(argc, argv);
  get_options(argc, argv, options);
  cout << "Using template:\n" << template_dir << "\n\n";
  cout << "Copying files...\n";
  for (recursive_directory_iterator dir_it{template_dir}, end{}; dir_it != end;
       ++dir_it) {
    if (!is_directory(dir_it->path())) {
      const path out = get_out_path(dir_it->path(), template_dir, options);
      if (out.filename().string() == "cmake_init_defaults.txt") {
        continue;
      }
      create_directories(out.parent_path());
      cout << " in: " << dir_it->path() << "\n";
      cout << "out: " << out << "\n";
      ifstream ifs{dir_it->path()};
      ofstream ofs{out};
      if (ifs && ofs) {
        for (string line; getline(ifs, line);) {
          ofs << replace_with_options(options, line) << "\n";
        }
        ifs.close();
        ofs.close();
      } else if (!ifs && !ofs) {
        cout << "Bad ifstream & ofstream.\n";
        exit(3);
      } else if (!ifs) {
        cout << "Bad ifstream.\n";
        ofs.close();
        exit(1);
      } else {
        cout << "Bad ofstream.\n";
        ifs.close();
        exit(2);
      }
    }
  }
  cout << "\ndone!\n";
  exit(0);
}
