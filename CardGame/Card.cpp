class Card
{
public:
	int value;
	int color;

	Card() //default constructor för kompilatorn klagade på att det inte fanns annars
	{
		value = 0;
		color = 0;
	}

	Card(int newValue, int newColor)
	{
		value = newValue;
		color = newColor;
	}

	bool operator==(const Card& other)
	{
		return other.value == value && other.color == color;
	}

	bool operator!=(const Card& other)
	{
		return !(other.value == value && other.color == color);
	}

	bool operator<(const Card& other)
	{
		int otherSum = other.value * 10 + other.color;
		int thisSum = value * 10 + color;

		return otherSum < thisSum;
	}

	bool operator>(const Card& other)
	{
		int otherSum = other.value * 10 + other.color;
		int thisSum = value * 10 + color;

		return otherSum > thisSum;
	}
};