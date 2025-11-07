#include<iostream>
#include <cstring>
#include <ctime> 
#include <iomanip>
#include <cctype>
#include<fstream>
#include<cstddef> //para tipos estadar como size_t
#include<limits>//para numeric_limits
using namespace std;


//0. ESTRUCTURA PARA ARCHIVOS BINARIOS
// Estructura que va al inicio de cada archivo .bin para saber cuántos datos hay y el próximo ID.
struct ArchivoHeader {
    int cantidadRegistros;
    int siguienteId;
    int registrosActivos;
    int version;
};
//--------------------------------

//1.MODELO DE DATOS

// Estructura HistorialMedico (archivo: historiales.bin)

struct HistorialMedico {
    int id;
    int idPaciente;
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;

     //navegacion enlazada 
    int siguienteConsultaId;
    //Metadata 
    bool eliminado;
    time_t fecharegistro;
};

// Estructura Cita (archivo: citas.bin)

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

    //Referencia del historial
    int consultaID;
    //Metadata 
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

   
};
// Estructura Paciente (archivo: pacientes.bin)

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
    char alergias[500];
    char observaciones[500];
    bool activo;

    //indices para relaciones 

    int cantidadConsultas;
    int primerConsultaID;
    int cantidadCitas;
    int citasIDs [20];

    //Metadata 
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
};
// Estructura Doctor (archivo: doctores.bin)

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
    bool disponible;

    //relaciones con array fijos 
    int CantidadPacientes;
    int pacientesIDs[50];
    int CantidadCitas;
    int citasIDs[30];

    //Metadata
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
};
// Estructura Hospital (archivo: hospital.bin) - Guarda contadores y datos generales

struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];
    
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;

    // Estadísticas
    int totalPacientesRegistrados;
    int totalDoctoresRegistrados;
    int totalCitasAgendadas;
    int totalConsultasRealizadas;

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
void mostrarError(const char* mensaje);
void mostrarExito(const char* mensaje);
void pausar();

//gestion de archivos binarios 


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

//funcion para limpiar buffer de entrada
void limpiarBuffer() {
    while (cin.get() != '\n');
}


//--------------------------------------------

//Gestion de memoria / utilidades

//--------------------------------------------
Hospital*inicializarHospital(const char* nombre){
    Hospital*hospital =new Hospital;
// copiamos la info basica
    strncpy(hospital->nombre,nombre,99);
    hospital->nombre[99]='\0' ;
    hospital->direccion[0]='\0' ;
    hospital->telefono[0]='\0' ;
    
    //inicilizar arrays de pacientes
    hospital->capacidadPacientes = 10;
    hospital->cantidadPacientes = 0;
    hospital->pacientes = new Paciente[hospital->capacidadPacientes];

    //inicilizar arrays de doctores
    hospital->capacidadDoctores = 10;
    hospital->cantidadDoctores = 0;
    hospital->doctores = new Doctor[hospital->capacidadDoctores];

    //inicilizar arrays de citas
    hospital->capacidadCitas = 20;
    hospital->cantidadCitas = 0;
    hospital->citas = new Cita[hospital->capacidadCitas];

    //inicilizar ids
    hospital->siguienteIdPaciente = 1;
    hospital->siguienteIdDoctor = 1;
    hospital->siguienteIdCita = 1;
    hospital->siguienteIdConsulta = 1;

    return hospital;

}

//Destruir hospital y liberar la memoria

void destruirHospital(Hospital*hospital){
    if(hospital==nullptr) return;
    //liberar memoria de pacientes
    for(int i=0; i<hospital->cantidadPacientes;i++){
        Paciente*paciente =&hospital->pacientes[i];
        if(paciente->historial!=nullptr){
            delete[] paciente->historial;
        }
        if(paciente->citasAgendadas!=nullptr){
            delete[] paciente->citasAgendadas;
        }
}
//liberar memoria de doctores
    for(int i=0; i<hospital->cantidadDoctores;i++){
        Doctor*doctor =&hospital->doctores[i];
        if(doctor->pacientesAsignados!=nullptr){
            delete[] doctor->pacientesAsignados;
        }
        if(doctor->citasAgendadas!=nullptr){
            delete[] doctor->citasAgendadas;
        }
    }
    //liberar arrays principales
    if(hospital->pacientes!=nullptr){ 
        delete[] hospital->pacientes;}
    if (hospital->doctores!=nullptr){
        delete[] hospital->doctores;}
    if(hospital->citas!=nullptr){
         delete[] hospital->citas;}
   
    //liberar estructura hospital
    delete hospital;
}

// Redimensionar array de pacientes
void redimensionarArrayPacientes(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadPacientes * 2;
    Paciente* nuevoArray = new Paciente[nuevaCapacidad];
    
    // Copiar pacientes existentes
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        nuevoArray[i] = hospital->pacientes[i];
    }
    
    // Liberar array antiguo y actualizar
    delete[] hospital->pacientes;
    hospital->pacientes = nuevoArray;
    hospital->capacidadPacientes = nuevaCapacidad;
}

// Redimensionar array de doctores
void redimensionarArrayDoctores(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadDoctores * 2;
    Doctor* nuevoArray = new Doctor[nuevaCapacidad];
    
    // Copiar doctores existentes
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        nuevoArray[i] = hospital->doctores[i];
    }
    
    // Liberar array antiguo y actualizar
    delete[] hospital->doctores;
    hospital->doctores = nuevoArray;
    hospital->capacidadDoctores = nuevaCapacidad;
}

// Redimensionar array de citas
void redimensionarArrayCitas(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadCitas * 2;
    Cita* nuevoArray = new Cita[nuevaCapacidad];
    
    // Copiar citas existentes
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        nuevoArray[i] = hospital->citas[i];
    }
    
    // Liberar array antiguo y actualizar
    delete[] hospital->citas;
    hospital->citas = nuevoArray;
    hospital->capacidadCitas = nuevaCapacidad;
}

 // Redimensionar array de enteros (genérico)
void redimensionarArrayInt(int** array, int& cantidad, int& capacidad) {
    int nuevaCapacidad = capacidad * 2;
    int* nuevoArray = new int[nuevaCapacidad];
    
    // Copiar elementos existentes
    for (int i = 0; i < cantidad; i++) {
        nuevoArray[i] = (*array)[i];
    }
    
    // Liberar array antiguo y actualizar
    delete[] *array;
    *array = nuevoArray;
    capacidad = nuevaCapacidad;
}

// Redimensionar historial médico de un paciente
void redimensionarHistorial(Paciente* paciente) {
    int nuevaCapacidad = paciente->capacidadHistorial * 2;
    HistorialMedico* nuevoArray = new HistorialMedico[nuevaCapacidad];
    
    // Copiar consultas existentes
    for (int i = 0; i < paciente->cantidadConsultas; i++) {
        nuevoArray[i] = paciente->historial[i];
    }
    
    // Liberar array antiguo y actualizar
    delete[] paciente->historial;
    paciente->historial = nuevoArray;
    paciente->capacidadHistorial = nuevaCapacidad;
}

// Remover ID de un array de enteros
bool removerIdDeArray(int* array, int& cantidad, int idARemover) {
    int indice = -1;
    
    // Buscar el ID
    for (int i = 0; i < cantidad; i++) {
        if (array[i] == idARemover) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) return false;
    
    // Mover elementos hacia adelante
    for (int i = indice; i < cantidad - 1; i++) {
        array[i] = array[i + 1];
    }
    
    cantidad--;
    return true;
}

