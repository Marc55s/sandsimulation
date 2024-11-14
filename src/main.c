#include "../include/mouse.h"
#include "../include/particle.h"
#include "../include/config.h"
#include "../include/util.h"
#include "raylib.h"
#include "rlgl.h"
#include <stdlib.h>

const int screenWidth = 800;
const int screenHeight = 600;

/* TODOs ------------------------------------------------------------
* TODO optimize dispersionRate updating
* TODO add gravity
* TODO update border rules -> if at border move to other side
* TODO add logic for interacting between SAND and WATER
* -------------------------------------------------------------------
*/


void update_grid(Particle_t **grid) {
    int rows = screenHeight / TILES_SIZE;
    int cols = screenWidth / TILES_SIZE;
    Particle_t **nextGrid;
    init_grid(&nextGrid);
    copy_grid(grid, nextGrid, rows, cols);

    // Iterate from the bottom row to the top row
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {
            //skip EMPTY,STONE type
            if(nextGrid[i][j].type == EMPTY || nextGrid[i][j].type == STONE){
                continue;
            }
            update_particle(nextGrid, i, j, rows, cols);
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
                    // color = GOLD;
                    color = particle.color;
                    break;
                case WATER:
                    color = particle.color;
                    break;
                case STONE:
                    color = particle.color;
                    break;
            }
            DrawRectangle(j * TILES_SIZE, i * TILES_SIZE, TILES_SIZE, TILES_SIZE,
                          color);
        }
    }
}

void spawn(Particle_t **grid) {
    grid[0][(screenWidth / TILES_SIZE) / 2].type = WATER;
    grid[0][(screenWidth / TILES_SIZE) / 2].dispersionRate = 10;
    Color color = BLUE;
    randomize_color(&color, 5);
    grid[0][(screenWidth / TILES_SIZE) / 2].color = color;
    grid[0][(screenWidth / TILES_SIZE) / 2].state = SOLID;
}

int main(void) {
    srand(23);
    InitWindow(screenWidth, screenHeight, "ParticleSimualation");
    SetTargetFPS(60);

    Particle_t **grid;
    init_grid(&grid);

    Rectangle r = {0, 0, 0, 0};

    Particle_t p = (Particle_t) {STONE, SOLID, false,false,0,PINK};
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);
        spawn(grid);
        DrawFPS(0, 30);
        container(&r);

        if (!IsMouseButtonDown(0)) {
            set_rectangle_in_grid(grid, r, p);
        }

        update_grid(grid);
        draw_grid(grid);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    MemFree(grid);
    return 0;
}
