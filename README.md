# Local setup

## Windows:

TODO: solve conflicting libstdc++-6.dll in Neovim on %PATH%

*Minimal setup for compilation on windows*

- `winget install — accept-source-agreements chocolatey.chocolatey`
    - `choco install make`
    - `choco install mingw`

TODO: read later to set up compile_commands.json on Neovim:

- https://medium.com/@adarshroy.formal/setting-up-neovim-on-windows-a-beginner-friendly-no-nonsense-guide-with-cpp-clangd-without-wsl-f792117466a0
- https://medium.com/unixification/how-to-setup-clangd-with-gcc-headers-and-neovim-lsp-for-competitive-programming-2f3f98425ae1

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

