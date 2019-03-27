echo off

REM SET PATHS (line 5-6 to be updated with the paths that match your installation of Qt)
REM echo Setting up environment for Qt 5 usage...
REM set PATH=C:\Qt\5.11.0\mingw53_32\bin;C:\Qt\Tools\mingw530_32\bin;%PATH%
REM set PATH=E:\Qt5.11\5.11.0\mingw53_32\bin;E:/Qt5.11/Tools/mingw530_32\bin;%PATH%
echo.


REM compilation and deployment of CleanQtProjects
cd %~dp0\CleanQtProjects
call build_CleanQtProjects_fct.bat
cd ..


REM compilation of static lib Settings
cd StaticLibs/SOURCES/Settings
call build_Settings_fct.bat
cd ../../..


REM compilation of static lib QtGameControllerModif
cd StaticLibs/SOURCES/QtGameControllerModif
call build_QtGameControllerModif_fct.bat
cd ../../..


REM compilation of static libRealJoysticks
cd StaticLibs/SOURCES/RealJoysticks
call build_RealJoysticks_fct.bat
cd ../../..


REM build the branch of Monitoring
start cmd.exe /c build_branch_Monitoring.bat


REM build the branch of ControllersInfo
start cmd.exe /c build_branch_ControllersInfo.bat


REM build the branch of AxesCurves
start cmd.exe /c build_branch_AxesCurves.bat


REM build the branch of UJPS main app
start cmd.exe /c build_branch_UJPS_main_app.bat


REM compilation and deployment of controllers plugins
cd ControllersPlugins
call build_ControllersPlugins.bat
cd ..


echo finished
pause

