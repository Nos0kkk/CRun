#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include <regex>
#include <atomic>

int main(int argc, char* argv[]) {
  if (argc > 0) {
    try {
      if (std::string(argv[1]) != ".." && std::string(argv[1]) != "-h" &&
      std::string(argv[1]) != "--help" && std::string(argv[1]) != "-l" &&
      std::string(argv[1]) != "--log" && std::string(argv[1]) != "-lc" &&
      std::string(argv[1]) != "--launch") {
        std::cerr << "crun: " << argv[1] << " not found" << std::endl;
        std::cerr << "crun: 'crun --help' more information" << std::endl;
        return 1;
      }
  
      if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        std::cout << "Crun the simple and easy lib, for make your project\n";
        std::cout << std::endl;
        std::cout << "all flags:\n";
        std::cout << "  -h\t--help - help list\n";
        std::cout << "  -l\t--log - compiler and view logs in runtime\n";
        std::cout << "  ..\t     - compiler\n";
        std::cout << "  -lc\t --launch - launch assembled project (executable only)\n";
        std::cout << std::endl;
        std::cout << "template:\n";
        std::cout << "crun [ARGUMENT]\n";
        std::cout << std::endl;
        std::cout << "template build.crun:" << std::endl;
        std::cout << R"(
COMPILER=clang
FLAGS={-g -o}
SRC={src/myapp.cpp}
EXEC=myapp
LIBS={-lc++ -lc -lm}
)" << std::endl;
        std::cout << std::endl;
      
        std::cout << "Created by Nos0kkk\n";
        std::cout << "GitHub: https://github.com/Nos0kkk\n";
        std::cout << "tg chanle: https://t.me/BioNos0k\n";
        return 1;
      }
  
      auto path = std::filesystem::current_path();
      std::string line, compiler, flags, exec, src, libs;
  
      std::string buildcrun = path.string() + "/build.crun";
      std::ifstream file(buildcrun);
      
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
          std::string launch_command = "./" + exec;
          system(launch_command.c_str());
          return 1;
        }
        
        std::atomic<bool> end{false};
        
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
       
        std::string fullcommand = compiler + " " + flags + " " + exec + " " + src + " " + libs;
        system(fullcommand.c_str());
        
        end = true;
      }
    }
    catch (std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
    }
  }
  return 0;
}
