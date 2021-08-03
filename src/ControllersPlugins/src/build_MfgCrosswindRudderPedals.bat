echo off


REM COMPILATION OF PLUGIN MfgCrosswindRudderPedals
echo compiling MfgCrosswindRudderPedals
echo.
cd MfgCrosswindRudderPedals
qmake
mingw32-make release
copy /Y release\MfgCrosswindRudderPedals.dll ..\..\..\..\bin\ControllersPlugins
cd ..
echo.
echo.


echo finished
REM pause

