echo off


REM COMPILATION OF PLUGIN LogitechExtreme3D
echo compiling LogitechExtreme3D
echo.
cd LogitechExtreme3D
qmake
mingw32-make release
echo.
copy /Y release\LogitechExtreme3D.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
pause

