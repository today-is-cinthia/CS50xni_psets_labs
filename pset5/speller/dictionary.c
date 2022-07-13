// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"
#define hsize 500

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int tamaño = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //hashtable en la palabra original
    int valhash = hash(word);

    //accediendo a la lista en el índice del hash table
    node *nodo = table[valhash];

    while (nodo != NULL)
    {
        if (strcasecmp(word, nodo -> word) == 0)
        {
            return true;
        }
        nodo = nodo -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    long ope = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        ope += tolower(word[i]);
    }
    return ope % N;
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    //abrir el archivo dictionario
    FILE *apuntador = fopen(dictionary, "r");

    if (dictionary == NULL)
    {
        printf("No se  puede abrir. El archivo no existe");
        return false;
    }

    //arreglo para la longitud de la palabra
    char sigpalabra[LENGTH + 1];

    //ciclo para leer caracteres del string
    while (fscanf(apuntador, "%s", sigpalabra) != EOF)
    {
        //nuevo nodo para la palabra
        node *nodo = malloc(sizeof(node));
        if (nodo == NULL)
        {
            return false;
        }

        //copiar la palabra en el nuevo nodo
        strcpy(nodo->word, sigpalabra);

        //aplicando hashtable en la palabra siguiente
        int valhash = hash(sigpalabra);

        //asignando el nodo siguiente el puntero de arreglo de hashtable
        nodo -> next = table[valhash];
        table[valhash] = nodo;
        tamaño++;
    }

    fclose(apuntador);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return tamaño;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *nodo = table[i];
        while (nodo != NULL)
        {
            node *tmp = nodo;
            nodo = nodo -> next;
            free(tmp);
        }
        if (nodo == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
