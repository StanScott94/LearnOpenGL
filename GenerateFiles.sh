#!/bin/bash

set -e
rm -rf build
mkdir build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
make -C build
./build/LearnOpenGL/LearnOpenGl
