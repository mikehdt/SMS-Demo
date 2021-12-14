# Sega Master System Demo

I'm making a mess learning stuff about coding for the Sega Master System. Being helped along by some much more clever people who _actually_ know what they're doing.

Some basic settings exist for VSCode. I'm currently building on Windows, but as I do cross-platform I may aim to make it also as Mac-friendly as possible (some third-party tooling notwithstanding).

## Goals

-   Have a sane sort of code/asset build pipeline
-   Have C remote debugging with Emulicious
-   Draw a picture to the screen

## Dependencies

It uses [devkitSMS](https://github.com/sverx/devkitSMS) as a basis for doing all its fancy stuff.

Code is compiled with [SDCC](http://sdcc.sourceforge.net/) `4.1.12` pre-release (`4.1.0` is also compatible, but may need the `--sdcccall 0` flags removed from `scripts/build.bat`)

I've added the [STMcomp plugin](https://github.com/sverx/STMcomp) by sverx to the `bmp2tile` utility here, needed for using STM compressed tilemaps. It's nifty.
