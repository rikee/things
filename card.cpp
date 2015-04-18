#include "card.h"

Card::Card()
{
	value = -1;
	suit = 'j';
	faceUp = false;
	cardWidth = 75;
	cardHeight = 100;
	imageName = L"";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 1;
}
Card::Card(char s, int v)
{
	suit = s;
	value = v;
	faceUp = false;
	cardWidth = 75;
	cardHeight = 100;
	imageName = L"";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 1;
}

void Card::drawCard(HWND cHWND, int x, int y)
{
	HDC hdc = GetDC(cHWND);
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Image image(imageName.c_str());
	graphics.DrawImage(&image, x, y, getGridPositionX(), getGridPositionY(), cardWidth, cardHeight, Gdiplus::UnitPixel);
}

void Card::flipCard()
{
	faceUp = !faceUp;
}

void Card::setCardDimentions(int x, int y)
{
	cardWidth = x;
	cardHeight = y;
}
void Card::setImageName(std::wstring name)
{
	imageName = name;
}
void Card::setGridDimentions(int x, int y)
{
	gridWidth = x;
	gridHeight = y;
}
void Card::setCardBackPosition(int x)
{
	cardBackPosition = x;
}
int Card::getGridPositionX()
{
	if(!faceUp)
	{
		return cardBackPosition * gridWidth;
	}
	else if(suit == 'j')
	{
		return 0;
	}
	else {
		return gridWidth * (value - 1);
	}
}
int Card::getGridPositionY()
{
	if(faceUp)
	{
		switch(suit)
		{
		case 'j':
			return 0;
		case 'c':
			return gridHeight;
		case 'd':
			return 2 * gridHeight;
		case 'h':
			return 3 * gridHeight;
		case 's':
			return 4 * gridHeight;
		}
	}
	return 0;
}