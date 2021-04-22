#ifndef CUBE_CUBE_HXX
#define CUBE_CUBE_HXX

#include <array>
#include "colour_side.hxx"
#include "slice.hxx"

class cube {
    // Stores the colours of all of the faces
    std::array<std::array<std::array<colour_side, 3>, 3>, 6> faces;
    // Stores all 6 slices for rotating
    std::array<slice, 6> slices;
    // Stores a map to get the colour letter (G, B, O, R, W, Y)
    std::array<char,  6> colours;
public:
    // Functions descriptions found in the .cxx file
    cube();
    void rotate(colour_side face, bool anti);
    void render();
};

#endif //CUBE_CUBE_HXX
