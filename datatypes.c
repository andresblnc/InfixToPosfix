#include "datatypes.h"

TYPE int_create(int n)
{
	int *ptr=malloc(sizeof(int));
	*ptr = n;
	return(ptr);
}

TYPE float_create(float n)
{
	float *ptr=malloc(sizeof(float));
	*ptr = n;
	return(ptr);
}

TYPE double_create(double n)
{
	double *ptr=malloc(sizeof(double));
	*ptr = n;
	return(ptr);
}

TYPE char_create(char c)
{
	int *ptr=malloc(sizeof(char));
	*ptr = c;
	return(ptr);
}

TYPE string_create(char *s)
{
	int strsize=strlen(s);
	char *ptr=malloc(strsize);
	strcpy(ptr,s);
	return(ptr);
}

