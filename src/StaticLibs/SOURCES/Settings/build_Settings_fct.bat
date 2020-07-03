REM compilation of Settings
echo compiling Settings
echo.
qmake
mingw32-make release
copy /Y release\settings.dll ..\..\..\..\bin
echo.
echo.

