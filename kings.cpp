#include "kings.h"

std::string Kings::wndTitle = "Kings Corners";
int Kings::wndWidth = 528;
int Kings::wndHeight = 463;

Kings::Kings(HWND hwnd)
{
	state = 0;
	cHWND = hwnd;
	cardWidth = 75;
	cardHeight = 100;
	cardImage = L"legacy_sources/cards_sprite.png";
	gridWidth = 100;
	gridHeight = 100;
	cardBackPosition = 2;
	jokers = 0;
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

void Kings::paintCard(bool faceUp)
{
	Deck deck(jokers);
	deck.shuffleDeck();

	Card card = deck.drawCard();

	card.setCardBackPosition(cardBackPosition);
	card.setCardDimentions(cardWidth, cardHeight);
	card.setImageName(cardImage);
	card.setGridDimentions(gridWidth, gridHeight);

	if(faceUp) card.flipCard();

	card.paintCard(cHWND);
}
void Kings::paintScreen()
{
	paintCard(false);
}