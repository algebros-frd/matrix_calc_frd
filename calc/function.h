#include <stdio.h>
//#include <unitstd.h>
#include <stdlib.h>
#include <string.h>

// matrix[row][col]
typedef struct Matrix {
  int col;
  int row;
  double **data;
} Matrix;

typedef struct Vector {
	int dim;
	double *data;
}Vector; 

//Funciones de solo matrices
Matrix *copy_matrix(const Matrix *matrix1);
void set_elem_matrix(int row, int col, double value, Matrix *matrix);
Matrix *init_matrix_matrix(int row, int col);
void print_matrix(const Matrix *matrix);
Matrix *populate_matrix(int row, int col,const double *data);
void free_matrix(Matrix *matrix);
Matrix *add_matrix(Matrix *matrix1, Matrix *matrix2);
Matrix *scalar_multiplication_matrix(double val, Matrix *matrix);
Matrix *transpose_matrix(Matrix *matrix);
Matrix *matrix_multiplication(const Matrix *matrix1, const Matrix *matrix2);
Matrix *gaussian_elimination_matrix(const Matrix *matrix);
void interchange_row_matrix(Matrix *matrix, int row1, int row2);
double determinant_matrix(const Matrix *matrix);
Matrix *concatenate_matrix_matrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *populate_matrix_keyboard(int row, int col);
void mitosis_matrix(const Matrix *matrix, Matrix **result1, Matrix **result2, int i);
double cofactor_matrix_elem(int row, int col, Matrix *matrix);
Matrix *identity_matrix(int dim);
Matrix *inverse_matrix(const Matrix *matrix);
Matrix *gauss_jordan_elimination_matrix(const Matrix *matrix);
Matrix *cofactor_matrix(Matrix *matrix);
Matrix *adjoint_matrix(Matrix *matrix);
Matrix *fast_inverse_matrix(Matrix *inverse);
int range_matrix(const Matrix *matrix);


//funciones de solo vectores
Vector *init_vector(int dim);
Vector *copy_vector(const Vector *vector1);
void print_vector(const Vector *vector);
Vector *vector_addition(const Vector *vector1, const Vector *vector2);
double scalar_product_vector(const Vector *vector1, const Vector *vector2);
Vector *populate_vector(int dim, const double *data);
Vector *cross_product_3_dim_vector(const Vector *vector1, const Vector *vector2);


//funciones de matrices y vectores
Vector *matrix_vector_multiplication(const Matrix *matrix, const Vector *vector);
