##Matematica Discreta - Exercicio 6

Repositório do exercício 6 da disciplina de Matemática Discreta da Escola Politécnica de Pernambuco - UPE

#Autores

Hugo de Albuquerque Fonseca - <<hugoalbuquerque0@gmail.com>>

Mateus Lenier Rezende - <<mateuslenier@gmail.com>>

Thayna Maria Morim de Barros Barreto - <<tmorimbarreto@gmail.com>>

#Objetivo

Este exercicio tem como objetivo imprimir uma imagem de um automato finito, dados os seus parametros em um arquivo de texto.

#Entrada de texto

1. Linha 1: quantidade de estados (K). Valor inteiro que representa de q0 a q(K-1), ou seja, se K=1, tem-se um estado, q0. Para K=2, estados q0 e q1. E assim sucessivamente.
2. Linha 2: quantidade de letras do alfabeto. Valor inteiro, mínimo 2 (para 'a' e 'b') e máximo 26 (para alfabeto de 'a' até 'z'). A letra 'E' (maiúscula) é reservada para indicar uma transição vazia.
3. Linha 3: Valor inteiro; número do estado inicial; valor menor que K.
4. Linha 4: Lista de estados finais, separados por um espaço em branco. Valores inteiros menores que K.
5. Da linha 5 em diante, cada linha representa uma transição da função delta, sendo composta de 3 inteiros (estado origem, símbolo lido, estado destino), separados por espaço.
