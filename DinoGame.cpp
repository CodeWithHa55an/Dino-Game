#include "raylib.h"

int main()
{
    // ==================== SETUP ====================
    InitWindow(800, 420, "Dino Game");
    SetTargetFPS(60);

    // ==================== DINO VARIABLES ====================
    int dinoX = 100;
    int dinoY = 290;
    int dinoWidth = 40;
    int dinoHeight = 60;

    int dinoSpeed = 0;
    int gravity = 1;
    int jumpPower = 18;
    int ground = 290;

    // ==================== CACTUS VARIABLES ====================
    int cactusX = 800 + GetRandomValue(0, 300);
    int cactusY = 300;
    int cactusWidth = 30;
    int cactusHeight = 50;
    int cactusSpeed = 5;

    int cactus2X = 1400;
    int cactus2Y = 300;
    int cactus2Width = 30;
    int cactus2Height = 50;

    // ==================== CLOUD VARIABLES ====================
    int cloud1X = 800;
    int cloud1Y = 80;
    int cloud2X = 1100;
    int cloud2Y = 120;
    int cloud3X = 1400;
    int cloud3Y = 60;

    // ==================== DINO ANIMATION ====================
    int animationframe = 0;
    bool legforward = true;

    // ==================== BIRD VARIABLES ====================
    int birdX = 800;
    int birdY = 220;
    int birdWidth = 40;
    int birdheight = 20;
    int birdspeed = 7;
    bool birdActive = false;

    // ==================== GAME VARIABLES ====================
    bool gameStarted = false;
    bool gameOver = false;
    int score = 0;
    int highscore = 0;
    bool secondCactusActive = false;
    
    // BIRD SPAWN TRACKING - FIXED!
    int nextBirdSpawnScore = 10;  // First bird at score 10
    bool birdSpawnedAtThisScore = false;  // Prevents duplicate spawns

    // ==================== GAME LOOP ====================
    while (!WindowShouldClose())
    {
        // Start screen
        if (!gameStarted)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gameStarted = true;
            }
        }

        // Only update game if NOT game over
        if (!gameOver && gameStarted)
        {
            // ===== PLAYER INPUT =====
            if (IsKeyPressed(KEY_SPACE))
            {
                if (dinoY == ground)
                {
                    dinoSpeed = -jumpPower;
                }
            }

            if (IsKeyDown(KEY_RIGHT))
            {
                dinoX = dinoX + 5;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                dinoX = dinoX - 5;
            }

            // ===== PHYSICS =====
            dinoSpeed = dinoSpeed + gravity;
            dinoY = dinoY + dinoSpeed;

            // ===== DINO COLLISION WITH GROUND =====
            if (dinoY >= ground)
            {
                dinoY = ground;
                dinoSpeed = 0;
            }

            // ===== DINO BOUNDARIES =====
            if (dinoX < 0)
            {
                dinoX = 0;
            }
            if (dinoX > 800 - dinoWidth)
            {
                dinoX = 800 - dinoWidth;
            }

            // ===== CACTUS & BIRD MOVEMENT - ALWAYS ACTIVE =====
            cactusX = cactusX - cactusSpeed;
            cactus2X = cactus2X - cactusSpeed;
            
            if (birdActive)
            {
                birdX = birdX - birdspeed;
            }

            // ===== CACTUS 1 RESET =====
            if (cactusX < -cactusWidth)
            {
                cactusX = 800 + GetRandomValue(0, 300);
                score = score + 1;
                
                if (score > highscore)
                {
                    highscore = score;
                }
                
                if (score % 5 == 0 && cactusSpeed < 15)
                {
                    cactusSpeed++;
                }

                // Spawn second cactus at score 8
                if (score >= 8 && !secondCactusActive)
                {
                    int gap = 700 + (score / 5) * 70 + (cactusSpeed - 5) * 20;
                    cactus2X = cactusX + gap + GetRandomValue(80, 180);
                    secondCactusActive = true;
                }
            }

            // ===== CACTUS 2 RESET =====
            if (secondCactusActive && cactus2X < -cactus2Width)
            {
                int gap = 700 + (score / 5) * 70 + (cactusSpeed - 5) * 20;
                cactus2X = 900 + gap + GetRandomValue(100, 220);
                score = score + 1;
                
                if (score > highscore)
                {
                    highscore = score;
                }
            }

            // ===== BIRD RESET (When it passes off screen) =====
            if (birdActive && birdX < -birdWidth)
            {
                birdActive = false;
                score = score + 1;  // Player passed the bird
                
                if (score > highscore)
                {
                    highscore = score;
                }
            }

            // ===== SPAWN BIRD AT EXACT SCORES (10, 20, 30, 40, 50...) =====
            // FIXED: Simple loop-based spawning
            if (score >= nextBirdSpawnScore && !birdSpawnedAtThisScore && !birdActive)
            {
                // Check if cactus is far enough (spawn only when safe)
                if (cactusX > 600)  // Cactus is far away
                {
                    birdActive = true;
                    birdX = 800;  // Always spawn at same position
                    birdY = 220;  // Always spawn at same height (consistent)
                    birdSpawnedAtThisScore = true;
                }
            }

            // Move to next bird spawn score after this one is reached
            if (score > nextBirdSpawnScore && birdSpawnedAtThisScore && !birdActive)
            {
                nextBirdSpawnScore += 10;  // Next bird at +10
                birdSpawnedAtThisScore = false;  // Reset flag for next bird
            }

            // ===== COLLISION DETECTION - CACTUS 1 =====
            bool horizontalOverlap = cactusX + cactusWidth > dinoX &&
                                     cactusX < dinoX + dinoWidth;
            bool verticalOverlap = dinoY + dinoHeight > cactusY &&
                                   dinoY < cactusY + cactusHeight;

            // ===== COLLISION DETECTION - CACTUS 2 =====
            bool horizontalOverlap2 = cactus2X + cactus2Width > dinoX &&
                                      cactus2X < dinoX + dinoWidth;
            bool verticalOverlap2 = dinoY + dinoHeight > cactus2Y &&
                                    dinoY < cactus2Y + cactus2Height;

            // ===== COLLISION DETECTION - BIRD =====
            bool birdHorizontal = birdX + birdWidth > dinoX &&
                                  birdX < dinoX + dinoWidth;
            bool birdVertical = dinoY + dinoHeight > birdY &&
                                dinoY < birdY + birdheight;

            // ===== GAME OVER IF HIT ANYTHING =====
            if ((horizontalOverlap && verticalOverlap) || 
                (horizontalOverlap2 && verticalOverlap2) || 
                (birdActive && birdHorizontal && birdVertical))
            {
                gameOver = true;
                dinoSpeed = 0;
            }
        }

        // ===== RESTART LOGIC =====
        if (IsKeyPressed(KEY_R) && gameOver)
        {
            gameOver = false;
            dinoX = 100;
            dinoY = ground;
            dinoSpeed = 0;
            cactusX = 800 + GetRandomValue(0, 300);
            cactus2X = 1400;
            score = 0;
            cactusSpeed = 5;
            secondCactusActive = false;
            birdActive = false;
            birdX = 800;
            birdY = 220;
            nextBirdSpawnScore = 10;  // Reset bird spawn score
            birdSpawnedAtThisScore = false;  // Reset flag
            cloud1X = 800;
            cloud2X = 1100;
            cloud3X = 1400;
            cloud1Y = GetRandomValue(40, 150);
            cloud2Y = GetRandomValue(40, 150);
            cloud3Y = GetRandomValue(40, 150);
            gameStarted = true;
        }

        // ===== CLOUD MOVEMENT =====
        cloud1X--;
        cloud2X--;
        cloud3X--;

        if (cloud1X < -60)
        {
            cloud1X = 800;
            cloud1Y = GetRandomValue(40, 150);
        }
        if (cloud2X < -60)
        {
            cloud2X = 800;
            cloud2Y = GetRandomValue(40, 150);
        }
        if (cloud3X < -60)
        {
            cloud3X = 800;
            cloud3Y = GetRandomValue(40, 150);
        }

        // ===== DINO LEG ANIMATION =====
        if (dinoY == ground)
        {
            animationframe++;
            if (animationframe > 10)
            {
                legforward = !legforward;
                animationframe = 0;
            }
        }

        // ===== DRAWING =====
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw ground line
        DrawLine(0, 350, 800, 350, BLACK);

        // Draw clouds
        DrawCircle(cloud1X, cloud1Y, 20, LIGHTGRAY);
        DrawCircle(cloud1X + 20, cloud1Y, 20, LIGHTGRAY);
        DrawCircle(cloud1X + 40, cloud1Y, 20, LIGHTGRAY);

        DrawCircle(cloud2X, cloud2Y, 20, LIGHTGRAY);
        DrawCircle(cloud2X + 20, cloud2Y, 20, LIGHTGRAY);
        DrawCircle(cloud2X + 40, cloud2Y, 20, LIGHTGRAY);

        DrawCircle(cloud3X, cloud3Y, 20, LIGHTGRAY);
        DrawCircle(cloud3X + 20, cloud3Y, 20, LIGHTGRAY);
        DrawCircle(cloud3X + 40, cloud3Y, 20, LIGHTGRAY);

        // Draw dino
        DrawRectangle(dinoX, dinoY, 40, 60, BLACK);
        DrawRectangle(dinoX + 30, dinoY + 10, 20, 20, BLACK);
        DrawCircle(dinoX + 35, dinoY + 15, 3, WHITE);
        
        if (legforward)
        {
            DrawRectangle(dinoX + 5, dinoY + 60, 8, 15, BLACK);
            DrawRectangle(dinoX + 25, dinoY + 60, 8, 8, BLACK);
        }
        else
        {
            DrawRectangle(dinoX + 5, dinoY + 60, 8, 8, BLACK);
            DrawRectangle(dinoX + 25, dinoY + 60, 8, 15, BLACK);
        }

        // Draw cacti
        DrawRectangle(cactusX, cactusY, cactusWidth, cactusHeight, GREEN);
        DrawRectangle(cactus2X, cactus2Y, cactus2Width, cactus2Height, DARKGREEN);

        // Draw bird (only when active)
        if (birdActive)
        {
            DrawCircle(birdX, birdY, 10, BLACK);
            DrawTriangle(
                {(float)birdX - 10, (float)birdY},
                {(float)birdX - 25, (float)birdY - 10},
                {(float)birdX - 25, (float)birdY + 10},
                BLACK);
        }

        // Draw UI
        DrawText("Press SPACE to JUMP", 10, 10, 20, DARKGRAY);
        DrawText("Use LEFT RIGHT arrows to MOVE", 10, 40, 20, DARKGRAY);
        DrawText(TextFormat("Score: %d", score), 650, 20, 20, DARKGRAY);
        DrawText(TextFormat("High Score: %d", highscore), 600, 50, 20, DARKGRAY);

        // Start screen
        if (!gameStarted)
        {
            DrawText("DINO GAME", 250, 120, 50, BLACK);
            if ((GetTime() * 2) - (int)(GetTime() * 2) < 0.5)
            {
                DrawText("Press ENTER to Start", 220, 200, 30, DARKGRAY);
            }
        }

        // Game over screen
        if (gameOver)
        {
            DrawText("GAME OVER", 280, 150, 40, RED);
            DrawText("Press R to restart", 285, 195, 25, DARKGRAY);
            DrawText(TextFormat("High Score: %d", highscore), 320, 240, 25, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}