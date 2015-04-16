#ifndef THIEVES_H
#define THIEVES_H

#include <Windows.h>
#include <string>
#include "card.h"

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
	std::string cardImage;
	int gridWidth;
	int gridHeight;
};

#endif