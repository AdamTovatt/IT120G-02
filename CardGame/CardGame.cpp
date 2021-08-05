#include <iostream>
#include <ctime>
#include <windows.h>
#include <thread>
#include "CardDeck.cpp"
#include "Player.cpp"

#pragma execution_character_set( "utf-8" )

using namespace std;

Player playerOne; //här sparas information om spelare 1
Player playerTwo; //här sparas information om spelare 2

int TakeIntInput(string promt, int min, int max) //detta är en funktion för att ta indata från användaren som säkerställs till att vara av typen int och inte mer än max och inte mindre än min
{
	cout << promt; //skriver ut det medelande som ska visas innan indata tas, ibland är det tomt men då skrivs inget ut heller
	int input;
	cin >> input; //tar input

	while (!cin || input < min || input > max) //vi kollar att vi tog input korrekt, "cin" är false om tex en bokstav skrevs in. Vi kollar också så att värdet är inom vad det får vara
	{
		cin.clear(); //om vi kommer hit kan det vara så att ett felaktigt tecken dvs typ en bokstav skrivits in så vi återställer och rensar cin
		cin.ignore(100, '\n'); //ignorerar de tecken som varit felaktiga
		cout << "Var god ange ett heltal mellan " << min << " och " << max << "\n";
		cin >> input; //tar input igen
	}

	return input; //returnerar det man skrivit
}

int PlayRound(CardDeck deck) //funktion för att spela en runda
{
	cout << playerOne.Name << ", tryck på enter för att dra ett kort\n";

	deck.Shuffle(); //blandar kortleken innan varje spelares drag
	Card card1 = deck.GetFirstCard(); //tar kortet som är "högst upp" i kortleken

	cin.get(); //vänta på enter

	cout << playerOne.Name << " drog kortet " << deck.GetNameOfCard(card1) << "\n\n"; //presenterar kortet
	cout << playerTwo.Name << ", tryck på enter för att dra ett kort\n";

	deck.Shuffle(); //blandar kortleken här också eftersom nu ska spelare 2 dra
	Card card2 = deck.GetFirstCard(card1); //skickar med det kortet som nyss drogs så vi vet att det inte ska finnas med i kortleken

	cin.get(); //vänta på enter

	cout << playerTwo.Name << " drog kortet " << deck.GetNameOfCard(card2) << "\n\n"; //presenterar kortet

	cout << "Tryck på enter för att fortsätta\n";
	cin.get(); //väntar på enter

	if (card1 == card2) //kastar ett fel om detta händer så att vi märker det eftersom det inte borde kunna hända så då har koden skrivits fel på något sätt
		throw new exception("Något fel har lett till att spelarna fått samma kort, detta borde inte gå");

	if (card1 > card2) //spelare 1s kort var mer värt än spelare 2s så vi returnerar 1
		return 1;
	return 2; //annars vann spelare 2
}

int PlayMatch(CardDeck deck) //funktion för att spela en match
{
	cin.clear(); //så att vi senare kan använda cin.get() för att vänta på enter
	cin.ignore();
	system("CLS"); //städar skärmen innan matchen börjar

	int playerOneRounds = 0; //kommer användas för att hålla koll på antal rundor respektive spelare har vunnit
	int playerTwoRounds = 0;

	while (playerOneRounds < 2 && playerTwoRounds < 2) //så länge ingen har vunnit ska vi göra det som är i loopen
	{
		int roundResult = PlayRound(deck); //börjar med att spela en runda med kortleken vi har fått med oss in i matchen

		if (roundResult == 1) //tolkar resultatet av rundan
		{
			playerOneRounds++; //här vann spelare 1
			playerOne.RoundsWon++; //används för statistik sen
			cout << playerOne.Name << " vann denna runda\n\n";
		}
		else
		{
			playerTwoRounds++; //här vann spelare 2
			playerTwo.RoundsWon++; //används för statistik sen
			cout << playerTwo.Name << " vann denna runda\n\n";
		}

		if (playerOneRounds < 2 && playerTwoRounds < 2) //om ingen har vunnit ska vi göra detta
		{
			cout << playerOne.Name << " har vunnit " << playerOneRounds << (playerOneRounds == 1 ? " runda\n" : " rundor\n"); //skriver ut resultat i rundor
			cout << playerTwo.Name << " har vunnit " << playerTwoRounds << (playerTwoRounds == 1 ? " runda\n\n" : " rundor\n\n"); //vi har den här i ifsatsen för det känns onödigt att skriva ut den om någon har vunnit

			cout << "Tryck på enter för att fortsätta"; //väntar på att man trycker på enter och städar sen skärmen
			cin.get();
			system("CLS");
		}
	}

	if (playerOneRounds == 2) //om spelare 1 har vunnit 2 rundor returnerar vi att spelare 1 har vunnit matchen, annars har spelare 2 vunnit eftersom vi kom ur loopen så någon måste ha vunnit men det var inte spelare 1
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
	cin >> playerOneName; //tar in spelare 1s namn
	playerOne = Player(playerOneName); //skapar spelare 1s användardata
	cout << "\nSpelare två, skriv in ditt namn och tryck sedan på enter:\n";
	string playerTwoName;
	cin >> playerTwoName; //tar in spelare 2s namn
	playerTwo = Player(playerTwoName); //skapar spelare 2s användardata

	bool keepPlaying = true; //håller reda på om någon vill avsluta spelet eller inte

	while (keepPlaying) //så länge ingen har valt att avsluta fortsätter vi
	{
		if (PlayMatch(deck) == 1) //spelar en match med vår kortlek och kollar resultatet
		{
			playerOne.MatchesWon++; //här vann spelare 1
			cout << playerOne.Name << " vann därmed också matchen!\n\n";
		}
		else
		{
			playerTwo.MatchesWon++; //här vann spelare 2
			cout << playerTwo.Name << " vann därmed också matchen!\n\n";
		}

		cout << "Total resultat i matcher:\n"; //skriver ut lite statistik
		cout << playerOne.Name << " " << playerOne.MatchesWon << "\n";
		cout << playerTwo.Name << " " << playerTwo.MatchesWon << "\n";
		cout << "\nTotalt resultat i rundor:\n";
		cout << playerOne.Name << " " << playerOne.RoundsWon << "\n";
		cout << playerTwo.Name << " " << playerTwo.RoundsWon << "\n";

		if (TakeIntInput("\n\nVill ni fortsätta spela?\n1. Ja\n2. Nej, avsluta\n\n", 1, 2) == 2) //kollar om man vill fortsätta spela
			keepPlaying = false;
	}

	cout << "\n\n";
}