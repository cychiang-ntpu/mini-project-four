#include <stdio.h>
#include <stdlib.h>

typedef struct _codeword {
    char symbol;
    int count;
    float probability;
    char bits[32];
    float self_information;
} codeword;

typedef struct _codebook {
    codeword words[256];
    size_t size;
} codebook;

typedef struct _huffman_node {
    char symbol;
    float probability;
    struct _huffman_node *left;
    struct _huffman_node *right;
} huffman_node;

typedef struct _huffman_tree {
    huffman_node *root;
} huffman_tree;

void print_codebook(codebook *cb) {
    printf("\n========== Codebook Contents ==========\n");
    printf("%-8s %-8s %-12s %-10s %-18s\n", 
           "Symbol", "Count", "Probability", "Bits", "Self-Information");
    printf("-----------------------------------------------------------\n");
    
    for (size_t i = 0; i < cb->size; i++) {
        char symbol_display[10];
        if (cb->words[i].symbol == ' ') {
            sprintf(symbol_display, "<space>");
        } else if (cb->words[i].symbol == '\n') {
            sprintf(symbol_display, "<LF>");
        } else if (cb->words[i].symbol == '\r') {
            sprintf(symbol_display, "<CR>");
        } else {
            sprintf(symbol_display, "%c", cb->words[i].symbol);
        }
        
        printf("%-8s %-8d %-12.6f %-10s %-18.6f\n",
               symbol_display,
               cb->words[i].count,
               cb->words[i].probability,
               cb->words[i].bits,
               cb->words[i].self_information);
    }
    printf("========================================\n\n");
}

int build_huffman_tree(huffman_tree *tree, codebook *cb) {
    // Implementation of Huffman tree building (not shown here)
    return 0;
}

int main() {
    codebook cb;
    huffman_tree ht;

    // read codebook data (for demonstration, hardcoded here)
    cb.size = 20;
    cb.words[0] = (codeword){'?', 1, 0.021277000000000, "000000", 5.554561440732264};
    cb.words[1] = (codeword){'\n', 1, 0.021277000000000, "000001", 5.554561440732264};
    cb.words[2] = (codeword){'\r', 1, 0.021277000000000, "000010", 5.554561440732264};
    cb.words[3] = (codeword){'a', 1, 0.021277000000000, "000011", 5.554561440732264};
    cb.words[4] = (codeword){'D', 1, 0.021277000000000, "000100", 5.554561440732264};
    cb.words[5] = (codeword){'d', 1, 0.021277000000000, "000101", 5.554561440732264};
    cb.words[6] = (codeword){'E', 1, 0.021277000000000, "000110", 5.554561440732264};
    cb.words[7] = (codeword){'s', 1, 0.021277000000000, "000111", 5.554561440732264};
    cb.words[8] = (codeword){'c', 2, 0.042553000000000, "1101", 4.554595343819929};
    cb.words[9] = (codeword){'m', 2, 0.042553000000000, "01001", 4.554595343819929};
    cb.words[10] = (codeword){'y', 2, 0.042553000000000, "01000", 4.554595343819929};
    cb.words[11] = (codeword){'g', 3, 0.063830000000000, "1100", 3.969621541981026};
    cb.words[12] = (codeword){'r', 3, 0.063830000000000, "0111", 3.969621541981026};
    cb.words[13] = (codeword){'t', 3, 0.063830000000000, "0110", 3.969621541981026};
    cb.words[14] = (codeword){'u', 3, 0.063830000000000, "0101", 3.969621541981026};
    cb.words[15] = (codeword){'e', 4, 0.085106000000000, "111", 3.554595343819928};
    cb.words[16] = (codeword){'i', 4, 0.085106000000000, "0011", 3.554595343819928};
    cb.words[17] = (codeword){'o', 4, 0.085106000000000, "0010", 3.554595343819928};
    cb.words[18] = (codeword){' ', 5, 0.106383000000000, "100", 3.232660468251296};
    cb.words[19] = (codeword){'n', 5, 0.106383000000000, "101", 3.232660468251296};

    // Display the codebook
    print_codebook(&cb);

    // conduct Huffman encoding on input data (not implemented here)
    build_huffman_tree(&ht, &cb);

    return 0;
}