#include <iostream>
#include "hospital.hpp"
#include "paciente.hpp"
#include "doctor.hpp"
#include "citas.hpp"
#include "historialmedico.hpp"
#include "operacionespacientes.hpp"
#include "operacionesdoctores.hpp"
#include "operacionescitas.hpp"
#include "operacioneshistorial.hpp"
#include "gestorarchivos.hpp"
#include "constantes.hpp"
#include "validaciones.hpp"

using namespace std;

// Declaraciones de funciones
void mostrarMenuPrincipal();
void menuPacientes(Hospital& hospital);
void menuDoctores(Hospital& hospital);
void menuCitas(Hospital& hospital);
void menuMantenimiento(Hospital& hospital);
Paciente capturarDatosPaciente();
Doctor capturarDatosDoctor();
Cita capturarDatosCita();
Hospital inicializarHospital();

int main() {
    Hospital hospital = inicializarHospital();
    
    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                menuPacientes(hospital);
                break;
            case 2:
                menuDoctores(hospital);
                break;
            case 3:
                menuCitas(hospital);
                break;
            case 4:
                menuMantenimiento(hospital);
                break;
            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
        }
    } while (opcion != 5);
    
    return 0;
}

void mostrarMenuPrincipal() {
    cout << "\n╔══════════════════════════════════════╗" << endl;
    cout << "║   SISTEMA DE GESTIÓN HOSPITALARIA   ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║ 1. Gestión de Pacientes             ║" << endl;
    cout << "║ 2. Gestión de Doctores              ║" << endl;
    cout << "║ 3. Gestión de Citas                 ║" << endl;
    cout << "║ 4. Mantenimiento                    ║" << endl;
    cout << "║ 5. Salir                            ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    cout << "Seleccione una opción: ";
}

Hospital inicializarHospital() {
    Hospital hospital;
    ifstream archivo(FILE_HOSPITAL, ios::binary);
    if (!archivo.is_open()) {
        cout << "Inicializando sistema hospitalario por primera vez..." << endl;
        hospital.setNombre("Hospital Coco 2");
        hospital.setDireccion("");
        hospital.setTelefono("");
        
        // Inicializar archivos si no existen
        GestorArchivos::inicializarArchivo(FILE_PACIENTES);
        GestorArchivos::inicializarArchivo(FILE_DOCTORES);
        GestorArchivos::inicializarArchivo(FILE_CITAS);
        GestorArchivos::inicializarArchivo(FILE_HISTORIALES);
        GestorArchivos::guardarHospital(hospital);
        
        return hospital;
    }
    
    archivo.read(reinterpret_cast<char*>(&hospital), sizeof(Hospital));
    archivo.close();
    return hospital;
}

Paciente capturarDatosPaciente() {
    Paciente p;
    char buffer[100];
    
    cout << "Nombre: ";
    cin.getline(buffer, 100);
    p.setNombre(buffer);
    
    cout << "Apellido: ";
    cin.getline(buffer, 100);
    p.setApellido(buffer);
    
    cout << "Cédula: ";
    cin.getline(buffer, 100);
    p.setCedula(buffer);
    
    cout << "Edad: ";
    int edad;
    cin >> edad;
    p.setEdad(edad);
    GestorArchivos::limpiarBuffer();
    
    cout << "Sexo (M/F): ";
    char sexo;
    cin >> sexo;
    p.setSexo(sexo);
    GestorArchivos::limpiarBuffer();
    
    cout << "Teléfono (opcional): ";
    cin.getline(buffer, 100);
    p.setTelefono(buffer);
    
    cout << "Email (opcional): ";
    cin.getline(buffer, 100);
    p.setEmail(buffer);
    
    return p;
}

