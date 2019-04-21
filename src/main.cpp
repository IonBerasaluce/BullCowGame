/*
This is the console executable that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is reponsible for all user interaction.
For game logic see the FBullCowGame.cpp
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// instantate a new game, we need global access to the game.
FBullCowGame BCGame;

int main() {

    // Run the main logic
    do{
        // Introduce the game
        PrintIntro();
        PlayGame();
    }
    while(AskToPlayAgain());

    return 0;
}

// Print the intro to the program
void PrintIntro(){
    const int WordLength = BCGame.GetHiddenWordLength();
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << WordLength;
    std::cout << " letter isogram I'm thinking of?\n" << std::endl;
    return;
}
//Plays a single game to completion
void PlayGame(){

    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        // Get the guesses from the user
        FText Guess = GetValidGuess();

        // Submit a valid guess to the game and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        // print the number of bulls and cows
        std::cout << "Number of Bulls: " << BullCowCount.Bulls << "! ";
        std::cout << "Number of Cows: " << BullCowCount.Cows << "!\n\n";
    }

    // Add a summary of the game here
    PrintGameSummary();
    return;
}

// Get the guess from the player
FText GetValidGuess(){
    
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        int32 Attempt = BCGame.GetCurrentTry();
        std::cout << "Try " << Attempt << " of " << BCGame.GetMaxTries(); 
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);

        // Check the user input
        Status = BCGame.CheckGuessValidity(Guess);
        switch(Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter an isogram.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter the word in lowercase letters.\n\n";
                break;
            default:
                break;
            }
    } while (Status != EGuessStatus::OK);
    return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "WELL DONE - YOU WIN!\n";
    } else {
        std::cout << "Better luck next time!\n";
    }
}

