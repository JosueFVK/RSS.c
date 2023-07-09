#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void removerTags(char *str) {
    int dentroTag = 0;
    char *src = str;
    char *dst = str;

    while (*src) {
        if (*src == '<') {
            dentroTag = 1;
            src++;
            continue;
        } else if (*src == '>') {
            dentroTag = 0;
            src++;
            continue;
        }

        if (!dentroTag) {
            *dst = *src;
            dst++;
        }

        src++;
    }

    *dst = '\0';
}

void extrairDados(xmlNode *no, FILE *arquivoHTML) {
    xmlNode *no_atual = NULL;

    char titulo[100];
    char descricao[1000] = "";  // Inicializar a descrição como uma string vazia
    char link[100];

    for (no_atual = no; no_atual; no_atual = no_atual->next) {
        if (no_atual->type == XML_ELEMENT_NODE && strcmp((char*)no_atual->name, "title") == 0) {
            xmlChar *tituloXML = xmlNodeGetContent(no_atual);
            strncpy(titulo, (char*)tituloXML, sizeof(titulo) - 1);
            titulo[sizeof(titulo) - 1] = '\0';
            xmlFree(tituloXML);
        }
        else if (no_atual->type == XML_ELEMENT_NODE && strcmp((char*)no_atual->name, "description") == 0) {
            xmlChar *descricaoXML = xmlNodeGetContent(no_atual);
            removerTags((char*)descricaoXML);
            strncpy(descricao, (char*)descricaoXML, sizeof(descricao) - 1);
            descricao[sizeof(descricao) - 1] = '\0';
            xmlFree(descricaoXML);

            fprintf(arquivoHTML, "<h1>%s</h1>\n", titulo);
            fprintf(arquivoHTML, "<p>%s</p>\n", descricao);
            fprintf(arquivoHTML, "<a href=\"%s\">Link</a>\n", link);

            titulo[0] = '\0';
            descricao[0] = '\0';
            link[0] = '\0';
        }
        else if (no_atual->type == XML_ELEMENT_NODE && strcmp((char*)no_atual->name, "link") == 0) {
            xmlChar *linkXML = xmlNodeGetContent(no_atual);
            strncpy(link, (char*)linkXML, sizeof(link) - 1);
            link[sizeof(link) - 1] = '\0';
        }

        extrairDados(no_atual->children, arquivoHTML);
    }
}

int main() {
    xmlDoc *doc = NULL;
    xmlNode *elemento_raiz = NULL;

    // Caminho do arquivo XML a ser lido
    const char* caminhoXML = "noticia.xml";

    // Abrir o arquivo XML em modo de leitura
    FILE* arquivoXML = fopen(caminhoXML, "r");
    if (arquivoXML == NULL) {
        printf("Erro ao abrir o arquivo XML.\n");
        return 1;
    }


    const char* caminhoHTML = "output.html";

    FILE* arquivoHTML = fopen(caminhoHTML, "w");
    if (arquivoHTML == NULL) {
        printf("Erro ao abrir o arquivo HTML de saída.\n");
        fclose(arquivoXML);
        return 1;
    }

    fprintf(arquivoHTML, "<html>\n<head>\n<title>Dados do XML</title>\n</head>\n<body>\n");

    // Ler o arquivo XML e extrair os dados
    doc = xmlReadFile(caminhoXML, NULL, 0);
    if (doc == NULL) {
        printf("Não foi possível abrir o arquivo XML.\n");
        fclose(arquivoXML);
        fclose(arquivoHTML);
        return 1;
    }

    elemento_raiz = xmlDocGetRootElement(doc);

    extrairDados(elemento_raiz, arquivoHTML);

    fprintf(arquivoHTML, "</body>\n</html>");

    fclose(arquivoXML);
    fclose(arquivoHTML);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}
