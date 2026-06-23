#include "raylib.h"

int main()
{
    // SETUP WINDOW
    InitWindow(800, 420, "Dino Game");
    SetTargetFPS(60);  // 60 frames per second (smoother)
    
    // DINO POSITION (where it appears on screen)
    int dinoX = 100;      // left-right position
    int dinoY = 290;      // up-down position
    int dinoWidth = 50;   // dino width
    int dinoHeight = 60;  // dino height
    
    // DINO JUMPING (falling & jumping)
    int dinoSpeed = 0;    // how fast dino is moving up/down
    int gravity = 1;      // how fast dino falls (1 pixel per frame)
    int jumpPower = 15;   // how strong the jump is
    
    // GROUND LOCATION
    int ground = 290;     // where dino should stand
    
    int cactusX = 800;
    int cactusY = 300;

    int cactusWidth = 30;
    int cactusHeight = 50;

    
    // GAME LOOP (runs forever until window closes)
    while (!WindowShouldClose()) {
        
        // ===== INPUT (check if player pressed keys) =====
        
        // JUMP - if player presses SPACE
        if (IsKeyPressed(KEY_SPACE)) {
            // Only jump if dino is on ground
            if (dinoY == ground) {
                dinoSpeed = -jumpPower;  // minus means UP
            }
        }
        
        // MOVE RIGHT - if player holds RIGHT ARROW
        if (IsKeyDown(KEY_RIGHT)) {
            dinoX = dinoX + 5;  // move 5 pixels right
        }
        
        // MOVE LEFT - if player holds LEFT ARROW
        if (IsKeyDown(KEY_LEFT)) {
            dinoX = dinoX - 5;  // move 5 pixels left
        }
        
        // ===== PHYSICS (make dino fall down) =====
        
        // Add gravity (dino gets slower at jumping, then falls)
        dinoSpeed = dinoSpeed + gravity;
        
        // Move dino up or down based on speed
        dinoY = dinoY + dinoSpeed;
        
        // ===== COLLISION (stop dino at ground) =====
        
        // If dino goes below ground, stop it
        if (dinoY >= ground) {
            dinoY = ground;        // put it on ground
            dinoSpeed = 0;         // stop movement
        }
        
        // Keep dino on screen (don't go off left/right)
        if (dinoX < 0) {
            dinoX = 0;
        }
        if (dinoX > 800 - dinoWidth) {
            dinoX = 800 - dinoWidth;
        }

        if (cactusX < -cactusWidth)
{
    cactusX = 800;
}
        
        cactusX = cactusX - 5;

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
    GREEN
     );
        // Show helpful info
        DrawText("Press SPACE to JUMP", 10, 10, 20, DARKGRAY);
        DrawText("Use LEFT RIGHT arrows to MOVE", 10, 40, 20, DARKGRAY);
        DrawText(TextFormat("Dino Height: %d", dinoY), 10, 70, 20, DARKGRAY);
        
        EndDrawing();
    }
    
    // Close window and exit
    CloseWindow();
    return 0;
}