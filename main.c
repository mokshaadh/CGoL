#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define GRID_SIZE_W (16 * 4)
#define GRID_SIZE_H (9 * 4)
// https://github.com/catppuccin/catppuccin
#define BASECAT (Color) {30, 30, 48, 255}
#define TEXTCAT (Color) {205, 214, 244, 255}
#define SURFACE1CAT (Color) {69, 71, 90, 255}
#define MANTLECAT (Color) {24, 24, 37, 255}
#define REDCAT (Color) {243, 139, 168, 255}
#define ROSEWATERCAT (Color) {245, 224, 220, 255}

typedef unsigned char grid[GRID_SIZE_W][GRID_SIZE_H];

int main(void)
{
    const unsigned int initWidth = 1280;
    const unsigned int initHeight = 720;

    grid mainGrid = {0};
    grid neighborsGrid = {0};
    // simple glider
    mainGrid[20][3] = 1;
    mainGrid[21][4] = 1;
    mainGrid[21][5] = 1;
    mainGrid[20][5] = 1;
    mainGrid[19][5] = 1;

    // SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(initWidth, initHeight, "Conway's Game of Life - mokshaadh");

    Vector2 squareSize = { (float)GetScreenWidth()/GRID_SIZE_W, (float)GetScreenHeight()/GRID_SIZE_H};

    bool play = 0;
    const int offsets[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

    size_t frame = 0;
    unsigned int fps = 60;
    unsigned int speed = fps * .75;

    SetTargetFPS(fps);
 
    while (!WindowShouldClose())
    {
        // play sim if space is pressed
        if (IsKeyPressed(KEY_SPACE)) play = !play;
        if (IsKeyPressed(KEY_LEFT)) if (speed > 0) speed--;
        if (IsKeyPressed(KEY_RIGHT)) if (speed < fps) speed++;

        // toggle square
        if (!play && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mpos = GetMousePosition();
            const unsigned int calcx = 0 + (int)((GRID_SIZE_W - 0) * (mpos.x / GetScreenWidth()));
            const unsigned int calcy = 0 + (int)((GRID_SIZE_H - 0) * (mpos.y / GetScreenHeight()));
            mainGrid[calcx][calcy] = !mainGrid[calcx][calcy];
        }

        for (size_t x = 0; x < GRID_SIZE_W; ++x) {
            for (size_t y = 0; y < GRID_SIZE_H; ++y) {
                // check num neighbors
                unsigned char neighbors = 0;
                for (size_t i = 0; i < 8; ++i) {
                    int newX = x + offsets[i][0];
                    int newY = y + offsets[i][1];
                    if (newX >= 0 && newX < GRID_SIZE_W && newY >= 0 && newY < GRID_SIZE_H) {
                        if (mainGrid[newX][newY] == 1) {
                            ++neighbors;
                        }
                    }
                }
                neighborsGrid[x][y] = neighbors;
            }
        }

        // game is being played
        if (play && frame == (fps - speed)) {
            grid newGrid = {0};
            for (size_t x = 0; x < GRID_SIZE_W; ++x) {
                for (size_t y = 0; y < GRID_SIZE_H; ++y) {
                    unsigned char neighbors = neighborsGrid[x][y];
                    // cell is alive
                    if (mainGrid[x][y] == 1) { 
                        if (neighbors < 2 || neighbors > 3) {
                            // under and over population
                            newGrid[x][y] = 0;
                        }
                        else newGrid[x][y] = 1;
                    }
                    // cell is dead
                    else {
                        if (neighbors == 3) {
                            // reproduction
                            newGrid[x][y] = 1;
                        }
                        else newGrid[x][y] = 0;
                    }
                }
            }
            for (size_t x = 0; x < GRID_SIZE_W; ++x) {
                for (size_t y = 0; y < GRID_SIZE_H; ++y) {
                    mainGrid[x][y] = newGrid[x][y];
                }
            }
        }

        // render
        BeginDrawing();
            ClearBackground(BASECAT);
            // borders
            for (size_t x = 0; x < GRID_SIZE_W + 1; ++x) {
                Vector2 bordSize = { 1, ((float)GetScreenHeight()) };
                Vector2 bordPos = { ((float)GetScreenWidth() / GRID_SIZE_W) * x - .5, 0 };
                DrawRectangleV(bordPos, bordSize, MANTLECAT);
            }
            for (size_t y = 0; y < GRID_SIZE_H + 1; ++y) {
                Vector2 bordSize = { ((float)GetScreenWidth()), 1 };
                Vector2 bordPos = { 0, ((float)GetScreenHeight() / GRID_SIZE_H) * y + 0 };
                DrawRectangleV(bordPos, bordSize, MANTLECAT);
            }
            
            // actual squares
            for (size_t x = 0; x < GRID_SIZE_W; ++x) {
                for (int y = 0; y < GRID_SIZE_H; ++y) {
                    if (mainGrid[x][y] == 1) {
                        Vector2 squarePos = { ((float)GetScreenWidth() / GRID_SIZE_W) * x, ((float)GetScreenHeight() / GRID_SIZE_H) * y };
                        DrawRectangleV(squarePos, squareSize, ROSEWATERCAT);
                        if (!play) { 
                            char str[2];
                            snprintf(str, sizeof(str), "%d", neighborsGrid[x][y]);
                            DrawText(str, squarePos.x+squareSize.x/4, squarePos.y+squareSize.x/12, squareSize.x, SURFACE1CAT);
                        }
                    }
                }
            }
            DrawFPS(10, GetScreenHeight() - 30);
            char spdstr[15];
            snprintf(spdstr, sizeof(spdstr), "speed: %d/%d", speed, fps);
            DrawText(spdstr, 10, 10, 24.0, REDCAT);
            DrawText("arrows to change speed", 10, 40, 24.0, REDCAT);
            DrawText("space to play/pause", 10, 70, 24.0, REDCAT);
        EndDrawing();
        frame >= (fps - speed) ? frame = 0 : ++frame;
    }

    CloseWindow();

    return 0;
}
