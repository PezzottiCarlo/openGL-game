/**
 * @file	engine.h
 * @brief	A simple graphical engine library
 *
 * This file defines the Engine class, a simple graphical engine library that provides
 * functionality for handling scenes, cameras, nodes, keyboard and mouse input, and more.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once
#include <vector>
#include <string>

#include "lib.h"
#include "list.h"
#include "ovoReader.h"
#include "camera.h"

 /////////////
 // CLASSES //
 /////////////

 /**
  * @brief Simple static class example.
  */
class LIB_API Engine {

    //////////
public: //
    //////////

    // Init/free:
    /**
     * @brief Initialize the graphical engine.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments.
     * @param windowTitle The title of the graphical window.
     * @param windowWidth The width of the graphical window.
     * @param windowHeight The height of the graphical window.
     * @return A boolean indicating the success of the initialization.
     */
    static bool init(int argc, char** argv, const char* windowTitle, int windowWidth, int windowHeight);

    /**
     * @brief Free resources and terminate the graphical engine.
     * @return A boolean indicating the success of freeing resources.
     */
    static bool free();

    // Other functions
    /**
     * @brief Set whether to use Z-buffer for rendering.
     * @param useZBuffer A boolean indicating whether to use Z-buffer.
     */
    static void setZBufferUsage(bool useZBuffer);

    /**
     * @brief Set the background color of the graphical window.
     * @param r Red component of the background color.
     * @param g Green component of the background color.
     * @param b Blue component of the background color.
     * @param a Alpha component of the background color.
     */
    static void setBackgroundColor(float r, float g, float b, float a);

    /**
     * @brief Set the window resize handler function.
     * @param func The function to be called when the window is resized.
     */
    static void setWindowResizeHandler(void (*func)(int, int));

    /**
     * @brief Check if the graphical engine is running.
     * @return A boolean indicating whether the engine is running.
     */
    static bool isRunning();

    /**
     * @brief Clear the graphical window.
     */
    static void clearWindow();

    /**
     * @brief Swap the front and back buffers of the graphical window.
     */
    static void swapBuffers();

    /**
     * @brief Start the main loop of the graphical engine.
     */
    static void start();

    /**
     * @brief Callback function for reshaping the graphical window.
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    static void reshapeCallback(int width, int height);

    /**
     * @brief Force redisplay of the window.
     */
    static void postWindowRedisplay();

    /**
     * @brief Update the graphical engine.
     */
    static void update();

    /**
     * @brief Execute tests for the graphical engine.
     */
    static void executeTests();

    /**
     * @brief Refresh and swap buffers of the graphical window.
     */
    static void refreshAndSwapBuffers();

    // Keyboard handling
    /**
     * @brief Set the keyboard callback function.
     * @param func The function to be called on keyboard input.
     */
    static void setKeyboardCallback(void (*func)(unsigned char, int, int));

    /**
     * @brief Set the special key callback function.
     * @param func The function to be called on special key input.
     */
    static void setSpecialCallback(void (*func)(int, int, int));

    // Mouse handling
    /**
     * @brief Remove the object picked callback function.
     */
    static void removeObjectPickedCallback();

    /**
     * @brief Set the object picked callback function.
     * @param func The function to be called when an object is picked.
     */
    static void setObjectPickedCallback(void (*func)(Node*, bool));

    // CLIENT FUNCTIONS

    // Scene
    /**
     * @brief Load a scene from a file.
     * @param sceneFile The file path of the scene to load.
     */
    static void loadScene(std::string sceneFile);

    // Cameras
    /**
     * @brief Set the active camera.
     * @param index The index of the camera to set as active.
     */
    static void setActiveCamera(int index);

    /**
     * @brief Add a camera to the graphical engine.
     * @param camera The camera to add.
     */
    static void addCamera(Camera* camera);

    // Node
    /**
     * @brief Load a node from a file.
     * @param nodeFile The file path of the node to load.
     * @return The loaded Node.
     */
    static Node loadNode(std::string nodeFile);

    /**
     * @brief Add a Node to the graphical engine.
     * @param node The Node to add.
     */
    static void addNode(Node node);

    // Write on screen
    /**
     * @brief Write text on the screen.
     * @param text The text to write.
     * @param coord The position on the screen to write the text.
     * @param color The color of the text.
     */
    static void writeOnScreen(std::string text, glm::vec3 color, glm::vec2 coord, int textType);

    // Timer
    /**
     * @brief Start a timer.
     * @param func The function to be called when the timer expires.
     * @param duration The duration of the timer in milliseconds.
     */
    static void startTimer(void (*func)(int), int duration);

    // List
    /**
     * @brief Get the List associated with the graphical engine.
     * @return A pointer to the List.
     */
    static List* getList();

    /**
     * @brief Clear the List associated with the graphical engine.
     * @return A boolean indicating the success of clearing the List.
     */
    static bool clearList();

    ///////////
private: //
    ///////////

    // Const/dest (as private to prevent instantiation):
    /**
     * @brief Private default constructor of the Engine class.
     */
    Engine() {}

    /**
     * @brief Private destructor of the Engine class.
     */
    ~Engine() {}

    // Functions
    /**
     * @brief Display callback function for rendering.
     */
    static void displayCallback();

    /**
     * @brief Execute Z-buffer setup.
     */
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

    // Cameras
    static int activeCamera;
    static std::vector<Camera*> cameras;
};
