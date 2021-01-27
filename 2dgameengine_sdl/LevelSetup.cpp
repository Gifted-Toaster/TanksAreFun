#include "LevelSetup.h"

#include "./Map.h"
#include "./AssetManager.h"
#include "./EntityManager.h"
#include "./Preset.h"

#include <fstream>
#include <map>
#include <string>

#include "./Component.h"
#include "./TransformComponent.h"
#include "./SpriteComponent.h"
#include "./KeyboardControlComponent.h"
#include "./ColliderComponent.h"
#include "./TextLabelComponent.h"
#include "./ProjectileEmitterComponent.h"
#include "./HealthComponent.h"
#include "./ButtonComponent.h"

#include <cmath>

void LoadLevelAssets(sol::table levelAssets, AssetManager* assetManager)
{
    unsigned int assetIndex = 0;
    while (true) {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        if (existsAssetIndexNode == sol::nullopt) {
            break;
        }
        else {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType.compare("texture") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetId, assetFile.c_str());
            }
            if (assetType.compare("font") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                int fontSize = asset["fontSize"];
                assetManager->AddFont(assetId, assetFile.c_str(), fontSize);
            }
        }
        assetIndex++;
    }
}

std::map<int, TileColliderInit> GetTileCollisionData(sol::table* tileData) {
    sol::table currentTileColliderData;
    std::map<int, TileColliderInit> colliderHolder;

    // Collecting each collidable tilepieces ID and its rectangle position and dimension
    tileData->for_each([&](sol::object const& key, sol::table const& value) {
        // Tablaban kerjuk ki a value-t
        currentTileColliderData = value["objectGroup"]["objects"][1];
        colliderHolder.emplace(
            value["id"],
            TileColliderInit{
                currentTileColliderData["x"] ,
                currentTileColliderData["y"],
                currentTileColliderData["width"] ,
                currentTileColliderData["height"] }
        );
        });
    return colliderHolder;
}

void LoadLevelMap(Levels levelNumber, Map* map)
{
    std::string level = "level" + std::to_string(levelNumber);

    sol::state lua;
    sol::table levelMap;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);;

    try {
        levelMap = lua.script_file("../assets/level_data/" + level + "/map/" + level + "_map.lua");
    }
    catch (const sol::error& e) {
        //TODO
    }

    // Tile collider
    sol::table tilesetdata = levelMap["tilesets"][1];
    sol::table tileData = tilesetdata["tiles"];

    // Getting mapData from it
    sol::table layersdata = levelMap["layers"][1];
    sol::table mapFile = layersdata["data"]; 


    // Instantiation a new map component
    map = new Map(
        "terrain-texture-day",
        2,
        static_cast<float>(levelMap["tilewidth"]) // tilewidht+height
    );
    // Initializing this map
    map->LoadMap(
        &mapFile,
        static_cast<float>(levelMap["width"]), // width+height
        static_cast<float>(levelMap["height"]),
        GetTileCollisionData(&tileData)
    );
}

