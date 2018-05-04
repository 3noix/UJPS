echo off
echo Setting up environment for cleaning projects...
set PATH=CleanQtProjects/release;%PATH%
echo.
echo.

echo cleaning all projects contained in the sub-directories
echo in progress...
echo.
echo.
CleanQtProjects.exe StaticLibs
echo.
CleanQtProjects.exe UjpsMainApp
echo.
CleanQtProjects.exe Monitoring0
echo.
CleanQtProjects.exe Monitoring1
echo.
CleanQtProjects.exe Monitoring2
echo.
CleanQtProjects.exe AxesCurves
echo.
CleanQtProjects.exe Profiles
echo.
CleanQtProjects.exe RemoteControllers
echo.
CleanQtProjects.exe ControllersPlugins
echo.
echo.

del UJPS.Ink
del Monitoring1.Ink
del Monitoring2.Ink
del AxesCurves.Ink

pause

