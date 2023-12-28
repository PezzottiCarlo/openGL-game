/**
 * @file	engine.h
 * @brief	A simple graphical engine library
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */
#pragma once
#include <vector>
#include <string>

#include "lib.h"
#include "list.h"
#include "ovoreader.h"
#include "camera.h"


/////////////
// CLASSES //
/////////////

/**
 * @brief Simple static class example.
 */
class LIB_API Engine{

//////////
public: //
//////////

	// Init/free:
	static bool init(int, char**, const char*, int, int);
	static bool free();

	// Other functions
	static void setZBufferUsage(bool);
	static void setBackgroundColor(float, float, float, float);
	static void setWindowResizeHandler(void (*func)(int, int));

	static bool isRunning();
	static void clearWindow();
	static void swapBuffers();
	static void start();
	static void reshapeCallback(int, int);
	static void postWindowRedisplay();
	static void update();
	static void executeTests();
	static void refreshAndSwapBuffers();

	//Keyboard handling
	static void setKeyboardCallback(void (*func)(unsigned char, int, int));
	static void setSpecialCallback(void (*func)(int, int, int));

	//Mouse handling
	static void setObjectPickedCallback(void (*func)(Node*,bool));
	

	//CLIENT FUNCTIONS

	//Scene
	static void loadScene(std::string);

	//Cameras
	static void initCameras(int);
	static void loadCamera(float, float, float, float, float, float, int);
	static void setActiveCamera(int);

	//node
	static Node loadNode(std::string);
	static void addNode(Node);

	//Write on screen
	static void writeOnScreen(std::string,glm::vec3,glm::vec2,float);

	//Timer
	static void startTimer(void (*func)(int),int);

///////////
private: //
///////////

	// Const/dest (as private to prevent instantiation):
	Engine() {}
	~Engine() {}

	// Functions
	static void displayCallback();
	static void execZBufferSetup();

	// Internal vars:
	static bool initFlag;
	static bool useZBuffer;
	static bool mainLoopRunning;
	static int windowId;
	static float bgR;
	static float bgG;
	static float bgB;
	static float bgA;

	static OvoReader reader;
	static List list;

	// cameras
	static int activeCamera;
	static std::vector<Camera*> cameras;

};
