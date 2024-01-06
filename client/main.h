#pragma once

// Library header:

#include "engine.h"
#include "node.h"
#include <mesh.h>
#include <light.h>

// C/C++:
#include <iostream>
#include <fstream>
#include <glm/gtx/string_cast.hpp>

// Constants:
#define PLAYGROUND_SIZE 6
#define BLOCK_SIZE 2.25f
////////////////////
// Global variables
////////////////////
// Matrixes
std::pair<int, unsigned int> matrix[PLAYGROUND_SIZE + 2][PLAYGROUND_SIZE + 2];
bool positioningMatrix[PLAYGROUND_SIZE + 2][PLAYGROUND_SIZE + 2];

// Window size
int width = 640;
int height = 480;

// Game vars
int gameDifficulty = -1;
int numberOfMoves = 0;
int numberOfCars = 0;
bool gameFinished = false;
bool canMove = true;

// Cameras
Camera* cameras[3];

// Fps calculation
int fc;
int fps;


// Object blinking vars
Node* pickedObject = nullptr;
glm::vec4 lastObjectEmission;
static float range = .5f;
static float step = .01f;
static float blinkStep = 0.0f;
bool blink = false;
bool blinkerTimerStarted = false;


// Other vars
int winningAnimationCounter = 0;


//////////
// METHODS
//////////
//CALLBACKS
void getPickedObject(Node* n, bool mousePressed);
void specialCallback(int key, int x, int y);
void keyboardCallback(unsigned char key, int x, int y);
void handleWindowResize(int w, int h);

//SCENE
std::vector<std::vector<int>> loadGameDifficulty();
void loadScene(std::string pathName);
void fillInitialPositioningMatrix();

//CAMERA
void loadCameras();
void rotateCamera(int value);

//FPS
void updateFPS(int value);

//CARS METHODS
void moveWinningCar(int value);
void loadCars();
void makeObjectBlink(Node* obj);
void updateBlinking(int value);
void blinkLight(int value);
std::vector<int> getCarDataFromId(unsigned int id);

// INIT
void init(int argc, char* argv[]);