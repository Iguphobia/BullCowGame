// main.cpp: Define o ponto de entrada para a aplicação de console.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
FText PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiante a new game

// entry point of the application
int main()
{
	// game's main loop
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

    return 0; // exit application
}

// introduce the game
void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows!\n";
	std::cout << "Can you guess what " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I am thinking?\n";
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset(); // starts a new game
	int32 MaxTries = BCGame.GetMaxTries();

	// loop the number of tries while the game is not won
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 
		
		// submit valid guess to the game and receive count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << ".\n\n";
	}

	std::cout << PrintGameSummary();
}

//take a guess from the player
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	
	do 
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << ". Take a guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.ValidateGuess(Guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "The word must be an isogram (no repeating letters).\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please insert only lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::Ok); // keep looping until we get no errors

	return Guess;
}

FText PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		return "Congratulations, you win the game!\n";
	}
	else
	{
		return "You lose! Better luck next time.\n";
	}
}

// asks if the player wants to play again
bool AskToPlayAgain()
{
	FText PlayAgainAns;
	std::cout << "Do you want to play again with the same hidden word? ";
	std::getline(std::cin, PlayAgainAns);

	return (PlayAgainAns[0] == 'y') || (PlayAgainAns[0] == 'Y');
}
