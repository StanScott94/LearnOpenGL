@echo off

if "%1"=="" (
    echo Please provide an argument: clean, build, run-debug
    exit /b 1
)

set PREMAKE_PATH=.\premake\windows\premake5.exe

if /i "%1"=="clean" (
    call rmdir /S /Q bin
    call rmdir /S /Q bin-int
    call del /Q imgui.ini
    call del /Q LearnOpenGL.sln
    call del /Q LearnOpenGL.vcxproj
    call del /Q LearnOpenGL.vcxproj.filters

    for %%f in (libs\*.vcxproj libs\*.vcxproj.filters) do (
        del /Q "%%f"
    )
) else if /i "%1"=="build-debug" (
    call %PREMAKE_PATH% gmake2
    call msbuild LearnOpenGL.sln /p:Configuration=Debug
) else if /i "%1"=="run-debug" (
    call bin\Debug-windows-x86\LearnOpenGL\LearnOpenGL.exe
) else ( else (
    echo Invalid argument
    exit /b 1
)
