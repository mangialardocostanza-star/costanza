#include "hospital/hospital.hpp"
#include "pacientes/operacionespacientes.hpp"
#include "doctores/operacionesdoctores.hpp"
#include "citas/operacionescitas.hpp"
#include "persistencia/gestorarchivos.hpp"
#include "persistencia/constantes.hpp"
#include "utilidades/validaciones.hpp"

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
    cout << "\n=== SISTEMA HOSPITALARIO ===" << endl;
    cout << "1. Pacientes" << endl;
    cout << "2. Doctores" << endl;
    cout << "3. Citas" << endl;
    cout << "4. Mantenimiento" << endl;
    cout << "5. Salir" << endl;
    cout << "Opcion: ";
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

void menuPacientes(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTION DE PACIENTES ===" << endl;
        cout << "1. Registrar paciente" << endl;
        cout << "2. Buscar por ID" << endl;
        cout << "3. Buscar por cedula" << endl;
        cout << "4. Listar todos" << endl;
        cout << "5. Actualizar" << endl;
        cout << "6. Eliminar" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                cout << "Registrar paciente - En desarrollo" << endl;
                break;
            case 2:
                cout << "Buscar por ID - En desarrollo" << endl;
                break;
            case 3:
                cout << "Buscar por cedula - En desarrollo" << endl;
                break;
            case 4:
                OperacionesPacientes::listarTodosPacientes();
                break;
            case 5:
                cout << "Actualizar paciente - En desarrollo" << endl;
                break;
            case 6:
                cout << "Eliminar paciente - En desarrollo" << endl;
                break;
            case 0:
                cout << "Volviendo..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    } while(opcion != 0);
}
void menuDoctores(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTION DE DOCTORES ===" << endl;
        cout << "1. Registrar doctor" << endl;
        cout << "2. Buscar por ID" << endl;
        cout << "3. Listar todos" << endl;
        cout << "4. Listar por especialidad" << endl;
        cout << "5. Actualizar" << endl;
        cout << "6. Eliminar" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                cout << "Registrar doctor - En desarrollo" << endl;
                break;
            case 2:
                cout << "Buscar doctor por ID - En desarrollo" << endl;
                break;
            case 3:
                OperacionesDoctores::listarTodosDoctores();
                break;
            case 4:
                cout << "Listar por especialidad - En desarrollo" << endl;
                break;
            case 5:
                cout << "Actualizar doctor - En desarrollo" << endl;
                break;
            case 6:
                cout << "Eliminar doctor - En desarrollo" << endl;
                break;
            case 0:
                cout << "Volviendo..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    } while(opcion != 0);
}
void menuCitas(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTION DE CITAS ===" << endl;
        cout << "1. Agendar cita" << endl;
        cout << "2. Buscar cita" << endl;
        cout << "3. Cancelar cita" << endl;
        cout << "4. Atender cita" << endl;
        cout << "5. Listar citas pendientes" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                cout << "Agendar cita - En desarrollo" << endl;
                break;
            case 2:
                cout << "Buscar cita - En desarrollo" << endl;
                break;
            case 3:
                cout << "Cancelar cita - En desarrollo" << endl;
                break;
            case 4:
                cout << "Atender cita - En desarrollo" << endl;
                break;
            case 5:
                cout << "Listar citas pendientes - En desarrollo" << endl;
                break;
            case 0:
                cout << "Volviendo..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    } while(opcion != 0);
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