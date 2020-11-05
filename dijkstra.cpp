#include <iostream>
#include <vector>
#include <queue>
#define INFINITO 10000000

using namespace std;

class Grafo
{
private:
	int num_vertices;

	// Ponteiro para um array contendo as listas de adjacências
	vector<pair<int, int>> *adj;
public:
	Grafo(int V)
	{
		this->num_vertices = V; // Atribui o número de vértices

		// Cria um arranjo de listas de pairs.
		// cada pair é formado pelo vértice destino e o custo.
		// A posição da lista no arranjo corresponde ao vértice de origem.
		adj = new vector<pair<int, int>>[V];
	}

	// Adiciona uma aresta ao grafo de v1 à v2
	void adicionarAresta(int v1, int v2, int custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
	}

	// O dijkstra é utilizado para encontrar o menor caminho entre dois vértices em um grafo
	int dijkstra(int orig, int dest)
	{
		// Vetor de distâncias
		int dist[num_vertices];

		// Vetor de visitados serve para caso o vértice já tenha sido
		// expandido (visitado), não expandir mais
		bool visitados[num_vertices];

		// Fila de prioridades de pair (distancia, vértice)
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> prioridades;

		// Inicializa o vetor de distâncias e visitados
		for (int i = 0; i < num_vertices; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		// A distância da origem para ela mesma é 0
		dist[orig] = 0;

		// Insere origem na fila de prioridades
		prioridades.push(make_pair(dist[orig], orig));

		while (!prioridades.empty())
		{
			pair<int, int> p = prioridades.top(); // Extrai o pair do topo
			int u = p.second;					  // Obtém o vértice origem do pair
			prioridades.pop();					  // Remove da fila

			// Verifica se o vértice não foi expandido
			if (visitados[u] == false)
			{
				// Marca como visitado
				visitados[u] = true;

				vector<pair<int, int>>::iterator it;

				// Percorre os vértices "v" adjacentes de "u"
				for (it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// Obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// Relaxamento (u, v)
					if (dist[v] > (dist[u] + custo_aresta))
					{
						// Atualiza a distância de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						prioridades.push(make_pair(dist[v], v));
					}
				}
			}
		}

		// Retorna a distância mínima até o destino
		return dist[dest];
	}
};

int main()
{
	int num_vertices, num_arestas, origem, destino, peso;
	int org, dest;

	cout << "-----------------DJIKSTRA-----------------" << endl;
	cout << "Numero de vertices do grafo: ";
	cin >> num_vertices;
	Grafo g(num_vertices);
	cout << "Numero de arestas do grafo: ";
	cin >> num_arestas;

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

	cout << "\nOrigem do menor caminho: ";
	cin >> org;
	cout << "Destino do menor caminho: ";
	cin >> dest;

	cout << "\nO menor caminho entre " << org << " e " << dest << " e: " << g.dijkstra(org, dest) << endl;

	return 0;
}
