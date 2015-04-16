#ifndef CARD_H
#define CARD_H

#include <Windows.h>
#include <GdiPlus.h>
#include <string>

class Card
{
public:
	Card();
	Card(int v, char s);
	void drawCard(HWND cHWND);
	void setCardDimentions(int x, int y);
	void setImageName(std::string name);
	void setGridDimentions(int x, int y);

private:
	int value;
	char suit;
	bool faceUp;
	int cardWidth;
	int cardHeight;
	std::string imageName;
	int gridWidth;
	int gridHeight;

	int getGridPositionX();
	int getGridPositionY();
};

#endif