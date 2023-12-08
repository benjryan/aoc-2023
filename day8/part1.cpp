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
    FILE* fp = fopen("input.txt", "r");
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

    {
        int node_idx = find_node(nodes, node_count, "AAA");
        bool complete = false;
        int step_count = 0;
        while (!complete) {
            for (int i = 0; i < inst_count; ++i) {
                if (strncmp(nodes[node_idx].name, "ZZZ", 3) == 0) {
                    complete = true;
                    break;
                }

                step_count++;
                if (inst[i] == 'L')
                    node_idx = find_node(nodes, node_count, nodes[node_idx].left);
                else if (inst[i] == 'R')
                    node_idx = find_node(nodes, node_count, nodes[node_idx].right);
            }
        }

        printf("answer: %d\n", step_count);
    }
}
