@echo off

:: Compile Assets
cd compile

:: Build main
echo === SDCC compiling ===
:: `--std-sdcc11` enables SDCC's extensions to C11, eg native 0b binary literals
for %%f in (..\src\*.c) do sdcc --std-sdcc11 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

for %%f in (..\src\engine\*.c) do sdcc --std-sdcc11 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

for %%f in (..\src\helpers\*.c) do sdcc --std-sdcc11 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

for %%f in (..\src\scenes\*.c) do sdcc --std-sdcc11 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

:: Link
echo === SDCC linking ===
:: add -Wl-b_BANK3=0x8000 etc. as needed
sdcc -o demo.ihx -mz80 --no-std-crt0 --data-loc 0xC000 -Wl-b_BANK2=0x8000 -Wl-b_BANK3=0x8000 ^
smslib\crt0_sms.rel ^
main.rel config_scenes.rel ^
console_init.rel global_helpers.rel global_variables.rel palettes.rel scenes.rel sprites.rel tilemap.rel ^
memcpy_expand_byte.rel ps_rand.rel screen_buffer.rel scroll_interrupt.rel sintab.rel ^
default.rel city.rel eye.rel fire.rel logo.rel plasma.rel scroller.rel sineline.rel sphere.rel type.rel ^
SMSlib.lib psglib/PSGlib.rel ^
bank2.rel bank3.rel %DEBUG%

:: Execute
echo === Converting to SMS ROM ===
ihx2sms demo.ihx demo.sms
:: The makesms app also exists, but seems to result in a broken ROM?

:: Move to dist
IF EXIST "demo.cdb" move demo.cdb ../dist
move demo.sms ../dist

cd ..
echo === All done! ===
