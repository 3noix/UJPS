echo off


REM COMPILATION OF PLUGIN LogitechExtreme3D
echo compiling LogitechExtreme3D
echo.
cd LogitechExtreme3D
qmake
mingw32-make release
copy /Y release\LogitechExtreme3D.dll ..\..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

