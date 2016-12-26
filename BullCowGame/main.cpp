#pragma once
/* This is the console executable, that makes use of the BullCow class
This acts as the view in the MVC pattern, and is responsible for all user interaction.
For game logic see FBullCowGame class.

*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Unreal friendly syntax
using FText = std::string;
using int32 = int;
int main();

// functions prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
int32 AskDifficulty();

FBullCowGame BCGame; //instanciate a new game, reused every play

//the entry point of the program
int main()
{
	
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
	return;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon())
	{
		std::cout << "You won\n";
	}
	else
	{
		std::cout << "Bad luck\n";
	}
	return;
}

// Manage the main game loop to completion
void PlayGame()
{
	int32 Difficulty = AskDifficulty();
	BCGame.Reset(Difficulty);
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game is NOT won
	//and there is still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls : " << BullCowCount.Bulls;
		std::cout << ". Cows : " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// Loop until we get a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		
		int32 CurrentTry = BCGame.GetCurrentTry(); //Get the current try
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess : ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word that is an isogram (without repeating letter).\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get valid guess
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y' );
}

int32 AskDifficulty()
{
	int32 DifficultyLevel;
	do
	{
		std::cout << "What difficulty setting do you want (1 : easy, 2 : medium, 3 : hard) ? ";
		std::cin >> DifficultyLevel;		
	} while (DifficultyLevel != 1 && DifficultyLevel != 2 && DifficultyLevel != 3);

		return DifficultyLevel;
}
