#include "function.h"
#define PRUEBA printf("LLEGUE a linea %d\n", __LINE__);
// matrix[row][col]
//vector[col]  --> no distingue entre vector fila o columna.

//primero van las funciones de solo matrices, despues la de solo vectores, por ultimo las que contiene ambos (ejemplo, sistema de ecuaciones). Mantener el orden!!

//Funciones de solo matrices
Matrix *init_matrix(int row, int col) {
	Matrix *matrix;
	matrix = calloc(1, sizeof(Matrix));
	matrix->col = col;
	matrix->row = row;
	matrix->data = calloc(matrix->row, sizeof(double *));
	for (int i = 0; i < row; i++) {
		matrix->data[i] = calloc(col, sizeof(double));
	}
	return matrix;
}

void print_matrix(const Matrix *matrix) {
	if (matrix == NULL) {
		printf("ERROR print_matrix: sos un wachin no se puede imprimir\n");
	} else {
		for (int i = 0; i < matrix->row; i++) {
			for (int j = 0; j < matrix->col; j++)
				printf("%4.6f ", matrix->data[i][j]);
			printf("\n");
		}
	}
}

void set_elem_matrix(int row, int col, double value, Matrix *matrix) {
	matrix->data[row - 1][col - 1] = value;
	return;
}

Matrix *copy_matrix(const Matrix *matrix1) {
	if (matrix1 == NULL){
		printf("ERROR copy_matrix: como queres copiar algo que no existe\n");
		return NULL;
	}
	Matrix *matrix2;
	matrix2 = init_matrix(matrix1->row, matrix1->col);
	for (int i = 0; i < matrix1->row; i++) {
		for (int j = 0; j < matrix1->col; j++)
			matrix2->data[i][j] = matrix1->data[i][j];
	}
	return matrix2;
}

//Para hacer la funcion mas versatil, la funcion ya recibe el array de numeros, y es trabajo de otra funcion como consigue el array.
//Se asume que se recibe la cantidad adecuada de valores. Si se recibe mas, los ulimos los desechará, y si recibe menos, completará con cero.
Matrix *populate_matrix(int row, int col, const double *data) {
	double elem;
	Matrix *matrix1;
	matrix1 = init_matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			elem = *(data ++);	
			matrix1->data[i][j] = elem;
		}
	}
	return matrix1;
}

//para directamente llenar una desde el teclado.
/* es una funcion que deben hacer los putos del frontend
Matrix *populate_matrix_keyboard(int row, int col){
	Matrix *matrix; 
	double *data;
	double *aux;
	data = calloc(col*row, sizeof(double));
	aux = data;
	printf("Mete los valores wachin\n");
	for (int i = 0; i< row; i++){
		for (int j=0; j<col; j++){
			printf("Posicion %d %d: ", i + 1, j + 1);
			scanf("%lf", aux++);
		}		
	}
	matrix = populate_matrix(row, col, data);
	free((void*)data);
	return matrix;

}
*/
void free_matrix(Matrix *matrix) {
	if (matrix != NULL) {
		if (matrix->data != NULL) {
			for (int i = 0; i < matrix->row; i++) {
				if (matrix->data[i])
					free((void *)matrix->data[i]);
			}
			free((void *)matrix->data);
		}
		free((void *)matrix);
	}
}

Matrix *add_matrix(Matrix *matrix1, Matrix *matrix2) {
	Matrix *matrix3;
	matrix3 = init_matrix(matrix1->row, matrix1->col);
	if (matrix1->row == matrix2->col && matrix1->col == matrix2->col) {
		for (int i = 0; i < matrix1->row; i++) {
			for (int j = 0; j < matrix1->col; j++) {
				matrix3->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
			}
		}
		return matrix3;
	} else {
		printf("ERROR add_matrix: sos un wachin como vas a sumar matrices de diferente dimension. "
				"kabum\n");
		return NULL;
	}
}

Matrix *scalar_multiplication_matrix(double val, Matrix *matrix1) {
	if (val == 0){
		return init_matrix(matrix1->row, matrix1->col); //si es cero directamente devuelvo la nula
	}
	Matrix *matrix2 = init_matrix(matrix1->row, matrix1->col);
	for (int i = 0; i < matrix1->row; i++) {
		for (int j = 0; j < matrix1->col; j++) {
			if (matrix2->data[i][j] == 0) continue; //si es cero no multiplica para evitar el -0
			matrix2->data[i][j] = (matrix1->data[i][j]) * val;
		}
	}
	return matrix2;
}

