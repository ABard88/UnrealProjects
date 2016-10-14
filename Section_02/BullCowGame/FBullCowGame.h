/*The game logic (no direct user interaction with this)
*/

#pragma once
#include<string>

using FString = std::string; //this is a substituion. Looks nicer, more compatible with unreal
using int32 = int;
//Never use a namespace inside a header file //Screws up what namespaces we have access to and which one we're refering
//Actually you'd be better off not using namespace at all

struct FBullCowCount   //Used instead of class when you have simple datatypes and no functions inside
{
	int32 Bulls = 0;
	int32 Cows=0; 
};

enum class EGuessStatus //enum values have a global scope but enum class has a local scope and you can use same keywords again in a different enum class
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

	FBullCowGame();// Is a constructor a Destructor is ~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	EGuessStatus IsGuessValid(FString) const;
	int32 GetTheWordLength() const;
	bool IsGameWon()const;
	void Reset();
	
	FBullCowCount SubmitValidGuess(FString);

private:
	//See constructor for initialzing values
	int32 CurrentTry;
	FString TheWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};


