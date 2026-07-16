

#include "raylib.h"
#include <cmath>


struct RainDrop
{
    float x;
    float y;
    float speed;
};
int main()
{
    const int screenWidth = 800;
    const int screenHeight = 420;
    // ==================== SETUP ====================
    InitWindow(screenWidth, screenHeight, "Dino Game");
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
    Texture2D dinoJump = LoadTexture("Assets/Dino_Jump.png");
    Texture2D dinoCrouchTexture = LoadTexture("Assets/Dino_Crouch.png");
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
    Texture2D rainycloud = LoadTexture("Assets/Summer/RainyCloud.png");
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
    //Menu
     Texture2D menu = LoadTexture("Assets/Menu.png");
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
    const int rainCloudCount = 18;

    float rainCloudX[rainCloudCount];
    float rainCloudY[rainCloudCount];
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
    int nextBirdSpawnScore = 9999;
    bool birdSpawnedAtThisScore = false;
    // Rain
    const int rainCount = 80;
    RainDrop rain[rainCount];

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
    bool isCrouching = false;
    float cloudAlpha = 0.0f;

    bool cloudEntering = false;
    bool cloudLeaving = false;
    float leftCloudOffset = -500.0f;
    float rightCloudOffset = 800.0f;
    float cloudFade = 0.0f;

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
    for (int i = 0; i < rainCloudCount; i++)
    {
        rainCloudX[i] = (i % 6) * 140 - 30;
        rainCloudY[i] = 20 + (i / 6) * 45;
    }
    for (int i = 0; i < rainCount; i++)
    {
        rain[i].x = GetRandomValue(0, screenWidth);
        rain[i].y = GetRandomValue(110, screenHeight);

        // All drops have similar speed (more realistic)
        rain[i].speed = GetRandomValue(12, 18);
    }
    float sunX = 750;
    float moonX = 850;
    float sunY = 30;
    float moonY = 50;
    float sunMoveProgress = 0.0f;
    float moonMoveProgress = 0.0f;
    int lastCyclePhase = 0;

    auto LerpColor = [](Color a, Color b, float t) -> Color
    {
        t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);
        return (Color){
            (unsigned char)(a.r + (b.r - a.r) * t),
            (unsigned char)(a.g + (b.g - a.g) * t),
            (unsigned char)(a.b + (b.b - a.b) * t),
            (unsigned char)(a.a + (b.a - a.a) * t)};
    };

    int lastWeatherPhase = 0;
    bool weatherTransitionActive = false;
    float weatherTransitionProgress = 1.0f;
    int weatherTransitionFromPhase = 0;
    int weatherTransitionToPhase = 0;
    float weatherTransitionDuration = 1.2f;

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
        if (gameStarted && IsKeyDown(KEY_DOWN) && !isJumping)
        {
            isCrouching = true;
        }
        else
        {
            isCrouching = false;
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

            if (summerPhase == 3 || summerPhase == 4) // Rain phases
            {
                for (int i = 0; i < rainCount; i++)
                {
                    // Fall down
                    rain[i].y += rain[i].speed * 0.7f;

                    // Slight wind towards left
                    rain[i].x -= 0.8f;
                    if (rain[i].x < -50)
                    {
                        rain[i].x = screenWidth + 50;
                    }

                    // Respawn when drop leaves screen
                    if (rain[i].y > screenHeight)
                    {
                        rain[i].y = GetRandomValue(95, 150);
                        rain[i].x = GetRandomValue(-100, screenWidth + 100);
                    }
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

                if (score % 10 == 0 && score != 0 && cactusSpeed < 15)
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

                // Spawn cactus 2 only if there isn't already one on screen
                if (!secondCactusActive)
                {
                    secondCactusActive = (GetRandomValue(1, 100) <= spawnChance);

                    if (secondCactusActive)
                    {
                        cactus2Type = ChooseCactusType(score);
                        SetCactusSize(cactus2Type, cactus2Width, cactus2Height);
                        cactus2Y = 360 - cactus2Height;

                        int gap = GetRandomValue(0, 40);

                        cactus2X = cactusX + cactusWidth + gap;
                    }
                }
            }

            // ===== CACTUS 2 RESET =====
            if (secondCactusActive && cactus2X < -cactus2Width)
            {
                secondCactusActive = false;
                cactus2X = 1400;
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
                    birdActive = false;
                    birdX = 800;
                    birdY = 220;
                    birdAnimationType = 0;
                    birdAnimationCounter = 0;
                    birdSpawnedAtThisScore = true;
                }
            }

            if (score > nextBirdSpawnScore && birdSpawnedAtThisScore && !birdActive)
            {
                nextBirdSpawnScore += 9999;
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

            // ===== CLOUD MOVEMENT =====
            if (selectedEnvironment == 1)
            {
                if (summerPhase == 3 || summerPhase == 4) // Rain phases only
                {
                    cloud1X -= 1;
                    cloud2X -= 1;
                    cloud3X -= 1;
                }
            }
            else if (selectedEnvironment == 2)
            {
                // Winter: gentle constant cloud drift
                cloud1X -= 1;
                cloud2X -= 1;
                cloud3X -= 1;
            }
            // ===== WEATHER & CELESTIAL PHASE LOGIC =====
            float dt = GetFrameTime();
            int cycleScore = score % 100;
            if (score == 0)
                cycleScore = 0;
            else if (cycleScore == 0)
                cycleScore = 100;

            // Determine weather phase based on user schedule:
            // 0-20: Day, 21-40: Night, 41-60: Day, 61-80: Day Rain, 81-90: Rain Night, 91-100: Night
            int weatherPhase;
            if (cycleScore <= 20)
                weatherPhase = 0; // Day
            else if (cycleScore <= 40)
                weatherPhase = 1; // Night
            else if (cycleScore <= 60)
                weatherPhase = 2; // Day
            else if (cycleScore <= 80)
                weatherPhase = 3; // Day Rain
            else if (cycleScore <= 88)
                weatherPhase = 4; // Rain Night
            else
                weatherPhase = 5; // Night
                                  // Cloud Enter Animation
            static bool cloudsEnteredThisCycle = false;
            if (cycleScore == 59 && !cloudsEnteredThisCycle)
            {
                cloudEntering = true;
                cloudLeaving = false;
                cloudsEnteredThisCycle = true;
            }

            if (cycleScore <= 20)
            {
                cloudsEnteredThisCycle = false;
            }

            // Cloud Leave Animation
            static bool cloudsLeftThisCycle = false;

            if (cycleScore >= 88 && cycleScore <= 89 && !cloudsLeftThisCycle)
            {
                cloudLeaving = true;
                cloudEntering = false;
                cloudsLeftThisCycle = true;
            }

            if (cycleScore <= 20)
            {
                cloudsLeftThisCycle = false;
            }

            // Update summerPhase for drawing
            summerPhase = weatherPhase;

            // ===== WEATHER TRANSITION DETECTION =====
            // Trigger transition whenever weather phase changes
            if (weatherPhase != lastWeatherPhase)
            {
                weatherTransitionActive = true;
                weatherTransitionProgress = 0.0f;
                weatherTransitionFromPhase = lastWeatherPhase;
                weatherTransitionToPhase = weatherPhase;
            }

            // Update lastWeatherPhase at end of game update
            lastWeatherPhase = weatherPhase;

            // ===== WEATHER TRANSITION ANIMATION =====
            if (weatherTransitionActive)
            {
                weatherTransitionProgress += dt / weatherTransitionDuration;
                if (weatherTransitionProgress >= 1.0f)
                {
                    weatherTransitionProgress = 1.0f;
                    weatherTransitionActive = false;
                }
            }

            // Determine celestial phase (which body moves)
            int celestialPhase;
            if (cycleScore <= 20)
                celestialPhase = 1; // Sun 0-20
            else if (cycleScore <= 40)
                celestialPhase = 2; // Moon 21-40
            else if (cycleScore <= 80)
                celestialPhase = 3; // Sun 41-80 (merged, continuous motion)
            else
                celestialPhase = 4; // Moon 81-100

            // Reset progress on phase transition
            if (celestialPhase != lastCyclePhase)
            {
                lastCyclePhase = celestialPhase;
                sunMoveProgress = 0.0f;
                moonMoveProgress = 0.0f;
                // Set starting positions
                if (celestialPhase == 1)
                    sunX = 750; // Sun starts at 750 for 0-20
                else if (celestialPhase == 2)
                    moonX = 850;
                else if (celestialPhase == 3)
                    sunX = 750; // Sun starts at 750 for 41-80 (merged)
                else if (celestialPhase == 4)
                    moonX = 850;
            }

            // Phase durations: 60pts for 20-score, 120pts for 40-score
            float phaseDuration = 60.0f;

            if (celestialPhase == 2) // Moon 21-40
                phaseDuration = 49.0f;
            else if (celestialPhase == 3) // Sun 41-80 (40 points, merged)
                phaseDuration = 100.0f;
            else if (celestialPhase == 4) // Moon 81-100
                phaseDuration = 28.0f;

            // Animate celestial bodies
            if (celestialPhase == 1) // Sun 0-20
            {
                float nextProgress = sunMoveProgress + dt / phaseDuration;
                sunMoveProgress = (nextProgress < 1.0f) ? nextProgress : 1.0f;
                sunX = 750 - sunMoveProgress * 830; // from 750 to -80
            }
            else if (celestialPhase == 2) // Moon 21-40
            {
                float nextProgress = moonMoveProgress + dt / phaseDuration;
                moonMoveProgress = (nextProgress < 1.0f) ? nextProgress : 1.0f;
                moonX = 750 - moonMoveProgress * 930; // from 850 to -80
            }
            else if (celestialPhase == 3) // Sun 41-80 (merged, continuous)
            {
                float nextProgress = sunMoveProgress + dt / phaseDuration;
                sunMoveProgress = (nextProgress < 1.0f) ? nextProgress : 1.0f;
                sunX = 750 - sunMoveProgress * 830; // from 750 to -80
            }
            else // celestialPhase == 4 // Moon 81-100
            {
                float nextProgress = moonMoveProgress + dt / phaseDuration;
                moonMoveProgress = (nextProgress < 1.0f) ? nextProgress : 1.0f;
                moonX = 750 - moonMoveProgress * 930; // from 850 to -80
            }
        }

        // ===== RESTART LOGIC (outside game update) =====
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
            nextBirdSpawnScore = 15;
            birdSpawnedAtThisScore = false;
            cloud1X = 800;
            cloud2X = 1100;
            cloud3X = 1400;
            cloud1Y = GetRandomValue(40, 150);
            cloud2Y = GetRandomValue(40, 150);
            cloud3Y = GetRandomValue(40, 150);
            sunMoveProgress = 0.0f;
            moonMoveProgress = 0.0f;
            lastCyclePhase = 0;
            sunX = 850;
            moonX = 850;
            gameStarted = true;
        }

        // ===== DRAWING =====
        int cycleScore = score % 100;
        if (score == 0)
            cycleScore = 0;
        else if (cycleScore == 0)
            cycleScore = 100;

        bool glowAndStickPhase = (cycleScore >= 21 && cycleScore <= 40) || (cycleScore > 80);
        // ---------- Clouds Enter ----------
        if (gameStarted && cloudEntering)
        {
            if (leftCloudOffset < 0)
                leftCloudOffset += 6.0f;

            if (rightCloudOffset > 250)
                rightCloudOffset -= 6.0f;

            if (cloudAlpha < 1.0f)
                cloudAlpha += 0.02f;

            if (leftCloudOffset >= 0 && rightCloudOffset <= 250)
            {
                leftCloudOffset = 0;
                rightCloudOffset = 250;
                cloudAlpha = 1.0f;
                cloudEntering = false;
            }
        }

        // ---------- Clouds Leave ----------
        if (gameStarted && cloudLeaving)
        {
            if (leftCloudOffset > -500)
                leftCloudOffset -= 6.0f;

            if (rightCloudOffset < 800)
                rightCloudOffset += 6.0f;

            if (cloudAlpha > 0.0f)
                cloudAlpha -= 0.02f;

            if (leftCloudOffset <= -500 && rightCloudOffset >= 800)
            {
                leftCloudOffset = -500;
                rightCloudOffset = 800;
                cloudAlpha = 0.0f;
                cloudLeaving = false;
            }
        }
        BeginDrawing();
        if (!gameStarted)
        {
            ClearBackground(BLACK);

            // Scale to fit maintaining aspect ratio (1419x736 -> 800x420)
            float scale = fminf((float)screenWidth / menu.width, (float)screenHeight / menu.height);
            float destWidth = menu.width * scale;
            float destHeight = menu.height * scale;
            float destX = (screenWidth - destWidth) / 2.0f;
            float destY = (screenHeight - destHeight) / 2.0f;

            // Draw scaled menu background
            DrawTexturePro(menu, 
                           (Rectangle){ 0.0f, 0.0f, (float)menu.width, (float)menu.height }, 
                           (Rectangle){ destX, destY, destWidth, destHeight }, 
                           (Vector2){ 0.0f, 0.0f }, 
                           0.0f, 
                           WHITE);

            // Pulse animation timer
            static float pulseTimer = 0.0f;
            pulseTimer += GetFrameTime() * 4.0f;
            float pulse = (sinf(pulseTimer) + 1.0f) / 2.0f; // 0.0f to 1.0f

            // Update scale micro-animations
            static float summerScale = 1.0f;
            static float winterScale = 1.0f;
            float targetSummerScale = (selectedEnvironment == 1) ? 1.08f : 1.0f;
            float targetWinterScale = (selectedEnvironment == 2) ? 1.08f : 1.0f;
            float dt = GetFrameTime();
            summerScale += (targetSummerScale - summerScale) * 12.0f * dt;
            winterScale += (targetWinterScale - winterScale) * 12.0f * dt;

            // Mapped button coordinates in 1419x736 texture space
            float summerTexX = 386.0f;
            float summerTexY = 455.0f;
            float summerTexW = 305.0f;
            float summerTexH = 99.0f;

            float winterTexX = 731.0f;
            float winterTexY = 455.0f;
            float winterTexW = 305.0f;
            float winterTexH = 99.0f;

            // Translate to screen coordinates
            Rectangle summerScreenRec = {
                destX + (summerTexX / 1419.0f) * destWidth,
                destY + (summerTexY / 736.0f) * destHeight,
                (summerTexW / 1419.0f) * destWidth,
                (summerTexH / 736.0f) * destHeight
            };

            Rectangle winterScreenRec = {
                destX + (winterTexX / 1419.0f) * destWidth,
                destY + (winterTexY / 736.0f) * destHeight,
                (winterTexW / 1419.0f) * destWidth,
                (winterTexH / 736.0f) * destHeight
            };

            // Custom Button drawing helper
            auto DrawCustomButton = [&](Rectangle baseRec, float scaleVal, bool selected, Color themeColor, const char* text, bool isSummer) {
                // Scale rectangle centered
                float newWidth = baseRec.width * scaleVal;
                float newHeight = baseRec.height * scaleVal;
                float newX = baseRec.x - (newWidth - baseRec.width) / 2.0f;
                float newY = baseRec.y - (newHeight - baseRec.height) / 2.0f;
                Rectangle rec = { newX, newY, newWidth, newHeight };

                // Draw button background
                Color bgColor = selected ? themeColor : BLACK;
                Color borderColor = selected ? themeColor : (Color){215, 200, 180, 255};
                
                // Rounded button backing (covers the background image button)
                DrawRectangleRounded(rec, 0.35f, 16, bgColor);
                
                // Borders
                DrawRectangleRoundedLines(rec, 0.35f, 16, borderColor);
                
                if (selected)
                {
                    // Draw outer glow layers
                    Rectangle outerRec1 = { rec.x - 2, rec.y - 2, rec.width + 4, rec.height + 4 };
                    Rectangle outerRec2 = { rec.x - 4, rec.y - 4, rec.width + 8, rec.height + 8 };
                    DrawRectangleRoundedLines(outerRec1, 0.35f, 16, Fade(themeColor, 0.35f * pulse));
                    DrawRectangleRoundedLines(outerRec2, 0.35f, 16, Fade(themeColor, 0.15f * pulse));
                }
                else
                {
                    // Faint pulsing border for interactive feel when none is selected
                    DrawRectangleRoundedLines(rec, 0.35f, 16, Fade(borderColor, 0.6f + 0.3f * pulse));
                }

                // Render procedural icons and text inside the button
                int fontSize = rec.height * 0.28f;
                int textWidth = MeasureText(text, fontSize);
                
                float contentWidth = textWidth + 30.0f; // text width + icon + spacing
                float startX = rec.x + (rec.width - contentWidth) / 2.0f;
                float centerY = rec.y + rec.height / 2.0f;
                
                Color textColor = selected ? WHITE : (Color){200, 190, 180, 255};
                Color iconColor = selected ? WHITE : (Color){215, 200, 180, 255};

                if (isSummer)
                {
                    // Procedural Sun: circle with lines for rays
                    DrawCircle(startX + 10, centerY, 6, iconColor);
                    for (int a = 0; a < 360; a += 45)
                    {
                        float rad = a * DEG2RAD;
                        Vector2 start = { startX + 10 + cosf(rad) * 8, centerY + sinf(rad) * 8 };
                        Vector2 end = { startX + 10 + cosf(rad) * 11, centerY + sinf(rad) * 11 };
                        DrawLineEx(start, end, 1.5f, iconColor);
                    }
                }
                else
                {
                    // Procedural Snowflake: intersecting lines with terminal ticks
                    DrawLineEx((Vector2){ startX + 4, centerY }, (Vector2){ startX + 16, centerY }, 2.0f, iconColor);
                    DrawLineEx((Vector2){ startX + 10, centerY - 6 }, (Vector2){ startX + 10, centerY + 6 }, 2.0f, iconColor);
                    DrawLineEx((Vector2){ startX + 6, centerY - 4 }, (Vector2){ startX + 14, centerY + 4 }, 1.5f, iconColor);
                    DrawLineEx((Vector2){ startX + 6, centerY + 4 }, (Vector2){ startX + 14, centerY - 4 }, 1.5f, iconColor);
                }

                // Draw label next to icon
                DrawText(text, startX + 25.0f, centerY - fontSize / 2.0f, fontSize, textColor);
            };

            // Render custom button overlays on top of the menu image buttons
            DrawCustomButton(summerScreenRec, summerScale, selectedEnvironment == 1, ORANGE, "SUMMER", true);
            DrawCustomButton(winterScreenRec, winterScale, selectedEnvironment == 2, SKYBLUE, "WINTER", false);

            // Pulse line under "Press ENTER to Start" if environment is selected
            if (selectedEnvironment != 0)
            {
                Color themeColor = (selectedEnvironment == 1) ? ORANGE : SKYBLUE;
                Color glowColor = LerpColor(themeColor, WHITE, pulse);
                float lineX1 = destX + destWidth / 2.0f - 140.0f;
                float lineX2 = destX + destWidth / 2.0f + 140.0f;
                float lineY = destY + (680.0f / 736.0f) * destHeight;

                DrawLineEx((Vector2){ lineX1, lineY }, (Vector2){ lineX2, lineY }, 2.5f, Fade(glowColor, 0.4f + 0.4f * pulse));
            }
        }
        else
        {
            ClearBackground(WHITE);
        Color nightBG = (Color){20, 30, 60, 120};      // strong blue tint (background feel)
        Color nightObject = (Color){80, 100, 160, 60}; // lighter tint for objects
        // ==================== DRAW ENVIRONMENT ====================
        if (selectedEnvironment == 1)
        {
            // BACKGROUND tint system based on weather phase
            Color daySkyTint = WHITE;
            Color cloudySkyTint = (Color){185, 190, 200, 255}; // Light gray-blue
            Color nightSkyTint = (Color){60, 60, 100, 255};

            auto GetTargetSkyTint = [&](int phase) -> Color {
                if (phase == 0) return daySkyTint;
                if (phase == 1) return nightSkyTint;
                if (phase == 2) return LerpColor(daySkyTint, cloudySkyTint, cloudAlpha);
                if (phase == 3) return cloudySkyTint;
                if (phase == 4 || phase == 5) return nightSkyTint;
                return daySkyTint;
            };

            Color skyTint = daySkyTint;

            if (weatherTransitionActive)
            {
                Color fromSky = GetTargetSkyTint(weatherTransitionFromPhase);
                Color toSky = GetTargetSkyTint(weatherTransitionToPhase);
                skyTint = LerpColor(fromSky, toSky, weatherTransitionProgress);
            }
            else
            {
                skyTint = GetTargetSkyTint(summerPhase);
            }


            DrawTexturePro(
                desertBG,
                (Rectangle){0, 0, (float)desertBG.width, (float)desertBG.height},
                (Rectangle){0, 0, 800, 420},
                (Vector2){0, 0},
                0,
                skyTint);

            // 🌞 SUN / 🌙 MOON SWITCH - draw celestial body based on phase
            if (cycleScore <= 20 || (cycleScore > 40 && cycleScore <= 80))
            {
                // SUN visible: 0-20, 41-60, 61-80
                DrawCircle(sunX + 40, 70, 70, Fade(YELLOW, 0.08f));
                DrawCircle(sunX + 40, sunY + 40, 55, Fade(ORANGE, 0.12f));
                DrawCircle(sunX + 40, sunY + 40, 40, Fade(YELLOW, 0.18f));
                DrawTexturePro(
                    sunTexture,
                    (Rectangle){0, 0, (float)sunTexture.width, (float)sunTexture.height},
                    (Rectangle){sunX, 30, 80, 80},
                    (Vector2){0, 0},
                    0,
                    WHITE);
            }
            else
            {
                // Moon Glow
                DrawCircle(moonX + 35, 85, 70, Fade((Color){150, 200, 255, 255}, 0.05f));
                DrawCircle(moonX + 35, 85, 55, Fade((Color){200, 225, 255, 255}, 0.08f));
                DrawCircle(moonX + 35, 85, 40, Fade((Color){235, 245, 255, 255}, 0.12f));
                DrawTexturePro(
                    moonSummer,
                    (Rectangle){0, 0, (float)moonSummer.width, (float)moonSummer.height},
                    (Rectangle){moonX, 50, 70, 70},
                    (Vector2){0, 0},
                    0,
                    WHITE);
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
            Color dayGroundTint = WHITE;
            Color cloudyGroundTint = (Color){185, 185, 185, 255};
            Color nightGroundTint = (Color){100, 110, 140, 255};

            auto GetTargetGroundTint = [&](int phase) -> Color {
                if (phase == 0) return dayGroundTint;
                if (phase == 1) return nightGroundTint;
                if (phase == 2) return LerpColor(dayGroundTint, cloudyGroundTint, cloudAlpha);
                if (phase == 3) return cloudyGroundTint;
                if (phase == 4 || phase == 5) return nightGroundTint;
                return dayGroundTint;
            };

            Color groundTint = dayGroundTint;

            // ===== Weather Transition =====
            if (weatherTransitionActive)
            {
                Color fromGround = GetTargetGroundTint(weatherTransitionFromPhase);
                Color toGround = GetTargetGroundTint(weatherTransitionToPhase);
                groundTint = LerpColor(fromGround, toGround, weatherTransitionProgress);
            }
            else
            {
                groundTint = GetTargetGroundTint(summerPhase);
            }

            // ===== Draw Ground =====
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
        // ================= RAIN CLOUDS =================
        if ((cycleScore >= 59 && cycleScore <= 90) ||
            cloudEntering ||
            cloudLeaving)
        {
            // ================= TOP ROW =================

            // Left Half
            for (int x = -40; x < 400; x += 250)
            {
                DrawTextureEx(
                    rainycloud,
                    (Vector2){leftCloudOffset + x, -60},
                    0.0f,
                    0.45f,
                    Fade(WHITE, cloudAlpha));
            }

            // Right Half
            for (int x = 220; x < screenWidth + 200; x += 250)
            {
                DrawTextureEx(
                    rainycloud,
                    (Vector2){rightCloudOffset + x, -60},
                    0.0f,
                    0.45f,
                    Fade(WHITE, cloudAlpha));
            }

            // ================= MIDDLE ROW =================

            // Left Half
            for (int x = -150; x < 400; x += 250)
            {
                DrawTextureEx(
                    rainycloud,
                    (Vector2){leftCloudOffset + x, -15},
                    0.0f,
                    0.45f,
                    Fade(WHITE, cloudAlpha * 0.9f));
            }

            // Right Half
            for (int x = 110; x < screenWidth + 200; x += 250)
            {
                DrawTextureEx(
                    rainycloud,
                    (Vector2){rightCloudOffset + x, -15},
                    0.0f,
                    0.45f,
                    Fade(WHITE, cloudAlpha * 0.9f));
            }

            // ================= BOTTOM ROW =================

            // Left Half
            for (int x = -50; x < 400; x += 250)
            {
                DrawTextureEx(
                    rainycloud,
                    (Vector2){leftCloudOffset + x, 30},
                    0.0f,
                    0.40f,
                    Fade(WHITE, cloudAlpha * 0.85f));
            }

            // Right Half
            for (int x = 210; x < screenWidth + 200; x += 250)
            {
                DrawTextureEx(
                    rainycloud,
                    (Vector2){rightCloudOffset + x, 30},
                    0.0f,
                    0.40f,
                    Fade(WHITE, cloudAlpha * 0.85f));
            }

            // ================= RAIN =================

            if (!cloudEntering &&
                !cloudLeaving &&
                cloudAlpha >= 1.0f &&
                cycleScore >= 61 &&
                cycleScore <= 87)
            {
                for (int i = 0; i < rainCount; i++)
                {
                    Color rainColor = (summerPhase == 4)
                                          ? (Color){220, 235, 255, 180}
                                          : (Color){90, 170, 255, 150};

                    DrawLineEx(
                        (Vector2){rain[i].x, rain[i].y},
                        (Vector2){rain[i].x - 2, rain[i].y + 10},
                        1.5f,
                        rainColor);
                }
            }
        }
        // ===== DRAW DINO =====
        if (isCrouching)
        {
            DrawTexturePro(
                dinoCrouchTexture,
                (Rectangle){0, 0, (float)dinoCrouchTexture.width, (float)dinoCrouchTexture.height},
                (Rectangle){(float)dinoX, (float)(dinoY + 20), 50.0f, 40.0f},
                (Vector2){0, 0},
                0.0f,
                WHITE);
        }
        else if (isJumping)
        {
            DrawTexturePro(
                dinoJump,
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
        if (glowAndStickPhase)
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
        if (glowAndStickPhase)
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
        if (glowAndStickPhase)
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
            glowAndStickPhase ? (Color){180, 255, 180, 255} : WHITE);

        if (secondCactusActive)
        {
            Texture2D cactus2TextureToDraw = GetCactusTextureForType(cactus2Type, selectedEnvironment == 2);
            if (glowAndStickPhase)
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
                glowAndStickPhase ? (Color){180, 255, 180, 255} : WHITE);
        }

        // ===== DRAW BIRD (Using textures with scaling) =====
        if (birdActive && glowAndStickPhase)
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
                    glowAndStickPhase ? (Color){190, 210, 255, 255} : WHITE);
            }
            else if (birdAnimationType == 1)
            {
                DrawTexturePro(
                    birdLevel2Texture,
                    (Rectangle){0, 0, (float)birdLevel2Texture.width, (float)birdLevel2Texture.height},
                    (Rectangle){(float)birdX, (float)birdY, 40.0f, 20.0f},
                    (Vector2){0, 0},
                    0.0f,
                    glowAndStickPhase ? (Color){190, 210, 255, 255} : WHITE);
            }
            else
            {
                DrawTexturePro(
                    birdDown2Texture,
                    (Rectangle){0, 0, (float)birdDown2Texture.width, (float)birdDown2Texture.height},
                    (Rectangle){(float)birdX, (float)birdY, 40.0f, 20.0f},
                    (Vector2){0, 0},
                    0.0f,
                    glowAndStickPhase ? (Color){190, 210, 255, 255} : WHITE);
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

        // Game over screen
        if (gameOver)
        {
            DrawText("GAME OVER", 280, 150, 40, RED);
            DrawText("Press R to restart", 285, 195, 25, DARKGRAY);
            DrawText(TextFormat("High Score: %d", highscore), 320, 240, 25, BLUE);
        }
        } // Close gameStarted else block

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
    UnloadTexture(dinoJump);
    UnloadTexture(dinoCrouchTexture);
     UnloadTexture(menu);

    CloseWindow();
    return 0;
}
