#!/bin/bash

g++ main.cpp glad.c game.cpp snake.cpp shader.cpp camera.cpp fruit.cpp grid.cpp python.cpp screen.cpp tx_test.cpp music.cpp text.cpp  -lm -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lglfw3 -L/usr/local/lib/ -lIrrKlang -I/usr/local/include/freetype2 -lfreetype



