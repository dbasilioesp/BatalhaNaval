#include <ctime>
#include <cstdlib>
#include "Board.h"

int main()
{
	srand (time(0));

	char linha;
	int coluna = 0, nLinha = 0;
	bool gameOver = false;
	Board t1, t2;

	t2.inicializar();
	t2.sortearNavios();
	
	t1.inicializar();
	t1.sortearNavios();
	//t1.jogadorSeleciona();

	while(!gameOver)
	{
		cout << "Jogador" << endl << endl;
		t1.desenharEspelho();
		cout << endl;
		cout << "Inimigo" << endl << endl;
		t2.desenharEspelho();

		cout << "Ataque linha: ";
		cin >> linha;
		nLinha = linha - 'A';

		cout << "Ataque coluna: ";
		cin >> coluna;

		cout << endl <<endl;
		t2.ataqueInimigo(nLinha, coluna);
		t1.sortearAtaqueInimigo();

		cout << endl;
		system("pause");
		system("cls");

		if (t1.acabouJogo() || t2.acabouJogo()){
			gameOver = true;
		}
	}

	cout << endl;
	cout << "####### GAME OVER #######" << endl << endl;
	
	if(t2.acabouJogo()){
		cout << "        You Win          " << endl << endl;
	}else{
		cout << "        You Lose          " << endl << endl;
	}

	cout << "#######           #######" << endl;

	system("pause");
	return 0;
}