/* The game logic (no view code or direct user interaction
The game is a simple guess the word game. */


#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); // Constructor

    int32 GetMaxTries() const;
    int32 GetCurrentTry();
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;

    void Reset();
    FBullCowCount SubmitValidGuess(FString);

private:
// If initialised here we cannot change it in runtime
// See constructor for initialisation
    int32 MyCurrentTry; 
    FString MyHiddenWord;
    bool bGameIsWon;
    bool IsIsogram(FString) const;
    bool IsLowerCase (FString) const;
};