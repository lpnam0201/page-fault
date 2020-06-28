#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "algo.h"

void main()
{
    int n;
    int sequenceType = inputSequenceType();
    int *sequence = determineSequence(sequenceType, &n);
    int pageFrame = inputPageFrame();
    int algorithm = inputAlgorithm();

    int **result = initResult(pageFrame, n);

    switch (algorithm)
    {
    case 1:
        fifo(sequence, n, pageFrame, result);
        break;
    case 2:
        opt(sequence, n, pageFrame, result);
        break;
    case 3:
        lru(sequence, n, pageFrame, result);
        break;
    default:
        break;
    }

    output(result, pageFrame, n);
}