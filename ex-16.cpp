// # Uso de this em C++
// O this é um ponteiro que aponta para o próprio objeto
// da classe. Ele é implícito, mas às vezes precisamos
// usá-lo explicitamente.

// 1. Quando os parâmetros têm o mesmo nome dos atributos
// Problema comum: Nome do parâmetro igual ao nome do
// atributo

class Pessoa
{
private:
    string nome;
    int idade;

public:
    // SEM this - AMBÍGUO!
    Pessoa (string nome, int idade)
    {
        nome = nome;    // Qual é qual??? Não funciona!
        idade = idade;  // Atribui o parâmetro a ele mesmo!
    }
};
