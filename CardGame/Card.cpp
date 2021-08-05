#include <string>

using namespace std;

class Card
{
public:
	int Value; //kortets val�r
	int Color; //kortets f�rg

	Card() //default konstruktor f�r kompilatorn klagade p� att det inte fanns annars
	{
		Value = 0;
		Color = 0;
	}

	Card(int newValue, int newColor) //konstruktor som tar in ett v�rde och en f�rg p� ett kort som ska skapas
	{
		Value = newValue;
		Color = newColor;
	}

	bool operator==(const Card& other) //en == operator s� att vi kan j�mf�ra kort med == senare
	{
		return other.Value == Value && other.Color == Color;
	}

	bool operator!=(const Card& other) //en != operator s� att vi kan j�mf�ra kort med != senare
	{
		return !(other.Value == Value && other.Color == Color);
	}

	bool operator<(const Card& other) //en < operator s� att vi kan j�mf�ra kort med < senare
	{
		int otherSum = other.Value * 10 + other.Color;
		int thisSum = Value * 10 + Color;

		return thisSum < otherSum;
	}

	bool operator>(const Card& other) //en > operator s� att vi kan j�mf�ra kort med > senare
	{
		int otherSum = other.Value * 10 + other.Color;
		int thisSum = Value * 10 + Color;

		return thisSum > otherSum;
	}
};