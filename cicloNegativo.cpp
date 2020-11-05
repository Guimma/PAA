#include <iostream>
#include <vector>
#include <queue>
#define INFINITO 10000000

using namespace std;

class Aresta
{
public:
	int origem;
	int destino;
	int peso;

	Aresta(int origem, int destino, int peso)
	{
		this->origem = origem;
		this->destino = destino;
		this->peso = peso;
	}
};

class Grafo
{
public:
	int num_vertices;
	int num_arestas;

	// Lista contendo todas as arestas do grafo
	vector<Aresta> arestas;
	Grafo(int V, int A)
	{
		this->num_vertices = V; // Atribui o número de vértices
		this->num_arestas = A;	// Atribui o número de arestas

		arestas = {};
	}

	// Adiciona uma aresta ao grafo de v1 à v2
	void adicionarAresta(int v1, int v2, int custo)
	{
		arestas.push_back(Aresta(v1, v2, custo));
	}
    
    // O algoritmo de Bellman-Ford encontra o menor caminho entre dois vértices
	// Além disso, também detecta se há ciclos negativos em um grafo
	bool BellmanFord()
	{
		int dist[num_vertices];

		// Passo 1:
		// Inicializa as distâncias da origem à todos os outros vértices como infinito
		for (int i = 0; i < num_vertices; i++)
			dist[i] = INFINITO;
		dist[0] = 0;

		// Passo 2:
		// Relaxa todas as arestas V - 1 vezes
		// O menor caminho entre dois vértices pode ter no máximo V - 1 arestas
		for (int i = 1; i <= num_vertices - 1; i++)
		{
			for (int j = 0; j < num_arestas; j++)
			{
				int u = arestas[j].origem;
				int v = arestas[j].destino;
				int peso = arestas[j].peso;
				if (dist[u] != INFINITO && dist[u] + peso < dist[v])
					dist[v] = dist[u] + peso;
			}
		}

		// Passo 3:
		// Detectar ciclos negativos
		// O passo 2 garante as menores distâncias para grafos sem ciclos negativos
		// Se houver um caminho mais curto, há um ciclo negativo
		for (int i = 0; i < num_arestas; i++)
		{
			int u = arestas[i].origem;
			int v = arestas[i].destino;
			int peso = arestas[i].peso;
			if (dist[u] != INFINITO && dist[u] + peso < dist[v])
			{
				return true; // Ciclo negativo detectado
			}
		}

		return false;
	}
};

int main()
{
	int num_vertices, num_arestas, origem, destino, peso;
	int org, dest;

	cout << "-----------------DETECTOR DE CICLO NEGATIVO-----------------" << endl;
	cout << "Numero de vertices do grafo: ";
	cin >> num_vertices;
	cout << "Numero de arestas do grafo: ";
	cin >> num_arestas;

	Grafo g(num_vertices, num_arestas);

	for (int i = 0; i < num_arestas; i++)
	{
		cout << "\nAresta " << i << endl;
		cout << "Origem: ";
		cin >> origem;
		cout << "Destino: ";
		cin >> destino;
		cout << "Peso: ";
		cin >> peso;
		g.adicionarAresta(origem, destino, peso);
	}

    string possuiCicloNegativo = g.BellmanFord() ? "possui" : "nao possui";
	cout << "\nO grafo " << possuiCicloNegativo << " ciclo negativo." <<endl;

	return 0;
}