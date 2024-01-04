#pragma once

#include <string>
#include <glm/glm.hpp>

void specialCallback(int, int, int);
void keyboardCallback(unsigned char, int, int);

void loadScene(std::string);
void loadCameras();
void moveWinningCar(int value);
void updateBlinking(int value);

void loadCars();

void init();

