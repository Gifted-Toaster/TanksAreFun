level1 = {
  version = "1.4",
  luaversion = "5.1",
  tiledversion = "1.4.0",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 10,
  height = 10,
  tilewidth = 32,
  tileheight = 32,
  nextlayerid = 2,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    [0] = {
      name = "jungle",
      firstgid = 1,
      filename = "asd.tsx",
      tilewidth = 32,
      tileheight = 32,
      spacing = 0,
      margin = 0,
      columns = 10,
      image = "../assets/tilemaps/jungle.png",
      imagewidth = 320,
      imageheight = 96,
      objectalignment = "unspecified",
      tileoffset = {
        x = 0,
        y = 0
      },
      grid = {
        orientation = "orthogonal",
        width = 32,
        height = 32
      },
      properties = {},
      terrains = {},
      tilecount = 30,
      tiles = {}
    }
  },
  layers = {
    [0] = {
      type = "tilelayer",
      x = 0,
      y = 0,
      width = 10,
      height = 10,
      id = 1,
      name = "Tile Layer 1",
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 7, 7, 1, 7, 4, 1, 7, 2, 1,
        8, 7, 7, 1, 1, 1, 1, 7, 4, 4,
        8, 1, 1, 16, 10, 10, 11, 1, 1, 1,
        8, 1, 1, 23, 22, 22, 12, 1, 7, 4,
        8, 1, 7, 23, 22, 22, 12, 1, 1, 4,
        8, 1, 1, 15, 14, 14, 13, 1, 1, 1,
        1, 2, 2, 1, 1, 1, 1, 1, 1, 7,
        1, 1, 4, 4, 4, 1, 1, 4, 1, 2,
        4, 1, 4, 1, 1, 1, 1, 1, 1, 1
      }
    }
  }
}
