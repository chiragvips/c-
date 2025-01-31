#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

// Function to convert numeric choice to string
std::string getChoiceName(int choice) {
    switch (choice) {
        case 1: return "Rock";
        case 2: return "Paper";
        case 3: return "Scissors";
        default: return "Invalid";
    }
}

// Function to determine the winner
std::string determineWinner(int playerChoice, int computerChoice) {
    if (playerChoice == computerChoice) {
        return "It's a tie!";
    } else if ((playerChoice == 1 && computerChoice == 3) ||
               (playerChoice == 2 && computerChoice == 1) ||
               (playerChoice == 3 && computerChoice == 2)) {
        return "You win!";
    } else {
        return "Computer wins!";
    }
}

void playGame() {
    int playerChoice, computerChoice;

    // Initialize random seed:
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "Welcome to Rock, Paper, Scissors!\n";
    std::cout << "1. Rock\n2. Paper\n3. Scissors\n";

    // Player makes a choice
    std::cout << "Enter your choice (1-3): ";
    std::cin >> playerChoice;

    // Generate computer's choice
    computerChoice = rand() % 3 + 1;

    std::cout << "You chose: " << getChoiceName(playerChoice) << "\n";
    std::cout << "Computer chose: " << getChoiceName(computerChoice) << "\n";

    // Determine the winner
    std::cout << determineWinner(playerChoice, computerChoice) << "\n";
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

