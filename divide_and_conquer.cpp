#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

double euclidianDistance(std::pair<int, int> p1, std::pair<int, int> p2) {   
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}

double calculateMinimumDistance(std::vector<std::pair<int, int>> points, int start, int end){
    double minDistance = INT_MAX;
    for(int i = start; i < end; i++){
        for(int j = i + 1; j <= end; j++){
            double distance = euclidianDistance(points[i], points[j]);
            minDistance = std::min(minDistance, distance);
        }
    }
    return minDistance;
}     

double recursiveAlgorithm(std::vector<std::pair<int, int>>& points, int start, int end){
    if (end - start + 1 <= 3){
        return calculateMinimumDistance(points, start, end);
    }

    // Obtiene la distancia euclidiana minima de los grupos obtenidos al dividir por la mitad
    // el conjunto de puntos actual
    int mid = start + (end - start)/2;
    double minDistanceFR = recursiveAlgorithm(points, start, mid);
    double minDistanceSR = recursiveAlgorithm(points, mid+1, end);
    double minDistance = minDistanceFR;
    if (minDistanceFR > minDistanceSR) minDistance = minDistanceSR;

    // Guarda los puntos que estan a una distancia, en el eje x, menor a la distancia
    // euclidiana minima de los 2 grupos actuales respecto al punto de al medio.
    std::vector<std::pair<int, int>> pointsNearMid;
    for (int i=start ; i <= end ; i++){
        if (abs(points[i].first - points[mid].first) < minDistance){
            pointsNearMid.push_back(points[i]);
        }
    }

    //Ordenar puntos segun eje Y
    std::sort(pointsNearMid.begin(), pointsNearMid.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b){
        return a.second < b.second;
    });

    // Verifica si los pares de puntos cercanos al punto mediano, segun el eje x, generan una distancia
    // euclidiana menor a la minima de ambos grupos
    int size = pointsNearMid.size();
    for (int i=0 ; i<size-1 ; i++){
        for (int j=i+1 ; j<size ; j++){
            double YDistance = abs(pointsNearMid[i].second - pointsNearMid[j].second);
            if (YDistance >= minDistance){
                break;
            }
            double distanceBetweenPoints = euclidianDistance(pointsNearMid[i], pointsNearMid[j]);
            if (distanceBetweenPoints < minDistance){
                minDistance = distanceBetweenPoints;
            }
        }
    }

    return minDistance;


}

double minEuclidianDistance(std::vector<std::pair<int, int>>& points){
    //ordenar vector segun el eje x
    std::sort(points.begin(), points.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b){
        return a.first < b.first;
    });

    return recursiveAlgorithm(points, 0, points.size()-1);       
}   

/*
int main(){
    int n, x, y; 
    double minDistance;
    std::cout << "Bienvenido al calculador de la distancia Euclidiana minima.\n" << std::endl;
    std::cout << "Ingrese la cantidad de puntos a evaluar: ";
    std::cin >> n;
    std::vector<std::pair<int, int>> points(n);
    std::cout << "Ingrese los " << n << " puntos en el siguiente formato 'x y':" << std::endl;
    for (int i=0 ; i<n ; i++){
        std::cin >> x >> y;
        points[i] = std::pair<int, int>(x, y);
    }

    minDistance = minEuclidianDistance(points);
    std::cout << "La distancia Euclidiana minima entre el conjunto de puntos dado es " << minDistance << std::endl;
    return 0;
} */