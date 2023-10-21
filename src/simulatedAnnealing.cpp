#include <array>
#include <string>

#include "rubikscube.h"

using namespace std;

int main()
{
    string filename = "test.txt";
    array<array<array<int, 3>, 3>, 6> cube = parseRubiksCube(filename);

    // print
    printRubiksCube(cube);
    // cout << "Cube successfully parsed !" << endl;

    // // print face
    // array<array<int, 3>, 3> face = cube[0];
    // face[0][0] = 1;
    // printFace(face);

    // // rotate
    // rotateFace(face);
    // printFace(face);
    // cout << "Face successfully rotated !" << endl;

    // move
    vector<string> move;
    move.push_back("F'");
    moveFunc(cube, move);
    printRubiksCube(cube);
}