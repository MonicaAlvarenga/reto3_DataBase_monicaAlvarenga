#include <vector>
#include "models.h"
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <fstream>

std::vector<Autor> autores; 
std::vector<Libro> libros;
std::vector<Estudiante> estudiantes;
std::vector<Prestamo> prestamos;

// ===== Funciones =====

// Agregar libro
void agregarLibro() {
    Libro l;
    // Generar ID del libro automáticamente
    l.id = libros.empty() ? 1 : libros.back().id + 1;

    std::cout << "Ingrese el título del libro: ";
    std::getline(std::cin, l.Titulo);

    std::string nombreAutor;
    std::cout << "Ingrese el nombre del autor: ";
    std::getline(std::cin, nombreAutor);

    std::cout << "Ingrese el año de publicación: ";
    std::cin >> l.anio_publicacion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Ingrese el ISBN: ";
    std::getline(std::cin, l.ISBN);

    // Buscar si el autor ya existe
    int autorID = -1;
    for (const auto &a : autores) {
        if (a.Nombre == nombreAutor) {
            autorID = a.id;
            break;
        }
    }

    // Si no existe, crearlo automáticamente
    if (autorID == -1) {
        Autor a;
        a.id = autores.empty() ? 1 : autores.back().id + 1;
        a.Nombre = nombreAutor;
        autores.push_back(a);
        autorID = a.id;
    }

    l.id_Autor = autorID;

    libros.push_back(l);
    std::cout << "Libro agregado con ID " << l.id << "\n";
}

// Listar libros mostrando el nombre del autor
void listarLibros() {
    if (libros.empty()) {
        std::cout << "No hay libros registrados.\n";
        return;
    }
    std::cout << "\n--- Lista de Libros ---\n";
    for (const auto &l : libros) {
        std::string nombreAutor;
        for (const auto &a : autores) {
            if (a.id == l.id_Autor) {
                nombreAutor = a.Nombre;
                break;
            }
        }
        std::cout << "ID: " << l.id
                  << " | Titulo: " << l.Titulo
                  << " | Año: " << l.anio_publicacion
                  << " | Autor: " << nombreAutor
                  << " | ISBN: " << l.ISBN << "\n";
    }
}

// Agregar estudiante
void agregarEstudiante() {
    Estudiante e;
    e.id = estudiantes.empty() ? 1 : estudiantes.back().id + 1;

    std::cout << "Ingrese nombre del estudiante: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, e.Nombre);

    std::cout << "Ingrese apellido del estudiante: ";
    std::getline(std::cin, e.apellido);

    std::cout << "Ingrese la carrera del estudiante: ";
    std::getline(std::cin, e.carrera);

    estudiantes.push_back(e);
    std::cout << "Estudiante agregado con ID " << e.id << "\n";
}

// Pedir un libro prestado
void prestarLibro() {
    Prestamo p;
    p.id = prestamos.empty() ? 1 : prestamos.back().id + 1;

    std::cout << "Ingrese ID del estudiante: ";
    std::cin >> p.id_Estudiante;
    std::cout << "Ingrese ID del libro: ";
    std::cin >> p.id_Libro;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    prestamos.push_back(p);
    std::cout << "Prestamo registrado con ID " << p.id << "\n";
}

// Buscar préstamos por estudiante
void buscarPrestamosPorEstudiante() {
    int idE;
    std::cout << "Ingrese el ID del estudiante: ";
    std::cin >> idE;

    std::cout << "--- Prestamos del estudiante " << idE << " ---\n";
    for (const auto &p : prestamos) {
        if (p.id_Estudiante == idE) {
            std::cout << "Prestamo ID: " << p.id
                      << " | Libro ID: " << p.id_Libro << "\n";
        }
    }
}

// Devolver libro
void devolverLibro() {
    int idPrestamo;
    std::cout << "Ingrese el ID del prestamo a devolver: ";
    std::cin >> idPrestamo;

    for (auto it = prestamos.begin(); it != prestamos.end(); ++it) {
        if (it->id == idPrestamo) {
            prestamos.erase(it);
            std::cout << "Prestamo devuelto correctamente.\n";
            return;
        }
    }
    std::cout << "No se encontró un préstamo con ese ID.\n";
}

// Guardar libros
void guardarLibros(const std::string &filename = "libros.txt") {
    std::ofstream f(filename);
    for (const auto &l : libros) {
        f << l.id << ',' 
          << l.Titulo << ',' 
          << l.anio_publicacion << ',' 
          << l.ISBN << ',' 
          << l.id_Autor << '\n';
    }
    f.close();
}

// Cargar libros
void cargarLibros(const std::string &filename = "libros.txt") {
    std::ifstream f(filename);
    if (!f) return;

    libros.clear();
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Libro l;
        std::string temp;

        std::getline(ss, temp, ','); l.id = std::stoi(temp);
        std::getline(ss, l.Titulo, ',');
        std::getline(ss, temp, ','); l.anio_publicacion = std::stoi(temp);
        std::getline(ss, l.ISBN, ',');
        std::getline(ss, temp, ','); l.id_Autor = std::stoi(temp);

        libros.push_back(l);
    }
    f.close();
}

// Guardar todos los datos
void guardarTodos() {
    guardarLibros();
    std::cout << "Datos guardados.\n";
}

// Cargar todos los datos
void cargarTodos() {
    cargarLibros();
    std::cout << "Datos cargados.\n";
}

// ===== Main =====
int main() {
    cargarTodos();
    bool run = true;

    while (run) {
        std::cout <<"\n---Menú Biblioteca---\n";
        std::cout <<"(1) Agregar libro \n";
        std::cout <<"(2) Listar libros\n";
        std::cout <<"(3) Agregar estudiante\n";
        std::cout << "4) Prestar libro\n";
        std::cout << "5) Buscar prestamos por estudiante\n";
        std::cout << "6) Devolver libro\n";
        std::cout << "7) Guardar datos\n";
        std::cout << "8) Cargar datos\n";
        std::cout << "0) Salir\n";
        std::cout << "Elige una opcion: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: agregarLibro(); break;
            case 2: listarLibros(); break;
            case 3: agregarEstudiante(); break;
            case 4: prestarLibro(); break;
            case 5: buscarPrestamosPorEstudiante(); break;
            case 6: devolverLibro(); break;
            case 7: guardarTodos(); break;
            case 8: cargarTodos(); break;
            case 0: 
                guardarTodos(); // guarda al salir
                run = false; 
                break;
            default: std::cout <<"opción no valida, ingrese otro numero\n";
        }
    }
    return 0;
}
