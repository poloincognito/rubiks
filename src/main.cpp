#include "rubikscube.h"

// edge sampler
string edgeFormulaeFilename = "edge_formulae.txt";
vector<vector<string>> edgeFormulae = parseFormulae(edgeFormulaeFilename);
array<array<array<int, 3>, 3>, 6> sampleEdgeFunc(array<array<array<int, 3>, 3>, 6> state)
{
    return sampleNeighbour(state, edgeFormulae);
};
sampleFunc sampleEdge = &sampleEdgeFunc;

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
    cout << "Mixing the cube..." << endl;
    rubikscube.mix(20);
    rubikscube.print();

    // // energy
    // float e = edgeEnergy(rubikscube.state);
    // cout << endl
    //      << "Edge energy: " << e << endl
    //      << endl;

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

    // simulated annealing for edges
    int maxLength = 5000;
    pair<array<array<array<int, 3>, 3>, 6>, vector<float>> resultEdge = simulatedAnnealing(
        rubikscube.state,
        sampleEdge,
        edgeEnergy,
        edgeBetaFunc,
        maxLength);
    cout << "Simulated annealing for edges done." << endl;
    printRubiksCube(resultEdge.first);

    // export energy list for edges
    string exportEdgeFilename = "edge_energy.txt";
    exportEnergyList(resultEdge.second, exportEdgeFilename);

    // simulated annealing for corners
    pair<array<array<array<int, 3>, 3>, 6>, vector<float>> resultCorner = simulatedAnnealing(
        resultEdge.first,
        sampleEdge,
        cornerEnergy,
        edgeBetaFunc,
        maxLength);
    cout << "Simulated annealing for corners done." << endl;
    printRubiksCube(resultCorner.first);

    // export energy list for corners
    string exportCornerFilename = "corner_energy.txt";
    exportEnergyList(resultCorner.second, exportCornerFilename);
}