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
#include "vertex.h"

// C/C++:
#include <iostream>

// GLM: 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>


// FreeGLUT:   
#include <GL/freeglut.h>


////////////
// STATIC //
////////////

bool Engine::initFlag = false;
bool Engine::useZBuffer = false;
bool Engine::mainLoopRunning = false;
float Engine::bgR = 0.0f;
float Engine::bgG = 0.0f;
float Engine::bgB = 0.0f;
float Engine::bgA = 0.0f;
int Engine::windowId = 0;

int fps = 0;
int fpsCounter = 0;

glm::mat4 perspective;
glm::mat4 ortho;

//////////////
// DLL MAIN //
//////////////

#ifdef _WINDOWS
#include <Windows.h>
#include "mesh.h"
#include "light.h"
#include "ovoReader.h"
#include "node.h"
#include "list.h"
#include <FreeImage.h>
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
 * @param argc argument count 
 * @param argv array containing arguments
 * @param title FreeGlut window title
 * @param width window width
 * @param height window height
 * @return true on success, false on error
 */
 /////////////////
 // FOR TESTING //
 /////////////////

List list;

bool LIB_API Engine::init(int argc, char* argv[], const char* title, int width, int height){


    if (!initFlag) {
        FreeImage_Initialise();
        
        // Init context:
        if (useZBuffer) {
            glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        } else {
            glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
        }
        
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(width, height);

        // FreeGLUT can parse command-line params, in case:
        glutInit(&argc, argv);

        // Set some optional flags:
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        // Enable Z buffer if it's required
        if (useZBuffer) execZBufferSetup();
        
        // Create window
        windowId = glutCreateWindow(title);


        OvoReader reader = OvoReader();
        Node* root = reader.readFile("..\\scene\\examples\\simple3dScene.ovo");
        list.addEntry(root);


        // Set callback functions
        glutDisplayFunc(displayCallback);
        glutReshapeFunc(reshapeCallback);
        //Enable Z-Buffer
        glEnable(GL_DEPTH_TEST);
        //Enable face culling
        glEnable(GL_CULL_FACE);
        //Enable smooth shading
        glShadeModel(GL_SMOOTH);
        //enable texture
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_NORMALIZE);

        //Init FreeImage
        //FreeImage_Initialise();

        // Start FPS timer 
        glutTimerFunc(1000, updateFPS, 0);
    }
    return initFlag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Deinitialization method.
 * @return true on success, false on error
 */
bool LIB_API Engine::free()
{
    // Close open connections or free allocated memory
    mainLoopRunning = false;
    
    // Release bitmap and FreeImage:
    FreeImage_DeInitialise();

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time the window gets resized (and once also when created).
 * @param width new window width
 * @param height new window height
 */
void LIB_API Engine::reshapeCallback(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    //create a perspective matrix with a 45 degree field of view and a near and far plane
    perspective = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 1.0f, 10000.0f);
    ortho = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 1.0f, -1.0f);
    glLoadMatrixf(glm::value_ptr(perspective));
    glMatrixMode(GL_MODELVIEW);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This is the main rendering routine automatically invoked by FreeGLUT.
 */
float angle = 0.0f;
void LIB_API Engine::displayCallback()
{
    Engine::clearWindow();

    //////
    // 3D:

    // Set perpsective matrix:
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(perspective));
    glMatrixMode(GL_MODELVIEW);

    // Enable Z buffer if it's required
    if (useZBuffer) execZBufferSetup();

    if (angle > 360.0f) angle -= 360.0f;
    angle += 0.01f; // Adjust the rotation speed as needed
    

    // create a matrix called translation for the camera
    glm::mat4 translation = glm::mat4(1.0f);
    //make the camera go back 5 units
    translation = glm::translate(translation, glm::vec3(0.0f, -50.0f, -150.0f));
    //make the object at the center of the world
    
    // Compute model matrix:
    glm::mat4 f = translation * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    glLoadMatrixf(glm::value_ptr(f));

    list.render(f, nullptr);

    // 2D
    // Set orthographic projection:
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(ortho));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::mat4(10.0f)));

    // Write 2D text
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    char text[64];
    sprintf_s(text, "Current FPS: %d", fps);
    //strcpy_s(text, "Current FPS: " + fps);

    glRasterPos2f(1.0f, 8.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text);


    // Re-enable lighting
    glEnable(GL_LIGHTING);

    // Increment fps
    fpsCounter++;

    // Force rendering refresh
    glutPostWindowRedisplay(windowId);
    //angle += .0005f;
    // Swap this context's buffer:
    glutSwapBuffers();
}

void LIB_API loadScene(std::string scene) {
    
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback connects the given function handler with the glutKeyboardFunc function.
 * @param func function handler
 * @param key pressed key character
 * @param x mouse x position relative to the window when the key gets pressed
 * @param y mouse y position relative to the window when the key gets pressed
 */
void LIB_API Engine::setKeyboardCallback(void (*func)(unsigned char key, int x, int y)) {
    glutKeyboardFunc(func);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback connects the given function handler with the glutSpecialFunc function.
 * @param func function handler
 * @param key pressed key integer
 * @param x mouse x position relative to the window when the key gets pressed
 * @param y mouse y position relative to the window when the key gets pressed
 */
void LIB_API Engine::setSpecialCallback(void (*func)(int key, int x, int y)) {
    glutSpecialFunc(func);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function sets the frames background color. 
 * @param r red rgba color component
 * @param g green rgba color component
 * @param b blue rgba color component
 * @param a alpha rgba color component
 */
void LIB_API Engine::setBackgroundColor(float r, float g, float b, float a) {     
    bgR = r;
    bgG = g;
    bgB = b;
    bgA = a;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function defines if the engine is still running.
 * @return true on running status, false on stop status
 */
bool LIB_API Engine::isRunning() {
    return mainLoopRunning;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function clears the contents off the frame leaving the background color.
 */
void LIB_API Engine::clearWindow() {
    // RGBA components
    glClearColor(bgR, bgG, bgB, bgA); 
    if (useZBuffer) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function swaps the buffers to display.
 */
void LIB_API Engine::swapBuffers() {
    glutSwapBuffers();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function defines if the Z-buffer will be used.
 * @param status boolean that defines useZBuffer's value
 */
void LIB_API Engine::setZBufferUsage(bool status) {
    useZBuffer = status;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function starts the engine activating the glutMainLoop.
 */
void LIB_API Engine::start() {
    mainLoopRunning = true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function forces a rendering refresh.
 */
void LIB_API Engine::postWindowRedisplay() {
    // Force rendering refresh
    glutPostWindowRedisplay(windowId);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function sets up the z-buffer.
 */
void LIB_API Engine::execZBufferSetup(){
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This function calls the glutMainLoopEvent (instead of using glutMainLoop that blocks the whole program).
 */
void LIB_API Engine::update() {
    glutMainLoopEvent();
}

void Engine::updateFPS(int value) {
    fps = fpsCounter;
    fpsCounter = 0;
    glutTimerFunc(1000, updateFPS, 0);
}