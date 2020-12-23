Level1Presets = {
    ----------------------------------------------------
    -- table to pre define entities and their components for dinamic creation
    ----------------------------------------------------
    entities = {
        [0] = {
            name = "projectile",
            layer = 3,
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
                    width = 4,
                    height = 4,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "projectile-texture",
                    animated = false
                },
                collider = {
                    tag = "FRIENDLY_PROJECTILE"
                },
                projectileEmitter = {
                    speed = 75,
                    range = 500,
                    shouldLoop = false
				}
            }
        },
        [1] = {
            name = "text",
            layer = 3,
            components = {
                textLabel = {
                    posx = 100,
                    posy = 100,
                    text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                    fontType = "charriot-font",
                    color = "",
                    dinamic = true
                }
            }
        }
    }
}
