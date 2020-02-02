echo off


set UJPSGUIEXE=%~dp0\..\bin\UJPS.exe
set PROFILESPATH=%~dp0\..\Profiles
cd %PROFILESPATH%
%UJPSGUIEXE% ProfileTest\profileTest.pro 25 -play
echo.


pause

