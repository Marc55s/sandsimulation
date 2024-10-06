#include "../include/util.h"
#include "../include/config.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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

double generateGaussianNoise(double mean, double stddev) {
    static int hasSpare = 0;
    static double spare;
    
    if (hasSpare) {
        hasSpare = 0;
        return mean + stddev * spare;
    }

    hasSpare = 1;
    double u, v, s;
    do {
        u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    s = sqrt(-2.0 * log(s) / s);
    spare = v * s;
    return mean + stddev * (u * s);
}

void randomize_color(Color *color, double stddev){
    double mean = 0;
    // Add Gaussian noise to each color channel
    int noise_r = (int)(generateGaussianNoise(mean, stddev));
    int noise_g = (int)(generateGaussianNoise(mean, stddev));
    int noise_b = (int)(generateGaussianNoise(mean, stddev));

    // Adjust and clamp the RGB values carefully to avoid extreme changes
    if (color->r + noise_r < 0) {
        color->r = 0;
    } else if (color->r + noise_r > 255) {
        color->r = 255;
    } else {
        color->r += noise_r;
    }

    if (color->g + noise_g < 0) {
        color->g = 0;
    } else if (color->g + noise_g > 255) {
        color->g = 255;
    } else {
        color->g += noise_g;
    }

    if (color->b + noise_b < 0) {
        color->b = 0;
    } else if (color->b + noise_b > 255) {
        color->b = 255;
    } else {
        color->b += noise_b;
    }
    //TraceLog(LOG_INFO, "%d",noise_b);
}
