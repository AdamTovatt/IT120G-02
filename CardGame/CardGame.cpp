#include <iostream>
#include <ctime>
#include <windows.h>
#include <thread>
#include "CardDeck.cpp"
#include "Player.cpp"

#pragma execution_character_set( "utf-8" )

using namespace std;

Player playerOne;
Player playerTwo;

int TakeIntInput(string promt, int min, int max) //detta �r en funktion f�r att ta indata fr�n anv�ndaren som s�kerst�lls till att vara av typen int och inte mer �n max och inte mindre �n min
{
	cout << promt; //skriver ut det medelande som ska visas innan indata tas, ibland �r det tomt men d� skrivs inget ut heller
	int input;
	cin >> input; //tar input

	while (!cin || input < min || input > max) //vi kollar att vi tog input korrekt, "cin" �r false om tex en bokstav skrevs in. Vi kollar ocks� s� att v�rdet �r inom vad det f�r vara
	{
		cin.clear(); //om vi kommer hit kan det vara s� att ett felaktigt tecken dvs typ en bokstav skrivits in s� vi �terst�ller och rensar cin
		cin.ignore(100, '\n'); //ignorerar det felaktiga tecken
		cout << "Var god ange ett heltal mellan " << min << " och " << max << "\n";
		cin >> input; //tar input igen
	}

	return input; //returnerar det man skrivit
}

int PlayRound(CardDeck deck) 
{
	cout << playerOne.Name << ", tryck p� enter f�r att dra ett kort\n";

	deck.Shuffle(); //blandar kortleken innan varje spelares drag
	Card card1 = deck.GetFirstCard();

	cin.ignore(100, '\n');
	cin.get(); //v�ntar p� att spelaren trycker p� enter f�r att forts�tta

	cout << playerOne.Name << " drog kortet " << deck.GetNameOfCard(card1) << "\n\n";
	cout << playerTwo.Name << ", tryck p� enter f�r att dra ett kort\n";

	deck.Shuffle();
	Card card2 = deck.GetFirstCard();

	cin.get();

	cout << playerTwo.Name << " drog kortet " << deck.GetNameOfCard(card2) << "\n\n";

	if (card1 == card2)
		throw new exception("n�got fel har lett till att spelarna f�tt samma kort, detta borde inte g�");

	if (card1 > card2) //spelare 1s kort var mer v�rt �n spelare 2s s� vi returnerar 1
		return 1;
	return 2; //annars vann spelare 2
}

int PlayMatch(CardDeck deck)
{
	int playerOneRounds = 0;
	int playerTwoRounds = 0;

	while (playerOneRounds < 2 && playerTwoRounds < 2)
	{
		int roundResult = PlayRound(deck);

		if (roundResult == 1)
		{
			playerOneRounds++;
			playerOne.RoundsWon++;
			cout << playerOne.Name << " vann denna runda\n\n";
		}
		else
		{
			playerTwoRounds++;
			playerTwo.RoundsWon++;
			cout << playerTwo.Name << " vann denna runda\n\n";
		}

		cout << playerOne.Name << " har vunnit " << playerOneRounds << (playerOneRounds == 1 ? " runda\n" : " rundor\n");
		cout << playerTwo.Name << " har vunnit " << playerTwoRounds << (playerTwoRounds == 1 ? " runda\n" : " rundor\n\n");
	}

	if (playerOneRounds == 2)
		return 1;
	return 2;
}

int main()
{
	SetConsoleOutputCP(65001); //g�r s� att ��� kan skrivas till konsolen
	srand(time(0)); //initialiserar random baserat p� den nuvarande tiden s� att det inte alltid �r samma

	CardDeck deck = CardDeck(); //skapar en ny kortlek som vi kan anv�nda f�r kortspelet

	cout << "V�lkommen till kortspelet\n\n";
	cout << "Spelare ett, skriv in ditt namn och tryck sedan p� enter:\n";
	string playerOneName;
	cin >> playerOneName;
	playerOne = Player(playerOneName);
	cout << "\nSpelare tv�, skriv in ditt namn och tryck sedan p� enter:\n";
	string playerTwoName;
	cin >> playerTwoName;
	playerTwo = Player(playerTwoName);

	bool keepPlaying = true;

	while (keepPlaying)
	{
		if (PlayMatch(deck) == 1)
		{
			playerOne.MatchesWon++;
			cout << playerOne.Name << " vann matchen!\n\n";
		}
		else
		{
			playerTwo.MatchesWon++;
			cout << playerTwo.Name << " vann matchen!\n\n";
		}

		cout << "Total resultat i matcher:\n";
		cout << playerOne.Name << " " << playerOne.MatchesWon;
		cout << playerTwo.Name << " " << playerTwo.MatchesWon;
		cout << "\nTotalt resultat i rundor:\n";
		cout << playerOne.Name << " " << playerOne.RoundsWon;
		cout << playerTwo.Name << " " << playerTwo.RoundsWon;

		if (TakeIntInput("\n\nVill ni forts�tta spela?\n1. Ja\n2. Nej, avsluta", 1, 2) == 2)
			keepPlaying = false;
	}

	cout << "\n\n";
}