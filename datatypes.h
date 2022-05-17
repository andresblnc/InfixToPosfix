#include <stdlib.h>
#include <string.h>

#ifndef DATATYPES_H_
#define DATATYPES_H_

typedef int BOOL;
typedef void * TYPE;


#define int_val(e)		(*((int *) e))
#define float_val(e)	(*((float *) e))
#define double_val(e)	(*((double *) e))
#define char_val(e)		(*((char *) e))
#define str_ptr(e)		((char *) e)


TYPE int_create(int n); 
TYPE float_create(float n);
TYPE double_create(double n);
TYPE char_create(char c);
TYPE string_create(char *s);

#endif /* DATATYPES_H_ */

