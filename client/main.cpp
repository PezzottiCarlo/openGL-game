/**
 * @brief   A simple graphical engine library
 *
 * @author  Jari N�ser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

 //////////////
 // #INCLUDE //
 //////////////

#include "main.h"
// Library header:

#include "engine.h"
#include "node.h"
#include <mesh.h>

// C/C++:
#include <iostream>
#include <glm/gtx/string_cast.hpp>

// Constants:
#define PLAYGROUND_SIZE 6


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

int matrix[PLAYGROUND_SIZE + 2][PLAYGROUND_SIZE + 2] = {
	{ 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 },
	{ 6 , 2 , 0 , 0 , 3 , 1 , 0 , 6 },
	{ 6 , 0 , 0 , 5 , 0 , 0 , 0 , 6 },
	{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
	{ 6 , 3 , 0 , 0 , 4 , 0 , 0 , 6 },
	{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
	{ 6 , 0 , 0 , 0 , 0 , 2 , 0 , 6 },
	{ 6 , 6 , 7 , 6 , 6 , 6 , 6 , 6 }
};

int width = 640;
int height = 480;
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

std::string getSeparator(){
	#ifdef _WIN32
	return "\\";
	#else
	return "/";
	#endif
}

///////////////
// CALLBACKS //
///////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback gets invoked when a special character on the keyboard gets pressed.
 * @param key pressed keyboard key as integer
 * @param x mouse x position relative to the window when the key gets pressed
 * @param y mouse y position relative to the window when the key gets pressed
 */
void specialCallback(int key, int x, int y) {
	std::cout << key << " has been pressed." << std::endl;
	// TBD
	Engine::postWindowRedisplay();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback gets invoked when a regular character on the keyboard gets pressed.
 * @param key pressed keyboard character
 * @param x mouse x position relative to the window when the key gets pressed
 * @param y mouse y position relative to the window when the key gets pressed
 */
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
	}
	Engine::postWindowRedisplay();
}

//////////
// MAIN //
//////////

void loadScene(std::string pathName) {
	Engine::loadScene(pathName);
}

void loadCameras() {

	Camera* c1 = new Camera("camera1");
	c1->setUserTransform(0, 15.0f, 0, -90.0f, 0, -90.0f);
	Camera* c2 = new Camera("camera2");
	c2->setUserTransform(-20.0f, 5.0f, 5.0f, 0, -75.0f, 0);
	Camera* c3 = new Camera("camera3");
	c3->setUserTransform(0.0f, 5.0f, 10.0f, 0, -75.0f, 0);

	Engine::addCamera(c1);
	Engine::addCamera(c2);
	Engine::addCamera(c3);

	cameras[0] = c1;
	cameras[1] = c2;
	cameras[2] = c3;

	Engine::setActiveCamera(0);
}


void rotateCamera() {
	static bool rotationSense = false;
	static float angle = 0.0f;
	glm::mat4 currentTransform = cameras[2]->getTransform();
	float rotation = 0.2f * (fps / 60.0f) * (rotationSense) ? -1.0f : 1.0f;
	currentTransform = glm::rotate(currentTransform, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	cameras[2]->setTransform(currentTransform);

	if (angle == 120.0f) 
		rotationSense = true;
	else if (angle == 0.0f)
		rotationSense = false;
	angle += rotation;
}

void loadCars(){
	for (int i = 1; i < PLAYGROUND_SIZE + 1; i++) {
		for (int j = 1; j < PLAYGROUND_SIZE + 1; j++) {

			if (matrix[i][j] == 0 || matrix[i][j] == PLAYGROUND_SIZE + 1 || matrix[i][j] == PLAYGROUND_SIZE) continue;

			std::string carName;

			switch (matrix[i][j]) {
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
			m = glm::translate(m, glm::vec3(-8.0f + (2.265f * (PLAYGROUND_SIZE + 1 - i)),1.0f, -7.25f + (2.25f * j)));


			/*	1->indicates car presence at 0 degrees with lenght 2		|
				2->indicates car presence at 90 degrees with lenght 2		-
				3->indicates car presence at 0 degrees with lenght 3		|
				4->indicates car presence at 90 degrees with lenght 3		-
				5->indicates the target car	at 0 degrees					|
				*/

			switch (matrix[i][j])
			{
				case 1: case 5:
					m = glm::rotate(m, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					m = glm::translate(m, glm::vec3(-0.6f, 0.0f, -0.6f));
					car.getChildAt(0)->setScale(1.1f);
					break;
				case 2:
					m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					car.getChildAt(0)->setScale(1.1f);
					break;
				case 3:
					m = glm::rotate(m, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					m = glm::translate(m, glm::vec3(3.3f, 0.0f, 0.6f));
					car.getChildAt(0)->setScale(1.0f);
					break;
				case 4:
					m = glm::rotate(m, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					m = glm::translate(m, glm::vec3(0.35f, 0.0f, -0.1f));
					car.getChildAt(0)->setScale(1.0f);
					break;
				default:
					break;
			}

			car.getChildAt(0)->setTransform(m);
			Engine::addNode(car);
		}
	}
}

void makeObjectBlink(Node* obj) {

	if (!(obj->getName().substr(0, 3) == "Car" || obj->getName().substr(0, 9) == "Limousine" || obj->getName().substr(0, 6) == "Police")) return;

	//scale step base on fps for a smooth animation
	step = 0.1f * (fps / 60.0f);

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

void getPickedObject(Node* n,bool mousePressed) {
	if (n != nullptr && mousePressed) {
		if (pickedObject != nullptr) {
			((Mesh*)pickedObject)->getMaterial()->setEmission(lastObjectEmission);
		}
		lastObjectEmission = ((Mesh*)n)->getMaterial()->getEmission();
		pickedObject = n;
	}
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

void init(int argc, char* argv[]) {
	Engine::setZBufferUsage(true);
	Engine::init(argc, argv, "RushHour Game", width, height);

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
}

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[])
{
	init(argc,argv);

	while (Engine::isRunning()) {
		Engine::update();
		if (pickedObject != nullptr) {
			makeObjectBlink(pickedObject);
		}

		Engine::writeOnScreen("Press [1] -> Top view", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height-15.0f), 10.0f);
		Engine::writeOnScreen("Press [2] -> Side view", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 30.0f), 10.0f);
		Engine::writeOnScreen("Press [3] -> Dynamic view", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 45.0f), 10.0f);
		Engine::writeOnScreen("FPS: " + std::to_string(fps), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 60.0f), 10.0f);
		Engine::refreshAndSwapBuffers();

		rotateCamera();
		fc++;
	}

	// Free engine
	Engine::free();
	return 0;
}