void LoadLevelEntities(sol::table levelEntities)
{
    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
        if (existsEntityIndexNode == sol::nullopt) {
            break;
        }
        else {
            sol::table entity = levelEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

            // Add new entity
            Entity& newEntity(manager.AddEntity(entityName, entityLayerType));
            std::cout << &newEntity << " ...\n";
            // Add Transform Component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                    static_cast<float>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<float>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<float>(entity["components"]["transform"]["velocity"]["x"]),
                    static_cast<float>(entity["components"]["transform"]["velocity"]["y"]),
                    static_cast<float>(entity["components"]["transform"]["width"]),
                    static_cast<float>(entity["components"]["transform"]["height"]),
                    static_cast<float>(entity["components"]["transform"]["scale"])
                    );
            }

            // Add sprite component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            if (existsSpriteComponent != sol::nullopt) {
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                bool isAnimated = entity["components"]["sprite"]["animated"];
                if (isAnimated) {
                    newEntity.AddComponent<SpriteComponent>(
                        textureId,
                        static_cast<float>(entity["components"]["sprite"]["frameCount"]),
                        static_cast<float>(entity["components"]["sprite"]["animationSpeed"]),
                        static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                        static_cast<bool>(entity["components"]["sprite"]["fixed"])
                        );
                }
                else {
                    newEntity.AddComponent<SpriteComponent>(textureId);
                }
            }

            // Scrap this whole thing and hardcode the player since its no reason to generalize a single object
            //// Add input control component
            //sol::optional<sol::table> existsInputComponent = entity["components"]["controller"];
            //if (existsInputComponent != sol::nullopt) {
            //    sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["controller"]["keyboard"];
            //    sol::optional<sol::table> existsMouseInputComponent = entity["components"]["controller"]["mouse"];
            //    if (existsKeyboardInputComponent != sol::nullopt) {
            //        std::string upKey = entity["components"]["controller"]["keyboard"]["up"];
            //        std::string rightKey = entity["components"]["controller"]["keyboard"]["right"];
            //        std::string downKey = entity["components"]["controller"]["keyboard"]["down"];
            //        std::string leftKey = entity["components"]["controller"]["keyboard"]["left"];
            //        std::string shootKey = entity["components"]["controller"]["keyboard"]["shoot"];
            //        newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);
            //    }
            //    if (existsMouseInputComponent != sol::nullopt) {
            //        std::string left_click = entity["components"]["controller"]["mouse"]["left_click"];
            //        std::string right_click = entity["components"]["controller"]["mouse"]["right_click"];
            //        newEntity.AddComponent<KeyboardControlComponent>(left_click,right_click);
            //    }
            //}

            // Add collider component
            sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
            if (existsColliderComponent != sol::nullopt) {
                std::string colliderTag = entity["components"]["collider"]["tag"];
                newEntity.AddComponent<ColliderComponent>(
                    colliderTag,
                    static_cast<float>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<float>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<float>(entity["components"]["transform"]["width"]),
                    static_cast<float>(entity["components"]["transform"]["height"])
                    );
            }

            // Add projectile emitter component
            sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];
            if (existsProjectileEmitterComponent != sol::nullopt) {
                float parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                float parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                float parentEntityWidth = entity["components"]["transform"]["width"];
                float parentEntityHeight = entity["components"]["transform"]["height"];
                float projectileWidth = entity["components"]["projectileEmitter"]["width"];
                float projectileHeight = entity["components"]["projectileEmitter"]["height"];
                float projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                float projectileRange = entity["components"]["projectileEmitter"]["range"];
                float projectileAngle = entity["components"]["projectileEmitter"]["angle"];
                bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
                std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
                Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
                projectile.AddComponent<TransformComponent>(
                    parentEntityXPos + (parentEntityWidth / 2),
                    parentEntityYPos + (parentEntityHeight / 2),
                    0,
                    0,
                    projectileWidth,
                    projectileHeight,
                    1
                    );
                projectile.AddComponent<SpriteComponent>(textureAssetId);
                projectile.AddComponent<ProjectileEmitterComponent>(
                    projectileSpeed,
                    projectileAngle,
                    projectileRange,
                    projectileShouldLoop,
                    &newEntity
                    );
                projectile.AddComponent<ColliderComponent>(
                    "PROJECTILE",
                    parentEntityXPos,
                    parentEntityYPos,
                    projectileWidth,
                    projectileHeight
                    );
            }

            // Add a Health Component
            sol::optional<sol::table> existsHealthComponent = entity["components"]["health"];
            if (existsHealthComponent != sol::nullopt) {
                int startingHealth = entity["components"]["health"]["start"];
                newEntity.AddComponent<HealthComponent>(startingHealth);
            }

            // Add a text Component
            sol::optional<sol::table> existsTextLabelComponent = entity["components"]["textLabel"];
            if (existsTextLabelComponent != sol::nullopt) {
                int posX = entity["components"]["textLabel"]["posx"];
                int posY = entity["components"]["textLabel"]["posy"];
                std::string text = entity["components"]["textLabel"]["text"];
                std::string fontType = entity["components"]["textLabel"]["fontType"];
                // todo to convert this value not the one in constans.h
                std::string color = entity["components"]["textLabel"]["color"];
                bool dinamic = static_cast<bool>(entity["components"]["textLabel"]["dinamic"]);
                newEntity.AddComponent<TextLabelComponent>(posX, posY, text, fontType, WHITE_COLOR);
            }

            // Add a button Component
            sol::optional<sol::table> existsButtonComponent = entity["components"]["button"];
            if (existsButtonComponent != sol::nullopt) {
                int posX = entity["components"]["button"]["posX"];
                int posY = entity["components"]["button"]["posY"];
                int w = entity["components"]["button"]["width"];
                int h = entity["components"]["button"]["height"];
                std::string text = entity["components"]["button"]["text"];
                std::string color = entity["components"]["button"]["color"];
                std::string fontType = entity["components"]["button"]["fontFam"];
                ButtonType type = static_cast<ButtonType>(static_cast<int>(entity["components"]["button"]["type"]));
                // todo to convert this value not the one in constans.h

                newEntity.AddComponent<ButtonComponent>(posX, posY, w, h, text, WHITE_COLOR, fontType, type);
                manager.buttons.AddButton(&newEntity);
            }
        }
        entityIndex++;
    }
    
}

