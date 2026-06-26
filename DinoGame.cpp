#include "raylib.h"

int main()
{
    // ==================== SETUP ====================
    InitWindow(800, 420, "Dino Game");
    SetTargetFPS(60);

    // Load textures from the correct Assets folder
    Texture2D birdUpTexture = LoadTexture("Assets/Bird.png");
    Texture2D birdLevel2Texture = LoadTexture("Assets/Bird_Level2.png");
    Texture2D birdDown2Texture = LoadTexture("Assets/Bird_Down2.png");
    Texture2D dinoIdleTexture = LoadTexture("Assets/Dino_Idle.png");
    Texture2D dinoRun1Texture = LoadTexture("Assets/Dino_Run.png");
    Texture2D dinoRun2Texture = LoadTexture("Assets/Dino_Run2.png");

    // ==================== DINO VARIABLES ====================
    int dinoX = 100;
    int dinoY = 290;
    int dinoWidth = 40;
    int dinoHeight = 60;

    int dinoSpeed = 0;
    int gravity = 1;
    int jumpPower = 18;
    int ground = 290;
    bool isJumping = false;
    bool isMoving = false;
    int dinoRunCounter = 0;
    int dinoRunFrame = 0;

    // ==================== CACTUS VARIABLES ====================
    int cactusX = 800 + GetRandomValue(0, 300);
    int cactusY = 295;
    int cactusWidth = 30;
    int cactusHeight = 50;
    int cactusSpeed = 5;

    int cactus2X = 1400;
    int cactus2Y = 295;
    int cactus2Width = 30;
    int cactus2Height = 50;
    bool secondCactusActive = false;

    // ==================== CLOUD VARIABLES ====================
    int cloud1X = 800;
    int cloud1Y = 80;
    int cloud2X = 1100;
    int cloud2Y = 120;
    int cloud3X = 1400;
    int cloud3Y = 60;

    // ==================== BIRD VARIABLES ====================
    int birdX = 800;
    int birdY = 220;
    int birdWidth = 40;
    int birdHeight = 20;
    int birdSpeed = 7;
    bool birdActive = false;
    int birdAnimationCounter = 0;
    int birdAnimationType = 0; // 0=up, 1=level, 2=down

    // ==================== GAME VARIABLES ====================
    bool gameStarted = false;
    bool gameOver = false;
    int score = 0;
    int highscore = 0;

    int nextBirdSpawnScore = 10;
    bool birdSpawnedAtThisScore = false;

    // ==================== GAME LOOP ====================
    while (!WindowShouldClose())
    {
        // Start screen
        if (!gameStarted)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gameStarted = true;
                dinoY = ground;
                dinoSpeed = 0;
                isJumping = false;
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
                    isJumping = true;
                }
            }

            isMoving = false;
            if (IsKeyDown(KEY_RIGHT))
            {
                dinoX = dinoX + 5;
                isMoving = true;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                dinoX = dinoX - 5;
                isMoving = true;
            }

            // ===== PHYSICS =====
            dinoSpeed = dinoSpeed + gravity;
            dinoY = dinoY + dinoSpeed;

            // ===== DINO COLLISION WITH GROUND =====
            if (dinoY >= ground)
            {
                dinoY = ground;
                dinoSpeed = 0;
                isJumping = false;
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

            // ===== DINO RUN ANIMATION =====
            if (!isJumping && isMoving)
            {
                dinoRunCounter++;
                if (dinoRunCounter > 10)
                {
                    dinoRunFrame = (dinoRunFrame + 1) % 2;
                    dinoRunCounter = 0;
                }
            }
            else
            {
                dinoRunFrame = 0;
                dinoRunCounter = 0;
            }

            // ===== CACTUS MOVEMENT =====
            cactusX = cactusX - cactusSpeed;
            cactus2X = cactus2X - cactusSpeed;

            // ===== BIRD MOVEMENT & ANIMATION =====
            if (birdActive)
            {
                birdX = birdX - birdSpeed;
                birdAnimationCounter++;
                if (birdAnimationCounter > 15)
                {
                    birdAnimationType = (birdAnimationType + 1) % 3;
                    birdAnimationCounter = 0;
                }
            }

            // ===== CACTUS 1 RESET =====
            if (cactusX < -cactusWidth)
            {
                cactusX = 800 + GetRandomValue(0, 300);
                cactusY = 295;
                cactusWidth = 30;
                cactusHeight = 50;
                score = score + 1;

                if (score > highscore)
                {
                    highscore = score;
                }

                if (score % 5 == 0 && cactusSpeed < 15)
                {
                    cactusSpeed++;
                }

                if (score >= 8 && !secondCactusActive)
                {
                    cactus2X = cactusX + GetRandomValue(200, 400);
                    secondCactusActive = true;
                }
            }

            // ===== CACTUS 2 RESET =====
            if (secondCactusActive && cactus2X < -cactus2Width)
            {
                cactus2X = 900 + GetRandomValue(100, 220);
                cactus2Y = 295;
                cactus2Width = 30;
                cactus2Height = 50;
                score = score + 1;

                if (score > highscore)
                {
                    highscore = score;
                }
            }

            // ===== BIRD RESET =====
            if (birdActive && birdX < -birdWidth)
            {
                birdActive = false;
                score = score + 1;

                if (score > highscore)
                {
                    highscore = score;
                }
            }

            // ===== SPAWN BIRD AT EXACT SCORES =====
            if (score >= nextBirdSpawnScore && !birdSpawnedAtThisScore && !birdActive)
            {
                if (cactusX > 600)
                {
                    birdActive = true;
                    birdX = 800;
                    birdY = 220;
                    birdAnimationType = 0;
                    birdAnimationCounter = 0;
                    birdSpawnedAtThisScore = true;
                }
            }

            if (score > nextBirdSpawnScore && birdSpawnedAtThisScore && !birdActive)
            {
                nextBirdSpawnScore += 10;
                birdSpawnedAtThisScore = false;
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
                                dinoY < birdY + birdHeight;

            // ===== GAME OVER =====
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
            isJumping = false;
            cactusX = 800 + GetRandomValue(0, 300);
            cactus2X = 1400;
            score = 0;
            cactusSpeed = 5;
            secondCactusActive = false;
            birdActive = false;
            birdX = 800;
            birdY = 220;
            birdAnimationType = 0;
            birdAnimationCounter = 0;
            nextBirdSpawnScore = 10;
            birdSpawnedAtThisScore = false;
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

        // ===== DRAW DINO =====
        if (isJumping)
        {
            DrawTexturePro(
                dinoIdleTexture,
                (Rectangle){0, 0, (float)dinoIdleTexture.width, (float)dinoIdleTexture.height},
                (Rectangle){(float)dinoX, (float)dinoY, 40.0f, 60.0f},
                (Vector2){0, 0},
                0.0f,
                WHITE);
        }
        else if (isMoving)
        {
            if (dinoRunFrame == 0)
            {
                DrawTexturePro(
                    dinoRun1Texture,
                    (Rectangle){0, 0, (float)dinoRun1Texture.width, (float)dinoRun1Texture.height},
                    (Rectangle){(float)dinoX, (float)dinoY, 40.0f, 60.0f},
                    (Vector2){0, 0},
                    0.0f,
                    WHITE);
            }
            else
            {
                DrawTexturePro(
                    dinoRun2Texture,
                    (Rectangle){0, 0, (float)dinoRun2Texture.width, (float)dinoRun2Texture.height},
                    (Rectangle){(float)dinoX, (float)dinoY, 40.0f, 60.0f},
                    (Vector2){0, 0},
                    0.0f,
                    WHITE);
            }
        }
        else
        {
            DrawTexturePro(
                dinoIdleTexture,
                (Rectangle){0, 0, (float)dinoIdleTexture.width, (float)dinoIdleTexture.height},
                (Rectangle){(float)dinoX, (float)dinoY, 40.0f, 60.0f},
                (Vector2){0, 0},
                0.0f,
                WHITE);
        }

        // ===== DRAW CACTUS 1 (PLACEHOLDER - Green rectangle) =====
        // TODO: Will replace with texture once images are ready
        DrawRectangle(cactusX, cactusY, cactusWidth, cactusHeight, GREEN);

        // ===== DRAW CACTUS 2 (PLACEHOLDER - Dark green rectangle) =====
        // TODO: Will replace with texture once images are ready
        DrawRectangle(cactus2X, cactus2Y, cactus2Width, cactus2Height, DARKGREEN);

        // ===== DRAW BIRD (Using textures with scaling) =====
        if (birdActive)
        {
            if (birdAnimationType == 0)
            {
                DrawTexturePro(
                    birdUpTexture,
                    (Rectangle){0, 0, (float)birdUpTexture.width, (float)birdUpTexture.height},
                    (Rectangle){(float)birdX, (float)birdY, 40.0f, 20.0f},
                    (Vector2){0, 0},
                    0.0f,
                    WHITE);
            }
            else if (birdAnimationType == 1)
            {
                DrawTexturePro(
                    birdLevel2Texture,
                    (Rectangle){0, 0, (float)birdLevel2Texture.width, (float)birdLevel2Texture.height},
                    (Rectangle){(float)birdX, (float)birdY, 40.0f, 20.0f},
                    (Vector2){0, 0},
                    0.0f,
                    WHITE);
            }
            else
            {
                DrawTexturePro(
                    birdDown2Texture,
                    (Rectangle){0, 0, (float)birdDown2Texture.width, (float)birdDown2Texture.height},
                    (Rectangle){(float)birdX, (float)birdY, 40.0f, 20.0f},
                    (Vector2){0, 0},
                    0.0f,
                    WHITE);
            }
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

    // Unload bird and dino textures
    UnloadTexture(birdUpTexture);
    UnloadTexture(birdLevel2Texture);
    UnloadTexture(birdDown2Texture);
    UnloadTexture(dinoIdleTexture);
    UnloadTexture(dinoRun1Texture);
    UnloadTexture(dinoRun2Texture);

    CloseWindow();
    return 0;
}