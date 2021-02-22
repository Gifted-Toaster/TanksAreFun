#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "./sol.hpp"
#include "./Entity/Entity.h"
#include "./Entity/Component/Component.h"
#include "./misc/LogWindow.h"
#include "./misc/LogData.h"
#include "./misc/LevelSetup.h"
#include "./Controller/Keyboard.h"
#include "./Controller/Mouse.h"

class AssetManager;
class LogWindow;
class Player;
class CollisionManager;
class EntityManager;

static bool isRunning;

/*This is our main game object which serves as a basis for many runtime events such as spawn entities or modify the player object and load objects
* 
It stores the following important objects aswell:
- Log and Main window
- Renderer
- Asset and Entity managers ( which stores ingame objects and their images )
- Runtime conditions
- Camera


The main iteration cycle events are the following:
- Process input
- Update ( Transform , Collision , Camera movement , Refresh Log window)
- Render ( Transform and redraw assets on both windows )


It also manages the buttons at the main menu
*/

class Game {
private:  
    SDL_Window* mainWindow;

public:
    static SDL_Renderer* renderer;
    static AssetManager* asset_manager;
    static EntityManager* entity_manager;
    static CollisionManager* collision_manager;
    static SDL_Event event;
    static SDL_Rect camera;
    static LogWindow* log_window;

    static Player* mainPlayer;
    static Mouse* mouse;
    static Keyboard* keyboard;

    static void MoveCamera(Direction dir);

    Game();
    ~Game();

    int ticksLastFrame = 0;

    bool IsRunning() const;

    // SETUP EVENTS
    void Initialize(int width, int height, bool devConsole);
    void MouseCollideWithButton();
    void loadMainWindow();
    void LoadLogWindow(bool devConsole);


    // UPDATE EVENTS
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    void HandleCameraMovement();
    void Collision();
    void PassLogData(float deltaTime);

    static void Select();
    static void StepUp();
    static void StepDown();

    // RUNTIME EVENTS
    static void spawnEntity(std::string type , int posX , int posY , Direction faceOfDirection);
    static void ProcessNextLevel();
    static void ProcessGameOver();
    
};

#endif
