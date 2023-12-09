@echo off

:: Assets
cd assets

echo === Cleaning assets starting ===
del *.bin > nul
del *.stmcompr > nul
del *.psgcompr > nul
echo === Cleaning assets done ===

cd ..
