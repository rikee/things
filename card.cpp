#include "card.h"

Card::Card()
{
	value = -1;
	suit = 'j';
	faceUp = false;
	cardWidth = 75;
	cardHeight = 100;
	imageName = "";
	gridWidth = 100;
	gridHeight = 100;
}
Card::Card(int v, char s)
{
	value = v;
	suit = s;
	faceUp = false;
	cardWidth = 75;
	cardHeight = 100;
	imageName = "";
	gridWidth = 100;
	gridHeight = 100;
}

void Card::setCardDimentions(int x, int y)
{
	cardWidth = x;
	cardHeight = y;
}
void Card::setImageName(std::string name)
{
	imageName = name;
}
void Card::setGridDimentions(int x, int y)
{
	gridWidth = x;
	gridHeight = y;
}
int Card::getGridPositionX()
{
	if(!faceUp)
	{
		return 0;
	}
	switch(suit)
	{
	case 'j':
		return gridWidth;
	default:
		return gridWidth * (value - 1);
	}
}
int Card::getGridPositionY()
{
	if(!faceUp)
	{
		return 0;
	}
	switch(suit)
	{
	case 'j':
		return gridHeight;
	case 'c':
		return gridHeight;
	}
}

void Card::drawCard(HWND cHWND)
{
	HBITMAP hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL),imageName.c_str(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	HDC hdc = GetDC(cHWND);
	HDC image_dc = CreateCompatibleDC(hdc);
	HBITMAP old_hbitmap = (HBITMAP)SelectObject(image_dc,hbm);
	BitBlt(hdc,50,50,cardWidth,cardHeight,image_dc,0,0,SRCCOPY);
	BitBlt(hdc,250,50,cardWidth,cardHeight,image_dc,0,100,SRCCOPY);
}