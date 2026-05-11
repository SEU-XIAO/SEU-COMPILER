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
echo === 编译 SeuYacc ===

if not exist "obj" mkdir obj

echo 编译 main.cpp...
cl /c /EHsc /std:c++17 /Foobj\main.obj main.cpp

if %errorlevel% neq 0 (
    echo 编译 main.cpp 失败
    exit /b 1
)

echo 编译 yaccDFA.cpp...
cl /c /EHsc /std:c++17 /Foobj\yaccDFA.obj yaccDFA.cpp

if %errorlevel% neq 0 (
    echo 编译 yaccDFA.cpp 失败
    exit /b 1
)

echo 编译 yyProducer.cpp...
cl /c /EHsc /std:c++17 /Foobj\yyProducer.obj yyProducer.cpp

if %errorlevel% neq 0 (
    echo 编译 yyProducer.cpp 失败
    exit /b 1
)

echo 编译 yaccSource.cpp...
cl /c /EHsc /std:c++17 /Foobj\yaccSource.obj yaccSource.cpp

if %errorlevel% neq 0 (
    echo 编译 yaccSource.cpp 失败
    exit /b 1
)

echo 链接...
link /OUT:seuYacc.exe obj\main.obj obj\yaccDFA.obj obj\yyProducer.obj obj\yaccSource.obj

if %errorlevel% equ 0 (
    echo.
    echo === 编译成功 ===
    echo 生成的可执行文件: seuYacc.exe
) else (
    echo.
    echo === 链接失败 ===
    exit /b 1
)

endlocal