#ifndef LIB_SCI_PUTE_VECTORS
#define LIB_SCI_PUTE_VECTORS

void copyVectors(double* from, double* to, int size);
double dotProduct(double* vec1, double* vec2, int size);
void normalize(double* vec, int size);
double magnitude(double* vec, int size);
void printVector(double* vec, int size, char* msg);

#endif
