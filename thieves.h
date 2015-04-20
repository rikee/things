#ifndef THIEVES_H
#define THIEVES_H

#include <Windows.h>
#include <string>
#include "deck.h"

class Thieves
{
public:
	Thieves(HWND hwnd);
	void paintScreen();

	HWND cHWND;

	static std::string wndTitle;
	static int wndWidth;
	static int wndHeight;
	
private:
	void paintPoints();
	void paintCard(Card card, bool faceUp);
	void dealHand();
	void initializeHand();
	std::vector<Deck> drawCardColumns(Deck &currDeck);

	int high;
	int low;
	int average;
	int points;
	int cardWidth;
	int cardHeight;
	std::wstring cardImage;
	int gridWidth;
	int gridHeight;
	int cardBackPosition;
	int jokers;
	Deck deck;
	std::vector<Deck> cardColumns;
};

#endif