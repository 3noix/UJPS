echo off


REM COMPILATION OF PLUGIN LogitechX56Throttle
echo compiling LogitechX56Throttle
echo.
cd LogitechX56Throttle
qmake
mingw32-make release
copy /Y release\LogitechX56Throttle.dll ..\..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

