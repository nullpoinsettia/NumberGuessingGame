//---------------------------------------------
// Number Guessing Game by nullpoinsettia
//---------------------------------------------
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <fstream> // for file handling

// file name where high score will be kept
const std::string ScoreFile = "highscore.txt";

// function to get high score from file
int getHighScore()
{
    std::ifstream file(ScoreFile);
    int highScore = 0;

    if (file.is_open()){
        file >> highScore;
        file.close();
    }
    return highScore; // returns 0 if file doesn't exist or is empty
}

// function to save high score to the file
void saveHighScore(int newScore){
    std::ofstream file(ScoreFile);
    if (file.is_open()) {
        file << newScore;
        file.close();
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    char playAgain;

    std::cout << "========================================\n";
    std::cout << "     WELCOME TO THE GUESSING GAME       \n";
    std::cout << "========================================\n";

    // main game loop
    do {
        int randomNumber = (std::rand() % 20) + 1;
        int userGuess = 0;
        int attempts = 0;
        int currentHighScore = getHighScore();

        if (currentHighScore == 0){
        std::cout << "There is currently no record set. Start playing to show everyone how good you are!\n";
        }
        else {
            std::cout << "Current record is: " << currentHighScore << "! Let's see if you can beat it!\n";
        }

        std::cout << "I have chosen a random number between 1 and 20!\n";



        while (userGuess != randomNumber){
            std::cout << "Enter your guess: ";
            std:: cin >> userGuess;

            if (std::cin.fail()){
                std::cin.clear(); // clears error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                std::cout << "Invalid input, please enter a number.\n";
                continue;
            }
            
            attempts++;

            if (userGuess > randomNumber) {
                std::cout << "Too high! Try a lower number!\n";
            } else if (userGuess < randomNumber){
                std::cout << "Too low! Try a higher number!\n";
            } else {
                std::cout << "Congratulations! You found the number!\n";
                std::cout << "It took you " << attempts << " attempts\n";

                // check for a new high score (fewer attempts is better)
                if (currentHighScore == 0 || attempts < currentHighScore){
                    std::cout << "NEW HIGH SCORE\n";
                    std::cout << "You beat the record of " << currentHighScore << " attempts!\n";
                    saveHighScore(attempts);
                }
                else {
                    std::cout << "Nice try! The record remains " << currentHighScore << " attempts!\n";
                }
            }
        }
    // ask the user if they want to play another round
    std::cout << "\nWould you like to play again? (y/any key to escape) ";
    std::cin >> playAgain;
} while (playAgain == 'y' || playAgain == 'Y');

std::cout << "\nThank you for playing! See ya!\n";

    return 0;
}