#include <stdio.h>
#include <stdlib.h>
#include "mouse.h"
#include "particle.h"
#include "raylib.h"
#include "rlgl.h"

#define TILES_SIZE 5

const int screenWidth = 800;
const int screenHeight = 600;


void init_grid(particle_t ***grid) {
    int rows = screenHeight / TILES_SIZE;
    int cols = screenWidth / TILES_SIZE;

    // Allocate memory for the grid of pointers
    *grid = (particle_t **)MemAlloc(rows * sizeof(particle_t *));
    if (*grid == NULL) {
        perror("Failed to allocate memory for grid rows");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        (*grid)[i] = (particle_t *)MemAlloc(cols * sizeof(particle_t));
        if ((*grid)[i] == NULL) {
            perror("Failed to allocate memory for grid columns");
            exit(EXIT_FAILURE);
        }
    }

    // Initialize the grid with empty_rect
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*grid)[i][j].type = EMPTY;
        }
    }
}

void update_grid(particle_t  **grid) {
    int rows = screenHeight / TILES_SIZE;
    int cols = screenWidth / TILES_SIZE;

    // Iterate from the bottom row to the top row
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {

            if (!grid[i][j].type) {
                continue;
            }
            switch (grid[i][j].type) {
                case EMPTY:
                    break;
                case SAND:
                    break;
                case WATER:
                    break;
                case STONE:
                    break;
            }

            // Check bounds before accessing grid elements
            if (i + 1 < rows && !(grid[i + 1][j].type)) {
                // Move down if free
                grid[i + 1][j] = grid[i][j];
                grid[i][j].type = 0;
            } else if (i + 1 < rows && j + 1 < cols && !(grid[i + 1][j + 1].type)) {
                // Move diagonally right if free
                grid[i + 1][j + 1] = grid[i][j];
                grid[i][j].type = 0;
            } else if (i + 1 < rows && j - 1 >= 0 && !(grid[i + 1][j - 1].type)) {
                // Move diagonally left if free
                grid[i + 1][j - 1] = grid[i][j];
                grid[i][j].type = EMPTY;
            }
        }
    }
}

void draw_grid(particle_t **grid) {
    for (int i = 0; i < screenHeight / TILES_SIZE; i++) {
        for (int j = 0; j < screenWidth / TILES_SIZE; j++) {
            int particle = grid[i][j].type;
            Color color;
            switch (particle) {
                case EMPTY:
                    continue;
                case SAND:
                    color = GOLD;
                    break;
                case WATER:
                    color = BLUE;
                    break;
            }
            DrawRectangle(j * TILES_SIZE, i * TILES_SIZE, TILES_SIZE, TILES_SIZE,
                          color);
        }
    }
}

void spawn(particle_t **grid) {
    grid[0][(screenWidth / TILES_SIZE) / 2].type = SAND;
    grid[0][(screenWidth / TILES_SIZE) / 2].state= SOLID;
}

void set_particle_in_grid(particle_t **grid, int x, int y, enum particle_type type) {
    grid[y / TILES_SIZE][x / TILES_SIZE].type = type;
}

void set_particles_in_grid(particle_t **grid, Rectangle rect,
                           enum particle_type type) {
    for (int y = rect.y; y < rect.y + rect.height && y >= 0 && y < screenHeight;
    y++) {
        for (int x = rect.x; x < rect.x + rect.width && x >= 0 && x < screenWidth;
        x++) {
            set_particle_in_grid(grid, x, y, type);
        }
    }
}

int main(void) {

    InitWindow(screenWidth, screenHeight, "ParticleSimualation");
    SetTargetFPS(60);

    particle_t **grid;
    init_grid(&grid);

    Rectangle r = {0, 0, 0, 0};

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);
        spawn(grid);
        DrawFPS(0, 30);
        container(&r);

        if (!IsMouseButtonDown(0)) {
            set_particles_in_grid(grid, r, SAND);
        }

        update_grid(grid);
        draw_grid(grid);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    MemFree(grid);
    return 0;
}
