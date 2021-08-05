#include <string>

using namespace std;

class Player
{
public:
	string Name;
	int MatchesWon;
	int RoundsWon;

	Player() //default konstruktor för kompilatorn klagade annars
	{
		Name = "";
		MatchesWon = 0;
		RoundsWon = 0;
	} 

	Player(string name)
	{
		Name = name;
		MatchesWon = 0;
		RoundsWon = 0;
	}
};