Matrix *transpose_matrix(Matrix *matrix) {
	Matrix *transposed;
	transposed = init_matrix(matrix->col, matrix->row);
	for (int i = 0; i < matrix->row; i++) {
		for (int j = 0; j < matrix->col; j++)
			transposed->data[j][i] = matrix->data[i][j];
	}
	return transposed;
}

Matrix *matrix_multiplication(const Matrix *matrix1, const Matrix *matrix2) {
	if (matrix1 == NULL ||  matrix2 == NULL){
		printf("ERROR matrix multiplication: quiere multiplicar una matriz que no existe\n");
		return NULL;
	}
	Matrix *result = init_matrix(matrix1->row, matrix2->col);
	if (matrix1->row != matrix2->col) {
		printf("ERROR matrix_multiplication: fijate las dimensiones de las matrices wachin\n");
		return NULL;
	} else {
		for (int i = 0; i < matrix1->row; i++) {
			for (int j = 0; j < matrix2->col; j++) {
				for (int k = 0; k < matrix1->col; k++) {
					if (!(matrix1->data[i][k] || matrix2->data[k][j])) continue; //si alguno es cero no se hace la multiplicacion para evitar el doble cero si no entedes la sintaxis es pq sos el bot de filimilki.
					result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
				}
			}
		}
		return result;
	}
}



Matrix *gaussian_elimination_matrix(const Matrix *matrix){
	/*
	 *La idea de esta funcion es la siguiente. 
	 Primero se selecciona un pivot y a partir de ahí tenemos 2 casos:
	 1. si el pivot no es cero simplemente se generan ceros debajo
	 2. Si no es empiezo a buscar un pivot que no sea cero.
	 Si encuentr: Intercambio las filas
	 Si no, muev el pivot a la derecha y repito.
	 */

	Matrix *result = copy_matrix(matrix);
	int pivot_pos[2] = {0,0}; 
	double pivot, aux, factor; 

	while((pivot_pos[0] < matrix->row && pivot_pos[1] < matrix->col))
	{
		pivot = result->data[pivot_pos[0]][pivot_pos[1]];
		if (pivot) { //entra solamente si el pivot no es cero
			for (int i = pivot_pos[0] + 1; i < matrix->row; i ++){

				aux = result->data[i][pivot_pos[1]];//valor a convertir en cero
				if (aux == 0) continue;
				factor = aux / pivot; 
				for (int j = pivot_pos[1]; j < matrix->col; j ++){
					if (! result->data[pivot_pos[0]][j]) continue;
					result->data[i][j] -= (result->data[pivot_pos[0]][j] * factor);

				}
			}
			pivot_pos[0] ++;
			pivot_pos[1] ++;

		}
		else{
			aux = 0;
			for (int i = pivot_pos[0] + 1; i < matrix->row; i ++){
				aux = result->data[i][pivot_pos[1]];//posible nuevo pivot
				if(aux != 0){
					interchange_row_matrix(result, pivot_pos[0], i);
					break;	
				} 
			}
			if (aux == 0) pivot_pos[1] ++;
		}
	}
	return result;
}

