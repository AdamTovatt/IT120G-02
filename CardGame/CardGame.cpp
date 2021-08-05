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
	deck.Shuffle(); //blandar kortleken i b�rjan av varje runda innan spelarna drar sina kort

	cout << playerOne.Name << ", tryck p� enter f�r att dra ett kort\n";
	Card card = deck.GetFirstCard();
	cin.ignore(100, '\n');
	cin.get();
	cout << playerOne.Name << " drog kortet " << deck.GetNameOfCard(card);

	return 1;
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
			cout << playerOne.Name << " vann denna runda";
		}
		else
		{
			playerTwoRounds++;
			cout << playerTwo.Name << " vann denna runda";
		}
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

	cout << "\n" << playerOne.Name << " mot " << playerTwo.Name << "\n";

	PlayMatch(deck);

	Card card = deck.GetFirstCard();

	cout << "v�rde: " << card.Value << "\n";
	cout << "f�rg: " << card.Color << "\n\n";

	deck.Shuffle();

	Card card2 = deck.GetFirstCard();
	cout << "v�rde: " << card2.Value << "\n";
	cout << "f�rg: " << card2.Color << "\n\n";

	if (card == card2)
		cout << "det var samma kort";
	else if (card > card2)
		cout << "det f�rsta kortet var b�ttre";
	else if (card < card2)
		cout << "det andra kortet var b�ttre";
	else
		cout << "vi borde inte kunna komma hit...";

	cout << "\n\n";
}