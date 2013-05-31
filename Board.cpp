#include "Board.h"


Board::Board(void)
{
}

Board::~Board(void)
{
}

void Board::inicializar()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			matriz[i][j] = AGUA;
			matrizEspelho[i][j] = AGUA;
		}
	}
}

void Board::sortearAtaqueInimigo()
{
	int x = rand() % 10;
	int y = rand() % 10;

	if(matriz[x][y] != AGUA){
		matrizEspelho[x][y] = matriz[x][y];
		cout << "**** Fogo Inimigo" << endl << endl;
	}

}

void Board::ataqueInimigo(int x, int y)
{
	
	if(matriz[x][y] == AGUA){
		cout << "*** Agua" << endl << endl;
	}else{

		cout << "*** Fogo" << endl << endl;
		char square = matriz[x][y];
		matrizEspelho[x][y] = square;
		int index;

		if(square == 'P'){
			if(afundouNavio(0, 5)){
				cout << "PORTA AVIOES AFUNDOU ..." << endl << endl;
			}
		}
		else if(square == 'K'){
			if(afundouNavio(1, 4)){
				cout << "AFUNDOU NAVIO ..." << endl << endl;
			}
		}
		else if(square == 'J'){

			index = encontrarNavio(x, y, 2, 4, 3);
			
			if(afundouNavio(index, 3)){
				cout << "AFUNDOU NAVIO ..." << endl << endl;
			}
			
		}
		else if(square == 'G'){
			
			index = encontrarNavio(x, y, 4, 7, 2);

			if(afundouNavio(index, 2)){
				cout << "AFUNDOU NAVIO ..." << endl << endl;
			}

		}
		else if(square == 'N'){

			index = encontrarNavio(x, y, 8, 10, 1);

			if(afundouNavio(index, 1)){
				cout << "AFUNDOU NAVIO ..." << endl << endl;
			}
			
		}

	}

}

int Board::encontrarNavio(int x, int y, int i, int quantidade, int tamanho)
{
	int *positionsX, *positionsY, index;
	
	for(; i <= quantidade; i++){

		positionsX = ships[i].getPositionsX();
		positionsY = ships[i].getPositionsY();

		for(int j = 0; j < tamanho; j++){
			if(positionsX[j] == x && positionsY[j] == y){
				index = i;
			}
		}
	}

	return index;
}

bool Board::afundouNavio(int index, int acertos)
{
	int firesHitted = 0, x1, y1;
	int* positionsX = ships[index].getPositionsX();
	int* positionsY = ships[index].getPositionsY();

	for(int i = 0; i < acertos; i++){
		x1 = positionsX[i];
		y1 = positionsY[i];

		if (matrizEspelho[x1][y1] != AGUA){
			firesHitted++;
		}
	}

	if(firesHitted == acertos){
		return true;
	}

	return false;
}

void Board::desenhar(bool mostrar_navios)
{
	char c;
	for(int i = 0; i < 10; i++)
	{
		c = 'A'+i;
		cout << c << " ";
		for(int j = 0; j < 10; j++)
		{
			if(mostrar_navios){
				cout << matriz[i][j] << "   ";
			}else{
				cout << matrizEspelho[i][j] << "   ";
			}
			
		}
		cout << endl;
	}

	cout << "  ";
	for(int i = 0; i < 10; i++)
	{
		cout << i << "   ";
	}
	cout << endl << endl;
}

void Board::desenharEspelho()
{
	char c;
	for(int i = 0; i < 10; i++)
	{
		c = 'A'+i;
		cout << c << " ";
		for(int j = 0; j < 20; j++)
		{
			if(j >= 10){
				// Espaco entre as matrizes
				if(j == 10)
					cout << "  " << c << "  ";	
				
				cout << matriz[i][j-10] << "  ";	
			}else{
				cout << matrizEspelho[i][j] << "  ";	
			}
			
		}
		cout << endl;
	}

	cout << "  ";
	for(int i = 0; i < 10; i++)
	{
		cout << i << "  ";
	}

	cout << "     ";
	for(int i = 0; i < 10; i++)
	{
		cout << i << "  ";
	}

	cout << endl << endl;
}

void Board::criarPortaAvioes(int ship_index, int x, int y)
{
	ships[ship_index].createAircraft(x, y);

    matriz[x][y] = 'P';
    matriz[x][y+1] = 'P';
    matriz[x][y+2] = 'P';
    matriz[x+1][y+1] = 'P';
    matriz[x+2][y+1] = 'P';
}

