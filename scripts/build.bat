@echo off

:: Compile Assets
cd compile

:: Build main
echo *** SDCC compiling ***
:: `--sdcccall 0` tells SDCC 4.1.12+ not to use its new breaking fn calls yet
:: However, SDCC 4.1.12+ makes the debugger very unhappy, not using it for now
:: `--std-sdcc11` enables SDCC's extensions to C11, eg native 0b binary literals
for %%f in (..\src\*.c) do sdcc --std-sdcc11 -c -mz80 --peep-file .\smslib\peep-rules.txt "%%f" --opt-code-speed -DPAL_MACHINE %DEBUG%
for %%f in (..\src\engine\*.c) do sdcc --std-sdcc11 -c -mz80 --peep-file .\smslib\peep-rules.txt "%%f" --opt-code-speed -DPAL_MACHINE %DEBUG%
for %%f in (..\src\helpers\*.c) do sdcc --std-sdcc11 -c -mz80 --peep-file .\smslib\peep-rules.txt "%%f" --opt-code-speed -DPAL_MACHINE %DEBUG%
for %%f in (..\src\scenes\*.c) do sdcc --std-sdcc11 -c -mz80 --peep-file .\smslib\peep-rules.txt "%%f" --opt-code-speed -DPAL_MACHINE %DEBUG%
echo *** SDCC compiling complete ***

:: Link
echo *** SDCC linking ***
sdcc -o demo.ihx -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 -Wl-b_BANK3=0x8000 smslib/crt0_sms.rel   main.rel   init_console.rel palettes.rel scenes.rel   clear_tilemap.rel memcpy_expand_byte.rel ps_rand.rel sintab.rel   default.rel fire.rel grid.rel intro.rel particles.rel plasma.rel scroller.rel sphere.rel sineline.rel type.rel   SMSlib.lib   bank2.rel bank3.rel   %DEBUG%
echo *** SDCC linking complete ***

:: Execute
echo *** Converting to SMS ROM ***
ihx2sms demo.ihx demo.sms
echo *** Converting to SMS ROM complete ***
:: The makesms app also exists, but seems to result in a broken ROM?

:: Move to dist
IF EXIST "demo.cdb" move demo.cdb ../dist
move demo.sms ../dist

cd ..
echo *** All done! ***
