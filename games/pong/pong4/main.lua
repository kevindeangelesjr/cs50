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

    -- Paddles
    player1Score = 0
    player2Score = 0

    player1Y = 30
    player2Y = VIRTUAL_HEIGHT - 40

    -- Ball 
    ballX = VIRTUAL_WIDTH / 2 - 2
    ballY = VIRTUAL_HEIGHT / 2 - 2

    -- Ball velocity
    ballDX = math.random(2) == 1 and -100 or 100
    ballDY = math.random(-50, 50)

    gameState = 'start'
end

function love.update(dt)
    -- PLayer 1 paddle
    if love.keyboard.isDown('w') then
        player1Y = math.max(0, player1Y - PADDLE_SPEED * dt)
    elseif love.keyboard.isDown('s') then
        player1Y = math.min(VIRTUAL_HEIGHT - 20, player1Y + PADDLE_SPEED * dt)
    end

    -- Player 2 paddle
    if love.keyboard.isDown('up') then
        player2Y = math.max(0, player2Y - PADDLE_SPEED * dt)
    elseif love.keyboard.isDown('down') then
        player2Y = math.min(VIRTUAL_HEIGHT - 20, player2Y + PADDLE_SPEED * dt)
    end

    if gameState == 'play' then
        ballX = ballX + ballDX *dt
        ballY = ballY + ballDY *dt
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

            -- Set ball back to default values
            ballX = VIRTUAL_WIDTH / 2 - 2
            ballY = VIRTUAL_HEIGHT / 2 - 2
            ballDX = math.random(2) == 1 and -100 or 100
            ballDY = math.random(-50, 50)
        end
    end
end

function love.draw()
    push:apply('start')

    -- Set screen (fill) color.  Draw this before drawing anything else
    -- / by 255 bc Lua wants number betwen 0.0 - 1.0 for RGBA values.  / 255 converts from normal RGB
    love.graphics.clear(40 / 255, 45 / 255, 52 / 255, 255 / 255)

    -- Draw the ball, 5 x 5 pixels
    love.graphics.rectangle('fill', ballX, ballY, 4, 4)

    -- Draw left paddle
    love.graphics.rectangle('fill', 5, player1Y, 5, 20)

    -- Draw right paddle
    love.graphics.rectangle('fill', VIRTUAL_WIDTH - 10, player2Y, 5, 20)

    love.graphics.setFont(smallFont)
    if gameState == 'start' then
        love.graphics.printf("Hello Start State!", 0, 20, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'play' then
        love.graphics.printf("Hello Play State!", 0, 20, VIRTUAL_WIDTH, 'center')
    end

    love.graphics.setFont(scoreFont)
    love.graphics.print(player1Score, VIRTUAL_WIDTH / 2 - 50, VIRTUAL_HEIGHT / 3)
    love.graphics.print(player2Score, VIRTUAL_WIDTH / 2 + 30, VIRTUAL_HEIGHT / 3)

    push:apply('end')
end