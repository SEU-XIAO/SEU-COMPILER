@echo off
setlocal

set "VS_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools"
set "VCVARS_PATH=%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat"

echo === 设置 MSVC 编译环境 ===
call "%VCVARS_PATH%" x64

if %errorlevel% neq 0 (
    echo 无法设置 MSVC 环境
    exit /b 1
)

echo.
echo === 编译 MySEULex ===

if not exist "obj" mkdir obj

echo 编译 main.cpp...
cl /c /EHsc /std:c++17 /Foobj\main.obj main.cpp

if %errorlevel% neq 0 (
    echo 编译 main.cpp 失败
    exit /b 1
)

echo 编译 parser.cpp...
cl /c /EHsc /std:c++17 /Foobj\parser.obj parser.cpp

if %errorlevel% neq 0 (
    echo 编译 parser.cpp 失败
    exit /b 1
)

echo 编译 re_standardize.cpp...
cl /c /EHsc /std:c++17 /Foobj\re_standardize.obj re_standardize.cpp

if %errorlevel% neq 0 (
    echo 编译 re_standardize.cpp 失败
    exit /b 1
)

echo 编译 re_to_suffix.cpp...
cl /c /EHsc /std:c++17 /Foobj\re_to_suffix.obj re_to_suffix.cpp

if %errorlevel% neq 0 (
    echo 编译 re_to_suffix.cpp 失败
    exit /b 1
)

echo 编译 suffix_to_nfa.cpp...
cl /c /EHsc /std:c++17 /Foobj\suffix_to_nfa.obj suffix_to_nfa.cpp

if %errorlevel% neq 0 (
    echo 编译 suffix_to_nfa.cpp 失败
    exit /b 1
)

echo 编译 nfa_to_dfa.cpp...
cl /c /EHsc /std:c++17 /Foobj\nfa_to_dfa.obj nfa_to_dfa.cpp

if %errorlevel% neq 0 (
    echo 编译 nfa_to_dfa.cpp 失败
    exit /b 1
)

echo 编译 code_generator.cpp...
cl /c /EHsc /std:c++17 /Foobj\code_generator.obj code_generator.cpp

if %errorlevel% neq 0 (
    echo 编译 code_generator.cpp 失败
    exit /b 1
)

echo 编译 utils.cpp...
cl /c /EHsc /std:c++17 /Foobj\utils.obj utils.cpp

if %errorlevel% neq 0 (
    echo 编译 utils.cpp 失败
    exit /b 1
)

echo 链接...
link /OUT:seuLex.exe obj\main.obj obj\parser.obj obj\re_standardize.obj obj\re_to_suffix.obj obj\suffix_to_nfa.obj obj\nfa_to_dfa.obj obj\code_generator.obj obj\utils.obj

if %errorlevel% equ 0 (
    echo.
    echo === 编译成功 ===
    echo 生成的可执行文件: seuLex.exe
) else (
    echo.
    echo === 链接失败 ===
    exit /b 1
)

endlocal