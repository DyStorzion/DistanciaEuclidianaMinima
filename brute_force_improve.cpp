#include <iostream>
#include <climits>
#include <cmath>
#include <vector>

double euclidianDistance(std::pair<int, int> p1, std::pair<int, int> p2) {    
    return pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2);
}

double calculateMinimumDistance(std::vector<std::pair<int, int>> puntos){
    double distancia_minima = INT_MAX;
    int l = puntos.size();
    for(int i = 0; i < l - 1; i++){
        for(int j = i + 1; j < l; j++){
            double distancia = euclidianDistance(puntos[i], puntos[j]);
            distancia_minima = std::min(distancia_minima, distancia);
        }
    }
    return sqrt(distancia_minima); 
}

/*
int main() {
    int n;
    std::cout << "Cuantos puntos desea ingresar: \n";
    std::cin >> n;
    std::vector<std::pair<int, int>> puntos; 
    for(int i = 0; i < n; i++){ 
        int x, y;
        std::cout << "Ingrese x: ";
        std::cin >> x;
        std::cout << "Ingrese y: "; 
        std::cin >> y;
        puntos.push_back({x,y});
        std::cout << "Punto agregado!\n";
    }
    
    double distancia = calculateMinimumDistance(puntos);
    std::cout << "La distancia minima entre los puntos es: " << distancia << std::endl;
    return 0;
} */