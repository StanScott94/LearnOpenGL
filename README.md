# Dependancies

- See `.gitmodules`

# Cloning

- Clone with submodules: `git clone --recurse-submodules <repo>`
- For already cloned repos: `git submodule update --init --recursive`

# Building

*Premake5*

Premake5 is used to generate project files for Visual Studio, GNU Make, Xcode, CodeLite, and more across Windows, Mac OS X, and Linux.
See `Premake5.lua` for more details

## Windows:

*With Developer Command Prompt (Visual Studio Code)*

- Run `GenerateFiles.bat`
- Run `msbuild LearnOpenGL.sln /p:Configuration=<Debug, Release>`
- Application executable can be found under `bin\<configuration>\LearnOpenGL\`

## Mac

- Run `GenerateFiles.sh`
- Run `make`
- Application executable can be found under `bin\<configuration>\LearnOpenGL\`

