#include "Card.cpp"
#include <stdlib.h>

class CardDeck
{
private:
	Card cards[52];

public:
	CardDeck()
	{
		for (int i = 0; i < 4; i++) //loopar igenom färger, det finns fyra stycken
		{
			for (int j = 0; j < 13; j++) //loopar igenom kortvalörer, det finns 13 stycken
			{
				cards[i * 13 + j] = Card(j + 1, i + 1);
			}
		}
	}

	Card GetFirstCard()
	{
		return cards[0];
	}

	void Shuffle() //blandar kortleken med fisher yates metoden
	{
		for (int i = (sizeof(cards)/sizeof(*cards)) - 1; i > 0; --i)
		{
			int switchIndex = rand() % (i + 1);
			Card temp = cards[i];
			cards[i] = cards[switchIndex];
			cards[switchIndex] = temp;
		}
	}
};