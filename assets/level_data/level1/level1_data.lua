----------------------------------------------------
-- Get the current time of the day from the OS
----------------------------------------------------
math.randomseed(os.time())
local currentSystemHour = os.date("*t").hour
local mapTextureAssetId = "terrain-texture-day"

----------------------------------------------------
-- Use a night-map or a day-map texture (9am-9pm)
----------------------------------------------------
if currentSystemHour > 9 and currentSystemHour < 21 then
    mapTextureAssetId = "terrain-texture-day"
else
    mapTextureAssetId = "terrain-texture-night"
end


level1 = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="texture", id = "terrain-texture-day", file = "../assets/level_data/level1/map/jungle.png" },
        [1] = { type="texture", id = "terrain-texture-night", file = "../assets/level_data/level1/map/jungle-night.png" },
        [2] = { type="texture", id = "chopper-texture", file = "../assets/level_data/level1/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "projectile-texture", file = "../assets/level_data/level1/images/bullet-enemy.png" },
        [4] = { type="texture", id = "obstacles-texture", file = "../assets/level_data/level1/images/obstacles.png" },
        [5] = { type="texture", id = "truck-left-texture", file = "../assets/level_data/level1/images/truck-left.png" },
        [6] = { type="texture", id = "truck-right-texture", file = "../assets/level_data/level1/images/truck-right.png" },
        [7] = { type="texture", id = "truck-down-texture", file = "../assets/level_data/level1/images/truck-down.png" },
        [8] = { type="texture", id = "tank-big-down-texture", file = "../assets/level_data/level1/images/tank-big-down.png" },
        [9] = { type="texture", id = "tank-big-left-texture", file = "../assets/level_data/level1/images/tank-big-left.png" },
        [10] = { type="texture", id = "tank-big-right-texture", file = "../assets/level_data/level1/images/tank-big-right.png" },
        [11] = { type="texture", id = "tank-small-left-texture", file = "../assets/level_data/level1/images/tank-small-left.png" },
        [12] = { type="texture", id = "tank-small-right-texture", file = "../assets/level_data/level1/images/tank-small-right.png" },
        [13] = { type="texture", id = "army-group-1-texture", file = "../assets/level_data/level1/images/army-group-1.png" },
        [14] = { type="texture", id = "army-group-2-texture", file = "../assets/level_data/level1/images/army-group-2.png" },
        [15] = { type="texture", id = "army-group-3-texture", file = "../assets/level_data/level1/images/army-group-3.png" },
        [16] = { type="texture", id = "rock-big-1-texture", file = "../assets/level_data/level1/images/rock-big-1.png" },
        [17] = { type="texture", id = "rock-big-2-texture", file = "../assets/level_data/level1/images/rock-big-2.png" },
        [18] = { type="texture", id = "rock-big-3-texture", file = "../assets/level_data/level1/images/rock-big-3.png" },
        [19] = { type="texture", id = "rock-big-4-texture", file = "../assets/level_data/level1/images/rock-big-4.png" },
        [20] = { type="texture", id = "rock-small-1-texture", file = "../assets/level_data/level1/images/rock-small-1.png" },
        [21] = { type="texture", id = "tree-small-1-texture", file = "../assets/level_data/level1/images/tree-small-1.png" },
        [22] = { type="texture", id = "tree-small-2-texture", file = "../assets/level_data/level1/images/tree-small-2.png" },
        [23] = { type="texture", id = "tree-small-3-texture", file = "../assets/level_data/level1/images/tree-small-3.png" },
        [24] = { type="texture", id = "tree-small-4-texture", file = "../assets/level_data/level1/images/tree-small-4.png" },
        [25] = { type="texture", id = "tree-small-5-texture", file = "../assets/level_data/level1/images/tree-small-5.png" },
        [26] = { type="texture", id = "tree-small-6-texture", file = "../assets/level_data/level1/images/tree-small-6.png" },
        [27] = { type="texture", id = "tree-small-7-texture", file = "../assets/level_data/level1/images/tree-small-7.png" },
        [28] = { type="texture", id = "tree-small-8-texture", file = "../assets/level_data/level1/images/tree-small-8.png" },
        [29] = { type="texture", id = "start-texture", file = "../assets/level_data/level1/images/start.png" },
        [30] = { type="texture", id = "heliport-texture", file = "../assets/level_data/level1/images/heliport.png" },
        [31] = { type="texture", id = "bullet-friendly-texture", file = "../assets/level_data/level1/images/bullet-friendly.png" },
        [32] = { type="texture", id = "radar-texture", file = "../assets/level_data/level1/images/radar.png" },
        [33] = { type="sound", id = "blades-sound", file = "../assets/level_data/level1/sounds/blades.wav" },
        [34] = { type="font", id = "charriot-font", file = "../assets/fonts/charriot.ttf", fontSize = 14 },
        [35] = { type="texture", id = "kyra", file = "../assets/level_data/level1/images/kyr.png" },
        [36] = { type="texture", id = "enemy_main_building", file = "../assets/level_data/level1/images/buildings/enemy_main_building.png" },
        [37] = { type="texture", id = "player_main_building", file = "../assets/level_data/level1/images/buildings/player_main_building.png"},
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = mapTextureAssetId,
        file = "../assets/level_data/level1/map/level1.lua"
    },

    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] = {
            name = "player_main_building",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 50,
                        y = 25
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 100,
                    height = 257,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "player_main_building",
                    animated = false
                } 
            }
        },
        [1] = {
            name = "enemy_main_building",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 400,
                        y = 250
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 100,
                    height = 69,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "enemy_main_building",
                    animated = false
                },
                collider = {
                    tag = "LEVEL_COMPLETE"
                }
            }
        },
        [2] = {
            name = "tank1",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 650,
                        y = 405
                    },
                    velocity = {
                        x = 10,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "tank-big-left-texture",
                    animated = false
                },
                collider = {
                    tag = "ENEMY"
                },
                projectileEmitter = {
                    speed = 70,
                    range = 300,
                    angle = 180,
                    width = 4,
                    height = 4,
                    shouldLoop = true,
                    textureAssetId = "projectile-texture"
                }
            }
        },
        [3] = {
            name = "radar",
            layer = 6,
            components = {
                transform = {
                    position = {
                        x = 720,
                        y = 15
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 64,
                    height = 64,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "radar-texture",
                    animated = true,
                    frameCount = 8,
                    animationSpeed = 150,
                    hasDirections = false,
                    fixed = true
                }
            }
        },
        [4] = {
            name = "label-level-name",
            layer = 6,
            components = {
                textLabel = {
                    posx = 10,
                    posy = 10,
                    text = "First level...",
                    fontType = "charriot-font",
                    color = "red",
                    dinamic = false
				}     
			}
        }
    }
}
