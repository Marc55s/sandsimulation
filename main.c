#include "raylib.h"
#include "rlgl.h"
#include <stdio.h>
#include <stdlib.h>
#define TILES_SIZE 1

const int screenWidth = 800;
const int screenHeight = 450;

Rectangle empty_rect = {0};

int rect_isempty(Rectangle rect) {
    return (rect.x == 0 && rect.y == 0 && rect.width == 0 && rect.height == 0);
}

void init_grid(Rectangle ***grid) {
    int rows = screenHeight / TILES_SIZE;
    int cols = screenWidth / TILES_SIZE;

    // Allocate memory for the grid of pointers
    *grid = (Rectangle **)MemAlloc(rows * sizeof(Rectangle *));
    if (*grid == NULL) {
        perror("Failed to allocate memory for grid rows");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        (*grid)[i] = (Rectangle *)MemAlloc(cols * sizeof(Rectangle));
        if ((*grid)[i] == NULL) {
            perror("Failed to allocate memory for grid columns");
            exit(EXIT_FAILURE);
        }
    }

    // Initialize the grid with empty_rect
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*grid)[i][j] = empty_rect;
        }
    }
}
void update_grid(Rectangle **grid) {
    int rows = screenHeight / TILES_SIZE;
    int cols = screenWidth / TILES_SIZE;

    // Iterate from the bottom row to the top row
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {

            if (rect_isempty(grid[i][j])) {
                continue;
            }

            // Check bounds before accessing grid elements
            if (i + 1 < rows && rect_isempty(grid[i + 1][j])) {
                // Move down if free
                grid[i + 1][j] = grid[i][j];
                grid[i][j] = empty_rect;
            } else if (i + 1 < rows  && j + 1 < cols - 1 &&
                rect_isempty(grid[i + 1][j + 1])) {
                // Move diagonally right if free
                grid[i + 1][j + 1] = grid[i][j];
                grid[i][j] = empty_rect;
            } else if (i + 1 < rows  && j - 1 >= 0 &&
                rect_isempty(grid[i + 1][j - 1])) {
                // Move diagonally left if free
                grid[i + 1][j - 1] = grid[i][j];
                grid[i][j] = empty_rect;
            }
        }
    }
}

void draw_grid(Rectangle **grid) {
    for (int i = 0; i < screenHeight / TILES_SIZE; i++) {
        for (int j = 0; j < screenWidth / TILES_SIZE; j++) {
            Rectangle rect = grid[i][j];
            if (!rect_isempty(rect))
                DrawRectangle(j * rect.height, i * rect.width, rect.width, rect.height,
                              GOLD);
        }
    }
}

void spawn(Rectangle **grid) {
    for (int j = 30-1; j < 30; j++) {
    }
    grid[0][screenWidth/2] = (Rectangle){0, 0, TILES_SIZE, TILES_SIZE};
}

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "ParticleSimualation");
    Rectangle **grid;
    init_grid(&grid);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(0, 30);
        spawn(grid);

        update_grid(grid);
        draw_grid(grid);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow(); // Close window and OpenGL context
    MemFree(grid);
    return 0;
}
