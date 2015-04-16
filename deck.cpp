#include "deck.h"

Deck::Deck(int j)
	:deck(std::vector<Card>())
{
	jokers = j;
	for(size_t i = 0; i < jokers; i++)
	{
		deck.push_back(Card('j'));
	}
	char suit;
	for(size_t i = 0; i < 4; i++)
	{
		if(i == 0) suit = 'c';
		else if(i == 1) suit = 'd';
		else if(i == 2) suit = 'h';
		else if(i == 3) suit = 's';

		for(size_t j = 1; j < 14; j++)
		{
			deck.push_back(Card(suit, j));
		}
	}
}

void Deck::shuffleDeck()
{
	std::random_shuffle(deck.begin(), deck.end(), getRandom);
}
Card Deck::drawCard()
{
	Card drawnCard = deck[deck.size() - 1];
	deck.pop_back();
	return drawnCard;
}

int Deck::getRandom(int i)
{
	return std::rand() % i;
}