#include "rubikscube.h"

// edge sampler
string edgeFormulaeFilename = "edge_formulae.txt";
vector<vector<string>> edgeFormulae = parseFormulae(edgeFormulaeFilename);
array<array<array<int, 3>, 3>, 6> sampleEdge(array<array<array<int, 3>, 3>, 6> state)
{
    return sampleNeighbour(state, edgeFormulae);
};

// corner sampler
string cornerFormulaeFilename = "corner_formulae.txt";
vector<vector<string>> cornerFormulae = parseFormulae(cornerFormulaeFilename);
array<array<array<int, 3>, 3>, 6> sampleCorner(array<array<array<int, 3>, 3>, 6> state)
{
    return sampleNeighbour(state, cornerFormulae);
};

int main()
{
    string filename = "reference.txt";
    array<array<array<int, 3>, 3>, 6> cube = parseRubiksCube(filename);

    // print
    printRubiksCube(cube);
    cout << endl
         << "Cube successfully parsed !" << endl
         << endl;

    // mixing
    RubiksCube rubikscube;
    rubikscube.state = cube;
    rubikscube.mix(20);
    rubikscube.print();

    // energy
    float e = computeEdgeEnergy(rubikscube.state);
    cout << endl
         << "Edge energy: " << e << endl
         << endl;

    // // print face
    // array<array<int, 3>, 3> face = cube[0];
    // face[0][0] = 1;
    // printFace(face);

    // // rotate
    // rotateFace(face);
    // printFace(face);
    // cout << "Face successfully rotated !" << endl;

    // // move
    // vector<string> move;
    // move.push_back("F'");
    // moveFunc(cube, move);
    // printRubiksCube(cube);

    // formulae
    vector<string> formula = sampleFormula(edgeFormulae);
    printFormula(formula);
    cout << endl
         << "Formula successfully sampled !" << endl
         << endl;

    // neighbour
    array<array<array<int, 3>, 3>, 6> neighbour = sampleNeighbour(rubikscube.state, edgeFormulae);
    printRubiksCube(neighbour);
    cout << "Neighbour successfully sampled !" << endl
         << endl;
    rubikscube.print();

    // // simulated annealing
    // int maxLength = 3000;
    // pair<array<array<array<int, 3>, 3>, 6>, vector<float>> result = simulatedAnnealing(
    //     rubikscube.state,
    //     sampleEdge,
    //     computeEdgeEnergy,
    //     edgeBetaFunc,
    //     maxLength);
    // cout << "Simulated annealing done !" << endl;
    // printRubiksCube(result.first);
}