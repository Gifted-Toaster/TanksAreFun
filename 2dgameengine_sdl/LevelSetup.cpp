#include "LevelSetup.h"

#include "./Map.h"
#include "./AssetManager.h"
#include "./EntityManager.h"
#include "./Preset.h"

#include <fstream>
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

void swap_first_line(std::string level) {
    std::fstream file("../assets/tilemaps/" + level + "/" + level + ".lua");
    file << level + " = {\n";
    file.close();
}

void swap_subtables(std::string level) {
    //read and replace
    std::ifstream file("../assets/tilemaps/" + level + "/" + level + ".lua");
    std::vector<std::string> text;
    std::string line;
    while (getline(file, line)) { // reading every line into an array and if its pre defined one which need to be corrected then correct it
        if (line.find("tilesets", 0) != std::string::npos || line.find("layers", 0) != std::string::npos) {
            text.push_back(line);
            std::getline(file, line);
            if (line.find_first_of("0", 0) == std::string::npos) {
                int index = line.find_first_of("{");
                line.at(index) = '[';
                line.append("0] = {");
            }
        }
        text.push_back(line);
    }
    file.close();

    //write
    std::fstream out("../assets/tilemaps/" + level + "/" + level + ".lua");
    for (std::string lines : text) {
        out << lines << std::endl;
    }
    file.close();
}

void reconstruct_lua_file(std::string level) {
    swap_first_line(level);
    swap_subtables(level);
}

void LoadLevelMap(Levels levelNumber, Map* map)
{
    std::string level = "level" + std::to_string(levelNumber);

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);;
    lua.script_file("../assets/tilemaps/" + level + "/" + level + ".lua");

    reconstruct_lua_file(level); // Since the tiled editor places the whole data in a return block which sol cannot accept i had to manualy replace the first line

    sol::table levelMap = lua[level];

    // Getting the table for the texture id
    sol::table tilesetdata = levelMap["tilesets"];


    // Getting mapData from it
    sol::table layersdata = levelMap["layers"];
    sol::table mapFile = layersdata[0]["data"]; // ez lesz a lay ers-data de nem fstrema hanem egy array lesz



    //std::string mapFile;
    // Instantiation a new map component
    map = new Map(
        "terrain-texture-day",
        2,
        static_cast<int>(levelMap["tilewidth"]) // tilewidht+height
    );
    // Initializing this map
    map->LoadMap(
        &mapFile,
        static_cast<int>(levelMap["width"]), // width+height
        static_cast<int>(levelMap["height"]),
        static_cast<int>(tilesetdata[0]["imagewidth"]),
        static_cast<int>(tilesetdata[0]["imageheight"])
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

            // Add Transform Component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["width"]),
                    static_cast<int>(entity["components"]["transform"]["height"]),
                    static_cast<int>(entity["components"]["transform"]["scale"])
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
                        static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                        static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                        static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                        static_cast<bool>(entity["components"]["sprite"]["fixed"])
                        );
                }
                else {
                    newEntity.AddComponent<SpriteComponent>(textureId);
                }
            }

            // Add input control component
            sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
            if (existsInputComponent != sol::nullopt) {
                sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["input"]["keyboard"];
                if (existsKeyboardInputComponent != sol::nullopt) {
                    std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                    std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                    std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                    std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                    std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                    newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);
                }
            }

            // Add collider component
            sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
            if (existsColliderComponent != sol::nullopt) {
                std::string colliderTag = entity["components"]["collider"]["tag"];
                newEntity.AddComponent<ColliderComponent>(
                    colliderTag,
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["width"]),
                    static_cast<int>(entity["components"]["transform"]["height"])
                    );
            }

            // Add projectile emitter component
            sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];
            if (existsProjectileEmitterComponent != sol::nullopt) {
                int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                int parentEntityWidth = entity["components"]["transform"]["width"];
                int parentEntityHeight = entity["components"]["transform"]["height"];
                int projectileWidth = entity["components"]["projectileEmitter"]["width"];
                int projectileHeight = entity["components"]["projectileEmitter"]["height"];
                int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                int projectileRange = entity["components"]["projectileEmitter"]["range"];
                int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
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
                    projectileShouldLoop
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

            // ----- This is kinda bad in here but will do the trick
            if (newEntity.HasComponent<ColliderComponent>()) {
                manager.collision.AddElement(&newEntity);
            }

        }
        entityIndex++;
    }
}

// Loading our assets from our lua script file
// The file gets choosed based upon our current level
void LevelSetup::LoadLevel(Levels levelNumber, EntityManager* entityManager, AssetManager* assetManager, Map* map, Entity* player)
{
    // We set the current level
    // First we clear the manager if its not empty
    if (!entityManager->HasNoEntities()) {
        entityManager->ClearData();
    }
    if (!assetManager->HasNoAssets()) {
        assetManager->ClearData();
    }
   
    sol::state lua;

    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);;

    std::string levelName = "Level" + std::to_string(levelNumber);
    lua.script_file("../assets/scripts/" + levelName + ".lua");

    // We will load and get the data from this table
    sol::table levelData = lua[levelName];

    // a) Passing its assets data to this variable
    sol::table levelAssets = levelData["assets"];
    LoadLevelAssets(levelAssets, assetManager);

    // b) Passing its map data to this variable 
    if (levelNumber != 0) {
        LoadLevelMap(levelNumber, map);
    }

    // c) Passing its entity data to this variable
    sol::table levelEntities = levelData["entities"];
    LoadLevelEntities(levelEntities);

    player = entityManager->GetEntityByName("player");
}


void LevelSetup::LoadPresets(Levels levelNumber, EntityManager* manager) {

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    lua.script_file("../assets/scripts/EntityPresets.lua");


    //  Loading everything into this table
    sol::table presetData = lua["EntityPreset"];
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
                newPreset.AddComponent(type, entity["components"]["projectileEmitter"]["shouldLoop"]);
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
}
