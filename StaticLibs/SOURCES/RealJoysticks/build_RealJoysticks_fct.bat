REM compilation of RealJoysticks
echo compiling RealJoysticks
echo.
qmake
mingw32-make release
copy /Y release\realJoysticks.dll ..\..\..\bin
echo.
echo.

