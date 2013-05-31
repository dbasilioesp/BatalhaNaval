#include "Ship.h"


Ship::Ship(void)
{
	lastIndex = 0;
	for(int i = 0; i < 5; i++)
	{
		positionsX[i] = -1;
		positionsY[i] = -1;
	}
}

Ship::~Ship(void)
{
}


void Ship::markPosition(int x, int y)
{
	positionsX[lastIndex] = x;
	positionsY[lastIndex] = y;
	lastIndex++;
}

bool Ship::getPosition(int x, int y)
{
	for(int i = 0; i < lastIndex; i++){

		if(positionsX[i] == x && positionsY[i] == y){
			return true;
		}
	}

	return false;
}

int* Ship::getPositionsX()
{
	return positionsX;
}

int* Ship::getPositionsY()
{
	return positionsY;
}

void Ship::createShip(int x, int y, int size)
{
    for(int i = 0; i < size; i++)
    {
        markPosition(x, y+i);
    }
}

void Ship::createAircraft(int x, int y)
{
    markPosition(x, y);
	markPosition(x, y+1);
	markPosition(x, y+2);
	markPosition(x+1, y+1);
	markPosition(x+2, y+1);
}