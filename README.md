# Local setup

## Windows:

*Minimal setup for compilation on windows*

- `winget install — accept-source-agreements chocolatey.chocolatey`
    - `choco install make`
    - `choco install mingw`
    - `choco install jq`
    - `choco install grep`

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

- compile: `GenerateFiles.bat build`
- run: `GenerateFiles.bat win-run`
- Application executable can be found under `bin\<configuration>\LearnOpenGL\`

## Mac

- Run `GenerateFiles.sh`
- Run `make`
- Application executable can be found under `bin\<configuration>\LearnOpenGL\`

