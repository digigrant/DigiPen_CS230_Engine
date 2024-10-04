@echo off
setlocal

set "config=%1"
if "%config%"=="Debug" (
    set "dglLib=DGL_d.dll"
) else (
    if "%config%"=="Release" (
        set "dglLib=DGL.dll"
    ) else (
        echo Invalid configuration: %config%. Valid configurations are: Debug, Release.
        exit /b 1
    )
)

set "projectRoot=%~dp0.."
set "binaryDir=%projectRoot%\bin\x64\%config%"
set "dglLibPath=%projectRoot%\DGL\lib\x64\%dglLib%"
set "assetsSourcePath=%projectRoot%\Assets"
set "dataSourcePath=%projectRoot%\Data"
set "assetsDestPath=%binaryDir%\Assets"
set "dataDestPath=%binaryDir%\Data"

if not exist "%binaryDir%" mkdir "%binaryDir%"
if not exist "%assetsDestPath%" mkdir "%assetsDestPath%"
if not exist "%dataDestPath%" mkdir "%dataDestPath%"

xcopy "%dglLibPath%" "%binaryDir%\" /d /y
xcopy "%assetsSourcePath%" "%assetsDestPath%" /s /d /y
xcopy "%dataSourcePath%" "%dataDestPath%" /s /d /y

endlocal
