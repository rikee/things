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
	void setHWND(HWND hwnd);
	void setState(int s);
	int getState();

	HWND cHWND;

	static std::string wndTitle;
	static int wndWidth;
	static int wndHeight;
	
private:
	void paintCard(bool faceUp);

	int state; // 0 = not started, 1 = between hands, 2 = during hand

	int cardWidth;
	int cardHeight;
	std::wstring cardImage;
	int gridWidth;
	int gridHeight;
	int cardBackPosition;
	int jokers;
};

#endif