// Función para copiar string (deep copy)
char* copiarString(const char* origen) {
    if (origen == nullptr) return nullptr;
    
    int longitud = strlen(origen);
    char* copia = new char[longitud + 1];
    strcpy(copia, origen);
    return copia;
}
// Función auxiliar para mostrar mensajes de error
void mostrarError(const char* mensaje) {
    cout << " Error: " << mensaje << endl;
}

// Función auxiliar para mostrar mensajes de éxito
void mostrarExito(const char* mensaje) {
    cout << "✅ " << mensaje << endl;
}

// Función para pausar la ejecución
void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

//===========================================================
// 2. MÓDULO DE GESTIÓN DE PACIENTES
//===========================================================

// Crear nuevo paciente
Paciente* crearPaciente(Hospital* hospital, const char* nombre, 
                        const char* apellido, const char* cedula, 
                        int edad, char sexo) {
    
    // Verificar si la cédula ya existe
    if (buscarPacientePorCedula(hospital, cedula) != nullptr) {
        mostrarError("Ya existe un paciente con esta cédula");
        return nullptr;
    }

    
    // Validar edad
    if (edad < 0 || edad > 120) {
        mostrarError("La edad debe estar entre 0 y 120 años");
        return nullptr;
    }
    
    // Validar sexo
    if (sexo != 'M' && sexo != 'F') {
        mostrarError("El sexo debe ser 'M' o 'F'");
        return nullptr;
    }
    
    // Redimensionar array si está lleno
    if (hospital->cantidadPacientes >= hospital->capacidadPacientes) {
        redimensionarArrayPacientes(hospital);
    }
    
    // Obtener referencia al nuevo paciente
    Paciente* nuevoPaciente = &hospital->pacientes[hospital->cantidadPacientes];
    
    // Asignar ID único
    nuevoPaciente->id = hospital->siguienteIdPaciente++;
    
    // Copiar datos básicos
    strncpy(nuevoPaciente->nombre, nombre, 49);
    nuevoPaciente->nombre[49] = '\0';
    
    strncpy(nuevoPaciente->apellido, apellido, 49);
    nuevoPaciente->apellido[49] = '\0';
    
    strncpy(nuevoPaciente->cedula, cedula, 19);
    nuevoPaciente->cedula[19] = '\0';
    
    nuevoPaciente->edad = edad;
    nuevoPaciente->sexo = sexo;
    
    // Inicializar arrays dinámicos del paciente
    nuevoPaciente->capacidadHistorial = 5;
    nuevoPaciente->cantidadConsultas = 0;
    nuevoPaciente->historial = new HistorialMedico[nuevoPaciente->capacidadHistorial];
    
    nuevoPaciente->capacidadCitas = 5;
    nuevoPaciente->cantidadCitas = 0;
    nuevoPaciente->citasAgendadas = new int[nuevoPaciente->capacidadCitas];
    
    // Inicializar strings vacíos
    nuevoPaciente->tipoSangre[0] = '\0';
    nuevoPaciente->telefono[0] = '\0';
    nuevoPaciente->direccion[0] = '\0';
    nuevoPaciente->email[0] = '\0';
    nuevoPaciente->alergias[0] = '\0';
    nuevoPaciente->observaciones[0] = '\0';
    
    // Estado activo
    nuevoPaciente->activo = true;
    
    hospital->cantidadPacientes++;
    
    mostrarExito("Paciente creado correctamente");
    return nuevoPaciente;
}

// Buscar paciente por cédula
Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedula) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (mi_strcasecmp(hospital->pacientes[i].cedula, cedula) == 0) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}

// Buscar paciente por ID
Paciente* buscarPacientePorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id && hospital->pacientes[i].activo) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}

// Buscar pacientes por nombre (búsqueda parcial)
Paciente** buscarPacientesPorNombre(Hospital* hospital, const char* nombre, int* cantidad) {
    // Primero contar cuántos pacientes coinciden
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].activo) {
            // Buscar en nombre
            if (strstr(hospital->pacientes[i].nombre, nombre) != nullptr ||
                strstr(hospital->pacientes[i].apellido, nombre) != nullptr) {
                (*cantidad)++;
            }
        }
    }
    
    if (*cantidad == 0) {
        return nullptr;
    }
    
    // Crear array de punteros
    Paciente** resultados = new Paciente*[*cantidad];
    int indice = 0;
    
    // Llenar el array con punteros a los pacientes encontrados
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].activo) {
            if (strstr(hospital->pacientes[i].nombre, nombre) != nullptr ||
                strstr(hospital->pacientes[i].apellido, nombre) != nullptr) {
                resultados[indice++] = &hospital->pacientes[i];
            }
        }
    }
    
    return resultados;
}

// Actualizar datos del paciente
bool actualizarPaciente(Hospital* hospital, int id) {
    Paciente* paciente = buscarPacientePorId(hospital, id);
    if (paciente == nullptr) {
        mostrarError("Paciente no encontrado");
        return false;
    }
    
    cout << "\n=== ACTUALIZAR DATOS DEL PACIENTE ===" << endl;
    cout << "Paciente: " << paciente->nombre << " " << paciente->apellido << endl;
    cout << "Deje en blanco para mantener el valor actual" << endl;
    
    char buffer[100];
    int tempEdad;
    
    // Actualizar nombre
    cout << "Nuevo nombre [" << paciente->nombre << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(paciente->nombre, buffer, 49);
        paciente->nombre[49] = '\0';
    }
    
    // Actualizar apellido
    cout << "Nuevo apellido [" << paciente->apellido << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(paciente->apellido, buffer, 49);
        paciente->apellido[49] = '\0';
    }
    
    // Actualizar edad
    cout << "Nueva edad [" << paciente->edad << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        tempEdad = atoi(buffer);
        if (tempEdad >= 0 && tempEdad <= 120) {
            paciente->edad = tempEdad;
        } else {
            mostrarError("Edad no válida, manteniendo valor anterior");
        }
    }
    
    // Actualizar teléfono
    cout << "Nuevo teléfono [" << paciente->telefono << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(paciente->telefono, buffer, 14);
        paciente->telefono[14] = '\0';
    }
    
    // Actualizar dirección
    cout << "Nueva dirección [" << paciente->direccion << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(paciente->direccion, buffer, 99);
        paciente->direccion[99] = '\0';
    }
    
    // Actualizar email
    cout << "Nuevo email [" << paciente->email << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        if (validarEmail(buffer)) {
            strncpy(paciente->email, buffer, 49);
            paciente->email[49] = '\0';
        } else {
            mostrarError("Email no válido, manteniendo valor anterior");
        }
    }
    
    // Actualizar tipo de sangre
    cout << "Nuevo tipo de sangre [" << paciente->tipoSangre << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(paciente->tipoSangre, buffer, 4);
        paciente->tipoSangre[4] = '\0';
    }
    
    // Actualizar alergias
    cout << "Nuevas alergias [" << paciente->alergias << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(paciente->alergias, buffer, 499);
        paciente->alergias[499] = '\0';
    }
    
    // Actualizar observaciones
    cout << "Nuevas observaciones [" << paciente->observaciones << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(paciente->observaciones, buffer, 499);
        paciente->observaciones[499] = '\0';
    }
    
    mostrarExito("Datos del paciente actualizados correctamente");
    return true;
}

