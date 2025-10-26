// solução:
class Pessoa
{
private:
    string nome;
    int idade;

public:
    Pessoa (string nome, int idade)
    {
        this->nome = nome;    // this->nome é o atributo
        this->idade = idade;  // idade (sem this) é o parâmetro
    }

    void print()
    {
        cout << "Nome: " << this->nome << ", Idade: " << this->idade << endl;
    }
};

int main()
{
    Pessoa p ("João", 25);
    p.print();  // Nome: João, Idade: 25
}
