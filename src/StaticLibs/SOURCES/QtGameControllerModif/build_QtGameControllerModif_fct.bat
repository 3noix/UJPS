REM COMPILATION OF QT GAME CONTROLLER MODIF
echo compiling QtGameControllerModif
echo.
qmake
mingw32-make release
copy /Y release\QtGameControllerModif.dll ..\..\..\..\bin
echo.
echo.

