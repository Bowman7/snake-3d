#!/bin/bash

g++ src/main.cpp src/glad.c src/game.cpp src/snake.cpp src/shader.cpp src/camera.cpp src/fruit.cpp src/grid.cpp src/python.cpp src/screen.cpp src/tx_test.cpp src/music.cpp src/text.cpp  -lm -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lglfw3 -L/usr/local/lib/ -lIrrKlang -I/usr/local/include/freetype2 -lfreetype



