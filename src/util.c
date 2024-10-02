#include "util.h"
#include <raylib.h>

void copy_grid(Particle_t **src, Particle_t **dst, int row, int col){
    for (int i  = 0 ; i< row; i++) {
        for (int k = 0;k < col; k++) {
            dst[i][k] = src[i][k];
        }
    }
}

void free_grid(Particle_t ***grid, int rows){
    for(int i = 0; i< rows;i++) {
        MemFree((*grid)[i]);
    }
    MemFree(*grid);
}
