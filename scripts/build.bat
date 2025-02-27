@echo off

:: Compile Assets
cd compile

:: Build main
echo --- SDCC compiling
:: TO EXPLORE: --max-allocs-per-node 50000 instead of --opt-code-speed
:: `--std-sdcc23` enables SDCC's extensions to C23, eg native 0b binary literals
for %%f in (..\src\*.c) do sdcc --std-sdcc23 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

for %%f in (..\src\engine\*.c) do sdcc --std-sdcc23 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

for %%f in (..\src\helpers\*.c) do sdcc --std-sdcc23 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

for %%f in (..\src\scenes\*.c) do sdcc --std-sdcc23 -c -mz80 --opt-code-speed ^
--peep-file .\smslib\peep-rules.txt "%%f" -DPAL_MACHINE %DEBUG%

:: Link
echo --- SDCC linking
:: On bank numbering: https://www.smspower.org/forums/19430-DevkitSMSBankingCodeQuestions#124958
:: add -Wl-b_BANKn=0xn4000 or -Wl-b_BANKn=0xn8000 etc. as needed, along with the bankn.rel
sdcc -o da-invasion.ihx -mz80 --no-std-crt0 --data-loc 0xC000 ^
-Wl-b_BANK2=0x28000 -Wl-b_BANK3=0x38000 -Wl-b_BANK4=0x48000 -Wl-b_BANK5=0x58000 ^
smslib/crt0_sms.rel ^
main.rel config_scenes.rel ^
console_init.rel palettes.rel scenes.rel sprites.rel tilemap.rel ^
memcpy_expand_byte.rel ps_rand.rel screen_buffer.rel scroll_interrupt.rel sintab.rel ^
default.rel city.rel credits.rel eye.rel fire.rel lady.rel logo.rel plasma.rel sineline.rel skull.rel type.rel ^
SMSlib.lib psglib/PSGlib_MB.rel ^
bank2.rel bank3.rel bank4.rel bank5.rel %DEBUG%

:: Execute
:: If `makesms` is used, banks must use 0xn4000 or 0xn8000 where n is the bank number
:: If `ihx2sms` is used, banks must use 0x4000 or 0x8000 -- ihx2sms is legacy; makesms is preferred
echo --- Converting to SMS ROM
makesms da-invasion.ihx da-invasion.sms

:: Move to dist
IF EXIST "da-invasion.cdb" move da-invasion.cdb ../dist
move da-invasion.sms ../dist

cd ..
echo --- Build done!
