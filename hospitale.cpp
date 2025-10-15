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

//-------------------------------------------

//3.Definir funciones 

//-------------------------------------------

//5.MODULO DE UTILIDADES Y HELPERS

//--------------------------------------------


//primero necesitamos una funcion para comparar los strings sin importar que tenga mayuscula o minuscula

int mi_strcasecmp(const char*s1,const char*s2){

    //esta funcion se necesita para buscar pacientes y doctores sin importar si esta escrito con mayuscula o minuscula
while(*s1 && *s2){
    char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
    char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
    if(c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
return *s1 - *s2;
}

//funcion para validar la fecha en YYYY-MM-DD

bool validarFecha(const char* fecha){
    int año, mes, dia;
    if(strlen(fecha)!=10){
        return false;
    }
//Para verificar el formato con guiones
    if(fecha[4]!='-' || fecha[7]!='-') {
        return false;
    }
//verificamos que el numero corresponda 
for(int i=0; i<10;i++) {
    if (i==4 || i==7 ) 
continue;//saltamos los guiones
    if (fecha[i] < '0' || fecha[i]>'9') {
    return false;
      }
}

//extraemos año,mes y dia 

año =    (fecha[0]-'0')* 1000 +
         (fecha[1]-'0')* 100 +
         (fecha[2]-'0')* 10 +
         (fecha[3]-'0');
mes =    (fecha[5]-'0')* 10 + (fecha[6]-'0');
dia =    (fecha[8]-'0')* 10 + (fecha[9]- '0');

 return true;
//validar rangos 

    if ( año < 1900 || año > 2100) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;

//verificar dias segun mes

if (mes==4 || mes==6 || mes==9 || mes==11) {
    if (dia>30) return false;
} else if (mes==2) {
    bool esBisiesto = (año % 4 == 0 && año % 100 != 0) || (año% 400 == 0);
        if (esBisiesto) {
            if (dia > 29) return false;
        } else {
            if (dia > 28) return false;
        }
       
    }
    
      return true;
}

//funcion para validar la hora en formato HH:MM

bool validarHora(const char* hora) {
    if (strlen(hora) != 5) return false;{
    }
    if (hora[2] != ':') return false;{
    }
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue; // saltar el ':'
        if (hora[i] < '0' || hora[i] > '9') {return false;
    }
    }
    int HH = (hora[0] - '0') * 10 + (hora[1] - '0');
    int MM = (hora[3] - '0') * 10 + (hora[4] - '0');
    if (HH < 0 || HH > 23) return false;
    if (MM < 0 || MM > 59) return false;
    return true;
}

//funcion para validar la cedula 
bool validarCedula(const char* cedula) {
    if (cedula == nullptr|| strlen (cedula) == 0 || strlen(cedula)>20){
        return false;
    }
    return true;
}

//funcion para validar el email
bool validarEmail(const char* email) {
    if(email==nullptr|| strlen (email)==0){\
        return false;
    }
    bool tienearroba=false;
    bool tienepunto=false;
    for(int i=0;email[i]!='0';i++){
        if(email[i]=='@'){
            tienearroba=true;
        } else if(email[i]=='.' && tienearroba){
            tienepunto=true;
        }
    }
    return tienearroba && tienepunto;
}

int compararFechas (const char* fecha1, const char* fecha2){
    //asumiendo el formato de YYYY-MM-DD
    for (int i=0; i<10; i++){
        if (fecha1[i] < fecha2[i]) return -1;
        if (fecha1[i] > fecha2[i]) return 1;
    }
    return 0; //son iguales
}


// =========================================================================
// PUNTO DE ENTRADA PRINCIPAL
// =========================================================================
int main() {
    iniciarSistema();
    return 0;
} 



