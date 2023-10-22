#include "rubikscube.h"

// int main()
// {
//     string filename = "reference.txt";
//     array<array<array<int, 3>, 3>, 6> cube = parseRubiksCube(filename);

//     // print
//     printRubiksCube(cube);
//     cout << "Cube successfully parsed !" << endl
//          << endl;

//     // mixing
//     RubiksCube rubikscube;
//     rubikscube.state = cube;
//     cout << "Mixing the cube..." << endl
//          << endl;
//     rubikscube.mix(30);
//     rubikscube.print();

// // rotate face
// array<array<int, 3>, 3> face = rubikscube.state[0];
// cout << "Rotating the face 0" << endl
//      << endl;
// rotateFace(face);
// printFace(face);

// // elementary move
// vector<string> moves;
// moves.push_back("U'");
// cout << "Moving the cube by U'" << endl
//      << endl;
// rubikscube.move(moves);
// rubikscube.print();

// // energy
// float e = edgeEnergy(rubikscube.state);
// cout << endl
//      << "Edge energy: " << e << endl
//      << endl;

// // formulae
// vector<vector<string>> edgeFormulae = parseFormulae("edge_formulae.txt");
// vector<string> formula = sampleFormula(edgeFormulae);
// printFormula(formula);
// cout << endl
//      << "Formula successfully sampled !" << endl
//      << endl;

// // neighbour
// array<array<array<int, 3>, 3>, 6> neighbour = sampleNeighbour(rubikscube.state, edgeFormulae);
// printRubiksCube(neighbour);
// cout << "Neighbour successfully sampled !" << endl
//      << endl;
// rubikscube.print();
//}