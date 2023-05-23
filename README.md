# snepk
A simple implementation of the snake game in C, for Windows.

## Why?
Long overdue for me, it feels like writing an implementation of Snake is something everyone who's into C should ever try to do, so here's mine.

While there is no shortage of examples for how to write Snake in C on the internet, I just wanted to share my take on it, properly commented and whatnot.

The main way it stands on it's own is having a separate thread for input handling, which avoids the annoying delay between inputs found in other "basic" implementations.

![Screenshot](https://github.com/markski1/snake/assets/22557859/5b57a424-0124-4a1f-bd09-a3dab60feef6)

Build: gcc -pthread snake.c -O2 -o snepk.exe