#ifndef KINGS_H
#define KINGS_H

#include <Windows.h>
#include <string>
#include "card.h"
#include "deck.h"

class Kings
{
public:
	Kings(HWND hwnd);
	void paintScreen();

	HWND cHWND;

	static std::string wndTitle;
	static int wndWidth;
	static int wndHeight;
	
private:
	void paintCard(bool faceUp, int x, int y);

	int cardWidth;
	int cardHeight;
	std::wstring cardImage;
	int gridWidth;
	int gridHeight;
	int cardBackPosition;
	int jokers;
};

#endif