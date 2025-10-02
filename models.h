#ifndef MODELS_H
#define MODELS_H

#include <string>

struct Autor {
    int id; //PK -> id del autor
    std::string Nombre;
};

struct Libro {
    int id; //PK -< id del libro 
    std::string Titulo;
    int anio_publicacion;
    std::string ISBN; //UNIQUE
    std::string nombre_autor;
    int id_Autor; //FK -> Autor.id 
};

struct Estudiante {
    int id; //PK -> id del estudiante
    std::string Nombre;
    std::string apellido;
    std::string carrera;   
};

struct Prestamo {
    int id; //PK, id del prestamo
    std::string Fecha_Prestamo; 
    std::string Fecha_Devolucion; //Can be empty if not returned yet
    std::string Estado;  // "activo" ó "Devuelto"
    int id_Libro;  //FK Libro.id
    int id_Estudiante; //FK -> Estudiante.id
};

#endif