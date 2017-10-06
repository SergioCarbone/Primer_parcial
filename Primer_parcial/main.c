#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pantalla.h"
#include "contrataciones.h"
#include "validar.h"
#include "informes.h"

#define CANTIDAD_CONTRATACIONES 5
#define CANTIDAD_PANTALLAS 5

int main()
{
    sContrataciones contrataciones[CANTIDAD_CONTRATACIONES];
    sPantalla pantalla[CANTIDAD_PANTALLAS];

    contr_initArray(contrataciones,CANTIDAD_CONTRATACIONES);
    pantalla_initArray(pantalla,CANTIDAD_PANTALLAS);

    char opcion[10];
    int salir = 1;
    do
    {
        val_getUnsignedInt(opcion,"\n\n1- Alta de pantalla.\n2- Modificar datos de pantalla.\n3- Baja de pantalla.\n4- Contratar una publicidad.\n5- Modificar condiciones de publicidad.\n6- Cancelar contratacion.\n7- Consulta facturacion.\n8- Listar contrataciones.\n9- Listar pantallas.\n10- Informar.\n11- Salir.\n\nIngrese una opcion: ","\nIngrese una opcion valida.\n",3,10);

        switch(atoi(opcion))
        {
        case 1:
            pantalla_cargarPantalla(pantalla,CANTIDAD_PANTALLAS);
            break;
        case 2:
            pantalla_modificarPantalla(pantalla,CANTIDAD_PANTALLAS);
            break;
        case 3:
            pantalla_darDeBajaPantalla(pantalla,CANTIDAD_PANTALLAS);
            break;
        case 4:
            contr_nuevaPublicidad(pantalla,contrataciones,CANTIDAD_CONTRATACIONES,CANTIDAD_PANTALLAS,"Error.");
            break;
        case 5:
            contr_modificarContratacion(pantalla,contrataciones,CANTIDAD_CONTRATACIONES,CANTIDAD_PANTALLAS);
            break;
        case 6:
            contr_cancelarContratacion(pantalla,contrataciones,CANTIDAD_CONTRATACIONES,CANTIDAD_PANTALLAS);
            break;
        case 7:

            salir = 0;
            break;
        }
    }
    while(salir != 0);
    return 0;
}