Doctor capturarDatosDoctor() {
    Doctor d;
    char buffer[100];
    
    cout << "Nombre: ";
    cin.getline(buffer, 100);
    d.setNombre(buffer);
    
    cout << "Apellido: ";
    cin.getline(buffer, 100);
    d.setApellido(buffer);
    
    cout << "Cédula profesional: ";
    cin.getline(buffer, 100);
    
    cout << "Especialidad: ";
    cin.getline(buffer, 100);
    d.setEspecialidad(buffer);
    
    cout << "Años de experiencia: ";
    int experiencia;
    cin >> experiencia;
    d.setAniosExperiencia(experiencia);
    GestorArchivos::limpiarBuffer();
    
    cout << "Costo de consulta: ";
    float costo;
    cin >> costo;
    d.setCostoConsulta(costo);
    GestorArchivos::limpiarBuffer();
    
    cout << "Teléfono (opcional): ";
    cin.getline(buffer, 100);
    d.setTelefono(buffer);
    
    return d;
}

Cita capturarDatosCita() {
    Cita c;
    char buffer[100];
    
    cout << "ID del Paciente: ";
    int pacienteID;
    cin >> pacienteID;
    c.setPacienteID(pacienteID);
    GestorArchivos::limpiarBuffer();
    
    cout << "ID del Doctor: ";
    int doctorID;
    cin >> doctorID;
    c.setDoctorID(doctorID);
    GestorArchivos::limpiarBuffer();
    
    cout << "Fecha (YYYY-MM-DD): ";
    cin.getline(buffer, 100);
    c.setFecha(buffer);
    
    cout << "Hora (HH:MM): ";
    cin.getline(buffer, 100);
    c.setHora(buffer);
    
    cout << "Motivo: ";
    cin.getline(buffer, 100);
    c.setMotivo(buffer);
    
    return c;
}

void menuPacientes(Hospital& hospital) {n    int opcion;n    do {n        cout << "\\n=== GESTION DE PACIENTES ===" << endl;n        cout << "1. Registrar paciente" << endl;n        cout << "2. Buscar por ID" << endl;n        cout << "3. Buscar por cedula" << endl;n        cout << "4. Listar todos" << endl;n        cout << "5. Actualizar" << endl;n        cout << "6. Eliminar" << endl;n        cout << "0. Volver" << endl;n        cout << "Opcion: ";n        cin >> opcion;n        GestorArchivos::limpiarBuffer();n        n        switch(opcion) {n            case 1: cout << "Registrar paciente - En desarrollo" << endl; break;n            case 2: cout << "Buscar por ID - En desarrollo" << endl; break;n            case 3: cout << "Buscar por cedula - En desarrollo" << endl; break;n            case 4: OperacionesPacientes::listarTodosPacientes(); break;n            case 5: cout << "Actualizar paciente - En desarrollo" << endl; break;n            case 6: cout << "Eliminar paciente - En desarrollo" << endl; break;n            case 0: cout << "Volviendo..." << endl; break;n            default: cout << "Opcion invalida" << endl;n        }n    } while(opcion != 0);n}

void menuDoctores(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTIÓN DE DOCTORES ===" << endl;
        cout << "1. Registrar nuevo doctor" << endl;
        cout << "2. Buscar doctor por ID" << endl;
        cout << "3. Listar todos los doctores" << endl;
        cout << "4. Volver" << endl;
        cout << "Opción: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1: {
                Doctor nuevo = capturarDatosDoctor();
                if (OperacionesDoctores::agregarDoctor(nuevo)) {
                    hospital.incrementarDoctoresRegistrados();
                    GestorArchivos::guardarHospital(hospital);
                    cout << "Doctor registrado exitosamente!" << endl;
                } else {
                    cout << "Error al registrar doctor" << endl;
                }
                break;
            }
            case 2: {
                int id;
                cout << "ID del doctor: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Doctor d = OperacionesDoctores::buscarDoctorPorID(id);
                if (d.getId() != 0) {
                    cout << "\n=== DATOS DEL DOCTOR ===" << endl;
                    cout << "ID: " << d.getId() << endl;
                    cout << "Nombre: " << d.getNombre() << " " << d.getApellido() << endl;
                    cout << "Especialidad: " << d.getEspecialidad() << endl;
                    cout << "Años experiencia: " << d.getAniosExperiencia() << endl;
                    cout << "Costo consulta: " << d.getCostoConsulta() << endl;
                    cout << "Teléfono: " << d.getTelefono() << endl;
                } else {
                    cout << "Doctor no encontrado" << endl;
                }
                break;
            }
            case 3:
                OperacionesDoctores::listarTodosDoctores();
                break;
            case 4:
                cout << "Volviendo..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
        }
    } while(opcion != 4);
}

