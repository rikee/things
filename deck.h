#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include "card.h"

struct Deck
{
public:
	Deck(int j);
	Deck(int j, std::vector<Card> custDeck);
	void shuffleDeck();
	Card drawCard();
	void discardTop();
	int getRemainingCount();
	void getNewDeck();
	std::vector<Card> getCardVector();

private:
	static int getRandom(int i);

	std::vector<Card> deck;
	int jokers;
	
	std::vector<Card> newDeck();
};

#endif