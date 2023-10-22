#include <chrono>

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
    // initialize
    string filename = "reference.txt";
    array<array<array<int, 3>, 3>, 6> cube = parseRubiksCube(filename);
    cout << "Cube successfully parsed." << endl;

    // mixing
    RubiksCube rubikscube;
    rubikscube.state = cube;
    cout << "Mixing the cube..." << endl
         << endl;
    rubikscube.mix(30);
    rubikscube.print();

    auto start = chrono::high_resolution_clock::now();

    // simulated annealing for edges
    int maxLength = 5000;
    pair<array<array<array<int, 3>, 3>, 6>, vector<float>> resultEdge = simulatedAnnealing(
        rubikscube.state,
        sampleEdge,
        edgeEnergy,
        edgeBetaFunc,
        maxLength);
    cout << "Simulated annealing for edges done." << endl
         << endl;
    printRubiksCube(resultEdge.first);

    // // export energy list for edges
    // string exportEdgeFilename = "edge_energy.txt";
    // exportEnergyList(resultEdge.second, exportEdgeFilename);

    // simulated annealing for corners
    pair<array<array<array<int, 3>, 3>, 6>, vector<float>> resultCorner = simulatedAnnealing(
        resultEdge.first,
        sampleCorner,
        cornerEnergy,
        edgeBetaFunc,
        maxLength);
    cout << "Simulated annealing for corners done." << endl
         << endl;
    printRubiksCube(resultCorner.first);

    auto stop = chrono::high_resolution_clock::now();

    // export energy list for corners
    string exportCornerFilename = "corner_energy.txt";
    exportEnergyList(resultCorner.second, exportCornerFilename);

    // print the execution time
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
}