// 4. Comparação: COM e SEM this

class Conta
{
private:
    double saldo;

public:
    Conta (double s) : saldo (s) {}

    // Método 1: SEM this (funciona quando não há conflito)
    void depositar1 (double valor)
    {
        saldo += valor;  // OK - sem ambiguidade
    }

    // Método 2: COM this (mais explícito)
    void depositar2 (double valor)
    {
        this->saldo += valor;  // Mais claro que é o atributo
    }

    // Método 3: COM this (NECESSÁRIO quando há conflito)
    void setSaldo (double saldo)
    {
        this->saldo = saldo;  // NECESSÁRIO! Senão não funciona
    }

    double getSaldo()
    {
        return saldo;  // this->saldo também funcionaria
    }
};

int main()
{
    Conta c (100);
    c.depositar1 (50);
    cout << c.getSaldo() << endl;  // 150

    c.setSaldo (200);
    cout << c.getSaldo() << endl;  // 200
}
