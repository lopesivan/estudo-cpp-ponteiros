# Smart pointers
Ponteiros inteligentes em C++ são uma parte da biblioteca padrão
que provê uma forma mais segura de gerenciar a memória. Eles
garantem que os recursos alocados sejam liberados
automaticamente quando não forem mais necessários, evitando
assim vazamentos de memória e outros problemas relacionados à
gestão manual de memória. Existem três principais tipos de
ponteiros inteligentes na C++ Standard Library:

1. `std::unique_ptr`: Permite a posse exclusiva de um objeto.
   Quando o `unique_ptr` é destruído (por exemplo, quando sai de
escopo), o objeto que ele possui é automaticamente destruído e
sua memória é liberada. `unique_ptr` é leve e rápido e não
suporta a cópia, mas permite a transferência de posse com o uso
de `std::move()`. É útil quando você quer garantir que um
recurso seja possuído por apenas um controlador por vez.

   ```cpp
   std::unique_ptr<int> myUniquePtr(new int(10));
   ```

2. `std::shared_ptr`: Mantém uma contagem de referências para um
   recurso compartilhado. Quando a última `shared_ptr` que
aponta para o recurso é destruída ou reatribuída, o recurso é
deletado. `shared_ptr` é mais pesado que `unique_ptr` devido ao
controle da contagem de referências, mas é útil quando você
precisa de múltiplas referências para o mesmo recurso.

   ```cpp
   std::shared_ptr<int> mySharedPtr1(new int(20));
   std::shared_ptr<int> mySharedPtr2 = mySharedPtr1; // Ambos apontam para o mesmo inteiro
   ```

3. `std::weak_ptr`: É uma versão mais fraca de `shared_ptr` que
   não aumenta a contagem de referências. Isso significa que ele
não controla a vida útil do objeto ao qual aponta. `weak_ptr` é
usado para evitar o problema de referências circulares que pode
acontecer com `shared_ptr`, o que poderia levar a vazamentos de
memória. Você deve converter um `weak_ptr` em um `shared_ptr`
para acessar o objeto ao qual ele se refere.

   ```cpp
   std::weak_ptr<int> myWeakPtr = mySharedPtr1;
   ```

## **Vantagens dos Ponteiros Inteligentes:**

- **Gerenciamento Automático de Memória**: Os ponteiros
inteligentes cuidam da desalocação de memória automaticamente.
- **Segurança**: Reduzem a ocorrência de erros como vazamentos
de memória e dangling pointers.
- **Facilidade de Uso**: Fazem a interface com o gerenciamento
de memória mais intuitiva, especialmente para programadores que
vêm de linguagens com gerenciamento de memória automático.

## **Desvantagens dos Ponteiros Inteligentes:**

- **Custo de Performance**: Especialmente para `shared_ptr`, que
precisa manter o controle da contagem de referências.
- **Complexidade**: Em alguns casos, o uso de ponteiros
inteligentes pode adicionar complexidade ao código,
especialmente quando mal utilizados.

Em resumo, ponteiros inteligentes devem ser a escolha padrão
para gerenciamento de memória em C++ moderno, a menos que exista
uma razão específica para usar ponteiros brutos (raw pointers).
