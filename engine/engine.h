/**
 * @file	engine.h
 * @brief	A simple graphical engine library
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */
#pragma once
#include <vector>



 /////////////
 // VERSION //
 /////////////

// Generic info:
#define LIB_NAME      "Engine Library v0.1a"		///< Library credits
#define LIB_VERSION   10                            ///< Library version (divide by 10)

#ifdef _WINDOWS
// Export API:
// Specifies i/o linkage (VC++ spec):
#ifdef ENGINE_EXPORTS
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif
#else // Under Linux
#define LIB_API  // Dummy declaration
#endif

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
	static void setKeyboardCallback(void (*func)(unsigned char, int, int));
	static void setSpecialCallback(void (*func)(int, int, int));
	static void setBackgroundColor(float, float, float, float);
	static bool isRunning();
	static void clearWindow();
	static void swapBuffers();
	static void start();
	static void reshapeCallback(int, int);
	static void postWindowRedisplay();
	static void update();
	

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
};
