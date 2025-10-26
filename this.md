# Uso de `this` em C++

O `this` é um **ponteiro** que aponta para o **próprio objeto** da classe. Ele é implícito, mas às vezes precisamos usá-lo explicitamente.

## 1. Quando os parâmetros têm o mesmo nome dos atributos

**Problema comum**: Nome do parâmetro igual ao nome do atributo

```cpp
class Pessoa {
private:
    string nome;
    int idade;
    
public:
    // SEM this - AMBÍGUO!
    Pessoa(string nome, int idade) {
        nome = nome;    // Qual é qual??? Não funciona!
        idade = idade;  // Atribui o parâmetro a ele mesmo!
    }
};
```

**Solução com `this`**:

```cpp
class Pessoa {
private:
    string nome;
    int idade;
    
public:
    Pessoa(string nome, int idade) {
        this->nome = nome;    // this->nome é o atributo
        this->idade = idade;  // idade (sem this) é o parâmetro
    }
    
    void print() {
        cout << "Nome: " << this->nome << ", Idade: " << this->idade << endl;
    }
};

int main() {
    Pessoa p("João", 25);
    p.print();  // Nome: João, Idade: 25
}
```

## 2. Retornar o próprio objeto (method chaining)

Permite encadear chamadas de métodos:

```cpp
class Calculadora {
private:
    int valor;
    
public:
    Calculadora(int v = 0) : valor(v) {}
    
    Calculadora& somar(int x) {
        valor += x;
        return *this;  // Retorna o próprio objeto
    }
    
    Calculadora& multiplicar(int x) {
        valor *= x;
        return *this;
    }
    
    void mostrar() {
        cout << "Valor: " << valor << endl;
    }
};

int main() {
    Calculadora calc(5);
    
    // Encadeamento de métodos (method chaining)
    calc.somar(3).multiplicar(2).somar(10);
    
    calc.mostrar();  // Valor: 26  ->  (5+3)*2+10 = 26
}
```

## 3. Passar o próprio objeto como argumento

```cpp
class Comparador {
public:
    void comparar(Comparador& outro) {
        if (this == &outro) {
            cout << "É o mesmo objeto!" << endl;
        } else {
            cout << "São objetos diferentes!" << endl;
        }
    }
};

int main() {
    Comparador c1, c2;
    
    c1.comparar(c1);  // É o mesmo objeto!
    c1.comparar(c2);  // São objetos diferentes!
}
```

## 4. Comparação: COM e SEM `this`

```cpp
class Conta {
private:
    double saldo;
    
public:
    Conta(double s) : saldo(s) {}
    
    // Método 1: SEM this (funciona quando não há conflito)
    void depositar1(double valor) {
        saldo += valor;  // OK - sem ambiguidade
    }
    
    // Método 2: COM this (mais explícito)
    void depositar2(double valor) {
        this->saldo += valor;  // Mais claro que é o atributo
    }
    
    // Método 3: COM this (NECESSÁRIO quando há conflito)
    void setSaldo(double saldo) {
        this->saldo = saldo;  // NECESSÁRIO! Senão não funciona
    }
    
    double getSaldo() {
        return saldo;  // this->saldo também funcionaria
    }
};

int main() {
    Conta c(100);
    c.depositar1(50);
    cout << c.getSaldo() << endl;  // 150
    
    c.setSaldo(200);
    cout << c.getSaldo() << endl;  // 200
}
```

## 5. Exemplo prático: Classe Retângulo

```cpp
class Retangulo {
private:
    int largura;
    int altura;
    
public:
    Retangulo(int largura, int altura) {
        // NECESSÁRIO usar this aqui!
        this->largura = largura;
        this->altura = altura;
    }
    
    Retangulo& setLargura(int largura) {
        this->largura = largura;
        return *this;  // Para encadear
    }
    
    Retangulo& setAltura(int altura) {
        this->altura = altura;
        return *this;  // Para encadear
    }
    
    int area() {
        // NÃO precisa de this aqui (mas pode usar)
        return largura * altura;
    }
    
    void print() {
        cout << "Largura: " << largura 
             << ", Altura: " << altura 
             << ", Área: " << area() << endl;
    }
};

int main() {
    Retangulo r(5, 3);
    r.print();  // Largura: 5, Altura: 3, Área: 15
    
    // Method chaining
    r.setLargura(10).setAltura(4);
    r.print();  // Largura: 10, Altura: 4, Área: 40
}
```

## Quando usar `this`?

| Situação | Precisa de `this`? | Por quê? |
|----------|-------------------|----------|
| Parâmetro tem o mesmo nome do atributo | ✅ **SIM** | Para diferenciar |
| Retornar o próprio objeto | ✅ **SIM** | Usar `return *this` |
| Passar o objeto como argumento | ✅ **SIM** | Usar `this` (ponteiro) |
| Sem conflito de nomes | ❌ Opcional | Funciona sem, mas pode usar para clareza |

## Resumo

```cpp
class Exemplo {
private:
    int x;
    
public:
    // 1. NECESSÁRIO - conflito de nomes
    Exemplo(int x) {
        this->x = x;  // PRECISA
    }
    
    // 2. OPCIONAL - sem conflito
    void metodo1() {
        x = 10;        // OK
        this->x = 10;  // Também OK (mais explícito)
    }
    
    // 3. NECESSÁRIO - retornar próprio objeto
    Exemplo& metodo2() {
        return *this;  // PRECISA
    }
};
```

**Dica**: Use `this` quando houver **conflito de nomes** ou quando precisar **retornar/passar o próprio objeto**. Fora isso, é opcional!
