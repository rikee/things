#include "deck.h"

Deck::Deck(int j)
{
	jokers = j;
	deck = newDeck();
}
Deck::Deck(int j, std::vector<Card> custDeck)
{
	jokers = j;
	deck = custDeck;
}

std::vector<Card> Deck::newDeck()
{
	std::vector<Card> tmpDeck;
	for(int i = 0; i < jokers; i++)
	{
		tmpDeck.push_back(Card('j'));
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
			tmpDeck.push_back(Card(suit, j));
		}
	}
	return tmpDeck;
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
void Deck::discardTop()
{
	deck.pop_back();
}

int Deck::getRandom(int i)
{
	return std::rand() % i;
}
int Deck::getRemainingCount()
{
	return deck.size();
}
void Deck::getNewDeck()
{
	deck = newDeck();
}
std::vector<Card> Deck::getCardVector()
{
	return deck;
}