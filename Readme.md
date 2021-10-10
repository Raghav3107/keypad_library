# Keypad Library for ESP32

The Keypad library is designed to easily integrate on any platform. Right now it is compatable with the ESP-IDF. It uses the standard method of selecting a row and scanning all the column to see which key may be pressed. 

Library test on 4x4 Matrix Keypad with ESP32 on ESP-IDF v4.2. Can support more that 4x4 keypad ( Not Tested ).

Features of this library are: Allows multiple, simultaneous keypresses.

## Library Structure

```
.
├── examples
│   ├── keypad_countdown_timer.c
│   ├── keypad_read_demo.c
│   └── keypad_read_simultaneous.c
├── Readme.md
├── simple arduino program
│   └── simple_keypad.ino
└── src
    ├── keypad.c
    └── keypad.h


```

Create the `issue` and `pull request` for new feature or fixes.