// Eliminar paciente
bool eliminarPaciente(Hospital* hospital, int id) {
    Paciente* paciente = buscarPacientePorId(hospital, id);
    if (paciente == nullptr) {
        mostrarError("Paciente no encontrado");
        return false;
    }
    
    // Eliminar citas asociadas al paciente
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == id) {
            cancelarCita(hospital, hospital->citas[i].id);
        }
    }
    
    // Remover paciente de las listas de doctores
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        removerPacienteDeDoctor(&hospital->doctores[i], id);
    }
    
    // Liberar memoria de los arrays dinámicos del paciente
    if (paciente->historial != nullptr) {
        delete[] paciente->historial;
        paciente->historial = nullptr;
    }
    
    if (paciente->citasAgendadas != nullptr) {
        delete[] paciente->citasAgendadas;
        paciente->citasAgendadas = nullptr;
    }
    
    // Marcar como inactivo en lugar de eliminar físicamente
    paciente->activo = false;
    
    mostrarExito("Paciente eliminado correctamente");
    return true;
}

// Listar todos los pacientes
void listarPacientes(Hospital* hospital) {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    LISTA DE PACIENTES                      ║" << endl;
    cout << "╠═════╦═════════════════════╦══════════════╦══════╦══════════╣" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO     ║ CÉDULA       ║ EDAD ║ CONSULTAS║" << endl;
    cout << "╠═════╬═════════════════════╬══════════════╬══════╬══════════╣" << endl;
    
    int pacientesActivos = 0;
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].activo) {
            cout << "║ " << setw(3) << left << hospital->pacientes[i].id << " ";
            cout << "║ " << setw(19) << left 
                 << (string(hospital->pacientes[i].nombre) + " " + hospital->pacientes[i].apellido).substr(0, 19) << " ";
            cout << "║ " << setw(12) << left << hospital->pacientes[i].cedula << " ";
            cout << "║ " << setw(4) << left << hospital->pacientes[i].edad << " ";
            cout << "║ " << setw(8) << left << hospital->pacientes[i].cantidadConsultas << "║" << endl;
            pacientesActivos++;
        }
    }
    if (pacientesActivos == 0) {
        cout << "║                 NO HAY PACIENTES REGISTRADOS               ║" << endl;
    }
    
    cout << "╚═════╩═════════════════════╩══════════════╩══════╩══════════╝" << endl;
    cout << "Total de pacientes: " << pacientesActivos << endl;
}

//===========================================================
// FUNCIONES DE HISTORIAL MÉDICO
//===========================================================

// Agregar consulta al historial
void agregarConsultaAlHistorial(Paciente* paciente, HistorialMedico consulta) {
    // Verificar si es necesario redimensionar
    if (paciente->cantidadConsultas >= paciente->capacidadHistorial) {
        redimensionarHistorial(paciente);
    }
    
    // Agregar la consulta al array
    paciente->historial[paciente->cantidadConsultas] = consulta;
    paciente->cantidadConsultas++;
}

// Obtener historial completo
HistorialMedico* obtenerHistorialCompleto(Paciente* paciente, int* cantidad) {
    *cantidad = paciente->cantidadConsultas;
    return paciente->historial;
}

// Mostrar historial médico
void mostrarHistorialMedico(Paciente* paciente) {
    if (paciente == nullptr) {
        mostrarError("Paciente no válido");
        return;
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                         HISTORIAL MÉDICO DE " << setw(25) << left 
         << (string(paciente->nombre) + " " + paciente->apellido).substr(0, 25) << " ║" << endl;
    cout << "╠════════╦════════════╦══════╦══════════════════════════════════════╦══════════╣" << endl;
    cout << "║ CONSUL ║ FECHA      ║ HORA ║ DIAGNÓSTICO                         ║ COSTO    ║" << endl;
    cout << "╠════════╬════════════╬══════╬══════════════════════════════════════╬══════════╣" << endl;
    
    if (paciente->cantidadConsultas == 0) {
        cout << "║                              NO HAY CONSULTAS REGISTRADAS                    ║" << endl;
    } else {
        for (int i = 0; i < paciente->cantidadConsultas; i++) {
            cout << "║ " << setw(6) << left << paciente->historial[i].idConsulta << " ";
            cout << "║ " << setw(10) << left << paciente->historial[i].fecha << " ";
            cout << "║ " << setw(4) << left << paciente->historial[i].hora << " ";
            
            // Acortar diagnóstico si es muy largo
            string diagnostico = paciente->historial[i].diagnostico;
            if (diagnostico.length() > 30) {
                diagnostico = diagnostico.substr(0, 27) + "...";
            }
            cout << "║ " << setw(34) << left << diagnostico << " ";
            cout << "║ " << setw(8) << left << fixed << setprecision(2) << paciente->historial[i].costo << "║" << endl;
        }
    }
    
    cout << "╚════════╩════════════╩══════╩══════════════════════════════════════╩══════════╝" << endl;
    cout << "Total de consultas: " << paciente->cantidadConsultas << endl;
}

// Obtener última consulta
HistorialMedico* obtenerUltimaConsulta(Paciente* paciente) {
    if (paciente->cantidadConsultas == 0) {
        return nullptr;
    }
    return &paciente->historial[paciente->cantidadConsultas - 1];
}


//===========================================================
// 3. MÓDULO DE GESTIÓN DE DOCTORES
//===========================================================

// Crear nuevo doctor
Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, const char* especialidad, int aniosExperiencia, float costoConsulta) {
    // Verificar si la cédula ya existe
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (mi_strcasecmp(hospital->doctores[i].cedula, cedula) == 0) {
            mostrarError("Ya existe un doctor con esta cédula");
            return nullptr;
        }
    }

    // Validar años de experiencia
    if (aniosExperiencia < 0) {
        mostrarError("Los años de experiencia no pueden ser negativos");
        return nullptr;
    }

    // Validar costo de consulta
    if (costoConsulta <= 0) {
        mostrarError("El costo de consulta debe ser mayor a 0");
        return nullptr;
    }

    // Redimensionar array si está lleno
    if (hospital->cantidadDoctores >= hospital->capacidadDoctores) {
        redimensionarArrayDoctores(hospital);
    }

    // Obtener referencia al nuevo doctor
    Doctor* nuevoDoctor = &hospital->doctores[hospital->cantidadDoctores];

    // Asignar ID único
    nuevoDoctor->id = hospital->siguienteIdDoctor++;

    // Copiar datos básicos
    strncpy(nuevoDoctor->nombre, nombre, 49);
    nuevoDoctor->nombre[49] = '\0';

    strncpy(nuevoDoctor->apellido, apellido, 49);
    nuevoDoctor->apellido[49] = '\0';

    strncpy(nuevoDoctor->cedula, cedula, 19);
    nuevoDoctor->cedula[19] = '\0';

    strncpy(nuevoDoctor->especialidad, especialidad, 49);
    nuevoDoctor->especialidad[49] = '\0';

    nuevoDoctor->aniosExperiencia = aniosExperiencia;
    nuevoDoctor->costoConsulta = costoConsulta;

    // Inicializar arrays dinámicos del doctor
    nuevoDoctor->capacidadPacientes = 5;
    nuevoDoctor->cantidadPacientes = 0;
    nuevoDoctor->pacientesAsignados = new int[nuevoDoctor->capacidadPacientes];

    nuevoDoctor->capacidadCitas = 10;
    nuevoDoctor->cantidadCitas = 0;
    nuevoDoctor->citasAgendadas = new int[nuevoDoctor->capacidadCitas];

    // Inicializar strings vacíos
    nuevoDoctor->horarioAtencion[0] = '\0';
    nuevoDoctor->telefono[0] = '\0';
    nuevoDoctor->email[0] = '\0';

    // Estado disponible
    nuevoDoctor->disponible = true;

    hospital->cantidadDoctores++;

    mostrarExito("Doctor creado correctamente");
    return nuevoDoctor;
}

