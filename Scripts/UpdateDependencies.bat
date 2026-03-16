echo off

@echo Updating Win32-Debug ...
if not exist "..\Binaries\Win32\Debug\" mkdir ..\Binaries\Win32\Debug\ >nul
copy /y "..\Engine\Libraries\Glew\Binaries\Win32\Debug\glew32.dll" "..\Binaries\Win32\Debug\" >nul
copy /y "..\Engine\Libraries\GLFW\Binaries\Win32\Debug\glfw3.dll" "..\Binaries\Win32\Debug\" >nul
copy /y "..\Engine\Libraries\Assimp\Binaries\Win32\Debug\assimp-vc142-mtd.dll" "..\Binaries\Win32\Debug\" >nul
@echo Updated

@echo Updating Win32-Release ...
if not exist "..\Binaries\Win32\Release\" mkdir ..\Binaries\Win32\Release\ >nul
copy /y "..\Engine\Libraries\Glew\Binaries\Win32\Release\glew32.dll" "..\Binaries\Win32\Release\" >nul
copy /y "..\Engine\Libraries\GLFW\Binaries\Win32\Release\glfw3.dll" "..\Binaries\Win32\Release\" >nul
copy /y "..\Engine\Libraries\Assimp\Binaries\Win32\Release\assimp-vc142-mtd.dll" "..\Binaries\Win32\Release\" >nul
@echo Updated

@echo Updating x64-Debug ...
if not exist "..\Binaries\x64\Debug\" mkdir ..\Binaries\x64\Debug\ >nul
copy /y "..\Engine\Libraries\Glew\Binaries\x64\Debug\glew32.dll" "..\Binaries\x64\Debug\" >nul
copy /y "..\Engine\Libraries\GLFW\Binaries\x64\Debug\glfw3.dll" "..\Binaries\x64\Debug\" >nul
copy /y "..\Engine\Libraries\Assimp\Binaries\x64\Debug\assimp-vc142-mtd.dll" "..\Binaries\x64\Debug\" >nul
@echo Updated

@echo Updating x64-Release ...
if not exist "..\Binaries\x64\Release\" mkdir ..\Binaries\x64\Release\ >nul
copy /y "..\Engine\Libraries\Glew\Binaries\x64\Release\glew32.dll" "..\Binaries\x64\Release\" >nul
copy /y "..\Engine\Libraries\GLFW\Binaries\x64\Release\glfw3.dll" "..\Binaries\x64\Release\" >nul
copy /y "..\Engine\Libraries\Assimp\Binaries\x64\Release\assimp-vc142-mtd.dll" "..\Binaries\x64\Release\" >nul
@echo Updated
