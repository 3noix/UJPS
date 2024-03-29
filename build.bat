echo off

REM SET PATHS (line 5-6 to be updated with the paths that match your installation of Qt)
REM echo Setting up environment for Qt 5 usage...
REM set PATH=C:\Qt\5.11.0\mingw53_32\bin;C:\Qt\Tools\mingw530_32\bin;%PATH%
REM set PATH=E:\Qt5.11\5.11.0\mingw53_32\bin;E:/Qt5.11/Tools/mingw530_32\bin;%PATH%
echo.
cd %~dp0


REM add the environment variable UJPSPATH
echo add environment variable UJPSPATH
setx UJPSPATH %~dp0
echo.
echo.


If not exist bin mkdir bin
cd bin
If not exist ControllersPlugins mkdir ControllersPlugins
cd ..


REM compilation and deployment of CleanQtProjects
cd utils/CleanQtProjects
call build_CleanQtProjects_fct.bat
cd ../..


REM compilation of static lib HttpServer
cd 3rdparty/HttpServer/src
echo compiling HttpServer
echo.
qmake
mingw32-make release
echo.
echo.
cd ../../..


REM compilation of static lib Settings
cd src/StaticLibs/Settings
call build_Settings_fct.bat
cd ../../..


REM compilation of static lib VigemWrapper
cd src/StaticLibs/VigemWrapper
call build_VigemWrapper_fct.bat
cd ../../..


REM compilation of static lib QtGameControllerModif
cd src/StaticLibs/QtGameControllerModif
call build_QtGameControllerModif_fct.bat
cd ../../..


REM compilation of static libRealJoysticks
cd src/StaticLibs/RealJoysticks
call build_RealJoysticks_fct.bat
cd ../../..


REM build in parallel:
REM - AxesCurves
REM - ControllersInfo
REM - Monitoring
REM - ControllersPlugins
REM - VirtualJoysticks+UjpsCore+UjpsMainApp (from this file)

cd src/AxesCurves
start cmd.exe /c build_AxesCurves_fct.bat
cd ../..
cd src/ControllersInfo
start cmd.exe /c build_ControllersInfo_fct.bat
cd ../..
cd src/Monitoring
start cmd.exe /c build_Monitoring_fct.bat
cd ../..
cd src/ControllersPlugins
call build_ControllersPlugins.bat
cd ../..


REM compilation of static lib VirtualJoysticks
cd src/StaticLibs/VirtualJoysticks
call build_VirtualJoysticks_fct.bat
cd ../../..


REM compilation of static lib UjpsCore
cd src/StaticLibs/UjpsCore
call build_UjpsCore_fct.bat
cd ../../..


REM compilation and deployment of UJPS main app
cd src/UjpsMainApp
call build_UJPS_main_app_fct.bat
cd ../..


echo finished
pause

