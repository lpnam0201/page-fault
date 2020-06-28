#include <stdbool.h>

bool hasPage(int **result, int column, int pageFrame, int pageToFind)
{
    for (int i = 0; i < pageFrame - 1; i++)
    {
        if (result[i][column] == pageToFind)
        {
            return true;
        }
    }

    return false;
}

int findEmptyFrame(int **result, int column, int pageFrame)
{
    for (int i = 0; i < pageFrame; i++)
    {
        if (result[i][column] == -1)
        {
            return i;
        }
    }

    return -1;
}

void fifo(int *sequence, int n, int pageFrame, int **result)
{
    int currentFrameIndex = 0;

    for (int i = 0; i < n; i++)
    {
        if (!hasPage(result, i, pageFrame, sequence[i]))
        {
            int emptyFrameIndex = findEmptyFrame(result, i, pageFrame);
            if (emptyFrameIndex != -1)
            {
                result[emptyFrameIndex][i] = sequence[i];
            }
            else
            {
                result[currentFrameIndex][i] = sequence[i];

                currentFrameIndex += 1;
                if (currentFrameIndex == pageFrame)
                {
                    currentFrameIndex = 0;
                }

                result[pageFrame][i] = 1;
            }
        }
    }
}

void opt(int *sequence, int n, int pageFrame, int **result)
{
}

void lru(int *sequence, int n, int pageFrame, int **result)
{
}