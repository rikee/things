#ifndef THIEVES_H
#define THIEVES_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include "resource.h"
#include "deck.h"

BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

class Thieves
{
public:
	Thieves(HWND hwnd);
	void paintScreen();
	void setHWND(HWND hwnd);
	void setHDC(HDC hdc);
	void releaseDC();
	void setState(int s);
	int getState();
	void processClick(int x, int y);
	void resetPoints(int val = 0);

	static std::string wndTitle;
	static int wndWidth;
	static int wndHeight;
	
private:
	void writePoints();
	std::vector<int> readPoints();
	void paintPoints();
	void paintCard(Card card);
	void eraseCard(Card card, char type);
	void dealHand();
	void initializeHand();
	std::vector<Deck> drawCardColumns(Deck &currDeck);
	int getClickedStack(int mouseX, int mouseY);
	bool boardClear();
	bool noDrawPile();
	int getCardValue(Card cleared);
	
	int state; // 0 = not started, 1 = game over prompt, 2 = during hand

	HWND cHWND;
	HWND cDlg;
	HDC cHDC;
	int high;
	int low;
	int average;
	int games;
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
	HWND initDialog();
	HWND initDialogHigh();
};

#endif