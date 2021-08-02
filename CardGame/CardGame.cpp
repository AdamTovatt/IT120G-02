#include <iostream>
#include <ctime>
#include <windows.h>
#include <thread>

#pragma execution_character_set( "utf-8" )

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
}

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