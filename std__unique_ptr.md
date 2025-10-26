# entender *por que* usamos `std::unique_ptr` e deleters personalizados no código C++ moderno.

Vamos fazer dois exemplos simples que mostram exatamente o mesmo conceito:

---

## 🧠 Exemplo 1 — Estilo C clássico (com `malloc` e `free`)

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Aloca manualmente memória para um inteiro
    int* p = (int*) malloc(sizeof(int));
    if (!p) {
        fprintf(stderr, "Falha ao alocar memória\n");
        return 1;
    }

    *p = 42;
    printf("Valor = %d\n", *p);

    // Lembre-se de liberar!
    free(p);

    return 0;
}
```

✅ Funciona, mas:

* Você precisa chamar `free` manualmente.
* Se der uma exceção ou `return` antes de `free`, há vazamento de memória.
* Em projetos grandes, isso vira uma armadilha fácil.

---

## 🚀 Exemplo 2 — Estilo moderno C++ (com `std::unique_ptr`)

```cpp
#include <iostream>
#include <memory>

int main()
{
    // Cria um unique_ptr para um inteiro
    auto p = std::make_unique<int>(42);

    std::cout << "Valor = " << *p << '\n';

    // NÃO precisa chamar delete/free — destrói automaticamente
    // ao sair do escopo (RAII = Resource Acquisition Is Initialization)
}
```

✅ Vantagens:

* `std::make_unique` cuida da alocação.
* Liberação é **automática** quando o ponteiro sai do escopo.
* Zero risco de vazamento, mesmo se lançar exceção ou retornar cedo.

---

## 🧩 Exemplo 3 — Custom deleter (igual ao Allegro)

Às vezes, o recurso **não é memória alocada com `new`**,
mas um *handle* de uma biblioteca C (ex: `ALLEGRO_DISPLAY*`,
`FILE*`, `SDL_Window*` etc.).  Nesses casos, usamos um
**deleter customizado**:

```cpp
#include <iostream>
#include <memory>
#include <cstdio> // FILE, fopen, fclose

// Define um deleter personalizado
struct FileCloser {
    void operator()(FILE* f) const noexcept {
        if (f) std::fclose(f);
    }
};

int main() {
    // Usa unique_ptr com deleter customizado
    std::unique_ptr<FILE, FileCloser> file(std::fopen("teste.txt", "w"));

    if (!file) {
        std::cerr << "Erro ao abrir arquivo.\n";
        return 1;
    }

    std::fprintf(file.get(), "Olá, C++ moderno!\n");
    // fclose() chamado automaticamente quando 'file' sai do escopo
}
```

✅ É exatamente o mesmo padrão que usamos para:

```cpp
std::unique_ptr<ALLEGRO_DISPLAY, AllegroDeleter> display(al_create_display(...));
```

---

### 🧭 Resumo

| Estilo             | Alocação                     | Liberação  | Risco de vazamento | Exemplo                    |
| ------------------ | ---------------------------- | ---------- | ------------------ | -------------------------- |
| C clássico         | `malloc` / `free`            | manual     | alto               | Allegro puro, OpenGL, etc. |
| C++ moderno (RAII) | `std::make_unique` / deleter | automática | nenhum             | Allegro com `unique_ptr`   |

---


Excelente pergunta 👏 — **sim**, dá pra usar `std::unique_ptr`
com **qualquer função de deleção**, incluindo `free`, desde que
o tipo combine com a assinatura esperada. Mas há alguns detalhes
importantes sobre **como declarar corretamente** o tipo.

Vamos passo a passo 👇

---

## 🧩 1️⃣ O que `std::unique_ptr` espera

Por padrão, `std::unique_ptr<T>` usa `delete ptr;` quando o objeto sai do escopo.
Se você quiser mudar isso, precisa declarar o **deleter**
como segundo template parameter:

```cpp
std::unique_ptr<T, Deleter>
```

onde `Deleter` pode ser:

* um *functor* (struct com `operator()`)
* um *lambda*
* um ponteiro de função (ex: `void (*)(T*)`)

---

## ✅ 2️⃣ Usando `free` diretamente

Se você aloca memória com `malloc`, pode usar
`std::unique_ptr` com `free` como deleter.

### Exemplo com `malloc` + `free`

```cpp
#include <iostream>
#include <memory>
#include <cstdlib> // malloc, free

