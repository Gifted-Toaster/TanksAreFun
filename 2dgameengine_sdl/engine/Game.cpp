#pragma once

#include <iostream>
#include <fstream>
#include "Constans.h"
#include "Game.h"
#include "./Entity/Preset/Preset.h"
#include "./Entity/Map.h";
#include "./glm/glm.hpp"
#include "./Managers/AssetManager.h"
#include "./Managers/EntityManager.h"
#include "./misc/Player.h"
#include "./Entity/Component/TransformComponent.h"
#include "./Entity/Component/HealthComponent.h"
#include "./Controller/EventHandler.h"
#include "./Managers/CollisionManager.h"

EntityManager* Game::entity_manager;
AssetManager* Game::asset_manager;
CollisionManager* Game::collision_manager;
Player* Game::mainPlayer;
Mouse* Game::mouse;
Keyboard* Game::keyboard;

Map* map;
Levels currentLevel;
SDL_Renderer* Game::renderer;

SDL_Event Game::event;

//Mouse Game::cursor = new Mouse();
//Keyboard Game::keyboard = new Keyboard();

SDL_Rect Game::camera = { 0 ,0 ,WINDOW_WIDTH ,WINDOW_HEIGHT }; // Follows the player

// Log Window
LogWindow* Game::log_window;

Game::Game() { isRunning = false; }
Game::~Game() {}

// Returning the games current state
bool Game::IsRunning() const {
    return isRunning;
}
// Clearing data and closing SDL window when the game is over
void Game::Destroy() {
    entity_manager->DeleteData();
    asset_manager->DeleteData();

    // Closing logwindow only if it was opened
    if (log_window) {
        log_window->Destroy();
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
        log_window = new LogWindow(CONSOLE_WIDTH, CONSOLE_HEIGHT);
        std::cout << "Console working?" << std::endl << std::endl;
    }
    else {
        log_window = NULL;
    }

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
    mouse = new Mouse();
    keyboard = new Keyboard();
    mainPlayer = Player::LoadPlayer();
    entity_manager = EntityManager::InitializeEntityManager();
    asset_manager = new AssetManager(entity_manager);
    collision_manager = new CollisionManager(entity_manager);
    mouse->Initialize(MENU);
    keyboard->Initialize(MENU);
    LevelSetup::LoadLevel(MAIN_MENU, map);  

    isRunning = true;
    return;
}



// 1) First game loop method
// Handle user input
void Game::ProcessInput() {

    mouse->Update();
    keyboard->Update();
    // After the update in the menu we have to check if the cursor is on a button , if so then highlight it

    // 0 is false 1 is true
    if (EventHandler::isThereUserInput(&Game::event)) { // this function gives back 0 if there is no user action in que , otherwise 1
        switch (Game::event.type) {
            case SDL_MOUSEBUTTONDOWN: {
                EventHandler::HandleUserInput_Mouse(Game::event, mouse->state);
                break;
            }
            case SDL_KEYDOWN: {
                EventHandler::HandleUserInput_Keyboard(Game::event, keyboard->state);
                if (Game::event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            }
            default: {
                break;
            }
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
    entity_manager->Update(deltaTime);
 
    if (log_window != NULL) {
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
    log_window->UpdateLog("FPS" , "FPS: " , deltaTime*1000);
    log_window->UpdateLog("log_1" , "Active entities: ", entity_manager->GetEntityCount());
    log_window->UpdateLog("log_2", "Inactive entities: ", entity_manager->GetInactiveCount());
    log_window->UpdateLog("log_3", "Collidable entities: ", collision_manager->ListSize());
    log_window->UpdateLog("log_4", "MousePosX: ", mouse->getPosX());
    log_window->UpdateLog("log_5", "MousePosY: ", mouse->getPosY());
    //logWindow->UpdateLog("log_6", ": ", y);
}

void Game::Select()
{
    // Do button action based upon its type
    switch (entity_manager->buttons.SelectButton()) {
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
    entity_manager->buttons.HighLightLast();
}

void Game::StepDown()
{
    entity_manager->buttons.HighLightNext();
}

// 3) Third game loop method
// Render our assets 
void Game::Render() {


    if (entity_manager->HasNoEntities()) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    entity_manager->Render();
    SDL_RenderPresent(renderer);

    // runs and calls its every type of entities update method
    
    if (log_window != NULL) {
        log_window->RenderLog();
    }
    
}

void Game::MoveCamera(Direction dir) {
    switch (dir) {
        case UP:
            camera.y += 10;
            break;
        case DOWN:
            camera.y -= 10;
        case RIGHT:
            camera.x += 10;
            break;
        case LEFT:
            camera.x -= 10;
            break;
    }

    // Clamping the values of the camera
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

// METHODS USED IN OUR UPDATE METHOD
// Handle camera movement
void Game::HandleCameraMovement() {


    //if (mainPlayer) {
    //    // In this case following the main player
    //    TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();

    //    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    //    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    //    // Clamping the values of the camera
    //    camera.x = camera.x < 0 ? 0 : camera.x;
    //    camera.y = camera.y < 0 ? 0 : camera.y;
    //    camera.x = camera.x > camera.w ? camera.w : camera.x;
    //    camera.y = camera.y > camera.h ? camera.h : camera.y;
    //}
    //else {
    //    // missing player error
    //}
}


// Feltetelezzuk hogy a button objektum statikus marad a helyzetet tekintve igy elkerulhetjuk a folyamatos lista iteraciot ha kimentjuk a teruletet amit lefednek generalasnal

// Handle different type of collisions
void Game::Collision() 
{
    collision_manager->CheckCollision();
    collision_manager->MouseCollideWithButton(mouse->getPosX(), mouse->getPosY()); // mukodik
}

// Loading next level
void Game::ProcessNextLevel() {
    currentLevel = static_cast<Levels>(static_cast<int>(currentLevel) + 1);
    keyboard->state = IN_GAME;
    mouse->state = IN_GAME;
    LevelSetup::LoadLevel(currentLevel, map);
}

// Ending the game
void Game::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    isRunning = false;
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
    //Entity& newEntity(manager.presets.LoadPreset(&manager, name, mainPlayer , faceOfDirection));
    //std::cout << "Outside entity name : " << newEntity.name << " at: " << &newEntity << std::endl;
}
