#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>

double euclidianDistance(std::pair<int, int> p1, std::pair<int, int> p2) {   
    return pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2);
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

std::pair<std::vector<std::pair<int, int>>, double> recursiveAlgorithm(std::vector<std::pair<int, int>>& points, int start, int end){

    // Si hay 3 o menos elementos se genera un vector ordenado en base a la coordenada y; se retorna el arreglo y la distancia minima entre los puntos.
    if (end - start + 1 <= 3){
        std::vector<std::pair<int, int>> ySortedPoints;
        for (int i=start ; i<=end ; i++){
            ySortedPoints.push_back(points[i]);
        }
        std::sort(ySortedPoints.begin(), ySortedPoints.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b){
            return a.second < b.second;
        });
        return std::pair<std::vector<std::pair<int, int>>, double>(ySortedPoints, calculateMinimumDistance(points, start, end));
    }

    // Obtiene la distancia euclidiana minima de los grupos obtenidos al dividir por la mitad
    // el conjunto de puntos actual
    std::pair<std::vector<std::pair<int, int>>, double> leftVectorAndResult;
    std::pair<std::vector<std::pair<int, int>>, double> rightVectorAndResult;
    int mid = start + (end - start)/2;
    leftVectorAndResult = recursiveAlgorithm(points, start, mid);
    rightVectorAndResult = recursiveAlgorithm(points, mid+1, end);
    double minDistance = leftVectorAndResult.second;
    if (leftVectorAndResult.second > rightVectorAndResult.second) minDistance = rightVectorAndResult.second;

    //Combina los vectores ordenados en base a la coordenada y
    int size = leftVectorAndResult.first.size()+rightVectorAndResult.first.size();
    std::vector<std::pair<int, int>> ySortedPoints(size);
    std::merge(leftVectorAndResult.first.begin(), leftVectorAndResult.first.end(), rightVectorAndResult.first.begin(), rightVectorAndResult.first.end(), ySortedPoints.begin());

    // Guarda los puntos que estan a una distancia, en el eje x, menor a la distancia
    // euclidiana minima de los 2 grupos actuales respecto al punto de al medio.
    std::vector<std::pair<int, int>> pointsNearMid;
    for (int i=0 ; i < size ; i++){
        if (abs(ySortedPoints[i].first - points[mid].first) < minDistance){
            pointsNearMid.push_back(points[i]);
        }
    }

    //Ordenar puntos segun eje Y
    std::sort(pointsNearMid.begin(), pointsNearMid.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b){
        return a.second < b.second;
    });

    // Verifica si los pares de puntos cercanos al punto mediano, segun el eje x, generan una distancia
    // euclidiana menor a la minima de ambos grupos
    size = pointsNearMid.size();
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

    std::pair<std::vector<std::pair<int, int>>, double> result(ySortedPoints, minDistance);
    return result;
}

double minEuclidianDistance(std::vector<std::pair<int, int>>& points){
    //ordenar vector segun el eje x
    std::sort(points.begin(), points.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b){
        return a.first < b.first;
    });

    return sqrt(recursiveAlgorithm(points, 0, points.size()-1).second);       
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