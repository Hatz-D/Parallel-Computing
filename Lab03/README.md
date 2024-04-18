<h1>Laboratório 3</h1>

<h3>Laboratório realizado no dia 18 de abril</h3>

<ins>Conteúdo:</ins> Neste laboratório, o cáluco de uma integral utilizando a regra dos trapézios foi explorado através da construção de algoritmos paralelos em C utilizando a biblioteca OpenMP. O programa distribui o cálculo de porções de trapézios em diferentes threads em somas parciais para depois somar as somas parciais em uma variável global compartilhada entre as threads. Ademais, uma comparação com diferentes quantidades de vCPUs foi realizada para obter o tempo de execução e speedup com números diferentes de núcleos.

<ins>Integrantes:</ins>

- Diogo Lourenzon Hatz

<h2>Índice</h2>

<ul>
<li><code>trapezio-paralelo.c</code>: Código-fonte do exercício paralelo proposto.</li>
<li><code>critical.c</code>: Código-fonte do exercício paralelo proposto com exclusão mútua.</li>
<li><code>teste.c</code>: Código-fonte do teste de busywait realizado para o exercício proposto.</li>
</ul>


