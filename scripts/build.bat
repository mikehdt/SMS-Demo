@echo off

:: Compile Assets
cd compile

:: Build main
echo *** SDCC building source ***
:: `--sdcccall 0` tells SDCC 4.1.12+ not to use its new breaking fn calls yet
:: However, SDCC 4.1.12+ makes the debugger very unhappy, not using it for now
for %%f in (..\src\*.c) do sdcc -c -mz80 "%%f" -DPAL_MACHINE %DEBUG%
for %%f in (..\src\examples\*.c) do sdcc -c -mz80 "%%f" -DPAL_MACHINE %DEBUG%
echo *** SDCC building complete ***

:: Link
echo *** SDCC linking source ***
sdcc -o demo.ihx -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 smslib/crt0_sms.rel bank2.rel main.rel utils.rel picture.rel SMSlib.lib %DEBUG%
echo *** SDCC linking complete ***

:: Execute
echo *** Converting to SMS ROM ***
ihx2sms demo.ihx demo.sms
:: The makesms app also exists, but seems to result in a broken ROM?

:: Tidy up
echo *** Tidying up ***
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
