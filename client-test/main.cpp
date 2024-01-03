/**
 * @brief   A simple graphical engine library
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
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
1 -> indicates car presence at 0 degrees
2 -> indicates car presence at 90 degrees
3 -> indicates car presence at 180 degrees
4 -> indicates car presence at 270 degrees
5 -> indicates the exit
6 -> indicates the wall

in the game scene the point matrix[0][0] is [5.645,5.645,0] and the point matrix[7][7] is [-5.645,-5.645,0]
*/

int matrix[PLAYGROUND_SIZE + 2][PLAYGROUND_SIZE + 2] = {
	{ 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 },
	{ 6 , 1 , 0 , 0 , 0 , 1 , 0 , 6 },
	{ 6 , 0 , 0 , 1 , 0 , 1 , 0 , 6 },
	{ 6 , 0 , 1 , 0 , 0 , 0 , 0 , 6 },
	{ 6 , 0 , 0 , 0 , 1 , 0 , 0 , 6 },
	{ 6 , 1 , 0 , 1 , 0 , 1 , 1 , 6 },
	{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
	{ 6 , 6 , 5 , 6 , 6 , 6 , 6 , 6 }
};

int width = 640;
int height = 480;

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
	if (key == '1')
		Engine::setActiveCamera(1);
	else if (key == '2')
		Engine::setActiveCamera(0);
	Engine::postWindowRedisplay();
}

//////////
// MAIN //
//////////

void loadScene(std::string pathName) {
	Engine::loadScene(pathName);
}

void loadCameras() {
	Engine::initCameras(2);
	Engine::loadCamera(-20.0f, 5.0f, 5.0f, 0, -75.0f, 0, 0);
	Engine::loadCamera(0, 15.0f, 0, -90.0f, 0, -90.0f, 1);
	Engine::setActiveCamera(1);
}

void loadCars(){
	for (int i = 1; i < PLAYGROUND_SIZE + 1; i++) {
		for (int j = 1; j < PLAYGROUND_SIZE + 1; j++) {

			if (matrix[i][j] == 0 || matrix[i][j] == PLAYGROUND_SIZE - 1 || matrix[i][j] == PLAYGROUND_SIZE) continue;

			std::string path = ".." + getSeparator() + "scene" + getSeparator() + "car.ovo";
			Node car = Engine::loadNode(path);
			glm::mat4 m = glm::mat4(1.0f);
			m = glm::translate(m, glm::vec3(-8.0f + (2.2f * (7-i)),0.5f, -8.0f + (2.2f * j)));

			switch (matrix[i][j])
			{
				case 1:
					m = glm::rotate(m, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					break;
				case 2:
					m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					break;
				case 3:
					m = glm::rotate(m, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					break;
				case 4:
					m = glm::rotate(m, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
					break;
				default:
					break;
			}

			car.getChildAt(0)->setTransform(m);
			car.getChildAt(0)->setScale(2.2f);
			Engine::addNode(car);
		}
	}
}

void makeObjectBlink(Node* obj) {
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
	if (!mousePressed && pickedObject != nullptr) {
		((Mesh*)pickedObject)->getMaterial()->setEmission(lastObjectEmission);
		pickedObject = nullptr;
		blinkStep = 0.0f;
		blink = false;
		return;
	}
	else {
		if (n != nullptr) {
			std::cout << "Object picked: " << n->getName() << " with id: " << n->getId() << std::endl;
			lastObjectEmission = ((Mesh*)n)->getMaterial()->getEmission();
			pickedObject = n;
		}
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

		Engine::writeOnScreen("Press [1] or [2] to change perspective", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height-15.0f), 10.0f);
		Engine::writeOnScreen("FPS: " + std::to_string(fps), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(10.0f, height - 30.0f), 10.0f);
		Engine::refreshAndSwapBuffers();
		fc++;
	}

	// Free engine
	Engine::free();
	return 0;
}
