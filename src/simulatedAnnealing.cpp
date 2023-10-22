#include "rubikscube.h"

// Parsing formulae

vector<vector<string>> parseFormulae(const string &filename)
{
    // This function parse the edge swap and corner swap formulae exported by the notebook.

    // declare
    ifstream inputFile(filename);
    vector<vector<string>> formulae;
    string line;

    // iteration through the file
    while (getline(inputFile, line))
    {
        vector<string> tokens;
        istringstream tokenStream(line);
        string token;
        while (tokenStream >> token)
        {
            tokens.push_back(token);
        }
        formulae.push_back(tokens);
    }

    return formulae;
}

mt19937 rng(std::time(0));

vector<string> sampleFormula(const vector<vector<string>> &formulae)
{
    // This function samples a random formula from a list of formulae.
    uniform_int_distribution<size_t> dist(0, formulae.size() - 1);
    size_t randomIndex = dist(rng);
    return formulae[randomIndex];
}

void printFormula(const vector<string> formula)
{
    // This function concatenates and prints a formula.
    for (string str : formula)
    {
        std::cout << str << " ";
    }
}

// Energy functions

float computeEdgeEnergy(const array<array<array<int, 3>, 3>, 6> &state)
{
    float energy = 0.;
    for (int face = 0; face < 6; face++)
    {
        energy += state[face][0][1] != face;
        energy += state[face][1][0] != face;
        energy += state[face][1][2] != face;
        energy += state[face][2][1] != face;
    }
    return energy / (4 * 6);
}
energyFunc edgeEnergy = &computeEdgeEnergy;

float computeCornerEnergy(const array<array<array<int, 3>, 3>, 6> &state)
{
    float energy = 0.;
    for (int face = 0; face < 6; face++)
    {
        energy += state[face][0][0] != face;
        energy += state[face][2][2] != face;
        energy += state[face][0][2] != face;
        energy += state[face][2][0] != face;
    }
    return energy / (4 * 6);
}
energyFunc cornerEnergy = &computeCornerEnergy;

array<array<array<int, 3>, 3>, 6> sampleNeighbour(
    array<array<array<int, 3>, 3>, 6> state,
    const vector<vector<string>> &formulae)
{
    // This function samples a neighbour of a Rubik's cube state.
    vector<string> formula = sampleFormula(formulae);
    moveFunc(state, formula);
    return state;
}

float edgeBetaFunc(int idx)
{
    return sqrt(idx);
}

// Simulated annealing algorithm

pair<array<array<array<int, 3>, 3>, 6>, vector<float>> simulatedAnnealing(
    array<array<array<int, 3>, 3>, 6> initialState,
    sampleFunc sample,
    energyFunc computeEnergy,
    betaFunc beta,
    int maxLength)
{
    // This function implements the simulated annealing algorithm.
    vector<float> energyList;
    float energy = computeEnergy(initialState);
    array<array<array<int, 3>, 3>, 6> neighbour;
    float neighbourEnergy;
    float current_beta = beta(0);
    float proba;
    float random;

    // debug
    cout << "SA starting, initial state energy is: " << energy << endl;

    // SA algorithm
    for (int length = 0; length < maxLength; length++)
    {
        neighbour = sample(initialState);
        neighbourEnergy = computeEnergy(neighbour);
        current_beta = beta(length);

        // accept or reject
        proba = exp(current_beta * (energy - neighbourEnergy));
        uniform_real_distribution<float> dist(0., 1.);
        random = dist(rng);
        if (random < proba)
        {
            initialState = neighbour;
            energy = neighbourEnergy;
        }

        energyList.push_back(energy);

        // break if solved
        if (energy == 0)
        {
            cout << "Solved in " << length << " steps." << endl;
            break;
        }
    }

    return make_pair(initialState, energyList);
}

void exportEnergyList(const vector<float> &energyList, const string &filename)
{
    // This function exports the energy list to a file.
    ofstream outputFile(filename);
    for (float energy : energyList)
    {
        outputFile << energy << endl;
    }
}