void menuCitas(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTIÓN DE CITAS ===" << endl;
        cout << "1. Agendar nueva cita" << endl;
        cout << "2. Buscar cita por ID" << endl;
        cout << "3. Volver" << endl;
        cout << "Opción: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1: {
                Cita nueva = capturarDatosCita();
                
                // Verificar que paciente y doctor existen
                Paciente paciente = OperacionesPacientes::buscarPacientePorID(nueva.getPacienteID());
                Doctor doctor = OperacionesDoctores::buscarDoctorPorID(nueva.getDoctorID());
                
                if (paciente.getId() == 0) {
                    cout << "Error: Paciente no encontrado" << endl;
                    break;
                }
                
                if (doctor.getId() == 0) {
                    cout << "Error: Doctor no encontrado" << endl;
                    break;
                }
                
                if (!Validaciones::validarFecha(nueva.getFecha())) {
                    cout << "Error: Fecha no válida" << endl;
                    break;
                }
                
                if (!Validaciones::validarHora(nueva.getHora())) {
                    cout << "Error: Hora no válida" << endl;
                    break;
                }
                
                if (OperacionesCitas::agregarCita(nueva)) {
                    hospital.incrementarCitasAgendadas();
                    GestorArchivos::guardarHospital(hospital);
                    cout << "Cita agendada correctamente" << endl;
                } else {
                    cout << "Error al agendar cita" << endl;
                }
                break;
            }
            case 2: {
                int id;
                cout << "ID de la cita: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Cita c = OperacionesCitas::buscarCitaPorID(id);
                if (c.getId() != 0) {
                    cout << "\n=== DATOS DE LA CITA ===" << endl;
                    cout << "ID: " << c.getId() << endl;
                    cout << "Paciente ID: " << c.getPacienteID() << endl;
                    cout << "Doctor ID: " << c.getDoctorID() << endl;
                    cout << "Fecha: " << c.getFecha() << endl;
                    cout << "Hora: " << c.getHora() << endl;
                    cout << "Motivo: " << c.getMotivo() << endl;
                    cout << "Estado: " << c.getEstado() << endl;
                } else {
                    cout << "Cita no encontrada" << endl;
                }
                break;
            }
            case 3:
                cout << "Volviendo..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
        }
    } while(opcion != 3);
}

void menuMantenimiento(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== MANTENIMIENTO ===" << endl;
        cout << "1. Verificar archivos" << endl;
        cout << "2. Verificar referencias" << endl;
        cout << "3. Compactar pacientes" << endl;
        cout << "4. Compactar doctores" << endl;
        cout << "5. Compactar citas" << endl;
        cout << "6. Compactar historiales" << endl;
        cout << "7. Hacer respaldo" << endl;
        cout << "8. Restaurar respaldo" << endl;
        cout << "9. Ver estadisticas" << endl;
        cout << "10. Volver" << endl;
        cout << "Opción: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                GestorArchivos::verificarIntegridadArchivos();
                break;
            case 2:
                GestorArchivos::verificarIntegridadReferencial();
                break;
            case 3:
                GestorArchivos::compactarArchivoPacientes();
                break;
            case 4:
                GestorArchivos::compactarArchivoDoctores();
                break;
            case 5:
                GestorArchivos::compactarArchivoCitas();
                break;
            case 6:
                GestorArchivos::compactarArchivoHistoriales();
                break;
            case 7:
                GestorArchivos::hacerRespaldo();
                break;
            case 8:
                GestorArchivos::restaurarRespaldo();
                break;
            case 9:
                hospital.mostrarEstadisticas();
                GestorArchivos::mostrarEstadisticas();
                break;
            case 10:
                cout << "Volviendo..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
        }
    } while(opcion != 10);
}