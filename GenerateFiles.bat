@echo off

rmdir /s /q build 2>nul
mkdir build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
make -C build
build\LearnOpenGL\LearnOpenGL.exe
