#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "./sol.hpp"
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"
#include "./LogWindow.h"
#include "./LogData.h"
#include "./LevelSetup.h"

class AssetManager;
class LogWindow;

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
    static AssetManager* assetManager;
    static SDL_Event event;
    static SDL_Rect camera;
    static LogWindow* logWindow;
    SDL_Cursor* cursor;

    Game();
    ~Game();

    int ticksLastFrame = 0;

    bool IsRunning() const;

    // SETUP EVENTS
    void Initialize(int width, int height, bool devConsole);
    void loadMainWindow();
    void LoadLogWindow(bool devConsole);
    void LoadCursor();


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
    static void DamagePlayer(Entity* thatEntity);
    static void ProcessNextLevel();
    static void ProcessGameOver();
    
};

#endif
