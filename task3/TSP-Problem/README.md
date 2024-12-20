### Traveling Salesman Problem

This problem we will solve with the **Brute-Force algorithm** and the **Genetic algorithm**. 

The main idea of this problem: 
Given **n** cities with different **distances** among them and a designated first city, what is the least cost to visit all cities and return to the first one ?

#### Brute-Force algorithm
This algorithm systematically tries all possible permutations, ultimately computing the optimal answer. Runtime complexity can be estimated as O((n-1)!/2). We devides by 2, because we consider for simplicity the complete graph. 

#### Genetic algorithm
The basic idea that is used to solve this problem:
1. Choose the initial population of tours, so in our case, generate a set of permutations of the orderings of the cities
2. Evaluate the cost (distance) of each individual tour
3. Repeat until termination: 
	- Select best-ranking individuals 
	- Create additional tours through crossover, mutation or both (genetic operations) and give birth to offspring
	- Add new permutations to fill out the current generation
	- Evaluate the fitness of each individual tour

For mutations we will make a minor change (randomly swap 3 cities) to make a different version of an already good order.
In our project we will use termination way as we reach a fixed number of generations.

Runtime complexity can be estimated as O(n^2).

#### Notes
We will consider a complete graph in which all cities connect to all other. In my approach, there is a file *distances.txt*, which contains the weights of the edges between cities. To build graph we will use adjacency matrix (20x20) for 20 cities.
