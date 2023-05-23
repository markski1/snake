# snepk
A simple implementation of the snake game in C, which works on Windows and Linux*.

## Why?
Long overdue for me, it feels like writing an implementation of Snake is something everyone who's into C should ever try to do, so here's mine.

While there is no shortage of examples for how to write Snake in C on the internet, I just wanted to share my take on it, properly commented and whatnot.

The main way it stands on it's own is having a separate thread for input handling, which avoids the annoying delay between inputs found in other "basic" implementations.

![Screenshot](https://github.com/markski1/snake/assets/22557859/5b57a424-0124-4a1f-bd09-a3dab60feef6)

Usage: Control with WASD. Exit with ESC.

### Windows:
Builds and works perfectly.
Build with gcc: `gcc -pthread snake.c -O2 -o snepk.exe`

### Linux:
Builds, and ALMOST works.
Namely there is an issue with the terminal update rate that I cannot figure out.
The terminal will only update while a key is being held down which makes the game barely playable.

Build linux: `gcc -pthread snake.c -O2 -o snepk`