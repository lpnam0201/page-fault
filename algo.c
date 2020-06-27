#include <stdbool.h>

bool hasPage(int** result, int column, int pageFrame, int pageToFind) {
    for (int i = 0; i < pageFrame - 1; i++) {
        if (result[i][column] == pageToFind) {
            return true;
        }
    }

    return false;
}

void fifo(int* sequence, int n, int pageFrame, int** result) {
    int currentFrameIndex = 0;

    for (int i = 0; i < n; i++) {
        if (!hasPage(result, i, pageFrame, sequence[i])) {
            

            result[pageFrame][i] = 1;
        }
    }
}

void opt(int* sequence, int n, int pageFrame, int** result) {

}

void lru(int* sequence, int n, int pageFrame, int** result) {

}