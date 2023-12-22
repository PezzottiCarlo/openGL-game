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
// C/C++:
#include <iostream>


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
	std::cout << key << " has been pressed." << std::endl;
	// TBD
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
	Engine::loadCamera(0, 0, -5.0f, 0, 75.0f, 0, 0);
	Engine::loadCamera(0, -5.0f, 0, 0, 0, 90.0f, 0);
}

void init(){
	loadCameras();
	loadScene("..\\scene\\scene.ovo");
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
	while (Engine::isRunning()){
		// Render stuff…
		// Engine::renderTriangle();
		// Update engine 
		Engine::update();
	}

	// Free engine
	Engine::free();
	return 0;
}
