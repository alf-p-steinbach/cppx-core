@echo off
echo.^>^>^> Running Doxygen... 1>&2
doxygen config.for-windows.txt
echo.^>^>^> Applying fixes... 1>&2
powershell -File ./fixups.ps1
