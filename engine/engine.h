/**
 * @file		engine.h
 * @brief	A simple graphical engine library
 *
 * @author	Jari N�ser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */
#pragma once



 /////////////
 // VERSION //
 /////////////

	// Generic info:
#define LIB_NAME      "Engine Library v0.1a"  ///< Library credits
#define LIB_VERSION   10                              ///< Library version (divide by 10)

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
class LIB_API Engine
{
	//////////
public: //
	//////////	   

	   // Init/free:
	static bool init();
	static bool free();

	// Event manager:
	static bool doNothing();


	///////////
private:	//
	///////////	   

		// Const/dest (as private to prevent instanciation):
	Engine() {}
	~Engine() {}

	// Internal vars:
	static bool initFlag;
};