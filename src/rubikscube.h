#ifndef RUBIKS_H
#define RUBIKS_H

#include <array>
#include <string>
#include <vector>

using namespace std;

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
};

#endif