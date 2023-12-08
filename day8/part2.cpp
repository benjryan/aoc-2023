#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    char name[3];
    char left[3];
    char right[3];
};

int find_node(Node* nodes, int node_count, char name[3])
{
    for (int i = 0; i < node_count; ++i) {
        if (strncmp(nodes[i].name, name, 3) == 0)
            return i;
    }

    return -1;
}

int main()
{
    FILE* fp = fopen("../input.txt", "r");
    char line[1024];
    Node nodes[1024];
    int node_count = 0;

    char inst[1024];
    int inst_count = 0;
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        int line_length = strlen(line);
        if (inst_count == 0) {
            inst_count = line_length - 1;
            strncpy(inst, line, inst_count);
            continue;
        }

        if (line_length < 5)
            continue;

        Node node;
        strncpy(node.name, line, 3);
        strncpy(node.left, line + 7, 3);
        strncpy(node.right, line + 12, 3);
        nodes[node_count++] = node;
    }

    size_t numbers[6] = {0};
    int number_count = 0;
    for (int i = 0; i < node_count; ++i) {
        if (nodes[i].name[2] != 'A')
            continue;

        int node_idx = i;
        size_t step_count = 0;
        bool complete = false;
        while (!complete) {
            for (int inst_id = 0; inst_id < inst_count; ++inst_id) {
                if (inst[inst_id] == 'L')
                    node_idx = find_node(nodes, node_count, nodes[node_idx].left);
                else if (inst[inst_id] == 'R')
                    node_idx = find_node(nodes, node_count, nodes[node_idx].right);

                step_count++;
                if (nodes[node_idx].name[2] == 'Z') {
                    complete = true;
                    break;
                }
            }

            if (complete) {
                numbers[number_count++] = step_count;
            }
        }
    }

    // use a prime factorization calculator on the output numbers and
    // multiply the primes together to get the final answer
    for (int i = 0; i < 6; ++i) {
        printf("%llu\n", numbers[i]);
    }
}
