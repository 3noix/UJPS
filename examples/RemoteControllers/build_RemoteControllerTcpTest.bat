echo off

REM SET PATHS (line 4 to be updated with the paths that match your installation of Qt)
REM echo Setting up environment for Qt 5.11 usage...
REM set PATH=E:\Qt5.11\5.11.0\mingw53_32\bin;E:/Qt5.11/Tools/mingw530_32\bin;%PATH%
REM echo.


REM COMPILATION
echo compiling RemoteControllerTcpTest
echo.
cd RemoteControllerTcpTest
qmake
mingw32-make release
echo.
echo.


echo build finished
pause

