<h1>Projeto - Entrega 1</h1>

<h3>Laboratório realizado no dia 28 de abril</h3>

<ins>Conteúdo:</ins> Para este projeto, o cálculo da constante matemática de Euler utilizando a série de Taylor foi explorado através da construção de algoritmos paralelos em C utilizando a biblioteca OpenMP. O programa distribui o cálculo de porções de somatórias em diferentes threads em somas parciais para depois somar as somas parciais em uma variável global compartilhada entre as threads. Ademais, uma comparação com diferentes quantidades de vCPUs foi realizada para obter o tempo de execução e speedup com números diferentes de núcleos. Para se obter uma maior precisão no cálculo da aproximação, as bibliotecas MPFR e GMP foram utilizadas para se criar estruturas cuja precisão de número de bits é limitada somente pela memória disponível no computador.

<ins>Integrantes:</ins>

- Diogo Lourenzon Hatz

<h2>Índice</h2>

<ul>
<li><code>parallel.c</code>: Código-fonte do exercício paralelo proposto.</li>
<li><code>critical.c</code>: Código-fonte do exercício paralelo proposto com a diretiva critical.</li>
</ul>

<hr>
<h2>Exercício</h2>
Para realizar a comparação dos tempos seriais e paralelos de execução do problema da aproximação do número de Euler através da série de Taylor, duas versões diferentes deste exercício foram desenvolvidas: <code>parallel.c</code> e <code>critical.c</code>. Cada versão desse exercício corresponde a duas abordagens para a versão paralela: uma com o cálculo sem a utilização do prag critical e outra com o cálculo com a utilização do prag critical.

A função <code>soma</code> é responsável por calcular uma série de somatórias da série de Taylor <code>(1/n!)</code>. Ela recebe um argumento com o vetor de fatoriais <code>vet</code> calculados na função <code>fatorial</code>, bem como o número de somatórias a serem calculados <code>n</code>, a quantidade de bits <code>nBits</code> que representarão a precisão das variáveis <code>mpfr_t</code> e um ponteiro para a variável global <code>globalPointer</code>. As threads criadas posteriormente executarão essa função para efetuar os cálculos das somatórias da série.

Vale notar que os únicos argumentos passados para as thread são as variáveis <code>n</code>, <code>vet</code>, <code>nBits</code> e <code>globalPointer</code>, que são globais para todas as threads. Há uma condição de corrida presente na agregação das somatórias parciais de cada thread na variável global <code>global</code>, portanto, a diretiva <code>critical</code> foi utilizada para fazer com que essa variável só seja modificada por uma thread de cada vez. Já para o vetor de fatoriais <code>vet</code>, não há condição de corrida presente, considerando que cada thread irá acessar os índices do vetor somente para leitura. Ademais, cada thread utilizará das funções <code>omp_get_thread_num()</code> e <code>omp_get_num_threads()</code> para delimitar quais somatórias serão calculados por determinada thread.

Vale notar que para validar o paralelismo do código desenvolvido, um outro código foi criado para que threads sejam criadas e entrem no estado de busywait com um loop while. Desta forma, é possível obter a visualização de quais núcleos da CPU estão sendo ocupados pelas threads com um programa como <code>htop</code>. O código fonte deste teste é referente ao item <code>teste.c</code> presente no subdiretório <code>Lab03</code> deste repositório.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/compilacao-teste.png" alt="Busywait">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab03/htop-teste.png" alt="Busywait">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab02b/specs.PNG" alt="Specs do processador">

<hr>

<h2>Questões</h2>
<ins><b>1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução.</b></ins>

Durante o desenvolvimento do exercício, foi notório como o tempo de execução serial não mudou com a adição ou remoção de vCPUs, assim como o tempo de execução paralelo apresentou uma diferença muito significativa com a adição de vCPUs, reduzindo bastante o tempo de execução do programa. Essa diferença alarmante na versão paralela do código pode ser atribuída ao paralelismo sendo efetuado em todos os cores do processador utilizado. Vale notar que para a versão paralela do código, foi padronizado a utilização de 8 threads. 

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/tabela.png" alt="Tabela do tempo de execução serial e paralelo">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/grafico-serial-vs-paralela.png" alt="Gráfico do tempo de execução serial e paralelo">

