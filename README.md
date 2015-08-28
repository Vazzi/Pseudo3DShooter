###Pseudo 3D Game

This project is about a game that looks like old Wolfenstein3D. I would like to learn how to do it, so I created this project. I do not know how I will do it or how it will look like. It is just for my study purposes.

## Current state

Really simple engine. I created a 3D world using Ray casting. Data and level information are loaded from json files. Every screen is represented as a state and is handled by state machine. Sound is handled by SDL2_mixer.

Player can walk and shoot but there are no enemies.

## Requirements

cmake 3.1+

SDL2, SDL2_image and SDL2_mixer

## Build

1. cmake .
2. make
3. ./bin/Game

