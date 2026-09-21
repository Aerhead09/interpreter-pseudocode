@echo off
setlocal enabledelayedexpansion

set PASS=0
set FAIL=0
set TOTAL=0

REM Cari binary: di CI, folder tests/ ada di root project, binary di ../bin/
if exist "..\bin\interpreter.exe" (
    set BIN=..\bin\interpreter.exe
) else if exist "..\bin\interpreter" (
    set BIN=..\bin\interpreter
) else (
    echo [ERROR] Binary tidak ditemukan di ..\bin\
    echo         Jalankan build.bat dulu dari root project.
    exit /b 1
)

for %%f in (cases\*.psdc) do (
    set NAME=%%~nf
    set SRC=cases\%%~nf.psdc
    set EXPECTED=cases\%%~nf.expected
    set INPUT=cases\%%~nf.in
    set OUT=output_%%~nf.txt

    set /a TOTAL+=1

    if exist "!INPUT!" (
        "!BIN!" "!SRC!" < "!INPUT!" > "!OUT!" 2>nul
    ) else (
        "!BIN!" "!SRC!" < nul > "!OUT!" 2>nul
    )

    if exist "!EXPECTED!" (
        fc /W "!OUT!" "!EXPECTED!" > nul
        if !errorlevel! == 0 (
            echo [PASS] !NAME!
            set /a PASS+=1
        ) else (
            echo [FAIL] !NAME!
            set /a FAIL+=1
        )
    ) else (
        echo [SKIP] !NAME! ^(no .expected file^)
    )
)

echo.
echo ================================
echo Total: !TOTAL!  Pass: !PASS!  Fail: !FAIL!
echo ================================

if !FAIL! GTR 0 (
    exit /b 1
)

endlocal