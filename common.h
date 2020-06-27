extern int defaultReferencedSequence[];

int inputSequenceType();
int* determineSequence(int sequenceType, int* n);
int inputPageFrame();
int inputAlgorithm();
int** initResult(int pageFrame, int n);
void fifo(int* sequence, int** result);
void opt(int* sequence, int** result);
void lru(int* sequence, int** result);