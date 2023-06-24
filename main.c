#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "pila.h"

//======================================================FUNCIONES============================================================
typedef struct
{
    int legajo;
    char nombreYapellido [30];
    int edad;
    int anio;
//año que cursa, recordar que no podemos utilizar la ñ para definir variables
} stAlumno;


stAlumno cargarStruct()
{
    stAlumno aux;
    printf("===================================================== \n");
    printf("Ingrese el numero de legajo \n");
    scanf("%d",&aux.legajo);

    printf("Ingrese el nombre y apellido \n");
    fflush(stdin);
    gets(aux.nombreYapellido);

    printf("Ingrese la edad \n");
    scanf("%d",&aux.edad);

    printf("Ingrese el anio \n");
    scanf("%d",&aux.anio);

    return aux;

}

void mostrarStruct(stAlumno a)
{
    printf("\n=========================================\n");
    printf("El numero de legajo es : %d \n", a.legajo);
    printf("El nombre y apellido es : %s \n",a.nombreYapellido);
    printf("La edad es : %d \n",a.edad);
    printf("El anio es : %d \n ",a.anio);
    printf("\n=========================================\n");
}

void agregarElementoFinalArchivo (char nombreArchivo [], int dato)
{
    FILE *archi =NULL;
    archi=fopen(nombreArchivo,"ab");            // AB porque si no existe lo crea y escribe al final
    if(archi !=NULL)
    {
        fwrite(&dato,sizeof(int),1,archi);
        fclose(archi);
    }

}

void mostrarContenidoArchivo(char nombreArchivo [])
{
    FILE *archi=NULL;
    archi=fopen(nombreArchivo,"rb");
    int aux;
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(int),1,archi)>0)
        {
            printf("%d \n ",aux);
        }
        fclose(archi);
    }
}

int cantidadDeRegistrosArchivo(char nombreArchivo[])
{
    FILE * archi =NULL;
    archi=fopen(nombreArchivo,"rb");
    int aux, cont=0;
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(int),1,archi))
        {
            cont++;
        }
        fclose(archi);
    }
    return cont;
}

void cargarArchivoAlumnos(char nombreArchivo[])
{
    int i=0;
    FILE *archi=NULL;
    archi=fopen(nombreArchivo,"wb");
    if(archi!=NULL)
    {
        for(i=0; i<5; i++)
        {
            stAlumno aux;
            aux=cargarStruct();
            fwrite(&aux,sizeof(stAlumno),1,archi);

        }
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo \n");
    }
}

void mostrarArchivoAlumnos(char nombreArchivo[])
{
    FILE * archi= fopen(nombreArchivo,"rb");
    stAlumno aux;
    int i=0;
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,archi)>0)
        {
            mostrarStruct(aux);
            i++;
        }
        fclose(archi);
    }
}
void finalArchivoAlumnos(char nombreArchivo [])
{

    FILE *archi =NULL;
    archi=fopen(nombreArchivo,"ab");
    char continuar='s';
    stAlumno alumno;

    if(archi!=NULL)
    {
        while(fwrite(&alumno,sizeof(stAlumno),1,archi)>0 && continuar=='s')
        {
            alumno=cargarStruct();
            printf("Desea cargar otro alumno \n");
            fflush(stdin);
            scanf("%c",&continuar);
        }
        fclose(archi);
    }
    else
    {
        printf("Error");
    }
}

void pasarAPila(char nombreArchivo [],Pila *p)
{
    stAlumno aux;
    Pila auxiliar;
    inicpila(&auxiliar);
    FILE *archi =NULL;
    archi=fopen(nombreArchivo,"rb");

    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,archi)>0)
        {
            if(aux.edad>18)
            {
                apilar(p,aux.edad);
            }
            else
            {
                apilar(&auxiliar,aux.edad);
            }
        }
        fclose(archi);
    }
}
int contarEdadEspecifica(char nombreArchivo [], int edad)
{
    FILE *archi=NULL;
    archi= fopen(nombreArchivo,"rb");
    stAlumno aux;
    int cont=0;
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,archi)>0)
        {
            if(aux.edad>edad)
            {
                cont++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error al abrir \n");
    }
    return cont;
}

void rangoAlumnos (char nombreArchivo [], int rangoMenor, int RangoMayor)
{
    FILE *archi=NULL;
    archi=fopen(nombreArchivo,"rb");
    stAlumno aux;

    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,archi))
        {
            if(aux.edad >rangoMenor && aux.edad<RangoMayor)
            {
                mostrarStruct(aux);
            }
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir \n");
    }

}
void busquedaMayorEdad(char nombreArchivo[])
{
    stAlumno aux,mayor;

    FILE *archi =NULL;
    archi=fopen(nombreArchivo,"rb");

    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stAlumno),1,archi)>0)
        {
            if(aux.edad>mayor.edad)
            {
                mayor=aux;
            }

        }
        mostrarStruct(mayor);
        fclose(archi);
    }
}
int busquedaAnio(char nombreArchivo[], int anio)
{
    FILE *archi= NULL;
    archi=fopen(nombreArchivo,"rb");
    if(archi!=NULL)
    {
        stAlumno aux;
        while(fread(&aux,sizeof(stAlumno),1,archi)>0)
        {
            if(aux.anio ==anio)
            {
                mostrarStruct(aux);
            }
        }
        fclose(archi);

    }
    else
    {
        printf("Error al abrir archivo \n");
    }

}

