#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include <regex>
#include <atomic>

void helpmsg() {
  std::cout << R"(crun - simple utility for build C/C++ project

Usage: crun [option]

template build.crun:
  COMPILER=g++
  FLAGS={-g}
  SRC={src/main.cpp}
  EXEC=MyApp
  LIBS={-lboost}

Flags:
  -h   --help          - its message
  -l   --log           - build and view logs
  ..                   - build (current directory)
  -lc  --launch        - pojav executable
  -vc  --view-command  - view build command

By Nos0kkk
github:   https://github.com/Nos0kkk/
telegram: https://t.me/BioNos0k/)" << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    try {
      if (!std::regex_match(std::string(argv[1]), std::regex(R"((-h|--help|-l|--log|\.\.|-lc|--launch|-vc|--view-command))"))) {
        std::cerr << "crun: '" << argv[1] << "' not found\ncrun: 'crun --help' more information" << std::endl;
        return -1;
      }

      if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        helpmsg();
        return 1;
      }
  
      auto path = std::filesystem::current_path();
      std::string line, compiler, flags, exec, src, libs;
  
      std::string buildcrun = path.string() + "/build.crun";
      std::ifstream file(buildcrun);
      if (!file.is_open()) {
        std::cerr << "crun: Error: cannot open is build.crun" << std::endl;
        return -1;
      }
      
      for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == ".." && i + 1 <= argc) {
          if (std::string(argv[i]) == "-l" || std::string(argv[i]) == "--log" && i + 1 <= argc) {
              std::cout << "[crun][INFO] start crun" << std::endl;
              if (!file.is_open()) {
                std::cout << "[crun][ERROR] build.crun not found" << std::endl;
              }
              std::cout << "[crun][INFO] reading build.crun ..." << std::endl;
              std::cout << "[crun][INFO] path to build.crun: " << std::filesystem::current_path().string() << "/build.crun" << std::endl;
          }
        }
        while (std::getline(file, line)) {
          if (line.empty()) continue;
          
          /* size_t pos = line.find('=');
          std::string key = line.substr(0, pos);
          std::string value = line.substr(pos + 1);
          
          size_t pos1 = line.find('{');
          size_t pos2 = line.find('}');
          
          std::string value2 = line.substr(pos1, pos2);
          
          size_t arg_pos1 = line.find('(');
          size_t arg_pos2 = line.find(')');
          
          std::string key_arg = line.substr(0, arg_pos1);
          
          std::string value_arg = line.substr(arg_pos1, arg_pos2);
          */
          
            if ((std::string(argv[i]) == "-l" || std::string(argv[i]) == "--log") && i + 1 <= argc) {
              if (line.substr(0, line.find('=')) == "COMPILER") {
                if (line.substr(line.find('=') + 1) == "") {
                  std::cout << "[crun][ERROR] compiler not found" << std::endl; 
                } else {
                  std::cout << "[crun][INFO] set compiler: '" <<line.substr(line.find('=') + 1)  << "'" << std::endl;
                }
              } else if (line.substr(0, line.find('=')) == "EXEC") {
                if (line.substr(line.find('=') + 1) == "") {
                  std::cout << "[crun][ERROR] executable file not found" << std::endl;
                } else {
                  std::cout << "[crun][INFO] set executable file: '" << line.substr(line.find('=') + 1) << "'" << std::endl;
                }
              } else if (line.substr(0, line.find('=')) == "SRC") {
                std::regex check_src_pattern(R"(\{(.*)\})");
                std::smatch check_src_match;
                if (std::regex_search(line, check_src_match, check_src_pattern)) {
                  if (check_src_match.str(1) == "") {
                    std::cout << "[crun][ERROR] sources file(s) not found" << std::endl;
                  } else {
                    std::cout << "[crun][INFO] set sources file(s): '" << check_src_match.str(1) << "'" << std::endl;
                  }
                }
              } else if (line.substr(0, line.find('=')) == "FLAGS") {
                std::regex check_flags_pattern(R"(\{(.*)\})");
                std::smatch check_flags_match;
                if (std::regex_search(line, check_flags_match, check_flags_pattern)) {
                  if (check_flags_match.str(1) == "") {
                    std::cout << "[crun][WARNING] flag(s) is empty" << std::endl;
                  } else {
                    std::cout << "[crun][INFO] set flags: '" << check_flags_match.str(1) << "'" << std::endl;
                  }
                }
              } else if (line.substr(0, line.find('(')) == "arg") {
                if (line.substr(line.find('(') + 1, line.find(')') - 1) == "") {
                  std::cout << "[crun][WARNING] arguments is empty" << std::endl;
                } else {
                  std::cout << "[crun][INFO] arguments: '" << line.substr(line.find('(') + 1, line.find(')') - 1) << "'" << std::endl;
                }
              } else if (line.substr(0, line.find('=')) == "LIBS") {
                std::regex check_libs_pattern(R"(\{(.*)\})");
                std::smatch check_libs_match;

                if (std::regex_search(line, check_libs_match, check_libs_pattern)) {
                  if (check_libs_match.str(1) == "") {
                    std::cout << "[crun][WARNING] libs is empty" << std::endl;
                  } else {
                    std::cout << "[crun][INFO] set libs: '" << check_libs_match.str(1) << "'" << std::endl;
                  }
                }
              }
            }
            if (line.substr(0, line.find('=')) == "COMPILER") {
              compiler = line.substr(line.find('=') + 1);
            } else if (line.substr(0, line.find('=')) == "EXEC") {
              exec = line.substr(line.find('=') + 1);
            } else if (line.substr(0, line.find('=')) == "SRC") {
              std::regex src_pattern(R"(\{(.*)\})");

              std::smatch src_match;

              if (std::regex_search(line, src_match, src_pattern)) {
                src = src_match.str(1);
              }
            } else if (line.substr(0, line.find('=')) == "FLAGS") {
              std::regex flags_pettern(R"(\{(.*)\})");

              std::smatch flags_match;

              if (std::regex_search(line, flags_match, flags_pettern)) {
                flags = flags_match.str(1);
              }
            } else if (line.substr(0, line.find('=')) == "LIBS") {
              std::regex libs_pattern(R"(\{(.*)\})");

              std::smatch libs_match;

              if (std::regex_search(line, libs_match, libs_pattern)) {
                libs = libs_match.str(1);
              }
            }
        }
        
        if (std::string(argv[i]) == "-lc" || std::string(argv[i]) == "--launch" && i + 1 < argc && line.substr(0, line.find('=')) == "EXEC") {
          if (exec.empty()) {
            std::cerr << "crun: Error: executable file not found" << std::endl;
            return -1;
          }

          std::string launch_command = "./" + exec;
          system(launch_command.c_str());
          return 1;
        }
        
        std::atomic<bool> end = false;
        
        std::thread t([&end](){
          while (true) {
            std::cout << "\r" << R"(  \  )" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
          
            std::cout << "\r  |  " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            
            std::cout << "\r  /  " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            
            std::cout << "\r  —  " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            if (end) {
              break;
            }
          }
        });
        t.detach();
       
        std::string fullcommand = compiler + " " + flags + (std::regex_search(flags, std::regex(R"(-o)")) ? " " : " -o ") + exec + " " + src + " " + libs;
        if (std::string(argv[1]) == "-vc" || std::string(argv[1]) == "--view-command") {
          if (fullcommand.empty()) {
            std::cerr << "crun: Error: buipd.crun not found or empty" << std::endl;
            return -1;
          }
          std::cout << fullcommand << std::endl;
        } else {
          system(fullcommand.c_str());
        }
        
        end = true;
      }
    } catch (std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
    }
  } else {
    helpmsg();
  }
  return 0;
}