// Loading our assets from our lua script file
// The file gets choosed based upon our current level
void LevelSetup::LoadLevel(Levels levelNumber, EntityManager* entityManager, AssetManager* assetManager, Map* map)
{
    // We set the current level
    // First we clear the manager if its not empty
    if (!entityManager->HasNoEntities()) {
        entityManager->DeleteData();
    }
    if (!assetManager->HasNoAssets()) {
        assetManager->DeleteData();
    }
   
    sol::state lua;

    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);;

    std::string levelName = "level" + std::to_string(levelNumber);
    if (levelNumber == MAIN_MENU) {
        lua.script_file("../assets/level_data/menu/" + levelName + "_data.lua");
    }
    else {
        lua.script_file("../assets/level_data/" + levelName + "/" + levelName + "_data.lua");
    }

    // Our main table -> level"levelNumber"
    sol::table levelData = lua[levelName];

    // a) Getting the asset table and load it
    sol::table levelAssets = levelData["assets"];
    LoadLevelAssets(levelAssets, assetManager);

    // b) Opening and loading the map file and the presets , the first one loads the tile collision aswell
    if (levelNumber != 0) {
        LoadLevelMap(levelNumber, map);
        LoadPresets(levelNumber, entityManager);
    }

    // c) Getting the entitiy table and load it
    sol::table levelEntities = levelData["entities"];
    LoadLevelEntities(levelEntities);


}


