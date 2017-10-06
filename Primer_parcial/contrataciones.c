#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantalla.h"
#include "contrataciones.h"
#include "validar.h"
#include "informes.h"

/** \brief Inicializa los campos del array
 *
 * \param array estructura recibida por referencia
 * \param longitud tamaño del array
 * \return 0 ok -1 error
 *
 */
int contr_initArray (sContrataciones* arrayContrataciones, int longitud)
{
    int retorno = -1;
    int i;
    if(arrayContrataciones != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            arrayContrataciones[i].estado = ESTADO_LIBRE;
        }

    }
    return retorno;
}

/** \brief Genera un id autoincrementable
 *
 * \return id a utilizar
 *
 */
static int idAutoincrementable = -1;

int contr_generarProximoId (void)
{
    idAutoincrementable++;
    return idAutoincrementable;
}


/** \brief recorre el array buscando el proximo espacio libre para cargar una nueva publicidad
 *
 * \param array estructura recibida por referencia
 * \param longitud tamaño del array
 * \param mensaje de error para el usuario
 * \return 0 ok o -1 error
 *
 */
int contr_nuevaPublicidad (sPantalla* arrayPantalla, sContrataciones* arrayContrataciones,
                           int longitudPantalla, int longitudContrataciones, char* mensaje)
{
    int retorno = -1;
    int idAux, i;
    int indice;
    char buffer[10];
    char bNombre[50];
    int indicePantalla;
    char bCuit[13];
    char bDias[100];

    if((arrayContrataciones != NULL && arrayPantalla!= NULL) && (longitudPantalla>= 0 && longitudContrataciones>= 0))
    {
        for(i=0; i<longitudContrataciones; i++)
        {
            if(arrayContrataciones[i].estado == ESTADO_LIBRE)
            {
                indice = i;
                break;
            }
        }
        for(i=0; i<longitudPantalla; i++)
        {
            if(arrayPantalla[i].estadoPantalla == ESTADO_OCUPADO)
            {
                printf("\nPantalla id: %d", arrayPantalla[i].idPantalla);
            }
        }
        if (val_getUnsignedInt(buffer,"\nElija una de las pantallas: ", "\nIngrese solo numeros",3,10)>0)
        {
            idAux = atoi(buffer);
            indicePantalla = pantalla_buscarIndicePorId(arrayPantalla,longitudPantalla,idAux, "\nNo se encontro el id");

            if(indicePantalla != -1)
            {
                if(val_getCuit(bCuit,"\nIngrese el cuit: ","\nError, tiene que ser con este formato XX-XXXXXXXX-X: ",2,13)== 0)
                {
                    if(val_getUnsignedInt(bDias,"\nIngrese los dias que la va a alquilar: ","\nError, ingrese un numero: ",2,100)== 0)
                    {
                        if(val_getString(bNombre,"\nIngrese el nombre del archivo: ","\nError, solo puede ingresar letras: ",3,50)==0)
                        {
                            arrayContrataciones[indice].id = contr_generarProximoId();
                            arrayContrataciones[indice].idPantalla = idAux;
                            strncpy(arrayContrataciones[indice].CUIT,bCuit,13);
                            arrayContrataciones[indice].dias = atoi(bDias);
                            arrayContrataciones[indice].estado = ESTADO_OCUPADO;
                            retorno = 0;
                        }
                    }
                }
            }
        }
        else
        {
            printf("%s", mensaje);
        }
    }
    return retorno;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

int contr_modificarContratacion (sPantalla* arrayPantalla, sContrataciones* arrayContrataciones,
                                 int longitudPantalla, int longitudContrataciones)
{
    int retorno = -1;
    int idAux, i;
    int indice;
    char buffer[10];
    int indicePantalla;
    char bCuit[13];
    char bDias[100];

    if(val_getCuit(bCuit,"\nIngrese el cuit: ","\nError, tiene que ser con este formato XX-XXXXXXXX-X: ",2,13)== 0)
    {
        indice = contr_buscarIndicePorCuit(arrayContrataciones,longitudContrataciones,bCuit,"El cuit no se encontro");
    }

    if(indice != -1)
    {
        for(i=0; i<longitudContrataciones; i++)
        {
            if(arrayPantalla[i].estadoPantalla == ESTADO_OCUPADO && arrayContrataciones[indice].estado == ESTADO_OCUPADO)
            {
                printf("Id: %d",arrayContrataciones[i].idPantalla);
                printf("Nombre del archivo: %s",arrayContrataciones[i].nombreArchivo);
                printf("Dias alquilada: %d",arrayContrataciones[i].dias);
            }
        }

        if (val_getUnsignedInt(buffer,"\nElija una de las pantallas: ", "\nIngrese solo numeros",3,10)>0)
        {

            idAux = atoi(buffer);
            indicePantalla = pantalla_buscarIndicePorId(arrayPantalla,longitudPantalla,idAux, "\nNo se encontro el id");

            if(indicePantalla != -1)
            {
                if(val_getUnsignedInt(bDias,"\nIngrese los dias que la va a alquilar: ","\nError, ingrese un numero: ",2,100)== 0)
                {
                    arrayContrataciones[indice].dias = atoi(bDias);
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}


int contr_buscarIndicePorCuit (sContrataciones* arrayContrataciones, int longitud, char* cuit, char* mensaje)
{
    int retorno = -1;
    int i;

    if(arrayContrataciones != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            if(arrayContrataciones[i].estado== ESTADO_OCUPADO)
            {
                if(strcmp(cuit,arrayContrataciones[i].CUIT)==0)
                {
                    retorno = i;
                    break;
                }
            }
        }
        if(retorno == -1)
        {
            printf("%s", mensaje);
        }
    }
    return retorno;
}



int contr_cancelarContratacion (sPantalla* arrayPantalla, sContrataciones* arrayContrataciones,
                                int longitudPantalla, int longitudContrataciones)
{
    int retorno = -1;
    int idAux, i;
    int indice;
    char buffer[10];
    int indicePantalla;
    char bCuit[13];

    if(val_getCuit(bCuit,"\nIngrese el cuit: ","\nError, tiene que ser con este formato XX-XXXXXXXX-X: ",2,13)== 0)
    {
        indice = contr_buscarIndicePorCuit(arrayContrataciones,longitudContrataciones,bCuit,"El cuit no se encontro");
    }

    if(indice != -1)
    {
        for(i=0; i<longitudContrataciones; i++)
        {
            if(arrayPantalla[i].estadoPantalla == ESTADO_OCUPADO && arrayContrataciones[indice].estado == ESTADO_OCUPADO)
            {
                printf("Id: %d",arrayContrataciones[i].idPantalla);
                printf("Nombre del archivo: %s",arrayContrataciones[i].nombreArchivo);
                printf("Dias alquilada: %d",arrayContrataciones[i].dias);
            }
        }

        if (val_getUnsignedInt(buffer,"\nElija una de las pantallas: ", "\nIngrese solo numeros",3,10)>0)
        {

            idAux = atoi(buffer);
            indicePantalla = pantalla_buscarIndicePorId(arrayPantalla,longitudPantalla,idAux, "\nNo se encontro el id");

            if(indicePantalla != -1)
            {

                arrayContrataciones[indice].estado = ESTADO_LIBRE;
                retorno = 0;

            }
        }
    }
    return retorno;
}



///** \brief
// *
// * \param
// * \param
// * \return
// *
// */
//int contr_obtenerTotalesDeCadaContratacion (sPantalla* arrayPantalla, sContrataciones* arrayContrataciones,
//        int longitudPantalla, int longitudContrataciones)
//{
//    int retorno = -1;
//    int i;
//    int arrayTotal[longitudContrataciones];
//    char bCuit[13];
//    int indice;
//
//    if((arrayContrataciones != NULL && arrayPantalla!= NULL) && (longitudPantalla>= 0 && longitudContrataciones>= 0))
//    {
//        for(i= 0; i<longitudContrataciones; i++)
//        {
//            arrayContrataciones[i] = 0;
//
//        }
//
//        if(val_getCuit(bCuit,"\nIngrese el cuit: ","\nError, tiene que ser con este formato XX-XXXXXXXX-X: ",2,13)== 0)
//        {
//            indice = contr_buscarIndicePorCuit(arrayContrataciones,longitudContrataciones,bCuit,"El cuit no se encontro");
//        }
//
//        if(indice != -1)
//        {
//            for(i= 0; i<longitudPantalla; i++)
//            {
//                if(arrayPantalla[i].estadoPantalla == ESTADO_OCUPADO && arrayContrataciones[indice].estado == ESTADO_OCUPADO)
//                {
//                    arrayContrataciones[i] = arrayContrataciones[i].dias . arrayPantalla[i].precioPorDia;
//                }
//            }
//        }
//    }
//    return retorno;
//}


