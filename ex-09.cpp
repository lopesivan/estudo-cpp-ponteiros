#include <iostream>
#include <memory>

int main() {
  // Usando auto para armazenar a matriz de ponteiros únicos para double
  auto matrix = std::make_unique<std::unique_ptr<double[]>[]>(3);

  // Alocando cada linha da matriz
  for (int i = 0; i < 3; ++i) {
    matrix[i] = std::make_unique<double[]>(3);
  }

  // Preenchendo a matriz com valores e mostrando-a
  double value = 1.0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      matrix[i][j] = value;
      value += 1.0;
    }
  }

  // Exibindo a matriz
  std::cout << "Matriz 3x3 de doubles:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // A memória será automaticamente liberada quando os smart pointers saírem do escopo.
  return 0;
}

