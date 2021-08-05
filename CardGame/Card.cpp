#include <string>

using namespace std;

class Card
{
public:
	int Value; //kortets valör
	int Color; //kortets färg

	Card() //default konstruktor för kompilatorn klagade på att det inte fanns annars
	{
		Value = 0;
		Color = 0;
	}

	Card(int newValue, int newColor) //konstruktor som tar in ett värde och en färg på ett kort som ska skapas
	{
		Value = newValue;
		Color = newColor;
	}

	bool operator==(const Card& other) //en == operator så att vi kan jämföra kort med == senare
	{
		return other.Value == Value && other.Color == Color;
	}

	bool operator!=(const Card& other) //en != operator så att vi kan jämföra kort med != senare
	{
		return !(other.Value == Value && other.Color == Color);
	}

	bool operator<(const Card& other) //en < operator så att vi kan jämföra kort med < senare
	{
		int otherSum = other.Value * 10 + other.Color;
		int thisSum = Value * 10 + Color;

		return thisSum < otherSum;
	}

	bool operator>(const Card& other) //en > operator så att vi kan jämföra kort med > senare
	{
		int otherSum = other.Value * 10 + other.Color;
		int thisSum = Value * 10 + Color;

		return thisSum > otherSum;
	}
};