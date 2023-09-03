#ifndef XMAS_TREE
#define XMAS_TREE

int rand_range(int, int);
float reverseLinearMapping(float n, float minN, float maxN, float outputMin, float outputMax);
void clearConsole();
void sleepToPrint(float n, float max_n);

#include <wchar.h>
#include <stdbool.h>
void printBackground(int n, int snowflakeIntensity);

typedef struct
{
    int height;
    int rootHeight;
    int rootWidth;
    char treeSymbol;
    char logSymbol;
    int offsetLeft;
    int halfHeight;
    int halfOfRoot;
    int center;
    int greenColorIntensity;
    bool straightEdge;
    int snowflakeIntensity;
} xmas_tree;

void getInput(xmas_tree*);
void getWeightedColorsArray(int[], int);
void printTree(xmas_tree* tree, int colorsArray[], int len);
void printRoot(xmas_tree* tree);

#endif