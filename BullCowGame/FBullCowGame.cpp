/*  AUTHOR: Thomas CIANFARANI
	CONTEXT: Unreal Course Section02
	DESCRIPTION:
	This is the FBullCowGame class.	It is responsible for all the game mechanics/logic.
*/

#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map // To make syntax Unreal friendly

// Getter for max tries
int32 FBullCowGame::GetMaxTries() const // const = wont change anything in function
{
	TMap<int32, int32> WordLengthToMaxTries = {
		{3, 4},
		{4, 7},
		{5, 10},
		{6, 16},
		{7, 20},
	};

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// Getter for current try
int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

// Getter for hidden word length
int32 FBullCowGame::GetHiddenWordLength() const
{
	return this->MyHiddenWord.length();
}

// Getter for whether the game is won or not
bool FBullCowGame::IsGameWon() const
{
	return this->bGameIsWon;
}

// Resets the game with a given word length 
void FBullCowGame::Reset(int32 WordLength)
{
	SetHiddenWordFromLength(WordLength);

	MyCurrentTry = 1;
	bGameIsWon = false;
}

// Sets the hidden word depending on the given word length
void FBullCowGame::SetHiddenWordFromLength(int32 WordLength)
{
	TMap<int32, FString> WordFromLength = {   // the words must be isograms
		{3, "car"},
		{4, "lawn" },
		{5, "fight" },
		{6, "rocket" },
		{7, "subject" },
	};
	
	MyHiddenWord = WordFromLength[WordLength];
}

// Checks whether the given guess is valid or not  
EGuessValidityStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessValidityStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isn't a lowercase
	{
		return EGuessValidityStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess has the wrong length
	{
		return EGuessValidityStatus::Wrong_Length;
	}
	else // otherwise
	{
		return EGuessValidityStatus::OK;
	}
}

// receives a VALID guess, increments current try and returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = GetHiddenWordLength();

	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) // increment bulls if they're in the same place
				{
					BullCowCount.Bulls++;
				}
				else // increment cows if not
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	// Handle GG
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		this->bGameIsWon = true;
	}
	else
	{
		this->bGameIsWon = false;
	}

	return BullCowCount;
}

// Returns bool indicating whether the word is an isogram or not
bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms 
	if (Word.length() <= 1) { return true; }

	// create a map to store the seen letters
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case (Aa)		
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // not an isogram
		}
		else // if the letter isnt in the map
		{
			LetterSeen[Letter] = true; // insert it in the map and continue
		}
	}

	// return true if we get here
	return true;
}

// Returns bool indicating whether the word is in lowercase or not
bool FBullCowGame::IsLowerCase(FString Word) const
{
	// loop through letters in the word
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if the letter is upper case
			return false;
		else
			continue;
	}

	// return true if we get here
	return true;
}