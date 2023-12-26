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

// C/C++:
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <mesh.h>


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

int matrix[8][8] = {
	{ 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 },
	{ 6 , 1 , 0 , 0 , 0 , 1 , 0 , 6 },
	{ 6 , 0 , 0 , 1 , 0 , 1 , 0 , 6 },
	{ 6 , 0 , 1 , 0 , 0 , 0 , 0 , 6 },
	{ 6 , 0 , 0 , 0 , 1 , 0 , 0 , 6 },
	{ 6 , 1 , 0 , 1 , 0 , 1 , 1 , 6 },
	{ 6 , 0 , 0 , 0 , 0 , 0 , 0 , 6 },
	{ 6 , 6 , 5 , 6 , 6 , 6 , 6 , 6 }
};




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
		Engine::setActiveCamera(0);
	else if (key == '2')
		Engine::setActiveCamera(1);
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
}
void loadCars()
{
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7 ; j++) {
			if (matrix[i][j] == 0 || matrix[i][j] == 5 || matrix[i][j] == 6) continue;
			std::string path = "..\\scene\\car.ovo";
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



void init() {
	loadCameras();
	loadScene("..\\scene\\scene.ovo");
	loadCars();
}



/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char* argv[])
{
	// Setup initial frame properties
	Engine::setZBufferUsage(true);	// Must be executed before Engine::init
	Engine::init(argc, argv, "RushHour Game", 640, 480);
	init();
	// Setup callbacks 
	Engine::setKeyboardCallback(keyboardCallback);
	Engine::setSpecialCallback(specialCallback);
	// Set background color
	Engine::setBackgroundColor(0.01f, 0.01f, 0.3f, 1.0f);

	//Execute tests
	Engine::executeTests();

	// Start engine
	Engine::start();

	// Execute application logic
	while (Engine::isRunning()) {
		// Render stuff…
		// Engine::renderTriangle();
		// Update engine 
		
		Engine::update();
	}

	// Free engine
	Engine::free();
	return 0;
}
