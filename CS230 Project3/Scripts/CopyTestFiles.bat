@echo off
setlocal

set "config=%1"
if NOT "%config%"=="Debug" (
	if NOT "%config%"=="Release" (
        echo Invalid configuration: %config%. Valid configurations are: Debug, Release.
        exit /b 1
    )
)

set "projectRoot=%~dp0.."
set "binaryDir=%projectRoot%\bin\x64\%config%"
set "testDataSourcePath=%projectRoot%\Tests\TestData"
set "testDataDestPath=%binaryDir%\TestData"

if not exist "%testDataDestPath%" mkdir "%testDataDestPath%"

xcopy "%testDataSourcePath%" "%testDataDestPath%" /s /d /y

endlocal
