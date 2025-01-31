#include <iostream>
#include <cstdlib>  // For srand() and rand()
#include <ctime>    // For time()

void playGame() {
    // Initialize random seed:
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100:
    int numberToGuess = rand() % 100 + 1;
    int playerGuess = 0;
    int numberOfTries = 0;

    std::cout << "Welcome to 'Guess the Number' game!\n";
    std::cout << "I'm thinking of a number between 1 and 100.\n";

    // Game loop:
    while (playerGuess != numberToGuess) {
        std::cout << "Enter your guess: ";
        std::cin >> playerGuess;

        numberOfTries++;

        if (playerGuess > numberToGuess) {
            std::cout << "Too high! Try again.\n";
        } else if (playerGuess < numberToGuess) {
            std::cout << "Too low! Try again.\n";
        } else {
            std::cout << "Congratulations! You guessed the number in " << numberOfTries << " tries.\n";
        }
    }
}

int main() {
    char playAgain = 'y';
    while (playAgain == 'y') {
        playGame();
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}

