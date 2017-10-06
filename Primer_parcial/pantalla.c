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
int pantalla_initArray (sPantalla* arrayPantalla, int longitud)
{
    int retorno = -1;
    int i;
    if(arrayPantalla != NULL && longitud > 0)
    {
        for(i=0; i<longitud ; i++)
        {
            arrayPantalla[i].estadoPantalla = ESTADO_LIBRE;
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

int pantalla_generarProximoId (void)
{
    idAutoincrementable++;
    return idAutoincrementable;
}


/** \brief cargaPersona realiza la carga de datos
 * \param arrayPersona array recibido por parametro
 * \param longitud del array
 * \return 0 si se realizo la carga correctamente o -1 si no se pudo
 *
 */
int pantalla_cargarPantalla (sPantalla* arrayPantalla,int longitud)
{
    int retorno = -1;
    int i, indice;
    char bDireccion[60];
    char bPrecio[10];
    char buffer[10];
    int contadorIntentos =0;
    int flagTipo =0;

    if(arrayPantalla != NULL && longitud >= 0)
    {
        for(i=0; i<longitud; i++)
        {
            if(arrayPantalla[i].estadoPantalla == ESTADO_LIBRE)
            {
                indice = i;
                break;
            }
        }
        if(val_getAlfanumerico(bDireccion, "\nIngrese la direccion: ", "\nError, no se pueden ingresar signos: ",3,60)== 0)
        {
            if(val_getUnsignedInt(bPrecio,"\nIngrese el precio de la pantalla: ","\nError, solo puede ingresar numeros: ",2,10)== 0)
            {
                do
                {
                    val_getUnsignedInt(buffer,"\n1-Pantalla LCD.\n2- Pantalla LED.\n\nIngrese el tipo de pantalla: ","\nError, ingrese un numero dentro de las opciones ",3,10);
                    switch(atoi(buffer))
                    {
                    case 1:
                        arrayPantalla[indice].tipoPantalla = TIPO_LCD;
                        flagTipo = 1;
                        break;
                    case 2:
                        arrayPantalla[indice].tipoPantalla = TIPO_LED;
                        flagTipo = 1;
                        break;
                    }
                    contadorIntentos ++;
                }
                while (flagTipo == 0 && contadorIntentos < 3);

                if(flagTipo == 1)
                {
                    strncpy(arrayPantalla[indice].direccion,bDireccion,60);
                    arrayPantalla[indice].precioPorDia = atoi(bPrecio);
                    arrayPantalla[indice].estadoPantalla= ESTADO_OCUPADO;
                    arrayPantalla[indice].idPantalla = pantalla_generarProximoId();
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}


/** \brief recorre el array para modificar campos de la estructura
 *
 * \param array recibido por referencia
 * \param longitud del array
 * \return 0 ko o -1 error
 *
 */
int pantalla_modificarPantalla(sPantalla* arrayPantalla, int longitud)
{
    int retorno = -1;
    char bDireccion[60];
    char bPrecio[10];
    int idAux;
    int indice;
    char buffer[10];


    val_getUnsignedInt(buffer,"Ingrese el ID a modificar", "El ID no se encontro",3,10);
    idAux = atoi(buffer);

    indice = pantalla_buscarIndicePorId(arrayPantalla,longitud,idAux, "No se encontro el id");

    if(indice != -1)
    {
        if(val_getAlfanumerico(bDireccion, "\nIngrese la direccion: ", "\nError, no se pueden ingresar signos: ",3,60)== 0)
        {
            if(val_getUnsignedInt(bPrecio,"\nIngrese el precio de la pantalla: ","\nError, solo puede ingresar numeros: ",2,10)== 0)
            {
                strncpy(arrayPantalla[indice].direccion,bDireccion,60);
                arrayPantalla[indice].precioPorDia = atoi(bPrecio);
            }
        }
    }
    return retorno;
}

/** \brief recorre el array buscando un indice utilizando un id
 *
 * \param array estructura recibida por referencia
 * \param longitud tamaño del array
 * \param id recibido por parametro para ser comparado al recorrer el array
 * \param mensaje para el usuario
 * \return 0 ok o -1 error
 *
 */
int pantalla_buscarIndicePorId (sPantalla* arrayPantalla, int longitud, int id, char* mensaje)
{
    int retorno = -1;
    int i;

    if(arrayPantalla != NULL && longitud > 0 && id >= 0)
    {
        for(i=0; i<longitud ; i++)
        {
            if(arrayPantalla[i].estadoPantalla == ESTADO_OCUPADO)
            {
                if(id == arrayPantalla[i].idPantalla)
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


/** \brief recorre el array para hacer una baja logica
 *
 * \param array recibido por referencia
 * \param longitud del array
 * \return 0 ko o -1 error
 *
 */
int pantalla_darDeBajaPantalla(sPantalla* arrayPantalla, int longitud)
{
    int retorno = -1;
    int idAux;
    char buffer[10];
    int indice;

    val_getUnsignedInt(buffer,"Ingrese el ID para dar de baja", "El ID no se encontro",3,10);
    idAux = atoi(buffer);

    indice = pantalla_buscarIndicePorId(arrayPantalla,longitud,idAux, "No se encontro el id");

    if(indice != -1)
    {
        arrayPantalla[indice].estadoPantalla = ESTADO_LIBRE;
        retorno = 0;

    }
    return retorno;
}




