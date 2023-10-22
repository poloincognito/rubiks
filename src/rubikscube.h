#ifndef RUBIKS_H
#define RUBIKS_H

#include <array>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

// Rubik's cube
array<array<array<int, 3>, 3>, 6> parseRubiksCube(const string &filename);
void printFace(const array<array<int, 3>, 3> &face);
void printRubiksCube(const array<array<array<int, 3>, 3>, 6> &cube);
void rotateFace(array<array<int, 3>, 3> &arr);
void moveFunc(array<array<array<int, 3>, 3>, 6> &state, const vector<string> &moves);

class RubiksCube
{
public:
    array<array<array<int, 3>, 3>, 6> state;
    void move(const vector<string> &moves);
    void print();
    void mix(int n);
};

// Simulated annealing
vector<vector<string>> parseFormulae(const string &filename);
vector<string> sampleFormula(const vector<vector<string>> &formulae);
void printFormula(const vector<string>);
array<array<array<int, 3>, 3>, 6> sampleNeighbour(array<array<array<int, 3>, 3>, 6> state, const vector<vector<string>> &formulae);
float edgeBetaFunc(int idx);

// typedef for energy and sample functions
typedef array<array<array<int, 3>, 3>, 6> (*sampleFunc)(array<array<array<int, 3>, 3>, 6>);
typedef float (*energyFunc)(const array<array<array<int, 3>, 3>, 6> &);
typedef float (*betaFunc)(int);
extern energyFunc edgeEnergy;

pair<array<array<array<int, 3>, 3>, 6>, vector<float>> simulatedAnnealing(
    array<array<array<int, 3>, 3>, 6> initialState,
    sampleFunc,
    energyFunc,
    betaFunc,
    int maxLength);

#endif