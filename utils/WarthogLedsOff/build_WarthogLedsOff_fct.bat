REM compilation and deployment of WarthogLedsOff
echo compiling WarthogLedsOff
echo.
qmake
mingw32-make release
echo.
REM cd release
REM windeployqt WarthogLedsOff.exe
REM cd ..
echo.
echo.

