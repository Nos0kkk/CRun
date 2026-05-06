# CRUN
this is simple C/C++ builder

![](crun_logo.jpeg)
_logo_

# How to install?

## build.sh
***debian/ubuntu/mint/kali/astra/...***
```shell
./build.sh --linux-debian
```
***Termux (Android)***
```shell
./build.sh --android-termux
```

## CMake
***all system***
```shell
# in source directory
mkdir build && cd build
cmake ..
make

# for move executable in dir 'bin'
# ONLY LINUX
cmake --build .. --target install
```

# Usage
more information:

```bash
crun --help
```

***Template*** ```build.crun```:
```build.crun
COMPILER=clang
FLAGS={-g}
SRC={myapp.cpp myapp2.cpp}
EXEC=myapp
LIBS={-lboost}
```

What and how?

```COMPILER``` - your compiler (`g++`, `gcc`, `clang`, `mingw`)

```FLAGS``` - flags for compiling your project (flag '-o' put automatically)

```SRC``` - Adding the source file with the code

```EXEC``` - Adding an executable file

```LIBS``` - Connection of libraries
# TODO:
***build.sh:***
- [x] debian
- [x] ubuntu
- [x] kali
- [x] astra
- [x] mint
- [ ] arch
- [ ] fedora
- [ ] void
- [x] termux (android)

***crun***
- [x] start
- [x] minimum depends
- [x] new parser
- [ ] more function

# Thank you <3
