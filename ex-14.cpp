#include <iostream>
#include <memory>
#include <cstdlib> // malloc, free

// Alias genérico: unique_ptr<T, decltype(&std::free)>
template<typename T>
using MallocUPtr = std::unique_ptr<T, decltype (&std::free)>;

int main()
{
    using Matrix = int; // só um apelido

    // agora o deleter é passado uma vez só
    MallocUPtr<Matrix> matriz
    {
        static_cast<Matrix*> (std::malloc (3 * 3 * sizeof (Matrix))),
        &std::free
    };

    if (!matriz)
    {
        std::cerr << "Falha ao alocar memória.\n";
        return EXIT_FAILURE;
    }

    // usa normalmente
    for (int i = 0; i < 9; ++i)
        matriz.get()[i] = i * 10;

    for (int i = 0; i < 9; ++i)
        std::cout << matriz.get()[i] << ' ';
    std::cout << '\n';

    // ✅ free() chamado automaticamente quando sair do escopo
}
