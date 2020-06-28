#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int defaultReferencedSequence[] = {1, 8, 5, 2, 1, 3, 2, 5, 0, 0, 7};

int *determineSequence(int sequenceType, int *n)
{
    int *sequence;
    if (sequenceType == 1)
    {
        sequence = defaultReferencedSequence;
        *n = sizeof(defaultReferencedSequence) / sizeof(defaultReferencedSequence[0]);
    }

    if (sequenceType == 2)
    {
        int nInp = 0;
        printf("\nSequence count n = ");
        scanf("%d", &nInp);
        *n = nInp;

        printf("\nInput sequence = ");
        sequence = malloc(sizeof(int) * nInp);
        for (int i = 0; i < nInp; i++)
        {
            scanf("%d", &sequence[i]);
        }
    }

    return sequence;
}

int inputSequenceType()
{
    int sequenceType = 0;
    printf("---Page Replacement algorithm---");
    printf("\n1. Default referenced sequence");
    printf("\n2. Manual input sequence");
    printf("\nSequence type = ");
    scanf("%d", &sequenceType);

    return sequenceType;
}

int inputPageFrame()
{
    int pageFrame = 0;
    printf("\nInput page frames = ");
    scanf("%d", &pageFrame);

    return pageFrame;
}

int inputAlgorithm()
{
    int algorithm = 0;
    printf("\n1. FIFO");
    printf("\n2. OPT");
    printf("\n3. LRU");
    printf("\nInput algorithm = ");
    scanf("%d", &algorithm);

    return algorithm;
}

int **initResult(int pageFrame, int n)
{
    int **result = malloc((pageFrame + 1) * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        result[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < pageFrame; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i][j] = -1;
        }
    }

    // Asterisk row
    for (int i = 0; i < n; i++)
    {
        result[pageFrame][i] = 0;
    }

    return result;
}

void output(int **result, int pageFrame, int n, int *sequence)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", sequence[i]);
    }
    printf("\n\n");

    for (int i = 0; i < pageFrame; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (result[i][j] == -1) 
            {
                printf("_ ");
            }
            else
            {
                printf("%d ", result[i][j]);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        if (result[pageFrame][i] == 1) 
        {
            printf("* ");
        }
        else 
        {
            printf("  ");
        }
    }
}