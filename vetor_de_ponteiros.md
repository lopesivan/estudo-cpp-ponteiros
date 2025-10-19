Em C++ um `std::vector` pode armazenar **ponteiros normalmente**, basta especificar o tipo do ponteiro como o parâmetro do template.

### ✅ Exemplo simples com ponteiros crus

```cpp
#include <vector>

int main() {
    std::vector<int*> v;   // vector de ponteiros para int

    int a = 10;
    int b = 20;

    v.push_back(&a);
    v.push_back(&b);

    // Acessando os valores apontados
    for (int* p : v) {
        std::cout << *p << std::endl;
    }
}
```

### ✅ Exemplo com ponteiros para objetos

```cpp
#include <vector>

struct Pessoa {
    std::string nome;
};

int main() {
    std::vector<Pessoa*> pessoas;

    Pessoa p1{"Maria"};
    Pessoa p2{"João"};

    pessoas.push_back(&p1);
    pessoas.push_back(&p2);
}
```

### ⚠️ Cuidado com o tempo de vida dos objetos!

Se você armazenar ponteiros, os objetos apontados **devem continuar existindo** enquanto o vector os usa. Não armazene ponteiros para variáveis locais que irão sair de escopo.

---

### ✅ Alternativa melhor: smart pointers (`std::unique_ptr`, `std::shared_ptr`)

Mais seguro que usar ponteiros crus:

```cpp
#include <vector>
#include <memory>

struct Pessoa {
    std::string nome;
};

int main() {
    std::vector<std::unique_ptr<Pessoa>> pessoas;

    pessoas.push_back(std::make_unique<Pessoa>("Maria"));
    pessoas.push_back(std::make_unique<Pessoa>("João"));
}
```

✅ O `unique_ptr` cuida de liberar a memória automaticamente!

---

Se quiser, posso te explicar quando usar cada tipo (ponteiro cru vs smart pointer) ou como iterar, remover, etc. Quer que eu mostre mais exemplos?

Exato! **`std::vector` não pode armazenar referências diretamente.**

Em C++, referências (`T&`) **devem sempre referenciar algo existente e não podem ser “recolocadas”** (não são reatribuíveis). Já o `std::vector` precisa mover/copiar elementos internamente (por exemplo, ao redimensionar), o que **não é compatível com referências**.

Por isso, isto **não compila**:

```cpp
std::vector<int&> v; // ERRO!
```

---

## ✅ Alternativas para “armazenar referências”

Se você quer o efeito de armazenar referências, há três formas comuns:

### 1️⃣ Armazenar ponteiros (crus ou inteligentes)

```cpp
std::vector<int*> v;
```

### 2️⃣ Armazenar `std::reference_wrapper`

```cpp
#include <vector>
#include <functional>

int a = 10, b = 20;
std::vector<std::reference_wrapper<int>> v;
v.push_back(a);
v.push_back(b);

v[0].get() = 99; // Modifica 'a'
```

`reference_wrapper` simula uma referência "reatribuível" e o `vector` pode copiá-lo.

### 3️⃣ Usar `std::vector<std::unique_ptr<T>>` (se quiser gerenciar objetos dinamicamente)

---

✅ **Resumo:**

| Tipo                                      | Pode usar em vector? | Observação            |
| ----------------------------------------- | -------------------- | --------------------- |
| `T&` (referência)                         | ❌ Não                | Linguagem não permite |
| `T*` (ponteiro)                           | ✅ Sim                | Cuidado com lifetime  |
| `std::reference_wrapper`                  | ✅ Sim                | Forma segura e clara  |
| Smart pointer (`unique_ptr`,`shared_ptr`) | ✅ Sim                | Gerencia memória      |

Se quiser, posso te mostrar qual opção é melhor dependendo do seu caso!


