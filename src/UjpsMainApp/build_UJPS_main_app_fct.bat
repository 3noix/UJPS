REM compilation and deployment of UJPS main app
echo compiling UjpsMainApp
echo.
qmake ujps.pro
mingw32-make release
qmake ujps_console.pro
mingw32-make release
echo.
echo.

