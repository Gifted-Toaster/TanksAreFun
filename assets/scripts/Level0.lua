Level0 = {
    ----------------------------------------------------
    -- table to pre define entities and their components for dinamic creation
    ----------------------------------------------------

    assets = { -- asset font types and images for example
        [0] = { type="font", id = "charriot-font", file = "../assets/fonts/charriot.ttf", fontSize = 14 },
        [1] = { type="font", id = "charriot-font-big", file = "../assets/fonts/charriot.ttf", fontSize = 26 },
        [2] = { type="texture", id = "kyra", file = "../assets/images/kyr.png" },
        [3] = { type="texture", id = "bg-image", file = "../assets/tilemaps/main_menu.png" }
    },

    map = {
        textureAssetId = "bg-image",
        file = "../assets/tilemaps/main_menu.map",
        scale = 1, -- scale of the tiles
        tileSize = 32, -- size of the side of the rectangles which will be rendered on screen
        mapSizeX = 1, -- map file collumns
        mapSizeY = 1  -- map file rows
    },

    entities = {
        [0] = {
            name = "game_name",
            layer = 1,
            components = {
                transform = {
                    position = {
                        x = 275,
                        y = 25
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 250,
                    height = 75,
                    scale = 1,
                    rotation = 0
                },
                textLabel = {
                    posx = 275,
                    posy = 25,
                    text = "Some Game",
                    fontType = "charriot-font-big",
                    color = "red",
                    dinamic = false
				}  
                -- implement a button component
            }
        },
        [1] = {
            name = "start_button",
            layer = 1,
            components = {
                button = {
                    posX = 325,
                    posY = 150,
                    width = 150,
                    height = 50,
                    text = "Start Game",
                    color = "white",
                    fontFam = "charriot-font-big",
                    type = 0
                }
                -- implement a button component
            }
        },
        [2] = {
            name = "controll_button",
            layer = 1,
            components = {
                button = {
                    posX = 325,
                    posY = 225,
                    width = 150,
                    height = 50,
                    text = "Controlls",
                    color = "white",
                    fontFam = "charriot-font-big",
                    type = 1
                }
                -- implement a button component
            }
        },
        [3] = {
            name = "exit_button",
            layer = 1,
            components = {
                button = {
                    posX = 325,
                    posY = 300,
                    width = 150,
                    height = 50,
                    text = "Exit Game",
                    color = "white",
                    fontFam = "charriot-font-big",
                    type = 2
                }
                -- implement a button component
            }
        },
        [4] = {
            name = "bg-image",
            layer = 0,
            components = {
                transform = {
                    position = {
                        x = 0,
                        y = 0
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 800,
                    height = 600,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "bg-image",
                    animated = false,
                    frameCount = 2,
                    animationSpeed = 0,
                    hasDirections = false,
                    fixed = true
                }
            }
        },

        [5] = {
            name = "controller",
            layer = 0,
            components = {
                input = {
                    keyboard = {
                        up = "w",
                        left = "",
                        down = "s",
                        right = "",
                        shoot = "space"
                    }
                }
            }
        }
    }
}