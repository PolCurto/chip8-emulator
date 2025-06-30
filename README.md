# Chip-8 Emulator
A Chip-8 emulator written in C++. It uses SDL3 to manage the window and inputs.

![Astro Dodge](images/AstroDodge.png)
*Astro Dodge*

![Tetris](images/Tetris.png)
*Tetris*

![Most Dangerous Game](images/MostDangerousGame.png)
*Most Dangerous Game*

For now this emulator lacks the audio features

## How to Run
To run this emulator, download the latest release and execute it through the command line with the ROM you want to launch, like the following:

    ./Chip-8 <ROM file>

In the /Roms directory there are all the ROMs I tested, they should work fine. There are a lot more in the internet if you want ot try them out.

## Dependencies

This project depends on [SDL3](https://github.com/libsdl-org/SDL) for window management and input.  If you want to build it, you must install SDL3 development files as well as Visual Studio

## References
The main resource I used to develop this emulator: https://tobiasvl.github.io/blog/write-a-chip-8-emulator/