echo off

REM SET PATHS (line 4 to be updated with the paths that match your installation of Qt)
echo Setting up environment for Qt 5.7 usage...
set PATH=E:\Qt5.7\5.7\mingw53_32\bin;E:/Qt5.7/Tools/mingw530_32\bin;%PATH%
echo.


REM COMPILATION
echo compiling RemoteControllerTest_v1
echo.
cd RemoteControllerTest_v1
qmake
mingw32-make release
echo.
echo.


echo build finished
pause

