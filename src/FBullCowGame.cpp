#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); } // Default Constructor

// Public Getters
int32 FBullCowGame::GetCurrentTry(){ return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
    TMap<int32, int32> WordLengthToMaxTries {{3,4}, {4,7}, {5,10}, {6,16}, {7,20}};
    return WordLengthToMaxTries[GetHiddenWordLength()]; 
}

void FBullCowGame::Reset() {
    // This must be an isogram
    const FString HIDDEN_WORD = "planet";

    MyHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
    MyCurrentTry = 1;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
    if (!IsIsogram(Guess)){ 
        return EGuessStatus::Not_Isogram; 
    }
    else if (Guess.length() != MyHiddenWord.length()){ 
        return EGuessStatus::Wrong_Length; 
    }
    else if (!IsLowerCase(Guess)){ 
        return EGuessStatus::Not_Lowercase; 
    }
    else { 
        return EGuessStatus::OK; 
    }
}

// Receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
    MyCurrentTry++;
    FBullCowCount BullCowCount;

    int32 HiddenWordLength = MyHiddenWord.length();
    // loop through all letters in the guess 
    for (int32 i = 0; i < HiddenWordLength; i++){
        // If the character in the guess is in the word
        if (MyHiddenWord.find(Guess[i]) != FString::npos){
            // If the character is in the same position
            if (MyHiddenWord[i] == Guess[i]){ 
                BullCowCount.Bulls++;
            }
            else{
                BullCowCount.Cows++;
            }
        }
    }
    if (BullCowCount.Bulls == MyHiddenWord.length()) {
        bGameIsWon = true;
    }
    // compare letters against the hidden word
    return BullCowCount;
}

bool FBullCowGame::IsIsogram (FString Word) const{
    // treat 0 and 1 letter words as isograms
    if (Word.length() <= 1){return true ; }
    // Define the map (They are Python Dictionaries)
    TMap <char, bool> LetterSeen;
    for (auto Letter:Word){
        // handle the mixed case
        Letter = tolower(Letter);
        if (LetterSeen[Letter]){
            return false;
        } 
        else {
            LetterSeen[Letter] = true;
        }
    }
    // Return true if a word entered has more than 1 letter but less than word length
    // and the wird is indeed an Isogram
    return true;
}

bool FBullCowGame::IsLowerCase (FString Word) const{
    for (auto Letter:Word){
        if (!islower(Letter)){
            return  false;
        }
    } 
    return true;
}