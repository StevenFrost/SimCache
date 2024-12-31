@echo off

cd ..
set RootDirectory=%cd%

:: Remove C++ build output
rmdir /s /q %RootDirectory%\Built\

:: Remove MSFS Package output
rmdir /s /q %RootDirectory%\Packages\Built\

:: Clean EFB build output
cd %RootDirectory%\Packages\PackageSources\meridian-simcache\EFB\SimCache
call npm run clean:dist