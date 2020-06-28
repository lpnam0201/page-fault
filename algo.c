#include <stdbool.h>
#include <limits.h>

bool hasPage(int **result, int column, int pageFrame, int pageToFind)
{
    for (int i = 0; i < pageFrame; i++)
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

void copyPreviousFrameState(int **result, int currentSequenceIndex, int pageFrame) {
    if (currentSequenceIndex == 0) 
    {
        return;
    }

    for (int i = 0; i < pageFrame; i++) 
    {
        result[i][currentSequenceIndex] = result[i][currentSequenceIndex - 1];
    }
}

void fifo(int *sequence, int n, int pageFrame, int **result)
{
    int frameIndexToSwap = 0;

    for (int i = 0; i < n; i++)
    {
        copyPreviousFrameState(result, i, pageFrame);
        if (!hasPage(result, i, pageFrame, sequence[i]))
        {
            int emptyFrameIndex = findEmptyFrame(result, i, pageFrame);
            if (emptyFrameIndex != -1)
            {
                result[emptyFrameIndex][i] = sequence[i];
            }
            else
            {
                result[frameIndexToSwap][i] = sequence[i];

                frameIndexToSwap += 1;
                if (frameIndexToSwap == pageFrame)
                {
                    frameIndexToSwap = 0;
                }
            }
            
            result[pageFrame][i] = 1;
        }
    }
}

int findInRangeForward(int value, int from, int to, int *sequence)
{
    for (int i = from; i <= to; i++)
    {
        if (sequence[i] == value)
        {
            return i;
        }
    }

    return INT_MAX;
}

int findInRangeBackward(int value, int from, int to, int *sequence)
{
    for (int i = from; i >= to; i--)
    {
        if (sequence[i] == value)
        {
            return i;
        }
    }

    return INT_MIN;
}

int findFrameIndexToSwapInFuture(int *sequence, int currentColumn, int n, int **result, int pageFrame)
{
    int frameIndex = 0;
    int pageUsedIndex = INT_MIN;
    for (int i = 0; i < pageFrame; i++) 
    {
        int pageToCheck = result[i][currentColumn];
        int usedAt = findInRangeForward(pageToCheck, currentColumn, n - 1, sequence);
        if (usedAt > pageUsedIndex)
        {
            pageUsedIndex = usedAt;
            frameIndex = i;
        }
    }

    return frameIndex;
}

int findFrameIndexToSwapInPast(int *sequence, int currentColumn, int n, int **result, int pageFrame)
{
    int frameIndex = 0;
    int pageUsedIndex = INT_MAX;
    for (int i = 0; i < pageFrame; i++) 
    {
        int pageToCheck = result[i][currentColumn];
        int usedAt = findInRangeBackward(pageToCheck, currentColumn - 1, 0, sequence);
        if (usedAt < pageUsedIndex)
        {
            pageUsedIndex = usedAt;
            frameIndex = i;
        }
    }

    return frameIndex;
}

void opt(int *sequence, int n, int pageFrame, int **result)
{
    for (int i = 0; i < n; i++)
    {
        copyPreviousFrameState(result, i, pageFrame);
        if (!hasPage(result, i, pageFrame, sequence[i]))
        {
            int emptyFrameIndex = findEmptyFrame(result, i, pageFrame);
            if (emptyFrameIndex != -1)
            {
                result[emptyFrameIndex][i] = sequence[i];
            }
            else
            {
                int frameIndexToSwap = findFrameIndexToSwapInFuture(sequence, i, n, result, pageFrame);
                result[frameIndexToSwap][i] = sequence[i];
            }

            result[pageFrame][i] = 1;
        }
    }
}

void lru(int *sequence, int n, int pageFrame, int **result)
{
    for (int i = 0; i < n; i++)
    {
        copyPreviousFrameState(result, i, pageFrame);
        if (!hasPage(result, i, pageFrame, sequence[i]))
        {
            int emptyFrameIndex = findEmptyFrame(result, i, pageFrame);
            if (emptyFrameIndex != -1)
            {
                result[emptyFrameIndex][i] = sequence[i];
            }
            else
            {
                int frameIndexToSwap = findFrameIndexToSwapInPast(sequence, i, n, result, pageFrame);
                result[frameIndexToSwap][i] = sequence[i];
            }

            result[pageFrame][i] = 1;
        }
    }
}