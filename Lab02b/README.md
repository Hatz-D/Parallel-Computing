<h1>Laboratório 2b</h1>

<h3>Laboratório realizado no dia 13 de março</h3>

<ins>Conteúdo:</ins> Neste laboratório, a multiplicação de matrizes com o uso de threads em C foi explorada. O programa realiza a multiplicação de duas matrizes, A e B, para obter a matriz resultante C. O código utiliza pthreads para distribuir o trabalho de multiplicação concorrentemente. Ademais, uma comparação com diferentes quantidades de vCPUs foi realizada para obter o tempo de execução e speedup com números diferentes de núcleos.

<ins>Integrantes:</ins>

- Diogo Lourenzon Hatz

<h2>Índice</h2>

<ul>
<li><code>multiplicamatrizes.c</code>: Código-fonte do exercício paralelo proposto.</li>
<li><code>multiplicamatrizes-serial.c</code>: Código-fonte do exercício serial proposto.</li>
<li><code>multiplica-linha.c</code>: Código-fonte do exercício paralelo por linha proposto</li>
<li><code>whiletrue.c</code>: Código-fonte do teste de busywait realizado para o exercício proposto.</li>
</ul>

<hr>
<h2>Exercício</h2>
Para realizar a comparação dos tempos seriais e paralelos de execução do problema da multiplicação de matrizes, três versões diferentes deste exercício foram desenvolvidas: <code>multiplicamatrizes.c</code>, <code>multiplicamatrizes-serial.c</code> e <code>multiplica-linha.c</code>. Cada versão desse exercício corresponde à versão serial e duas abordagens para a versão paralela: uma com o cálculo por elemento da matriz e outra com o cálculo por linha/coluna da matriz. 

A função multiplicamatrizes é responsável por calcular cada célula da matriz C. Ela recebe um argumento com as coordenadas da célula a ser calculada (<code>i</code> e <code>j</code>), bem como o número de colunas n da matriz A, que é igual ao número de linhas n da matriz B (<code>n</code>). As threads criadas posteriormente executarão essa função para efetuar os cálculos de cada índice da matriz C.

É importante ressaltar que o vetor de argumentos das threads é alocado dinamicamente para cada thread para garantir que os argumentos <code>i</code> e <code>j</code> sejam passados para a função multiplicamatrizes de forma exclusiva, isto é, cada thread irá calcular uma célula delimitada pelos argumentos <code>i</code> e <code>j</code> fornecidos. Caso o vetor de argumentos não fosse criado dinamicamente para cada iteração dos laços alinhados, uma condição de corrida existiria para os valores presentes no endereço de memória compartilhado entre as threads. Alocando-se esse vetor dinamicamente a cada iteração garante que cada array de argumentos possua um endereço exclusivo, o que soluciona a condição de corrida encontrada. Ao fim de cada execução da função multiplicamatrizes, esse vetor de argumentos é desalocado.

Vale notar que para validar o paralelismo do código desenvolvido, um outro código foi criado para que threads sejam criadas e entrem no estado de busywait com um loop while. Desta forma, é possível obter a visualização de quais núcleos da CPU estão sendo ocupados pelas threads com um programa como <code>htop</code>. O código fonte deste teste é referente ao item <code>whiletrue.c</code> presente neste repositório.

<img src="" alt="Busywait">

<h2>Questões</h2>
<b>1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução</b>

Durante o desenvolvimento do exercício, foi notório como o tempo de execução serial não mudou com a adição ou remoção de vCPUs, assim como o tempo de execução paralelo apresentou uma diferença pouco significativa com a adição ou remoção de vCPUs, como é possível ver no gráfico abaixo. O fato de o tempo de execução serial ser menor do que o tempo de execução paralela para a multiplicação de matrizes 10x10 foi atribuído ao custo de criação e deleção das threads, que pode ser superior ao ganho tido pela paralelização do código desenvolvido.

<img src="" alt="Gráfico do tempo de execução serial e paralelo">

<b>2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.</b>

O speedup para 1, 2, 4, 6 e 8 processadores foi praticamente 1, o que representa uma constância no tempo de execução do código desenvolvido. Ou seja: mesmo que somente um núcleo fosse utilizado para a execução do código, o que representa um tempo serial, o tempo de execução seria o mesmo. Esse resultado pode ser atribuído ao fato de o problema possuir uma escala pequena. É provável que para problemas mais complexos, a adição de mais núcleos aumentaria o speedup.

<img src="" alt="Gráfico do speedup">

<b>3. Como você acha que poderia melhorar o seu algoritmo para obter maior benefício com o paralelismo? Para provar seu ponto, refaça a solução com essa abordagem e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.</b>

O resultado obtido pelo grupo foi atribuído ao custo de se criar e destruir inúmeras threads. Portanto, a abordagem encontrada para solucionar esse problema diz respeito à utilização de menos threads: ao invés de criar uma thread para cada elemento da matriz, criar uma thread para cada linha/coluna da matriz. Os resultados da experiência se encontram abaixo:

<img src="" alt="Gráfico do speedup">

<h2>Compilação</h2>

Para realizar a compilação dos códigos-fonte aqui disponibilizados, faz-se necessária a utilização do compilador GCC. Caso não o tenha instalado, basta digitar o seguinte comando em um terminal linux: <code>sudo yum install gcc</code>. A compilação dos arquivos .c deste repositório podem ser compilados da seguinte forma: <code>gcc exemplo.c -lpthread</code>, em que o campo exemplo é substituído pelo nome do arquivo .c. Após isso, um arquivo <code>a.out</code> será gerado. Vale ressaltar que como o código-fonte deste laboratório utiliza pthreads, é necessário adicionar o argumento <code>-lpthread</code> durante a compilação do programa. 

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab02/compilacao.png" alt="Processo de compilação">

<hr>
<h2>Execução</h2>
Para executá-lo, basta digitar o seguinte comando: <code>./a.out</code>. Caso o arquivo gerado possua um nome diferente, basta substituir o arquivo <code> a.out</code> pelo nome do arquivo gerado no comando anterior. Vale notar que o único programa que requer um argumento para a sua execução é o código-fonte <code>while-true.c</code>, o argumento sendo a quantidade de threads criadas para busywait.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab02/execucao.png" alt="Processo de execução">

