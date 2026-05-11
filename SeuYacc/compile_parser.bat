@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
cl /EHsc /std:c++17 y.tab.c /Fe:parser.exe
if %errorlevel% equ 0 (
    echo Compilation successful!
) else (
    echo Compilation failed!
)