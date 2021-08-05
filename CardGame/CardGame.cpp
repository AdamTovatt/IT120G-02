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

int TakeIntInput(string promt, int min, int max) //detta är en funktion för att ta indata från användaren som säkerställs till att vara av typen int och inte mer än max och inte mindre än min
{
	cout << promt; //skriver ut det medelande som ska visas innan indata tas, ibland är det tomt men då skrivs inget ut heller
	int input;
	cin >> input; //tar input

	while (!cin || input < min || input > max) //vi kollar att vi tog input korrekt, "cin" är false om tex en bokstav skrevs in. Vi kollar också så att värdet är inom vad det får vara
	{
		cin.clear(); //om vi kommer hit kan det vara så att ett felaktigt tecken dvs typ en bokstav skrivits in så vi återställer och rensar cin
		cin.ignore(100, '\n'); //ignorerar det felaktiga tecken
		cout << "Var god ange ett heltal mellan " << min << " och " << max << "\n";
		cin >> input; //tar input igen
	}

	return input; //returnerar det man skrivit
}

int PlayRound(CardDeck deck) 
{
	cout << playerOne.Name << ", tryck på enter för att dra ett kort\n";

	deck.Shuffle(); //blandar kortleken innan varje spelares drag
	Card card1 = deck.GetFirstCard();

	cin.ignore(100, '\n');
	cin.get(); //väntar på att spelaren trycker på enter för att fortsätta

	cout << playerOne.Name << " drog kortet " << deck.GetNameOfCard(card1) << "\n\n";
	cout << playerTwo.Name << ", tryck på enter för att dra ett kort\n";

	deck.Shuffle();
	Card card2 = deck.GetFirstCard();

	cin.get();

	cout << playerTwo.Name << " drog kortet " << deck.GetNameOfCard(card2) << "\n\n";

	if (card1 == card2)
		throw new exception("något fel har lett till att spelarna fått samma kort, detta borde inte gå");

	if (card1 > card2) //spelare 1s kort var mer värt än spelare 2s så vi returnerar 1
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
	SetConsoleOutputCP(65001); //gör så att åäö kan skrivas till konsolen
	srand(time(0)); //initialiserar random baserat på den nuvarande tiden så att det inte alltid är samma

	CardDeck deck = CardDeck(); //skapar en ny kortlek som vi kan använda för kortspelet

	cout << "Välkommen till kortspelet\n\n";
	cout << "Spelare ett, skriv in ditt namn och tryck sedan på enter:\n";
	string playerOneName;
	cin >> playerOneName;
	playerOne = Player(playerOneName);
	cout << "\nSpelare två, skriv in ditt namn och tryck sedan på enter:\n";
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

		if (TakeIntInput("\n\nVill ni fortsätta spela?\n1. Ja\n2. Nej, avsluta", 1, 2) == 2)
			keepPlaying = false;
	}

	cout << "\n\n";
}