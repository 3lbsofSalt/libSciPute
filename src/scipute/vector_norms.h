#ifndef LIB_SCI_PUTE_VECTOR_NORMS
#define LIB_SCI_PUTE_VECTOR_NORMS

double *subtract_vector(double vector1[], double vector2[], int sizes);

double l2_norm(double vector[], int v_size);
double l1_norm(double vector[], int v_size);
double linf_norm(double vector[], int v_size);

double l1_distance(double vector1[], double vector2[], int sizes);
double l2_distance(double vector1[], double vector2[], int sizes);
double linf_distance(double vector1[], double vector2[], int sizes);

#endif
