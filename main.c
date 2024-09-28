#include <stdio.h>
#include <stdlib.h>
#include "mouse.h"
#include "particle.h"
#include "util.h"
#include "raylib.h"
#include "rlgl.h"

#define TILES_SIZE 5

const int screenWidth = 800;
const int screenHeight = 600;


void init_grid(Particle_t ***grid) {
    int rows = screenHeight / TILES_SIZE;
    int cols = screenWidth / TILES_SIZE;

    // Allocate memory for the grid of pointers
    *grid = (Particle_t **)MemAlloc(rows * sizeof(Particle_t *));
    if (*grid == NULL) {
        perror("Failed to allocate memory for grid rows");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        (*grid)[i] = (Particle_t *)MemAlloc(cols * sizeof(Particle_t));
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

void update_grid(Particle_t  **grid) {
    int rows = screenHeight / TILES_SIZE;
    int cols = screenWidth / TILES_SIZE;
    Particle_t **nextGrid;
    init_grid(&nextGrid);
    copy_grid(grid, nextGrid, rows, cols);

    // Iterate from the bottom row to the top row
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {

            switch (nextGrid[i][j].type) {
                case EMPTY:
                    continue;
                    break;
                case SAND:
                    // Check bounds before accessing grid elements
                    if (i + 1 < rows && !(nextGrid[i + 1][j].type)) {
                        // Move down if free
                        nextGrid[i + 1][j] = nextGrid[i][j];
                        nextGrid[i][j].type = 0;
                    } else if (i + 1 < rows && j + 1 < cols && !(nextGrid[i + 1][j + 1].type)) {
                        // Move diagonally right if free
                        nextGrid[i + 1][j + 1] = nextGrid[i][j];
                        nextGrid[i][j].type = 0;
                    } else if (i + 1 < rows && j - 1 >= 0 && !(nextGrid[i + 1][j - 1].type)) {
                        // Move diagonally left if free
                        nextGrid[i + 1][j - 1] = nextGrid[i][j];
                        nextGrid[i][j].type = EMPTY;
                    }

                    break;
                case WATER:
                    break;
                case STONE:
                    break;
            }
        }
    }
    copy_grid(nextGrid, grid, rows, cols);
    free_grid(&nextGrid, rows);
}

void draw_grid(Particle_t **grid) {
    for (int i = 0; i < screenHeight / TILES_SIZE; i++) {
        for (int j = 0; j < screenWidth / TILES_SIZE; j++) {
            Particle_t particle = grid[i][j];
            Color color;
            switch (particle.type) {
                case EMPTY:
                    continue;
                case SAND:
                    //color = GOLD;
                    color = particle.color;
                    break;
                case WATER:
                    color = BLUE;
                    break;
                case STONE:
                    //TODO add color
                    break;
            }
            DrawRectangle(j * TILES_SIZE, i * TILES_SIZE, TILES_SIZE, TILES_SIZE,
                          color);
        }
    }
}

void spawn(Particle_t **grid) {
    grid[0][(screenWidth / TILES_SIZE) / 2].type = SAND;
    int randomG = 190 + rand() % 40;
    Color color = (Color){255,randomG,0,255};
    grid[0][(screenWidth / TILES_SIZE) / 2].color = color;
    grid[0][(screenWidth / TILES_SIZE) / 2].state= SOLID;
}

void set_particle_in_grid(Particle_t **grid, int x, int y, enum particle_type type) {
    grid[y / TILES_SIZE][x / TILES_SIZE].type = type;
    int randomG = 190 + rand() % 40;
    Color color = (Color){255,randomG,0,255};
    grid[y / TILES_SIZE][x / TILES_SIZE].color = color;
}

void set_particles_in_grid(Particle_t **grid, Rectangle rect,
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

    Particle_t **grid;
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
