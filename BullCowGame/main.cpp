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
	std::cout << "Welcome to Bulls and Cows!\n";
	std::cout << "Can you guess what " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I am thinking?\n";
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset(); // starts a new game
	int32 MaxTries = BCGame.GetMaxTries();

	// loop the number of guesses
	for (int32 i = 1; i <= MaxTries; i++) // TODO change FOR to While when validating tries
	{
		FText Guess = GetValidGuess(); 
		
		// submit valid guess to the game and receive count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << ".\n\n";
	}

	// TODO show game summary
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
			std::cout << "The word must be an isogram (without repeating letters)\n";
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

// asks if the player wants to play again
bool AskToPlayAgain()
{
	FText PlayAgainAns;
	std::cout << "Do you want to play again?\n";
	std::getline(std::cin, PlayAgainAns);
	return (PlayAgainAns[0] == 'y') || (PlayAgainAns[0] == 'Y');
}
