@echo off

:: Needs Java to be installed, of course
for %%f in (.\assets\music\*.vgm) do ^
java -jar .\utils\psgtool\PSGTool.jar %%f | echo Compiling %%f

echo === All done! ===
