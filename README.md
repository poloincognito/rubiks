# Rubik's cube

This project solves the Rubik's cube using simulated annealing, which seems possible (https://www.mecs-press.org/ijeme/ijeme-v8-n1/IJEME-V8-N1-1.pdf, https://doi.org/10.1016/j.cpc.2012.03.003). This project does not use the quickest algorithm (check Korf's algorithm, or https://en.wikipedia.org/wiki/Optimal_solutions_for_the_Rubik%27s_Cube), nor the most efficient data structure.

A notebook details the python prototype and proof of concept. The project was then implemented in C++.

There are two purposes:
- **A practical one:** Practicing programing, reimplementing simulated annealing, exploring data structures for the Rubik's cube, using C++.
- **A playful one:** There's a mathematical twist to this project: the Rubik's cube will be mixed and unmixed using the same principle, convergence to the stationary distribution of a Markov chain (only the transition matrix differs). This limit distribution is the uniform distribution when mixing with equiprobable moves, and it becomes $\frac{e^{-\beta E(x)}}{Z(\beta)}$ during the simulated annealing process ($E(x)$ being the *energy* function or *fit* function of the state). As $\beta$ augments, the limit distribution becomes $\delta_{x_{solved}}$.