int main() {
    // aloca uma "matriz" simples 3x3
    using Matrix = int; // só um apelido de tipo base

    // 👇 tipo de deleter é 'void(*)(void*)'
    std::unique_ptr<Matrix, decltype(&std::free)>
        matriz(static_cast<Matrix*>(std::malloc(3 * 3 * sizeof(Matrix))), &std::free);

    if (!matriz) {
        std::cerr << "Falha ao alocar memória.\n";
        return 1;
    }

    // preenche e imprime
    for (int i = 0; i < 9; ++i) {
        matriz.get()[i] = i * 10;
    }

    for (int i = 0; i < 9; ++i) {
        std::cout << matriz.get()[i] << ' ';
    }
    std::cout << '\n';

    // ✅ free() é chamado automaticamente quando matriz sai do escopo
}
```

🧠 **Resumo técnico:**

* `decltype(&std::free)` é o tipo exato de um ponteiro para função `void(void*)`.
* `std::unique_ptr<Matrix, decltype(&std::free)>` cria um smart pointer que usa `free` ao destruir.

---

## ⚙️ 3️⃣ Função genérica para alocar com RAII

Você pode até criar um *helper* pra encapsular isso:

```cpp
template <typename T>
auto make_malloc_ptr(std::size_t count)
{
    return std::unique_ptr<T, decltype(&std::free)>{
        static_cast<T*>(std::malloc(count * sizeof(T))),
        &std::free
    };
}
```

Uso:

```cpp
auto matriz = make_malloc_ptr<int>(9);
if (!matriz) return 1;
```

---

## ⚠️ 4️⃣ Cuidados

* Nunca misture `malloc` com `delete` ou `new` com `free`.
  (sempre mantenha par consistente!)
* `std::make_unique` **não** pode ser usado com `malloc` (ele sempre usa `new`).
* Se for alocar objetos complexos (com construtores), prefira `std::make_unique` normal.

---

## 🧭 5️⃣ Em resumo

| Tipo de alocação                 | Liberação             | Smart pointer correto                         |
| -------------------------------- | --------------------- | --------------------------------------------- |
| `new` / `new[]`                  | `delete` / `delete[]` | `std::unique_ptr<T>` / `std::unique_ptr<T[]>` |
| `malloc`                         | `free`                | `std::unique_ptr<T, decltype(&std::free)>`    |
| Recurso C (FILE*, Allegro, etc.) | função customizada    | `std::unique_ptr<T, CustomDeleter>`           |

---

Quer que eu te mostre o mesmo padrão aplicado a uma matriz 2D
(tipo `int** matriz`) com RAII também?





sim! você pode usar o mesmo “jeito do `malloc`+`free`”,
isto é, **usar o próprio ponteiro de função como
deleter**. Fica assim:

```cpp
#include <memory>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

// aliases com o tipo exato do deleter (decltype(&função))
using DisplayUPtr    = std::unique_ptr<ALLEGRO_DISPLAY,    decltype(&al_destroy_display)>;
using EventQueueUPtr = std::unique_ptr<ALLEGRO_EVENT_QUEUE,decltype(&al_destroy_event_queue)>;
using FontUPtr       = std::unique_ptr<ALLEGRO_FONT,       decltype(&al_destroy_font)>;

int main() {
    al_init();
    al_init_font_addon();

    int screen_width = 800, screen_height = 600;

    // mesmo estilo do exemplo da matriz com free:
    DisplayUPtr display{ al_create_display(screen_width, screen_height), &al_destroy_display };
    if (!display) {
        std::cerr << "Falha ao criar display.\n";
        return EXIT_FAILURE;
    }

    EventQueueUPtr event_queue{ al_create_event_queue(), &al_destroy_event_queue };
    if (!event_queue) {
        std::cerr << "Falha ao criar fila de eventos.\n";
        return EXIT_FAILURE;
    }

    FontUPtr font{ al_create_builtin_font(), &al_destroy_font };
    if (!font) {
        std::cerr << "Falha ao criar fonte.\n";
        return EXIT_FAILURE;
    }

    // ... uso normal: display.get(), event_queue.get(), font.get()

    // destruição automática ao sair do escopo (RAII)
    return EXIT_SUCCESS;
}
```

Isso é **idêntico em espírito** ao:

```cpp
std::unique_ptr<int, decltype(&std::free)>
    matriz(static_cast<int*>(std::malloc(9*sizeof(int))), &std::free);
```

A diferença é só o tipo do recurso e a função destruidora:

* `ALLEGRO_DISPLAY*` → `al_destroy_display`
* `ALLEGRO_EVENT_QUEUE*` → `al_destroy_event_queue`
* `ALLEGRO_FONT*` → `al_destroy_font`

Se quiser um *helper* genérico no mesmo estilo:

```cpp
template <typename T>
auto make_handle(T* p, void(*deleter)(T*)) {
    return std::unique_ptr<T, decltype(deleter)>{ p, deleter };
}

// uso:
// auto display = make_handle(al_create_display(w,h), &al_destroy_display);
```



Perfeito 👏 — dá sim para fazer o mesmo padrão com `using`, criando um alias de `std::unique_ptr` que usa **`free` como deleter**, exatamente como fizemos com o Allegro.

Aqui vai o exemplo completo e elegante em **C++17**, usando `malloc`/`free` e um `using` chamado `MallocUPtr` (ou `MatrixUPtr` se quiser algo mais específico):

---

### 🧩 Exemplo com alias `MatrixUPtr`

```cpp
#include <iostream>
#include <memory>
#include <cstdlib> // malloc, free

