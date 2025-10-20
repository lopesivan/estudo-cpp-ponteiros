#include <iostream>
#include <cassert>

bool cpm_ptr (int* a, int* b)
{
    return a == b;
}

bool cpm_ptr_content (int* a, int* b)
{
    return *a == *b;
}

bool cpm_ref (int& a, int& b)
{
    return a == b;
}

int main ()
{
    int a = 4,
        b = 4;

    // Teste do ponteiro
    if (cpm_ptr (&a, &b))
        std::cout << "cpm_ptr(&a, &b) TRUE\n";
    else
        std::cout << "cpm_ptr(&a, &b) FALSE\n";

    // Teste do ponteiro
    if (cpm_ptr_content (&a, &b))
        std::cout << "cpm_ptr_content(&a, &b) TRUE\n";
    else
        std::cout << "cpm_ptr_content(&a, &b) FALSE\n";

    // Teste da referência
    if (cpm_ref (a, b))
        std::cout << "cpm_ref(&a, &b) TRUE\n";
    else
        std::cout << "cpm_ref(&a, &b) FALSE\n";

    // std::cout << "Todos os testes passaram!\n";

    return 0;
}
