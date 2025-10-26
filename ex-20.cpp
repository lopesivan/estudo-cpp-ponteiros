// 5. Exemplo prático: Classe Retângulo


class Retangulo
{
private:
    int largura;
    int altura;

public:
    Retangulo (int largura, int altura)
    {
        // NECESSÁRIO usar this aqui!
        this->largura = largura;
        this->altura = altura;
    }

    Retangulo& setLargura (int largura)
    {
        this->largura = largura;
        return *this;  // Para encadear
    }

    Retangulo& setAltura (int altura)
    {
        this->altura = altura;
        return *this;  // Para encadear
    }

    int area()
    {
        // NÃO precisa de this aqui (mas pode usar)
        return largura * altura;
    }

    void print()
    {
        cout << "Largura: " << largura
             << ", Altura: " << altura
             << ", Área: " << area() << endl;
    }
};

int main()
{
    Retangulo r (5, 3);
    r.print();  // Largura: 5, Altura: 3, Área: 15

    // Method chaining
    r.setLargura (10).setAltura (4);
    r.print();  // Largura: 10, Altura: 4, Área: 40
}
