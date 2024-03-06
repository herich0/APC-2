#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef struct {
	string titulo;
	string plataformas;
	string lancamento;
	int metascore;
	string desenvolvedora;
	string publicadora;
	string genero;

}Jogo;

void adicionar(Jogo* v, int *n) {
	cout << "Titulo do jogo: ";
	getline(cin >> ws, v[*n].titulo);
	cout << "Plataforma(s): ";
	cin >> v[*n].plataformas;
	cout << "Data de lancamento(dd/mm/aaaa): ";
	cin >> v[*n].lancamento;
	do {
		cout << "Nota no metacritic: ";
		cin >> v[*n].metascore;
		if (v[*n].metascore < 1 || v[*n].metascore > 100) cout << "\nNota invalida\n" << endl;
	} while (v[*n].metascore < 1 || v[*n].metascore > 100);
	cout << "Desenvolvedora: ";
	getline(cin >> ws, v[*n].desenvolvedora);
	cout << "Publicadora: ";
	getline(cin >> ws, v[*n].publicadora);
	cout << "Genero: ";
	cin >> v[*n].genero;
	(*n)++;
}

void deletar(int x, Jogo* v, int* n) {
	for (int i = x - 1; i < *n - 1; i++) v[i] = v[i + 1];
	(*n)--;
}

void imprime(Jogo* v, int i) {
	cout << "[" << i + 1 << "]"
		<< "Titulo do jogo: \t" << v[i].titulo << "\n"
		<< " | Plataforma(s): \t" << v[i].plataformas << "\n"
		<< " | Data de lancamento: \t" << v[i].lancamento << "\n"
		<< " | Nota no metacritic: \t" << v[i].metascore << "\n"
		<< " | Desenvolvedora: \t" << v[i].desenvolvedora << "\n"
		<< " | Publicadora: \t" << v[i].publicadora << "\n"
		<< " | Genero: \t\t" << v[i].genero << "\n" << endl;
}

void bubble(Jogo* v, int n) {
	if (n > 1) {
		for (int i = 0; i < n - 1; i++)
			if (v[i].metascore < v[i + 1].metascore)
				swap(v[i], v[i + 1]);
		bubble(v, n - 1);
	}
}

void carregar(Jogo* v) {
	v[0] = { "Red Dead Redemption 2" , "Xbox One|Playstation 4|PC" , "26/10/2018" , 98 , "Rockstar Games" , "Rockstar Games" , "Acao em mundo aberto" };
	v[1] = { "Counter-Strike: Global Offensive" , "PlayStation 3|Xbox 360|PC" , "21/08/2012" , 83 , "Hidden Path Entertainment" , "Valve Software" , "FPS tatico" };
	v[2] = { "League of Legends" , "PC" , "27/10/2009" , 78 , "Riot Games" , "Riot Games" , "MOBA" };
}

int busca(int id, int n) {
	int ini = 0;
	int fim = n - 1; 
	while (ini <= fim) { 
		int i = (ini + fim) / 2;
		if (i + 1 == id)
			return 1; 
		if (i + 1 < id)
			ini = i + 1; 
		else
			fim = i; 
	}
	return -1;
}

void teste_busca() {
	assert(busca(50,99) == 1);
	assert(busca(10, 3) == -1);
}

int main() {
	int n = 3; 
	int input;
	Jogo* catalogo;
	catalogo = new(nothrow) Jogo[100];
	if (catalogo == nullptr) {
		cout << "Falha de alocacao de memoria" << endl;
		return -1;
	}
	carregar(catalogo);
	teste_busca();
	while (true){
		cout << "Digite "
			<< "\t[1] p/ Visualizar catalogo\n"
			<< "\t[2] p/ Buscar jogo por id\n"
			<< "\t[3] p/ Adicionar jogo\n"
			<< "\t[4] p/ Deletar jogo\n"
			<< "\t[0] p/ Sair\n" << endl;
		bubble(catalogo, n);
		cin >> input;
		switch (input) {
		case 1:
			if (n == 0) cout << "\nNenhum jogo catalogado\n" << endl;
			else {
				cout << "\n[Ordem decrescente de nota]\n" << endl;
				for (int i = 0; i < n; i++) imprime(catalogo, i);
			}
			break;
		case 2:
			if (n == 0) cout << "\nNenhum jogo catalogado\n" << endl;
			else {
				cout << "Id do jogo: ";
				cin >> input;
				if (busca(input, n) == -1) cout << "\nJogo nao encontrado\n" << endl;
				else imprime(catalogo, input - 1);
			}
			break;
		case 3:
			adicionar(catalogo, &n);
			break;
		case 4:
			if (n == 0) cout << "\nNenhum jogo catalogado\n" << endl;
			else {
				cout << "\nDigite o id do jogo: ";
				cin >> input;
				if (input < 1 || input > 100) cout << "\nId invalido\n" << endl;
				else deletar(input, catalogo, &n);
				cout << endl;
			}
			break;
		case 0:
			delete[] catalogo;
			return 0;
		default:
			cout << "\nComando invalido\n" << endl;
			break;
		}
	}
	delete[] catalogo;
	return 0;
}