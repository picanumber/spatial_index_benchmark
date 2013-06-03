@echo off
set BLD=_build
IF NOT EXIST %~dp0\CMakeLists.txt GOTO :NOTSRC
IF NOT EXIST %~dp0\%BLD% mkdir %BLD%
cd _build
cmake -G "Visual Studio 11" ^
    -DBOOST_ROOT=D:\dev\boost\_svn\trunk ^
    ..

GOTO :EOF

:NOTSRC
echo cannot find sources in '%~dp0'