void LevelSetup::LoadPresets(Levels levelNumber, EntityManager* manager) {

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    std::string levelName = "level" + std::to_string(levelNumber);
    lua.script_file("../assets/level_data/" + levelName + "/" + levelName + "_presets.lua");
    


    //  Loading everything into this table
    levelName = "Level" + std::to_string(levelNumber) + "Presets";
    sol::table presetData = lua[levelName];
    // a) Passing its assets data to this variable
    sol::table presetEntities = presetData["entities"];


    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntityIndexNode = presetEntities[entityIndex];
        if (existsEntityIndexNode == sol::nullopt) {
            break;
        }
        else {
            sol::table entity = presetEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

            // Add new entity
            Preset& newPreset(manager->presets.AddPreset(entityName, entityLayerType));

            // Add Transform Component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt) {
                ComponentType type = TRANSFORM;
                newPreset.AddComponent(type, entity["components"]["transform"]["position"]["x"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["position"]["y"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["velocity"]["x"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["velocity"]["y"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["width"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["height"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["scale"]);

            }

            // Add sprite component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            if (existsSpriteComponent != sol::nullopt) {
                ComponentType type = SPRITE;
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                bool isAnimated = entity["components"]["sprite"]["animated"];
                if (isAnimated) {
                    newPreset.AddComponent(type, textureId);
                    newPreset.AddComponent(type, entity["components"]["sprite"]["frameCount"]);
                    newPreset.AddComponent(type, entity["components"]["sprite"]["animationSpeed"]);
                    newPreset.AddComponent(type, entity["components"]["sprite"]["hasDirections"]);
                    newPreset.AddComponent(type, entity["components"]["sprite"]["fixed"]);
                }
                else {
                    newPreset.AddComponent(type, textureId);
                }
            }

            // Add input control component
            sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
            if (existsInputComponent != sol::nullopt) {
                sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["input"]["keyboard"];
                ComponentType type = KEYBOARD;
                if (existsKeyboardInputComponent != sol::nullopt) {
                    newPreset.AddComponent(type, entity["components"]["input"]["keyboard"]["up"]);
                    newPreset.AddComponent(type, entity["components"]["input"]["keyboard"]["right"]);
                    newPreset.AddComponent(type, entity["components"]["input"]["keyboard"]["down"]);
                    newPreset.AddComponent(type, entity["components"]["input"]["keyboard"]["left"]);
                    newPreset.AddComponent(type, entity["components"]["input"]["keyboard"]["shoot"]);
                }
            }

            // Add collider component
            sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
            if (existsColliderComponent != sol::nullopt) {
                // miert string?
                ComponentType type = COLLIDER;
                std::string colliderTag = entity["components"]["collider"]["tag"];

                newPreset.AddComponent(type, colliderTag);
                newPreset.AddComponent(type, entity["components"]["transform"]["position"]["x"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["position"]["y"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["width"]);
                newPreset.AddComponent(type, entity["components"]["transform"]["height"]);
            }
            // TODO ---------------------------------------------------------------------
            //// Add projectile emitter component
            sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];
            if (existsProjectileEmitterComponent != sol::nullopt) {
                ComponentType type = PROJECTILE_EMITTER;
                newPreset.AddComponent(type, entity["components"]["projectileEmitter"]["speed"]);
                newPreset.AddComponent(type, entity["components"]["projectileEmitter"]["angle"]);
                newPreset.AddComponent(type, entity["components"]["projectileEmitter"]["range"]);
                bool asd = entity["components"]["projectileEmitter"]["shouldLoop"]; // valami itt a bool stringbe olvasasaval elszarodik
                newPreset.AddComponent(type, std::to_string(asd));
            }

            // Add a Health Component
            sol::optional<sol::table> existsHealthComponent = entity["components"]["health"];
            if (existsHealthComponent != sol::nullopt) {
                ComponentType type = HEALTH;
                newPreset.AddComponent(type, entity["components"]["health"]["start"]);
            }
            // Add a text Component
            sol::optional<sol::table> existsTextLabelComponent = entity["components"]["textLabel"];
            if (existsTextLabelComponent != sol::nullopt) {
                ComponentType type = TEXTLABEL;
                newPreset.AddComponent(type, entity["components"]["textLabel"]["posx"]);
                newPreset.AddComponent(type, entity["components"]["textLabel"]["posy"]);
                newPreset.AddComponent(type, entity["components"]["textLabel"]["text"]);
                newPreset.AddComponent(type, entity["components"]["textLabel"]["fontType"]);
                newPreset.AddComponent(type, entity["components"]["textLabel"]["color"]);
            }
        }
        entityIndex++;
    }
    std::cout << "Presets has been loaded at " << levelNumber << ". \n";
}
