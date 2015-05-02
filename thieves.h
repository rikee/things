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
	void setHWND(HWND hwnd);
	void setHDC(HDC hdc);
	void setState(int s);
	int getState();
	void processClick(int x, int y);

	static std::string wndTitle;
	static int wndWidth;
	static int wndHeight;
	
private:
	void paintPoints();
	void paintCard(Card card);
	void eraseCard(Card card);
	void dealHand();
	void initializeHand();
	std::vector<Deck> drawCardColumns(Deck &currDeck);
	int getClickedStack(int mouseX, int mouseY);
	bool boardClear();
	int getCardValue(Card cleared);
	
	int state; // 0 = not started, 1 = between hands, 2 = during hand

	HWND cHWND;
	HDC cHDC;
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
	int drawPileY;
	Card activeCard;

	void moveToActiveSpot(Card &card);
};

#endif