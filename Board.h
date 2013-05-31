#pragma once
#include <iostream>
#include <string>
#include "Ship.h"

#define AGUA '*'
using namespace std;

class Board
{
public:
	Board(void);
	~Board(void);

	void desenhar(bool mostrar_navios = true);
	void desenharEspelho();
    void inicializar();
        
    bool verificarEixoX(int x, int y, int tamanho);
    bool verificarEixoY(int x, int y, int tamanho);
	bool verificarPosicaoPortaAvioes(int x, int y);

	void sortearNavios();
    void sortearPosicoes(int ship_index, int tamanho, char label);
    void sortearPortaAvioes(int ship_index, char label);

	void criarPortaAvioes(int ship_index, int x, int y);
	void criarNavio(int ship_index, int x, int y, int tamanho, char label);

	void jogadorSeleciona();

	void sortearAtaqueInimigo();
	void ataqueInimigo(int x, int y);
	
	bool acabouJogo();

protected:

	bool afundouNavio(int index, int acertos);
	int encontrarNavio(int x, int y, int i, int quantidade, int tamanho);

	char matriz[10][10], matrizEspelho[10][10];
    Ship ships[11];

};

