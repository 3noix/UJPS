echo off


REM COMPILATION OF PLUGIN MfgCrosswindRudderPedals
echo compiling MfgCrosswindRudderPedals
echo.
cd MfgCrosswindRudderPedals
qmake
mingw32-make release
echo.
copy /Y release\MfgCrosswindRudderPedals.dll ..\..\PLUGINS
cd ..
echo.
echo.


echo finished
REM pause

