if "%1"=="" (
    echo Please provide an argument: clean or build
    exit /b 1
)

set PREMAKE_PATH=.\premake\windows\premake5.exe

REM Check the argument and execute the corresponding command
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
) else if /i "%1"=="build" (
    call %PREMAKE_PATH% vs2022
) else (
    echo Invalid argument. Use "clean" or "build".
    exit /b 1
)
