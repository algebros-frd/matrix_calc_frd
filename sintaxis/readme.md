La idea de la calculadora es que se pueda correr desde una terminal, donde el usuario escribe de manera similar a lo que haría en un lenguaje de programacion. El usuario escribiria sentencias, que se terminen en ';', por lo tanto podría usar mas de una linea. Algunos ejemplos base de una sentencia serían los siguientes:
	det(inv(A * B); B = A * C; range(A);

Habría que definir primero las expresiones regulares de todos los tokens, y luego la gramatica. Para comenzar, se probará con un par de funciones nomas.
