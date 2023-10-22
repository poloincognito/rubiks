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
array<array<array<int, 3>, 3>, 6> parseRubiksCube(string &filename);
void printFace(array<array<int, 3>, 3> &face);
void printRubiksCube(array<array<array<int, 3>, 3>, 6> &cube);
void rotateFace(array<array<int, 3>, 3> &arr);
void moveFunc(array<array<array<int, 3>, 3>, 6> &state, vector<string> &moves);

class RubiksCube
{
public:
    array<array<array<int, 3>, 3>, 6> state;
    void move(vector<string> &moves);
    void print();
    void mix(int n);
};

// Simulated annealing
vector<vector<string>> parseFormulae(string &filename);
vector<string> sampleFormula(vector<vector<string>> &formulae);
void printFormula(vector<string>);
float computeEdgeEnergy(array<array<array<int, 3>, 3>, 6> &state);
array<array<array<int, 3>, 3>, 6> sampleNeighbour(array<array<array<int, 3>, 3>, 6> state, vector<vector<string>> &formulae);
float edgeBetaFunc(int idx);

pair<array<array<array<int, 3>, 3>, 6>, vector<float>> simulatedAnnealing(
    array<array<array<int, 3>, 3>, 6> initialState,
    array<array<array<int, 3>, 3>, 6> (*sampleFunc)(array<array<array<int, 3>, 3>, 6>),
    float (*energyFunc)(array<array<array<int, 3>, 3>, 6> &),
    float (*betaFunc)(int),
    int maxLength);

#endif