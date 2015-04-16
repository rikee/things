#include "thieves.h"

Thieves::Thieves(HWND hwnd)
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
void Thieves::paintCard()
{
	Deck deck(2);
	deck.shuffleDeck();

	Card card = deck.drawCard();

	card.setCardBackPosition(1);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);
	card.flipCard();
	card.drawCard(cHWND);
}
void Thieves::paintScreen()
{
	paintPoints();
	paintCard();
}