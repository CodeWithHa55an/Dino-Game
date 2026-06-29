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
    // Summer cactuses
    Texture2D cactusTexture = LoadTexture("Assets/Cactus.png");
    Texture2D cactusShortTexture = LoadTexture("Assets/Cactus_Short.png");
    Texture2D cactusTallTexture = LoadTexture("Assets/Cactus_Tall.png");
    Texture2D cactusVeryTallTexture = LoadTexture("Assets/Cactus_VeryTall.png");
    Texture2D dinoIdleTexture = LoadTexture("Assets/Dino_Idle.png");
    Texture2D dinoRun1Texture = LoadTexture("Assets/Dino_Run.png");
    Texture2D dinoRun2Texture = LoadTexture("Assets/Dino_Run2.png");
    // Summer
    Texture2D desertBG = LoadTexture("Assets/Summer/DesertBG1 copy.png");
    Texture2D bigCloud = LoadTexture("Assets/Summer/BigCloud.png");
    Texture2D smallCloud = LoadTexture("Assets/Summer/SmallCloud.png");
    Texture2D bigMountain = LoadTexture("Assets/Summer/BigDesertMountain.png");
    Texture2D smallMountain = LoadTexture("Assets/Summer/SmallDesertMountain.png");
    Texture2D sunTexture = LoadTexture("Assets/Summer/Sun.png");
    Texture2D moonSummer = LoadTexture("Assets/Summer/Moon.png");
    Texture2D soilGround = LoadTexture("Assets/Summer/SoilGround.png");
    Texture2D heatWave = LoadTexture("Assets/Summer/HeatWave.png");
    // Winter
    Texture2D snowBG = LoadTexture("Assets/Winter/SnowBackground.png");
    Texture2D winterCloud = LoadTexture("Assets/Winter/Cloud.png");
    Texture2D fogTexture = LoadTexture("Assets/Winter/Fog.png");
    Texture2D snowGround = LoadTexture("Assets/Winter/SnowGround.png");
    Texture2D moonWinter = LoadTexture("Assets/Winter/Moon.png");
    // Winter Cactus
    Texture2D cactusSnowTexture = LoadTexture("Assets/Winter/CactusSnowy.png");
    Texture2D cactusShortSnowTexture = LoadTexture("Assets/Winter/CactusShortSnow.png");
    Texture2D cactusTallSnowTexture = LoadTexture("Assets/Winter/CactusTallSnowy.png");
    Texture2D cactusVeryTallSnowTexture = LoadTexture("Assets/Winter/CactusVeryTallSnowy.png");
    Texture2D cactusFrostedTexture = LoadTexture("Assets/Winter/CactusFrosted.png");
    // ==================== DINO VARIABLES ====================
    int dinoX = 100;
    int dinoY = 290;
    int dinoWidth = 40;
    int dinoHeight = 60;

    int dinoSpeed = 0;
    int gravity = 1;
    int jumpPower = 18;
    int ground = 300;
    bool isJumping = false;
    bool isMoving = false;
    int dinoRunCounter = 0;
    int dinoRunFrame = 0;

    // ==================== CACTUS VARIABLES ====================
    int cactusX = 800 + GetRandomValue(0, 300);
    int cactusY = 360 - 50;
    int cactusWidth = 30;
    int cactusHeight = 50;
    int cactusType = 0;
    int cactusSpeed = 5;

    int cactus2X = 1400;
    int cactus2Y = 360 - 50;
    int cactus2Width = 30;
    int cactus2Height = 50;
    int cactus2Type = 0;
    bool secondCactusActive = false;

    auto SetCactusSize = [&](int type, int &width, int &height)
    {
        if (type == 1)
        {
            width = 30;
            height = 35;
        }
        else if (type == 2)
        {
            width = 30;
            height = 80;
        }
        else if (type == 3)
        {
            width = 30;
            height = 65;
        }
        else
        {
            width = 30;
            height = 50;
        }
    };

    // ==================== CLOUD VARIABLES ====================
    int cloud1X = 800;
    int cloud1Y = 80;
    int cloud2X = 1100;
    int cloud2Y = 120;
    int cloud3X = 1400;
    int cloud3Y = 60;

    // ==================== MOUNTAINS ====================
    float bigMountainX = 0;
    float smallMountainX = 450;

    float mountainSpeed = 1.0f;

    // ==================== BIRD VARIABLES ====================
    int birdX = 800;
    int birdY = 200;
    int birdWidth = 40;
    int birdHeight = 15;
    int birdSpeed = 7;
    bool birdActive = false;
    int birdAnimationCounter = 0;
    int birdAnimationType = 0; // 0=up, 1=level, 2=down

    // ==================== GAME VARIABLES ====================
    bool gameStarted = false;
    bool gameOver = false;
    int score = 0;
    int highscore = 0;

    int nextBirdSpawnScore = 5;
    bool birdSpawnedAtThisScore = false;

    // ==================== DAY / NIGHT ====================
    bool isNight = false;
    int nextDayNightScore = 5; // Change every 20 points

    int selectedEnvironment = 0;
    // 0 = not selected
    // 1 = Summer
    // 2 = Winter

    int summerPhase = 0;
    // 0 = Day (0–20)
    // 1 = Night (20–40)
    // 2 = Cloudy (40–60)
    // 3 = Sunny Heat (60–80)

    auto ChooseCactusType = [&](int score)
    {
        if (selectedEnvironment == 1)
        {
            if (score < 20)
                return GetRandomValue(0, 1);
            else if (score < 30)
                return GetRandomValue(0, 2);
            else
                return GetRandomValue(0, 3);
        }
        else
        {
            if (score < 20)
                return GetRandomValue(0, 2);
            else
                return GetRandomValue(0, 4);
        }
    };

    auto GetCactusTextureForType = [&](int type, bool winter)
    {
        if (winter)
        {
            if (type == 1)
                return cactusShortSnowTexture;
            if (type == 2)
                return cactusVeryTallSnowTexture;
            if (type == 3)
                return cactusTallSnowTexture;
            if (type == 4)
                return cactusFrostedTexture;
            return cactusSnowTexture;
        }

        if (type == 1)
            return cactusShortTexture;
        if (type == 2)
            return cactusVeryTallTexture;
        if (type == 3)
            return cactusTallTexture;
        return cactusTexture;
    };

    // ==================== GAME LOOP ====================
    while (!WindowShouldClose())
    {
        // Start screen
        if (!gameStarted)
        {
            if (IsKeyPressed(KEY_ONE))
            {
                selectedEnvironment = 1;
            }

            if (IsKeyPressed(KEY_TWO))
            {
                selectedEnvironment = 2;
            }
            if (IsKeyPressed(KEY_ENTER) && selectedEnvironment != 0)
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

            if (bigMountainX <= -800)
            {
                bigMountainX = 800;
            }

            if (smallMountainX <= -800)
            {
                smallMountainX = 800;
            }
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
            if (secondCactusActive)
            {
                cactus2X = cactus2X - cactusSpeed;
            }

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
                cactusType = ChooseCactusType(score);
                SetCactusSize(cactusType, cactusWidth, cactusHeight);
                cactusY = 360 - cactusHeight;
                score = score + 1;

                if (score > highscore)
                {
                    highscore = score;
                }

                if (score % 5 == 0 && cactusSpeed < 15)
                {
                    cactusSpeed++;
                }

                int spawnChance = 0;
                if (score < 10)
                    spawnChance = 20;
                else if (score < 20)
                    spawnChance = 40;
                else
                    spawnChance = 60;

                secondCactusActive = (GetRandomValue(1, 100) <= spawnChance);
                if (secondCactusActive)
                {
                    cactus2Type = ChooseCactusType(score);
                    SetCactusSize(cactus2Type, cactus2Width, cactus2Height);
                    cactus2Y = 360 - cactus2Height;
                    int gap = GetRandomValue(0, 40);
                    cactus2X = cactusX + cactusWidth + gap;
                }
                else
                {
                    cactus2X = 1400;
                }
            }

            // ===== CACTUS 2 RESET =====
            if (secondCactusActive && cactus2X < -cactus2Width)
            {
                cactus2X = 900 + GetRandomValue(100, 220);
                cactus2Type = ChooseCactusType(score);
                SetCactusSize(cactus2Type, cactus2Width, cactus2Height);
                cactus2Y = 360 - cactus2Height;
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
                nextBirdSpawnScore += 5;
                birdSpawnedAtThisScore = false;
            }

            // ===== COLLISION DETECTION - CACTUS 1 =====
            bool horizontalOverlap = cactusX + cactusWidth > dinoX &&
                                     cactusX < dinoX + dinoWidth;
            bool verticalOverlap = dinoY + dinoHeight > cactusY &&
                                   dinoY < cactusY + cactusHeight;

            // ===== COLLISION DETECTION - CACTUS 2 =====
            bool horizontalOverlap2 = false;
            bool verticalOverlap2 = false;
            if (secondCactusActive)
            {
                horizontalOverlap2 = cactus2X + cactus2Width > dinoX &&
                                     cactus2X < dinoX + dinoWidth;
                verticalOverlap2 = dinoY + dinoHeight > cactus2Y &&
                                   dinoY < cactus2Y + cactus2Height;
            }

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
            int cycleScore = score % 80;

            if (cycleScore < 20)
            {
                summerPhase = 0; // Day
            }
            else if (cycleScore < 40)
            {
                summerPhase = 1; // Night
            }
            else if (cycleScore < 60)
            {
                summerPhase = 2; // Cloudy
            }
            else
            {
                summerPhase = 3; // Heat / Sunny
            }
            // For quick testing: force night when score >= 5
            if (score >= 5)
            {
                summerPhase = 1;
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
            nextBirdSpawnScore = 5;
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
        if (selectedEnvironment == 1)
        {
            if (summerPhase == 2) // Cloudy
            {
                cloud1X -= 1;
                cloud2X -= 1;
                cloud3X -= 1;
            }
            else if (summerPhase == 3) // Hot wind
            {
                cloud1X -= 2;
                cloud2X -= 2;
                cloud3X -= 2;
            }
        }
        else if (selectedEnvironment == 2)
        {
            // Winter: gentle constant cloud drift
            cloud1X -= 1;
            cloud2X -= 1;
            cloud3X -= 1;
        }
        // ===== DRAWING =====
        BeginDrawing();
        ClearBackground(WHITE);
        Color nightBG = (Color){20, 30, 60, 120};      // strong blue tint (background feel)
        Color nightObject = (Color){80, 100, 160, 60}; // lighter tint for objects
        // ==================== DRAW ENVIRONMENT ====================
        if (selectedEnvironment == 1)
        {
            // BACKGROUND tint system (we will enhance it)
            Color skyTint = WHITE;

            if (summerPhase == 1)
                skyTint = (Color){60, 60, 100, 255}; // night
            else if (summerPhase == 2)
                skyTint = (Color){180, 180, 180, 255}; // cloudy
            else if (summerPhase == 3)
                skyTint = (Color){255, 240, 180, 255}; // hot sun

            DrawTexturePro(
                desertBG,
                (Rectangle){0, 0, (float)desertBG.width, (float)desertBG.height},
                (Rectangle){0, 0, 800, 420},
                (Vector2){0, 0},
                0,
                skyTint);

            // 🌞 SUN / 🌙 MOON SWITCH
            if (summerPhase == 1)
            {
                // MOON
                DrawTexturePro(
                    moonSummer,
                    (Rectangle){0, 0, (float)moonSummer.width, (float)moonSummer.height},
                    (Rectangle){650, 50, 70, 70},
                    (Vector2){0, 0},
                    0,
                    WHITE);
            }
            else
            {
                // SUN
                DrawTexturePro(
                    sunTexture,
                    (Rectangle){0, 0, (float)sunTexture.width, (float)sunTexture.height},
                    (Rectangle){650, 50, 80, 80},
                    (Vector2){0, 0},
                    0,
                    WHITE);

                // 🌞 Glow effect (only day + heat)
                if (summerPhase == 0 || summerPhase == 3)
                {
                    DrawCircle(690, 90, 60, Fade(YELLOW, 0.15f));
                    DrawCircle(690, 90, 40, Fade(YELLOW, 0.25f));
                    DrawCircle(690, 90, 25, Fade(YELLOW, 0.35f));
                }
            }
        }
        else if (selectedEnvironment == 2)
        {
            DrawTexturePro(
                snowBG,
                (Rectangle){0, 0, (float)snowBG.width, (float)snowBG.height},
                (Rectangle){0, 0, 800, 420},
                (Vector2){0, 0},
                0,
                WHITE);
        }
        // ===== DRAW GROUND =====
        if (selectedEnvironment == 1)
        {
            Color groundTint = WHITE;

            if (summerPhase == 1)
            {
                // slightly dark blue
                groundTint = (Color){100, 110, 140, 255};
            }

            DrawTexturePro(
                soilGround,
                (Rectangle){0, 0, (float)soilGround.width, (float)soilGround.height},
                (Rectangle){0, 340, 800, 80},
                (Vector2){0, 0},
                0,
                groundTint);
        }
        else if (selectedEnvironment == 2)
        {
            DrawTexturePro(
                snowGround,
                (Rectangle){0, 0, (float)snowGround.width, (float)snowGround.height},
                (Rectangle){0, 340, 800, 80},
                (Vector2){0, 0},
                0,
                WHITE);
        }

        // Draw ground line
        Color groundColor = isNight ? WHITE : BLACK;

        // Draw clouds
        if (selectedEnvironment == 2)
        {
            DrawCircle(cloud1X, cloud1Y, 20, LIGHTGRAY);
            DrawCircle(cloud1X + 20, cloud1Y, 20, LIGHTGRAY);
            DrawCircle(cloud1X + 40, cloud1Y, 20, LIGHTGRAY);

            DrawCircle(cloud2X, cloud2Y, 20, LIGHTGRAY);
            DrawCircle(cloud2X + 20, cloud2Y, 20, LIGHTGRAY);
            DrawCircle(cloud2X + 40, cloud2Y, 20, LIGHTGRAY);

            DrawCircle(cloud3X, cloud3Y, 20, LIGHTGRAY);
            DrawCircle(cloud3X + 20, cloud3Y, 20, LIGHTGRAY);
            DrawCircle(cloud3X + 40, cloud3Y, 20, LIGHTGRAY);
        }
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
        if (summerPhase == 1)
        {
            // torch stick
            DrawRectangle(
                dinoX + 32,
                dinoY + 20,
                3,
                15,
                BROWN);

            // flame
            DrawCircle(
                dinoX + 33,
                dinoY + 18,
                4,
                ORANGE);

            DrawCircle(
                dinoX + 33,
                dinoY + 18,
                2,
                YELLOW);
        }
        if (summerPhase == 1)
        {
            DrawCircle(
                dinoX + 33,
                dinoY + 18,
                90,
                Fade(YELLOW, 0.01f));

            DrawCircle(
                dinoX + 33,
                dinoY + 18,
                60,
                Fade(ORANGE, 0.02f));

            DrawCircle(
                dinoX + 33,
                dinoY + 18,
                35,
                Fade(YELLOW, 0.03f));
        }
        // ===== DRAW CACTUS 1 =====
        Texture2D cactus1Texture = GetCactusTextureForType(cactusType, selectedEnvironment == 2);
        if (summerPhase == 1)
        {
            // Soft green glow (behind cactus)
            DrawCircle(
                cactusX + cactusWidth / 2,
                cactusY + cactusHeight / 2,
                cactusWidth + 6,
                Fade(GREEN, 0.05f));

            DrawCircle(
                cactusX + cactusWidth / 2,
                cactusY + cactusHeight / 2,
                cactusWidth + 2,
                Fade(LIME, 0.08f));
        }

        DrawTexturePro(
            cactus1Texture,
            (Rectangle){0, 0, (float)cactus1Texture.width, (float)cactus1Texture.height},
            (Rectangle){(float)cactusX, (float)cactusY, (float)cactusWidth, (float)cactusHeight},
            (Vector2){0, 0},
            0,
            (summerPhase == 1) ? (Color){180, 255, 180, 255}
                               : WHITE);

        if (secondCactusActive)
        {
            Texture2D cactus2TextureToDraw = GetCactusTextureForType(cactus2Type, selectedEnvironment == 2);
            if (summerPhase == 1)
            {
                DrawCircle(
                    cactus2X + cactus2Width / 2,
                    cactus2Y + cactus2Height / 2,
                    cactus2Width + 6,
                    Fade(GREEN, 0.05f));

                DrawCircle(
                    cactus2X + cactus2Width / 2,
                    cactus2Y + cactus2Height / 2,
                    cactus2Width + 2,
                    Fade(LIME, 0.08f));
            }
            DrawTexturePro(
                cactus2TextureToDraw,
                (Rectangle){0, 0, (float)cactus2TextureToDraw.width, (float)cactus2TextureToDraw.height},
                (Rectangle){(float)cactus2X, (float)cactus2Y, (float)cactus2Width, (float)cactus2Height},
                (Vector2){0, 0},
                0.0f,
                (summerPhase == 1) ? (Color){180, 255, 180, 255} : WHITE);
        }

        // ===== DRAW BIRD (Using textures with scaling) =====
        if (birdActive && summerPhase == 1)
        {
            DrawCircle(
                birdX + 20,
                birdY + 10,
                18,
                Fade(WHITE, 0.12f));
        }
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
                    (summerPhase == 1) ? (Color){190, 210, 255, 255}
                                       : WHITE);
            }
            else if (birdAnimationType == 1)
            {
                DrawTexturePro(
                    birdLevel2Texture,
                    (Rectangle){0, 0, (float)birdLevel2Texture.width, (float)birdLevel2Texture.height},
                    (Rectangle){(float)birdX, (float)birdY, 40.0f, 20.0f},
                    (Vector2){0, 0},
                    0.0f,
                    (summerPhase == 1) ? (Color){190, 210, 255, 255}
                                       : WHITE);
            }
            else
            {
                DrawTexturePro(
                    birdDown2Texture,
                    (Rectangle){0, 0, (float)birdDown2Texture.width, (float)birdDown2Texture.height},
                    (Rectangle){(float)birdX, (float)birdY, 40.0f, 20.0f},
                    (Vector2){0, 0},
                    0.0f,
                    (summerPhase == 1) ? (Color){190, 210, 255, 255}
                                       : WHITE);
            }
        }

        // Draw UI
        Color textColor = DARKGRAY;

        if (selectedEnvironment == 1)
        {
            if (summerPhase == 1)
                textColor = WHITE;
        }
        DrawText("Press SPACE to JUMP", 10, 10, 20, textColor);
        DrawText("Use LEFT RIGHT arrows to MOVE", 10, 40, 20, textColor);
        DrawText(TextFormat("Score: %d", score), 650, 20, 20, textColor);
        DrawText(TextFormat("High Score: %d", highscore), 600, 50, 20, textColor);

        // Start screen
        if (!gameStarted)
        {
            DrawText("DINO GAME", 260, 70, 45, BLACK);

            DrawText("Select Environment", 240, 140, 30, DARKGRAY);

            Color summerColor = BLACK;
            Color winterColor = BLACK;

            if (selectedEnvironment == 1)
                summerColor = GREEN;

            if (selectedEnvironment == 2)
                winterColor = BLUE;

            DrawText("Press 1 : Summer", 250, 190, 28, summerColor);
            DrawText("Press 2 : Winter", 250, 230, 28, winterColor);

            DrawText("Press ENTER to Start", 210, 310, 30, DARKGRAY);
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

    // Unload bird, cactus, and dino textures
    UnloadTexture(birdUpTexture);
    UnloadTexture(birdLevel2Texture);
    UnloadTexture(birdDown2Texture);
    UnloadTexture(cactusTexture);
    UnloadTexture(cactusShortTexture);
    UnloadTexture(cactusTallTexture);
    UnloadTexture(cactusVeryTallTexture);
    UnloadTexture(dinoIdleTexture);
    UnloadTexture(dinoRun1Texture);
    UnloadTexture(dinoRun2Texture);
    UnloadTexture(desertBG);
    UnloadTexture(snowBG);
    UnloadTexture(cactusSnowTexture);
    UnloadTexture(cactusShortSnowTexture);
    UnloadTexture(cactusTallSnowTexture);
    UnloadTexture(cactusVeryTallSnowTexture);
    UnloadTexture(cactusFrostedTexture);

    CloseWindow();
    return 0;
}
