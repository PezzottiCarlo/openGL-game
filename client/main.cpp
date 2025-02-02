﻿/**
 * @brief   A simple graphical engine library
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

 //////////////
 // #INCLUDE //
 //////////////

// Library headers:
#include "main.h"
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

// Matrixes
std::pair<int, unsigned int> matrix[PLAYGROUND_SIZE + 2][PLAYGROUND_SIZE + 2];
bool positioningMatrix[PLAYGROUND_SIZE + 2][PLAYGROUND_SIZE + 2];

// Initial window sizes
int width = 640;
int height = 480;

// Fps calculation
int fc;
int fps;
int numberOfMoves = 0;

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
bool gameFinished = false;
bool canMove = true;
int numberOfCars = 0;
int gameDifficulty = -1;
Camera* cameras[3];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /////////////////////
 // #HELPER METHODS //
 /////////////////////

// Get the right separator depending on the OS this program runs on
std::string getSeparator() {
#ifdef _WIN32
	return "\\";
#else
	return "/";
#endif
}


std::vector<int> getCarDataFromId(unsigned int id) {
    std::vector<int> results(3, 0);

	for (int i = 1; i < PLAYGROUND_SIZE + 1; i++) {
		for (int j = 1; j < PLAYGROUND_SIZE + 1; j++) {
			if (matrix[i][j].second == id) {
				results[0] = i;
				results[1] = j;
				results[2] = matrix[i][j].first;	// Direction code
				return results;
			}
		}
	}

	return {};
}

void getPickedObject(Node* n, bool mousePressed) {
	if (n != nullptr && mousePressed) {
		if (pickedObject != nullptr) {
			((Mesh*)pickedObject)->getMaterial()->setEmission(lastObjectEmission);
		}
		lastObjectEmission = ((Mesh*)n)->getMaterial()->getEmission();
		pickedObject = n;

		// Start blinker timer if it isn't already running
		if (!blinkerTimerStarted) {
			Engine::startTimer(updateBlinking, 10);
			blinkerTimerStarted = true;
		}
	}
}

void makeObjectBlink(Node* obj) {

	if (!(obj->getName().substr(0, 3) == "Car" || obj->getName().substr(0, 9) == "Limousine" || obj->getName().substr(0, 6) == "Police")) return;

	step = 0.01f;

	if (blink) {
		blinkStep += step;
		if (blinkStep > range)
			blink = false;
	}
	else {
		blinkStep -= step;
		if (blinkStep < 0.0f)
			blink = true;
	}

	((Mesh*)obj)->getMaterial()->setEmission(glm::vec4(blinkStep, blinkStep, blinkStep, 1.0f));
}

void updateBlinking(int value) {
	makeObjectBlink(pickedObject);
	Engine::startTimer(updateBlinking, 10);
}

void handleWindowResize(int w, int h) {
	width = w;
	height = h;
	Engine::reshapeCallback(w, h);
}

void updateFPS(int value) {
	fps = fc;
	fc = 0;
	Engine::startTimer(updateFPS, 1000);
}

void blinkLight(int value) {
	static bool blink = false;
	static Mesh* lamp_parent = (Mesh*)(Engine::getList()->getObject(1)->getParent());
	static Light* light = (Light*)(lamp_parent)->getChildren().at(0);
	static Mesh* light_bulbe = (Mesh*)(lamp_parent)->getChildren().at(1);
	static glm::vec4 light_bulbe_emission = light_bulbe->getMaterial()->getEmission();

	if (blink) {
		light->setIntensity(0.0f);
		light_bulbe->getMaterial()->setEmission(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		blink = false;
	}
	else {
		light->setIntensity(7.0f);
		light_bulbe->getMaterial()->setEmission(light_bulbe_emission);
		blink = true;
	}

	//random between 0.5 and 3 seconds
	int random = rand() % 2500 + 500;
	Engine::startTimer(blinkLight, random);
}

void rotateCamera(int value) {
	static bool rotationSense = false;
	static float angle = 0.0f;
	glm::mat4 currentTransform = cameras[2]->getTransform();
	float rotation = (rotationSense) ? -0.002f : 0.002f;

	currentTransform = glm::rotate_slow(currentTransform, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	cameras[2]->setTransform(currentTransform);

	if (angle > 1.5)
		rotationSense = true;
	else if (angle < 0.0f)
		rotationSense = false;
	angle += rotation;

	// Restart timer
	Engine::startTimer(rotateCamera, 10);
}

void moveWinningCar(int value) {
	glm::mat4 currentTransform = glm::translate(pickedObject->getTransform(), glm::vec3(-BLOCK_SIZE / 25, 0.0f, 0.0f));
	pickedObject->setTransform(currentTransform);
	Engine::postWindowRedisplay();
	Engine::refreshAndSwapBuffers();

	// Recall function
	if (winningAnimationCounter < 200) {
		canMove = false;
		Engine::startTimer(moveWinningCar, 10);
		winningAnimationCounter++;
	}
	else {
		gameFinished = true;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////
// CALLBACKS //
///////////////

/**
 * This callback gets invoked when a special character on the keyboard gets pressed.
 * @param key pressed keyboard key as integer
 * @param x mouse x position relative to the window when the key gets pressed
 * @param y mouse y position relative to the window when the key gets pressed
 */
