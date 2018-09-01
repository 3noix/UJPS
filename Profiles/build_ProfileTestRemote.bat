echo off

REM SET PATHS (line 4 to be updated with the paths that match your installation of Qt)
REM echo Setting up environment for Qt 5 usage...
REM set PATH=C:\Qt\5.11.0\mingw53_32\bin;C:\Qt\Tools\mingw530_32\bin;%PATH%
REM set PATH=E:\Qt5.11\5.11.0\mingw53_32\bin;E:/Qt5.11/Tools/mingw530_32\bin;%PATH%
echo.


REM COMPILATION OF TEST PLUGIN
echo compiling ProfileTestRemote
echo.
cd %~dp0\ProfileTestRemote
qmake
mingw32-make release
cd ..
echo.
echo.


echo build finished
pause

