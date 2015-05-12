#include "kings.h"

std::string Kings::wndTitle = "Kings Corners";
int Kings::wndWidth = 523;
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
	cardImageSelected = L"cards_sprite_negative.png";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 2;
	jokers = 0;
	drawPilePosX = 398;
	drawPilePosY = 3;
	activePosX = 320;
	activePosY = 3;
	activeSlot.setPosition(activePosX, activePosY);
	messageTopLine = "";
	messageBottomLine = "";
	selectedSlotIndex = -1;
	fakeDeckTop.setPosition(drawPilePosX, drawPilePosY);
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

HWND Kings::initDialogStuck()
{
	return CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_L), cHWND, (DLGPROC)DialogProc);
}
HWND Kings::initDialogWon()
{
	return CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_W), cHWND, (DLGPROC)DialogProc);
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

	if(deck.getRemainingCount() >= 0)
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
void Kings::paintMessage()
{
	TEXTMETRIC textInfo;
	GetTextMetrics(cHDC, &textInfo);
	SetBkColor(cHDC, RGB(255,255,255));
	int textY = messageBoxTop + 2;
	int textX = messageBoxLeft + 10;
	TextOut(cHDC, textX, textY, messageTopLine.c_str(), strlen(messageTopLine.c_str()));
	textY += textInfo.tmHeight + 2;
	TextOut(cHDC, textX, textY, messageBottomLine.c_str(), strlen(messageBottomLine.c_str()));
}
void Kings::paintCard(Card card)
{
	card.setCardBackPosition(cardBackPosition);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);

	card.paintCard(cHWND, cHDC);
}
void Kings::paintCard(Card card, bool selected)
{
	card.setCardBackPosition(cardBackPosition);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);

	if(selected)
	{
		card.setImageName(cardImageSelected.c_str());
		card.paintCard(cHWND, cHDC);
		card.setImageName(cardImage.c_str());
	}
	else
	{
		card.paintCard(cHWND, cHDC);
	}
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
	if(state < 1)
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
	paintMessage();

	if(state == 10)
	{
		state = 1;
	}
	if(state == 30)
	{
		state = 3;
	}
}
void Kings::dealHand()
{
	active.setPosition(activePosX, activePosY);
	if(state < 3)
	{
		paintCard(active);
	}
	else
	{
		activeSlot.paintCardSlot(cHWND, cHDC);
	}
	paintCard(fakeDeckTop);
}
void Kings::processClick(int x, int y)
{
	if(state == 1) return;

	int slotIndex = getClickedSlot(x,y);

	int startingCount = deck.getRemainingCount();

	if(state == 3)
	{
		if(clickedDrawPile(x,y))
		{
			if(noDiscards())
			{
				state = 2;
				if(deck.getRemainingCount() > 0)
				{
					active = deck.drawCard();
					active.flipCard();
					active.setPosition(activePosX, activePosY);
				}
				for(size_t i = 0; i < slots.size(); i++)
				{
					slots[i].deselect();
				}
			}
			else
			{
				messageTopLine = "There are still";
				messageBottomLine = "cards to remove!";
			}
			InvalidateRect(cHWND, NULL, NULL);
			return;
		}
		else if(slotIndex < 0)
		{
			return;
		}

		for(size_t i = 0; i < slots.size(); i++)
		{
			slots[i].deselect();
		}
		int val = slots[slotIndex].getCard().getValue();
		if( val < 11 && slots[slotIndex].isFilled())
		{
			if(val == 10 && selectedSlotIndex != slotIndex)
			{
				slots[slotIndex].removeCard();
				selectedSlotIndex = -1;
			}
			else if(selectedSlotIndex > -1 &&
					val + slots[selectedSlotIndex].getCard().getValue() == 10 &&
					selectedSlotIndex != slotIndex)
			{
				slots[slotIndex].removeCard();
				slots[selectedSlotIndex].removeCard();
				selectedSlotIndex = -1;
			}
			else
			{
				slots[slotIndex].select();
				selectedSlotIndex = slotIndex;
				switch(val)
				{
				case 9:
					messageTopLine = "Pick an ace.";
					break;
				case 8:
					messageTopLine = "Pick a 2.";
					break;
				case 7:
					messageTopLine = "Pick a 3.";
					break;
				case 6:
					messageTopLine = "Pick a 4.";
					break;
				case 5:
					messageTopLine = "Pick a 5.";
					break;
				case 4:
					messageTopLine = "Pick a 6.";
					break;
				case 3:
					messageTopLine = "Pick a 7.";
					break;
				case 2:
					messageTopLine = "Pick an 8.";
					break;
				case 1:
					messageTopLine = "Pick a 9.";
					break;
				}
				messageBottomLine = "";
				InvalidateRect(cHWND,NULL,NULL);
				return;
			}
		}
		else
		{
			selectedSlotIndex = -1;
		}
	}

	if(slotIndex < 0) return;

	if(state == 2)
	{
		if(slots[slotIndex].isFilled()) return;

		if(active.getValue() == 13)
		{
			if(slotIndex != 0 && slotIndex != 3 && slotIndex != 12 && slotIndex != 15)
			{
				messageTopLine = "Kings go on the corners!";
				paintMessage();
				InvalidateRect(cHWND,NULL,NULL);
				return;
			}
			active.flipCard();
		}
		else if(active.getValue() == 12)
		{
			if(slotIndex != 4 && slotIndex != 7 && slotIndex != 8 && slotIndex != 11)
			{
				messageTopLine = "Queens go on the sides!";
				paintMessage();
				InvalidateRect(cHWND,NULL,NULL);
				return;
			}
			active.flipCard();
		}
		else if(active.getValue() == 11)
		{
			if(slotIndex != 1 && slotIndex != 2 && slotIndex != 13 && slotIndex != 14)
			{
				messageTopLine = "Jacks go on the";
				messageBottomLine = "top or bottom!";
				paintMessage();
				InvalidateRect(cHWND,NULL,NULL);
				return;
			}
			active.flipCard();
		}

		slots[slotIndex].setCard(active);
		if(boardFull())
		{
			activeSlot.paintCardSlot(cHWND, cHDC);
			state = 3;
			InvalidateRect(cHWND,NULL,NULL);
			if(isLost())
			{
				state = 30;
				initDialogStuck();
			}
			return;
		}
		if(deck.getRemainingCount() > 0)
		{
			active = deck.drawCard();
			active.flipCard();
			active.setPosition(activePosX, activePosY);
		}
	}
	
	messageTopLine = "";
	messageBottomLine = "";
	InvalidateRect(cHWND,NULL,NULL);

	if(isLost())
	{
		state = 1;
		initDialogStuck();
	}
	if(startingCount == 0 && isWon())
	{
		state = 10;
		initDialogWon();
	}
}
void Kings::initSlots()
{
	while(slots.size() > 0)
	{
		slots.pop_back();
	}
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
			if(slots[i].isSelected())
			{
				paintCard(slots[i].getCard(), true);
			}
			else
			{
				paintCard(slots[i].getCard());
			}
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
bool Kings::clickedDrawPile(int mouseX, int mouseY)
{
	if(mouseX > activePosX)
	{
		return true;
	}
	return false;
}

bool Kings::isWon()
{
	if(deck.getRemainingCount() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Kings::isLost()
{
	if(state == 3)
	{
		for(size_t i = 0; i < slots.size(); i++)
		{
			int val = slots[i].getCard().getValue();
			if(!slots[i].isFilled())
			{
				return false;
			}
			else if(val > 10)
			{
				continue;
			}
			else if(val == 10)
			{
				return false;
			}
			else
			{
				for(size_t j = i + 1; j < slots.size(); j++)
				{
					if(val + slots[j].getCard().getValue() == 10)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	else
	{
		if( active.getValue() == 13
			&& slots[0].isFilled() && slots[3].isFilled() && slots[12].isFilled() && slots[15].isFilled())
		{
			return true;
		}
		else if( active.getValue() == 12
			&& slots[4].isFilled() && slots[7].isFilled() && slots[8].isFilled() && slots[11].isFilled())
		{
			return true;
		}
		else if( active.getValue() == 11
			&& slots[1].isFilled() && slots[2].isFilled() && slots[13].isFilled() && slots[14].isFilled())
		{
			return true;
		}
	}
	return false;
}
bool Kings::boardFull()
{
	for(size_t i = 0; i < slots.size(); i++)
	{
		if(!slots[i].isFilled())
		{
			return false;
		}
	}
	return true;
}
bool Kings::noDiscards()
{
	for(size_t i = 0; i < slots.size(); i++)
	{
		int val = slots[i].getCard().getValue();
		if(!slots[i].isFilled())
		{
			continue;
		}
		else if(val > 10)
		{
			continue;
		}
		else if(val == 10)
		{
			return false;
		}
		else
		{
			for(size_t j = i + 1; j < slots.size(); j++)
			{
				if(slots[j].isFilled() && val + slots[j].getCard().getValue() == 10)
				{
					return false;
				}
			}
		}
	}
	return true;
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
	selected = false;
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
bool Slot::isSelected()
{
	return selected;
}
void Slot::select()
{
	selected = true;
}
void Slot::deselect()
{
	selected = false;
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