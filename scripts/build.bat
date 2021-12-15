@echo off

:: Compile Assets
cd compile

:: Build main
echo SDCC building source
:: `--sdcccall 0` tells SDCC 4.1.12+ not to use its new breaking fn calls yet
sdcc %DEBUG% --sdcccall 0 -c -mz80 ../src/main.c -DPAL_MACHINE
sdcc %DEBUG% --sdcccall 0 -c -mz80 ../src/examples/picture.c -DPAL_MACHINE
echo SDCC building complete

:: Link
echo SDCC linking source
sdcc -o demo.ihx %DEBUG% --sdcccall 0 -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 ../src/libs/crt0_sms.rel ../src/libs/SMSlib.lib main.rel picture.rel bank2.rel
echo SDCC linking complete

:: Execute
echo Converting to SMS ROM
ihx2sms demo.ihx demo.sms
:: The makesms app also exists, but seems to result in a broken ROM?

:: Tidy up
del *.adb > nul
del *.asm > nul
@REM del *.rel > nul
del *.ihx > nul
del *.lk > nul
del *.lst > nul
del *.map > nul
del *.noi > nul
del *.sym > nul

:: Move to dist
move demo.* ../dist

cd ..