// Buscar doctor por ID
Doctor* buscarDoctorPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id && hospital->doctores[i].disponible) {
            return &hospital->doctores[i];
        }
    }
    return nullptr;
}

// Buscar doctores por especialidad
Doctor** buscarDoctoresPorEspecialidad(Hospital* hospital, const char* especialidad, int* cantidad) {
    // Primero contar cuántos doctores coinciden
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].disponible) {
            if (mi_strcasecmp(hospital->doctores[i].especialidad, especialidad) == 0) {
                (*cantidad)++;
            }
        }
    }

    if (*cantidad == 0) {
        return nullptr;
    }

    // Crear array de punteros
    Doctor** resultados = new Doctor*[*cantidad];

    int indice = 0;
    // Llenar el array con punteros a los doctores encontrados
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].disponible) {
            if (mi_strcasecmp(hospital->doctores[i].especialidad, especialidad) == 0) {
                resultados[indice++] = &hospital->doctores[i];
            }
        }
    }

    return resultados;
}

// Asignar paciente a doctor
bool asignarPacienteADoctor(Doctor* doctor, int idPaciente) {
    // Verificar si el paciente ya está asignado
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        if (doctor->pacientesAsignados[i] == idPaciente) {
            mostrarError("El paciente ya está asignado a este doctor");
            return false;
        }
    }

    // Redimensionar array si está lleno
    if (doctor->cantidadPacientes >= doctor->capacidadPacientes) {
        redimensionarArrayInt(&doctor->pacientesAsignados, doctor->cantidadPacientes, doctor->capacidadPacientes);
    }

    // Agregar ID del paciente al array
    doctor->pacientesAsignados[doctor->cantidadPacientes] = idPaciente;
    doctor->cantidadPacientes++;

    mostrarExito("Paciente asignado correctamente al doctor");
    return true;
}

// Remover paciente de doctor
bool removerPacienteDeDoctor(Doctor* doctor, int idPaciente) {
    return removerIdDeArray(doctor->pacientesAsignados, doctor->cantidadPacientes, idPaciente);
}

// Listar pacientes asignados a doctor
void listarPacientesDeDoctor(Hospital* hospital, int idDoctor) {
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    if (doctor == nullptr) {
        mostrarError("Doctor no encontrado");
        return;
    }

    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        PACIENTES ASIGNADOS AL DR. " << setw(25) << left 
         << (string(doctor->nombre) + " " + doctor->apellido).substr(0, 25) << "║" << endl;
    cout << "╠═════╦═════════════════════╦══════════════╦══════╦══════════╣" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO     ║ CÉDULA       ║ EDAD ║ CONSULTAS║" << endl;
    cout << "╠═════╬═════════════════════╬══════════════╬══════╬══════════╣" << endl;

    if (doctor->cantidadPacientes == 0) {
        cout << "║                     NO HAY PACIENTES ASIGNADOS                   ║" << endl;
    } else {
        for (int i = 0; i < doctor->cantidadPacientes; i++) {
            Paciente* paciente = buscarPacientePorId(hospital, doctor->pacientesAsignados[i]);
            if (paciente != nullptr && paciente->activo) {
                cout << "║ " << setw(3) << left << paciente->id << " ";
                cout << "║ " << setw(19) << left 
                     << (string(paciente->nombre) + " " + paciente->apellido).substr(0, 19) << " ";
                cout << "║ " << setw(12) << left << paciente->cedula << " ";
                cout << "║ " << setw(4) << left << paciente->edad << " ";
                cout << "║ " << setw(8) << left << paciente->cantidadConsultas << "║" << endl;
            }
        }
    }
    cout << "╚═════╩═════════════════════╩══════════════╩══════╩══════════╝" << endl;
    cout << "Total de pacientes asignados: " << doctor->cantidadPacientes << endl;
}

// Listar todos los doctores
void listarDoctores(Hospital* hospital) {
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                            LISTA DE DOCTORES                                 ║" << endl;
    cout << "╠═════╦═════════════════════╦══════════════╦════════════════╦══════╦═══════════╣" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO     ║ ESPECIALIDAD ║ TELÉFONO       ║ EXP  ║ COSTO     ║" << endl;
    cout << "╠═════╬═════════════════════╬══════════════╬════════════════╬══════╬═══════════╣" << endl;

    int doctoresActivos = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].disponible) {
            cout << "║ " << setw(3) << left << hospital->doctores[i].id << " ";
            cout << "║ " << setw(19) << left 
                 << (string(hospital->doctores[i].nombre) + " " + hospital->doctores[i].apellido).substr(0, 19) << " ";
            cout << "║ " << setw(12) << left << hospital->doctores[i].especialidad << " ";
            cout << "║ " << setw(14) << left << hospital->doctores[i].telefono << " ";
            cout << "║ " << setw(4) << left << hospital->doctores[i].aniosExperiencia << " ";
            cout << "║ " << setw(9) << left << fixed << setprecision(2) << hospital->doctores[i].costoConsulta << "║" << endl;
            doctoresActivos++;
        }
    }

    if (doctoresActivos == 0) {
        cout << "║                     NO HAY DOCTORES REGISTRADOS                      ║" << endl;
    }

    cout << "╚═════╩═════════════════════╩══════════════╩════════════════╩══════╩═══════════╝" << endl;
    cout << "Total de doctores: " << doctoresActivos << endl;
}

// Eliminar doctor
bool eliminarDoctor(Hospital* hospital, int id) {
    Doctor* doctor = buscarDoctorPorId(hospital, id);
    if (doctor == nullptr) {
        mostrarError("Doctor no encontrado");
        return false;
    }

    // Cancelar citas asociadas al doctor
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == id && strcmp(hospital->citas[i].estado, "Agendada") == 0) {
            strcpy(hospital->citas[i].estado, "Cancelada");
        }
    }

    // Liberar memoria de los arrays dinámicos del doctor
    if (doctor->pacientesAsignados != nullptr) {
        delete[] doctor->pacientesAsignados;
        doctor->pacientesAsignados = nullptr;
    }

    if (doctor->citasAgendadas != nullptr) {
        delete[] doctor->citasAgendadas;
        doctor->citasAgendadas = nullptr;
    }

    // Marcar como no disponible en lugar de eliminar físicamente
    doctor->disponible = false;

    mostrarExito("Doctor eliminado correctamente");
    return true;
}

// Actualizar datos del doctor
bool actualizarDoctor(Hospital* hospital, int id) {
    Doctor* doctor = buscarDoctorPorId(hospital, id);
    if (doctor == nullptr) {
        mostrarError("Doctor no encontrado");
        return false;
    }

    cout << "\n=== ACTUALIZAR DATOS DEL DOCTOR ===" << endl;
    cout << "Doctor: " << doctor->nombre << " " << doctor->apellido << endl;
    cout << "Deje en blanco para mantener el valor actual" << endl;

    char buffer[100];
    float tempCosto;
    int tempExp;

    // Actualizar teléfono
    cout << "Nuevo teléfono [" << doctor->telefono << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(doctor->telefono, buffer, 14);
        doctor->telefono[14] = '\0';
    }

    // Actualizar email
    cout << "Nuevo email [" << doctor->email << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        if (validarEmail(buffer)) {
            strncpy(doctor->email, buffer, 49);
            doctor->email[49] = '\0';
        } else {
            mostrarError("Email no válido, manteniendo valor anterior");
        }
    }

    // Actualizar horario
    cout << "Nuevo horario de atención [" << doctor->horarioAtencion << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        strncpy(doctor->horarioAtencion, buffer, 49);
        doctor->horarioAtencion[49] = '\0';
    }

    // Actualizar años de experiencia
    cout << "Nuevos años de experiencia [" << doctor->aniosExperiencia << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        tempExp = atoi(buffer);
        if (tempExp >= 0) {
            doctor->aniosExperiencia = tempExp;
        } else {
            mostrarError("Años de experiencia no válidos, manteniendo valor anterior");
        }
    }

    // Actualizar costo de consulta
    cout << "Nuevo costo de consulta [" << doctor->costoConsulta << "]: ";
    cin.getline(buffer, 100);
    if (strlen(buffer) > 0) {
        tempCosto = atof(buffer);
        if (tempCosto > 0) {
            doctor->costoConsulta = tempCosto;
        } else {
            mostrarError("Costo de consulta no válido, manteniendo valor anterior");
        }
    }

    mostrarExito("Datos del doctor actualizados correctamente");
    return true;
}
//===========================================================
// 4. MÓDULO DE GESTIÓN DE CITAS
//===========================================================

