#ifndef CARD_H
#define CARD_H

#include <Windows.h>
#include <GdiPlus.h>
#include <string>

class Card
{
public:
	Card();
	Card(char s, int v = 1);
	void drawCard(HWND cHWND);
	void flipCard();
	void setCardDimentions(int x, int y);
	void setImageName(std::wstring name);
	void setGridDimentions(int x, int y);
	void setCardBackPosition(int x);
	void setPosition(int x, int y);
	int getPositionX();
	int getPositionY();

private:
	char suit;
	int value;
	bool faceUp;
	int cardWidth;
	int cardHeight;
	std::wstring imageName;
	int gridWidth;
	int gridHeight;
	int cardBackPosition;
	int posX;
	int posY;

	int getGridPositionX();
	int getGridPositionY();
};

#endif