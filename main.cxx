#include <iostream>
#include <sstream>
#include "cube.hxx"

int main() {
    // Initialise the cube
    cube c;
    // Instructions
    std::cout << "Please enter a valid rotation using F, B, L, R, U, D with/without ' to rotate the cube. Use Q to quit the application.\n";
    // Variable to store the input
    std::string in;
    // Keep going until the application is quit
    while (true) {
        c.render();
        std::cout << "Input: ";
        getline(std::cin, in);
        // Valid inputs are only 1 or 2 chars in length
        if (in.size() < 3) {
            // Input must be size 1 or the second char mush be a ' for anticlockwise rotation
            if (in.size() == 1 || in.at(1) == '\'') {
                bool quit = false;
                bool invalid = false;
                colour_side side;
                // Get the side of rotation
                switch (in.at(0)) {
                    case 'Q':
                        // Used to quit
                        if (in.size() == 1) {
                            quit = true;
                        }
                        else {
                            // Q should only be by itself
                            invalid = true;
                        }
                        break;
                    case 'F':
                        side = G_F;
                        break;
                    case 'B':
                        side = B_B;
                        break;
                    case 'L':
                        side = O_L;
                        break;
                    case 'R':
                        side = R_R;
                        break;
                    case 'U':
                        side = W_U;
                        break;
                    case 'D':
                        side = Y_D;
                        break;
                    default:
                        // Not a valid input
                        invalid = true;
                        break;
                }
                if (!invalid) {
                    // Valid input
                    if (quit) {
                        // Quitting
                        break;
                    }
                    std::cout << "Rotating cube!\n";
                    c.rotate(side, in.size() == 2);
                    // Avoid the cout statement below
                    continue;
                }
            }
        }
        std::cout << "Invalid input, please try again!\n";
    }
    std::cout << "Application quitting!\n";

    // Finished
    return 0;
}
