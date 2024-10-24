#include <iostream>
#include <memory>

int main() {
  // Usando um std::unique_ptr para armazenar uma matriz de ponteiros únicos
  // para as linhas
  std::unique_ptr<std::unique_ptr<int[]>[]> matrix =
      std::make_unique<std::unique_ptr<int[]>[]>(3);

  // Alocando cada linha da matriz
  for (int i = 0; i < 3; ++i) {
    matrix[i] = std::make_unique<int[]>(3);
  }

  // Preenchendo a matriz com valores e mostrando-a
  int value = 1;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      matrix[i][j] = value++;
    }
  }

  // Exibindo a matriz
  std::cout << "Matriz 3x3:\n";
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // A memória será automaticamente liberada quando os smart pointers saírem do
  // escopo.
  return 0;
}
