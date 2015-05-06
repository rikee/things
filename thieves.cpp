#include "thieves.h"

std::string Thieves::wndTitle = "Forty Thieves";
int Thieves::wndWidth = 578;
int Thieves::wndHeight = 388;

Thieves::Thieves(HWND hwnd)
	:deck(3)
{
	state = 0;
	cHWND = hwnd;
	cDlg = NULL;
	cHDC = NULL;
	high = 400;
	low = 100;
	average = 190;
	games = 0;
	points = 1;
	cardWidth = 75;
	cardHeight = 100;
	cardImage = L"legacy_sources/cards_sprite.png";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 1;
	jokers = 3;
	drawPileY = 194;
}

void Thieves::setHWND(HWND hwnd)
{
	cHWND = hwnd;
}
void Thieves::setState(int s)
{
	state = s;
}
int Thieves::getState()
{
	return state;
}


HWND Thieves::initDialog()
{
	return CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDDT_DIALOG_L), cHWND, (DLGPROC)DialogProc);
}
HWND Thieves::initDialogHigh()
{
	return CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDDT_DIALOG_L_HS), cHWND, (DLGPROC)DialogProc);
}
void Thieves::writePoints()
{
	std::ofstream data("record.tng");

	high = points > high ? points : high;
	low = points < low ? points : low;
	average = (average * games + points) / (games + 1);

	if(data.is_open())
	{
		data	<< high		<< std::endl
				<< low		<< std::endl
				<< average	<< std::endl
				<< ++games	<< std::endl;
	}

	data.close();
}
std::vector<int> Thieves::readPoints()
{
	std::ifstream data("record.tng");
	std::string item;
	std::vector<int> items;
	int tmp;

	while(data >> item)
	{
		std::stringstream str(item);
		str >> tmp;
		if (!str) break;

		items.push_back(tmp);
	}

	data.close();
	return items;
}
void Thieves::paintPoints()
{
	RECT cRect;
	GetClientRect(cHWND, &cRect);

	int clientWidth = cRect.right - cRect.left;
	int clientHeight = cRect.bottom - cRect.top;
	int thickness = 22;
	HBRUSH hbrush = CreateSolidBrush(RGB(255,255,255));;
	HBRUSH oldBrush = (HBRUSH)SelectObject(cHDC, hbrush);
	Rectangle(cHDC, 0, clientHeight - thickness, clientWidth, clientHeight);
	SelectObject(cHDC, oldBrush);
	DeleteObject(hbrush);

	TEXTMETRIC textInfo;
	GetTextMetrics(cHDC, &textInfo);
	SetBkColor(cHDC, RGB(255,255,255));
	int textY = clientHeight - textInfo.tmHeight - 3;
	int textX = 20;
	std::string highText = std::to_string(static_cast<long long>(high));
	std::string lowText = std::to_string(static_cast<long long>(low));
	std::string averageText = std::to_string(static_cast<long long>(average));
	std::string pointsText = std::to_string(static_cast<long long>(points));

	TextOut(cHDC, textX, textY, "High:", strlen("High:"));
	textX += textInfo.tmAveCharWidth * strlen("High:") + 3;
	TextOut(cHDC, textX, textY, highText.c_str(), strlen(highText.c_str()));
	textX += textInfo.tmAveCharWidth * strlen(highText.c_str()) + 20;
	TextOut(cHDC, textX, textY, "Low:", strlen("Low:"));
	textX += textInfo.tmAveCharWidth * strlen("Low:") + 3;
	TextOut(cHDC, textX, textY, lowText.c_str(), strlen(lowText.c_str()));
	textX += textInfo.tmAveCharWidth * strlen(lowText.c_str()) + 20;
	TextOut(cHDC, textX, textY, "Average:", strlen("Average:"));
	textX += textInfo.tmAveCharWidth * strlen("Average:") + 3;
	TextOut(cHDC, textX, textY, averageText.c_str(), strlen(averageText.c_str()));
	textX += textInfo.tmAveCharWidth * strlen(averageText.c_str()) + 20;
	TextOut(cHDC, textX, textY, "Points:", strlen("Points:"));
	textX += textInfo.tmAveCharWidth * strlen("Points:") + 3;
	TextOut(cHDC, textX, textY, pointsText.c_str(), strlen(pointsText.c_str()));
}
void Thieves::paintCard(Card card)
{
	card.setCardBackPosition(cardBackPosition);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);

	card.paintCard(cHWND, cHDC);
}
void Thieves::eraseCard(Card card, char type)
{
	RECT cRect;
	GetClientRect(cHWND, &cRect);
	cHDC = GetDC(cHWND);

	HBRUSH hbrush = CreateSolidBrush(RGB(0,127,0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(cHDC, hbrush);
	HPEN hpen = CreatePen(PS_NULL, 0, RGB(0,127,0));
	HPEN oldPen = (HPEN)SelectObject(cHDC, hpen);

	int leftEdge, topEdge, rightEdge, bottomEdge;
	switch(type)
	{
	case 'd':
		leftEdge = card.getPositionX() + cardWidth - 10;
		topEdge = card.getPositionY();
		rightEdge = card.getPositionX() + cardWidth + 1;
		bottomEdge = card.getPositionY() + cardHeight;
		break;

	case 'l':
		leftEdge = card.getPositionX();
		topEdge = card.getPositionY();
		rightEdge = card.getPositionX() + cardWidth;
		bottomEdge = card.getPositionY() + cardHeight;
		break;

	default:
		leftEdge = card.getPositionX();
		topEdge = card.getPositionY() + cardHeight - 22;
		rightEdge = card.getPositionX() + cardWidth;
		bottomEdge = card.getPositionY() + cardHeight;
	}
	Rectangle(cHDC, leftEdge, topEdge, rightEdge, bottomEdge);

	SelectObject(cHDC, oldBrush);
	DeleteObject(hbrush);
	SelectObject(cHDC, oldPen);
	DeleteObject(hpen);
}

void Thieves::initializeHand()
{
	deck.getNewDeck();
	deck.shuffleDeck();
	cardColumns = drawCardColumns(deck);
	dealHand();
}
void Thieves::paintScreen()
{
	if(state < 2)
	{
		std::vector<int> pointsArr = readPoints();
		high = pointsArr[0];
		low = pointsArr[1];
		average = pointsArr[2];
		games = pointsArr[3];
		resetPoints();
	}
	paintPoints();

	if(state < 2)
	{
		initializeHand();
		state = 2;
	}
	else
	{
		dealHand();
	}
}
void Thieves::dealHand()
{
	std::vector<Card> tmpDeck;
	Card topCard;
	for(size_t i = 0; i < cardColumns.size(); i++)
	{
		tmpDeck = cardColumns[i].getCardVector();
		for(size_t j = 0; j < tmpDeck.size(); j++)
		{
			topCard = tmpDeck[j];
			paintCard(topCard);
		}
	}
	if(state < 2)
	{
		int drawPileIndex = cardColumns.size() - 1;
		Card erased = cardColumns[drawPileIndex].getCardFromIndex(cardColumns[drawPileIndex].getRemainingCount() - 1);
		cardColumns[drawPileIndex].discardTop();
		eraseCard(erased, 'd');
		activeCard = erased;
		moveToActiveSpot(activeCard);
		if(!activeCard.isFaceUp()) activeCard.flipCard();
		if (cardColumns[drawPileIndex].getRemainingCount() > 0) {
			Card redraw = cardColumns[drawPileIndex].getCardFromIndex(cardColumns[drawPileIndex].getRemainingCount() - 1);
			paintCard(redraw);
		}
	}
	paintCard(activeCard);
}

void Thieves::processClick(int x, int y)
{
	if (state == 1) return;

	int stackIndex = getClickedStack(x,y);
	
	if(stackIndex == cardColumns.size() - 1 && noDrawPile())
	{
		state = 1;
		if(points > high)
		{
			writePoints();
			cDlg = initDialogHigh();
		}
		else
		{
			writePoints();
			cDlg = initDialog();
		}
	}

	if (stackIndex >= 0)
	{
		if (cardColumns[stackIndex].getRemainingCount() > 0) {
			Card erased = cardColumns[stackIndex].getCardFromIndex(cardColumns[stackIndex].getRemainingCount() - 1);
			if( erased.getValue() - activeCard.getValue() == 1 || 
				erased.getValue() - activeCard.getValue() == -1 ||
				stackIndex == cardColumns.size() - 1 ||
				activeCard.getSuit() == 'j' || erased.getSuit() == 'j')
			{
				cardColumns[stackIndex].discardTop();
				if(cardColumns[stackIndex].getRemainingCount() == 0)
				{
					eraseCard(erased, 'l');
				}
				else if(stackIndex == cardColumns.size() - 1)
				{
					eraseCard(erased, 'd');
				}
				else
				{
					eraseCard(erased, 's');
				}
				points += getCardValue(erased);
				paintPoints();
				activeCard = erased;
				moveToActiveSpot(activeCard);
				if(!activeCard.isFaceUp()) activeCard.flipCard();
				paintCard(activeCard);
				if (cardColumns[stackIndex].getRemainingCount() > 0) {
					Card redraw = cardColumns[stackIndex].getCardFromIndex(cardColumns[stackIndex].getRemainingCount() - 1);
					paintCard(redraw);
				}
			}
		}
	}
	if(boardClear())
	{
		points += 21;
		paintPoints();
		initializeHand();
	}
}

std::vector<Deck> Thieves::drawCardColumns(Deck &currDeck)
{
	std::vector<Deck> deckCols;
	Card topCard;
	for(size_t i = 0; i < 7; i++)
	{
		std::vector<Card> column;
		for(size_t j = 0; j < 5; j++)
		{
			topCard = currDeck.drawCard();
			topCard.flipCard();
			topCard.setPosition(i * (cardWidth + 1) + 3, j * 20 + 3);
			column.push_back(topCard);
		}
		deckCols.push_back(Deck(0, column));
	}
	size_t count = 0;
	std::vector<Card> drawPile;
	while(currDeck.getRemainingCount() > 0)
	{
		topCard = currDeck.drawCard();
		topCard.setPosition(count * 5 + 3, drawPileY);
		drawPile.push_back(topCard);
		count++;
	}
	deckCols.push_back(Deck(0, drawPile));
	return deckCols;
}

int Thieves::getClickedStack(int mouseX, int mouseY)
{
	int topCardX, topCardY;
	for(int i = 0; i < (int)cardColumns.size() - 1; i++)
	{
		if(cardColumns[i].getRemainingCount() > 0)
		{
			topCardX = cardColumns[i].getCardFromIndex(cardColumns[i].getRemainingCount() - 1).getPositionX();
			topCardY = cardColumns[i].getCardFromIndex(cardColumns[i].getRemainingCount() - 1).getPositionY();
			if( (mouseX > topCardX && mouseX < topCardX + cardWidth) &&
				(mouseY > topCardY && mouseY < topCardY + cardHeight) )
			{
				return i;
			}
		}
	}
	if(mouseY > drawPileY)
	{
		return cardColumns.size() - 1;
	}
	return -1;
}
void Thieves::moveToActiveSpot(Card &card)
{
	card.setPosition(3 * (cardWidth + 1) + 3, drawPileY);
}
bool Thieves::boardClear()
{
	for(int i = 0; i < (int)cardColumns.size() - 1; i++)
	{
		if(cardColumns[i].getRemainingCount() > 0) return false;
	}
	return true;
}
bool Thieves::noDrawPile()
{
	return cardColumns[cardColumns.size() - 1].getRemainingCount() == 0;
}
int Thieves::getCardValue(Card cleared)
{
	if(!cleared.isFaceUp())
	{
		return 0;
	}
	if(cleared.getSuit() == 'j')
	{
		return 0;
	}
	if(cleared.getValue() == 1 || cleared.getValue() == 13)
	{
		return 8;
	}
	else if(cleared.getValue() < 4 || cleared.getValue() > 10)
	{
		return 6;
	}
	else if(cleared.getValue() < 6 || cleared.getValue() > 8)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}
void Thieves::setHDC(HDC hdc)
{
	cHDC = hdc;
}
void Thieves::releaseDC()
{
	ReleaseDC(cHWND,cHDC);
}
void Thieves::resetPoints(int val)
{
	points = val;
}