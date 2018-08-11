echo off


REM COMPILATION OF PLUGIN LogitechX56Throttle
echo compiling LogitechX56Throttle
echo.
cd LogitechX56Throttle
qmake
mingw32-make release
echo.
copy /Y release\LogitechX56Throttle.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
pause

