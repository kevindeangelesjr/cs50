WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

-- About 16 x 9 resolution, to give it an NES-like feel
VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

-- import another lua file
push = require 'push'

-- Required in every Love game
function love.load()
    love.graphics.setDefaultFilter('nearest', 'nearest')    -- get rid of filter
    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        vsync = true,
        resizable = false
    })
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    end
end

function love.draw()
    push:apply('start')

    love.graphics.printf(
        "Hello Pong!",          -- text to render
        0,                      -- starting x (0 for center)
        VIRTUAL_HEIGHT / 2 - 6,  -- starting y (halfway down screen)
        VIRTUAL_WIDTH,           -- Number of pixesl to center within (entire screen here)
        'center')               -- alignment mode (center left or right)

    push:apply('end')
end