// Agendar nueva cita
Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor, const char* fecha, const char* hora, const char* motivo) {
    // Verificar que el paciente exista
    Paciente* paciente = buscarPacientePorId(hospital, idPaciente);
    if (paciente == nullptr) {
        mostrarError("Paciente no encontrado");
        return nullptr;
    }

    // Verificar que el doctor exista
    Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
    if (doctor == nullptr) {
        mostrarError("Doctor no encontrado");
        return nullptr;
    }

    // Validar formato de fecha
    if (!validarFecha(fecha)) {
        mostrarError("Formato de fecha inválido. Use YYYY-MM-DD");
        return nullptr;
    }

    // Validar formato de hora
    if (!validarHora(hora)) {
        mostrarError("Formato de hora inválido. Use HH:MM");
        return nullptr;
    }

    // Verificar disponibilidad del doctor
    if (!verificarDisponibilidad(hospital, idDoctor, fecha, hora)) {
        mostrarError("El doctor no está disponible en esa fecha y hora");
        return nullptr;
    }

    // Redimensionar array si está lleno
    if (hospital->cantidadCitas >= hospital->capacidadCitas) {
        redimensionarArrayCitas(hospital);
    }

    // Obtener referencia a la nueva cita
    Cita* nuevaCita = &hospital->citas[hospital->cantidadCitas];

    // Asignar ID único
    nuevaCita->id = hospital->siguienteIdCita++;

    // Copiar datos básicos
    nuevaCita->idPaciente = idPaciente;
    nuevaCita->idDoctor = idDoctor;
    strncpy(nuevaCita->fecha, fecha, 10);
    nuevaCita->fecha[10] = '\0';
    strncpy(nuevaCita->hora, hora, 5);
    nuevaCita->hora[5] = '\0';
    strncpy(nuevaCita->motivo, motivo, 149);
    nuevaCita->motivo[149] = '\0';

    // Estado inicial
    strcpy(nuevaCita->estado, "Agendada");
    nuevaCita->observaciones[0] = '\0';
    nuevaCita->atendida = false;

    // Agregar ID de cita al array del paciente
    if (paciente->cantidadCitas >= paciente->capacidadCitas) {
        redimensionarArrayInt(&paciente->citasAgendadas, paciente->cantidadCitas, paciente->capacidadCitas);
    }
    paciente->citasAgendadas[paciente->cantidadCitas] = nuevaCita->id;
    paciente->cantidadCitas++;

    // Agregar ID de cita al array del doctor
    if (doctor->cantidadCitas >= doctor->capacidadCitas) {
        redimensionarArrayInt(&doctor->citasAgendadas, doctor->cantidadCitas, doctor->capacidadCitas);
    }
    doctor->citasAgendadas[doctor->cantidadCitas] = nuevaCita->id;
    doctor->cantidadCitas++;

    hospital->cantidadCitas++;

    mostrarExito("Cita agendada correctamente");
    return nuevaCita;
}

// Cancelar cita
bool cancelarCita(Hospital* hospital, int idCita) {
    Cita* cita = nullptr;
    int indiceCita = -1; 

    // Buscar la cita
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].id == idCita) {
            cita = &hospital->citas[i];
            indiceCita = i;
            break;
        }
    }

    if (cita == nullptr) {
        mostrarError("Cita no encontrada");
        return false;
    }

    if (strcmp(cita->estado, "Atendida") == 0) {
        mostrarError("No se puede cancelar una cita ya atendida");
        return false;
    }

    // Cambiar estado
    strcpy(cita->estado, "Cancelada");

    // Remover de arrays de paciente y doctor
    Paciente* paciente = buscarPacientePorId(hospital, cita->idPaciente);
    if (paciente != nullptr) {
        removerIdDeArray(paciente->citasAgendadas, paciente->cantidadCitas, idCita);
    }

    Doctor* doctor = buscarDoctorPorId(hospital, cita->idDoctor);
    if (doctor != nullptr) {
        removerIdDeArray(doctor->citasAgendadas, doctor->cantidadCitas, idCita);
    }

    mostrarExito("Cita cancelada correctamente");
    return true;
}

// Atender cita
bool atenderCita(Hospital* hospital, int idCita, const char* diagnostico, const char* tratamiento, const char* medicamentos) {
    Cita* cita = nullptr;

    // Buscar la cita
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].id == idCita) {
            cita = &hospital->citas[i];
            break;
        }
    }

    if (cita == nullptr) {
        mostrarError("Cita no encontrada");
        return false;
    }

    if (strcmp(cita->estado, "Atendida") == 0) {
        mostrarError("La cita ya fue atendida");
        return false;
    }

    if (strcmp(cita->estado, "Cancelada") == 0) {
        mostrarError("No se puede atender una cita cancelada");
        return false;
    }

    // Cambiar estado de la cita
    strcpy(cita->estado, "Atendida");
    cita->atendida = true;

    // Obtener paciente y doctor
    Paciente* paciente = buscarPacientePorId(hospital, cita->idPaciente);
    Doctor* doctor = buscarDoctorPorId(hospital, cita->idDoctor);

    if (paciente == nullptr || doctor == nullptr) {
        mostrarError("Error al obtener datos del paciente o doctor");
        return false;
    }

    // Crear entrada en el historial médico
    HistorialMedico nuevaConsulta;
    nuevaConsulta.idConsulta = hospital->siguienteIdConsulta++;
    strcpy(nuevaConsulta.fecha, cita->fecha);
    strcpy(nuevaConsulta.hora, cita->hora);
    strncpy(nuevaConsulta.diagnostico, diagnostico, 199);
    nuevaConsulta.diagnostico[199] = '\0';
    strncpy(nuevaConsulta.tratamiento, tratamiento, 199);
    nuevaConsulta.tratamiento[199] = '\0';
    strncpy(nuevaConsulta.medicamentos, medicamentos, 149);
    nuevaConsulta.medicamentos[149] = '\0';
    nuevaConsulta.idDoctor = cita->idDoctor;
    nuevaConsulta.costo = doctor->costoConsulta;

    // Agregar al historial del paciente
    agregarConsultaAlHistorial(paciente, nuevaConsulta);

    mostrarExito("Cita atendida correctamente y agregada al historial");
    return true;
}

