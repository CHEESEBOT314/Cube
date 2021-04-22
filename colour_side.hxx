#ifndef CUBE_COLOUR_SIDE_HXX
#define CUBE_COLOUR_SIDE_HXX

#include <cstdint>

// Defines a way of designating each colour and face to a common number
enum colour_side : uint8_t {
    G_F = 0,
    B_B = 1,
    O_L = 2,
    R_R = 3,
    W_U = 4,
    Y_D = 5
};

#endif //CUBE_COLOUR_SIDE_HXX
