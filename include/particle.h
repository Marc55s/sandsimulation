#include <stdbool.h>
#include <raylib.h>

#ifndef PARTICLE_H
#define PARTICLE_H
enum particle_type {
    EMPTY,
    SAND,
    WATER,
    STONE
};

enum state_type{
    LIQUID,
    GAS,
    SOLID
};

typedef struct particle{
    enum particle_type type;
    enum state_type state;
    bool isFalling;
    bool isLiquid;
    int dispersionRate;
    Color color;
} Particle_t;

void set_particle_in_grid(Particle_t **grid, int x, int y, Particle_t p);
void set_rectangle_in_grid(Particle_t **grid, Rectangle rect, Particle_t p);
void update_particle(Particle_t **nextGrid, int i,int j,int rows,int cols);
#endif
