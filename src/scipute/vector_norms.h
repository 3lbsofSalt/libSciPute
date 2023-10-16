#ifndef LIB_SCI_PUTE_VECTOR_NORMS
#define LIB_SCI_PUTE_VECTOR_NORMS

float *subtract_vector(float vector1[], float vector2[], int sizes);

float l2_norm(float vector[], int v_size);
float l1_norm(float vector[], int v_size);
float linf_norm(float vector[], int v_size);

float l1_distance(float vector1[], float vector2[], int sizes);
float l2_distance(float vector1[], float vector2[], int sizes);
float linf_distance(float vector1[], float vector2[], int sizes);

#endif
