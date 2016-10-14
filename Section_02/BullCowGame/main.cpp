/* This is the console application that uses the BullCow class. Acts as a view in the MVC pattern.
This is reponsible for all user interaction.
For Game logic, see FBullCowGame class
*/
#pragma once
#include<iostream>
/* Just before it compiles it goes to iostream and goes through the text of iostream and uses it to turn it into a format that the comp can read
				  Use <> when importing default standard prebuilt visual studio c++ stuff When using own code use "" instead of <>
				   This is library code*/
#include<string>  //This tells std::cin>> what to do with the string
#include"FBullCowGame.h"  //The game class
//We removed the 'using namespace std' because it's bad practice to use namespaces// Instead use std:: before each command

using FText = std::string; //Done to make code more like unreals standards
using int32 = int;

void IntroduceGame();//Just letting it know that there is a func IntroduceGame somewhere down below Called a prototype
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //Here BCGame is an instance of the class FBullCowGame that we made


//The entry point for our application
int main()
{
	bool bReplay = false;
	do
	{
		IntroduceGame();
		PlayGame();
		bReplay=AskToPlayAgain();
	} 
	while (bReplay);

	return 0; //return== Leave with the status of 0
}

void IntroduceGame()
{
	//Here the scopre of WORD_LENGTH is within the brace brackets of IntroduceGame, you cannot use it elsewhere
	std::cout << "\n\nWelcome to Bulls and Cows" << std::endl;// std::cout is tagged as std(standard) in the iostream library
												// << indicates that take the value to the right of it and insert it into the left side
	std::cout << std::endl;
	std::cout <<"                  /   \\     ____                 " <<std::endl;
	std::cout <<"                 {0   0}   (O  O)                " <<std::endl;
	std::cout <<"       /---------  [ ]       []  ----------\\    " <<std::endl;
	std::cout <<"      /| BULL    |               |  COW    |\\  " <<std::endl;
	std::cout <<"       |--,------|               |____/\___|     " <<std::endl;
	std::cout <<"         |     |                    |    |" << std::endl;
	std::cout <<"         ^     ^                    ^    ^" << std::endl;
	std::cout << "It's an okay wordgame\n\n";
	std::cout << "Can you guess the " << BCGame.GetTheWordLength() << " letter isogram I am thinking off?\n\n";
	return; //Good habit to return at the end of your functions
}

//Plays 1 game to completion
void PlayGame()
{
	BCGame.Reset();
														//Loop for the max number of tries
	int32 MaxTries=BCGame.GetMaxTries();				// constexpr int32 MAX_TRIES = 5; Could have used this instead of getting it from a class
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	{
		FText Guess=GetValidGuess();							

		FBullCowCount BullCowCount= BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << "  Cows= " << BullCowCount.Cows<<std::endl;
	}
	PrintGameSummary();												
	return;
}

//Loop till the user inputs a valid guess
FText GetValidGuess()										
{
	FText Guess = "";
	EGuessStatus Status=EGuessStatus::Invalid_Status;
	//Get a guess from the player
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
 		std::cout << "Try" << CurrentTry <<" of "<<BCGame.GetMaxTries()<<std::endl <<"Type in your guess:";
		std::getline(std::cin, Guess);
		//Checking guess validity
		Status = BCGame.IsGuessValid(Guess);												//submit valid guess to game and recieve cowsnbulls 
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetTheWordLength() << " letter word\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your word in lowercase letters.\n\n";
			break;
		default:
			//Assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //Keep looping till we get valid guess
	return Guess;						  //Having return guess here instead of the default condition ensures all paths will return a value
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word? (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	bool AnotherGame= (Response[0] == 'y' || Response[0] == 'Y');
	return AnotherGame;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations you guessed it! \n\n";
	}
	else
	{
		std::cout << "You lose better luck next time! \n\n";
	}
	return; 
}


