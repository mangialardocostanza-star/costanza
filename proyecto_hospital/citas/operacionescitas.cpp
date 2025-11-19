#include "operacionescitas.hpp"
#include "citas.hpp"
#include "../persistencia/constantes.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

bool OperacionesCitas::agregarCita(Cita& nuevaCita) {
    // Buscar si ya existe una cita con el mismo ID
    Cita citaExistente = buscarCitaPorID(nuevaCita.getId());
    if (citaExistente.getId() != -1) {
        mostrarError("Ya existe una cita con ese ID");
        return false;
    }

    // Abrir archivo en modo append
    ofstream archivo(FILE_CITAS, ios::binary | ios::app);
    if (!archivo) {
        mostrarError("Error al abrir el archivo de citas");
        return false;
    }

    // Escribir la nueva cita
    archivo.write(reinterpret_cast<char*>(&nuevaCita), sizeof(Cita));
    archivo.close();

    if (!archivo.good()) {
        mostrarError("Error al escribir la cita");
        return false;
    }

    mostrarExito("Cita agregada correctamente");
    return true;
}

Cita OperacionesCitas::buscarCitaPorID(int id) {
    Cita cita;
    
    ifstream archivo(FILE_CITAS, ios::binary);
    if (!archivo) {
        Cita citaVacia;
        return citaVacia;
    }

    while (archivo.read(reinterpret_cast<char*>(&cita), sizeof(Cita))) {
        if (cita.getId() == id && !cita.getEliminado()) {
            archivo.close();
            return cita;
        }
    }

    archivo.close();
    Cita citaVacia;
    return citaVacia;
}

int OperacionesCitas::buscarIndiceCitaPorID(int id) {
    Cita cita;
    int indice = 0;

    ifstream archivo(FILE_CITAS, ios::binary);
    if (!archivo) {
        return -1;
    }

    while (archivo.read(reinterpret_cast<char*>(&cita), sizeof(Cita))) {
        if (cita.getId() == id && !cita.getEliminado()) {
            archivo.close();
            return indice;
        }
        indice++;
    }

    archivo.close();
    return -1;
}

bool OperacionesCitas::actualizarCita(Cita& citaModificada) {
    int indice = buscarIndiceCitaPorID(citaModificada.getId());
    if (indice == -1) {
        mostrarError("Cita no encontrada");
        return false;
    }

    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    if (!archivo) {
        mostrarError("Error al abrir el archivo de citas");
        return false;
    }

    // Posicionar en la cita a modificar
    archivo.seekp(indice * sizeof(Cita));
    archivo.write(reinterpret_cast<char*>(&citaModificada), sizeof(Cita));
    archivo.close();

    if (!archivo.good()) {
        mostrarError("Error al actualizar la cita");
        return false;
    }

    mostrarExito("Cita actualizada correctamente");
    return true;
}

bool OperacionesCitas::eliminarCita(int id) {
    Cita cita = buscarCitaPorID(id);
    if (cita.getId() == -1) {
        mostrarError("Cita no encontrada");
        return false;
    }

    // Marcar como eliminado (soft delete)
    cita.setEliminado(true);
    cita.setFechaModificacion(time(nullptr));

    return actualizarCita(cita);
}

bool OperacionesCitas::cancelarCita(int idCita) {
    Cita cita = buscarCitaPorID(idCita);
    if (cita.getId() == -1) {
        mostrarError("Cita no encontrada");
        return false;
    }

    // Verificar que la cita no esté ya cancelada
    if (strcmp(cita.getEstado(), "CANCELADA") == 0) {
        mostrarError("La cita ya está cancelada");
        return false;
    }

    // Cambiar estado a CANCELADA
    cita.setEstado("CANCELADA");
    cita.setFechaModificacion(time(nullptr));

    // Actualizar la cita en el archivo
    return actualizarCita(cita);
}

bool OperacionesCitas::atenderCita(int idCita, const char* diagnostico, const char* tratamiento, 
                          const char* medicamentos, float costo) {
    Cita cita = buscarCitaPorID(idCita);
    if (cita.getId() == -1) {
        mostrarError("Cita no encontrada");
        return false;
    }

    // Verificar que la cita no esté cancelada
    if (strcmp(cita.getEstado(), "CANCELADA") == 0) {
        mostrarError("No se puede atender una cita cancelada");
        return false;
    }

    // Actualizar información de la consulta
    cita.setDiagnostico(diagnostico);
    cita.setTratamiento(tratamiento);
    cita.setMedicamentos(medicamentos);
    cita.setCosto(costo);
    cita.setEstado("ATENDIDA");
    cita.setAtendida(true);
    cita.setFechaModificacion(time(nullptr));

    // Actualizar la cita en el archivo
    return actualizarCita(cita);
}

void OperacionesCitas::mostrarError(const char* mensaje) {
    cout << "\033[1;31mError: " << mensaje << "\033[0m" << endl;
}

void OperacionesCitas::mostrarExito(const char* mensaje) {
    cout << "\033[1;32m" << mensaje << "\033[0m" << endl;
}