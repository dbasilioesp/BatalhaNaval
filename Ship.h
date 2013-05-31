#pragma once
class Ship
{
public:
	Ship(void);
	~Ship(void);

	void createShip(int x, int y, int size);
    void createAircraft(int x, int y);
	bool getPosition(int x, int y);
	int* getPositionsX();
	int* getPositionsY();

protected:

    void markPosition(int x, int y);
	int positionsX[5], positionsY[5];
	int lastIndex;
};

