echo off
echo Setting up environment for cleaning projects...
set PATH=%~dp0\CleanQtProjects\release;%PATH%
echo.
echo.


echo cleaning all projects contained in the sub-directories
echo in progress...
echo.
echo.
CleanQtProjects.exe %~dp0\StaticLibs
echo.
CleanQtProjects.exe %~dp0\UjpsMainApp
echo.
CleanQtProjects.exe %~dp0\Monitoring0
echo.
CleanQtProjects.exe %~dp0\Monitoring1
echo.
CleanQtProjects.exe %~dp0\Monitoring2
echo.
CleanQtProjects.exe %~dp0\ControllersInfo
echo.
CleanQtProjects.exe %~dp0\AxesCurves
echo.
CleanQtProjects.exe %~dp0\Profiles
echo.
CleanQtProjects.exe %~dp0\RemoteControllers
echo.
CleanQtProjects.exe %~dp0\ControllersPlugins
echo.
echo.


echo cleaning all compile PLUGINS dlls
If exist ControllersPlugins\PLUGINS rmdir /S /Q %~dp0\ControllersPlugins\PLUGINS


echo removing CleanQtProjects manually
del %~dp0\CleanQtProjects\.qmake.stash
del %~dp0\CleanQtProjects\Makefile
del %~dp0\CleanQtProjects\Makefile.Debug
del %~dp0\CleanQtProjects\Makefile.Release
rmdir /S /Q %~dp0\CleanQtProjects\debug
rmdir /S /Q %~dp0\CleanQtProjects\release


echo cleaning up shortcuts
del %~dp0\UJPS.lnk
del %~dp0\Monitoring0.lnk
del %~dp0\Monitoring1.lnk
del %~dp0\Monitoring2.lnk
del %~dp0\ControllersInfo.lnk
del %~dp0\AxesCurves.lnk
echo.
echo cleaning finished


pause