void interchange_row_matrix(Matrix *matrix, int row1, int row2) {
	double *aux = calloc (matrix->col, sizeof(double));
	memcpy(aux,  matrix->data[row1], sizeof(double) * matrix->col);
	for(int i = 0; i < matrix->col; i++){
		if (aux[i]) aux[i]*=-1;
	}
	memcpy(matrix->data[row1], matrix->data[row2], sizeof(double)* matrix->col);
	memcpy(matrix->data[row2], aux, sizeof(double) *matrix->col);
	free(aux);
}
// void lu_decomposition(const Matrix *matrix){
//   Matrix *l = init_matrix(matrix->row, matrix->col);
//   Matrix *u = copy_matrix(matrix);
// }
double determinant_matrix(const Matrix *matrix) {
	if (matrix->row - matrix->col) {
		printf("ERROR determinant: Estas queriedo hacer un determinante de una no cuadrada wachin\n"); //Ayuda para debuggear nomas
		return 0;
	}
	Matrix * triangular = gaussian_elimination_matrix(matrix);
	double result = 1, value;

	for (int i = 0; i < matrix->row; i++){
		value = triangular->data[i][i];
		if (!value) return 0;
		result *= value;
	}
	free_matrix(triangular);
	return result;

}
Matrix *concatenate_matrix(const Matrix *matrix1, const Matrix *matrix2){
	if (matrix1->row - matrix2->row) {
		printf("ERROR CONCATENATE: No coinciden las filas\n");
	}
	Matrix *result = init_matrix(matrix1->row, 2*matrix1->col);
	for (int i = 0; i < matrix1->row; i++) {
		for (int j = 0; j < matrix1->col; j++){
			result->data[i][j] = matrix1->data[i][j];
			if (j < matrix2->col){
			       	result->data[i][j+matrix1->col] = matrix2->data[i][j];
			}
		}	
		if (matrix1->col < matrix2->col) {
				for (int j = (matrix1->col) *2; j < matrix1->col + matrix2->col; j++) result->data[i][j] = matrix2->data[i][j - matrix1->col]; 
			}
	}
			
	return result;
	
       	
}
//recibe punteros a la funciones 
//recibe las dos matrices donde va a guardar las matrices separadas, y la cantidad de columnas de la primera.
void mitosis_matrix(const Matrix *matrix, Matrix **result1, Matrix **result2, int col1)
{
	if (col1 >= matrix->col) {
		printf("ERROR MITOSIS: columnas de la segunda matriz, menor o igual a 0\n");
		return;
	}
	int col2 = matrix->col - col1; 
	double *data1,  *data2, *aux1, *aux2;
	
	data1 = calloc(matrix->row * col1, sizeof(double));
	data2 = calloc(matrix->row * col2, sizeof(double));
	aux1 = data1;
	aux2 = data2;

	//llene los vecctores de data
	for(int i = 0; i < matrix->row; i++){
		for (int j = 0; j < col1; j++){
			*(aux1++) = matrix->data[i][j]; 
		}
		for (int j = col1; j < matrix->col; j++){
			*(aux2++) = matrix->data[i][j];
		}
	}
	*result1 = populate_matrix(matrix->row, col1, data1);
	*result2 = populate_matrix(matrix->row, col2, data2);
	free((void*) data1);
	free((void*) data2);
	return;
}

Matrix *identity_matrix(int dim){
	Matrix *matrix;
	double *data;
	data = calloc(dim * dim, sizeof(double));
	
	for (int i = 0; i < dim; i ++){
		data[i * (dim + 1)] = 1;
	}	
	
	matrix = populate_matrix(dim, dim, data);
	free((void *) data);
	return matrix;
}

Matrix *gauss_jordan_elimination_matrix(const Matrix *matrix){
	Matrix  *result;
	int dim, pivot_col, pivot_row;
	double pivot, factor, aux;
	if (matrix->row > matrix->col) dim = matrix->col;
	else dim = matrix->row;
	result = gaussian_elimination_matrix(matrix);
	
	pivot_col = dim - 1; pivot_row = dim - 1;

	while(pivot_row && pivot_col){
		pivot = result->data[pivot_row][pivot_col];
		if (pivot){//entra solamente si el pivot no es cero
			for(int i = 0; i<pivot_row; i++){
				aux = result->data[i][pivot_col];
				if (aux == 0) continue;
				factor = aux / pivot;
				for(int j = pivot_col; j < result->col; j++){
					if(! result->data[i][j]) //evitar el menos cero
					result->data[i][j] -= (result->data[pivot_row][j] * factor);
				}
			}	
		pivot_col --; pivot_row --;
		}
		else {
			if((pivot_col + 1) < result->col) pivot_col ++;
			else pivot_row --;
		}
	}
	return result;
	
	
	
}

Matrix *inverse_matrix(const Matrix *matrix){
	if (!determinant_matrix(matrix)){
		printf("ERROR Inverse: matriz no tiene inversa\n");
		return NULL;
	}
	if (matrix->col - matrix->row){
		printf("Error Inverse: quiere calcular inversa de una no cuadrada\n");
		return NULL;
	}

	int dim = matrix->row;
	double pivot;
	Matrix *identity, *concatenate,*aux, *inverse, *concatenate_aux;
	
	identity = identity_matrix(dim);
	concatenate = concatenate_matrix(matrix, identity);
	concatenate_aux = gauss_jordan_elimination_matrix(concatenate);
	mitosis_matrix(concatenate_aux, &aux, &inverse, dim);

	for (int i = 0; i< dim; i++){
		pivot = aux->data[i][i];
		for (int j = 0; j < dim; j++){
			inverse->data[i][j] *= (1/pivot);
		}
	}
	free_matrix(concatenate);
	free_matrix(identity);
	free_matrix(aux);
	free_matrix(concatenate_aux);
	return inverse;
}

