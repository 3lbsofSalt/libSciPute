#ifndef LIB_SCI_PUTE_MATRIX
#define LIB_SCI_PUTE_MATRIX

struct Matrix {
  int rows;
  int cols;
  double* data;
};


struct Matrix* create_matrix(int n_rows, int n_cols);
double getMatrixData(struct Matrix* matrix, int i, int j);
void setMatrixData(struct Matrix* matrix, int i, int j, double val);
void setMatrixDataFromArray(struct Matrix *matrix, double vals[]);
void deleteMatrix(struct Matrix* matrix);
void printMatrix(struct Matrix* m);

double* multiplyMatrixVector(struct Matrix* m, double vec[]);
void gaussianElimination(struct Matrix* A, double b[]);
double* upperTriBackSub(struct Matrix* U, double c[]);

#endif
