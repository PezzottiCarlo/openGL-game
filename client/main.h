/**
 * @file	main.h
 * @brief	Header file for the main class
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

#include <string>
#include <node.h>
#include <glm/glm.hpp>

 /**
  * @brief   Get the separator string.
  * @return  The separator string.
  */
std::string getSeparator();

/**
 * @brief   Fill the initial positioning matrix.
 */
void fillInitialPositioningMatrix();

/**
 * @brief   Get car data based on the provided ID.
 * @param   id The ID of the car.
 * @return  A vector containing car data.
 */
std::vector<int> getCarDataFromId(unsigned int id);

/**
 * @brief   Callback function for special keys.
 * @param   key The pressed key.
 * @param   x The x-coordinate of the mouse.
 * @param   y The y-coordinate of the mouse.
 */
void specialCallback(int key, int x, int y);

/**
 * @brief   Perform actions based on picked object and mouse state.
 * @param   n The picked node.
 * @param   mousePressed The state of the mouse button.
 */
void getPickedObject(Node* n, bool mousePressed);

/**
 * @brief   Callback function for regular keyboard keys.
 * @param   key The pressed key.
 * @param   x The x-coordinate of the mouse.
 * @param   y The y-coordinate of the mouse.
 */
void keyboardCallback(unsigned char key, int x, int y);

/**
 * @brief   Load game difficulty data.
 * @return  A 2D vector containing game difficulty information.
 */
std::vector<std::vector<int>> loadGameDifficulty();

/**
 * @brief   Load a scene from the specified path.
 * @param   pathName The path to the scene.
 */
void loadScene(std::string pathName);

/**
 * @brief   Load camera configurations.
 */
void loadCameras();

/**
 * @brief   Rotate the camera based on the given value.
 * @param   value The rotation value.
 */
void rotateCamera(int value);

/**
 * @brief   Move the winning car based on the given value.
 * @param   value The movement value.
 */
void moveWinningCar(int value);

/**
 * @brief   Load car configurations.
 */
void loadCars();

/**
 * @brief   Make an object blink.
 * @param   obj The object to blink.
 */
void makeObjectBlink(Node* obj);

/**
 * @brief   Update the blinking effect.
 * @param   value The update value.
 */
void updateBlinking(int value);

/**
 * @brief   Handle window resize events.
 * @param   w The new width of the window.
 * @param   h The new height of the window.
 */
void handleWindowResize(int, int);

/**
 * @brief   Update the frames per second (FPS) display.
 * @param   value The update value.
 */
void updateFPS(int value);

/**
 * @brief   Blink a light source.
 * @param   value The blink effect value.
 */
void blinkLight(int value);

/**
 * @brief   Initialize the application.
 * @param   argc The number of command line arguments.
 * @param   argv The array of command line arguments.
 */
void init(int argc, char* argv[]);
