#include <iostream>
#include <vector>

using namespace std;

const int INF = 100000; //para representar que no hay arista 


struct tResult {

    int peso = 0;
    //arista
    int origen = 0;   
    int destino = 0; 
};

// Función poco eficiente para encontrar arista con peso minimo; devuelve arista y peso.

tResult menorPeso(vector<bool>& vAEM, int V, vector<vector<int>>& grafo) {

    tResult result;
   
    int minPeso = INF; //numero grande
    int origen = 0;
    int destino = 0;

    for (int u = 0; u < V; ++u) {
                                        
        if (vAEM[u] == true) {  /// si el nodo esta en el arbol mirar sus aristas a ver cual es la  menor peso  

            for (int v = 0; v < V; v++) {

                if (grafo[u][v] != INF && grafo[u][v] < minPeso && vAEM[v]== false ) { //que sea menor y que no una un nodo ya seleccionado 
                   
                    minPeso = grafo[u][v];
                    destino = v; //vertice destino 
                    origen = u;  // vertice origen 

                }

            }

        }
    }

    result.peso = minPeso;
    result.origen = origen;  
    result.destino = destino; 

    return result; 
}

// Función para imprimir

void pintarGrafo(vector<tResult>& grafoResult) {

    cout << "Arista " << "Peso" << endl;
    for (int i = 0; i < grafoResult.size(); ++i) {

        cout << " "<< grafoResult[i].origen << "-" << grafoResult[i].destino << "    " << grafoResult[i].peso << endl;
    }
}


// FUNCION ALGORITMO PRIM - arbol de expansion minima

void prim(vector<vector<int>>& grafo, int V) {

    vector<tResult> grafoResult;      // Almacena el arbol de expansion minima resultante 
    vector<bool> vAEM(V, false);      // vector de vértices incluidos en el arbol de expansion minima inicializado a false

    //empiezo arbitrariamente por el 0 
    int vertice = 0;
    vAEM[0] = true;

    for (int i = 0; i < V - 1; i++) {

        tResult u = menorPeso(vAEM, V, grafo); // menorPeso devuelve el vertice (indice) de la arista de menor peso

        vAEM[u.destino] = true;    // actualizar y guardar
        grafoResult.push_back(u); 
  
    }
   
    pintarGrafo(grafoResult);
}

int main() {

    // Ejemplo 1
    vector<vector<int>> grafo1 = {

        {INF, 2, INF, 1, INF},
        {2, INF, 1, 4, 3},
        {INF, 1, INF, INF, 7},
        {1, 4, INF, INF, 5},
        {INF, 3, 7, 5, INF}
    };

    cout << "Ejemplo 1 : Grafo 1" << endl;
    prim(grafo1, grafo1.size());

    // Ejemplo 2
    vector<vector<int>> grafo2 = {

      
        {INF, 3, INF, INF, INF},
        {3, INF, 1, INF,INF},
        {INF, 1, INF, 7, INF},
        {INF, INF, 7, INF, 2},
        {INF, INF, INF, 2, INF}
    };

    cout << "Ejemplo 2: Grafo 2" << endl;
    prim(grafo2, grafo2.size());

    return 0;
}
