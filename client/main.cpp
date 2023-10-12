/**
 * @file    engine.cpp
 * @brief   A simple graphical engine library
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

 //////////////
 // #INCLUDE //
 //////////////

	// Library header:
#include "engine.h"

// C/C++:
#include <iostream>

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
	// Credits:
	std::cout << "Client application example" << std::endl;
	std::cout << std::endl;

	// Init and use the lib:
	Engine::init();
	Engine::doNothing();
	Engine::free();
	Engine::testGLM();

	// Done:
	std::cout << "\n[application terminated]" << std::endl;
	return 0;
}
