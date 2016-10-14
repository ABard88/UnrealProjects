#pragma once

#include "FBullCowGame.h"
#include<map>
#define TMap std::map					//Here using would require more parameters and would complicate things TMap is unreal syntax for map
using int32 = int;

FBullCowGame::FBullCowGame() {Reset();}//If values are already defined- Constructor overwrites them at runtime

//const prevents any change in the value of the variables or constructors works only on class functions
int32 FBullCowGame::GetCurrentTry()const { return CurrentTry; } //These two methods can be known as Getters
int32 FBullCowGame::GetTheWordLength() const{return TheWord.length();}

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthvsMaxTries{ {3,5}, {4,7}, {5,9},{6,12} };
	return WordLengthvsMaxTries[TheWord.length()]; 
}
void FBullCowGame::Reset()
{
	CurrentTry = 1;
	const FString THE_WORD = "cunt";		//This must be an isogram
	TheWord = THE_WORD;
	return;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const		 //In performance profiling the cond that happens the most should be on top to save the other code from being executed	
{
	if (!IsIsogram(Guess))											 //Function to check isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))									 //Function to check lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetTheWordLength() !=Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}
//takes in a valid guess, increements the turn and returns cowsnbulls
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = TheWord.length();										//Assumes same length as guess word
	for (int32 TheWordChar = 0; TheWordChar < WordLength; TheWordChar++)		//loop through all letters in the word
	{
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++)			//loop through all letters in the guess
		{
			if (TheWord[TheWordChar]==Guess[GuessChar])
			{
				if (TheWordChar==GuessChar)
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
	if (BullCowCount.Bulls == WordLength)							//Checks if we've got the word right or not Winning Condition
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }		//0 or 1 letter word is an isogram
	TMap<char, bool> LetterPresent;					//Setup Map
	for (auto Letter : Guess)						//Literal translation- for each letter in Guess //auto automatically decides what type of data is involved
	{
		Letter = tolower(Letter);					//Store and retrieve only lowercase letters
		if (LetterPresent[Letter])
		{
			return false;							//We do not have an Isogram
		}
		else
		{
			LetterPresent[Letter] = true;			//Add letter to map
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	if (Guess.length() == 0) { return true; }
	for (auto Letter : Guess)
	{

		if (!islower(Letter)) { return false;}
	}
	return true;
}
