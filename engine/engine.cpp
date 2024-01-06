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
#include <stdio.h>
#include <functional>

// GLM: 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// FreeGLUT:   
#include <GL/freeglut.h>

// FreeImage:
#include <FreeImage.h>

// Own header files:
#include "mesh.h"
#include "light.h"
#include "node.h"
#include "engine-tests-runner.h"


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
std::vector<Camera*> Engine::cameras = std::vector<Camera*>();
int Engine::activeCamera = 0;


OvoReader Engine::reader = OvoReader();
List Engine::list;

glm::mat4 perspective;
glm::mat4 ortho;

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



bool LIB_API Engine::init(int argc, char* argv[], const char* title, int width, int height) {


    if (!initFlag) {
        FreeImage_Initialise();

        // Init context:
        if (useZBuffer) {
            glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        }
        else {
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


        // Set callback functions
        glutDisplayFunc(displayCallback);
        //Enable Z-Buffer
        glEnable(GL_DEPTH_TEST);
        //Enable face culling
        glEnable(GL_CULL_FACE);
        //Enable smooth shading
        glShadeModel(GL_SMOOTH);
        //enable texture
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_NORMALIZE);
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
    perspective = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 1.0f, 1000.0f);
    ortho = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 1.0f, -1.0f);
    glLoadMatrixf(glm::value_ptr(perspective));
    glMatrixMode(GL_MODELVIEW);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This is the main rendering routine automatically invoked by FreeGLUT.
 */
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

    //disable texturing
    glLoadMatrixf(glm::value_ptr(cameras.at(activeCamera)->getInverseCameraMat()));
    list.render(cameras.at(activeCamera)->getInverseCameraMat(), nullptr);

    // Force rendering refresh

    // Swap this context's buffer:

}

void LIB_API Engine::loadScene(std::string pathName)
{
    Node* root = reader.readFile(pathName.c_str());
    list.addEntry(root);
}

void LIB_API  Engine::addCamera(Camera* camera) {
    cameras.push_back(camera);
}

void LIB_API Engine::setActiveCamera(int num)
{
    activeCamera = num;
}

Node LIB_API Engine::loadNode(std::string pathName)
{
    Node* _car = reader.readFile(pathName.c_str());
    Node car = *_car;
    return car;
}

void LIB_API Engine::addNode(Node node)
{
    Node* _node = new Node(node);
    list.addEntry(_node);
}

void LIB_API Engine::writeOnScreen(std::string text, glm::vec3 color, glm::vec2 coord, int textType)
{
    /*
        Text types:

        1:  GLUT_BITMAP_8_BY_13
        2:  GLUT_BITMAP_9_BY_15
        3:  GLUT_BITMAP_TIMES_ROMAN_10
        4:  GLUT_BITMAP_TIMES_ROMAN_24
        5:  GLUT_BITMAP_HELVETICA_10
        6:  GLUT_BITMAP_HELVETICA_12
        7:  GLUT_BITMAP_HELVETICA_18
    
    */

    // 2D
    // Set orthographic projection:
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(ortho));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));

    // Write 2D text
    glDisable(GL_LIGHTING);
    glColor3f(color.x, color.y, color.z);
    glRasterPos2f(coord.x, coord.y);

    switch (textType) {
        case 1:
            glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text.c_str());
            break;
        case 2:
            glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char*)text.c_str());
            break;
        case 3:
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (unsigned char*)text.c_str());
            break;
        case 4:
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text.c_str());
            break;
        case 5:
            glutBitmapString(GLUT_BITMAP_HELVETICA_10, (unsigned char*)text.c_str());
            break;
        case 6:
            glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)text.c_str());
            break;
        case 7:
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)text.c_str());
            break;
    }

    // Re-enable lighting
    glEnable(GL_LIGHTING);
}

void LIB_API Engine::startTimer(void(*func)(int), int time)
{
    glutTimerFunc(time, func, 0);
}

List LIB_API* Engine::getList()
{
    return &list;
}

bool LIB_API Engine::clearList() {
    list.clear();
    return true;
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

void LIB_API Engine::removeObjectPickedCallback() {
    // Disables the generation of mouse callbacks
    glutMouseFunc(NULL);
}

void LIB_API Engine::setObjectPickedCallback(void (*func)(Node* n, bool mousePressed)) {
    static std::function<void(int, int)> lambdaWrapper = [func](int x, int y) {
        if (x == -1 && y == -1)
            return func(nullptr, false);

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(perspective));
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(cameras.at(activeCamera)->getInverseCameraMat()));

        list.render(cameras.at(activeCamera)->getInverseCameraMat(), (void*)true);

        unsigned char pixel[4];
        glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);

        int id = (pixel[0] << 16) | (pixel[1] << 8) | (pixel[2] << 0);
        Node* n = list.getObjectById(id);
        if (n != nullptr) {
            return func(n, true);
        }
        return func(nullptr, false);
        };

    //call lambdaWrapper when mouse left button is pressed
    glutMouseFunc([](int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            Engine::clearWindow();
            lambdaWrapper(x, y);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
            lambdaWrapper(-1, -1);
        }
    });
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

void Engine::setWindowResizeHandler(void(*func)(int, int))
{
    glutReshapeFunc(func);
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
void LIB_API Engine::execZBufferSetup() {
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

void LIB_API Engine::executeTests() {
    runTests();
}

void LIB_API Engine::refreshAndSwapBuffers()
{
    glutPostWindowRedisplay(windowId);
    glutSwapBuffers();
}