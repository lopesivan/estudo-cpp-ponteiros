// g++ -std=c++17 -O2 -Wall -Wextra -pedantic -I/usr/include/x86_64-linux-gnu ex-15.cpp -o app
#include <iostream>
#include <memory>
#include <cstdlib>

// alias do unique_ptr com free
template<typename T>
using MallocUPtr = std::unique_ptr<T, decltype (&std::free)>;

// helper que usa N
template<typename T, int N = 5>
auto make_matrix()
{
    return MallocUPtr<T>
    {
        static_cast<T*> (std::malloc (N* N * sizeof (T))),
        &std::free
    };
}

int main()
{
    constexpr int N = 5;
    auto matriz = make_matrix<int, N>();

    if (!matriz)
    {
        std::cerr << "Falha ao alocar memória.\n";
        return EXIT_FAILURE;
    }

    for (int i = 0; i < N * N; ++i)
        matriz.get()[i] = i;

    for (int i = 0; i < N * N; ++i)
    {
        std::cout << matriz.get()[i] << ' ';
        if ((i + 1) % N == 0) std::cout << '\n';
    }

    // free() automático ao sair do escopo
}
