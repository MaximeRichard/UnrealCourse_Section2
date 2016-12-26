/*Class for managing the logic of the game
Number of tries, checking if the Guess is correct...
*/
#pragma once
#include <string>

//Using and define for Unreal Friendly syntax
using FString = std::string;
using int32 = int;
#define TMap std::map

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// enum for Guess validity status
enum class EGuessStatus
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
	FBullCowGame(); //Constructor

	int32 GetMaxTries() const;
	FString GetLevelWord(int32 Difficulty) const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(int32);
	FBullCowCount SubmitValidGuess(FString);

// ^^ Ignore for now ^^
private:
	// See constructor for initialization
	int32 MyCurrenTry;
	bool bGameIsWon;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};