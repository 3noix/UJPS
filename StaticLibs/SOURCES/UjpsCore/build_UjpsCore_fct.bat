REM compilation of UjpsCore
echo compiling UjpsCore
echo.
qmake
mingw32-make release
copy /Y release\ujpsCore.dll ..\..\..\bin
echo.
echo.