void specialCallback(int key, int x, int y) {
	if (canMove) {
		// Retrieve data from selected car
		if (pickedObject == nullptr) return;

		std::vector<int> carData = getCarDataFromId(pickedObject->getId());
		if (carData.empty()) return;

		//convert to int array
		int i = carData[0];
		int j = carData[1];
		int d = carData[2];
		int carSize = (d == 1 || d == 2 || d == 5) ? 2 : 3;

		// Define if car can move vertically or horizontally
		bool canMoveVertical = (d == 1 || d == 3 || d == 5);
		bool canMoveHorizontal = (d == 2 || d == 4);

		glm::mat4 currentTransform = pickedObject->getTransform();

		switch (key) {
			case 100:	// Left arrow
				if (canMoveHorizontal) {
					// Check if cells on the left are empty
					if (!positioningMatrix[i][j - 1]) {
						currentTransform = glm::translate(currentTransform, glm::vec3(BLOCK_SIZE, 0.0f, 0.0f));
						matrix[i][j].second = 0;
						matrix[i][j - 1].first = matrix[i][j].first;
						matrix[i][j - 1].second = pickedObject->getId();
						matrix[i][j].first = 0;
						// Move position matrix elements
						positioningMatrix[i][j - 1] = true;
						positioningMatrix[i][j + carSize - 1] = false;
						numberOfMoves++;
					}
				}
				break;
			case 102:	// Right arrow
				if (canMoveHorizontal) {
					if (!positioningMatrix[i][j + carSize]) {
						currentTransform = glm::translate(currentTransform, glm::vec3(-BLOCK_SIZE, 0.0f, 0.0f));
						matrix[i][j].second = 0;
						matrix[i][j + 1].first = matrix[i][j].first;
						matrix[i][j + 1].second = pickedObject->getId();
						matrix[i][j].first = 0;
						// Move position matrix elements
						positioningMatrix[i][j + carSize] = true;
						positioningMatrix[i][j] = false;
						numberOfMoves++;
					}
				}
				break;
			case 101:	// Up arrow
				if (canMoveVertical) {
					if (!positioningMatrix[i - 1][j]) {
						currentTransform = glm::translate(currentTransform, glm::vec3(BLOCK_SIZE, 0.0f, 0.0f));
						matrix[i][j].second = 0;
						matrix[i - 1][j].first = matrix[i][j].first;
						matrix[i - 1][j].second = pickedObject->getId();
						matrix[i][j].first = 0;
						// Move position matrix elements
						positioningMatrix[i - 1][j] = true;
						positioningMatrix[i + carSize - 1][j] = false;
						numberOfMoves++;
					}
				}
				break;
			case 103:	// Down arrow
				if (canMoveVertical) {
					// Check if red car is pointing towards exit -> win
					// Exit block is [5][3] (in game coords. [4][2])
					if (pickedObject->getName() == "Car" && i == 5 && j == 3) {

						// Disable mouse
						Engine::removeObjectPickedCallback();

						// Move camera
						Engine::setActiveCamera(1);
						Engine::refreshAndSwapBuffers();

						// Start animation
						Engine::startTimer(moveWinningCar, 10);

					}
					else if (!positioningMatrix[i + carSize][j]) {
						currentTransform = glm::translate(currentTransform, glm::vec3(-BLOCK_SIZE, 0.0f, 0.0f));
						matrix[i][j].second = 0;
						matrix[i + 1][j].first = matrix[i][j].first;
						matrix[i + 1][j].second = pickedObject->getId();
						matrix[i][j].first = 0;
						// Move position matrix elements
						positioningMatrix[i + carSize][j] = true;
						positioningMatrix[i][j] = false;
						numberOfMoves++;
					}
				}
				break;
			}

		pickedObject->setTransform(currentTransform);
		Engine::postWindowRedisplay();
	}
}

