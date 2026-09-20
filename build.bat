@echo off
setlocal

echo [1] Memulai build...
echo [2] Folder saat ini: %CD%

set SRC_DIR=src
set BIN_DIR=bin
set TARGET=%BIN_DIR%\interpreter.exe

echo [3] Cek g++...
where g++ >nul 2>nul
if errorlevel 1 (
    echo [ERROR] g++ tidak ditemukan di PATH!
    exit /b 1
)
echo     g++ ditemukan.

echo [4] Cek folder src...
if not exist %SRC_DIR% (
    echo [ERROR] Folder %SRC_DIR% tidak ada.
    exit /b 1
)
echo     Folder src OK.

echo [5] Buat folder bin...
if not exist %BIN_DIR% mkdir %BIN_DIR%
echo     Folder bin OK.

echo [6] Compile...
g++ -std=c++17 -Wall -Wextra -I %SRC_DIR% %SRC_DIR%\Lexer.cpp %SRC_DIR%\Parser.cpp %SRC_DIR%\Evaluator.cpp %SRC_DIR%\main.cpp -o %TARGET%

if errorlevel 1 (
    echo [GAGAL] Compile error.
    exit /b 1
)

echo [7] Selesai. Binary ada di: %TARGET%
endlocal