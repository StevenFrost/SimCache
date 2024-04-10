@echo off

set PackageToolLocation=%MSFS_SDK%Tools\bin\fspackagetool.exe
set StoreUserConfigLocation=%LOCALAPPDATA%\Packages\Microsoft.FlightSimulator_8wekyb3d8bbwe\LocalCache\UserCfg.opt
set SteamUserConfigLocation=%APPDATA%\Microsoft Flight Simulator\UserCfg.opt

cd ..\Packages\

if not exist "%PackageToolLocation%" (
    echo "Unable to locate fspackagetool.exe"
    goto Exit
)

if exist "%StoreUserConfigLocation%" (
	goto Store
) else (
	if exist "%SteamUserConfigLocation%" (	
		goto Steam
	) else (
		echo "Failed to locate UserCfg.opt"
		goto Exit
	)
)


:Store
start "" "%PackageToolLocation%" ".\SimCache.xml" -nopause
goto Exit


:Steam
start "" "%PackageToolLocation%" ".\SimCache.xml" -forcesteam
goto Exit


:Exit