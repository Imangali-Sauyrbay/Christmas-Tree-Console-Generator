#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

#include "xmas_tree.h"

const int COLORS[] = {30, 31, 32, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};
const int COLORS_COUNT = 15;
// int COLORS_COUNT = sizeof(COLORS) / sizeof(COLORS[0]);

const float SLEEP_AT_START = 50000.0F;
const float SLEEP_AT_END = 1000.0F;

const wchar_t SNOWFLAKE = L'\u2744';

const short GREEN = 32;
const short LIGHT_GREEN = 92;

int main() {
    srand(time(NULL));
    setlocale(LC_CTYPE, "");

    xmas_tree tree;

    getInput(&tree);
    clearConsole();

    int weightedColorsCount = COLORS_COUNT * tree.greenColorIntensity;
    int weightedColorsArray[weightedColorsCount];
    getWeightedColorsArray(weightedColorsArray, weightedColorsCount);

    printTree(&tree, weightedColorsArray, weightedColorsCount);
    printRoot(&tree);
    
    wprintf(L"\n");

    return 0;
}

void getWeightedColorsArray(int colorsArray[], int len) {
    for (size_t i = 0; i < len; i++)
    {
        if(i < COLORS_COUNT) {
            colorsArray[i] = COLORS[i];
            continue;
        }

        colorsArray[i] = rand_range(0, 1) > 0 ? GREEN : LIGHT_GREEN;
    }
}

void getInput(xmas_tree* tree) {
    wprintf(L"\nGreen Color Intensity (1 - ∞): ");
    wscanf(L" %d", &tree->greenColorIntensity);

    wprintf(L"\nSnowflake Intensity (1 - 100): ");
    wscanf(L" %d", &tree->snowflakeIntensity);

    wprintf(L"\nTree Height: ");
    wscanf(L" %d", &tree->height);

    wprintf(L"\nTree Root Height: ");
    wscanf(L" %d", &tree->rootHeight);

    wprintf(L"\nTree Root Width: ");
    wscanf(L" %d", &tree->rootWidth);

    wprintf(L"\nTree Symbol: ");
    wscanf(L" %c", &tree->treeSymbol);

    wprintf(L"\nLog Symbol: ");
    wscanf(L" %c", &tree->logSymbol);

    wprintf(L"\nOffset left: ");
    wscanf(L" %d", &tree->offsetLeft);

    wchar_t answer; 
    wprintf(L"\nShould edges be straight? (y/N): ");
    getwc(stdin);
    wscanf(L"%c", &answer);

    if(tolower(answer) == 'y') {
        tree->straightEdge = true;
    }

    tree->halfHeight = tree->height / 2;
    tree->halfOfRoot = tree->rootWidth / 2;
    tree->center = tree->halfHeight + tree->offsetLeft;
}

void printBackground(int n, int snowflakeIntensity) {
    for (size_t i = 0; i < n; i++)
    {
        wchar_t toPrint = rand_range(0, 100) > (100 - snowflakeIntensity) ? SNOWFLAKE : L' ';
        wprintf(L"%lc\0", toPrint);
    }
}

float reverseLinearMapping(float n, float minN, float maxN, float outputMin, float outputMax) {
    float m = (outputMax - outputMin) / (maxN - minN);
    float c = outputMin - (m * minN);
    float y = (m * n) + c;
    return y;
}

int rand_range(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void clearConsole() {
    wprintf(L"\033[2J\033[H");
}

void sleepToPrint(float n, float max_n) {
    int usleepValue = (int) reverseLinearMapping(
        n,
        1.0F,
        max_n,
        SLEEP_AT_START,
        SLEEP_AT_END
    );

    usleep(usleepValue);
}

void printTree(xmas_tree* tree, int colorsArray[], int len) {
    for (size_t i = 1; i < tree->height; i++)
    {
        if(tree->straightEdge && !(i&1)) continue;

        printBackground(tree->center - (i / 2), tree->snowflakeIntensity);

        for (size_t j = 0; j < i; j++)
        {
            int color = colorsArray[rand_range(0, len)];

            wprintf(L"\033[%d;1m%c\033[0m", color, tree->treeSymbol);
            fflush(stdout);

            sleepToPrint(i, tree->height);
        }

        printBackground(tree->center - (i / 2), tree->snowflakeIntensity);

        wprintf(L"\n");
    }
}

void printRoot(xmas_tree* tree) {
    if(!(tree->rootWidth&1)) tree->rootWidth++;

    for (size_t i = 0; i < tree->rootHeight; i++)
    {
        printBackground(tree->center - tree->halfOfRoot, tree->snowflakeIntensity);
        
        for (size_t j = 0; j < tree->rootWidth; j++)
        {
            wprintf(L"\033[33;1m%c\033[0m", tree->logSymbol);
            fflush(stdout);
            
            sleepToPrint(i, tree->rootHeight);
        }

        printBackground(tree->center - tree->halfOfRoot, tree->snowflakeIntensity);

        wprintf(L"\n");
    }
}
