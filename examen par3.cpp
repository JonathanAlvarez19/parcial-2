#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    string apellido;
    float notas[4];
    float promedio;
    string resultado;
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
        float suma = 0;
        for (int j = 0; j < 4; ++j) {
            suma += (estudiantes + i)->notas[j];
        }
        (estudiantes + i)->promedio = suma / 4.0;
        if ((estudiantes + i)->promedio > 60) {
            (estudiantes + i)->resultado = "Aprobado";
        } else {
            (estudiantes + i)->resultado = "Reprobado";
        }
    }
}

void guardarEstudiantesEnArchivo(Estudiante* estudiantes, int cantidad) {
    ofstream archivo("notas.dat", ios::binary | ios::app);
    if (archivo.is_open()) {
        for (int i = 0; i < cantidad; ++i) {
            archivo.write(reinterpret_cast<char*>(&estudiantes[i]), sizeof(Estudiante));
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void leerEstudiantesDeArchivo() {
    ifstream archivo("notas.dat", ios::binary);
    if (archivo.is_open()) {
        Estudiante estudiante;
        while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
            cout << "ID: " << estudiante.id << endl;
            cout << "Nombre: " << estudiante.nombre << " " << estudiante.apellido << endl;
            cout << "Notas: ";
            for (int i = 0; i < 4; ++i) {
                cout << estudiante.notas[i] << " ";
            }
            cout << endl;
            cout << "Promedio: " << estudiante.promedio << endl;
            cout << "Resultado: " << estudiante.resultado << endl;
            cout << "---------------------------------------" << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void actualizarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante que desea actualizar: ";
    cin >> id;
    fstream archivo("notas.dat", ios::binary | ios::in | ios::out);
    if (archivo.is_open()) {
        Estudiante estudiante;
        bool encontrado = false;
        while (!encontrado && archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
            if (estudiante.id == id) {
                cout << "Ingrese las nuevas notas del estudiante: ";
                for (int i = 0; i < 4; ++i) {
                    cin >> estudiante.notas[i];
                }
                float suma = 0;
                for (int i = 0; i < 4; ++i) {
                    suma += estudiante.notas[i];
                }
                estudiante.promedio = suma / 4.0;
                if (estudiante.promedio > 60) {
                    estudiante.resultado = "Aprobado";
                } else {
                    estudiante.resultado = "Reprobado";
                }
                archivo.seekp(-static_cast<int>(sizeof(Estudiante)), ios::cur);
                archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "Estudiante no encontrado." << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void eliminarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante que desea eliminar: ";
    cin >> id;
    ifstream archivoEntrada("notas.dat", ios::binary);
    if (archivoEntrada.is_open()) {
        ofstream archivoTemporal("temp.dat", ios::binary);
        Estudiante estudiante;
        while (archivoEntrada.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
            if (estudiante.id != id) {
                archivoTemporal.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
            }
        }
        archivoEntrada.close();
        archivoTemporal.close();
        remove("notas.dat");
        rename("temp.dat", "notas.dat");
        cout << "Estudiante eliminado exitosamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

int main() {
    int opcion;
    do {
        cout << "MENU" << endl;
        cout << "1. Ingresar estudiantes" << endl;
        cout << "2. Mostrar estudiantes" << endl;
        cout << "3. Actualizar notas de estudiante" << endl;
        cout << "4. Eliminar estudiante" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:{
			
                int cantidad;
                
                cout << "Ingrese la cantidad de estudiantes: ";
                cin >> cantidad;
                Estudiante* estudiantes = new Estudiante[cantidad];
                ingresarEstudiantes(estudiantes, cantidad);
                guardarEstudiantesEnArchivo(estudiantes, cantidad);
                delete[] estudiantes;
                
            	break;
            	}
            case 2:
                leerEstudiantesDeArchivo();
                break;
            case 3:
                actualizarEstudiante();
                break;
            case 4:
                eliminarEstudiante();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);
    return 0;
}

