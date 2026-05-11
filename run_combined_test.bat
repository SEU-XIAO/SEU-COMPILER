@echo off
chcp 65001 >nul
echo ================================================
echo MySEULex + SeuYacc Combined Test
echo ================================================
echo.

cd "71123331-杨熙锐-MySEULex\2-词法分析程序生成器源程序"
echo [Step 1] Generate lexer using MySEULex
echo Input: c99_yacc.l
echo Output: lex.yy.cpp
echo.
seuLex.exe c99_yacc.l
if %errorlevel% neq 0 (
    echo MySEULex failed!
    pause
    exit /b 1
)

echo.
echo [Step 2] Compile lexer
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
cl /EHsc /std:c++17 lex.yy.cpp /Fe:lexer_yacc.exe >nul
if %errorlevel% neq 0 (
    echo Lexer compilation failed!
    pause
    exit /b 1
)
echo Lexer compiled successfully!

echo.
echo [Step 3] Lexical analysis - generate token stream
lexer_yacc.exe test_input.c > ..\..\test.lo
echo Token stream generated to test.lo

cd ..\..\SeuYacc
echo.
echo [Step 4] Syntax analysis - parse token stream
parser.exe ..\test.lo

echo.
echo ================================================
echo Combined test completed!
echo ================================================
pause