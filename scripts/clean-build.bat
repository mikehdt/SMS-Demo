@echo off

:: Compile Assets
cd compile
echo === Tidying up build artifacts ===
@REM REL files are used for linking, but may need cleaning if stale ones exist
del *.rel > nul
@REM Note: If asm are present, Emulicious extension's debugger gets confused
del *.asm > nul
@REM These are used for debugging assembly
del *.lst > nul
del *.sym > nul
@REM Everything else...
del *.adb > nul
del *.ihx > nul
del *.lk > nul
del *.map > nul
del *.noi > nul

cd ..

:: Dist Output
cd dist
echo === Tidying up distribution folder ===
del *.cdb > nul
del *.sms > nul

cd ..

echo === Done tidying ===
