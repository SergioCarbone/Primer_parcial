#ifndef _CONTRATACIONES
#define _CONTRATACIONES
typedef struct{
    char CUIT[13];
    char nombreArchivo[60];
    int id;
    int idPantalla;
    int dias;
    unsigned char estado;
}sContrataciones;
#endif // CONTRATACIONES


#define CONTRATACION_LIBRE 0
#define CONTRATACION_OCUPADA 1

int contr_initArray (sContrataciones* arrayContrataciones, int longitud);
int contr_generarProximoId (void);
int contr_nuevaPublicidad (sPantalla* arrayPantalla, sContrataciones* arrayContrataciones,int longitudPantalla, int longitudContrataciones, char* mensaje);
int contr_buscarIndicePorCuit (sContrataciones* arrayContrataciones, int longitud, char* cuit, char* mensaje);
int contr_modificarContratacion (sPantalla* arrayPantalla, sContrataciones* arrayContrataciones,int longitudPantalla, int longitudContrataciones);
int contr_cancelarContratacion (sPantalla* arrayPantalla, sContrataciones* arrayContrataciones,int longitudPantalla, int longitudContrataciones);

