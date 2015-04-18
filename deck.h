#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include "card.h"
#include "helper.h"

struct Deck
{
public:
	Deck(int j);
	void shuffleDeck();
	Card drawCard();

private:
	static int getRandom(int i);

	std::vector<Card> deck;
	int jokers;
};

#endif