# Darkest Room
Darkest Room is an ASCII dungeon crawler game written in C++ with the use of the ncurses library.

# Installation

## Linux

Install the **gcc** and **ncurses-devel** ( or **libncurses5-dev** ) packages with your package manager if you don't have them already, then run the following command to compile the game's code: 

`g++ main.cpp -lncurses`

After that, run the executable file (named `a.out` by default).

## Windows

Open the compiled executable file, OR, if it doesn't work, you can compile it yourself by doing the following:

Download MSYS2, or any other environment that lets you install the needed libraries and packages.
If you use MSYS2, you can install the g++ compiler and the required library for the game with this command:

`pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain ncurses-devel`

Then, give the command prompt the ability to compile by following point number 7 of [this guide,](https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites)
and finally compile by entering the directory where *main.cpp* is located and running this command:

`g++ main.c -o darkestroom.exe -lncurses -DNCURSES_STATIC`

Now, if you've done everything right, you should have the executable file in the same directory!