/*void copiarEnArchivo(stAlumno unArregloDeAlumnos[])
{

    FILE *archi =NULL;
    archi=fopen("Alumnos.bin",archi);
    if(archi!=NULL)
    {
        stAlumno aux;
        int i=0;
        while(fwrite(&aux,sizeof(stAlumno),1,archi)>0)
        {
            unArregloDeAlumnos[i]=aux;
            i++;
        }
        fclose(archi);
    }

}*/
int cantidadRegistros(char nombreArchivo[])
{
    int cantidad,registros;
    stAlumno aux;
    FILE *archi=NULL;
    archi=fopen(nombreArchivo,"rb");
    if(archi!=NULL)
    {
        fseek(archi,0,SEEK_END);
        cantidad=ftell(archi);
        registros=cantidad/sizeof(stAlumno);
        printf("La cantidad de registros que hay son : %d \n ",registros);

    }
}











int main()
{
    char nuevoArchivo[50];
    strcpy(nuevoArchivo, "cargaArchivo.bin");
    char continuar='s';
    char archivoAlumnos[50];
    strcpy(archivoAlumnos,"Alumnos.bin");

    int opcion,dato,cantidad,edad, contador,rangoMenor,rangoMayor,anio,filtrado;

    do
    {
        printf("Bienvenido al sistema \n");

        printf(" 1 - Crear una funcion que cargue un archivo de alumnos. Abrirlo de manera tal de verificar \n "
               "si el archivo ya esta creado previamente. Cargar el archivo con 5 datos. Cerrarlo dentro de la funcion \n");
        printf(" 2 - Crear una funcion que muestre por pantalla los registros de un archivo de alumnos. Modularizar.\n");
        printf(" 3 - Crear una funcion que permita agregar de a un elemento al final del archivo. O sea, se debe \n"
               "abrir el archivo, se piden los datos (se llena una variable de tipo struct alumno), \n"
               " se escribe en el archivo y se cierra\n");
        printf(" 4 - Crear una funcion que pase a una pila los números de legajo de los alumnos mayores de edad. \n");
        printf(" 5 - Dado un archivo de alumnos, hacer una función que cuente la cantidad de alumnos mayores a \n"
               "edad específica que se envía por parámetro\n");
        printf(" 6 - Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un rango de \n"
               "edades especifico (por ejemplo, entre 17 y 25 años). Dicho rango debe recibirse por parámetro. Modularizar\n");
        printf(" 7- Dado un archivo de alumnos, mostrar los datos del alumno de mayor edad. Modularizar\n");
        printf("8-Crear una funcion que retorne la cantidad de alumnos que cursan un determinado anio \n" );
        printf("9 -Crear una funcion que reciba como parametro un arreglo de tipo alumno y lo copie en el archivo \n "
               "Asimismo, realice otra funcion que pase los elementos del archivo a un arreglo de alumnos,\n"
               "filtrando los estudiantes de un anio en particular \n");
        printf("10-Crear una función que retorne la cantidad de registros que tiene el archivo. Usar fseek y ftell \n");


        printf(" \n Elija una opcion \n");
        fflush(stdin);
        scanf("%d",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1 :
        {
            cargarArchivoAlumnos(archivoAlumnos);
            break;

        }

        case 2 :
        {
            mostrarArchivoAlumnos(archivoAlumnos);
            break;
        }
        case 3:
        {
            finalArchivoAlumnos(archivoAlumnos);
            break;
        }
        case 4 :
        {
            Pila mayores;
            inicpila(&mayores);
            pasarAPila(archivoAlumnos,&mayores);
            mostrar(&mayores);
            break;
        }
        case 5:
        {
            printf("Ingrese una edad \n");
            scanf("%d",&edad);
            contador=contarEdadEspecifica(archivoAlumnos,edad);
            printf("La cantidad de alumnos superiores a la edad establecida es : %d \n ", contador);
            break;
        }

        case 6 :
        {
             printf("Ingrese el rango inferior \n");
            scanf("%d",&rangoMenor);

            printf("Ingrese el rango mayor \n");
            scanf("%d",&rangoMayor);

            system("cls");

            rangoAlumnos(archivoAlumnos,rangoMenor,rangoMayor);
            break;
        }
        case 7:
        {
            busquedaMayorEdad(archivoAlumnos);
            break;
        }
        case 8 :
        {
            printf("Ingrese el anio que desea buscar \n");
            scanf("%d",&anio);
            busquedaAnio(archivoAlumnos,anio);

            break;
        }
        case 9:
        {
            stAlumno unArregloDeAlumnos[50];
            printf("Ingrese por el anio que desea filtrar \n");
            scanf("%d",&filtrado);

            break;
        }
        case 10:
        {
            cantidadRegistros(archivoAlumnos);
            break;
        }


        }
        printf("Desea volver al menu principal? (s/n) \n");
        fflush(stdin);
        scanf("%c",&continuar);
        system("cls");
    }
    while(continuar=='s');
}
