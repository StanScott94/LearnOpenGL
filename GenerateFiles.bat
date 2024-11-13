@echo off

if "%1"=="" (
    echo Please provide an argument: clean, build, run-debug
    exit /b 1
)

set PREMAKE_PATH=.\premake\windows\premake5.exe

if /i "%1"=="build" (
    echo Cleaning project
    rmdir /S /Q bin
    rmdir /S /Q bin-int
    del /Q *.make
    del Makefile
    for %%f in (libs\*.make) do (
        del /Q "%%f"
    )
    echo Run premake5 for gmake2:
    %PREMAKE_PATH% --cc=clang gmake2
    echo Run make:
    make
) else if /i "%1"=="win-run" (
    call bin\Debug-windows-x86_64\LearnOpenGL\LearnOpenGL.exe
) else if /i "%1"=="test" (
make --always-make --dry-run ^
 | grep -wE "gcc|g\+\+" ^
 | grep -w "\-c" ^
 | jq -nR "[inputs|{directory:\"bin/Debug-windows-x86_64\", command: (.| gsub(\"\\""\"; \"\")), file: (match(\" [^^ ]+$\").string[1:] | gsub(\"\\""\"; \"\"))}]" ^
 > compile_commands.json
) else ( 
    echo Invalid argument
    exit /b 1
)
