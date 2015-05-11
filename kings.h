#ifndef KINGS_H
#define KINGS_H

#include <Windows.h>
#include <GdiPlus.h>
#include <WinGDI.h>
#include <string>
#include "resource.h"
#include "deck.h"

BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

struct Slot
{
public:
	Slot();
	bool isFilled();
	bool isSelected();
	void select();
	void deselect();
	int getPositionX();
	int getPositionY();
	void setPosition(int x, int y);
	void paintCardSlot(HWND cHWND, HDC cHDC);
	void setType(char t);
	Card getCard();
	void setCard(Card c);
	void removeCard();

private:
	int slotWidth;
	int slotHeight;
	std::wstring slotImage;
	bool filled;
	bool selected;
	int posX;
	int posY;
	char type;
	Card card;

	HBITMAP mLoadImg(WCHAR *szFilename);
};

class Kings
{
public:
	Kings(HWND hwnd);
	void paintScreen();
	void setHWND(HWND hwnd);
	void setHDC(HDC hdc);
	void releaseDC();
	void setState(int s);
	int getState();
	void processClick(int x, int y);

	static std::string wndTitle;
	static int wndWidth;
	static int wndHeight;
	
private:
	void paintFrame();
	void paintMessage();
	void initSlots();
	void paintSlots();
	void paintCard(Card card);
	void paintCard(Card card, bool selected);
	void dealHand();
	void initializeHand();
	int getClickedSlot(int mouseX, int mouseY);
	char getSlotType(int i, int j);
	bool clickedDrawPile(int mouseX, int mouseY);
	bool isWon();
	bool isLost();
	bool boardFull();
	HWND initDialogStuck();
	HWND initDialogWon();

	int state; // 0 = not started, 1 = between hands, 2 = during hand, 3 = board clearing

	HWND cHWND;
	HWND cDlg;
	HDC cHDC;
	int remainingBoxLeft, remainingBoxTop, remainingBoxRight, remainingBoxBottom;
	int messageBoxLeft, messageBoxTop, messageBoxRight, messageBoxBottom;
	int cardWidth;
	int cardHeight;
	std::wstring cardImage;
	std::wstring cardImageSelected;
	int gridWidth;
	int gridHeight;
	int cardBackPosition;
	int jokers;
	Deck deck;
	Card active;
	Slot activeSlot;
	int selectedSlotIndex;
	std::vector<Slot> slots;
	int drawPilePosX;
	int drawPilePosY;
	int activePosX;
	int activePosY;
	Card fakeDeckTop;
	std::string messageTopLine;
	std::string messageBottomLine;
};

#endif