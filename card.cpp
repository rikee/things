#include "card.h"

Card::Card()
{
	cardWidth = 73;
	cardHeight = 98;
	imageName = "";
}

void Card::setImageName(std::string name)
{
	imageName = name;
}
void Card::drawCard(HWND cHWND)
{
	HBITMAP hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL),imageName.c_str(),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	HDC hdc = GetDC(cHWND);
	HDC image_dc = CreateCompatibleDC(hdc);
	HBITMAP old_hbitmap = (HBITMAP)SelectObject(image_dc,hbm);
	BitBlt(hdc,50,50,cardWidth,cardHeight,image_dc,0,0,SRCCOPY);
	BitBlt(hdc,250,50,cardWidth,cardHeight,image_dc,0,100,SRCCOPY);

	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Image image(L"legacy_sources/cards_sprite.png");
	graphics.DrawImage(&image, 300, 100, 700, 300, 100, 100, Gdiplus::UnitPixel);
}