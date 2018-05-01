/*	AUTHOR: Thomas CIANFARANI
	CONTEXT: Unreal Course Section02
	DESCRIPTION: 
	This is the console executable that makes use of the BullCow class.
	This acts as the view in a MVC pattern and is responsible for all user
	interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream> // <...> for standard stuff ; ça fait un copié collé du fichier spécifié
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// Prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText);
bool AskToPlayAgain();
void PrintGameSummary();
int32 GetWordLength();

// Instance for the game which we re-use across plays
FBullCowGame BCGame;

// Entry point of the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // exit application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n\n";	
	std::cout << "              |\\ |\\" << std::endl;
	std::cout << "              //_//        ___" << std::endl;
	std::cout << "   .----------| ..|       |.. |----------. " << std::endl;
	std::cout << "  /|           \\  /       \\  /           |\\" << std::endl;
	std::cout << " / |   BULL     |o         o|     COW    | \\" << std::endl;
	std::cout << "*  |---,--------|           |------------|  *" << std::endl;
	std::cout << "   | |        | |           | |        | |\n" << std::endl;
	std::cout << "Bulls are the letters that are in the hidden word and in the right place." << std::endl;
	std::cout << "Cows are the letters that are in the hidden word but not in the right place." << std::endl;
	std::cout << std::endl;
}

// Plays a single game to completion
void PlayGame()
{
	// Reset the game
	BCGame.Reset(GetWordLength());

	// Game starts
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letters isogram I'm thinking of?\n";
	std::cout << std::endl;

	// Loop for the amount of trials while the game isn't won
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		// Get a valid guess from the user
		FText Guess = GetValidGuess();

		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

// Gets a valid guess from the user
FText GetValidGuess() 
{
	EGuessValidityStatus Status = EGuessValidityStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		// Getting the guess from the user
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess : ";
		std::getline(std::cin, Guess);

		// Validity checking
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessValidityStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;

		case EGuessValidityStatus::Not_Isogram:
			std::cout << "Please enter an isogram (word that doesn't contain twice the same letter).\n\n";
			break;

		case EGuessValidityStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n\n";
			break;

		default:
			// assume guess is valid
			break;
		}		
	} while (Status != EGuessValidityStatus::OK); // Keep looping until we have no error

	return Guess;
}

// Method returning a bool indicating player's desire to play again
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// Prints GG or GO
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRATULATIONS, you have found the hidden word and won the game!\n\n";
	}
	else
	{
		std::cout << "OH SNAP, better luck next time!\n\n";
	}
}

// Gets user's chosen word length
int32 GetWordLength()
{
	int32 WordLength;	

	do
	{
		std::cout << "Enter a length for the hidden word (between 3 and 7) : ";
		std::cin >> WordLength;
	} while (WordLength > 7 || WordLength < 3);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return WordLength;
}
