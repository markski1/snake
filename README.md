# snepk
A simple implementation of the snake game in C, which works on Windows and Linux*.

## Why?
Long overdue for me, it feels like writing an implementation of Snake is something everyone who's into C should ever try to do, so here's mine.

While there is no shortage of examples for how to write Snake in C on the internet, I just wanted to share my take on it, properly commented and whatnot.

My objectives for it:

- [x] Code must be no more than 512 lines
- [x] Game must weight no more than 32 kb
- [x] Must use no more than 1 Mb of RAM during runtime (not counting the terminal application's memory usage).
- [x] Have good movement. Snake C implementations will sometimes have a delay on inputs, or miss inputs in quick sucession.
- [ ] Work on both Windows and Linux (Failure explained below)

![Screenshot](https://github.com/markski1/snepk/assets/22557859/6886941a-4433-4e59-9654-9773e7c22a94)

Usage: Control with WASD. Exit with 'o'.

### Windows:
Builds and works perfectly.
Build with gcc: `gcc -pthread -s snake.c -O1 -o snepk.exe`

### Linux:
Builds, and ALMOST works.
Namely there is an issue with the terminal update rate that I cannot figure out.
The terminal will only update while a key is being held down which makes the game barely playable.

Build linux: `gcc -pthread -s snake.c -O1 -o snepk`
