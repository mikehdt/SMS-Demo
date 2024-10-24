# Invasion

by disasterarea

Code by darkowl with help from bananaboy and sh0ck
Art by darkowl
Music by cTrix

_For Pascal and Rafael_

## Dependencies

It uses [devkitSMS](https://github.com/sverx/devkitSMS) as a basis for doing all its fancy stuff.

Code is compiled with [SDCC](http://sdcc.sourceforge.net/) `4.4.0`.

The [bmp2tile](https://github.com/maxim-zhao/bmp2tile) project is included here for compiling assets, but I might move it to be an external dep later. For cross-platform support later, the [png2tile](https://github.com/yuv422/png2tile) looks like a great starting point.

I've added the [STMcomp plugin](https://github.com/sverx/STMcomp) by sverx to the `bmp2tile` utility here, needed for using STM compressed tilemaps. It's nifty.

Using VScode, make sure to install the [Emulicious Debugger](https://marketplace.visualstudio.com/items?itemName=emulicious.emulicious-debugger).

## Building

Only currently builds on Windows, though it'd be nice to one day have cross-platform building.

I need to expand this bit, but the basics is that once the external deps are in place, you can use VScode `Ctrl+Shift+P` > `Run Task` to first run `Compile Assets`.

Then you can use the `F5` key to automatically compile and attach the Emulicious Debugger to VScode and Emulicious, or use `Run Task` again to `Build (Debug)` and run it manually.

I'm just figuring things out for now, really.

## Thanks

-   The [SMS Power Forums](https://www.smspower.org/forums) have many super helpful and smart people
-   The [Gotris](https://gitlab.com/1985Alternativo/gotris) project by kusfo has been invaluable for learning. I've shamelessly borrowed some techniques, and am indebted to the knowledge contained therein and its author
-   The [devkitSMS](https://github.com/sverx/devkitSMS) project by sverx made setting up easy, and it makes getting started with the Sega Master System fast and fun
-   The [bmp2tile](https://github.com/maxim-zhao/bmp2tile) project by Maxim makes getting assets into a format suitable for the SMS really easy
-   The [Emulicious](https://emulicious.net/) emulator has fantastic support for SDCC's debug output being bridged across to VScode, making working with the SMS so much easier, and Calindro has been very helpful
-   My friends bananaboy, sh0ck, null, and cTrix, with whom we made a little SMS demo for the [Syntax Demoparty](https://syntaxparty.org/) in 2021. The experience making the art for it, even though simple, inspired me to learn about coding for the SMS so we can push the art even _further_
