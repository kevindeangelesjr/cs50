-- Window settings
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720
VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

-- Import class and push libraries
Class = require 'class'
push = require 'push'

-- Import Map class from Map.lua and import functions from Util.lua
require 'Util'
require 'Map'

function love.load()

    map = Map()

    -- Remove blurriness
    love.graphics.setDefaultFilter('nearest', 'nearest')

    -- Set up screen
    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        resizable = false,
        vsync = true
    })
end

function love.update(dt)


end

function love.draw()

    push:apply('start')

    -- Screen background color
    love.graphics.clear(108 / 255, 140 / 255, 1 , 1)
    map:render()

    push:apply('end')
end