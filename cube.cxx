#include <iostream>
#include "cube.hxx"

// Anonymous namespace for 'hiding' functions out of the global scope
namespace {
    // Add default slice rotations for the given face, all slices are the same (corners go to corners and edges go to edges)
    void add_defaults(slice& s, std::array<std::array<colour_side, 3>, 3>& face) {
        s.add(face[0][0], face[2][0], face[2][2], face[0][2]); // Corners
        s.add(face[1][0], face[2][1], face[1][2], face[0][1]); // Edges
    }
    // Add other slice rotations on the 4 neighbouring faces. Sub faces given in a clockwise direction.
    // This function reduces the size of code for initialising the slices
    void add_outer(slice& s,
                   std::array<std::array<colour_side, 3>, 3>& face0, int e00x, int e00y, int e01x, int e01y, int e02x, int e02y,
                   std::array<std::array<colour_side, 3>, 3>& face1, int e10x, int e10y, int e11x, int e11y, int e12x, int e12y,
                   std::array<std::array<colour_side, 3>, 3>& face2, int e20x, int e20y, int e21x, int e21y, int e22x, int e22y,
                   std::array<std::array<colour_side, 3>, 3>& face3, int e30x, int e30y, int e31x, int e31y, int e32x, int e32y) {

        s.add(face0[e00x][e00y], face1[e10x][e10y], face2[e20x][e20y], face3[e30x][e30y]); // Corners
        s.add(face0[e01x][e01y], face1[e11x][e11y], face2[e21x][e21y], face3[e31x][e31y]); // Edges
        s.add(face0[e02x][e02y], face1[e12x][e12y], face2[e22x][e22y], face3[e32x][e32y]); // Corners
    }
    // Render the face onto the 2D array for console output, convert the enum to the colour letter as well
    void render_face(std::array<std::array<char, 13>, 9>& out, int x, int y, std::array<std::array<colour_side, 3>, 3>& face, const std::array<char, 6>& converter) {
        for (int i = 0; i < face.size(); i++) {
            auto& col = face[i];
            for (int j = 0; j < col.size(); j++) {
                out[y + j][x + i] = converter[col[j]];
            }
        }
    }
    // Fill the 3x3 space with '.'s
    void add_space(std::array<std::array<char, 13>, 9>& out, int x, int y) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                out[y + j][x + i] = '.';
            }
        }
    }
};
// Initialise the cube, firstly the faces and then the slices
cube::cube() : faces(), slices(), colours({'G', 'B', 'O', 'R', 'W', 'Y'}) {
    // Set each face to a single colour by default
    for (int i = 0; i < faces.size(); i++) {
        auto& face = faces[i];
        for (auto& col : face) {
            for (auto& e : col) {
                e = (colour_side)i;
            }
        }
        // Add default slice rotations for each face
        add_defaults(slices[i], faces[i]);
    }

    // Add outer rotations for the front face
    add_outer(slices[G_F],
              faces[O_L], 2, 2, 2, 1, 2, 0,
              faces[W_U], 0, 2, 1, 2, 2, 2,
              faces[R_R], 0, 0, 0, 1, 0, 2,
              faces[Y_D], 2, 0, 1, 0, 0, 0);
    // Add outer rotations for the back face
    add_outer(slices[B_B],
              faces[R_R], 2, 2, 2, 1, 2, 0,
              faces[W_U], 2, 0, 1, 0, 0, 0,
              faces[O_L], 0, 0, 0, 1, 0, 2,
              faces[Y_D], 0, 2, 1, 2, 2, 2);
    // Add outer rotations for the left face
    add_outer(slices[O_L],
              faces[G_F], 0, 0, 0, 1, 0, 2,
              faces[Y_D], 0, 0, 0, 1, 0, 2,
              faces[B_B], 2, 2, 2, 1, 2, 0,
              faces[W_U], 0, 0, 0, 1, 0, 2);
    // Add outer rotations for the right face
    add_outer(slices[R_R],
              faces[G_F], 2, 2, 2, 1, 2, 0,
              faces[W_U], 2, 2, 2, 1, 2, 0,
              faces[B_B], 0, 0, 0, 1, 0, 2,
              faces[Y_D], 2, 2, 2, 1, 2, 0);
    // Add outer rotations for the up face
    add_outer(slices[W_U],
              faces[G_F], 2, 0, 1, 0, 0, 0,
              faces[O_L], 2, 0, 1, 0, 0, 0,
              faces[B_B], 2, 0, 1, 0, 0, 0,
              faces[R_R], 2, 0, 1, 0, 0, 0);
    // Add outer rotations for the down face
    add_outer(slices[Y_D],
              faces[G_F], 0, 2, 1, 2, 2, 2,
              faces[R_R], 0, 2, 1, 2, 2, 2,
              faces[B_B], 0, 2, 1, 2, 2, 2,
              faces[O_L], 0, 2, 1, 2, 2, 2);
}
// Function to rotate the given face, calls the method in the correct slice
void cube::rotate(colour_side face, bool anti) {
    slices[face].rotate(anti);
}

// Render the cube to the console, each face has a default offset
void cube::render() {
    std::array<std::array<char, 13>, 9> out = {};
    // Use this function to reduce the code size
    render_face(out, 3, 3, faces[G_F], colours);
    render_face(out, 9, 3, faces[B_B], colours);
    render_face(out, 0, 3, faces[O_L], colours);
    render_face(out, 6, 3, faces[R_R], colours);
    render_face(out, 3, 0, faces[W_U], colours);
    render_face(out, 3, 6, faces[Y_D], colours);

    // Fill in the remaining spaces
    add_space(out, 0, 0);
    add_space(out, 0, 6);
    add_space(out, 6, 0);
    add_space(out, 6, 6);
    add_space(out, 9, 0);
    add_space(out, 9, 6);

    // Print each line one by one with a newline
    for (auto& line : out) {
        std::cout << line.data() << std::endl;
    }
}