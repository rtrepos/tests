echo avec compile %1

set PP_HOME=c:\tests\mingw_libs_conflict


set OLD_CD=%cd%
rmdir /Q /S %PP_HOME%\buildwin
rmdir /Q /S %PP_HOME%\installwin
if %1% == NO goto end

echo Avec compile

  
mkdir %PP_HOME%\buildwin
mkdir %PP_HOME%\buildwin\pmain
mkdir %PP_HOME%\buildwin\pdll1
mkdir %PP_HOME%\buildwin\pdll2
cd %PP_HOME%\buildwin\pdll1

echo %PATH%

cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=%PP_HOME%/installwin %PP_HOME%\pdll1
mingw32-make install 
cd %PP_HOME%\buildwin\pdll2
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=%PP_HOME%/installwin %PP_HOME%\pdll2
mingw32-make install 
cd %PP_HOME%\buildwin\pmain
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=%PP_HOME%/installwin %PP_HOME%\pmain
mingw32-make install
cd %OLD_CD%


set OLD_PATH=%PATH% 

if %1% == ERR goto error  
if %1% == OK goto ok  
  
:error   
set PATH=%PP_HOME%\installwin\lib2;%PATH%
goto end

:ok   
set PATH=%PP_HOME%\installwin\lib;%PATH%
goto end

:end

