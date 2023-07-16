# RSS.c

Este programa é um conversor simples de XML para HTML. Ele lê um arquivo XML, extrai os dados relevantes e gera um arquivo HTML contendo as informações extraídas.

## Pré-requisitos

Antes de executar o programa, verifique se você atende aos seguintes requisitos:

- Compilador C (GCC ou qualquer outro compilador compatível)
- Biblioteca libxml2

## Primeiros Passos

1. Clone o repositório ou faça o download dos arquivos do código-fonte.
2. Verifique se a biblioteca libxml2 está instalada em seu sistema. Caso contrário, você pode instalá-la usando o gerenciador de pacotes específico do seu sistema operacional (por exemplo, `apt-get` para o Ubuntu ou `brew` para o macOS).
3. Compile o código-fonte usando um compilador C. Execute o seguinte comando no terminal:

   ```
   gcc -o dec main.c -I/usr/include/libxml2 -lxml2
   ```


## Uso

1. Coloque o seu arquivo XML no mesmo diretório do executável main.
3. Execute o comando e em seguida o executavel.
4. O programa irá gerar um arquivo HTML chamado `output.html` no mesmo diretório do arquivo XML.

## Como Funciona

O programa utiliza a biblioteca libxml2 para analisar o arquivo XML e extrair os dados relevantes. Ele define duas funções auxiliares:

- `removerTags`: Remove as tags HTML de uma string fornecida.
- `extrairDados`: Percorre recursivamente a árvore XML e extrai os dados dos elementos `<title>`, `<description>` e `<link>`.

A função principal realiza as seguintes etapas:

1. Abre o arquivo XML no modo de leitura e verifica se há erros.
2. Abre o arquivo HTML de saída no modo de escrita e verifica se há erros.
3. Escreve as tags HTML iniciais no arquivo de saída.
4. Lê o arquivo XML e cria um documento XML usando a função `xmlReadFile`.
5. Obtém o elemento raiz do documento XML.
6. Chama a função `extrairDados` com o elemento raiz e o arquivo de saída para extrair os dados e escrevê-los no arquivo HTML.
7. Escreve as tags HTML de fechamento no arquivo de saída.
8. Fecha os arquivos XML e HTML, libera a memória do documento XML e faz a limpeza do analisador libxml2.

6.Contribuição
Josué Felipe Vieira Klich(https://www.linkedin.com/in/josu%C3%A9-vieira-493768224/)
