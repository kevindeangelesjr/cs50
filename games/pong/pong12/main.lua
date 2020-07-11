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

    victoryFont = love.graphics.newFont('font.ttf', 24)

    -- Table of audio objects
    sounds = {
        ['paddle_hit'] = love.audio.newSource('sounds/paddle_hit.wav', 'static'),
        ['point_scored'] = love.audio.newSource('sounds/score.wav', 'static'),
        ['wall_hit'] = love.audio.newSource('sounds/wall_hit.wav', 'static')
    }

    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        vsync = true,
        resizable = true
    })

    player1Score = 0
    player2Score = 0
    
    servingPlayer = math.random(2) == 1 and 1 or 2

    winningPlayer = 0

    -- Construct Paddles
    player1 = Paddle(5, 20, 5, 20)
    player2 = Paddle(VIRTUAL_WIDTH - 10, VIRTUAL_HEIGHT - 30, 5, 20)

    -- Construct ball
    ball = Ball(VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 5, 5)

    if servingPlayer == 1 then
        ball.dx = 100
    else
        ball.dx = -100
    end

    gameState = 'start'
end

function love.resize(w, h)
    push:resize(w, h)
end

function love.update(dt)

    if gameState == 'play' then

        if ball.x <= 0 then
            player2Score = player2Score + 1
            
            sounds['point_scored']:play()

            servingPlayer = 1
            ball:reset()
            ball.dx = 100

            if player2Score >= 3 then
                gameState = 'victory'
                winningPlayer = 2
            else
                gameState = 'serve'
            end
        end

        if ball.x >= VIRTUAL_WIDTH - 4 then
            player1Score = player1Score + 1

            sounds['point_scored']:play()

            servingPlayer = 2
            ball:reset()
            ball.dx = -100

            if player1Score >= 3 then
                gameState = 'victory'
                winningPlayer = 1
            else
                gameState = 'serve'
            end
        end

        -- collision detection
        if ball:collides(player1) then
            sounds['paddle_hit']:play()

            -- deflect ball to the right
            ball.dx = -ball.dx
        end

        if ball:collides(player2) then
            sounds['paddle_hit']:play()

            -- deflect ball to the left
            ball.dx = -ball.dx
        end

        if ball.y <= 0 then
            sounds['wall_hit']:play()

            -- deflect the ball down
            ball.dy = -ball.dy
            ball.y = 0
        end

        if ball.y >= VIRTUAL_HEIGHT - 4 then
            sounds['wall_hit']:play()

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
        ball:update(dt)
    
    end
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    elseif key == 'enter' or key == 'return' then
        if gameState == 'start' then
            gameState = 'serve'
        elseif gameState == 'victory' then
            gameState = 'start'
            player1Score = 0
            player2Score = 0
        elseif gameState == 'serve' then
            gameState = 'play'
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
        love.graphics.printf("Welcome to Pong!", 0, 20, VIRTUAL_WIDTH, 'center')
        love.graphics.printf("Press Enter to Play!", 0, 32, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'serve' then
        love.graphics.printf("Player " .. tostring(servingPlayer) .. "'s turn!", 0, 20, VIRTUAL_WIDTH, 'center')
        love.graphics.printf("Press Enter to Serve!", 0, 32, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'victory' then
        love.graphics.setFont(victoryFont)
        love.graphics.printf("Player " .. tostring(winningPlayer) .. " wins!", 0, 10, VIRTUAL_WIDTH, 'center')
        love.graphics.setFont(smallFont)
        love.graphics.printf("Press Enter to Play Again!", 0, 42, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'play' then

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