<ins><b>2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.</b></ins>

O speedup para 1, 2, 4, 6 e 8 processadores aumentou de uma forma diretamente proporcional com a adição de vCPUs para a versão paralela do código desenvolvido, tendo em vista que o paralelismo foi aplicado ao programa. Já o speedup para a versão serial do programa se manteve como 1, considerando que não houve ganho de desempenho com a adição de vCPUs.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/speedup.png" alt="Gráfico do speedup">

<ins><b>3. Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.</b></ins>

Com a adição da diretiva critical no programa, a condição de corrida existente envolvendo a somatória das somas parciais calculadas pelas threads na variável global é resolvida, uma vez que, assim, somente uma das threads poderá acessar e modificar o valor dessa variável por vez. É notório como o speedup para essa versão continuou a crescer conforme a adição de vCPUs, no entanto, o tempo médio da execução dessa versão do código foi ligeiramente maior do que a versão sem a diretiva critical. Essa diferença pode ser atribuída ao fato que o critical representa uma porção serial no código, em que somente uma thread pode acessar o valor da variável global por vez.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/speedup-critical.png" alt="Gráfico do speedup">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/tabela-critical.png" alt="Tabela">

<br>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/grafico-paralela-critical.png" alt="Gráfico do tempo de execução serial e paralelo">

<hr>

<h2>Compilação</h2>

Para realizar a compilação dos códigos-fonte aqui disponibilizados, faz-se necessária a utilização do compilador GCC. Caso não o tenha instalado, basta digitar o seguinte comando em um terminal linux: <code>sudo yum install gcc</code>. A compilação dos arquivos .c deste repositório podem ser compilados da seguinte forma: <code>gcc exemplo.c -lmpfr -lgmp -fopenmp</code>, em que o campo exemplo é substituído pelo nome do arquivo .c. Após isso, um arquivo <code>a.out</code> será gerado. Vale ressaltar que como o código-fonte deste laboratório utiliza as bibliotecas OpenMP, MPFR e GMP, é necessário adicionar os argumentos <code>-fopenmp</code>, <code>lgmp</code> e <code>-lmpfr</code> durante a compilação do programa. Ademais, como as bibliotecas MPFR e GMP não são nativas ao GCC, faz-se necessário fazer o download delas pela internet. O link para o download está disponível na seção de referências deste subdiretório. 

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/compilacao.png" alt="Processo de compilação">

<hr>

<h2>Execução</h2>
Para executá-lo, basta digitar o seguinte comando: <code>./a.out x y z</code>. Caso o arquivo gerado possua um nome diferente, basta substituir o arquivo <code> a.out</code> pelo nome do arquivo gerado no comando anterior. Vale notar que o programa <code>teste.c</code> requer um único argumento para a sua execução, o argumento sendo a quantidade de threads criadas para busywait.

Para a execução dos programas desenvolvidos, foi padronizado o cálculo de 5.000.000 de iterações com uma precisão de 7.000 bits por cada variável <code>mpfr_t</code>.

<hr>

<ins>Argumentos:</ins>

<ol>
<li><code>X</code>: A quantidade de threads a serem executadas;</li>
<li><code>Y</code>: A quantidade de somatórias a serem calculadas;</li>
<li><code>Z</code>: A precisão do número a ser calculado (bits);</li>
</ol>

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/execucao.png" alt="Processo de execução">

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Projeto/Entrega1/execucao2.png" alt="Processo de execução">

<hr>

<h2>Referências</h2>

<ul>
<li>Documentação do MPFR, disponível no seguinte link: https://www.mpfr.org/mpfr-current/mpfr.html</li>
<li>Documentação do GMP, disponível no seguinte link: https://gmplib.org/manual/</li>
</ul>
