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

int sort_queue_by_probability(huffman_node **queue, size_t size) {
    // bubble sort implementation
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (queue[j]->probability > queue[j + 1]->probability) {
                huffman_node *temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
    return 1;
}

int print_huffman_tree(huffman_node *node, int depth) {
    // depth-first traversal to print the tree structure
    if (node == NULL) {
        return 0;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    if (node->left == NULL && node->right == NULL) {
        printf("Leaf: '%c' (%.6f)\n", node->symbol, node->probability);
    } else {
        printf("Node: (%.6f)\n", node->probability);
    }
    print_huffman_tree(node->left, depth + 1);
    print_huffman_tree(node->right, depth + 1);
    return 0;
}

int trace_huffman_tree_and_generate_codewords(huffman_node *node, char *code, codebook *cb) {
    // Implementation of tracing Huffman tree to generate codewords (not shown here)
    if (node == NULL) {
        return 0;
    }
    // If leaf node, add codeword to codebook
    if (node->left == NULL && node->right == NULL) {
        for (size_t i = 0; i < cb->size; i++) {
            if (cb->words[i].symbol == node->symbol) {
                sprintf(cb->words[i].bits, "%s", code);
                break;
            }
        }
    } else {
        // Traverse left
        char left_code[32];
        sprintf(left_code, "%s0", code);
        trace_huffman_tree_and_generate_codewords(node->left, left_code, cb);
        
        // Traverse right
        char right_code[32];
        sprintf(right_code, "%s1", code);
        trace_huffman_tree_and_generate_codewords(node->right, right_code, cb);
    }
    return 0;
}


int generate_codewords_from_huffman_tree(huffman_tree *tree, codebook *cb) {
    // Implementation of codeword generation from Huffman tree (not shown here)
    // trace the tree to generate codewords and fill the codebook
    trace_huffman_tree_and_generate_codewords(tree->root, "", cb);
    return 0;
}
int build_huffman_tree(huffman_tree *tree, codebook *cb) {
    // copy codebook data to huffman tree nodes
    huffman_node **nodes = (huffman_node **)malloc(cb->size * sizeof(huffman_node *));
    for(int i=0;i<cb->size;i++) {
        nodes[i] = (huffman_node *)malloc(sizeof(huffman_node));
        nodes[i]->symbol = cb->words[i].symbol;
        nodes[i]->probability = cb->words[i].probability;
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }

    // initialization of Huffman tree nodes from codebook
    // initialize priority queue
    huffman_node **queue = (huffman_node **)malloc(cb->size * sizeof(huffman_node *));
    size_t queue_size = cb->size;
    for (size_t i = 0; i < cb->size; i++) {
        queue[i] = nodes[i];
    }

    // sort queue by probability
    sort_queue_by_probability(queue, queue_size);

    // generate father nodes until only one node remains in the queue
    while (queue_size > 1) {
        // take out two nodes with smallest probabilities
        huffman_node *left = queue[0];
        huffman_node *right = queue[1];

        // create new father node
        huffman_node *father = (huffman_node *)malloc(sizeof(huffman_node));
        father->symbol = '\0'; // internal node
        father->probability = left->probability + right->probability;
        father->left = left;
        father->right = right;

        // remove the two nodes from the queue
        for (size_t i = 2; i < queue_size; i++) {
            queue[i - 2] = queue[i];
        }
        queue_size -= 2;

        // add the new father node to the queue
        queue[queue_size] = father;
        queue_size++;

        // sort the queue again
        sort_queue_by_probability(queue, queue_size);
    }

    // the remaining node is the root of the Huffman tree
    tree->root = queue[0];
    //tree->size = cb->size;
    free(queue);
    free(nodes);

    // print the Huffman tree for debugging
    print_huffman_tree(tree->root, 0);

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

    // generate codewords from Huffman tree (not implemented here)
    generate_codewords_from_huffman_tree(&ht, &cb);

    print_codebook(&cb);

    return 0;
}