void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		case '1':
			Engine::setActiveCamera(0);
			break;
		case '2':
			Engine::setActiveCamera(1);
			break;
		case '3':
			Engine::setActiveCamera(2);
			break;
		case 'n':
			if (gameFinished) {
				// Start new game
				canMove = true;
				gameFinished = false;

				// Reenable mouse
				Engine::setObjectPickedCallback(getPickedObject);

				// Reset variables
				numberOfMoves = 0;
				winningAnimationCounter = 0;
				for (int i = 0; i < numberOfCars; i++)
					Engine::getList()->popEntry();
				numberOfCars = 0;

				// Refill matrixes and other elements
				for (int i = 0; i < PLAYGROUND_SIZE + 2; i++) {
					for (int j = 0; j < PLAYGROUND_SIZE + 2; j++) {
						positioningMatrix[i][j] = false;
					}
				}

				fillInitialPositioningMatrix();
				loadCars();
				Engine::setActiveCamera(0);
			}
			break;
	}
	Engine::postWindowRedisplay();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////
// LOADING FUNCTIONS //
///////////////////////

std::vector<std::vector<int>> loadGameDifficulty() {
	std::string text;
	int diff = 1;

	// Read from the text file
	std::ifstream prefsFile(".." + getSeparator() + "preferences" + getSeparator() + "preferences.json");

	// Use a while loop together with the getline() function to read the file line by line
	while (std::getline(prefsFile, text)) {
		// Retrieve game difficulty
		if (text.substr(0, 14) == "\t\"difficulty\":") {
			diff = text[15] - '0';
			break;
		}
	}

	// Update global difficulty
	gameDifficulty = diff;

	// Close the file
	prefsFile.close();

	// Set initialMatrix
	std::vector<std::vector<int>> initialMatrix;

	switch (gameDifficulty) {
	case 2:
		initialMatrix = {
			{ 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 },
			{ 6 , 2 , 0 , 0 , 3 , 1 , 0 , 6 },
			{ 6 , 1 , 0 , 5 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 0 , 0 , 1 , 6 },
			{ 6 , 3 , 4 , 0 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 0 , 2 , 0 , 6 },
			{ 6 , 6 , 7 , 6 , 6 , 6 , 6 , 6 }
		};
		break;

	case 3:
		initialMatrix = {
			{ 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 },
			{ 6 , 2 , 0 , 5 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 3 , 2 , 0 , 6 },
			{ 6 , 3 , 3 , 0 , 0 , 0 , 1 , 6 },
			{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 2 , 0 , 1 , 6 },
			{ 6 , 0 , 0 , 4 , 0 , 0 , 0 , 6 },
			{ 6 , 6 , 6 , 7 , 6 , 6 , 6 , 6 }
		};
		break;

	default:
		initialMatrix = {
			{ 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 },
			{ 6 , 2 , 0 , 0 , 3 , 1 , 0 , 6 },
			{ 6 , 0 , 0 , 5 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
			{ 6 , 3 , 4 , 0 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
			{ 6 , 0 , 0 , 0 , 0 , 2 , 0 , 6 },
			{ 6 , 6 , 7 , 6 , 6 , 6 , 6 , 6 }
		};
		break;
	}

	return initialMatrix;
}
void loadScene(std::string pathName) {
	Engine::loadScene(pathName);
}
void fillInitialPositioningMatrix() {
	// Put borders to "true" value
	for (int i = 0; i < PLAYGROUND_SIZE + 2; i++) {
		for (int j = 0; j < PLAYGROUND_SIZE + 2; j++) {
			if (i == 0 || i == PLAYGROUND_SIZE + 1) {
				positioningMatrix[i][j] = true;
			}
			else if (j == 0 || j == PLAYGROUND_SIZE + 1) {
				positioningMatrix[i][j] = true;
			}
		}
	}
}


//CAMERA
void loadCameras() {

	Camera* c1 = new Camera("camera1");
	c1->setUserTransform(0, 15.0f, 0, -90.0f, 0, -90.0f);
	Camera* c2 = new Camera("camera2");
	c2->setUserTransform(-20.0f, 5.0f, 5.0f, 0, -75.0f, 0);
	Camera* c3 = new Camera("camera3");
	c3->setUserTransform(0.0f, 5.0f, 12.0f, 0, -45.0f, 0);

	Engine::addCamera(c1);
	Engine::addCamera(c2);
	Engine::addCamera(c3);

	cameras[0] = c1;
	cameras[1] = c2;
	cameras[2] = c3;

	Engine::setActiveCamera(0);
}

void loadCars() {

	// Populate initialMatrix
	std::vector<std::vector<int>> initialMatrix = loadGameDifficulty();

	for (int i = 1; i < PLAYGROUND_SIZE + 1; i++) {
		for (int j = 1; j < PLAYGROUND_SIZE + 1; j++) {

			// Setup matrix
			if (initialMatrix[i][j] >= 1 && initialMatrix[i][j] <= 5) {
				// Cell contains car
				std::string carName;
				numberOfCars++;

				switch (initialMatrix[i][j]) {
				case 1: case 2:
					carName = "car1.ovo";
					break;
				case 3: case 4:
					carName = "car2.ovo";
					break;
				case 5:
					carName = "car0.ovo";
					break;
				}

				std::string path = ".." + getSeparator() + "scene" + getSeparator() + carName;
				Node car = Engine::loadNode(path);
				glm::mat4 m = glm::mat4(1.0f);
				m = glm::translate(m, glm::vec3(-8.0f + (2.265f * (PLAYGROUND_SIZE + 1 - i)), 1.0f, -7.25f + (2.25f * j)));

				/*

				Playing field where:

				0 -> indicates empty space
				1 -> indicates car presence at 0 degrees with lenght 2
				2 -> indicates car presence at 90 degrees with lenght 2
				3 -> indicates car presence at 0 degrees with lenght 3
				4 -> indicates car presence at 90 degrees with lenght 3
				5 -> indicates the target car
				6 -> indicates the wall
				7 -> indicates the exit

				*/

				switch (initialMatrix[i][j])
				{
				case 1: case 5:
					m = glm::rotate(m, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					m = glm::translate(m, glm::vec3(-0.6f, 0.0f, -0.6f));
					car.getChildAt(0)->setScale(1.1f);
					// Add car to positioning matrix
					positioningMatrix[i][j] = true;
					positioningMatrix[i + 1][j] = true;
					break;
				case 2:
					m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					car.getChildAt(0)->setScale(1.1f);
					// Add car to positioning matrix
					positioningMatrix[i][j] = true;
					positioningMatrix[i][j + 1] = true;
					break;
				case 3:
					m = glm::rotate(m, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					m = glm::translate(m, glm::vec3(-1.2f, 0.0f, -0.6f));
					car.getChildAt(0)->setScale(1.0f);
					// Add car to positioning matrix
					positioningMatrix[i][j] = true;
					positioningMatrix[i + 1][j] = true;
					positioningMatrix[i + 2][j] = true;
					break;
				case 4:
					m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					m = glm::translate(m, glm::vec3(-0.4f, 0.0f, 0.1f));
					car.getChildAt(0)->setScale(1.0f);
					// Add car to positioning matrix
					positioningMatrix[i][j] = true;
					positioningMatrix[i][j + 1] = true;
					positioningMatrix[i][j + 2] = true;
					break;
				default:
					break;
				}

				car.getChildAt(0)->setTransform(m);
				Engine::addNode(car);

				// Create pair
				matrix[i][j] = std::make_pair(initialMatrix[i][j], car.getChildAt(0)->getId());
			}
			else {
				// Cell does not contain car
				matrix[i][j] = std::make_pair(initialMatrix[i][j], 0);
			}
		}
	}
}

void init(int argc, char* argv[]) {
	Engine::setZBufferUsage(true);
	Engine::init(argc, argv, "RushHour Game", width, height);

	fillInitialPositioningMatrix();
	loadCameras();
	loadScene(".." + getSeparator() + "scene" + getSeparator() + "scene.ovo");
	loadCars();

	Engine::setKeyboardCallback(keyboardCallback);
	Engine::setWindowResizeHandler(handleWindowResize);
	Engine::setSpecialCallback(specialCallback);
	Engine::setObjectPickedCallback(getPickedObject);
	Engine::setBackgroundColor(0.01f, 0.01f, 0.3f, 1.0f);
	Engine::executeTests();
	Engine::start();
	Engine::startTimer(updateFPS, 1000);
	Engine::startTimer(blinkLight, 500);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[])
{
	init(argc, argv);

	std::string difficultyStr = (gameDifficulty == 1) ? "Easy" : (gameDifficulty == 2) ? "Medium" : (gameDifficulty == 3) ? "Hard" : "Undefined";

	Engine::startTimer(rotateCamera, 10);
	while (Engine::isRunning()) {
		Engine::update();

		Engine::writeOnScreen("Commands:", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 15.0f), 6);
		Engine::writeOnScreen("[1]: Top view", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(20.0f, height - 30.0f), 6);
		Engine::writeOnScreen("[2]: Side view", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(20.0f, height - 45.0f), 6);
		Engine::writeOnScreen("[3]: Dynamic view", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(20.0f, height - 60.0f), 6);
		Engine::writeOnScreen("[Arrows]: Move selected car", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(20.0f, height - 75.0f), 6);

		Engine::writeOnScreen("FPS: " + std::to_string(fps), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 105.0f), 6);
		Engine::writeOnScreen("Game difficulty: " + difficultyStr, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 120.0f), 6);
		Engine::writeOnScreen("Number of moves: " + std::to_string(numberOfMoves), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 135.0f), 6);

		if (gameFinished) {
			// Display string on screen
			Engine::writeOnScreen("You won!", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(width - width / 2 -50.f, height - height / 2 + 15.0f), 7);
			Engine::writeOnScreen("To start a new game press [n]", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(width - width / 2 - 130.f, height - height / 2 - 15.0f), 7);
			Engine::refreshAndSwapBuffers();
		}

		Engine::refreshAndSwapBuffers();
		fc++;
	}

	// Free engine
	Engine::free();
	return 0;
}
