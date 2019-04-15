# Construção de um Compilador

• Objetivo:
  Montagem de um projeto que consiste na implementação dos blocos que compõem a construção de um compilador que tem a sua estrutura definida em análise e síntese, para um subconjunto de uma linguagem de programação.

• Primeira Etapa: Montagem do Manual da Linguagem
Tarefas:
1) Definição dos comandos de entrada e saída; de fluxo de controle (for, while, repeat); de decisão simples (if-then-else); comando de atribuição com operadores aritméticos, entre outros que houver. Nesta especificação deverá constar o comando em questão, a sintaxe do comando, uma explicação do comando e da sua sintaxe, um exemplo de funcionamento do comando.
2) Definição das regras léxicas que serão seguidas (como se forma e que tamanho máximo tem um identificador/variável, um número, comentario, etc.).
3) Definição do que será considerado erro léxico.

Entrega: 02/04/19

• Segunda Etapa: Analisador Léxico
  Consiste na implementação do analisador léxico, correspondente ao que foi especificado na primeira etapa.
Tarefas:
1) Criação de um autômato finito que descreverá o funcionamento do analisador léxico.
2) Respeitar a listagem dos símbolos terminais e não terminais (informados na gramática), com seus respectivos códigos.
3) Implementação do autômato descrito na tarefa 1.
Na implementação do analisador léxico deverá ser respeitado tudo o que foi definido no documento da primeira
etapa. O analisador léxico deverá retornar ao usuário o símbolo lido (token) com o respectivo código, e a linha em que
ele se encontra. Quando no programa fonte houver um erro léxico este também deverá ser reportado ao usuário indicando o tipo
de erro e a linha do mesmo.
Entrega: 30/04/19

• Terceira Etapa: Analisador Sintático
  A terceira etapa consiste na implementação do módulo referente ao analisador sintático. Deverá ser usado o algoritmo e as técnicas do analisador sintático descendente preditivo tabular (analisador sintático descendente sem backtracking).
Tarefas:
Implementação do analisador sintático (utilizando as técnicas do descendente preditivo tabular). Para a implementação deverá ser utilizar a tabela/matriz de análise sintática definida na gramática. O software deverá mostrar ao usuário o código do token, o token, a linha em que se encontra o token, a pilha a cada momento em que ela é modificada. Quando, no programa fonte, for encontrado um erro sintático, este deverá ser reportado ao usuário informando o erro e a linha em que ele se encontra.
Entrega: 28/5/19

• Quarta Etapa: Analisador Semântico
  A quarta etapa, consiste na implementação do Analisador Semântico com sua respectiva Tabela de Símbolos.
Tarefas:
1) Definir ações semânticas a serem implementadas.
2) Modificar a gramática da linguagem inserindo as ações semânticas definidas.
3) Montar um relatório explicando o que faz cada ação semântica.
4) Implementar as ações semânticas definidas.
  O software além de mostrar ao usuário tudo o que foi solicitado na segunda e terceira etapa deverá mostrar também a tabela de símbolos a cada momento em que ele for modificada. Quando for encontrado um erro semântico, no programa fonte, este deverá ser reportado ao usuário, informando o erro e a linha em que ele se encontra.
Entrega: 25/6/19
