#include <iostream>
#include <ctime>
#include <windows.h>
#include <thread>
#include "CardDeck.cpp"
#include "Player.cpp"

#pragma execution_character_set( "utf-8" )

using namespace std;

Player playerOne; //h�r sparas information om spelare 1
Player playerTwo; //h�r sparas information om spelare 2

int TakeIntInput(string promt, int min, int max) //detta �r en funktion f�r att ta indata fr�n anv�ndaren som s�kerst�lls till att vara av typen int och inte mer �n max och inte mindre �n min
{
	cout << promt; //skriver ut det medelande som ska visas innan indata tas, ibland �r det tomt men d� skrivs inget ut heller
	int input;
	cin >> input; //tar input

	while (!cin || input < min || input > max) //vi kollar att vi tog input korrekt, "cin" �r false om tex en bokstav skrevs in. Vi kollar ocks� s� att v�rdet �r inom vad det f�r vara
	{
		cin.clear(); //om vi kommer hit kan det vara s� att ett felaktigt tecken dvs typ en bokstav skrivits in s� vi �terst�ller och rensar cin
		cin.ignore(100, '\n'); //ignorerar de tecken som varit felaktiga
		cout << "Var god ange ett heltal mellan " << min << " och " << max << "\n";
		cin >> input; //tar input igen
	}

	return input; //returnerar det man skrivit
}

int PlayRound(CardDeck deck) //funktion f�r att spela en runda
{
	cout << playerOne.Name << ", tryck p� enter f�r att dra ett kort\n";

	deck.Shuffle(); //blandar kortleken innan varje spelares drag
	Card card1 = deck.GetFirstCard(); //tar kortet som �r "h�gst upp" i kortleken

	cin.get(); //v�nta p� enter

	cout << playerOne.Name << " drog kortet " << deck.GetNameOfCard(card1) << "\n\n"; //presenterar kortet
	cout << playerTwo.Name << ", tryck p� enter f�r att dra ett kort\n";

	deck.Shuffle(); //blandar kortleken h�r ocks� eftersom nu ska spelare 2 dra
	Card card2 = deck.GetFirstCard(card1); //skickar med det kortet som nyss drogs s� vi vet att det inte ska finnas med i kortleken

	cin.get(); //v�nta p� enter

	cout << playerTwo.Name << " drog kortet " << deck.GetNameOfCard(card2) << "\n\n"; //presenterar kortet

	cout << "Tryck p� enter f�r att forts�tta\n";
	cin.get(); //v�ntar p� enter

	if (card1 == card2) //kastar ett fel om detta h�nder s� att vi m�rker det eftersom det inte borde kunna h�nda s� d� har koden skrivits fel p� n�got s�tt
		throw new exception("N�got fel har lett till att spelarna f�tt samma kort, detta borde inte g�");

	if (card1 > card2) //spelare 1s kort var mer v�rt �n spelare 2s s� vi returnerar 1
		return 1;
	return 2; //annars vann spelare 2
}

int PlayMatch(CardDeck deck) //funktion f�r att spela en match
{
	cin.clear(); //s� att vi senare kan anv�nda cin.get() f�r att v�nta p� enter
	cin.ignore();
	system("CLS"); //st�dar sk�rmen innan matchen b�rjar

	int playerOneRounds = 0; //kommer anv�ndas f�r att h�lla koll p� antal rundor respektive spelare har vunnit
	int playerTwoRounds = 0;

	while (playerOneRounds < 2 && playerTwoRounds < 2) //s� l�nge ingen har vunnit ska vi g�ra det som �r i loopen
	{
		int roundResult = PlayRound(deck); //b�rjar med att spela en runda med kortleken vi har f�tt med oss in i matchen

		if (roundResult == 1) //tolkar resultatet av rundan
		{
			playerOneRounds++; //h�r vann spelare 1
			playerOne.RoundsWon++; //anv�nds f�r statistik sen
			cout << playerOne.Name << " vann denna runda\n\n";
		}
		else
		{
			playerTwoRounds++; //h�r vann spelare 2
			playerTwo.RoundsWon++; //anv�nds f�r statistik sen
			cout << playerTwo.Name << " vann denna runda\n\n";
		}

		if (playerOneRounds < 2 && playerTwoRounds < 2) //om ingen har vunnit ska vi g�ra detta
		{
			cout << playerOne.Name << " har vunnit " << playerOneRounds << (playerOneRounds == 1 ? " runda\n" : " rundor\n"); //skriver ut resultat i rundor
			cout << playerTwo.Name << " har vunnit " << playerTwoRounds << (playerTwoRounds == 1 ? " runda\n\n" : " rundor\n\n"); //vi har den h�r i ifsatsen f�r det k�nns on�digt att skriva ut den om n�gon har vunnit

			cout << "Tryck p� enter f�r att forts�tta"; //v�ntar p� att man trycker p� enter och st�dar sen sk�rmen
			cin.get();
			system("CLS");
		}
	}

	if (playerOneRounds == 2) //om spelare 1 har vunnit 2 rundor returnerar vi att spelare 1 har vunnit matchen, annars har spelare 2 vunnit eftersom vi kom ur loopen s� n�gon m�ste ha vunnit men det var inte spelare 1
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
	cin >> playerOneName; //tar in spelare 1s namn
	playerOne = Player(playerOneName); //skapar spelare 1s anv�ndardata
	cout << "\nSpelare tv�, skriv in ditt namn och tryck sedan p� enter:\n";
	string playerTwoName;
	cin >> playerTwoName; //tar in spelare 2s namn
	playerTwo = Player(playerTwoName); //skapar spelare 2s anv�ndardata

	bool keepPlaying = true; //h�ller reda p� om n�gon vill avsluta spelet eller inte

	while (keepPlaying) //s� l�nge ingen har valt att avsluta forts�tter vi
	{
		if (PlayMatch(deck) == 1) //spelar en match med v�r kortlek och kollar resultatet
		{
			playerOne.MatchesWon++; //h�r vann spelare 1
			cout << playerOne.Name << " vann d�rmed ocks� matchen!\n\n";
		}
		else
		{
			playerTwo.MatchesWon++; //h�r vann spelare 2
			cout << playerTwo.Name << " vann d�rmed ocks� matchen!\n\n";
		}

		cout << "Total resultat i matcher:\n"; //skriver ut lite statistik
		cout << playerOne.Name << " " << playerOne.MatchesWon << "\n";
		cout << playerTwo.Name << " " << playerTwo.MatchesWon << "\n";
		cout << "\nTotalt resultat i rundor:\n";
		cout << playerOne.Name << " " << playerOne.RoundsWon << "\n";
		cout << playerTwo.Name << " " << playerTwo.RoundsWon << "\n";

		if (TakeIntInput("\n\nVill ni forts�tta spela?\n1. Ja\n2. Nej, avsluta\n\n", 1, 2) == 2) //kollar om man vill forts�tta spela
			keepPlaying = false;
	}

	cout << "\n\n";
}