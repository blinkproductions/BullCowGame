/*This is the console excutable, that makes use of the BullCow class
This acts as the view in a MVC patter, and is resposible forll
user interaction. For game logic see the FBullCowGame class.

FText --> used when interacting with user
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;
FBullCowGame BCGame; //instantiate a new game, which we re-use across plays

void PrintIntro()
{
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking off?\n\n";
}

// loop continuslly until user gives a valid guess
FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    do
    {
        std::cout << "Try #" << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
            break;

        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lowercase letters.\n\n";
            break;

        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;

        default:
            // assume the guess is valid
            break;
        }
    } while (Status != EGuessStatus::OK); // keep looping until we get no errors
    return Guess;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "You won!\n";
    }
    else
    {
        std::cout << "You lost!\n";
    }
}

// plays a single game to completion
void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    //loop asking for gueses while the game
    //is NOT won and there are still tries remaining

    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();

        //submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls =  " << BullCowCount.Bulls;
        std::cout << " Cows = " << BullCowCount.Cows << std::endl
                  << std::endl;
    }
    PrintGameSummary();
    return;
}

bool AskToPlayAgain()
{
    FText Response = "";

    std::cout << "Do you want to play again? (y/n)\n";
    std::getline(std::cin, Response);

    if (Response[0] == 'y' || Response[0] == 'Y')
    {
        return true;
    }
    return false;
}

int main()
{
    PrintIntro();
    bool bPlayAgain = false;
    do
    {
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);

    return 0;
}
