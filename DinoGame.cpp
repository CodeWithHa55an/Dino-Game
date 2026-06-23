#include "raylib.h"

int main()
{
    // SETUP WINDOW
    InitWindow(800, 420, "Dino Game");
    SetTargetFPS(60); // 60 frames per second (smoother)

    // DINO POSITION (where it appears on screen)
    int dinoX = 100;     // left-right position
    int dinoY = 290;     // up-down position
    int dinoWidth = 50;  // dino width
    int dinoHeight = 60; // dino height

    // DINO JUMPING (falling & jumping)
    int dinoSpeed = 0;  // how fast dino is moving up/down
    int gravity = 1;    // how fast dino falls (1 pixel per frame)
    int jumpPower = 15; // how strong the jump is

    // GROUND LOCATION
    int ground = 290; // where dino should stand

    int cactusX = 800;
    int cactusY = 300;

    int cactusWidth = 30;
    int cactusHeight = 50;

    bool gameOver = false;
    int score = 0;

    // GAME LOOP (runs forever until window closes)
    while (!WindowShouldClose())
    {
        if (!gameOver)
        {
            // ===== INPUT (check if player pressed keys) =====

            // JUMP - if player presses SPACE
            if (IsKeyPressed(KEY_SPACE))
            {
                // Only jump if dino is on ground
                if (dinoY == ground)
                {
                    dinoSpeed = -jumpPower; // minus means UP
                }
            }

            // MOVE RIGHT - if player holds RIGHT ARROW
            if (IsKeyDown(KEY_RIGHT))
            {
                dinoX = dinoX + 5; // move 5 pixels right
            }

            // MOVE LEFT - if player holds LEFT ARROW
            if (IsKeyDown(KEY_LEFT))
            {
                dinoX = dinoX - 5; // move 5 pixels left
            }

            // ===== PHYSICS (make dino fall down) =====

            // Add gravity (dino gets slower at jumping, then falls)
            dinoSpeed = dinoSpeed + gravity;

            // Move dino up or down based on speed
            dinoY = dinoY + dinoSpeed;

            // ===== COLLISION (stop dino at ground) =====

            // If dino goes below ground, stop it
            if (dinoY >= ground)
            {
                dinoY = ground; // put it on ground
                dinoSpeed = 0;  // stop movement
            }

            // Keep dino on screen (don't go off left/right)
            if (dinoX < 0)
            {
                dinoX = 0;
            }
            if (dinoX > 800 - dinoWidth)
            {
                dinoX = 800 - dinoWidth;
            }

            if (cactusX < -cactusWidth)
            {
                cactusX = 800;
                score += 1;
            }

            cactusX = cactusX - 5;
            Rectangle dino = {
                (float)dinoX,
                (float)dinoY,
                (float)dinoWidth,
                (float)dinoHeight};

            Rectangle cactus = {
                (float)cactusX,
                (float)cactusY,
                (float)cactusWidth,
                (float)cactusHeight};

            bool horizontalOverlap = cactus.x + cactus.width > dino.x && cactus.x < dino.x + dino.width;
            bool verticalOverlap = dino.y + dino.height > cactus.y && dino.y < cactus.y + cactus.height;

            if (horizontalOverlap && verticalOverlap)
            {
                gameOver = true;
                dinoSpeed = 0;
            }
        }
        else
        {
            cactusX -= 5;
            if (cactusX < -cactusWidth)
            {
                cactusX = 800;
            }
        }

        if (IsKeyPressed(KEY_R) && gameOver)
        {
            gameOver = false;
            dinoX = 100;
            dinoY = ground;
            dinoSpeed = 0;
            cactusX = 800;
            score = 0;
        }

        // ===== DRAWING (show everything on screen) =====

        BeginDrawing();

        // Clear screen white
        ClearBackground(RAYWHITE);

        // Draw ground line
        DrawLine(0, 350, 800, 350, BLACK);

        // Draw dino as black box
        DrawRectangle(dinoX, dinoY, dinoWidth, dinoHeight, BLACK);

        DrawRectangle(
            cactusX,
            cactusY,
            cactusWidth,
            cactusHeight,
            GREEN);
        // Show helpful info
        DrawText("Press SPACE to JUMP", 10, 10, 20, DARKGRAY);
        DrawText("Use LEFT RIGHT arrows to MOVE", 10, 40, 20, DARKGRAY);
        DrawText(TextFormat("Score: %d", score), 10, 70, 20, DARKGRAY);
        if (gameOver)
        {
            DrawText("GAME OVER", 280, 150, 40, RED);
            DrawText("Press R to restart", 255, 195, 25, DARKGRAY);
        }
        EndDrawing();
    }

    // Close window and exit
    CloseWindow();
    return 0;
}