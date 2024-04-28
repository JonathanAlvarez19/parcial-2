#include <iostream>
#include <string>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string apellido;
    float notas[4];
};

void ingresarEstudiantes(Estudiante* estudiantes, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Ingrese ID del estudiante: ";
        cin >> (estudiantes + i)->id;
        cout << "Ingrese nombre del estudiante: ";
        cin >> (estudiantes + i)->nombre;
        cout << "Ingrese apellido del estudiante: ";
        cin >> (estudiantes + i)->apellido;
        cout << "Ingrese las 4 notas del estudiante: ";
        for (int j = 0; j < 4; ++j) {
            cin >> (estudiantes + i)->notas[j];
        }
    }
}

void calcularPromedio(Estudiante* estudiantes, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        float suma = 0;
        for (int j = 0; j < 4; ++j) {
            suma += (estudiantes + i)->notas[j];
        }
        float promedio = suma / 4.0;
        cout << "El promedio del estudiante " << (estudiantes + i)->nombre << " " << (estudiantes + i)->apellido << " es: " << promedio << endl;
        if (promedio > 60) {
            cout << "El estudiante ha aprobado." << endl;
        } else {
            cout << "El estudiante ha reprobado." << endl;
        }
    }
}

int main() {
    int cantidad;
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> cantidad;
    Estudiante* estudiantes = new Estudiante[cantidad];
    ingresarEstudiantes(estudiantes, cantidad);
    calcularPromedio(estudiantes, cantidad);
    delete[] estudiantes;
    return 0;
}

