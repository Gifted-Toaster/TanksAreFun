#pragma once

#include <iostream>
#include <fstream>
#include "Constans.h"
#include "Game.h"
#include "./Preset.h"
#include "./Map.h";
#include "./glm/glm.hpp"
#include "./AssetManager.h"
#include "./TransformComponent.h"
#include "./HealthComponent.h"

EntityManager manager;
Map* map;
Entity* mainPlayer = NULL;
Levels currentLevel;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0 ,0 ,WINDOW_WIDTH ,WINDOW_HEIGHT }; // Follows the player

// Log Window
LogWindow* Game::logWindow;

Game::Game() { isRunning = false; }
Game::~Game() {}

// Returning the games current state
bool Game::IsRunning() const {
    return isRunning;
}
// Closing SDL window when the game is over
void Game::Destroy() {
    // Closing logwindow only if it was opened
    if (logWindow) {
        logWindow->Destroy();
    }   
    // Destruct the renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

void Game::loadMainWindow()
{
    mainWindow = SDL_CreateWindow(
        "Main Window",
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if (!mainWindow) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(mainWindow, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
}

void Game::LoadLogWindow(bool devConsole)
{
    if (devConsole) {
        logWindow = new LogWindow(CONSOLE_WIDTH, CONSOLE_HEIGHT);
        std::cout << "Console working?" << std::endl << std::endl;
    }
    else {
        logWindow = NULL;
    }

}

void Game::LoadCursor()
{
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_SetCursor(cursor);
}

// Initilaize our SDL window and loading our first level
void Game::Initialize(int width, int height , bool devConsole) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
#pragma warning(suppress : 4996) freopen("CON", "w", stdout);
#pragma warning(suppress : 4996) freopen("CON", "w", stderr);
    
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL TTF" << std::endl;
        return;
    }
    loadMainWindow();

    LoadLogWindow(devConsole);

    LoadCursor();

    LevelSetup::LoadLevel(MAIN_MENU, &manager, assetManager, map, &mainPlayer);  

    isRunning = true;
    return;
}

// 1) First game loop method
// Handle user input
void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

// 2) Second game loop method
// Update our assets
void Game::Update() {
    // Wait until 16ms has ellapsed since the last frame 
    int timeToTick = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if (timeToTick > 0 && timeToTick <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToTick);
    }

    // Delta time is the difference in ticks from last frame converted to secomds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
   
    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.5f) ? 0.5f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    // runs and calls its every type of entities update method
    // which calles every entities every component update 
    manager.Update(deltaTime);
 
    if (logWindow != NULL) {
        PassLogData(deltaTime);
    }

    // handling the camera movement based on a logic
    HandleCameraMovement();

    // check collisions
    Collision();
    // after everything delete the inactive entities
    //manager.DestroyInactiveEntities();
}

void Game::PassLogData(float deltaTime) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    //x += camera.x;
    //y += camera.y;
    logWindow->UpdateLog("FPS" , "FPS: " , deltaTime*1000);
    logWindow->UpdateLog("log_1" , "Active entities: ", manager.GetEntityCount());
    logWindow->UpdateLog("log_2", "Inactive entities: ", manager.GetInactiveCount());
    logWindow->UpdateLog("log_3", "Collidable entities: ", manager.GetColliderSize());
    logWindow->UpdateLog("log_4", "MousePosX: ", x);
    logWindow->UpdateLog("log_5", "MousePosY: ", y);
}

void Game::Select()
{
    // Do button action based upon its type
    switch (manager.buttons.SelectButton()) {
    case START: {
        Game::ProcessNextLevel();
        break;
    }
    case SETTINGS: {
        
        break;
    }
    case EXIT: {
        Game::ProcessGameOver();
        break;
    }
    default:
        break;
    }
}

void Game::StepUp()
{
    manager.buttons.HighLightLast();
}

void Game::StepDown()
{
    manager.buttons.HighLightNext();
}

// 3) Third game loop method
// Render our assets 
void Game::Render() {

    if (manager.HasNoEntities()) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    manager.Render();
    SDL_RenderPresent(renderer);

    // runs and calls its every type of entities update method
    
    if (logWindow != NULL) {
        logWindow->RenderLog();
    }
    
}

// METHODS USED IN OUR UPDATE METHOD
// Handle camera movement
void Game::HandleCameraMovement() {

    if (mainPlayer) {
        // In this case following the main player
        TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();

        camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
        camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

        // Clamping the values of the camera
        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
}
// Handle different type of collisions
void Game::Collision() 
{
    manager.collision.CheckCollision();
}

// Loading next level
void Game::ProcessNextLevel() {
    currentLevel = static_cast<Levels>(static_cast<int>(currentLevel) + 1);
    LevelSetup::LoadLevel(currentLevel, &manager, assetManager, map, &mainPlayer);
    std::cout << mainPlayer;
    LevelSetup::LoadPresets(currentLevel, &manager);
}

// Ending the game
void Game::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    isRunning = false;
}


void Game::DamagePlayer(Entity* thatEntity) {
    // lose health  
    mainPlayer->GetComponent<HealthComponent>()->setHealth(-1);
    if (mainPlayer->GetComponent<HealthComponent>()->getHealth() == 0) {
        ProcessGameOver();
    }
    // Enemy destroy
    thatEntity->SetInactive();
}

void Game::spawnEntity(std::string name, int posX, int posY , Direction faceOfDirection)
{
    /*
    New Logic :
    Whenever we spawn an entity check first if there is an existing inactive one with the same type
    If so then reuse that Object instead of create a new one
    */
    //Entity* temp = manager.GetInactiveByName(name);
    //if (temp) {
    //    temp->Reset(manager.presets.GetPresetAt(name),posX,posY,faceOfDirection);
    //}
    Entity& newEntity(manager.presets.LoadPreset(&manager, name, posX, posY , faceOfDirection));
    std::cout << "Outside entity name : " << newEntity.name << " at: " << &newEntity << std::endl;
}
