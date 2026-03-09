#!/bin/bash
# crun
# author: Nos0kkk
# GitHub: https://github.com/Nos0kkk

if [ "$1" = "--linux-debian" ]; then
  sudo mkdir -p BUILD_CRUN/crun/{DEBIAN,usr/bin}
  sudo touch BUILD_CRUN/crun/DEBIAN/control
  sudo chmod 755 BUILD_CRUN/crun/DEBIAN/control
  sudo chmod 755 BUILD_CRUN/crun/DEBIAN
  echo "Package: crun
Version: 1.0
Architecture: x86-64
Maintainer: Nos0kkk <nos0kdev@gmail.com>
Description: simple lib for assembly project C/C++
Depends: libc++ | libc, clang
" > BUILD_CRUN/crun/DEBIAN/control

  if dpkg -s "clang" &>/dev/null; then
    sudo apt install clang
  fi

  clang++ src/crun.cpp -o crun
  sudo cp -r crun BUILD_CRUN/crun/usr/bin
  dpkg-deb --build BUILD_CRUN/crun
  sudo apt install BUILD_CRUN/crun.deb
  printf "crun: crun usefull build\n" 
  printf "crun: usage: 'crun [ --help | -h ]'\n"
  printf "crun: white if error: https://t.me/BioNos0kkk\n" 
elif [ "$1" = "--android-termux" ]; then
  mkdir -p BUILD_CRUN/crun/{DEBIAN,data/data/com.termux/files/usr/bin}
  touch BUILD_CRUN/crun/DEBIAN/control
  chmod 755 BUILD_CRUN/crun/DEBIAN/control
  chmod 755 BUILD_CRUN/crun/DEBIAN
  echo "Package: crun
Version: 1.0
Architecture: aarch64
Maintainer: Nos0kkk <nos0kdev@gmail.com>
Description: simple lib for assembly project C/C++
Depends: libc++ | libc, clang" > BUILD_CRUN/crun/DEBIAN/control

  if dpkg -s "clang" &>/dev/null; then
    pkg install clang -y
  fi

  clang++ src/crun.cpp -o crun
  cp -r crun BUILD_CRUN/crun/data/data/com.termux/files/usr/bin
  dpkg-deb --build BUILD_CRUN/crun
  dpkg -i ./BUILD_CRUN/crun.deb
  printf "crun: crun usefull build\n"
  printf "crun: usage: 'crun [ --help | -h ]'\n" 
  printf "crun: white if error: https://t.me/BioNos0kkk\n"
  
elif [ "$1" = "--help" ]; then
  printf "help list for build crun\n"
  printf "  --linux-debian — build for debian/ubuntu/mint/kali/astra/redhat/...\n"
  printf "  --adnroid-termux — build for termux (Android)\n"
  printf "  ...\n"
fi