// Obtener citas de paciente
Cita** obtenerCitasDePaciente(Hospital* hospital, int idPaciente, int* cantidad) {
    // Primero contar cuántas citas tiene el paciente
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == idPaciente) {
            (*cantidad)++;
        }
    }

    if (*cantidad == 0) {
        return nullptr;
    }

    // Crear array de punteros
    Cita** resultados = new Cita*[*cantidad];

    int indice = 0;
    // Llenar el array con punteros a las citas encontradas
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == idPaciente) {
            resultados[indice++] = &hospital->citas[i];
        }
    }

    return resultados;
}

// Obtener citas de doctor
Cita** obtenerCitasDeDoctor(Hospital* hospital, int idDoctor, int* cantidad) {
    // Primero contar cuántas citas tiene el doctor
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor) {
            (*cantidad)++;
        }
    }

    if (*cantidad == 0) {
        return nullptr;
    }

    // Crear array de punteros
    Cita** resultados = new Cita*[*cantidad];

    int indice = 0;
    // Llenar el array con punteros a las citas encontradas
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor) {
            resultados[indice++] = &hospital->citas[i];
        }
    }

    return resultados;
}

// Obtener citas por fecha
Cita** obtenerCitasPorFecha(Hospital* hospital, const char* fecha, int* cantidad) {
    // Validar fecha
    if (!validarFecha(fecha)) {
        *cantidad = 0;
        return nullptr;
    }

    // Primero contar cuántas citas hay en esa fecha
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].fecha, fecha) == 0) {
            (*cantidad)++;
        }
    }

    if (*cantidad == 0) {
        return nullptr;
    }

    // Crear array de punteros
    Cita** resultados = new Cita*[*cantidad];

    int indice = 0;
    // Llenar el array con punteros a las citas encontradas
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].fecha, fecha) == 0) {
            resultados[indice++] = &hospital->citas[i];
        }
    }

    return resultados;
}

// Listar citas pendientes
void listarCitasPendientes(Hospital* hospital) {
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                              CITAS PENDIENTES                                       ║" << endl;
    cout << "╠═════╦════════╦════════╦════════════╦═══════╦════════════════════════════════════╦═════════╣" << endl;
    cout << "║ ID  ║ PAC    ║ DOC    ║ FECHA      ║ HORA  ║ MOTIVO                             ║ ESTADO  ║" << endl;
    cout << "╠═════╬════════╬════════╬════════════╬═══════╬════════════════════════════════════╬═════════╣" << endl;

    int citasPendientes = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].estado, "Agendada") == 0) {
            // Obtener nombres de paciente y doctor
            Paciente* paciente = buscarPacientePorId(hospital, hospital->citas[i].idPaciente);
            Doctor* doctor = buscarDoctorPorId(hospital, hospital->citas[i].idDoctor);
            
            string nombrePaciente = "N/A";
            string nombreDoctor = "N/A";
            
            if (paciente != nullptr) {
                nombrePaciente = string(paciente->nombre).substr(0, 1) + ". " + string(paciente->apellido).substr(0, 3);
            }
            if (doctor != nullptr) {
                nombreDoctor = string(doctor->nombre).substr(0, 1) + ". " + string(doctor->apellido).substr(0, 3);
            }
            
            cout << "║ " << setw(3) << left << hospital->citas[i].id << " ";
            cout << "║ " << setw(3) << left << nombrePaciente << " ";
            cout << "║ " << setw(5) << left << nombreDoctor << " ";
            cout << "║ " << setw(10) << left << hospital->citas[i].fecha << " ";
            cout << "║ " << setw(4) << left << hospital->citas[i].hora << " ";
            
            // Acortar motivo si es muy largo
            string motivo = hospital->citas[i].motivo;
            if (motivo.length() > 30) {
                motivo = motivo.substr(0, 27) + "...";
            }
            cout << "║ " << setw(34) << left << motivo << " ";
            cout << "║ " << setw(6) << left << hospital->citas[i].estado << "║" << endl;
            
            citasPendientes++;
        }
    }

    if (citasPendientes == 0) {
        cout << "║                         NO HAY CITAS PENDIENTES                           ║" << endl;
    }

    cout << "╚═════╩════════╩════════╩════════════╩═══════╩════════════════════════════════════╩═════════╝" << endl;
    cout << "Total de citas pendientes: " << citasPendientes << endl;
}

// Verificar disponibilidad
bool verificarDisponibilidad(Hospital* hospital, int idDoctor, const char* fecha, const char* hora) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor &&
            strcmp(hospital->citas[i].fecha, fecha) == 0 &&
            strcmp(hospital->citas[i].hora, hora) == 0 &&
            strcmp(hospital->citas[i].estado, "Agendada") == 0) {
            return false; // Ya tiene una cita a esa hora
        }
    }
    return true; // Está disponible
}

//===========================================================
// 5. INTERFAZ DE USUARIO
//===========================================================

// Función para crear datos de prueba
void crearDatosPrueba(Hospital* hospital) {
    // Crear doctores de prueba
    crearDoctor(hospital, "Carlos", "Gonzalez", "V-12345678", "Cardiología", 10, 50.0);
    crearDoctor(hospital, "Maria", "Lopez", "V-87654321", "Pediatría", 8, 40.0);
    crearDoctor(hospital, "Roberto", "Perez", "V-11223344", "Traumatología", 15, 60.0);
    
    // Crear pacientes de prueba
    crearPaciente(hospital, "Juan", "Martinez", "V-11111111", 35, 'M');
    crearPaciente(hospital, "Ana", "Garcia", "V-22222222", 28, 'F');
    crearPaciente(hospital, "Luis", "Rodriguez", "V-33333333", 45, 'M');
    
    // Agendar algunas citas de prueba
    agendarCita(hospital, 1, 1, "2024-01-15", "09:00", "Dolor en el pecho");
    agendarCita(hospital, 2, 2, "2024-01-15", "10:00", "Control infantil");
    agendarCita(hospital, 3, 3, "2024-01-16", "11:00", "Dolor en la rodilla");
}

// Menú principal
void mostrarMenuPrincipal() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║   SISTEMA DE GESTIÓN HOSPITALARIA     ║" << endl;
    cout << "╠════════════════════════════════════════╣" << endl;
    cout << "║ 1. Gestión de Pacientes               ║" << endl;
    cout << "║ 2. Gestión de Doctores                ║" << endl;
    cout << "║ 3. Gestión de Citas                   ║" << endl;
    cout << "║ 4. Salir                              ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "Seleccione una opción: ";
}

