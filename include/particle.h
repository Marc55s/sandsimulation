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
#endif
