@echo off

set PackageToolLocation=%MSFS2024_SDK%Tools\bin\fspackagetool.exe
set StoreUserConfigLocation=%LOCALAPPDATA%\Packages\Microsoft.Limitless_8wekyb3d8bbwe\LocalCache\UserCfg.opt
set SteamUserConfigLocation=%APPDATA%\Microsoft Flight Simulator 2024\UserCfg.opt

cd ..\..
set RootDirectory=%cd%


:: Build the EFB app
cd %RootDirectory%\Packages\PackageSources\meridian-simcache\EFB\SimCache\
call npm run build


:: Build the MSFS Package
cd %RootDirectory%\Packages\

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