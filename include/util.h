#include "particle.h"

void copy_grid(Particle_t **src, Particle_t **dst, int row, int col);
void free_grid(Particle_t ***grid, int rows);
void init_grid(Particle_t ***grid);
void randomize_color(Color *color, double stddev);
