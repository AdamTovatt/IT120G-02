#include "Card.cpp"
#include <stdlib.h>

#pragma execution_character_set( "utf-8" )

class CardDeck
{
private:
	Card cards[52];
	const string names[13] = { "ett", "två", "tre", "fyra", "fem", "sex", "sju", "åtta", "nio", "tio", "knekt", "dam", "kung" };
	const string colors[4] = { "spader", "hjärter", "ruter", "klöver" };

public:
	CardDeck() //skapar en ny kortlek som fylls med kort
	{
		for (int i = 0; i < 4; i++) //loopar igenom färger, det finns fyra stycken
		{
			for (int j = 0; j < 13; j++) //loopar igenom kortvalörer, det finns 13 stycken
			{
				cards[i * 13 + j] = Card(j + 1, i + 1);
			}
		}
	}

	Card GetFirstCard(Card ignoreCard) //tar "översta" kortet i kortleken fast tar inte med kortet man redan dragit
	{
		if (cards[0] == ignoreCard) //om första kortet råkar vara det vi inte ska ta med tar vi nästa kort bara vilket ger samma resultat som att faktiskt ta bort det ignorerade kortet och sen dra ett kort
			return cards[1];
		return cards[0];
	}

	Card GetFirstCard() //tar "översta" kortet i kortleken
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

	string GetNameOfCard(Card card)
	{
			return colors[card.Color - 1] + " " + names[card.Value - 1];
	}
};