@echo off

if "%1"=="" (
    echo Please provide an argument: clean, build, run-debug
    exit /b 1
)

set PREMAKE_PATH=.\premake\windows\premake5.exe

if /i "%1"=="build" (
    echo Cleaning project
    call rmdir /S /Q bin
    call rmdir /S /Q bin-int
    call del /Q *.make
    call del Makefile
    for %%f in (libs\*.make) do (
        del /Q "%%f"
    )
    echo Run premake5 for gmake2:
    call %PREMAKE_PATH% gmake2
    echo Run make:
    call make CC=gcc
) else if /i "%1"=="win-run" (
    call bin\Debug-windows-x86_64\LearnOpenGL\LearnOpenGL.exe
) else ( 
    echo Invalid argument
    exit /b 1
)