void Board::criarNavio(int ship_index, int x, int y, int tamanho, char label)
{
	for(int j = 0; j < tamanho; j++)
    {
        matriz[x][y+j] = label;
    }

    ships[ship_index].createShip(x, y, tamanho);
}

void Board::sortearPortaAvioes(int ship_index, char label)
{
    bool marked = false;
    int x, y;

    while(!marked)
    {
        x = rand() % 7;
        y = rand() % 7;

        if(verificarPosicaoPortaAvioes(x, y)){
			criarPortaAvioes(ship_index, x, y);
            marked = true;
        }
    }
}

void Board::sortearPosicoes(int ship_index, int tamanho, char label)
{
    bool marked = false;
    int x, y;

    while(!marked)
    {
        x = rand() % (10);
        y = rand() % (10 - tamanho);

        if( verificarEixoY(x, y, tamanho) )
        {
            for(int j = 0; j < tamanho; j++)
            {
                matriz[x][y+j] = label;
            }

            ships[ship_index].createShip(x, y, tamanho);
			marked = true;
        }

    }

}

void Board::sortearNavios()
{

    for(int i = 0; i < 11; i++)
    {
        if (i == 0){
            sortearPortaAvioes(i, 'P'); // Porta avioes
	    }else if(i == 1){
            sortearPosicoes(i, 4, 'K'); // 1 Ship 4
	    }else if(i < 4){
            sortearPosicoes(i, 3, 'J'); // 2 Ship 3
	    }else if(i < 7){
            sortearPosicoes(i, 2, 'G'); // 3 Ship 2
	    }else {
            sortearPosicoes(i, 1, 'N'); // 4 Ship 1
	    }
    }

}

bool Board::verificarEixoY(int x, int y, int tamanho)
{
	for(int i = 0; i < tamanho; i++)
	{
		int posY = y+i;

		if(posY > 9)
		{
			return false;
		}

		if(matriz[x][posY] != AGUA)
		{
			return false;
		}
	}
	 
	return true;

}

bool Board::verificarEixoX(int x, int y, int tamanho)
{
	for(int i = 0; i < tamanho; i++)
	{
		int posX = x+i;

		if(posX > 9)
		{
			return false;
		}

		if(matriz[posX][y] != AGUA)
		{
			return false;
		}
	}

	return true;

}

bool Board::verificarPosicaoPortaAvioes(int x, int y)
{
	if(verificarEixoX(x, y+1, 3) && verificarEixoY(x, y, 3))
	{
		return true;
	}

	return false;
}

void Board::jogadorSeleciona()
{

	int coluna, nLinha;
	char linha;
	int i = 0;
	while(i < 11)
	{
		cout << "  BATALHA NAVAL" << endl << endl;
		desenhar();

		if (i == 0){
            cout << "Selecione a posição do porta avioes" << endl;
	    }else if(i == 1){
            cout << "Selecione a posição do navio 4" << endl;
	    }else if(i < 4){
            cout << "Selecione a posição do navio 3" << endl;
	    }else if(i < 7){
            cout << "Selecione a posição do navio 2" << endl;
	    }else {
            cout << "Selecione a posição do navio 1" << endl;
	    }

		cout << "Linha: ";
		cin >> linha;
		nLinha = linha - 'A';
	
		cout << "Coluna: ";
		cin >> coluna;

		if(i == 0){
			if(verificarPosicaoPortaAvioes(nLinha, coluna)){
				criarPortaAvioes(i, nLinha, coluna);
				i++;
			}
		}
		else if(i == 1){
			if(verificarEixoY(nLinha, coluna, 4)){
				criarNavio(i, nLinha, coluna, 4, 'K');
				i++;
			}
		}
		else if(i < 4){
			if(verificarEixoY(nLinha, coluna, 3)){
				criarNavio(i, nLinha, coluna, 3, 'J');
				i++;
			}
		}
		else if(i < 7){
			if(verificarEixoY(nLinha, coluna, 2)){
				criarNavio(i, nLinha, coluna, 2, 'G');
				i++;
			}
		}
		else{
			if(verificarEixoY(nLinha, coluna, 1)){
				criarNavio(i, nLinha, coluna, 1, 'N');
				i++;
			}
		}

		system("cls");
	}
}

bool Board::acabouJogo()
{
	int pontosAcertados = 0;

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(matrizEspelho[i][j] != AGUA){
				pontosAcertados++;
			}
		}
	}

	if(pontosAcertados == 25){
		return true;
	}

	return false;
}