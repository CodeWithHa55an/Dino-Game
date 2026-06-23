#include "raylib.h"

int main()
{
    // ==================== SETUP ====================
    // Create window and set frame rate
    InitWindow(800, 420, "Dino Game");
    SetTargetFPS(60); // 60 frames per second (smooth gameplay)

    // ==================== DINO VARIABLES ====================
    // Position on screen
    int dinoX = 100;     // How far from LEFT edge
    int dinoY = 290;     // How far from TOP edge
    int dinoWidth = 50;  // How wide is dino
    int dinoHeight = 60; // How tall is dino

    // Physics
    int dinoSpeed = 0;  // Speed going up/down (- = up, + = down)
    int gravity = 1;    // How much dino gets pulled down each frame
    int jumpPower = 15; // How strong the jump is
    int ground = 290;   // Y position where dino stands

    // ==================== CACTUS VARIABLES ====================
    // Position on screen
    int cactusX = 800;     // Start at right side of screen
    int cactusY = 300;     // How far from TOP
    int cactusWidth = 30;  // How wide
    int cactusHeight = 50; // How tall
    int cactusSpeed = 5;   // How fast it moves left (same as dinoX movement)

    // ==================== GAME VARIABLES ====================
    bool gameOver = false; // Is game finished?
    int score = 0;         // How many obstacles passed?

    // ==================== GAME LOOP ====================
    // This runs 60 times per second (because SetTargetFPS(60))
    while (!WindowShouldClose())
    {
        // Only update game if NOT game over
        if (!gameOver)
        {
            // ===== PLAYER INPUT (What player does) =====

            // JUMP - Check if player pressed SPACE
            if (IsKeyPressed(KEY_SPACE))
            {
                // Only allow jump if dino is on ground
                if (dinoY == ground)
                {
                    dinoSpeed = -jumpPower; // Negative = move UP
                }
            }

            // MOVE RIGHT - Check if player HOLDS right arrow
            if (IsKeyDown(KEY_RIGHT))
            {
                dinoX = dinoX + 5; // Add 5 pixels to X position
            }

            // MOVE LEFT - Check if player HOLDS left arrow
            if (IsKeyDown(KEY_LEFT))
            {
                dinoX = dinoX - 5; // Subtract 5 pixels from X position
            }

            // ===== PHYSICS (How dino moves) =====

            // Gravity: Make dino fall (add 1 pixel of downward speed each frame)
            dinoSpeed = dinoSpeed + gravity;

            // Apply speed: Actually move dino up or down
            dinoY = dinoY + dinoSpeed;

            // ===== DINO COLLISION WITH GROUND =====

            // If dino went too low, put it back on ground
            if (dinoY >= ground)
            {
                dinoY = ground; // Exactly on ground
                dinoSpeed = 0;  // Stop moving
            }

            // ===== DINO BOUNDARIES (Don't go off-screen) =====

            // Don't go off LEFT side
            if (dinoX < 0)
            {
                dinoX = 0; // Stop at left edge
            }

            // Don't go off RIGHT side
            if (dinoX > 800 - dinoWidth)
            {
                dinoX = 800 - dinoWidth; // Stop at right edge
            }

            // ===== CACTUS MOVEMENT =====

            // Move cactus LEFT (coming toward dino)
            cactusX = cactusX - cactusSpeed;

            // If cactus goes off LEFT side, bring it back from RIGHT
            if (cactusX < -cactusWidth)
            {
                cactusX = 800;     // Reset to right side
                score = score + 1; // Player avoided it, increase score
                if (score % 5 == 0 && cactusSpeed < 15)
                {
                    cactusSpeed++;
                }
            }

            // ===== COLLISION DETECTION (Did dino hit cactus?) =====

            // Check if dino and cactus are overlapping
            // Horizontal overlap: Is cactus horizontally touching dino?
            bool horizontalOverlap = cactusX + cactusWidth > dinoX &&
                                     cactusX < dinoX + dinoWidth;

            // Vertical overlap: Is cactus vertically touching dino?
            bool verticalOverlap = dinoY + dinoHeight > cactusY &&
                                   dinoY < cactusY + cactusHeight;

            // If BOTH horizontal AND vertical overlap = COLLISION
            if (horizontalOverlap && verticalOverlap)
            {
                gameOver = true; // End the game
                dinoSpeed = 0;   // Stop dino movement
            }
        }

        // ===== RESTART LOGIC =====

        // If game over AND player presses R, restart
        if (IsKeyPressed(KEY_R) && gameOver)
        {
            // Reset all variables to starting position
            gameOver = false;
            dinoX = 100;
            dinoY = ground;
            dinoSpeed = 0;
            cactusX = 800;
            score = 0;
        }

        // ===== DRAWING (Show everything on screen) =====

        BeginDrawing(); // Start drawing frame

        // Clear screen (make it white)
        ClearBackground(RAYWHITE);

        // Draw ground line
        DrawLine(0, 350, 800, 350, BLACK);

        // Draw dino as a BLACK rectangle
        DrawRectangle(dinoX, dinoY, dinoWidth, dinoHeight, BLACK);

        // Draw cactus as a GREEN rectangle
        DrawRectangle(cactusX, cactusY, cactusWidth, cactusHeight, GREEN);

        // Draw instructions
        DrawText("Press SPACE to JUMP", 10, 10, 20, DARKGRAY);
        DrawText("Use LEFT RIGHT arrows to MOVE", 10, 40, 20, DARKGRAY);

        // Draw current score
        DrawText(TextFormat("Score: %d", score), 10, 70, 20, DARKGRAY);

        // If game is over, show game over screen
        if (gameOver)
        {
            DrawText("GAME OVER", 280, 150, 40, RED);
            DrawText("Press R to restart", 255, 195, 25, DARKGRAY);
        }

        EndDrawing(); // Finish drawing frame
    }

    // Close window when player exits
    CloseWindow();
    return 0;
}