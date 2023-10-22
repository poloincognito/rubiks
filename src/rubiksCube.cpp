#include "rubikscube.h"

array<array<array<int, 3>, 3>, 6> parseRubiksCube(const string &filename)
{ // This function parse a Rubik's cube configuration from a txt file.

    // declare
    array<array<array<int, 3>, 3>, 6> cube;
    ifstream inputFile(filename);

    for (int row_idx = 0; row_idx < 3; ++row_idx)
    {
        // declare
        string line;
        getline(inputFile, line);

        istringstream iss(line);
        int num;

        for (int face = 0; face < 6; ++face)
        {
            for (int col = 0; col < 3; ++col)
            {
                iss >> num;
                cube[face][row_idx][col] = num;
            }
        }
    }

    return cube;
}

void printFace(const array<array<int, 3>, 3> &face)
{ // This function prints a face of a Rubik's cube.
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            cout << face[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printRubiksCube(const array<array<array<int, 3>, 3>, 6> &cube)
{ // This function prints a Rubik's cube configuration.
    for (int face = 0; face < 6; ++face)
    {
        printFace(cube[face]);
    }
}

void rotateFace(array<array<int, 3>, 3> &arr)
{
    array<int, 3> buffer = arr[0];
    // right to front
    for (int i = 0; i < 3; ++i)
    {
        arr[0][i] = arr[i][2];
    }
    // back to right
    for (int i = 0; i < 3; ++i)
    {
        arr[i][2] = arr[2][2 - i];
    }
    // left to back
    for (int i = 0; i < 3; ++i)
    {
        arr[2][2 - i] = arr[2 - i][0];
    }
    // front to left
    for (int i = 0; i < 3; ++i)
    {
        arr[2 - i][0] = buffer[i];
    }
}

void moveFunc(array<array<array<int, 3>, 3>, 6> &state, const vector<string> &moves)
{ // This function moves the Rubik's cube according to the given moves.
    for (const string &move : moves)
    {
        if (move == "F'")
        { // front counter-clockwise
            rotateFace(state[2]);
            auto buffer = state[1][2];
            state[1][2] = {state[0][2][2], state[0][1][2], state[0][0][2]};
            state[0][2][2] = state[3][0][0];
            state[0][1][2] = state[3][1][0];
            state[0][0][2] = state[3][2][0];
            state[3][0][0] = state[5][2][2];
            state[3][1][0] = state[5][2][1];
            state[3][2][0] = state[5][2][0];
            state[5][2][2] = buffer[0];
            state[5][2][1] = buffer[1];
            state[5][2][0] = buffer[2];
        }
        else if (move == "F")
        {
            vector<string> equivalent_move;
            for (int i = 0; i < 3; i++)
            {
                equivalent_move.push_back("F'");
            }
            moveFunc(state, equivalent_move);
        }
        else if (move == "B'")
        { // back counter-clockwise
            rotateFace(state[4]);
            auto buffer = state[0][0];
            state[0][0] = {state[1][0][2], state[1][0][1], state[1][0][0]};
            state[1][0][2] = state[5][2][0];
            state[1][0][1] = state[5][2][1];
            state[1][0][0] = state[5][2][2];
            state[5][2][0] = state[3][2][2];
            state[5][2][1] = state[3][2][1];
            state[5][2][2] = state[3][2][0];
            state[3][2][2] = buffer[0];
            state[3][2][1] = buffer[1];
            state[3][2][0] = buffer[2];
        }
        else if (move == "B")
        {
            vector<string> equivalent_move;
            for (int i = 0; i < 3; i++)
            {
                equivalent_move.push_back("B'");
            }
            moveFunc(state, equivalent_move);
        }
        else if (move == "L'")
        { // left counter-clockwise
            rotateFace(state[1]);
            auto buffer = state[4][2];
            state[4][2] = {state[0][0][0], state[0][1][0], state[0][2][0]};
            state[0][0][0] = state[2][0][0];
            state[0][1][0] = state[2][1][0];
            state[0][2][0] = state[2][2][0];
            state[2][0][0] = state[5][0][0];
            state[2][1][0] = state[5][1][0];
            state[2][2][0] = state[5][2][0];
            state[5][0][0] = buffer[0];
            state[5][1][0] = buffer[1];
            state[5][2][0] = buffer[2];
        }
        else if (move == "L")
        {
            vector<string> equivalent_move;
            for (int i = 0; i < 3; i++)
            {
                equivalent_move.push_back("L'");
            }
            moveFunc(state, equivalent_move);
        }
        else if (move == "R'")
        { // right counter-clockwise
            rotateFace(state[3]);
            auto buffer = state[0][2];
            state[0][2] = {state[4][0][0], state[4][1][0], state[4][2][0]};
            state[4][0][0] = state[5][0][2];
            state[4][1][0] = state[5][1][2];
            state[4][2][0] = state[5][2][2];
            state[5][0][2] = state[2][0][2];
            state[5][1][2] = state[2][1][2];
            state[5][2][2] = state[2][2][2];
            state[2][0][2] = buffer[0];
            state[2][1][2] = buffer[1];
            state[2][2][2] = buffer[2];
        }
        else if (move == "R")
        {
            vector<string> equivalent_move;
            for (int i = 0; i < 3; i++)
            {
                equivalent_move.push_back("R'");
            }
            moveFunc(state, equivalent_move);
        }
        else if (move == "U'")
        { // up counter-clockwise
            rotateFace(state[0]);
            auto buffer = state[2][0];
            state[2][0] = state[1][0];
            state[1][0] = state[4][0];
            state[4][0] = state[3][0];
            state[3][0] = buffer;
        }
        else if (move == "U")
        {
            vector<string> equivalent_move;
            for (int i = 0; i < 3; i++)
            {
                equivalent_move.push_back("U'");
            }
            moveFunc(state, equivalent_move);
        }
        else if (move == "D'")
        { // down counter-clockwise
            rotateFace(state[5]);
            auto buffer = state[2][2];
            state[2][2] = state[3][2];
            state[3][2] = state[4][2];
            state[4][2] = state[1][2];
            state[1][2] = buffer;
        }
        else if (move == "D")
        {
            vector<string> equivalent_move;
            for (int i = 0; i < 3; i++)
            {
                equivalent_move.push_back("D'");
            }
            moveFunc(state, equivalent_move);
        }
        else if (move == "E")
        {
            return;
        }
    }
}

void RubiksCube::move(const vector<string> &moves)
{
    moveFunc(state, moves);
}

void RubiksCube::print()
{
    printRubiksCube(state);
}

void RubiksCube::mix(int n)
{
    vector<vector<string>> elementary_moves;
    elementary_moves.push_back({"U"});
    elementary_moves.push_back({"D"});
    elementary_moves.push_back({"L"});
    elementary_moves.push_back({"R"});
    elementary_moves.push_back({"F"});
    elementary_moves.push_back({"B"});

    for (int i = 0; i < n; i++)
    {
        vector<string> random_move = sampleFormula(elementary_moves);
        move(random_move);
    }
}