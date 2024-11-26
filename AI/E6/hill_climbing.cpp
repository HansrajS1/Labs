#include <iostream>
#include <cstdlib>
#include <ctime>
int objective_function(int solution[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += solution[i];
    }
    return sum;
}
void generate_neighbor(int solution[], int size) {
    int index = rand() % size;
    solution[index] = 1 - solution[index]; 
}
void hill_climbing(int solution[], int size, int& best_fitness, int max_iterations = 1000) {
    for (int i = 0; i < size; ++i) {
        solution[i] = rand() % 2;
    }
    best_fitness = objective_function(solution, size);
    for (int iteration = 0; iteration < max_iterations; ++iteration) {
        int neighbor[size];
        for (int i = 0; i < size; ++i) {
            neighbor[i] = solution[i];
        }
        generate_neighbor(neighbor, size);
        int neighbor_fitness = objective_function(neighbor, size);
        if (neighbor_fitness >= best_fitness) {
            for (int i = 0; i < size; ++i) {
                solution[i] = neighbor[i];
            }
            best_fitness = neighbor_fitness;
        } else {
            break; 
        }
    }
}
int main() {
    srand(static_cast<unsigned int>(time(0))); 
    const int size = 10;
    int best_solution[size];
    int best_fitness = 0;
    hill_climbing(best_solution, size, best_fitness);
    std::cout << "Best Solution: ";
    for (int i = 0; i < size; ++i) {
        std::cout << best_solution[i] << " ";
    }
    std::cout << "\nBest Fitness: " << best_fitness << std::endl;
    return 0;
}
