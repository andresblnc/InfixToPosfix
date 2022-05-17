#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

#define MAX 30 //Tamaño de las expresiones

char Infija[MAX]; //Expresion infija
char Posfija[MAX]; //Expresion posfija
int posfija_index = 0; //Indice de posfija para agregar valores

void parentesis_stack(STACK operators);
void converter(char infix[MAX],STACK operators, char postfix[MAX]);
int precedence(char value);
void calculateOrder(STACK operators,int scan, char character);


int main()
{
    STACK operators=stack_create(); //se crea el stack de operadores

	printf("Escriba expresión arítmetica infija:");
	gets(Infija);

    parentesis_stack(operators);
    converter(Infija,operators,Posfija);

    printf("\nExpresión en notación Postfija:");
    puts(Posfija);
    
    stack_destroy(operators);
	return 0;
}

void parentesis_stack(STACK operators)//Agrega parentesis inicio y final a la infija
{
    int i;
    for ( i = 0; i < MAX; i++)
    {
        if (Infija[i] == '\0')
        {
            Infija[i]=')';//Agregar al final de la notacion infija un parentesis derecho
            i=MAX;
        }
    } 
    stack_push(operators,"("); //agregar al stack de operadores un parentesis izquierdo
    
}

void converter(char infix[MAX],STACK operators, char postfix[MAX]) // Invertidor de infija a posfija
{
    int i;
    TYPE operatorTop; //Variable de el top del stack
    TYPE operatorDelete; //Variable a eliminar del stack
    int pre; //Variable para comparar precedencia de operadores
    
    for ( i = 0; infix[i]!= '\0'; i++) //Se recorre toda la cadena que contiene la operacion en notacion infija 
    {
        if (infix[i]=='/'|| infix[i]=='+' || infix[i]=='-' ||infix[i]=='*')//Si es algun operador
        {
            if (operators->size==1)//Si es el primer operador que se encuentra solo se agrega el stack
            {
                stack_push(operators,char_create(infix[i]));
            }
            else//Si ya no es el primer operador entonces se va a checar la precedencia del operador que se esta leyendo
            {
                pre=precedence(infix[i]); //checar la precedencia del operador
                calculateOrder(operators,pre,infix[i]); //Calcular la manera en la que se agrega el operador al stack
            }
        }
        else if (infix[i]=='(')//si es parentesis izquierdo se agrega al stack de operadores
        {
            stack_push(operators,char_create(infix[i]));
        }
        else if (infix[i]==')')//si es parentesis derecho
        {
            operatorTop=stack_top(operators);
            while (char_val(operatorTop)!='(')//Mientras que el valor de hasta arriba sea diferente a un parentesis derecho 
            {
                operatorDelete=stack_pop(operators);//se elimina el valor de hasta arriba del stack
                postfix[posfija_index]=char_val(operatorDelete);//Y se agrega a la cadena de salida que es la operacion en notacion postfija
                posfija_index++;//Se aumenta el indice cada vez que se agrega algo a la cadena
                operatorTop=stack_top(operators); //Ahora el top de la cadena será diferente porque ya borramos un elemento
            } 

            if (char_val(operatorTop)=='(')//Despues de sacar los operadores que se encuentran despues del parentesis izquierdo, se elimina el top que en este caso es el parentesis izquierdo
            {
                operatorDelete=stack_pop(operators);
            }
        }  
        else //Si no es ninguna de las variables que mencionamos anteriormente siempremente se agregan a la cadena con notacion postfija
        {
            postfix[posfija_index]=infix[i];
            posfija_index++;
        }   
    }
}

int precedence(char value)//Calcular la precedencia del operador
{
    if (value=='/' || value== '*' ) //si es "/" o "*" tiene mayor precedencia
    {
        return 2;
    }
    else if (value=='-'|| value == '+')//Si es "+" o "-" tiene menor precedencia
    {
        return 1;
    }
    else  //Si no es ninguno de ellos  tendra 0 de precedencia
    {
        return 0;
    }
}

void calculateOrder(STACK operators,int scan,char character)//Funcion para calcular el orden en que se agregan los operadores al stack, o a la cadena postfix
{
    TYPE operatorTop;//Operador de hasta arriba del stack
    TYPE operatorDelete;//Operador que sera eliminado del stack
    int precedenceTop;//Valor que tendra la precedencia del operador de hasta arriba del stack
    operatorTop=stack_top(operators);
    precedenceTop=precedence(char_val(operatorTop));

    if (scan > precedenceTop)//Si la precedencia del operador que leimos en la cadena infix es mayor a la precedencia del operador de hasta arriba del stack
    {
        stack_push(operators,char_create(character));//Se agrega el operador al stack
    }
    else if (scan <= precedenceTop )//Si la precedencia del operador que leimos en la cadena infix es menor o igual  a la precedencia del operador de hasta arriba del stack
    {
        do
        {
            operatorDelete=stack_pop(operators);//Se elimina del stack el operador de hasta arriba
            Posfija[posfija_index]=char_val(operatorDelete);//Se agrega a la cadena que incluye la notacion postfija
            posfija_index++; //Se aumenta el indice cada vez que se agrega algo a la cadena
            operatorTop=stack_top(operators);//El top de la cadena será diferente porque ya borramos un elemento
            precedenceTop=precedence(char_val(operatorTop));//De igual manera la precedencia cambia por que el top cambio
            
        } while (precedenceTop>scan ); //Mientras que el operador de hasta arriba del stack tenga mayor precedencia
        
        if (precedenceTop<scan)//Si la precedencia del top es menor a la precedencia del top que leimos en la cadena infix
        {
            stack_push(operators,char_create(character));//Se agrega el operador al stack
        }
    }   
}