// Menú de pacientes
void menuPacientes(Hospital* hospital) {
    int opcion; 
    char buffer[100]; 
    do {
        cout << "\n╔════════════════════════════════════════╗" << endl;
        cout << "║         GESTIÓN DE PACIENTES          ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "║ 1. Registrar nuevo paciente           ║" << endl;
        cout << "║ 2. Buscar paciente por cédula         ║" << endl;
        cout << "║ 3. Buscar paciente por nombre         ║" << endl;
        cout << "║ 4. Ver historial médico completo      ║" << endl;
        cout << "║ 5. Actualizar datos del paciente      ║" << endl;
        cout << "║ 6. Listar todos los pacientes         ║" << endl;
        cout << "║ 7. Eliminar paciente                  ║" << endl;
        cout << "║ 0. Volver al menú principal           ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        limpiarBuffer();
        
        switch(opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20], tipoSangre[5], telefono[20], direccion[100], email[50],alergias[200],observaciones[200];
                int edad;
                char sexo;
                
                cout << "\n=== REGISTRAR NUEVO PACIENTE ===" << endl;
                cout << "Nombre: ";
                cin.getline(nombre, 50);
                cout << "Apellido: ";
                cin.getline(apellido, 50);
                cout << "Cédula: ";
                cin.getline(cedula, 20);
                cout << "Edad: ";
                cin >> edad;
                limpiarBuffer();
                cout << "Sexo (M/F): ";
                cin >> sexo;
                limpiarBuffer();
                cout << "tipo de Sangre: ";
                cin.getline(tipoSangre, 5);
                cout << "telefono: ";
                cin.getline(telefono, 20);
                cout << "Direccion: ";
                cin.getline(direccion, 100);
                cout << "email: ";
                cin.getline(email, 50);
                cout << "alegias: ";
                cin.getline(alergias, 200);
                cout << "observaciones: ";
                cin.getline(observaciones, 200);
                
                

                
                crearPaciente(hospital, nombre, apellido, cedula, edad, sexo);
                pausar();
                break;
            }
            
            case 2: {
                char cedula[20];
                cout << "\n=== BUSCAR PACIENTE POR CÉDULA ===" << endl;
                cout << "Ingrese la cédula: ";
                cin.getline(cedula, 20);
                
                Paciente* paciente = buscarPacientePorCedula(hospital, cedula);
                if (paciente != nullptr) {
                    cout << "\nPaciente encontrado:" << endl;
                    cout << "ID: " << paciente->id << endl;
                    cout << "Nombre: " << paciente->nombre << " " << paciente->apellido << endl;
                    cout << "Cédula: " << paciente->cedula << endl;
                    cout << "Edad: " << paciente->edad << endl;
                    cout << "Sexo: " << paciente->sexo << endl;
                } else {
                    mostrarError("Paciente no encontrado");
                }
                pausar();
                break;
            }
            
            case 3: {
                char nombre[50];
                cout << "\n=== BUSCAR PACIENTE POR NOMBRE ===" << endl;
                cout << "Ingrese el nombre o apellido: ";
                cin.getline(nombre, 50);
                
                int cantidad;
                Paciente** resultados = buscarPacientesPorNombre(hospital, nombre, &cantidad);
                if (resultados != nullptr) {
                    cout << "\nSe encontraron " << cantidad << " pacientes:" << endl;
                    for (int i = 0; i < cantidad; i++) {
                        cout << i+1 << ". " << resultados[i]->nombre << " " << resultados[i]->apellido 
                             << " (Cédula: " << resultados[i]->cedula << ")" << endl;
                    }
                    delete[] resultados;
                } else {
                    mostrarError("No se encontraron pacientes");
                }
                pausar();
                break;
            }
            
            case 4: {
                int id;
                cout << "\n=== VER HISTORIAL MÉDICO ===" << endl;
                cout << "Ingrese el ID del paciente: ";
                cin >> id;
                limpiarBuffer();
                
                Paciente* paciente = buscarPacientePorId(hospital, id);
                if (paciente != nullptr) {
                    mostrarHistorialMedico(paciente);
                } else {
                    mostrarError("Paciente no encontrado");
                }
                pausar();
                break;
            }
            
            case 5: {
                int id;
                cout << "\n=== ACTUALIZAR DATOS DE PACIENTE ===" << endl;
                cout << "Ingrese el ID del paciente: ";
                cin >> id;
                limpiarBuffer();
                
                actualizarPaciente(hospital, id);
                pausar();
                break;
            }
            
            case 6:
                listarPacientes(hospital);
                pausar();
                break;
                
            case 7: {
                int id;
                cout << "\n=== ELIMINAR PACIENTE ===" << endl;
                cout << "Ingrese el ID del paciente: ";
                cin >> id;
                limpiarBuffer();
                
                eliminarPaciente(hospital, id);
                pausar();
                break;
            }
            
            case 0:
                cout << "Volviendo al menú principal..." << endl;
                break;
                
            default:
                mostrarError("Opción no válida");
                pausar();
        }
    } while (opcion != 0);
}

