#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <json/json.h>

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
      std::cout << "  \t.. - compiler\n";
      std::cout << "  -lc\t --launch - launch assembled project (executable only)\n";
      std::cout << std::endl;
      std::cout << "template:\n";
      std::cout << "crun [ARGUMENT]\n";
      std::cout << std::endl;
      std::cout << "Created by Nos0kkk\n";
      std::cout << "GitHub: https://github.com/Nos0kkk\n";
      std::cout << "tg chanle: https://t.me/BioNos0k\n";
      return 1;
    }
  
    Json::Value root;
    auto path = std::filesystem::current_path();
  
    std::string jsonpath = path.string() + "/CRun.json";
    std::ifstream file(jsonpath);
    file >> root;
    
    if (std::string(argv[1]) == "-lc" || std::string(argv[1]) == "--launch") {
      std::string launchProject = "./" +
      root["setFiles"]["setExecFile"].asString();
      system(launchProject.c_str());
      return 1;
    }
  
    if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
      if (!file.is_open()) {
        std::cerr << "[crun][ERROR] CRun.json not found" << std::endl;
      } else {
        std::cerr << "[crun][INFO] read CRun.json ..." << std::endl;
      }
    }
    
    std::string compiler = root["setCompiler"].asString();
    
    if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
      if (compiler == "") {
        std::cerr << "[crun][ERROR] compiler not found: '" << compiler << "'" << std::endl;
      } else {
        std::cerr << "[crun][INFO] add compiler '" << compiler << "'" << std::endl;
      }
    }
  
    std::string flags = root["setFlags"].asString();
  
    if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
      if (flags == "") {
        std::cerr << "[crun][WARNING] flags empty: '" << flags << "'" << std::endl;
      } else {
        std::cerr << "[crun][INFO] add flags: '" << flags << "'" << std::endl;
      }
    }
  
    std::string srcFile = root["setFiles"]["setSrcFile"].asString();
  
    if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
      if (srcFile == "") {
        std::cerr << "[crun][ERROR] input file not found: '" << srcFile << "'" << std::endl;
      } else {
        std::cerr << "[crun][INFO] add input file or directory to input file: '" << srcFile << "'" << std::endl;
      }
    }
  
    std::string execFile = root["setFiles"]["setExecFile"].asString();
  
    if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
      if (execFile == "") {
        std::cerr << "[crun][ERROR] exec file the empty: '" << execFile << "'" << std::endl;
      } else {
        std::cerr << "[crun][INFO] add name for exec file: '" << execFile << "'" << std::endl;
      }
    }
  
    std::string libs = root["setLibs"].asString();
  
    if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
      std::cerr << "[crun][INFO] lib flags: '" << libs << "'" << std::endl;
    }
  
    std::string fullcom = "cd " + path.string() + " && " + compiler + " " + flags + " " + execFile + " " + srcFile + " " + libs;
  
    if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
      std::cerr << "[crun][INFO] compiles project ..." << std::endl;
    }
    system(fullcom.c_str());
  
    if (root["autoStart"].asBool() == true) {
      if (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--log") {
        std::cerr << "[crun][INFO] pojav program: '" << execFile << "'" << std::endl;
      }
      std::string pojav = "./" + execFile;
      system(pojav.c_str());
    }
    }
    catch (std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
    }
  }
  return 0;
}