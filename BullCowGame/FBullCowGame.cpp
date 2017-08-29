#include "stdafx.h"
#include "FBullCowGame.h"

using FString = std::string;
using int32 = int32;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	
	MyCurrentTry = 1;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EGuessStatus FBullCowGame::ValidateGuess(FString CurrentGuess) const
{
	if (false) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (CurrentGuess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise, return ok
	{
		return EGuessStatus::Ok;
	}
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming it has the same length as the guess

	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++) 
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	return BullCowCount;
}
