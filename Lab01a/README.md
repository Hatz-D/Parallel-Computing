<h1>Laboratório 1a</h1>

<h3>Laboratório realizado no dia 3 de março</h3>

<ins>Conteúdo:</ins> Um programa "Hello, world!" foi desenvolvido e enviado para este repositório através da ferramenta de versionamento git. O código foi desenvolvido, compilado e executado no ambiente da AWS gerenciado pelo grupo.

<ins>Integrantes:</ins>

- Diogo Lourenzon Hatz

<h2>Índice</h2>

<ul>
<li><code>hello-world.c</code>: Código-fonte do "hello, world!";</li>
<li><code>compilado.bin</code>: Binário do código-fonte do programa "hello, world!";</li>
<li><code>logs</code>: Log de execução do programa.</li>
</ul>

<h2>Exercício</h2>

Neste lab, um simples programa "Hello, world!" foi escrito, compilado e executado no ambiente de cloud da AWS.

<h2>Compilação</h2>

Para realizar a compilação dos códigos-fonte aqui disponibilizados, faz-se necessária a utilização do compilador GCC. Caso não o tenha instalado, basta digitar o seguinte comando em um terminal linux: <code>sudo yum install gcc</code>. A compilação dos arquivos .c deste repositório podem ser compilados da seguinte forma: <code>gcc exemplo.c</code>, em que o campo exemplo é substituído pelo nome do arquivo .c. Após isso, um arquivo <code>a.out</code> será gerado.

<h2>Execução</h2>

Para executar o arquivo binário gerado, basta digitar o seguinte comando: <code>./a.out</code>. Caso o arquivo gerado possua um nome diferente, basta substituir o arquivo <code>a.out</code> pelo nome do arquivo gerado no comando anterior.

<img src="https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab01a/compilado.png" alt="Compilação e execução">

<hr>

<h2>Geração do log de execução</h2>

O log de execução do programa foi gerado através do seguinte comando: <code>./compilado.bin >> logs</code>, que representa o append da saída do código no arquivo <code>logs</code>.

<img src = "https://raw.githubusercontent.com/Hatz-D/Parallel-Computing/main/src/Lab01a/logs.png" alt="Geração do log de execução">

<ins>Referências:</ins>
<ul>
<li>https://docs.github.com/pt/authentication/connecting-to-github-with-ssh/managing-deploy-keys</li>
<li>https://docs.github.com/pt/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent#generating-a-new-ssh-key</li>
</ul>
