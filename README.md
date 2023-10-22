# Rubik's cube

This project solves the Rubik's cube using simulated annealing, which seems possible (https://www.mecs-press.org/ijeme/ijeme-v8-n1/IJEME-V8-N1-1.pdf, https://doi.org/10.1016/j.cpc.2012.03.003). This project does not use the quickest algorithm (check Korf's algorithm, or https://en.wikipedia.org/wiki/Optimal_solutions_for_the_Rubik%27s_Cube), nor the most efficient data structure.

A notebook details the python prototype and proof of concept. The project was then implemented in C++.

There are two purposes:
- **A practical one:** Practicing programing, reimplementing simulated annealing, exploring data structures for the Rubik's cube, using C++.
- **A playful one:** There's a mathematical twist to this project: the Rubik's cube will be mixed and unmixed using the same principle, convergence to the stationary distribution of a Markov chain (only the transition matrix differs). This limit distribution is the uniform distribution when mixing with equiprobable moves, and it becomes $\frac{e^{-\beta E(x)}}{Z(\beta)}$ during the simulated annealing process ($E(x)$ being the *energy* function or *fit* function of the state). As $\beta$ augments, the limit distribution becomes $\delta_{x_{solved}}$.

## Example

**The python implementation takes approximately 4 seconds to run, whereas the C++ implementation runs in 0,182 seconds.**

Example of a run:

        Cube successfully parsed.
        Mixing the cube...       

            1 3 1
            2 0 3
            2 1 1

        5 1 5  3 4 5  2 5 0  4 2 4
        4 1 2  5 2 4  3 3 1  5 4 5
        4 0 5  3 0 3  2 0 2  1 2 0

            4 1 0
            4 5 3
            3 0 0

        SA starting, initial state energy is: 0.916667
        Solved in 4179 steps.
        Simulated annealing for edges done.

            0 0 0
            0 0 0
            0 0 2

        3 1 3  4 2 5  3 3 4  1 4 2
        1 1 1  2 2 2  3 3 3  4 4 4
        1 1 1  2 2 1  0 3 4  5 4 4

            5 5 2
            5 5 5
            5 5 3

        SA starting, initial state energy is: 0.583333
        Solved in 530 steps.
        Simulated annealing for corners done.

            0 0 0
            0 0 0
            0 0 0

        1 1 1  2 2 2  3 3 3  4 4 4
        1 1 1  2 2 2  3 3 3  4 4 4
        1 1 1  2 2 2  3 3 3  4 4 4

            5 5 5
            5 5 5
            5 5 5
        
        Time taken by function: 182296 microseconds

![SA for edges](/figures/edges.png)

![SA for corners](/figures/corners.png)