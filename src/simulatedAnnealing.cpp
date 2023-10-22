#include "rubikscube.h"

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

array<array<array<int, 3>, 3>, 6> sampleNeighbour(array<array<array<int, 3>, 3>, 6> state, const vector<vector<string>> &formulae)
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

pair<array<array<array<int, 3>, 3>, 6>, vector<float>> simulatedAnnealing(
    array<array<array<int, 3>, 3>, 6> initialState,
    sampleFunc,
    energyFunc,
    betaFunc,
    int maxLength)
{
    // This function implements the simulated annealing algorithm.
    vector<float> energyList;
    // float energy = energyFunc(initialState);
    // array<array<array<int, 3>, 3>, 6> neighbour;
    // float neighbourEnergy;
    // float beta = betaFunc(0);
    // float proba;
    // float random;

    // // debug
    // cout << "SA starting, initial state energy is:" << energy << endl;

    // // SA algorithm
    // for (int length = 0; length < maxLength; length++)
    // {
    //     neighbour = sampleFunc(initialState);
    //     neighbourEnergy = energyFunc(neighbour);
    //     beta = betaFunc(length);

    //     // accept or reject
    //     proba = exp(beta * (energy - neighbourEnergy));
    //     uniform_real_distribution<float> dist(0., 1.);
    //     random = dist(rng);
    //     if (random < proba)
    //     {
    //         initialState = neighbour;
    //         energy = neighbourEnergy;
    //     }

    //     // debug
    //     cout << "Energy: " << energy << endl;

    //     energyList.push_back(energy);

    //     // break if solved
    //     if (energy == 0)
    //     {
    //         break;
    //     }
    // }

    return make_pair(initialState, energyList);
}