# GeneticOptimization
This repository provides tools for genetic optimization. To use it, include `OptimizationRun.h` in your project and define your own `OptimizationCase` (you must implement the abstract class).

`OptimizationRun` can be constructed in four ways, with three offering more configuration possibilities. One option allows you to choose between fixed configurations of the optimizer and stopping criteria.

To customize the configurations, you must implement the appropriate classes and methods. However, if you prefer to use pre-configured settings, you can provide the index of `ARRANGEMENT_CONSTRUCTOR`, which can be found in `OptimizationRun.h`.

## Classical Genetic Algorithm
This is a classical conceptual implementation of genetic algorithms, where genotypes are divided into two continuous parts. Mutations are included, and their probability is regulated by the appropriate parameters.

## Parameter-less Population Pyramid (P3)
This optimizer is an implementation of the algorithm presented in the paper:

> Goldman, Brian W., and William F. Punch. "Parameter-less population pyramid." *Proceedings of the 2014 Annual Conference on Genetic and Evolutionary Computation*, 2014.

The algorithm utilizes a pyramid-like population structure, greedy optimization, and gene linkage learning (to improve crossover efficiency). The optimizer does not require parameters and only needs a case to solve.
