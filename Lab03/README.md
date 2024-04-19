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

<hr>
<h2>Exercício</h2>
Para realizar a comparação dos tempos seriais e paralelos de execução do problema da integral através do método dos trapézio, duas versões diferentes deste exercício foram desenvolvidas: <code>trapezio-paralelo.c</code> e <code>critical.c</code>. Cada versão desse exercício corresponde a duas abordagens para a versão paralela: uma com o cálculo sem a utilização do prag critical e outra com o cálculo com a utilização do prag critical. 

A função <code>soma</code> é responsável por calcular uma série de trapézios da função seno. Ela recebe um argumento com as coordenadas do eixo X a ser calculada (<code>a</code> e <code>b</code>), bem como o número de trapézios a serem calculados <code>n</code>. As threads criadas posteriormente executarão essa função para efetuar os cálculos dos trapézios da função

parei aqui.

É importante ressaltar que o vetor de argumentos das threads é alocado dinamicamente para cada thread para garantir que os argumentos <code>i</code> e <code>j</code> sejam passados para a função multiplicamatrizes de forma exclusiva, isto é, cada thread irá calcular uma célula delimitada pelos argumentos <code>i</code> e <code>j</code> fornecidos. Caso o vetor de argumentos não fosse criado dinamicamente para cada iteração dos laços alinhados, uma condição de corrida existiria para os valores presentes no endereço de memória compartilhado entre as threads. Alocando-se esse vetor dinamicamente a cada iteração garante que cada array de argumentos possua um endereço exclusivo, o que soluciona a condição de corrida encontrada. Ao fim de cada execução da função multiplicamatrizes, esse vetor de argumentos é desalocado.

Vale notar que para validar o paralelismo do código desenvolvido, um outro código foi criado para que threads sejam criadas e entrem no estado de busywait com um loop while. Desta forma, é possível obter a visualização de quais núcleos da CPU estão sendo ocupados pelas threads com um programa como <code>htop</code>. O código fonte deste teste é referente ao item <code>whiletrue.c</code> presente neste repositório.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab02b/busywait-compilacao.PNG" alt="Busywait">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab02b/htop-busywait.PNG" alt="Busywait">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab02b/specs.PNG" alt="Specs do processador">

<hr>
