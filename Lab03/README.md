<h1>Laboratório 3</h1>

<h3>Laboratório realizado no dia 18 de abril</h3>

<ins>Conteúdo:</ins> Neste laboratório, o cálculo de uma integral utilizando a regra dos trapézios foi explorado através da construção de algoritmos paralelos em C utilizando a biblioteca OpenMP. O programa distribui o cálculo de porções de trapézios em diferentes threads em somas parciais para depois somar as somas parciais em uma variável global compartilhada entre as threads. Ademais, uma comparação com diferentes quantidades de vCPUs foi realizada para obter o tempo de execução e speedup com números diferentes de núcleos.

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

Vale notar que os únicos argumentos passados para as thread são as variáveis <code>a</code>, <code>b</code> e <code>n</code>, que são globais para todas as threads. Por isso, não há condição de corrida em relação ao valor atribuido a essas variáveis. Ademais, cada thread utilizará das funções <code>omp_get_thread_num()</code> e <code>omp_get_num_threads()</code> para delimitar quais trapézios serão calculados por determinada thread.

Vale notar que para validar o paralelismo do código desenvolvido, um outro código foi criado para que threads sejam criadas e entrem no estado de busywait com um loop while. Desta forma, é possível obter a visualização de quais núcleos da CPU estão sendo ocupados pelas threads com um programa como <code>htop</code>. O código fonte deste teste é referente ao item <code>teste.c</code> presente neste repositório.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/compilacao-teste.png" alt="Busywait">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/htop-teste.png" alt="Busywait">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab02b/specs.PNG" alt="Specs do processador">

<hr>

<h2>Questões</h2>
<ins><b>1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução.</b></ins>

Durante o desenvolvimento do exercício, foi notório como o tempo de execução serial não mudou com a adição ou remoção de vCPUs, assim como o tempo de execução paralelo apresentou uma diferença muito significativa com a adição de vCPUs, reduzindo bastante o tempo de execução do programa. Essa diferença alarmante na versão paralela do código pode ser atribuída ao paralelismo sendo efetuado em todos os cores do processador utilizado. Vale notar que para a versão paralela do código, foi padronizado a utilização de 8 threads. 

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/tabela-sem-critical.png" alt="Tabela do tempo de execução serial e paralelo">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/paralelo-vs-serial-sem-critical.png" alt="Gráfico do tempo de execução serial e paralelo">

<ins><b>2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.</b></ins>

O speedup para 1, 2, 4, 6 e 8 processadores aumentou de uma forma diretamente proporcional com a adição de vCPUs para a versão paralela do código desenvolvido, tendo em vista que o paralelismo foi aplicado ao programa. Já o speedup para a versão serial do programa se manteve como 1, considerando que não houve ganho de desempenho com a adição de vCPUs.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/speedup.png" alt="Gráfico do speedup">

<ins><b>3. Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.</b></ins>

Com a adição da diretiva critical no programa, a condição de corrida existente envolvendo a somatória das somas parciais calculadas pelas threads na variável global é resolvida, uma vez que, assim, somente uma das threads poderá acessar e modificar o valor dessa variável por vez. É notório como o speedup para essa versão continuou a crescer conforme a adição de vCPUs, no entanto, o tempo médio da execução dessa versão do código foi ligeiramente maior do que a versão sem a diretiva critical. Essa diferença pode ser atribuída ao fato que o critical representa uma porção serial no código, em que somente uma thread pode acessar o valor da variável global por vez.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/speedup-critical.png" alt="Gráfico do speedup">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/tabela-critical.png" alt="Tabela">

<hr>

<h2>Compilação</h2>

Para realizar a compilação dos códigos-fonte aqui disponibilizados, faz-se necessária a utilização do compilador GCC. Caso não o tenha instalado, basta digitar o seguinte comando em um terminal linux: <code>sudo yum install gcc</code>. A compilação dos arquivos .c deste repositório podem ser compilados da seguinte forma: <code>gcc exemplo.c -fopenmp -lm</code>, em que o campo exemplo é substituído pelo nome do arquivo .c. Após isso, um arquivo <code>a.out</code> será gerado. Vale ressaltar que como o código-fonte deste laboratório utiliza a biblioteca OpenMP e Math, é necessário adicionar os argumentos <code>-fopenmp</code> e <code>-lm</code> durante a compilação do programa. 

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/compilacao.png" alt="Processo de compilação">

<hr>

<h2>Execução</h2>
Para executá-lo, basta digitar o seguinte comando: <code>./a.out x y m n</code>. Caso o arquivo gerado possua um nome diferente, basta substituir o arquivo <code> a.out</code> pelo nome do arquivo gerado no comando anterior. Vale notar que o programa <code>teste.c</code> requer um único argumento para a sua execução, o argumento sendo a quantidade de threads criadas para busywait.

<hr>

<ins>Argumentos:</ins>

<ol>
<li><code>X</code>: A variável 'a' do código;</li>
<li><code>Y</code>: A variável 'b' do código;</li>
<li><code>M</code>: A quantidade de trapézios a serem calculados;</li>
<li><code>N</code>: A quantidade de threads a serem executadas.</li>
</ol>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/execucao-paralela-sem-critical.png" alt="Processo de execução">

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/execucao-sem-critical.png" alt="Processo de execução">
