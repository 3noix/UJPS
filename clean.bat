echo off
echo Setting up environment for cleaning projects...
set PATH=%~dp0\utils\CleanQtProjects\release;%PATH%
echo.
echo.


echo cleaning all projects contained in the sub-directories
echo in progress...
echo.
echo.
CleanQtProjects.exe %~dp0\src\StaticLibs
echo.
CleanQtProjects.exe %~dp0\src\UjpsMainApp
echo.
CleanQtProjects.exe %~dp0\src\Monitoring
echo.
CleanQtProjects.exe %~dp0\src\ControllersInfo
echo.
CleanQtProjects.exe %~dp0\src\AxesCurves
echo.
CleanQtProjects.exe %~dp0\examples\Profiles
echo.
CleanQtProjects.exe %~dp0\examples\RemoteControllers
echo.
CleanQtProjects.exe %~dp0\src\ControllersPlugins
echo.
CleanQtProjects.exe %~dp0\utils
echo.
echo.


echo removing CleanQtProjects manually
del %~dp0\utils\CleanQtProjects\.qmake.stash
del %~dp0\utils\CleanQtProjects\Makefile
del %~dp0\utils\CleanQtProjects\Makefile.Debug
del %~dp0\utils\CleanQtProjects\Makefile.Release
rmdir /S /Q %~dp0\utils\CleanQtProjects\debug
rmdir /S /Q %~dp0\utils\CleanQtProjects\release
echo.
echo.


REM echo cleaning up shortcuts
REM del %~dp0\UJPS.lnk
REM del %~dp0\Monitoring.lnk
REM del %~dp0\ControllersInfo.lnk
REM del %~dp0\AxesCurves.lnk


echo cleaning up bin directory
cd bin
rmdir /S /Q bearer
rmdir /S /Q iconengines
rmdir /S /Q imageformats
rmdir /S /Q platforms
rmdir /S /Q styles
rmdir /S /Q translations
rmdir /S /Q ControllersPlugins
del *.exe
del *.dll
cd ..
echo.
echo.


REM remove the environment variable UJPSPATH
echo remove environment variable UJPSPATH
REG delete HKCU\Environment /f /v UJPSPATH
REM REG delete "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /f /v UJPSPATH
REM echo.
REM echo cleaning finished

pause

