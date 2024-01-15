
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int INF = 100000; //cuando no hay arista entre vertices 


struct tResult {  //Guarda los resultados del algoritmo Floyd-Wharshall

    vector<vector<int>> vPonderada;
    vector<vector<int>> vRecorrido;
};


// funcion del algoritmo

tResult floydWarshall(vector<vector<int>> & grafo1) {

    int V = grafo1.size();

    vector<vector<int>> vRecorrido(V, vector<int>(V));  //matriz de recorridos, Ej: (P[i][j] = 3 ,vertice anterior a j n el camino mas corto de i a j seria 3)
                                                       
    vector<vector<int>> vPonderada(V, vector<int>(V));  //matriz de pesos, guarda distancia mas corta  entre todos los pares de vertices 
                                                       

    for (int i = 0; i < V; i++) {       // inicializacion de matrices
        for (int j = 0; j < V; j++) {
            vPonderada[i][j] = grafo1[i][j];  
            vRecorrido[i][j] = i;            
        }
    }

    //FLOYD  
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (vPonderada[i][k] + vPonderada[k][j] < vPonderada[i][j]) {
                    vPonderada[i][j] = vPonderada[i][k] + vPonderada[k][j];
                    vRecorrido[i][j] = k;
                }
            }
        }
    }

    tResult sol;
    sol.vPonderada = vPonderada;
    sol.vRecorrido = vRecorrido;

    return sol; 
}

//Imprimir resultados 

void imprimirRuta(int a, int b, vector<vector<int>>& P) { //recursiva 

    if (a == b) {        //vertice a coincide con vertice b
        cout << b << " ";
        return;
    }

    imprimirRuta(a, P[a][b], P);
    cout << b << " ";
}

void caminos(vector<vector<int>>& D, vector<vector<int>>& P) {
    int V = D.size();

    // Imprimir encabezados
    cout << "Origen " << " Destino" << " Camino " << "Distancia" << endl;

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (D[i][j] != INF) {
                cout << "  "<< i << "        " << j << "     ";
                imprimirRuta(i, j, P);
                cout << setw(10) << D[i][j] << " ";   //las distancias quedan poquito mal impresas por los anchos
                cout << endl;
            }
        }
    }
}


int main() {

    //Ejemplo 1 

    vector<vector<int>> grafo1 = {
        {INF, 2, INF, 1, INF},
        {2, INF , 1, 4, 3},
        {INF, 1, INF, INF , 7},
        {1, 4, INF, INF , 5},
        {INF, 3, 7, 5, INF}
    };

    tResult sol = floydWarshall(grafo1);
    cout << "Grafo 1 :" << endl;
    caminos(sol.vPonderada, sol.vRecorrido);
    cout << endl;

   // Ejemplo 2 

    vector<vector<int>> grafo2 = {
        {INF, 5, 2, 8},
        {5, INF, 1, 4},
        {2, 1, INF, 6},
        {8, 4, 6, INF}
    };

    tResult sol2 = floydWarshall(grafo2);
    cout << "Grafo 2 :" << endl;
    caminos(sol2.vPonderada, sol2.vRecorrido);
  
    return 0;
}