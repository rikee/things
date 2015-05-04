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
	posX = 0;
	posY = 0;
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
	posX = 0;
	posY = 0;
}

void Card::paintCard(HWND cHWND, HDC hdc)
{
	RECT rect;
	GetClientRect(cHWND, &rect);
	BITMAP bm;
	HDC oldDC = CreateCompatibleDC(hdc);
	HBITMAP image = mLoadImg(&imageName[0]);
	HBITMAP oldBmp;
	BLENDFUNCTION bf;

	GetObject(image, sizeof(bm), &bm);

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 0xff;
	bf.AlphaFormat = AC_SRC_ALPHA;

	oldBmp = (HBITMAP)SelectObject(oldDC, image);
	AlphaBlend(hdc, posX, posY, cardWidth, cardHeight, oldDC, getGridPositionX(), getGridPositionY(), cardWidth, cardHeight, bf);

	SelectObject(oldDC, oldBmp);
	DeleteDC(oldDC);
}

int Card::getValue()
{
	return value;
}
char Card::getSuit()
{
	return suit;
}
void Card::flipCard()
{
	faceUp = !faceUp;
}
bool Card::isFaceUp()
{
	return faceUp;
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
void Card::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}
int Card::getPositionX()
{
	return posX;
}
int Card::getPositionY()
{
	return posY;
}
HBITMAP Card::mLoadImg(WCHAR *szFilename)
{
	HBITMAP result = NULL;

	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(szFilename,false);
	bitmap->GetHBITMAP(NULL, &result);
	delete bitmap;
	return result;
}