#include <iostream>
#include <memory>

// Template para criar uma matriz genérica
template <typename T>
class Matrix {
public:
    // Construtor que cria uma matriz 2D com o número de linhas e colunas, usando lista de inicialização de membros
    Matrix(int rows, int cols) 
        : rows(rows), cols(cols), data(std::make_unique<std::unique_ptr<T[]>[]>(rows)) 
    {
        for (int i = 0; i < rows; ++i) {
            data[i] = std::make_unique<T[]>(cols);
        }
    }

    // Função para acessar os elementos da matriz
    T& at(int row, int col) {
        return data[row][col];
    }

    // Função para exibir a matriz
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    int rows, cols;  // Dimensões da matriz
    std::unique_ptr<std::unique_ptr<T[]>[]> data; // Armazena a matriz de smart pointers
};

// Função template para preencher a matriz (a dedução do tipo acontece aqui)
template <typename T>
void fillMatrix(Matrix<T>& matrix, int rows, int cols, T startValue) {
    T value = startValue;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix.at(i, j) = value++;
        }
    }
}

int main() {
    // Criando uma matriz 3x3 de tipo inferido quando preenchida
    Matrix<double> matrix(3, 3);

    // Preenchendo a matriz com valores do tipo double
    fillMatrix(matrix, 3, 3, 1.0);

    // Exibindo a matriz
    std::cout << "Matriz 3x3 de doubles:\n";
    matrix.print();

    return 0;
}

