#include "helper.h"

std::string Helper::getTitle(char x)
{
	switch(x)
	{
	case 't':
		return "Forty Thieves";
	case 'k':
		return "Kings Corners";
	default:
		return "Things";
	}
}