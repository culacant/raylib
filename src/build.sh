#! /bin/bash
#make clean
#yes | sudo make uninstall RAYLIB_LIBTYPE=SHARED
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED
sudo make install RAYLIB_LIBTYPE=SHARED
