@echo off

set StoreUserConfigLocation=%LOCALAPPDATA%\Packages\Microsoft.FlightSimulator_8wekyb3d8bbwe\LocalCache\UserCfg.opt
set SteamUserConfigLocation=%APPDATA%\Microsoft Flight Simulator\UserCfg.opt

if exist "%StoreUserConfigLocation%" (
	set UserConfigFileLocation=%StoreUserConfigLocation%
	goto CopyPackage
) else (
	if exist "%SteamUserConfigLocation%" (
		set UserConfigFileLocation=%SteamUserConfigLocation%
		goto CopyPackage
	) else (
		echo "Failed to locate UserCfg.opt"
		goto Exit
	)
)


:CopyPackage
for /f "tokens=1,*" %%a in ( 'findstr /C:"InstalledPackagesPath" "%UserConfigFileLocation%"' ) do (
	set PackagesDirectory=%%b
)
set PackagesDirectory=%PackagesDirectory:"=%
set CommunityDirectory=%PackagesDirectory%\Community

cd ..\..\Packages\

set SourcePackageDirectory=%cd%\Built\Packages\meridian-simcache
set DestinationPackageDirectory=%CommunityDirectory%\meridian-simcache

if exist "%SourcePackageDirectory%" (
	if exist "%DestinationPackageDirectory%" (
		rmdir /s /q "%DestinationPackageDirectory%"
	)
	robocopy "%SourcePackageDirectory%" "%DestinationPackageDirectory%" /E
)

:Exit