#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	struct Trie *children[26];
    int occurrences;  // Number of occurrences of the word
};

struct Trie *createNode(void) {
    struct Trie *newNode = malloc(sizeof(struct Trie));
    if (newNode) {
        int i;
        newNode->occurrences = 0;
        for (i = 0; i < 26; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{int level;
    int length = strlen(word);
    int index;
    
    struct Trie *pCrawl = pTrie;
    
    for (level = 0; level < length; level++) {
        index = word[level] - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode();
        }
        pCrawl = pCrawl->children[index];
    }
    
    // Increment the occurrences count at the end of the word
    pCrawl->occurrences++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{int level;
    int length = strlen(word);
    int index;
    
    struct Trie *pCrawl = pTrie;
    
    for (level = 0; level < length; level++) {
        index = word[level] - 'a';
        
        if (!pCrawl->children[index]) {
            return 0; // The word is not in the trie
        }
        
        pCrawl = pCrawl->children[index];
    }
    
    // The word exists in the trie, return the occurrences count
    return (pCrawl != NULL && pCrawl->occurrences) ? pCrawl->occurrences : 0;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{if (pTrie) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i]) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL; // Return NULL to indicate the trie has been deallocated
}

// Initializes a trie structure
struct Trie *createTrie()
{return createNode(); // A trie is initialized by creating a new node
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        exit(EXIT_FAILURE);
    }

    char buffer[256]; // Buffer to hold each word
    int wordCount = 0;

    while (fgets(buffer, sizeof(buffer), file) && wordCount < 256) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        pInWords[wordCount++] = strdup(buffer); // Duplicate the string
    }

    fclose(file);
    return wordCount;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
    for (int i = 0; i < numWords; ++i) {
        free(inWords[i]);
    }

    return 0;
}
