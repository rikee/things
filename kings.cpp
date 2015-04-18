#include "kings.h"

std::string Kings::wndTitle = "Kings Corners";
int Kings::wndWidth = 520;
int Kings::wndHeight = 455;

Kings::Kings(HWND hwnd)
{
	cHWND = hwnd;
	cardWidth = 75;
	cardHeight = 100;
	cardImage = L"legacy_sources/cards_sprite.png";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 2;
	jokers = 0;
}

void Kings::paintCard()
{
	Deck deck(jokers);
	deck.shuffleDeck();

	Card card = deck.drawCard();

	card.setCardBackPosition(cardBackPosition);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);
	//card.flipCard();
	card.drawCard(cHWND);
}
void Kings::paintScreen()
{
	paintCard();
}