// Alias genérico: unique_ptr<T, decltype(&std::free)>
template<typename T>
using MallocUPtr = std::unique_ptr<T, decltype(&std::free)>;

int main() {
    using Matrix = int; // só um apelido

    // agora o deleter é passado uma vez só
    MallocUPtr<Matrix> matriz{
        static_cast<Matrix*>(std::malloc(3 * 3 * sizeof(Matrix))),
        &std::free
    };

    if (!matriz) {
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
```

---

### 🔍 Explicação

* `template<typename T> using MallocUPtr = std::unique_ptr<T, decltype(&std::free)>;`
  cria um **apelido genérico** que você pode usar para qualquer tipo alocado com `malloc`.

* Uso prático:

  ```cpp
  MallocUPtr<float> vetor{ static_cast<float*>(std::malloc(10*sizeof(float))), &std::free };
  ```

---

### 🧭 Comparativo rápido

| Tipo de recurso    | Alocação            | Liberação            | Alias de RAII                                     |
| ------------------ | ------------------- | -------------------- | ------------------------------------------------- |
| `new` / `delete`   | `new`               | `delete`             | `std::unique_ptr<T>`                              |
| `malloc` / `free`  | `malloc`            | `free`               | `MallocUPtr<T>` (como no exemplo)                 |
| `ALLEGRO_DISPLAY*` | `al_create_display` | `al_destroy_display` | `DisplayUPtr` com `decltype(&al_destroy_display)` |

---

Quer que eu mostre como estender o `MallocUPtr` pra lidar
com **matrizes 2D (ex: `int**`)** também — com liberação
automática linha a linha?



ótima pergunta 👏 — dá pra usar o parâmetro `N = 5` sim, mas o jeito que está ali (`template<typename T, int N = 5>`) **não tem efeito** ainda, porque o valor `N` não está sendo usado em lugar nenhum.

vamos ver como integrá-lo de verdade 👇

---

## 🧩 objetivo

queremos que o alias (ou um helper) saiba que a “matriz” tem tamanho `N×N`, e use esse valor pra alocar e percorrer.

---

## ✅ opção 1 — usar o `N` dentro de uma função helper

```cpp
#include <iostream>
#include <memory>
#include <cstdlib>

// alias do unique_ptr com free
template<typename T>
using MallocUPtr = std::unique_ptr<T, decltype(&std::free)>;

// helper que usa N
template<typename T, int N = 5>
auto make_matrix()
{
    return MallocUPtr<T>{
        static_cast<T*>(std::malloc(N * N * sizeof(T))),
        &std::free
    };
}

int main()
{
    constexpr int N = 5;
    auto matriz = make_matrix<int, N>();

    if (!matriz) {
        std::cerr << "Falha ao alocar memória.\n";
        return EXIT_FAILURE;
    }

    for (int i = 0; i < N * N; ++i)
        matriz.get()[i] = i;

    for (int i = 0; i < N * N; ++i) {
        std::cout << matriz.get()[i] << ' ';
        if ((i + 1) % N == 0) std::cout << '\n';
    }

    // free() automático ao sair do escopo
}
```

🔹 **Como funciona:**

* `make_matrix<int, 5>()` aloca uma matriz 5×5.
* o valor `N` é usado tanto na alocação (`N*N*sizeof(T)`) quanto nos loops.

---

## ✅ opção 2 — incorporar `N` diretamente no alias (só pra referência)

O `using MallocUPtr<T, int N = 5>` em si **não pode usar `N` dentro da expressão de tipo**, porque o alias só define o tipo do ponteiro — não pode executar código.
Mas dá pra deixar o `N` no alias **pra documentação** e depois usar `N` num helper.

```cpp
template<typename T, int N = 5>
using MatrixUPtr = std::unique_ptr<T, decltype(&std::free)>;

template<typename T, int N = 5>
MatrixUPtr<T, N> make_matrix()
{
    return { static_cast<T*>(std::malloc(N * N * sizeof(T))), &std::free };
}
```

uso:

```cpp
constexpr int N = 5;
auto matriz = make_matrix<int, N>();
```

---

## 🧭 resumo

| abordagem                                  | onde `N` é usado         | observação              |
| ------------------------------------------ | ------------------------ | ----------------------- |
| **1. helper separado (`make_matrix`)**     | dentro da função         | mais idiomático         |
| **2. alias + helper**                      | no helper                | mantém o alias genérico |
| **apenas alias (`using MallocUPtr<T,N>`)** | não usa `N` (sem efeito) | apenas decorativo       |

---

quer que eu te mostre uma versão que realmente trata como **matriz 2D** (acesso `matriz(x, y)` com operador customizado, mas ainda usando `malloc` + `unique_ptr`)?
