#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CHILDREN_SIZE 30

// Structure for a trie. Each node stores a char as data and its children as an array.
typedef struct Trie {
    char data;
    struct Trie *children[CHILDREN_SIZE];
} Trie;

// Default Constructor
Trie* trieCreate() {
    return calloc(1, sizeof(Trie));
}

// Parameterized Constructor
Trie* trieCreateByData(char c) {
    Trie* trie = trieCreate();
    trie->data = c;
    return trie;
}

// Insert word into obj
void trieInsert(Trie* obj, char * word) {
    Trie* current = obj;
    for (int i = 0; i <= strlen(word); i++) {
        char c;
        bool added = false;
        int end = 0;

        if (i == strlen(word)) c = '0';
        else c = word[i];

        for (int j = 0; j < CHILDREN_SIZE; j++) {
            Trie* t = current->children[j];
            if (t == NULL) {
                end = j; 
                break; 
            }
            if (t->data > c) { 
                for (int k = CHILDREN_SIZE-1; k > j; k--) { 
                    current->children[k] = current->children[k-1];
                }

                current->children[j] = trieCreateByData(c);
                current = current->children[j];

                added = true;
                break;
            }
            if (t->data == c) { 
                current = t;
                added = true;
                break;
            }
        }
         if (!added) {
            current->children[end] = trieCreateByData(c);
            current = current->children[end];
        }
    }
}

// Check whether word has been inserted into obj
bool trieSearch(Trie* obj, char * word) {
    Trie* current = obj;

    for (int i = 0; i <= strlen(word); i++) {
        char c;
        bool found = false;

        if (i == strlen(word)) c = '0';
        else c = word[i];

        for (int j = 0; j < CHILDREN_SIZE; j++) {
            Trie* t = current->children[j];
            if (t == NULL || t->data > c) return false;
            if (t->data == c) { 
                current = t;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// Check whether a string starting with prefix exists in obj
bool trieStartsWith(Trie* obj, char * prefix) {
    Trie* current = obj;

    for (int i = 0; i < strlen(prefix); i++) {
        char c;
        bool found = false;

        c = prefix[i];

        for (int j = 0; j < CHILDREN_SIZE; j++) {
            Trie* t = current->children[j];
            if (t == NULL || t-> data > c) return false;
            if (t->data == c) { 
                current = t;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// Recursively free root and all its children
void trieFree(Trie* obj) {
    for (int i = 0; i < CHILDREN_SIZE; i++) {
        if (obj -> children[i]) 
            trieFree(obj->children[i]);
    }
    free(obj);
}

// Testing method for trieSearch()
void testSearch(Trie* obj, char* str) {
    if (trieSearch(obj, str)) 
        printf("\"%s\" was inserted into the trie\n", str);
    else 
        printf("\"%s\" was NOT inserted into the trie\n", str);
}
// Testing method for trieStartsWith()
void testStartsWith(Trie* obj, char* str) {
    if (trieStartsWith(obj, str)) 
        printf("A string that starts with \"%s\" exists in the trie\n", str);
    else 
        printf("A string that starts with \"%s\" does NOT exist in the trie\n", str);
}

int main() {
    // Initialize trie
    Trie* trie = trieCreate();
    // Test methods
    trieInsert(trie, "hello world");

    testSearch(trie, "hello world");
    testSearch(trie, "sopwithcamel110");

    testStartsWith(trie, "hello");
    testStartsWith(trie, "world");

    // Free trie space
    trieFree(trie);

    return 0;
}