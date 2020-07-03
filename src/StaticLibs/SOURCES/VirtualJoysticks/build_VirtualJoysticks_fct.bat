REM compilation of VirtualJoysticks
echo compiling VirtualJoysticks
echo.
qmake
mingw32-make release
copy /Y release\virtualJoysticks.dll ..\..\..\..\bin
echo.
echo.

