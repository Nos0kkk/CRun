# crun is a simple utility for compiling C/C++ project

# How to install?
Termux:

```bash
cd crun/CRUN_DEB_TERMUX
pkg install ./crun.deb
```

Linux:

```bash
cd crun/CRUN_DEB_LINUX
dpkg -i crun.deb
```

# Usage
more information:

```bash
crun --help
```

CRun.json syntax:
template
```json
{
  "setCompiler" : "g++",
  "setFlags" : "-static -o",
  "setFiles" : 
  {
    "setSrcFile" : "src/main.cpp",
    "setExecFile" : "main"
  },
  "setLibs" : "-lc++_shared",
  "autoStart" : false
}
```

What and how?

```setCompiler``` - your compiler (`g++`, `gcc`, `clang`, `mingw`)

```setFlags``` - flags for compiling your project

```setFiles``` - Duplicate key

ㅤㅤ```setSrcFile``` - Adding the source file with the code

ㅤㅤ```setExecFile``` - Adding an executable file

```setLibs``` - Connection of library libraries (dynamic/static)

```autoStart``` - whether the executable will run immediately after compilation (the only one takes a Boolean value)
 