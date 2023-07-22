#include "CombinationGenerator.hpp"

/*Function to generate combinations of characters with the given length*/
CombinationGenerator combinations(const std::vector<char>& characters, int length) {
    // Initialize vectors to store the current combination and indices for characters
    std::vector<char> combination(length, ' '); // The current combination of characters
    std::vector<int> indices(length, 0); // Current indices for characters in the combination

    // Infinite loop to generate combinations
    while (true) {
        // Create the current combination using the current indices
        std::vector<char> current_combination;
        for (int i = 0; i < length; ++i) {
            current_combination.push_back(characters[indices[i]]);
        }

        // Yield the current combination to the calling coroutine
        co_yield current_combination;

        // Update indices to generate the next combination
        int i;
        for (i = length - 1; i >= 0 && indices[i] == static_cast<int>(characters.size()) - 1; --i) {
            indices[i] = 0; // Reset indices to zero if the current index reaches the last character in the characters vector
        }

        // Break out of the loop when all possible combinations have been generated
        if (i < 0) {
            break;
        }

        // Increment the index at position i to generate the next combination
        ++indices[i];
    }
}