double cofactor_matrix_elem(int row, int col, Matrix *matrix){
  double *data = calloc((matrix->row -1)*(matrix->row -1), sizeof(double));
  double cofactor;
  int k = 0;

  for (int i = 0; i < matrix->row; i++){
    for (int j = 0; j < matrix->col; j++){
      if (i != row && j != col){
        data[k++] = matrix->data[i][j];
      }
    }
  }

  cofactor = determinant_matrix(populate_matrix((matrix->row)-1, (matrix->col)-1, data));
  if (cofactor != 0 && (row + col + 2) % 2 != 0){
   cofactor = cofactor * (-1); 
  }

  return cofactor;
}

Matrix *cofactor_matrix(Matrix *matrix){	
	if (matrix == NULL){
		printf("ERROR COFACTOR: sos muy wachin, me diste una matriz que no existe\n");
		return NULL;
	}
	if (matrix->col - matrix->row){
		printf("ERROR COFACTOR: sos muy wachin, me diste una matriz no cuadrada\n");
	}

	int dim = matrix->row;
	Matrix *result = init_matrix(dim, dim);

	for (int i = 0; i < dim; i ++){
		for (int j = 0; j < dim; j++){
			result->data[i][j] = cofactor_matrix_elem(i, j, matrix);
		}
	}
	return result;

}
Matrix *adjoint_matrix(Matrix *matrix){
	if (matrix == NULL){
		printf("ERROR COFACTOR: sos muy wachin, me diste una matriz que no existe\n");
		return NULL;
	}
	if (matrix->col - matrix->row){
		printf("ERROR COFACTOR: sos muy wachin, me diste una matriz no cuadrada\n");
	}
	
	Matrix *result, *cofactor = cofactor_matrix(matrix);
	result = transpose_matrix(cofactor);
	free_matrix(cofactor);
	return result;

}

Matrix *fast_inverse_matrix(Matrix *matrix){
	if (!determinant_matrix(matrix)){
		printf("ERROR Inverse: matriz no tiene inversa\n");
		return NULL;
	}
	if (matrix->col - matrix->row){
		printf("Error Inverse: quiere calcular inversa de una no cuadrada\n");
		return NULL;
	}

	Matrix *result, *adjoint;

	adjoint = adjoint_matrix(matrix);
	result = scalar_multiplication_matrix(1 / determinant_matrix(matrix), adjoint);
	free_matrix(adjoint);

	return result;
}

int range_matrix(const Matrix *matrix){
	if (matrix == NULL){
		printf("ERROR range, wachin me metiste una matriz que no existe\n");
		return 0;
	}

	Matrix *triangular = gaussian_elimination_matrix(matrix);
	int i, row_pos = 0, col_pos = 0, range = 0;

	while(row_pos < triangular->row && col_pos < triangular->col){
		if (triangular->data[row_pos][col_pos]) {
			row_pos ++; col_pos ++; range ++;
		}	
		else{
			for( i = col_pos; i < triangular->row; i++){
				if (triangular->data[row_pos][i]) {
					range ++; col_pos = i +1; row_pos ++;
					break;
				}
			}
			
		}

	}
	free_matrix(triangular);
	return range;
}


//Funciones de vectores
Vector *init_vector(int dim){
	if (dim <= 0){
		printf("ERROR: init_vector no existe dimension menor a 1\n");
		return NULL;
	}
	
	Vector *vector;
	vector = calloc(1, sizeof(Vector));
	vector->dim = dim;
	vector->data = calloc(dim, sizeof(double));
	return vector;	
}

Vector *copy_vector(const Vector *vector1){
	if(vector1 == NULL){
		printf("ERROR: copy_vector recibe NULL\n");
		return NULL;
	}	
	Vector *vector;
	vector = init_vector(vector1->dim);
	for(int i = 0; i < vector->dim; i++) vector->data[i] = vector1->data[i];
	
	return vector;
}

