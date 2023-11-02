#include <iostream>
#include <vector>
using namespace std;
// Function to generate all permutations recursively
void generatePermutations(std::vector<int>& elements, int index) {
    cout<<"index : "<<index<<endl;
    if (index == elements.size()) {
        // Print the current permutation
        for (int num : elements) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        return;
    }

    for (int i = index; i < elements.size(); i++) {
        // Swap elements[index] with elements[i]
        std::swap(elements[index], elements[i]);

        // Recursively generate permutations for the remaining elements
        generatePermutations(elements, index + 1);

        // Restore the original order (backtracking)
        std::swap(elements[index], elements[i]);
    }
}

int main() {
    std::vector<int> elements = {0, 1, 2, 3};

    // Generate all permutations starting from index 0
    generatePermutations(elements, 0);

    return 0;
}