// Menú de doctores
void menuDoctores(Hospital* hospital) {
    int opcion;
    char buffer[100];
    
    do {
        cout << "\n╔════════════════════════════════════════╗" << endl;
        cout << "║          GESTIÓN DE DOCTORES          ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "║ 1. Registrar nuevo doctor             ║" << endl;
        cout << "║ 2. Buscar doctor por ID               ║" << endl;
        cout << "║ 3. Buscar doctores por especialidad   ║" << endl;
        cout << "║ 4. Asignar paciente a doctor          ║" << endl;
        cout << "║ 5. Ver pacientes asignados a doctor   ║" << endl;
        cout << "║ 6. Listar todos los doctores          ║" << endl;
        cout << "║ 7. Eliminar doctor                    ║" << endl;
        cout << "║ 8. Actualizar datos del doctor        ║" << endl;
        cout << "║ 0. Volver al menú principal           ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        limpiarBuffer();
        
        switch(opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20], especialidad[50],horarioAtencion[50],telefono[20],email[50];
                int aniosExperiencia;
                float costoConsulta;
                
                cout << "\n=== REGISTRAR NUEVO DOCTOR ===" << endl;
                cout << "Nombre: ";
                cin.getline(nombre, 50);
                cout << "Apellido: ";
                cin.getline(apellido, 50);
                cout << "Cédula: ";
                cin.getline(cedula, 20);
                cout << "Especialidad: ";
                cin.getline(especialidad, 50);
                cout << "Años de experiencia: ";
                cin >> aniosExperiencia;
                cout << "Costo de consulta: ";
                cin >> costoConsulta;
                limpiarBuffer();
                cout << "horario de atencion: ";
                cin >> horarioAtencion;
                limpiarBuffer();
                cout << "telefono: ";
                cin.getline(telefono, 20);
                cout << "email: ";
                cin.getline(email, 50);
                
                
  crearDoctor(hospital, nombre, apellido, cedula, especialidad, aniosExperiencia, costoConsulta);
                pausar();
                break;
            }
            
            case 2: {
                int id;
                cout << "\n=== BUSCAR DOCTOR POR ID ===" << endl;
                cout << "Ingrese el ID del doctor: ";
                cin >> id;
                limpiarBuffer();
                
                Doctor* doctor = buscarDoctorPorId(hospital, id);
                if (doctor != nullptr) {
                    cout << "\nDoctor encontrado:" << endl;
                    cout << "ID: " << doctor->id << endl;
                    cout << "Nombre: " << doctor->nombre << " " << doctor->apellido << endl;
                    cout << "Cédula: " << doctor->cedula << endl;
                    cout << "Especialidad: " << doctor->especialidad << endl;
                    cout << "Años experiencia: " << doctor->aniosExperiencia << endl;
                    cout << "Costo consulta: " << doctor->costoConsulta << endl;
                } else {
                    mostrarError("Doctor no encontrado");
                }
                pausar();
                break;
            }
            
            case 3: {
                char especialidad[50];
                cout << "\n=== BUSCAR DOCTORES POR ESPECIALIDAD ===" << endl;
                cout << "Ingrese la especialidad: ";
                cin.getline(especialidad, 50);
                
                int cantidad;
                Doctor** resultados = buscarDoctoresPorEspecialidad(hospital, especialidad, &cantidad);
                if (resultados != nullptr) {
                    cout << "\nSe encontraron " << cantidad << " doctores:" << endl;
                    for (int i = 0; i < cantidad; i++) {
                        cout << i+1 << ". " << resultados[i]->nombre << " " << resultados[i]->apellido 
                             << " (ID: " << resultados[i]->id << ")" << endl;
                    }
                    delete[] resultados;
                } else {
                    mostrarError("No se encontraron doctores");
                }
                pausar();
                break;
            }
            
            case 4: {
                int idDoctor, idPaciente;
                cout << "\n=== ASIGNAR PACIENTE A DOCTOR ===" << endl;
                cout << "Ingrese el ID del doctor: ";
                cin >> idDoctor;
                cout << "Ingrese el ID del paciente: ";
                cin >> idPaciente;
                limpiarBuffer();
                
                Doctor* doctor = buscarDoctorPorId(hospital, idDoctor);
                if (doctor != nullptr) {
                    asignarPacienteADoctor(doctor, idPaciente);
                } else {
                    mostrarError("Doctor no encontrado");
                }
                pausar();
                break;
            }
            
            case 5: {
                int idDoctor;
                cout << "\n=== VER PACIENTES ASIGNADOS A DOCTOR ===" << endl;
                cout << "Ingrese el ID del doctor: ";
                cin >> idDoctor;
                limpiarBuffer();
                
                listarPacientesDeDoctor(hospital, idDoctor);
                pausar();
                break;
            }
            
            case 6:
                listarDoctores(hospital);
                pausar();
                break;
                
            case 7: {
                int id;
                cout << "\n=== ELIMINAR DOCTOR ===" << endl;
                cout << "Ingrese el ID del doctor: ";
                cin >> id;
                limpiarBuffer();
                
                eliminarDoctor(hospital, id);
                pausar();
                break;
            }
            
            case 8: {
                int id;
                cout << "\n=== ACTUALIZAR DATOS DE DOCTOR ===" << endl;
                cout << "Ingrese el ID del doctor: ";
                cin >> id;
                limpiarBuffer();
                
                actualizarDoctor(hospital, id);
                pausar();
                break;
            }
            
            case 0:
                cout << "Volviendo al menú principal..." << endl;
                break;
                
            default:
                mostrarError("Opción no válida");
                pausar();
        }
    } while (opcion != 0);
}
// Menú de citas
void menuCitas(Hospital* hospital) {
    int opcion;
    char buffer[100];
    
    do {
        cout << "\n╔════════════════════════════════════════╗" << endl;
        cout << "║           GESTIÓN DE CITAS            ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "║ 1. Agendar nueva cita                 ║" << endl;
        cout << "║ 2. Cancelar cita                      ║" << endl;
        cout << "║ 3. Atender cita                       ║" << endl;
        cout << "║ 4. Ver citas de un paciente           ║" << endl;
        cout << "║ 5. Ver citas de un doctor             ║" << endl;
        cout << "║ 6. Ver citas de una fecha             ║" << endl;
        cout << "║ 7. Ver citas pendientes               ║" << endl;
        cout << "║ 0. Volver al menú principal           ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        limpiarBuffer();
        
        switch(opcion) {
            case 1: {
                int idPaciente, idDoctor;
                char fecha[11], hora[6], motivo[150];
                
                cout << "\n=== AGENDAR NUEVA CITA ===" << endl;
                cout << "ID del paciente: ";
                cin >> idPaciente;
                cout << "ID del doctor: ";
                cin >> idDoctor;
                limpiarBuffer();
                cout << "Fecha (YYYY-MM-DD): ";
                cin.getline(fecha, 11);
                cout << "Hora (HH:MM): ";
                cin.getline(hora, 6);
                cout << "Motivo: ";
                cin.getline(motivo, 150);
                
                agendarCita(hospital, idPaciente, idDoctor, fecha, hora, motivo);
                pausar();
                break;
            }
            
            case 2: {
                int idCita;
                cout << "\n=== CANCELAR CITA ===" << endl;
                cout << "Ingrese el ID de la cita: ";
                cin >> idCita;
                limpiarBuffer();
                
                cancelarCita(hospital, idCita);
                pausar();
                break;
            }
            
            case 3: {
                int idCita;
                char diagnostico[200], tratamiento[200], medicamentos[150];
                
                cout << "\n=== ATENDER CITA ===" << endl;
                cout << "Ingrese el ID de la cita: ";
                cin >> idCita;
                limpiarBuffer();
                cout << "Diagnóstico: ";
                cin.getline(diagnostico, 200);
                cout << "Tratamiento: ";
                cin.getline(tratamiento, 200);
                cout << "Medicamentos: ";
                cin.getline(medicamentos, 150);
                
                atenderCita(hospital, idCita, diagnostico, tratamiento, medicamentos);
                pausar();
                break;
            }
            
            case 4: {
                int idPaciente;
                cout << "\n=== VER CITAS DE PACIENTE ===" << endl;
                cout << "Ingrese el ID del paciente: ";
                cin >> idPaciente;
                limpiarBuffer();
                
                int cantidad;
                Cita** citas = obtenerCitasDePaciente(hospital, idPaciente, &cantidad);
                if (citas != nullptr) {
                    cout << "\nCitas del paciente:" << endl;
                    for (int i = 0; i < cantidad; i++) {
                        cout << "ID: " << citas[i]->id << " | Fecha: " << citas[i]->fecha 
                             << " | Hora: " << citas[i]->hora << " | Estado: " << citas[i]->estado << endl;
                    }
                    delete[] citas;
                } else {
                    mostrarError("No se encontraron citas para este paciente");
                }
                pausar();
                break;
            }
            
            case 5: {
                int idDoctor;
                cout << "\n=== VER CITAS DE DOCTOR ===" << endl;
                cout << "Ingrese el ID del doctor: ";
                cin >> idDoctor;
                limpiarBuffer();
                
                int cantidad;
                Cita** citas = obtenerCitasDeDoctor(hospital, idDoctor, &cantidad);
                if (citas != nullptr) {
                    cout << "\nCitas del doctor:" << endl;
                    for (int i = 0; i < cantidad; i++) {
                        cout << "ID: " << citas[i]->id << " | Fecha: " << citas[i]->fecha 
                             << " | Hora: " << citas[i]->hora << " | Estado: " << citas[i]->estado << endl;
                    }
                    delete[] citas;
                } else {
                    mostrarError("No se encontraron citas para este doctor");
                }
                pausar();
                break;
            }
            
            case 6: {
                char fecha[11];
                cout << "\n=== VER CITAS POR FECHA ===" << endl;
                cout << "Ingrese la fecha (YYYY-MM-DD): ";
                cin.getline(fecha, 11);
                
                int cantidad;
                Cita** citas = obtenerCitasPorFecha(hospital, fecha, &cantidad);
                if (citas != nullptr) {
                    cout << "\nCitas para la fecha " << fecha << ":" << endl;
    for (int i = 0; i < cantidad; i++) {
            cout << "ID: " << citas[i]->id << " | Fecha: " << citas[i]->fecha 
                 << " | Hora: " << citas[i]->hora << " | Estado: " << citas[i]->estado << endl;
        }
        delete[] citas;
    } else {
        mostrarError("No se encontraron citas para este paciente");
    }
    pausar();
    break;
}

case 7:
    listarCitasPendientes(hospital);
    pausar();
    break;

case 0:
    cout << "Volviendo al menú principal..." << endl;
    break;

default:
    mostrarError("Opción no válida");
    pausar();
}
} while (opcion != 0);
}

//=========================================================================
// PUNTO DE ENTRADA PRINCIPAL
// =========================================================================

void iniciarSistema() {
    Hospital* hospital = inicializarHospital("hospital costanza");
    crearDatosPrueba(hospital);
    
    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        limpiarBuffer();
        
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
                cout << "Saliendo del sistema. ¡Hasta luego!" << endl;
                break;
            default:
                mostrarError("Opción no válida");
        }
    } while (opcion != 4);
    
    destruirHospital(hospital);
}
int main() {
    iniciarSistema();
    return 0;
}