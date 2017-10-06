#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantalla.h"
#include "contrataciones.h"
#include "validar.h"
#include "informes.h"

#define MAX_INPUT_BUFFER 4096

/** \brief recibe un buffer y en la ultima posicion coloca un \0
 *
 * \param buffer donde se carga el string
 * \param limite tamaño del string
 *
 */
void myFgets(char* buffer, int limite,FILE* archivo)
{
    int i=0;
    fflush(archivo);
    fgets(buffer, limite,archivo);
    buffer[limite-1] = '\0';
    while(buffer[i] != '\0')
    {
        if(buffer[i] == 10)//10 -> LF
        {
            buffer[i] = '\0';
            break;
        }
        i++;
    }
}

/** \brief Valida que solo se ingresen letras
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getString(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarString(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}


/** \brief valida que solo se ingresen letras
 *
 * \param buffer donde se guarda es string
 * \return 0 ok y -1 error
 */
int val_validarString(char* buffer)
{
    int i=0;
    int retorno = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') && (buffer[i] < 'A' || buffer[i] > 'Z') && buffer[i] != ' ')
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}



/** \brief Valida que solo se ingrese formato DNI
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getCuit(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarCuit(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}



/** \brief valida que solo se ingresen numeros y puntos
 *
 * \param buffer donde se guarda es string
 * \return 0 ok y -1 error
 */
int val_validarCuit(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagGuion = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '-')
        {
            retorno = -1;
            break;
        }
        else
        {
            if((buffer[i] == '-' && i == 3) || (buffer[i] == '-' && i == 12))
            {
                flagGuion++;
            }
        }
        i++;
    }
    if(flagGuion != 2)
    {
        retorno = -1;
    }
    return retorno;
}


/** \brief Valida que solo se ingresen numeros enteros
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getUnsignedInt(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarUnsignedInt(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}



/** \brief valida que solo se ingresen numeros
 *
 * \param buffer donde se guarda es string
 * \return 0 ok y -1 error
 */
int val_validarUnsignedInt(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagPunto = 0;
    while(buffer[i] != '\0')
    {
        if(buffer[i] < '0' || buffer[i] > '9' )
        {
            retorno = -1;
            break;
        }
        else
        {
            if(buffer[i] == '-' && i != 0)
            {
                retorno = -1;
                break;
            }
            else if(buffer[i] == '.')
            {
                flagPunto++;
                if(flagPunto > 1)
                {
                    retorno = -1;
                    break;
                }
            }
        }
        i++;
    }
    return retorno;
}



/** \brief Valida que solo se ingresen edad dentro de un rango
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getUnsignedEdad(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = 0;
     char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarUnsignedEdad(buffer) == -1 || (atoi(buffer) < 0 || atoi(buffer) > 100))
            {
                printf(mensajeError);
                retorno = -1;
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
            }
            break;
        }
    }
    return retorno;
}



/** \brief valida que solo se ingresen numeros
 *
 * \param buffer donde se guarda es string
 * \return 0 ok y -1 error
 */
int val_validarUnsignedEdad(char* buffer)
{
    int i=0;
    int retorno = 0;
    while(buffer[i] != '\0')
    {
        if(buffer[i] < '0' || buffer[i] > '9' )
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}


/** \brief Toma un string ingresado por el usuario
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getAlfanumerico(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarAlfanumerico(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/** \brief valida que solo se ingresen numeros, letras o signos
 *
 * \param buffer donde se guarda es string
 * \return 0 ok y -1 error
 */
int val_validarAlfanumerico(char* buffer)
{
    int i=0;
    int retorno = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') &&
            (buffer[i] < 'A' || buffer[i] > 'Z') && (buffer[i] < '0' || buffer[i] > '9') && (buffer[i] != ' '))
        {
            retorno = -1;
            break;
        }
        i++;
    }
    return retorno;
}



/** \brief Toma un string ingresado por el usuario
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getMail(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarMail(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}



/** \brief valida que solo se ingresen numeros, letras o signos y controla que el @ no este en el primer caracter y que
    no contenga mas de un @
 * \param buffer donde se guarda es string
 * \return 0 ok y -1 error
 */
int val_validarMail(char* buffer)
{
    int i=0;
    int retorno = 0;
    int contAt = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < 'a' || buffer[i] > 'z') &&
            (buffer[i] < 'A' || buffer[i] > 'Z') && (buffer[i] < '0' || buffer[i] > '9') &&
            (buffer[i] != '.') && (buffer[i] != '-') && (buffer[i] != '_') && (buffer[i] != '@'))
        {
            retorno = -1;
            break;
        }
        if(buffer[i] == '@' && i == 0)
           {
               retorno = -1;
               break;
           }
           else if (buffer[i] == '@')
            {
                contAt++;
            }

        if(contAt == 0)
        {
            retorno = 0;
        }
        i++;
    }
    return retorno;
}

/** \brief Toma un string ingresado por el usuario
 *
 * \param destino donde se guarda el string
 * \param mensaje para el usuario
 * \param mensajeError para el usuario
 * \param intentos cantidad de intentos si no cumple con la validacion
 * \param limite tamaño del string
 * \return 0 ok -1 error
 *
 */
int val_getFloat(char* destino, char* mensaje,char* mensajeError,int intentos,int limite)
{
    int retorno = -1;
    char buffer[MAX_INPUT_BUFFER];

    if(destino != NULL && limite > 0 && limite < MAX_INPUT_BUFFER)
    {
        printf(mensaje);
        for( ; intentos>0; intentos--)
        {

            myFgets(buffer, limite,stdin);

            if(val_validarFloat(buffer) == -1)
            {
                printf(mensajeError);
                continue;
            }
            else
            {
                strncpy(destino,buffer,limite);
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}


/** \brief valida que solo se ingresen numeros y que contenga un punto o "-" en la primera posicion
 * \param buffer donde se guarda es string
 * \return 0 ok y -1 error
 */
int val_validarFloat(char* buffer)
{
    int i=0;
    int retorno = 0;
    int flagPunto = 0;
    while(buffer[i] != '\0')
    {
        if((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '.' && buffer[i] != '-' )
        {
            retorno = -1;
            break;
        }
        else
        {
            if(buffer[i] == '-' && i != 0)
            {
                retorno = -1;
                break;
            }
            else if(buffer[i] == '.')
            {
                flagPunto++;
                if(flagPunto > 1)
                {
                    retorno = -1;
                    break;
                }
            }
        }
        i++;
    }
    return retorno;
}


