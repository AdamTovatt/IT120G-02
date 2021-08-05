#include <string>

using namespace std;

class Player
{
public:
	string Name;
	int MatchesWon;
	int RoundsWon;

	Player() { } //default konstruktor för kompilatorn klagade annars

	Player(string name)
	{
		Name = name;
	}
};