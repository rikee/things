#include "kings.h"

std::string Kings::wndTitle = "Kings Corners";
int Kings::wndWidth = 518;
int Kings::wndHeight = 458;

Kings::Kings(HWND hwnd)
	:deck(0)
{
	state = 0;
	cHWND = hwnd;
	cDlg = NULL;
	cHDC = NULL;
	remainingBoxLeft = 320;
	remainingBoxTop = 120;
	remainingBoxRight = 460;
	remainingBoxBottom = 140;
	messageBoxLeft = 320;
	messageBoxTop = 180;
	messageBoxRight = 505;
	messageBoxBottom = 220;
	cardWidth = 75;
	cardHeight = 100;
	cardImage = L"cards_sprite.png";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 2;
	jokers = 0;
	drawPilePosX = 398;
	drawPilePosY = 3;
	activePosX = 320;
	activePosY = 3;
}

void Kings::setHWND(HWND hwnd)
{
	cHWND = hwnd;
}
void Kings::setState(int s)
{
	state = s;
}
int Kings::getState()
{
	return state;
}

void Kings::paintFrame()
{
	RECT cRect;
	GetClientRect(cHWND, &cRect);

	HBRUSH hbrush = CreateSolidBrush(RGB(255,255,255));;
	HBRUSH oldBrush = (HBRUSH)SelectObject(cHDC, hbrush);
	Rectangle(cHDC, remainingBoxLeft, remainingBoxTop, remainingBoxRight, remainingBoxBottom);
	Rectangle(cHDC, messageBoxLeft, messageBoxTop, messageBoxRight, messageBoxBottom);
	SelectObject(cHDC, oldBrush);
	DeleteObject(hbrush);

	if(deck.getRemainingCount() > 0)
	{
		TEXTMETRIC textInfo;
		GetTextMetrics(cHDC, &textInfo);
		SetBkColor(cHDC, RGB(255,255,255));
		int textY = remainingBoxTop + 2;
		int textX = remainingBoxLeft + 10;
		std::string cardsLeft = std::to_string(static_cast<long long>(deck.getRemainingCount() + 1));
		cardsLeft += " cards left";
		TextOut(cHDC, textX, textY, cardsLeft.c_str(), strlen(cardsLeft.c_str()));
	}
}
void Kings::paintCard(Card card)
{
	card.setCardBackPosition(cardBackPosition);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);

	card.paintCard(cHWND, cHDC);
}
void Kings::initializeHand()
{
	initSlots();
	deck.getNewDeck();
	deck.shuffleDeck();
	active = deck.drawCard();
	active.flipCard();
	dealHand();
}
void Kings::paintScreen()
{
	if(state < 2)
	{
		initializeHand();
		state = 2;
	}
	else
	{
		dealHand();
	}
	paintSlots();
	paintFrame();
}
void Kings::dealHand()
{
	active.setPosition(activePosX, activePosY);
	paintCard(active);
	Card fakeDeckTop;
	fakeDeckTop.setPosition(drawPilePosX, drawPilePosY);
	paintCard(fakeDeckTop);
}
void Kings::processClick(int x, int y)
{
	if (state == 1) return;

	int slotIndex = getClickedSlot(x,y);
	if (slotIndex > -1)
	{
		slots[slotIndex].setCard(active);
		active = deck.drawCard();
		active.flipCard();
		active.setPosition(activePosX, activePosY);

		paintFrame();
		InvalidateRect(cHWND,NULL,NULL);
	}
}
void Kings::initSlots()
{
	Slot slot;
	int posX, posY;
	for(int i = 0; i < 4; i++)
	{
		posY = 3 + i * (cardHeight + 1);
		for (int j = 0; j < 4; j++)
		{
			posX = 3 + j * (cardWidth + 1);

			slot.setPosition(posX, posY);
			slot.setType(getSlotType(i, j));
			slots.push_back(slot);
		}
	}
}
void Kings::paintSlots()
{
	for(size_t i = 0; i < slots.size(); i++)
	{
		if (slots[i].isFilled())
		{
			paintCard(slots[i].getCard());
		}
		else
		{
			slots[i].paintCardSlot(cHWND, cHDC);
		}
	}
}
char Kings::getSlotType(int i, int j)
{
	if(i == 0 || i == 3)
	{
		if(j == 0 || j == 3)
		{
			return 'k';
		}
		else if(j == 1 || j == 2)
		{
			return 'j';
		}
	}
	else if(i == 1 || i == 2)
	{
		if(j == 0 || j == 3)
		{
			return 'q';
		}
	}
	return 'o';
}
int Kings::getClickedSlot(int mouseX, int mouseY)
{
	int slotX, slotY;
	for(size_t i = 0; i < slots.size(); i++)
	{
		slotX = slots[i].getPositionX();
		slotY = slots[i].getPositionY();
		if( (mouseX > slotX && mouseX < slotX + cardWidth) &&
			(mouseY > slotY && mouseY < slotY + cardHeight) )
		{
			return i;
		}
	}
	return -1;
}

void Kings::setHDC(HDC hdc)
{
	cHDC = hdc;
}
void Kings::releaseDC()
{
	ReleaseDC(cHWND,cHDC);
}

Slot::Slot()
{
	slotWidth = 75;
	slotHeight = 100;
	slotImage = L"kings_empty.png";
	posX = 0;
	posY = 0;
	filled = false;
	type = 'o';
}
void Slot::paintCardSlot(HWND cHWND, HDC cHDC)
{
	RECT rect;
	GetClientRect(cHWND, &rect);
	BITMAP bm;
	HDC tHDC = CreateCompatibleDC(cHDC);
	HBITMAP image = mLoadImg(&slotImage[0]);
	HBITMAP oldBmp;
	BLENDFUNCTION bf;

	GetObject(image, sizeof(bm), &bm);

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 0xff;
	bf.AlphaFormat = AC_SRC_ALPHA;

	oldBmp = (HBITMAP)SelectObject(tHDC, image);
	AlphaBlend(cHDC, posX, posY, slotWidth, slotHeight, tHDC, 0, 0, slotWidth, slotHeight, bf);

	SelectObject(tHDC, oldBmp);
	DeleteObject(image);
	DeleteDC(tHDC);
}
bool Slot::isFilled()
{
	return filled;
}
int Slot::getPositionX()
{
	return posX;
}
int Slot::getPositionY()
{
	return posY;
}
void Slot::setPosition(int x, int y)
{
	posX = x;
	posY = y;
}
void Slot::setType(char t)
{
	type = t;
}
Card Slot::getCard()
{
	return card;
}
void Slot::setCard(Card c)
{
	card = c;
	card.setPosition(posX, posY);
	filled = true;
}
void Slot::removeCard()
{
	filled = false;
}

HBITMAP Slot::mLoadImg(WCHAR *szFilename)
{
	HBITMAP result = NULL;

	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(szFilename,false);
	bitmap->GetHBITMAP(NULL, &result);
	delete bitmap;
	return result;
}