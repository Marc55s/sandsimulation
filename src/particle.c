#include "../include/particle.h"
#include "../include/config.h"
#include <stdlib.h>

/*
* update_particle updates WATER and SAND
* handles updates downwards & dispersion
*/
void update_particle(Particle_t **nextGrid, int i,int j,int rows,int cols){
    // Check bounds before accessing grid elements
    // with dispersion the particle goes far abroader to left and right
    // to essentially move down if possible

    int disp_max = nextGrid[i][j].dispersionRate;
    if (i + 1 < rows && !(nextGrid[i + 1][j].type)) {
        // Move down if free
        nextGrid[i + 1][j] = nextGrid[i][j];
        nextGrid[i][j].type = EMPTY;
    } else {
        for (int dispersion = 1; dispersion <= disp_max; dispersion++) {
            int randomizeMovement = 0;
            if(nextGrid[i][j].type != WATER)
                randomizeMovement = rand() % 2;

            if(randomizeMovement){
                if (i + 1 < rows && j + dispersion < cols &&
                    // Move diagonally right if free
                    !(nextGrid[i + 1][j + dispersion].type)) {
                    nextGrid[i + 1][j + dispersion] = nextGrid[i][j];
                    nextGrid[i][j].type = EMPTY;
                    break;
                } else if (i + 1 < rows && j - dispersion >= 0 &&
                    // Move diagonally left if free
                    !(nextGrid[i + 1][j - dispersion].type)) {
                    nextGrid[i + 1][j - dispersion] = nextGrid[i][j];
                    nextGrid[i][j].type = EMPTY;
                    break;
                }
            }else{
                if (i + 1 < rows && j - dispersion >= 0 &&
                    // Move diagonally left if free
                    !(nextGrid[i + 1][j - dispersion].type)) {
                    nextGrid[i + 1][j - dispersion] = nextGrid[i][j];
                    nextGrid[i][j].type = EMPTY;
                    break;
                }else if (i + 1 < rows && j + dispersion < cols &&
                    // Move diagonally right if free
                    !(nextGrid[i + 1][j + dispersion].type)) {
                    nextGrid[i + 1][j + dispersion] = nextGrid[i][j];
                    nextGrid[i][j].type = EMPTY;
                    break;

                }
            }
        }
    }
}

void set_particle_in_grid(Particle_t **grid, int x, int y, Particle_t p) {
    grid[y / TILES_SIZE][x / TILES_SIZE].type = p.type;
    grid[y / TILES_SIZE][x / TILES_SIZE].dispersionRate = p.dispersionRate;
    grid[y / TILES_SIZE][x / TILES_SIZE].color = p.color;
}

void set_rectangle_in_grid(Particle_t **grid, Rectangle rect, Particle_t p) {
    for (int y = rect.y; y < rect.y + rect.height && y >= 0 && y < screenHeight;
    y++) {
        for (int x = rect.x; x < rect.x + rect.width && x >= 0 && x < screenWidth;
        x++) {
            set_particle_in_grid(grid, x, y, p);
        }
    }
}
