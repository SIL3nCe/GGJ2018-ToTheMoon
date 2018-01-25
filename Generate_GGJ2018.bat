SET DEVLINE_DIR=%~dp0/../../Shine/DevLine_IOS
SET PROJECT_LOCATION=../

SET SHINE_EDITOR_EXT_DIR=%DEVLINE_DIR%/Build/Win32_VS2015/Compiled/Bin/x86/Extensions
SET SHSDK_EDITOR_LIBRARIES=%DEVLINE_DIR%/Build/Win32_VS2015/Compiled/Lib/x86/ShSDK_Editor_Debug.lib

SET SHINE_SDK_LIB_PATH_WIN32=%DEVLINE_DIR%/Build/Win32_VS2015/Compiled/Lib/
		
mkdir Build
cd Build
cmake -G "Visual Studio 14 2015" -DSHINE_INTERNAL=1 -DShSDK_DIR="%SHINE_SDK_LIB_PATH_WIN32%/x86/cmake" -DCMAKE_CONFIGURATION_TYPES=Debug;Release -DSHSDK_EDITOR_LIBRARIES=%SHSDK_EDITOR_LIBRARIES% -DSHINE_EDITOR_EXT_DIR=%SHINE_EDITOR_EXT_DIR% %PROJECT_LOCATION%
cd ..

pause