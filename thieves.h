#ifndef THIEVES_H
#define THIEVES_H

#include <Windows.h>
#include <string>
#include "card.h"
#include "deck.h"

class Thieves
{
public:
	Thieves(HWND hwnd);
	void paintScreen();

	HWND cHWND;
	
private:
	void paintPoints();
	void paintCard();

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
};

#endif