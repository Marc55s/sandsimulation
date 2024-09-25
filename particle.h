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
} particle_t;
