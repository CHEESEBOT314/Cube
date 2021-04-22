#include "slice.hxx"

// Add a rotation set, these four variables map onto each other
void slice::add(colour_side &p0, colour_side &p1, colour_side &p2, colour_side &p3) {
    // Each slice only rotates 5 groups of 4 sub faces
    if (curr > 4) {
        return;
    }
    // Store the pointers to each sub face instead for easy manipulation
    rotations[curr] = {&p0, &p1, &p2, &p3, true};
    curr++;
}

// Rotate depending on direction
void slice::rotate(bool anti) {
    for (auto& r : rotations) {
        if (r.set) {
            // Swap the 4 values around in the correct direction
            colour_side temp = *r.p0;
            if (anti) {
                *r.p0 = *r.p1;
                *r.p1 = *r.p2;
                *r.p2 = *r.p3;
                *r.p3 = temp;
            }
            else {
                *r.p0 = *r.p3;
                *r.p3 = *r.p2;
                *r.p2 = *r.p1;
                *r.p1 = temp;
            }
        }
    }
}