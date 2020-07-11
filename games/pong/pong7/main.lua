-- import another lua libraries and classes
Class = require 'class'
push = require 'push'
require 'Paddle'
require 'Ball'

-- Window settings
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

-- About 16 x 9 resolution, to give it an NES-like feel
VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

-- Speed at which paddle will move
PADDLE_SPEED = 200

-- Required in every Love game
function love.load()

    love.window.setTitle('Pong')

    math.randomseed(os.time())

    love.graphics.setDefaultFilter('nearest', 'nearest')    -- get rid of filter

    -- Create object with new font (file in directory).  8 pixel size
    smallFont = love.graphics.newFont('font.ttf', 8)
    -- score font with 32 pixel font
    scoreFont = love.graphics.newFont('font.ttf', 32)

    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        vsync = true,
        resizable = false
    })

    player1Score = 0
    player2Score = 0

    -- Construct Paddles
    player1 = Paddle(5, 20, 5, 20)
    player2 = Paddle(VIRTUAL_WIDTH - 10, VIRTUAL_HEIGHT - 30, 5, 20)

    -- Construct ball
    ball = Ball(VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 5, 5)

    gameState = 'start'
end

function love.update(dt)

    -- collision detection
    if ball:collides(player1) then
        -- deflect ball to the right
        ball.dx = -ball.dx
    end

    if ball:collides(player2) then
        -- deflect ball to the left
        ball.dx = -ball.dx
    end

    if ball.y <= 0 then
        -- deflect the ball down
        ball.dy = -ball.dy
        ball.y = 0
    end

    if ball.y >= VIRTUAL_HEIGHT - 4 then
        -- deflect the ball up
        ball.dy = -ball.dy
        ball.y = VIRTUAL_HEIGHT - 4
    end

    -- PLayer 1 paddle
    if love.keyboard.isDown('w') then
        player1.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('s') then
        player1.dy = PADDLE_SPEED
    else
        player1.dy = 0
    end

    -- Player 2 paddle
    if love.keyboard.isDown('up') then
        player2.dy = -PADDLE_SPEED
    elseif love.keyboard.isDown('down') then
        player2.dy = PADDLE_SPEED
    else
        player2.dy = 0
    end

    player1:update(dt)
    player2:update(dt)

    if gameState == 'play' then
        ball:update(dt)
    end
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    elseif key == 'enter' or key == 'return' then
        if gameState == 'start' then
            gameState = 'play'
        elseif gameState == 'play' then
            gameState = 'start'
            ball:reset()
        end
    end
end

function love.draw()
    push:apply('start')

    -- Set screen (fill) color.  Draw this before drawing anything else
    -- / by 255 bc Lua wants number betwen 0.0 - 1.0 for RGBA values.  / 255 converts from normal RGB
    love.graphics.clear(40 / 255, 45 / 255, 52 / 255, 255 / 255)

    love.graphics.setFont(smallFont)
    if gameState == 'start' then
        love.graphics.printf("Hello Start State!", 0, 20, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'play' then
        love.graphics.printf("Hello Play State!", 0, 20, VIRTUAL_WIDTH, 'center')
    end

    -- Render ball
    ball:render()
    -- Render left paddle
    player1:render()
    -- Render right paddle
    player2:render()

    love.graphics.setFont(scoreFont)
    love.graphics.print(player1Score, VIRTUAL_WIDTH / 2 - 50, VIRTUAL_HEIGHT / 3)
    love.graphics.print(player2Score, VIRTUAL_WIDTH / 2 + 30, VIRTUAL_HEIGHT / 3)

    displayFPS()

    push:apply('end')
end

function displayFPS()
    love.graphics.setColor(0, 1, 0, 1)
    love.graphics.setFont(smallFont)
    love.graphics.print('FPS: ' .. tostring(love.timer.getFPS()), 40, 20)
    love.graphics.setColor(1, 1, 1, 1)
end