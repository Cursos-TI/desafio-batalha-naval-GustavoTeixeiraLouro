// Entrega de trabalho para graduação em ADS (Escola Estácio de Sá)
   Feito por Gustavo Teixeira Louro

# Batalha Naval em C - Nível Aventureiro

Implementação do jogo **Batalha Naval - Nível Aventureiro** em linguagem C.

## 🆕 Diferenças em relação ao Nível Novato

-   **Tabuleiro 10x10**: a matriz foi expandida para 10x10 posições.
-   **Posicionamento de quatro navios**: o sistema posiciona
    automaticamente quatro navios de tamanhos 5, 4, 3 e 3.
-   **Posicionamento diagonal**: pelo menos dois navios são posicionados
    na diagonal (um ↘ e um ↗).
-   **Exibição completa da matriz**: o tabuleiro é mostrado com:
    -   `0` indicando posição vazia\
    -   `3` indicando posição ocupada por parte de um navio

## 🚩 Funcionalidades

-   Matriz maior (10x10) para representar o tabuleiro.
-   Navios podem ser colocados horizontalmente, verticalmente ou
    diagonalmente.
-   Garantia de que pelo menos dois navios são posicionados em
    diagonais.
-   Exibição da matriz completa com números, facilitando a visualização.

## 📷 Exemplo de execução

    ==== BATALHA NAVAL - NIVEL AVENTUREIRO ====
    Matriz 10x10 com 0=livre e 3=ocupado por navio.

        1  2  3  4  5  6  7  8  9 10
     1  0  0  0  3  3  3  3  3  0  0
     2  0  0  0  0  0  0  0  0  0  0
     ...
    10  0  0  0  0  0  3  0  0  0  0

------------------------------------------------------------------------
