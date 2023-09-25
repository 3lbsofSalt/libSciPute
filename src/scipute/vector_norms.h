#ifndef LIB_SCI_PUTE_VECTOR_NORMS
#define LIB_SCI_PUTE_VECTOR_NORMS

float two_norm(float vector[], int v_size);
float one_norm(float vector[], int v_size);
float infty_norm(float vector[], int v_size);

float one_norm_distance(float vector1[], float vector2[], int sizes);
float two_norm_distance(float vector1[], float vector2[], int sizes);
float infty_norm_distance(float vector1[], float vector2[], int sizes);

#endif
