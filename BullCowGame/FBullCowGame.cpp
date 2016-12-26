#pragma once
#include "FBullCowGame.h"
#include <map>

//Using and define for Unreal Friendly syntax
using int32 = int;
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(1); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrenTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{ 
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,16 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
FString FBullCowGame::GetDifficultyWord(int32 Difficulty) const
{
	// TODO check for a better design of the word list (random from specific ranges, list stored outside of code) 
	FString ChosenWord;
	FString EasyWords[] = { "ant", "dog", "cat", "ben", "pig" }; //these MUST be isograms
	FString MediumWords[] = { "zombie", "squid", "bricks", "magic", "rabids" };
	FString HardWords[] = { "karting", "padlock", "zephyr", "update", "backlog" };
	switch (Difficulty)
	{
	case 1:
		ChosenWord = EasyWords[rand() % 5]; // Get a random index from 0 to 4
		break;
	case 2:
		ChosenWord = MediumWords[rand() % 5];
		break;
	case 3:
		ChosenWord = HardWords[rand() % 5];
		break;
	default:
		break;
	}
	
	return ChosenWord;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram, return an error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase, return an error
	{
		return EGuessStatus::Not_Lowercase;
	} 
	else if (GetHiddenWordLength() != Guess.length()) // if the guess length is wrong, return an error
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// Act as constructor
void FBullCowGame::Reset(int32 Difficulty)
{
	const FString HIDDEN_WORD = GetDifficultyWord(Difficulty);
	MyHiddenWord = HIDDEN_WORD;
	MyCurrenTry = 1;
	bGameIsWon = false;
	return;
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrenTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength(); // assume same length as guess

	// loop through all letters in the word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match 
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				// if they're in the same place
				if (MHWChar == GChar)
				{
					// increments Bulls
					BullCowCount.Bulls++;
				}
			//else, if they don't
				else
				{
					//increment Cows
					BullCowCount.Cows++;
				}
				
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) { bGameIsWon = true; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 & 1 letter strings as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
			// if it's already in the map
				// return false
			// else
				// add it to the map
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	// treat 0 & 1 letter strings as isograms
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word) // for all letters of the word
	{
		if (!islower(Letter)) { return false; }
	}

	return true;
}

