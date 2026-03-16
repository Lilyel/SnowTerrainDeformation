
set platform=%1
set configuration=%2

if not exist "..\Binaries\%platform%\%configuration%\glew32.dll" (set doUpdate=1)
if not exist "..\Binaries\%platform%\%configuration%\glfw3.dll" (set doUpdate=1)

if %configuration% EQU "Release" (
set libAssimp=assimp-vc142-mt.dll
) ELSE (
set libAssimp=assimp-vc142-mtd.dll
)

if not exist "..\Binaries\%platform%\%configuration%\%libAssimp%" (set doUpdate=1) 


if defined doUpdate (

@echo Updating %platform%-%configuration% dependencies ...
	if not exist "..\Binaries\%platform%" mkdir ..\Binaries\%platform% >nul
	if not exist "..\Binaries\%platform%\%configuration%" mkdir ..\Binaries\%platform%\%configuration% >nul
	
	copy /y "..\Engine\Libraries\Glew\Binaries\%platform%\%configuration%\glew32.dll" "..\Binaries\%platform%\%configuration%\" >nul
	copy /y "..\Engine\Libraries\GLFW\Binaries\%platform%\%configuration%\glfw3.dll" "..\Binaries\%platform%\%configuration%\" >nul	
	copy /y "..\Engine\Libraries\Assimp\Binaries\%platform%\%configuration%\%libAssimp%" "..\Binaries\%platform%\%configuration%\" >nul
	
	@echo Updated
)
