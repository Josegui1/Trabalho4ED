# Sistema de Autocomplete de Jogos com Trie

## Descrição do Projeto

Este projeto implementa um sistema simples de autocomplete de jogos utilizando a estrutura de dados Trie.

Cada jogo possui um título, uma descrição curta e um valor de popularidade. A Trie armazena os títulos dos jogos caractere por caractere, permitindo buscas eficientes por prefixo.

O programa recebe pela linha de comando um número `k` e um prefixo. Em seguida, retorna até `k` jogos cujo título começa com esse prefixo, ordenados pelos seguintes critérios:

1. Maior popularidade;
2. Em caso de empate, ordem alfabética pela chave de busca do título.

A busca é case-insensitive, ou seja, não diferencia letras maiúsculas e minúsculas, e também ignora espaços em branco. Por exemplo, o título "Resident Evil Village" é convertido para a chave de busca "residentevilvillage".

## Estrutura do Projeto

O projeto está organizado nos seguintes arquivos:

```text
main.cpp
Game.hpp
Game.cpp
Trie.hpp
Trie.cpp
GamesDatabase.hpp
GamesDatabase.cpp
```

### Descrição dos arquivos

* `main.cpp`: arquivo principal do programa. Ele lê os argumentos da linha de comando, cria a Trie, insere os jogos da base e imprime os resultados do autocomplete.
* `Game.hpp`: declaração da classe `Game`.
* `Game.cpp`: implementação dos métodos da classe `Game`.
* `Trie.hpp`: declaração das classes `Trie` e `TrieNode`.
* `Trie.cpp`: implementação da Trie, incluindo inserção, busca exata, autocomplete, normalização de texto e ordenação dos resultados.
* `GamesDatabase.hpp`: declaração da lista de jogos e da quantidade de jogos.
* `GamesDatabase.cpp`: definição da base inicial de jogos.

## Classe Game

A classe `Game` representa um jogo do catálogo.

Cada objeto possui:

* título;
* descrição curta;
* popularidade.

A Trie armazena ponteiros para objetos `Game` já existentes na base de jogos, sem criar novas cópias dinamicamente.

## Classe Trie

A classe `Trie` é responsável por armazenar os jogos e realizar as buscas.

Ela possui métodos para:

* inserir jogos;
* verificar se um título existe;
* converter textos para chave de busca;
* buscar jogos por prefixo;
* ordenar os resultados do autocomplete.

A chave de busca é gerada removendo espaços e convertendo letras maiúsculas para minúsculas.

Exemplos:

```cpp
toSearchKey("Hades") == "hades"
toSearchKey("Half Life") == "halflife"
toSearchKey("HALF L") == "halfl"
toSearchKey("Portal 2") == "portal2"
```

## Compilação

Para compilar o projeto, execute no terminal:

```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```

Todos os arquivos devem estar no mesmo diretório.

## Execução

O programa deve ser executado no seguinte formato:

```bash
./app k prefixo
```

Onde:

* `k` é a quantidade máxima de sugestões desejadas;
* `prefixo` é o prefixo usado na busca.

Exemplo:

```bash
./app 3 ha
```

Caso o prefixo contenha espaços, ele deve ser passado entre aspas:

```bash
./app 5 "half l"
```

## Exemplos de Uso

### Exemplo 1

Comando:

```bash
./app 3 ha
```

Saída esperada:

```text
Hades | Roguelike de acao baseado na mitologia grega | 95
Half Life | FPS classico de ficcao cientifica | 92
Halo | FPS futurista com campanha e multiplayer | 85
```

### Exemplo 2

Comando:

```bash
./app 5 "half l"
```

Saída esperada:

```text
Half Life | FPS classico de ficcao cientifica | 92
```

### Exemplo 3

Comando:

```bash
./app 3 HA
```

A saída deve ser equivalente à busca por:

```bash
./app 3 ha
```

Isso acontece porque a busca não diferencia letras maiúsculas e minúsculas.

### Exemplo 4

Comando:

```bash
./app 3 zelda
```

Caso nenhum jogo seja encontrado, a saída será:

```text
No results found
```

### Exemplo 5

Comando incorreto:

```bash
./app
```

Saída esperada:

```text
Usage: ./app k prefix
```

## Funcionamento Geral

Ao iniciar, o programa cria uma Trie vazia. Depois, percorre a lista de jogos definida em `GamesDatabase.cpp` e insere cada jogo na estrutura.

Cada título é convertido para uma chave de busca antes de ser inserido. Essa chave ignora espaços e diferencia apenas letras minúsculas e números.

Durante o autocomplete, o programa primeiro percorre a Trie seguindo os caracteres do prefixo informado. Se o prefixo existir, a Trie coleta todos os jogos presentes na subárvore correspondente. Em seguida, os resultados são ordenados manualmente por popularidade decrescente e, em caso de empate, por ordem alfabética da chave de busca.

Por fim, o programa imprime até `k` resultados.

