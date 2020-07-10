WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

-- About 16 x 9 resolution, to give it an NES-like feel
VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

PADDLE_SPEED = 200
-- import another lua file
push = require 'push'

-- Required in every Love game
function love.load()
    love.graphics.setDefaultFilter('nearest', 'nearest')    -- get rid of filter

    -- Create object with new font (file in directory).  8 pixel size
    smallFont = love.graphics.newFont('font.ttf', 8)
    -- score font with 32 pixel font
    scoreFont = love.graphics.newFont('font.ttf', 32)

    player1Score = 0
    player2Score = 0

    player1Y = 30
    player2Y = VIRTUAL_HEIGHT - 40

    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        vsync = true,
        resizable = false
    })
end

function love.update(dt)
    if love.keyboard.isDown('w') then
        player1Y = player1Y - PADDLE_SPEED * dt
    elseif love.keyboard.isDown('s') then
        player1Y = player1Y + PADDLE_SPEED * dt
    end

    if love.keyboard.isDown('up') then
        player2Y = player2Y - PADDLE_SPEED * dt
    elseif love.keyboard.isDown('down') then
        player2Y = player2Y + PADDLE_SPEED * dt
    end
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    end
end

function love.draw()
    push:apply('start')

    -- Set screen (fill) color.  Draw this before drawing anything else
    -- / by 255 bc Lua wants number betwen 0.0 - 1.0 for RGBA values.  / 255 converts from normal RGB
    love.graphics.clear(40 / 255, 45 / 255, 52 / 255, 255 / 255)

    -- Draw the ball, 5 x 5 pixels
    love.graphics.rectangle('fill', VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 5, 5)

    -- Draw left paddle
    love.graphics.rectangle('fill', 5, player1Y, 5, 20)

    -- Draw right paddle
    love.graphics.rectangle('fill', VIRTUAL_WIDTH - 10, player2Y, 5, 20)

    love.graphics.setFont(smallFont)
    love.graphics.printf(
        "Hello Pong!",          -- text to render
        0,                      -- starting x (0 for center)
        20,                     -- starting y (20 pixels down screen)
        VIRTUAL_WIDTH,          -- Number of pixesl to center within (entire screen here)
        'center')               -- alignment mode (center left or right)

    love.graphics.setFont(scoreFont)
    love.graphics.print(player1Score, VIRTUAL_WIDTH / 2 - 50, VIRTUAL_HEIGHT / 3)
    love.graphics.print(player2Score, VIRTUAL_WIDTH / 2 + 30, VIRTUAL_HEIGHT / 3)

    push:apply('end')
end