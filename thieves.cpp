#include "thieves.h"

std::string Thieves::wndTitle = "Forty Thieves";
int Thieves::wndWidth = 578;
int Thieves::wndHeight = 388;

Thieves::Thieves(HWND hwnd)
	:deck(2)
{
	cHWND = hwnd;
	high = 400;
	low = 100;
	average = 190;
	points = 0;
	cardWidth = 75;
	cardHeight = 100;
	cardImage = L"legacy_sources/cards_sprite.png";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 1;
	jokers = 2;
}

void Thieves::paintPoints()
{
	RECT cRect;
	GetClientRect(cHWND, &cRect);
	PAINTSTRUCT paintStruct;

	HDC cHDC = BeginPaint(cHWND, &paintStruct);

	int clientWidth = cRect.right - cRect.left;
	int clientHeight = cRect.bottom - cRect.top;
	int thickness = 22;
	HBRUSH hbrush = CreateSolidBrush(RGB(255,255,255));;
	Rectangle(cHDC, 0, clientHeight - thickness, clientWidth, clientHeight);
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

	EndPaint(cHWND, &paintStruct);
}
void Thieves::paintCard(Card card, bool faceUp)
{
	card.setCardBackPosition(cardBackPosition);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);

	if(faceUp) card.flipCard();

	card.drawCard(cHWND);
}
void Thieves::dealHand()
{
	Card topCard;
	for(size_t i = 0; i < cardColumns.size(); i++)
	{
		while(cardColumns[i].getRemainingCount() > 0)
		{
			topCard = cardColumns[i].drawCard();
			paintCard(topCard, true);
		}
	}

}
void Thieves::paintScreen()
{
	paintPoints();
	initializeHand();
	dealHand();
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
			topCard.setPosition(i * (cardWidth + 1) + 3, j * 20 + 3);
			column.push_back(topCard);
		}
		deckCols.push_back(Deck(0, column));
	}
	return deckCols;
}
void Thieves::initializeHand()
{
	deck.getNewDeck();
	deck.shuffleDeck();
	cardColumns = drawCardColumns(deck);
}