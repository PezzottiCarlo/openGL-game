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

   // Library main include:
   #include "engine.h"

   // C/C++:
   #include <iostream>



////////////
// STATIC //
////////////

   // Reserved pointer:
   bool Engine::initFlag = false;



//////////////
// DLL MAIN //
//////////////

#ifdef _WINDOWS
#include <Windows.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
 * @param instDLL handle
 * @param reason reason
 * @param _reserved reserved
 * @return true on success, false on failure
 */
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
	// Check use:
   switch (reason)
   {
         ///////////////////////////
         case DLL_PROCESS_ATTACH: //
            break;


         ///////////////////////////
         case DLL_PROCESS_DETACH: //
            break;
   }

   // Done:
   return true;
}
#endif



//////////////////////////
// BODY OF CLASS Engine //
//////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Initialization method. Call this before any other Eureka function.
 * @return true on success, false on error
 */
bool LIB_API Engine::init()
{
   // Prevent double init:
   if (initFlag)
   {
      std::cout << "ERROR: class already initialized" << std::endl;
      return false;
   }

	// Done:
   initFlag = true;
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Deinitialization method.
 * @return true on success, false on error
 */
bool LIB_API Engine::free()
{
   // Really necessary?
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }

	// Done:
   initFlag = false;
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Simple, useless method.
 * @return true on success, false on error
 */
bool LIB_API Engine::doNothing()
{
   // Probably excessive checking:
   if (!initFlag)
   {
      std::cout << "ERROR: class not initialized" << std::endl;
      return false;
   }

   std::cout << "If you read this, your library is working as expected" << std::endl;

	// Done:
	return true;
}




