#include<iostream>
#include <cstring>
#include <ctime> 
#include <iomanip>
#include <cctype>

using namespace std;

//--------------------------------

//1.MODELO DE DATOS

struct HistorialMedico {
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;
};

struct Cita {
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];
    char observaciones[200];
    bool atendida;
};

struct Paciente {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    char sexo;
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    
    HistorialMedico* historial;
    int cantidadConsultas;
    int capacidadHistorial;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    char alergias[500];
    char observaciones[500];
    
    bool activo;
};

struct Doctor {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    
    int* pacientesAsignados;
    int cantidadPacientes;
    int capacidadPacientes;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    bool disponible;
};

struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];
    
    Paciente* pacientes;
    int cantidadPacientes;
    int capacidadPacientes;
    
    Doctor* doctores;
    int cantidadDoctores;
    int capacidadDoctores;
    
    Cita* citas;
    int cantidadCitas;
    int capacidadCitas;
    
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;
};

//--------------------------------

//2.PROTOTIPOS DE FUNCIONES

//---------------------------------

//1.funciones auxiliares

int mi_strcasecmp(const char *s1, const char *s2);
bool validarFecha(const char* fecha);
bool validarHora(const char* hora);
bool validarCedula(const char* cedula);
bool validarEmail(const char* email);
int compararFechas(const char* fecha1, const char* fecha2);
void limpiarBuffer();

// --- Gestión de Memoria / Utilidades ---
Hospital* inicializarHospital(const char* nombre);
void destruirHospital(Hospital* hospital);
void redimensionarArrayPacientes(Hospital* hospital);
void redimensionarArrayDoctores(Hospital* hospital);
void redimensionarArrayCitas(Hospital* hospital);
void redimensionarArrayInt(int** array, int& cantidad, int& capacidad);
void redimensionarHistorial(Paciente* paciente);
bool removerIdDeArray(int* array, int& cantidad, int idARemover);

// --- Módulo de Pacientes (CRUD) ---
Paciente* crearPaciente(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, int edad, char sexo);
Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedula);
Paciente* buscarPacientePorId(Hospital* hospital, int id);
Paciente** buscarPacientesPorNombre(Hospital* hospital, const char* nombre, int* cantidad);
bool actualizarPaciente(Hospital* hospital, int id);
bool eliminarPaciente(Hospital* hospital, int id);
void listarPacientes(Hospital* hospital);

// --- Historial Médico ---
void agregarConsultaAlHistorial(Paciente* paciente, HistorialMedico consulta);
HistorialMedico* obtenerHistorialCompleto(Paciente* paciente, int* cantidad);
void mostrarHistorialMedico(Paciente* paciente);

// --- Módulo de Doctores (CRUD) ---
Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, const char* especialidad, int aniosExperiencia, float costoConsulta);
Doctor* buscarDoctorPorId(Hospital* hospital, int id);
Doctor** buscarDoctoresPorEspecialidad(Hospital* hospital, const char* especialidad, int* cantidad);
bool asignarPacienteADoctor(Doctor* doctor, int idPaciente);
bool removerPacienteDeDoctor(Doctor* doctor, int idPaciente);
void listarDoctores(Hospital* hospital);
bool eliminarDoctor(Hospital* hospital, int id);

// --- Módulo de Citas (CRUD) ---
Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor, const char* fecha, const char* hora, const char* motivo);
bool cancelarCita(Hospital* hospital, int idCita);
bool atenderCita(Hospital* hospital, int idCita, const char* diagnostico, const char* tratamiento, const char* medicamentos);
Cita** obtenerCitasDePaciente(Hospital* hospital, int idPaciente, int* cantidad);
void listarCitasPendientes(Hospital* hospital);
bool verificarDisponibilidad(Hospital* hospital, int idDoctor, const char* fecha, const char* hora);

// --- Interfaz de Usuario ---
void iniciarSistema();
void mostrarMenuPrincipal();
void menuPacientes(Hospital* hospital);
void menuDoctores(Hospital* hospital);
void menuCitas(Hospital* hospital);

