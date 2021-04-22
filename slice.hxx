#ifndef CUBE_SLICE_HXX
#define CUBE_SLICE_HXX

#include <array>
#include <memory>

#include "colour_side.hxx"

class slice {
    // Structure used to store the rotation groups
    struct rot_group {
        colour_side* p0;
        colour_side* p1;
        colour_side* p2;
        colour_side* p3;
        bool set;
    };
    // Stores all 5 rotation groups for this slice
    std::array<rot_group, 5> rotations;
    // Counter to limit to only 5 rotation groups
    int curr;
public:
    // Functions descriptions found in the .cxx file
    void add(colour_side& p0, colour_side& p1, colour_side& p2, colour_side& p3);
    void rotate(bool anti);
};

#endif //CUBE_SLICE_HXX
