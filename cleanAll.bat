echo off
echo Setting up environment for cleaning projects...
set PATH=CleanQtProjects/release;%PATH%
echo.
echo.

echo cleaning projects STATIC_LIBS, PROFILES, PROGRAM, MONITORING and AXES_CURVES
echo in progress...
echo.
echo.
CleanQtProjects.exe STATIC_LIBS
echo.
CleanQtProjects.exe PROFILES
echo.
CleanQtProjects.exe PROGRAM
echo.
CleanQtProjects.exe MONITORING
echo.
CleanQtProjects.exe AXES_CURVES
echo.
echo.

pause

