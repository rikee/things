#ifndef CARD_H
#define CARD_H

#include <Windows.h>
#include <string>

class Card
{
public:
	Card();
	void drawCard(HWND cHWND);
	void setImageName(std::string name);

private:
	int cardWidth;
	int cardHeight;
	std::string imageName;
};

#endif