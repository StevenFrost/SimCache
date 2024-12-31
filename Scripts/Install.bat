cd ..
set RootDirectory=%cd%

:: Install git submodules
git submodule update --init

:: Setup EFB API workspace (temporary)
cd %RootDirectory%\Packages\PackageSources\meridian-simcache\EFB\efb_api
call npm install

:: Setup EFB App workspace
cd %RootDirectory%\Packages\PackageSources\meridian-simcache\EFB\SimCache
call npm install
