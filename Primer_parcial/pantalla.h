#ifndef _PANTALLA
#define _PANTALLA
typedef struct{
    char direccion [60];
    unsigned char tipoPantalla;
    unsigned char estadoPantalla;
    int precioPorDia;
    int idPantalla;

}sPantalla;
#endif // _PANTALLA

#define TIPO_LCD 0
#define TIPO_LED 1

#define ESTADO_LIBRE 0
#define ESTADO_OCUPADO 1

int pantalla_initArray (sPantalla* arrayPantalla, int longitud);
int pantalla_generarProximoId (void);
int pantalla_cargarPantalla (sPantalla* arrayPantalla,int longitud);
int pantalla_modificarPantalla(sPantalla* arrayPantalla, int longitud);
int pantalla_buscarIndicePorId (sPantalla* arrayPantalla, int longitud, int id, char* mensaje);
int pantalla_darDeBajaPantalla(sPantalla* arrayPantalla, int longitud);