void print_vector(const Vector *vector){
	if(vector == NULL){
		printf("ERROR: print_vector recibe NULL\n");	
		return;
	}
	for (int i = 0; i < vector->dim; i++) printf("%lf\n", vector->data[i]); 
}

void set_elem_vector(int elem, double value,  Vector *vector){
	if (vector == NULL){
		printf("ERROR: set_elem, ingresa vector NULL\n");
		return;
	}
	if(elem > vector->dim){
		printf("ERRIR: set_elem_vector, dimension no valida\n");
	return;
	}
	vector->data[elem - 1] = value;
}

double scalar_product_vector(const Vector *vector1, const Vector *vector2){
	if (vector1 == NULL || vector2 == NULL){
		printf("ERRO: scalar_product, ingresa vectores NULL\n");
		return 0;
	}	
	int dim = vector1->dim;
	if (vector1->dim - vector2->dim){
		printf("ERROR: sclar_product, dimension incorrecta\n");
		return 0;
	}	
	
	double scalar_product = 0.0;

	for(int i = 0; i < dim; i++) if(vector1->data[i] && vector2->data[i]) scalar_product += (vector1->data[i] * vector2->data[i]);  //el if es para evitar el -0
	return scalar_product;
}

Vector *vector_addition(const Vector *vector1, const Vector *vector2){
	if (vector1 == NULL || vector2 == NULL){
		printf("ERRO: vector_addition, ingresa vectores NULL\n");
		return NULL;
	}	
	int dim = vector1->dim;
	if (vector1->dim != vector2->dim){
		printf("ERROR: vector_addition, dimension incorrecta\n");
		return NULL;
	}	
	Vector *result = init_vector(dim);
	
	for(int i = 0; i < dim; i++){ 
		if(vector1->data[i] && vector2->data[i]) result->data[i] = (vector1->data[i] + vector2->data[i]);  //el if es para evitar el -0}
	}
	return result;
}

//Si data es mas grande que dim, se desechan los valores restante, si es mas chico se completa el vector con cero. Comportamiento similar a popoulate_matrix
Vector *populate_vector(int dim, const double *data){
	if (dim <= 0){
		printf("ERROR: populate vector, dimension invalida\n");
		return NULL;
	}
	if(data == NULL){
		printf("ERROR: populate_vector, data NULL\n");
		return NULL;
	}
		
	Vector *vector = init_vector(dim);
	for(int i = 0; i < dim; i ++){
		vector->data[i] = data[i];
	}

	return vector;
}

Vector *cross_product_3_dim_vector(const Vector *vector1, const Vector *vector2){
	if(vector1 == NULL || vector2 == NULL){
		printf("ERROR: cross_product recibe NULL\n");
		return NULL;
	}
	if(vector1->dim != 3 && vector2->dim != 3){
		printf("ERROR: cross_product solo para dimension tres\n");
		return NULL;
	}
	
	double data[3];

	data[0] = vector1->data[1]*vector2->data[2] - vector1->data[2]*vector2->data[1];
	data[1] = vector1->data[2]*vector2->data[0] - vector1->data[0]*vector2->data[2];
	data[2] = vector1->data[0]*vector2->data[1] - vector1->data[1]*vector2->data[2];

	for(int i = 0; i ++; i < 3){
		if(data[i] == (-0)) data[i] = 0; //evitar el -0
	}
	return populate_vector(3, data);
}


//funciones de matrices y vectores


//asume que la multiplicacion es con el vector a la izquierda. El vector se escribe como columna. Si no te sirve matate (o usa matrix_multiplication).
Vector *matrix_vector_multiplication(const Matrix *matrix, const Vector* vector){
	if(matrix == NULL || vector == NULL){
		printf("ERROR: matrix_vector_multiplication, ingresa NULL\n");
		return NULL;
	}
	if(matrix->col - vector->dim){
		printf("ERROR: matrix_vector_multiplication, error de dimension\n");
		return NULL;
	}	
	
	Vector *result = init_vector(matrix->row);
	for (int i = 0; i < result->dim; i ++){
		for (int j = 0; j < vector->dim; j++){
			if(matrix->data[i][j] && vector->data[j]) {//evitar el -0
				result->data[i] += (matrix->data[i][j] * vector->data[j]);
				
			}
		}
	}
	return result;
}


