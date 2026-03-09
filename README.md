# CRUN
this is simple C/C++ builder

![](crun_logo.jpeg)
_logo_

# How to install?

***debian/ubuntu/mint/kali/astra/...***
```bash
./build.sh --linux-debian
```
***Termux (Android)***
```bash
./build.sh --android-termux
```

# Usage
more information:

```bash
crun --help
```

***Template*** ```build.crun```:
```build.crun
COMPILER=clang
FLAGS={-g -o}
SRC={myapp.cpp myapp2.cpp}
EXEC=myapp
LIBS={-lc++ -lc -lm}
```

What and how?

```COMPILER``` - your compiler (`g++`, `gcc`, `clang`, `mingw`)

```FLAGS``` - flags for compiling your project

```SRC``` - Adding the source file with the code

```EXEC``` - Adding an executable file

```LIBS``` - Connection of library libraries (dynamic/static)

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
