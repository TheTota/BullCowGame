/*  AUTHOR: Thomas CIANFARANI
	CONTEXT: Unreal Course Section02
	DESCRIPTION: 
	This is the header file for the class FBullCowGame.
*/

#pragma once
#include <string>

// To make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessValidityStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessValidityStatus CheckGuessValidity(FString) const;

	void Reset(int32);
	void SetHiddenWordFromLength(int32);
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;	
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};