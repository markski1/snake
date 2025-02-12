# snepk
A simple implementation of the snake game in C, which works on Windows.

While there is no shortage of examples for how to write Snake in C on the internet, I just wanted to have a go at a simple text-based game since I never made one, and Snake seemed ideal.

It does have something, quote unquote rare (for this format), which is to have a buffered keyboard input instead of the usual loop that comes with a bit of delay.

![Screenshot](https://github.com/markski1/snepk/assets/22557859/6886941a-4433-4e59-9654-9773e7c22a94)

Usage: Control with WASD. Exit with 'o'.

Build with gcc: `gcc -pthread -s main.c -O1 -o snepk.exe`