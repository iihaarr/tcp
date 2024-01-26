set BUILD_DIR=build
set GENERATOR=Visual Studio 17 2022

if not exist %~dp0%BUILD_DIR%\ (mkdir %BUILD_DIR%)
cd %~dp0%BUILD_DIR%
cmake .. -G "%GENERATOR%"
pause