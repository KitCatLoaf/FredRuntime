@echo off
echo Installing Fred...

set "FRED_PATH=%~dp0build"

for /f "tokens=2*" %%A in ('reg query "HKCU\Environment" /v PATH 2^>nul') do set "CURRENT_PATH=%%B"

if "%CURRENT_PATH%"=="" (
    reg add "HKCU\Environment" /v PATH /t REG_EXPAND_SZ /d "%FRED_PATH%" /f
) else (
    reg add "HKCU\Environment" /v PATH /t REG_EXPAND_SZ /d "%CURRENT_PATH%;%FRED_PATH%" /f
)

echo Done! Please log out and back in, or restart your computer.
echo Fred will then be available by typing 'fred' anywhere.
pause