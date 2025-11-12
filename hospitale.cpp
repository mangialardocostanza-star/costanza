#include <iostream>
#include <cstring>
#include <ctime> 
#include <iomanip>
#include <cctype>
#include <fstream>
#include <cstddef> //para tipos estadar como size_t
using namespace std;
//constantes de archivos binarios
const char FILE_HOSPITAL[] = "hospital.bin";
const char FILE_PACIENTES[] = "pacientes.bin";
const char FILE_DOCTORES[] = "doctores.bin";
const char FILE_CITAS[] = "citas.bin";
const char FILE_HISTORIALES[] = "historiales.bin";

//0. ESTRUCTURA PARA ARCHIVOS BINARIOS
// Estructura que va al inicio de cada archivo .bin para saber cuántos datos hay y el próximo ID.
struct ArchivoHeader {
    int cantidadRegistros;
    int siguienteId;
    int registrosActivos;
    int version =1;
};
//--------------------------------
//1.MODELO DE DATOS
//---------------------------------
// Estructura HistorialMedico (archivo: historiales.bin)

struct HistorialMedico {
    int id;
    int PacienteID;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int DoctorID;
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
    int PacienteID;
    int  DoctorID;
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
    int cantidadPacientes;
    int pacientesIDs[50];
    int cantidadCitas;
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
// Inicialización y cierre
Hospital inicializarHospital(const char* nombre);
Hospital cargarDatosHospital();
bool guardarDatosHospital(Hospital hospital);
bool verificarIntegridadArchivos();
// Doctores
Doctor buscarDoctorPorID(int id);
Doctor leerDoctorPorIndice(int indice);
int buscarIndiceDoctorPorID(int id);
bool agregarDoctor(Doctor nuevoDoctor);
bool actualizarDoctor(Doctor doctorModificado);
bool eliminarDoctor(int id);
bool validarDatosDoctor(int aniosExperiencia, float costoConsulta);
void listarTodosDoctores();
// Pacientes
Paciente buscarPacientePorID(int id);
bool agregarPaciente(Paciente nuevoPaciente);
Paciente buscarPacientePorCedula(const char* cedula);
bool ExistePacienteConCedula(const char* cedula);
Paciente leerPacienteporIndice(int indice);
int buscarIndiceDeID(int id);
bool actualizarPaciente(Paciente pacienteModificado);
bool eliminarPaciente(int id);
bool validarEdad(int edad);
bool validarSexo(char sexo);
void listarTodosPacientes();
// Citas
Cita buscarCitaPorID(int id);
bool agregarCita(Cita nuevaCita);
bool actualizarCita(Cita citaModificada);
bool eliminarCita(int id);
bool cancelarCita(int idCita);
bool atenderCita(int idCita, const char* diagnostico, const char* tratamiento, const char* medicamentos, float costo);
Cita buscarCitaPorID(int id);
bool actualizarCita(Cita citaModificada);
int buscarIndiceCitaPorID(int id);
// Historiales Médicos
HistorialMedico buscarHistorialPorID(int id);
bool agregarHistorial(HistorialMedico nuevoHistorial);
bool actualizarHistorial(HistorialMedico historialModificado);
bool eliminarHistorial(int id);
int buscarIndiceConsultaPorID(int id);
bool actualizarConsulta(HistorialMedico consultaModificada);
// Headers
ArchivoHeader leerHeader(const char* nombreArchivo);
bool actualizarHeader(const char* nombreArchivo, ArchivoHeader header);
bool inicializarArchivo(const char* nombreArchivo);
bool verificarArchivo(const char* nombreArchivo);
// Utilidades
time_t obtenerTimestamp();
void mostrarError(const char* mensaje);
void mostrarExito(const char* mensaje) ;
void pausar();
void limpiarBuffer();
// Cálculo de posiciones
long getPosicionPaciente(int indice);
long getPosicionDoctor(int indice);
long getPosicionCita(int indice);
long getPosicionHistorial(int indice);
// Validaciones
int mi_strcasecmp(const char* s1, const char* s2);
bool validarFecha(const char* fecha);
bool validarHora(const char* hora);
bool validarCedula(const char* cedula);
bool validarEmail(const char* email);
int compararFechas(const char* fecha1, const char* fecha2);
// Menús
bool verificarIntegridadArchivos();
void menuPrincipal();
void menuPacientes(); 
void menuDoctores();
void menuCitas();
void mostrarMenuPrincipal();
void menuMantenimiento();
time_t obtenerTimestamp();
// Para compactación
bool actualizarReferenciasPacientes(int mapaIDs[]);
bool actualizarReferenciasEnDoctores(int mapaIDs[]);
bool actualizarReferenciasEnCitas(int mapaIDs[]);
bool actualizarReferenciasEnHistoriales(int mapaIDs[]);
bool actualizarReferenciasDoctores(int mapaIDs[]);
bool actualizarReferenciasDoctoresEnCitas(int mapaIDs[]);
bool actualizarReferenciasDoctoresEnHistoriales(int mapaIDs[]);
// Para historial médico
HistorialMedico buscarUltimaConsulta(int primeraConsultaID);
HistorialMedico buscarConsultaPorID(int id);
bool verificarDisponibilidadDoctor(int doctorID, const char* fecha, const char* hora);

//-------------------------------------------
//3.Definir funciones 
//-------------------------------------------
//5.MODULO DE UTILIDADES Y HELPERS
//--------------------------------------------
// Implementar estas funciones mínimas:
time_t obtenerTimestamp() {
    return time(0);
}
void mostrarError(const char* mensaje) {
    std::cout << "Error: " << mensaje << endl;
}
void mostrarExito(const char* mensaje) {
    std::cout << "Exito: " << mensaje << endl;
}
void pausar() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}
int mi_strcasecmp(const char*s1,const char*s2){
 while(*s1 && *s2){
    char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
    char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
    if(c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
  return *s1 - *s2;
}
bool validarFecha(const char* fecha){
    int año, mes, dia;
    if(strlen(fecha)!=10){
        return false;
    }
    if(fecha[4]!='-' || fecha[7]!='-') {
        return false;
    }
for(int i=0; i<10;i++) {
    if (i==4 || i==7 ) 
continue;
    if (fecha[i] < '0' || fecha[i]>'9') {
    return false;
      }
}
año =    (fecha[0]-'0')* 1000 +
         (fecha[1]-'0')* 100 +
         (fecha[2]-'0')* 10 +
         (fecha[3]-'0');
mes =    (fecha[5]-'0')* 10 + (fecha[6]-'0');
dia =    (fecha[8]-'0')* 10 + (fecha[9]- '0');

    if ( año < 1900 || año > 2100) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;

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
bool validarCedula(const char* cedula) {
    if (cedula == 0| strlen (cedula) == 0 || strlen(cedula)>20){
        return false;
    }
    return true;
}
bool validarEmail(const char* email) {
    if(strlen (email)==0){\
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
    for (int i=0; i<10; i++){
        if (fecha1[i] < fecha2[i]) return -1;
        if (fecha1[i] > fecha2[i]) return 1;
    }
    return 0; 
}
void limpiarBuffer() {
    while (std::cin.get() != '\n');
}
//-----------------------------------------
//Archivos binarios de hospital
//-----------------------------------------
bool inicializarHeader(const char* nombreArchivo ) {
    ofstream archivo( nombreArchivo ,ios::binary | ios::out );
    if (!archivo.is_open()) {
        return false;
    }
    ArchivoHeader header = {0, 1, 0, 1}; 
    archivo.write(reinterpret_cast<const char*>(&header), sizeof(ArchivoHeader));
    archivo.close();
    return archivo.good();//verifica que la esrcritura fue exitosa
}

ArchivoHeader leerHeader(const char*nombreArchivo){
    ArchivoHeader header={0,0,0,0};
    ifstream archivo(nombreArchivo , ios::binary|ios::in);
    if(!archivo.is_open()){
        return header;
    }
    // Verificar que el archivo tiene  el tamaño 
    archivo.seekg(0, ios::end);
    streampos fileSize = archivo.tellg();
    archivo.seekg(0, ios::beg);
    
    if (fileSize < static_cast<streampos>(sizeof(ArchivoHeader))) {
        archivo.close();
        return header; // Archivo demasiado pequeño
    }
  archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    archivo.close();
    return header; // Retorna el header (sea válido o no)
}
bool actualizarHeader(const char* nombreArchivo, ArchivoHeader header){
    fstream archivo(nombreArchivo , ios::binary |ios::in |ios::out);
    if(!archivo.is_open()){
        return false;
    }
    archivo.seekp(0,ios::beg);
    archivo.write(reinterpret_cast<const char*>(&header), sizeof(ArchivoHeader));
    bool exito = archivo.good();
    archivo.close();
    return exito;
}
bool verificarArchivo(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        return false;
    }
    // Verificar que tenga al menos el tamaño del header
    archivo.seekg(0, ios::end);
    long tamaño = archivo.tellg();
    archivo.close();
    return (tamaño >= sizeof(ArchivoHeader));
}
bool verificarIntegridadArchivos() {
    std::cout << "\n=== VERIFICANDO INTEGRIDAD DE ARCHIVOS ===" << std::endl;
    bool todosOK = true;
    const char* archivos[] = {
        FILE_HOSPITAL, FILE_PACIENTES, FILE_DOCTORES, 
        FILE_CITAS, FILE_HISTORIALES
    };
    const char* nombres[] = {
        "Hospital", "Pacientes", "Doctores", "Citas", "Historiales"
    };
    for (int i = 0; i < 5; i++) {
        if (verificarArchivo(archivos[i])) {
            std::cout << "✅ " << nombres[i] << ": OK" << std::endl;
        } else {
            std::cout << "❌ " << nombres[i] << ": Error o archivo corrupto" << std::endl;  
            todosOK = false;
        }
    }
     if (todosOK) {
        std::cout << "\n✅ Todos los archivos están en buen estado." << std::endl;
    } else {
        std::cout << "\n⚠️  Se encontraron problemas en algunos archivos." << std::endl;
    }
    return todosOK;
}
bool inicializarArchivo(const char* nombreArchivo) {
    return inicializarHeader(nombreArchivo); 
}
//--------------------------------------------------------------------------
//compactacion de archivos binarios
//---------------------------------------------------------------------------
bool compactarArchivoPacientes() {
    // 1. Crear archivo temporal "pacientes_temp.bin"
    ofstream archivoTemp("pacientes_temp.bin", ios::binary);
    if (!archivoTemp.is_open()) {
        mostrarError("No se pudo crear archivo temporal");
        return false;
    }
    // 2. Leer header original
    ArchivoHeader headerOriginal = leerHeader(FILE_PACIENTES);
    ifstream archivoOriginal(FILE_PACIENTES, ios::binary);
    if (!archivoOriginal.is_open()) {
        archivoTemp.close();
        mostrarError("No se pudo abrir archivo original de pacientes");
        return false;
    }
    // Preparar nuevo header
    ArchivoHeader nuevoHeader;
    nuevoHeader.cantidadRegistros = 0;
    nuevoHeader.siguienteId = headerOriginal.siguienteId;
    nuevoHeader.registrosActivos = 0;
    nuevoHeader.version = headerOriginal.version;
    // Escribir nuevo header en archivo temporal
    archivoTemp.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));
    // Saltar header en archivo original
    archivoOriginal.seekg(sizeof(ArchivoHeader));
    // Mapa para re-indexar IDs viejos a nuevos
    int mapaIDs[1000] = {0}; // Asumiendo máximo 1000 pacientes
    int nuevoID = 1;
    Paciente paciente;
    // 3. Leer pacientes.bin registro por registro
    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        archivoOriginal.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
        if (archivoOriginal.fail()) break;
        // 4. Copiar solo registros con eliminado == false
        if (!paciente.eliminado) {
            // 5. Actualizar IDs secuencialmente 
            int idViejo = paciente.id;
            paciente.id = nuevoID;
            mapaIDs[idViejo] = nuevoID; // Guardar mapeo
            // Escribir paciente compactado en archivo temporal
            archivoTemp.write(reinterpret_cast<const char*>(&paciente), sizeof(Paciente));
            nuevoHeader.cantidadRegistros++;
            nuevoHeader.registrosActivos++;
            nuevoID++;
        }
    }
    archivoOriginal.close();
    archivoTemp.close();
    // Actualizar header del archivo temporal
    fstream archivoTempUpdate("pacientes_temp.bin", ios::binary | ios::in | ios::out);
    if (archivoTempUpdate.is_open()) {
        archivoTempUpdate.seekp(0);
        archivoTempUpdate.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));
        archivoTempUpdate.close();
    }
    // 6. Eliminar pacientes.bin original
    if (remove(FILE_PACIENTES) != 0) {
        mostrarError("Error al eliminar archivo original");
        remove("pacientes_temp.bin");
        return false;
    }
    // 7. Renombrar temp a pacientes.bin
    if (rename("pacientes_temp.bin", FILE_PACIENTES) != 0) {
        mostrarError("Error al renombrar archivo temporal");
        return false;
    }
    // 8. Actualizar referencias en otros archivos
    bool exitoActualizacion = actualizarReferenciasPacientes(mapaIDs);
    if (exitoActualizacion) {
        mostrarExito("Archivo de pacientes compactado exitosamente");
        std::cout << "Registros antes: " << headerOriginal.cantidadRegistros << std::endl;
        std::cout << "Registros después: " << nuevoHeader.cantidadRegistros << std::endl;
        std::cout << "Espacio liberado: " 
                  << (headerOriginal.cantidadRegistros - nuevoHeader.cantidadRegistros) * sizeof(Paciente) 
                  << " bytes" << std::endl;
    }
    return exitoActualizacion;
}
bool actualizarReferenciasPacientes(int mapaIDs[]) {
    bool exitoTotal = true;
    // Actualizar referencias en archivo de doctores
    exitoTotal &= actualizarReferenciasEnDoctores(mapaIDs);
    
    // Actualizar referencias en archivo de citas
    exitoTotal &= actualizarReferenciasEnCitas(mapaIDs);
    
    // Actualizar referencias en archivo de historiales
    exitoTotal &= actualizarReferenciasEnHistoriales(mapaIDs);

    return exitoTotal;
}

bool actualizarReferenciasEnDoctores(int mapaIDs[]) {
    ArchivoHeader header = leerHeader(FILE_DOCTORES);
    fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) return false;

    archivo.seekg(sizeof(ArchivoHeader));
    Doctor doctor;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        
        if (archivo.fail()) break;

        // Actualizar IDs de pacientes en el array del doctor
        bool modificado = false;
        for (int j = 0; j < doctor.cantidadPacientes; j++) {
            int idViejo = doctor.pacientesIDs[j];
            if (mapaIDs[idViejo] != 0) {
                doctor.pacientesIDs[j] = mapaIDs[idViejo];
                modificado = true;
            }
        }

        // Si se modificó, guardar cambios
        if (modificado) {
            archivo.seekp(posicion);
            archivo.write(reinterpret_cast<const char*>(&doctor), sizeof(Doctor));
            archivo.seekg(posicion + sizeof(Doctor)); // Volver a posición de lectura
        }
    }

    archivo.close();
    return true;
}

bool actualizarReferenciasEnCitas(int mapaIDs[]) {
    ArchivoHeader header = leerHeader(FILE_CITAS);
    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) return false;

    archivo.seekg(sizeof(ArchivoHeader));
    Cita cita;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
        
        if (archivo.fail()) break;

        // Actualizar ID del paciente en la cita
        if (mapaIDs[cita.PacienteID] != 0) {
            cita.PacienteID = mapaIDs[cita.PacienteID];
            
            archivo.seekp(posicion);
            archivo.write(reinterpret_cast<const char*>(&cita), sizeof(Cita));
            archivo.seekg(posicion + sizeof(Cita));
        }
    }

    archivo.close();
    return true;
}

bool actualizarReferenciasEnHistoriales(int mapaIDs[]) {
    ArchivoHeader header = leerHeader(FILE_HISTORIALES);
    fstream archivo(FILE_HISTORIALES, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) return false;

    archivo.seekg(sizeof(ArchivoHeader));
    HistorialMedico historial;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read(reinterpret_cast<char*>(&historial), sizeof(HistorialMedico));
        
        if (archivo.fail()) break;

        // Actualizar ID del paciente en el historial
        if (mapaIDs[historial.PacienteID] != 0) {
            historial.PacienteID = mapaIDs[historial.PacienteID];
            
            archivo.seekp(posicion);
            archivo.write(reinterpret_cast<const char*>(&historial), sizeof(HistorialMedico));
            archivo.seekg(posicion + sizeof(HistorialMedico));
        }
    }

    archivo.close();
    return true;
}
bool compactarArchivoDoctores() {
    // 1. Crear archivo temporal
    ofstream archivoTemp("doctores_temp.bin", ios::binary);
    if (!archivoTemp.is_open()) {
        mostrarError("No se pudo crear archivo temporal");
        return false;
    }

    // 2. Leer header original
    ArchivoHeader headerOriginal = leerHeader(FILE_DOCTORES);
    ifstream archivoOriginal(FILE_DOCTORES, ios::binary);
    if (!archivoOriginal.is_open()) {
        archivoTemp.close();
        mostrarError("No se pudo abrir archivo original de doctores");
        return false;
    }
    // Preparar nuevo header
    ArchivoHeader nuevoHeader;
    nuevoHeader.cantidadRegistros = 0;
    nuevoHeader.siguienteId = headerOriginal.siguienteId;
    nuevoHeader.registrosActivos = 0;
    nuevoHeader.version = headerOriginal.version;
    // Escribir nuevo header
    archivoTemp.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));

    // Saltar header en archivo original
    archivoOriginal.seekg(sizeof(ArchivoHeader));
    // Mapa para re-indexar IDs
    int mapaIDs[1000] = {0};
    int nuevoID = 1;
    Doctor doctor;
    // 3. Leer doctores.bin registro por registro
    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        archivoOriginal.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        if (archivoOriginal.fail()) break;
        // 4. Copiar solo registros no eliminados
        if (!doctor.eliminado) {
            int idViejo = doctor.id;
            doctor.id = nuevoID;
            mapaIDs[idViejo] = nuevoID;
            // Escribir doctor compactado
            archivoTemp.write(reinterpret_cast<const char*>(&doctor), sizeof(Doctor));
            nuevoHeader.cantidadRegistros++;
            nuevoHeader.registrosActivos++;
            nuevoID++;
        }
    }
    archivoOriginal.close();
    archivoTemp.close();
    // Actualizar header del archivo temporal
    fstream archivoTempUpdate("doctores_temp.bin", ios::binary | ios::in | ios::out);
    if (archivoTempUpdate.is_open()) {
        archivoTempUpdate.seekp(0);
        archivoTempUpdate.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));
        archivoTempUpdate.close();
    }
    // 6. Eliminar original y renombrar temporal
    if (remove(FILE_DOCTORES) != 0) {
        mostrarError("Error al eliminar archivo original");
        remove("doctores_temp.bin");
        return false;
    }
    if (rename("doctores_temp.bin", FILE_DOCTORES) != 0) {
        mostrarError("Error al renombrar archivo temporal");
        return false;
    }
    // 8. Actualizar referencias en otros archivos
    bool exitoActualizacion = actualizarReferenciasEnDoctores(mapaIDs);
    if (exitoActualizacion) {
        mostrarExito("Archivo de doctores compactado exitosamente");
        std::cout << "Registros antes: " << headerOriginal.cantidadRegistros << std::endl;
        std::cout << "Registros después: " << nuevoHeader.cantidadRegistros << std::endl;
        std::cout << "Espacio liberado: " 
                  << (headerOriginal.cantidadRegistros - nuevoHeader.cantidadRegistros) * sizeof(Doctor) 
                  << " bytes" << std::endl;
    }
    return exitoActualizacion;
}
bool actualizarReferenciasDoctores(int mapaIDs[]) {
    bool exitoTotal = true;

    // Actualizar referencias en citas
    exitoTotal &= actualizarReferenciasDoctoresEnCitas(mapaIDs);
    
    // Actualizar referencias en historiales
    exitoTotal &= actualizarReferenciasDoctoresEnHistoriales(mapaIDs);

    return exitoTotal;
}
bool actualizarReferenciasDoctoresEnCitas(int mapaIDs[]) {
    ArchivoHeader header = leerHeader(FILE_CITAS);
    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    archivo.seekg(sizeof(ArchivoHeader));
    Cita cita;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
        if (archivo.fail()) break;
        // Actualizar ID del doctor en la cita
        if (mapaIDs[cita.DoctorID] != 0) {
            cita.DoctorID = mapaIDs[cita.DoctorID];
            archivo.seekp(posicion);
            archivo.write(reinterpret_cast<const char*>(&cita), sizeof(Cita));
            archivo.seekg(posicion + sizeof(Cita));
        }
    }
    archivo.close();
    return true;
}
bool actualizarReferenciasDoctoresEnHistoriales(int mapaIDs[]) {
    ArchivoHeader header = leerHeader(FILE_HISTORIALES);
    fstream archivo(FILE_HISTORIALES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    archivo.seekg(sizeof(ArchivoHeader));
    HistorialMedico historial;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read(reinterpret_cast<char*>(&historial), sizeof(HistorialMedico));
        if (archivo.fail()) break;
        // Actualizar ID del doctor en el historial
        if (mapaIDs[historial.DoctorID] != 0) {
            historial.DoctorID = mapaIDs[historial.DoctorID];
            archivo.seekp(posicion);
            archivo.write(reinterpret_cast<const char*>(&historial), sizeof(HistorialMedico));
            archivo.seekg(posicion + sizeof(HistorialMedico));
        }
    }
    archivo.close();
    return true;
}
bool compactarArchivoCitas() {
    // 1. Crear archivo temporal
    ofstream archivoTemp("citas_temp.bin", ios::binary);
    if (!archivoTemp.is_open()) {
        mostrarError("No se pudo crear archivo temporal");
        return false;
    }
    // 2. Leer header original
    ArchivoHeader headerOriginal = leerHeader(FILE_CITAS);
    ifstream archivoOriginal(FILE_CITAS, ios::binary);
    if (!archivoOriginal.is_open()) {
        archivoTemp.close();
        mostrarError("No se pudo abrir archivo original de citas");
        return false;
    }
    // Preparar nuevo header
    ArchivoHeader nuevoHeader;
    nuevoHeader.cantidadRegistros = 0;
    nuevoHeader.siguienteId = headerOriginal.siguienteId;
    nuevoHeader.registrosActivos = 0;
    nuevoHeader.version = headerOriginal.version;
    // Escribir nuevo header
    archivoTemp.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));
    // Saltar header en archivo original
    archivoOriginal.seekg(sizeof(ArchivoHeader));
    // Mapa para re-indexar IDs
    int mapaIDs[1000] = {0};
    int nuevoID = 1;
    Cita cita;
    // 3. Leer citas.bin registro por registro
    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        archivoOriginal.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
        if (archivoOriginal.fail()) break;
        // 4. Copiar solo registros no eliminados
        if (!cita.eliminado) {
            int idViejo = cita.id;
            cita.id = nuevoID;
            mapaIDs[idViejo] = nuevoID;
            // Escribir cita compactada
            archivoTemp.write(reinterpret_cast<const char*>(&cita), sizeof(Cita));
            nuevoHeader.cantidadRegistros++;
            nuevoHeader.registrosActivos++;
            nuevoID++;
        }
    }
    archivoOriginal.close();
    archivoTemp.close();
    // Actualizar header del archivo temporal
    fstream archivoTempUpdate("citas_temp.bin", ios::binary | ios::in | ios::out);
    if (archivoTempUpdate.is_open()) {
        archivoTempUpdate.seekp(0);
        archivoTempUpdate.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));
        archivoTempUpdate.close();
    }
    // Eliminar original y renombrar
    if (remove(FILE_CITAS) != 0) {
        mostrarError("Error al eliminar archivo original");
        remove("citas_temp.bin");
        return false;
    }

    if (rename("citas_temp.bin", FILE_CITAS) != 0) {
        mostrarError("Error al renombrar archivo temporal");
        return false;
    }

    mostrarExito("Archivo de citas compactado exitosamente");
    std::cout << "Registros antes: " << headerOriginal.cantidadRegistros << std::endl;
    std::cout << "Registros después: " << nuevoHeader.cantidadRegistros << std::endl;
    std::cout << "Espacio liberado: " 
              << (headerOriginal.cantidadRegistros - nuevoHeader.cantidadRegistros) * sizeof(Cita) 
              << " bytes" << std::endl;
    return true;
}
bool compactarArchivoHistoriales() {
    // 1. Crear archivo temporal
    ofstream archivoTemp("historiales_temp.bin", ios::binary);
    if (!archivoTemp.is_open()) {
        mostrarError("No se pudo crear archivo temporal");
        return false;
    }

    // 2. Leer header original
    ArchivoHeader headerOriginal = leerHeader(FILE_HISTORIALES);
    ifstream archivoOriginal(FILE_HISTORIALES, ios::binary);
    if (!archivoOriginal.is_open()) {
        archivoTemp.close();
        mostrarError("No se pudo abrir archivo original de historiales");
        return false;
    }

    // Preparar nuevo header
    ArchivoHeader nuevoHeader;
    nuevoHeader.cantidadRegistros = 0;
    nuevoHeader.siguienteId = headerOriginal.siguienteId;
    nuevoHeader.registrosActivos = 0;
    nuevoHeader.version = headerOriginal.version;
    // Escribir nuevo header
    archivoTemp.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));
    // Saltar header en archivo original
    archivoOriginal.seekg(sizeof(ArchivoHeader));
    // Mapa para re-indexar IDs
    int mapaIDs[1000] = {0};
    int nuevoID = 1;
    HistorialMedico historial;
    // 3. Leer historiales.bin registro por registro
    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        archivoOriginal.read(reinterpret_cast<char*>(&historial), sizeof(HistorialMedico));
        if (archivoOriginal.fail()) break;
        // 4. Copiar solo registros no eliminados
        if (!historial.eliminado) {
            int idViejo = historial.id;
            historial.id = nuevoID;
            mapaIDs[idViejo] = nuevoID;
            // Escribir historial compactado
            archivoTemp.write(reinterpret_cast<const char*>(&historial), sizeof(HistorialMedico));
            
            nuevoHeader.cantidadRegistros++;
            nuevoHeader.registrosActivos++;
            nuevoID++;
        }
    }
    archivoOriginal.close();
    archivoTemp.close();
    // Actualizar header del archivo temporal
    fstream archivoTempUpdate("historiales_temp.bin", ios::binary | ios::in | ios::out);
    if (archivoTempUpdate.is_open()) {
        archivoTempUpdate.seekp(0);
        archivoTempUpdate.write(reinterpret_cast<const char*>(&nuevoHeader), sizeof(ArchivoHeader));
        archivoTempUpdate.close();
    }
    // Eliminar original y renombrar
    if (remove(FILE_HISTORIALES) != 0) {
        mostrarError("Error al eliminar archivo original");
        remove("historiales_temp.bin");
        return false;
    }
    if (rename("historiales_temp.bin", FILE_HISTORIALES) != 0) {
        mostrarError("Error al renombrar archivo temporal");
        return false;
    }
    // Los historiales no son referenciados por otros archivos
    mostrarExito("Archivo de historiales compactado exitosamente");
    std::cout << "Registros antes: " << headerOriginal.cantidadRegistros << std::endl;
    std::cout << "Registros después: " << nuevoHeader.cantidadRegistros << std::endl;
    std::cout << "Espacio liberado: " 
              << (headerOriginal.cantidadRegistros - nuevoHeader.cantidadRegistros) * sizeof(HistorialMedico) 
              << " bytes" << std::endl;
    return true;
}
void reiniciarArchivoPacientes() {
    std::ofstream archivo("pacientes.bin", std::ios::binary | std::ios::trunc);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear pacientes.bin\n";
        return;
    }

    ArchivoHeader header = {0, 1, 0, 1}; // Reinicia contador de ID
    archivo.write((char*)&header, sizeof(header));
    archivo.close();

    std::cout << "Archivo pacientes.bin reiniciado. Todos los registros fueron eliminados.\n";
}
void reiniciarArchivoDoctores() {
    std::ofstream archivo("doctores.bin", std::ios::binary | std::ios::trunc);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear doctores.bin\n";
        return;
    }
    ArchivoHeader header = {0, 1, 0, 1}; // Reinicia contador de ID
    archivo.write((char*)&header, sizeof(header));
    archivo.close();

    std::cout << "Archivo doctores.bin reiniciado. Todos los registros fueron eliminados.\n";
}
void reiniciarArchivoCitas() {
    std::ofstream archivo("citas.bin", std::ios::binary | std::ios::trunc);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear citas.bin\n";
        return;
    }
    ArchivoHeader header = {0, 1, 0, 1}; // Reinicia contador de ID
    archivo.write((char*)&header, sizeof(header));
    archivo.close();
    std::cout << "Archivo cin.bin reiniciado. Todos los registros fueron eliminados.\n";
}

//----------------------------------------------------------
//calcular la posicion en bytes de un registro por su indice 
//----------------------------------------------------------
long getPosicionPaciente(int indice){
    return sizeof(ArchivoHeader) + (indice * sizeof(Paciente));
}
long getPosicionDoctor(int indice){
    return sizeof(ArchivoHeader) + (indice * sizeof(Doctor));
}
long getPosicionCita(int indice){
    return sizeof(ArchivoHeader) + (indice * sizeof(Cita));
}
long getPosicionHistorial(int indice){
    return sizeof(ArchivoHeader) + (indice * sizeof(HistorialMedico));
}
//--------------------------------------------
//Gestion de memoria / utilidades
//--------------------------------------------
Hospital inicializarHospital(const char* nombre) {
    Hospital hospital;
    // 1. Verificar si existe el archivo del hospital
    ifstream archivo(FILE_HOSPITAL, ios::binary);
    if (!archivo.is_open()) {
        // Si no existe, inicializar con valores por defecto
        std::cout << "Inicializando sistema hospitalario por primera vez..." << endl;
        std::strcpy(hospital.nombre, "Hospital Coco 2");
        std::strcpy(hospital.direccion, "");
        std::strcpy(hospital.telefono, "");
        // Inicializar contadores
        hospital.siguienteIdPaciente = 1;
        hospital.siguienteIdDoctor = 1;
        hospital.siguienteIdCita = 1;
        hospital.siguienteIdConsulta = 1;
        // Inicializar estadísticas
        hospital.totalPacientesRegistrados = 0;
        hospital.totalDoctoresRegistrados = 0;
        hospital.totalCitasAgendadas = 0;
        hospital.totalConsultasRealizadas = 0;
        // Guardar el hospital inicializado
        guardarDatosHospital(hospital);
        return hospital;
    }
    // 2. Si el archivo existe, leer los datos
    archivo.read((char*)&hospital, sizeof(Hospital));
    archivo.close();
    // 3. Verificar integridad de los demás archivos
    if (!verificarArchivo(FILE_PACIENTES)) {
        inicializarArchivo(FILE_PACIENTES);
    }
    if (!verificarArchivo(FILE_DOCTORES)) {
        inicializarArchivo(FILE_DOCTORES);
    }
    if (!verificarArchivo(FILE_CITAS)) {
        inicializarArchivo(FILE_CITAS);
    }
    if (!verificarArchivo(FILE_HISTORIALES)) {
        inicializarArchivo(FILE_HISTORIALES);
    }
    
    return hospital;
}
bool guardarDatosHospital(Hospital hospital) {
    ofstream archivo(FILE_HOSPITAL, ios::binary);
    if (!archivo.is_open()) {
        return false;
    }
    archivo.write((char*)&hospital, sizeof(Hospital));
    archivo.close();
    return true;
}
//===========================================================
// 2. MÓDULO DE GESTIÓN DE PACIENTES
//===========================================================
// agregar paciente
bool agregarPaciente(Paciente nuevoPaciente){
ArchivoHeader header= leerHeader (FILE_PACIENTES);
nuevoPaciente.id= header.siguienteId;
nuevoPaciente.fechaCreacion = obtenerTimestamp();
nuevoPaciente.fechaModificacion = obtenerTimestamp();
nuevoPaciente.eliminado = 0;
    
ofstream archivo(FILE_PACIENTES, ios::binary |ios::app);
if (!archivo.is_open()){
    return false;
}
 archivo.write(reinterpret_cast<const char*>(&nuevoPaciente), sizeof(Paciente));
  if (archivo.fail()){
    archivo.close();
    return false;
}
//actualizar header
header.cantidadRegistros++;
header.siguienteId++;
header.registrosActivos++;
bool exitoHeader= actualizarHeader(FILE_PACIENTES, header);
archivo.close();
return exitoHeader;

}
Paciente capturarDatosPaciente() {
    Paciente p;
    // Inicializar solo lo necesario
    p.nombre[0] = '\0';
    p.apellido[0] = '\0';
    p.cedula[0] = '\0';
    p.edad = 0;
    p.sexo = ' ';
    
    // Campos opcionales - el usuario decidirá si los llena
    p.tipoSangre[0] = '\0';
    p.telefono[0] = '\0'; 
    p.direccion[0] = '\0';
    p.email[0] = '\0';
    p.alergias[0] = '\0';
    p.observaciones[0] = '\0';
    
    // Campos del sistema
    p.activo = true;
    p.cantidadConsultas = 0;
    p.primerConsultaID = 1;
    p.cantidadCitas = 0;
    for (int i = 0; i < 20; i++) p.citasIDs[i] = -1;
    
    return p;
}
//verificar cedulas

bool ExistePacienteConCedula(const char* cedula){
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()){
        return false;
    }
    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    //leer cada paciente
    Paciente paciente;
    for (int i=0; i< header.cantidadRegistros; i++){
        archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
        if (archivo.fail()){
            break;
        }
        if (!paciente.eliminado && strcmp(paciente.cedula, cedula)==0 ){
            archivo.close();
            return true; //encontrado
        }
    }
    archivo.close();
    return false; //no encontrado
}
    // Validar edad
    bool validarEdad(int edad) {
    if (edad < 0 || edad > 120) {
        mostrarError("La edad debe estar entre 0 y 120 años");
        return false;
    }
    return true;
}
    // Validar sexo
    bool validarSexo(char sexo) {
    if (sexo != 'M' && sexo != 'F') {
        mostrarError("El sexo debe ser 'M' o 'F'");
        return false;
    }
    return true;
}
// Buscar paciente por cédula
Paciente buscarPacientePorCedula(const char* cedula) {
    Paciente paciente;
    paciente.id = 0; // Marcar como no encontrado
    
    // Solo verificar longitud
    if (strlen(cedula) == 0) {
        return paciente;
    }
    ArchivoHeader header = leerHeader(FILE_PACIENTES);
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) {
        return paciente;
    }
    archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Paciente pacienteActual;
        archivo.read(reinterpret_cast<char*>(&pacienteActual), sizeof(Paciente));
        if (archivo.fail()) {
            break;
        }
        if (mi_strcasecmp(pacienteActual.cedula, cedula) == 0 && pacienteActual.eliminado == 0) {
            paciente = pacienteActual;
            break;
        }
    }
    archivo.close();
    return paciente;
}
Paciente buscarPacientePorID(int id) {
    Paciente paciente;
    paciente.id = 0; // Marcar como no encontrado
    
    // Validacion 1: ID válido
    if (id < 1) {
        std::cerr << "Error: ID de paciente inválido: " << id << std::endl;
        return paciente;
    }
    // Validacion2: Leer header
    ArchivoHeader header = leerHeader(FILE_PACIENTES);
    if (header.cantidadRegistros == 0) {
        std::cerr << "Advertencia: Archivo de pacientes vacío" << std::endl;
        return paciente;
    }
    // Validacion 3: Abrir archivo
    std::ifstream archivo(FILE_PACIENTES, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir " << FILE_PACIENTES << std::endl;
        return paciente;
    }
    // Validacion 4: Posicionarse después del header
    archivo.seekg(sizeof(ArchivoHeader), std::ios::beg);
    if (archivo.fail()) {
        std::cerr << "Error: No se pudo posicionar en el archivo" << std::endl;
        archivo.close();
        return paciente;
    }
    // 5. Bucle: leer cada paciente hasta encontrar ID o EOF
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Paciente pacienteActual;
        // Validacion5: Leer registro
        archivo.read(reinterpret_cast<char*>(&pacienteActual), sizeof(Paciente));
        if (archivo.fail()) {
            std::cerr << "Error: Lectura fallida en registro " << i << std::endl;
            break;
        }
        // Validacion6: Encontrar paciente activo con ID correcto
        if (pacienteActual.id == id && !pacienteActual.eliminado) {
            paciente = pacienteActual;
            
            // Validacion 7: Verificar datos críticos
            if (strlen(paciente.nombre) == 0) {
                std::cerr << "Advertencia: Paciente ID " << id << " tiene nombre vacío" << std::endl;
            }
            break;
        }
    }
    // Validacion 8: Reportar si no se encontró
    if (paciente.id == -1) {
        std::cerr << "Advertencia: Paciente ID " << id << " no encontrado o eliminado" << std::endl;
    }
    archivo.close();
    return paciente;
}
Paciente buscarPacientePorNombre(const char* nombre) {
    Paciente paciente;
    paciente.id = 0; // Marcar como no encontrado
    // Validar parámetro
    if (!nombre || strlen(nombre) == 0) {
        return paciente;
    }
    // 1. Leer header para saber cantidad de registros
    ArchivoHeader header = leerHeader(FILE_PACIENTES);
    // 2. Abrir pacientes.bin
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) {
        return paciente;
    }
    // 3. Saltar header: seekg(sizeof(ArchivoHeader))
    archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    // 4. Bucle: leer cada paciente hasta encontrar nombre o EOF
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Paciente pacienteActual;
        archivo.read(reinterpret_cast<char*>(&pacienteActual), sizeof(Paciente));
        // Si hay error de lectura, salir del bucle
        if (archivo.fail()) {
            break;
        }
        // Verificar si encontramos el paciente (activo y con nombre correcto)
        if (mi_strcasecmp(pacienteActual.nombre, nombre) == 0 && pacienteActual.eliminado == 0) {
            paciente = pacienteActual;
            break;
        }
    }
    // 5. Retornar paciente encontrado (o paciente vacío si no existe)
    archivo.close();
    return paciente;
}
//leer por id
Paciente leerPacienteporIndice(int indice){
Paciente p;
p.id=0; // marcar como no encontrado
//validar indice
if(indice < 0){
    return p;
}
ifstream archivo(FILE_PACIENTES, ios::binary);
if (!archivo.is_open()){
    return p;
}
//calcular la posicion
long posicion = sizeof(ArchivoHeader) + (indice * sizeof(Paciente));
archivo.seekg(posicion);//ir directamente a la posicion
 // Leer estructura completa
    archivo.read(reinterpret_cast<char*>(&p), sizeof(Paciente));
    archivo.close();
    // Verificar si el registro está activo
    if (p.eliminado != 0) {
        p.id = 0; // Marcar como no encontrado si está eliminado
    }
return p;
}
//buscar idice de id
int buscarIndiceDeID(int id) {
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) {
        return -1;
    } 
    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(ArchivoHeader));
    Paciente temp;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&temp, sizeof(Paciente));
        if (temp.id == id && !temp.eliminado) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}
bool eliminarPaciente(int id) {
int indice = buscarIndiceDeID(id);
    if (indice == -1) {
        mostrarError("Paciente no encontrado");
        return false;
}
fstream archivo(FILE_PACIENTES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        mostrarError("No se pudo abrir el archivo de pacientes");
        return false;
}
    long posicion = sizeof(ArchivoHeader) + (indice * sizeof(Paciente));
    archivo.seekg(posicion);
    Paciente paciente;
    archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
    if (archivo.fail()) {
        archivo.close();
        mostrarError("Error al leer el registro del paciente");
        return false;
    }
    if (paciente.eliminado == true){
        archivo.close();
        mostrarError("El paciente ya está eliminado");
        return false;
    }
    paciente.eliminado = true;
    paciente.fechaModificacion = time(0);
    archivo.seekp(posicion);
    archivo.write(reinterpret_cast<const char*>(&paciente), sizeof(Paciente));

     if (archivo.fail()) {
        archivo.close();
        return false;
    }
     // 8. Actualizar header.registrosActivos--
     ArchivoHeader header = leerHeader(FILE_PACIENTES);
     header.registrosActivos--;
    
     if (!actualizarHeader(FILE_PACIENTES, header)) {
        archivo.close();
        return false;
     }
     // 9. Cerrar archivo
     archivo.close();
     return true ;

}
 // Actualizar datos del paciente
bool actualizarPaciente(Paciente pacienteModificado) {
    int indice = buscarIndiceDeID(pacienteModificado.id);
    if (indice == -1) {
        return false; // no se encontró el paciente
}
    fstream archivo(FILE_PACIENTES, ios::binary | ios::in | ios::out);
    if(!archivo.is_open()){ 
        return false;
    }
    // 3. Posicionarse en la ubicación exacta 
    long posicion = sizeof(ArchivoHeader) + (indice * sizeof(Paciente));
    archivo.seekp(posicion);
    // 4. Actualizar timestamp
    pacienteModificado.fechaModificacion = obtenerTimestamp();
    // 5. Escribir estructura completa sobre el registro existente
    archivo.write(reinterpret_cast<const char*>(&pacienteModificado), sizeof(Paciente));
    // 6. Cerrar archivo
    archivo.close();
    // 7. Retornar true si exitoso
    return true;
    }   
    bool modificarPacienteDesdeTeclado(int idPaciente) {
    // 1. Buscar paciente en archivo (NO en memoria)
    Paciente paciente = buscarPacientePorID(idPaciente);
    if (paciente.id == -1) {
        mostrarError("Paciente no encontrado");
        return false;
    }
    std::cout << "\n=== ACTUALIZAR DATOS DEL PACIENTE ===" << std::endl;
    std::cout << "Paciente: " << paciente.nombre << " " << paciente.apellido << std::endl;
    std::cout << "Deje en blanco para mantener el valor actual" << std::endl;
    char buffer[100];
    int tempEdad;
    
    // Actualizar nombre
    std::cout << "Nuevo nombre [" << paciente.nombre << "]: ";
    std::cin.getline(buffer, 100);
    if (std::strlen(buffer) > 0) {
        std::strncpy(paciente.nombre, buffer, 49);
        paciente.nombre[49] = '\0';
    }
    // Actualizar apellido
    std::cout << "Nuevo apellido [" << paciente.apellido << "]: ";
    std::cin.getline(buffer, 100);
    if (std::strlen(buffer) > 0) {
        std::strncpy(paciente.apellido, buffer, 49);
        paciente.apellido[49] = '\0';
    }
    
    // Actualizar edad
     std::cout << "Nueva edad [" << paciente.edad << "]: ";
    std::cin.getline(buffer, 100);
    if (std::strlen(buffer) > 0) {
        tempEdad = std::atoi(buffer);
        if (tempEdad >= 0 && tempEdad <= 120) {
            paciente.edad = tempEdad;
        } else {
            mostrarError("Edad no válida, manteniendo valor anterior");
        }
    }
     // Actualizar teléfono
     std::cout << "Nuevo teléfono [" << paciente.telefono << "]: ";
    std::cin.getline(buffer, 100);
    if (std::strlen(buffer) > 0) {
    std::strncpy(paciente.telefono, buffer, 14);
        paciente.telefono[14] = '\0';
    }
    
    // Actualizar dirección 
     std::cout << "Nueva dirección [" << paciente.direccion << "]: ";  
     std::cin.getline(buffer, 100);                                  
      if (std::strlen(buffer) > 0) {                                    
     std::strncpy(paciente.direccion, buffer, 99);                 
     paciente.direccion[99] = '\0';                                
}
    
    // Actualizar email
    std::cout << "Nuevo email [" << paciente.email << "]: ";
    std::cin.getline(buffer, 100);
    if (std::strlen(buffer) > 0) {
    if (validarEmail(buffer)) {
    std::strncpy(paciente.email, buffer, 49);
    paciente.email[49] = '\0';
        } else {
            mostrarError("Email no válido, manteniendo valor anterior");
        }
    }
// Actualizar tipo de sangre
std::cout << "Nuevo tipo de sangre[" << paciente.tipoSangre << "]: ";
std::cin.getline(buffer, 100);
if (std::strlen(buffer) > 0) {
    std::strncpy(paciente.tipoSangre, buffer, 4);
    paciente.tipoSangre[4] = '\0';
}

// Actualizar alergias
std::cout << "Nuevas alergias [" << paciente.alergias << "]: ";
std::cin.getline(buffer, 100);
if (std::strlen(buffer) > 0) {
    std::strncpy(paciente.alergias, buffer, 499);
    paciente.alergias[499] = '\0';
}

// Actualizar observaciones
std::cout << "Nuevas observaciones [" << paciente.observaciones << "]: ";
std::cin.getline(buffer, 100);
if (std::strlen(buffer) > 0) {
    std::strncpy(paciente.observaciones, buffer, 499);
    paciente.observaciones[499] = '\0';
}

mostrarExito("Datos del paciente actualizados correctamente");
return true;
   
}
   void listarTodosPacientes() {
    // 1. Leer header para saber cantidad
    ArchivoHeader header = leerHeader(FILE_PACIENTES);
    
    // 2. ABRIR ARCHIVO
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) {
        mostrarError("No se pudo abrir archivo de pacientes");
        return;
    }
    
    // Saltar header
    archivo.seekg(sizeof(ArchivoHeader));
    
    int pacientesActivos = 0;
    Paciente paciente;
  
    
    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                    LISTA DE PACIENTES                      ║" << std::endl;
    std::cout << "╠═════╦═════════════════════╦══════════════╦══════╦══════════╣" << std::endl;
    std::cout << "║ ID  ║ NOMBRE COMPLETO     ║ CÉDULA       ║ EDAD ║ CONSULTAS║" << std::endl;
    std::cout << "╠═════╬═════════════════════╬══════════════╬══════╬══════════╣" << std::endl;

    // 2. Bucle: leer cada paciente secuencialmente
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
        
        if (archivo.fail()) break;
        
        // 3. Si !eliminado, mostrar en formato tabular
        if (!paciente.eliminado) {
            pacientesActivos++;
            
            // Formatear nombre completo
            std::string nombreCompleto = std::string(paciente.nombre) + " " + paciente.apellido;
            if (nombreCompleto.length() > 19) {
                nombreCompleto = nombreCompleto.substr(0, 16) + "...";
            }
            
            std::cout << "║ " << std::setw(3) << std::left << paciente.id << " ";
            std::cout << "║ " << std::setw(19) << std::left << nombreCompleto << " ";
            std::cout << "║ " << std::setw(12) << std::left << paciente.cedula << " ";
            std::cout << "║ " << std::setw(4) << std::left << paciente.edad << " ";
            std::cout << "║ " << std::setw(8) << std::left << paciente.cantidadConsultas << "║" << std::endl;
        }
    }

    // Mostrar mensaje si no hay pacientes

    if (pacientesActivos == 0) {
        std::cout << "║              NO HAY PACIENTES REGISTRADOS               ║" << std::endl;
    }

    std::cout << "╚═════╩═════════════════════╩══════════════╩══════╩══════════╝" << std::endl;
    std::cout << "Total de pacientes activos: " << pacientesActivos << std::endl;
    std::cout << "Total en archivo: " << header.cantidadRegistros << " (incluyendo eliminados)" << std::endl;
    
    archivo.close();
}

//===========================================================
// FUNCIONES DE HISTORIAL MÉDICO
//===========================================================

// Agregar consulta al historial
bool agregarConsultaAlHistorial(int pacienteID, HistorialMedico nuevaConsulta) {
    // 1. Leer paciente de pacientes.bin
    Paciente paciente = buscarPacientePorID(pacienteID);
    if (paciente.id == -1) {
        mostrarError("Paciente no encontrado");
        return false;
    }
    // Asignar ID automático
    ArchivoHeader headerHistorial = leerHeader(FILE_HISTORIALES);
    nuevaConsulta.id = headerHistorial.siguienteId;
    nuevaConsulta.PacienteID = pacienteID;
    nuevaConsulta.eliminado = false;
    nuevaConsulta.fecharegistro = time(0);
    // 2. Si es su primera consulta:
    if (paciente.primerConsultaID == -1) {
        nuevaConsulta.siguienteConsultaId = -1;
        paciente.primerConsultaID = nuevaConsulta.id;
    } 
    // 3. Si ya tiene consultas:
    else {
        nuevaConsulta.siguienteConsultaId = -1;
        // Buscar última consulta recorriendo la lista enlazada
        HistorialMedico ultimaConsulta = buscarUltimaConsulta(paciente.primerConsultaID);
        // ultimaConsulta.siguienteConsultaID = nuevaConsulta.id
        ultimaConsulta.siguienteConsultaId = nuevaConsulta.id;
        // Actualizar última consulta en historiales.bin
        if (!actualizarConsulta(ultimaConsulta)) {
            mostrarError("Error al actualizar la última consulta");
            return false;
        }
    }
    // 4. Agregar nuevaConsulta a historiales.bin (DIRECTAMENTE)
    ofstream archivo(FILE_HISTORIALES, ios::binary | ios::app);
    if (!archivo.is_open()) {
        mostrarError("Error al abrir archivo de historiales");
        return false;
    }
    archivo.write(reinterpret_cast<const char*>(&nuevaConsulta), sizeof(HistorialMedico));
    bool exitoEscritura = !archivo.fail();
    archivo.close();
    if (!exitoEscritura) {
        mostrarError("Error al guardar la nueva consulta");
        return false;
    }
    // Actualizar header del archivo de historiales
    headerHistorial.cantidadRegistros++;
    headerHistorial.siguienteId++;
    headerHistorial.registrosActivos++;
    if (!actualizarHeader(FILE_HISTORIALES, headerHistorial)) {
        mostrarError("Error al actualizar header de historiales");
        return false;
    }
    // 5. Actualizar paciente.cantidadConsultas++
    paciente.cantidadConsultas++;
    paciente.fechaModificacion = time(0);
    // 6. Guardar paciente modificado
    if (!actualizarPaciente(paciente)) {
        mostrarError("Error al actualizar el paciente");
        return false;
    }
    mostrarExito("Consulta agregada al historial exitosamente");
    return true;
}
HistorialMedico* leerHistorialCompleto(int pacienteID, int* cantidad) {
    // 1. Leer paciente para obtener paciente.primerConsultaID
    Paciente paciente = buscarPacientePorID(pacienteID);
    if (paciente.id == -1) {
        *cantidad = 0;
        return NULL;
    }
    if (paciente.primerConsultaID == -1) {
        *cantidad = 0;
        return NULL;
    }
    // 3. Crear array dinámico de tamaño paciente.cantidadConsultas
    HistorialMedico* historial = new HistorialMedico[paciente.cantidadConsultas];
    
    // 4. Abrir historiales.bin
    ifstream archivo(FILE_HISTORIALES, ios::binary);
    if (!archivo.is_open()) {
        *cantidad = 0;
        delete[] historial; // Liberar memoria
        return NULL;
    }
    
    // 5. Buscar primera consulta por ID
    int consultaActualID = paciente.primerConsultaID;
    int contador = 0;
    
    // 6. Bucle: seguir enlaces (siguienteConsultaID) hasta -1
    while (consultaActualID != -1 && contador < paciente.cantidadConsultas) {
        // Buscar consulta por ID en el archivo
        HistorialMedico consulta = buscarConsultaPorID(consultaActualID);
        
        if (consulta.id == -1) {
            break; // Consulta no encontrada
        }
        // 7. Agregar cada consulta al array
        historial[contador] = consulta;
        contador++;
        
        consultaActualID = consulta.siguienteConsultaId;
    }
    // 8. Retornar array y cantidad por referencia
    *cantidad = contador;
    archivo.close();
    return historial;
}
 int buscarIndiceConsultaPorID(int id) {
    ifstream archivo(FILE_HISTORIALES, ios::binary);
    if (!archivo.is_open()) {
        return -1;
    }
    // Leer header
    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    HistorialMedico temp;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(HistorialMedico));
        if (archivo.fail()) {
            break;
        }
        
        if (temp.id == id && !temp.eliminado) {
            archivo.close();
            return i;  // Índice encontrado
        }
    }
    archivo.close();
    return -1;  // No encontrado
}  
bool actualizarConsulta(HistorialMedico consultaModificada) {
    int indice = buscarIndiceConsultaPorID(consultaModificada.id);
    if (indice == -1) {
        return false;
    }
    fstream archivo(FILE_HISTORIALES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        return false;
    }
    long posicion = sizeof(ArchivoHeader) + (indice * sizeof(HistorialMedico));
    archivo.seekp(posicion);
    consultaModificada.fecharegistro = time(0); // Actualizar timestamp
    archivo.write(reinterpret_cast<const char*>(&consultaModificada), sizeof(HistorialMedico));
    bool exito = !archivo.fail();
    archivo.close();
    return exito;
}
HistorialMedico buscarConsultaPorID(int id) {
    HistorialMedico consulta;
    consulta.id = -1;
    if (id <= 0) return consulta;
    ArchivoHeader header = leerHeader(FILE_HISTORIALES);
    ifstream archivo(FILE_HISTORIALES, ios::binary);
    if (!archivo.is_open()) return consulta;
    archivo.seekg(sizeof(ArchivoHeader), ios::beg); 
    for (int i = 0; i < header.cantidadRegistros; i++) {
        HistorialMedico consultaActual;
        archivo.read(reinterpret_cast<char*>(&consultaActual), sizeof(HistorialMedico));
        if (archivo.fail()) break;
        
        if (consultaActual.id == id && !consultaActual.eliminado) {
            consulta = consultaActual;
            break;
        }
    }
    archivo.close();
    return consulta;
}
// Mostrar historial médico
void listarTodoHistorialMedico() {
    // 1. Leer header para saber cantidad
    ArchivoHeader header = leerHeader(FILE_HISTORIALES);
    // 2. ABRIR ARCHIVO
    ifstream archivo(FILE_HISTORIALES, ios::binary);
    if (!archivo.is_open()) {
        mostrarError("No se pudo abrir archivo de historiales");
        return;
    }
    // Saltar header
    archivo.seekg(sizeof(ArchivoHeader));
    int historialesActivos = 0;
    HistorialMedico historial;
    
    std::cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                        LISTA COMPLETA DE HISTORIALES " << std::setw(25) << std::left 
                << "║" << std::endl;
    std::cout << "╠════════╦════════════╦══════╦══════════════════════════════════════╦══════════╣" << std::endl;
    std::cout << "║ CONSUL ║ FECHA      ║ HORA ║ DIAGNÓSTICO                         ║ COSTO    ║" << std::endl;
    std::cout << "╠════════╬════════════╬══════╬══════════════════════════════════════╬══════════╣" << std::endl;
    
    // 2. Bucle: leer cada historial secuencialmente
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&historial), sizeof(HistorialMedico));
        
        if (archivo.fail()) break;
        
        // 3. Si !eliminado, mostrar en formato tabular
        if (!historial.eliminado) {
            historialesActivos++;
            
            // Obtener nombres de paciente y doctor
            Paciente paciente = buscarPacientePorID(historial.PacienteID);
            Doctor doctor = buscarDoctorPorID(historial.DoctorID);
            
            std::string nombrePaciente = (paciente.id != -1) ? 
            std::string(paciente.nombre).substr(0, 1) + ". " + paciente.apellido : "N/A";
            std::string nombreDoctor = (doctor.id != -1) ? 
            std::string(doctor.nombre).substr(0, 1) + ". " + doctor.apellido : "N/A";
            
            std::cout << std::setw(3) << std::left << historial.id << " | ";
            std::cout << std::setw(8) << std::left << nombrePaciente << " | ";
            std::cout << std::setw(10) << std::left << historial.fecha << " | ";
            std::cout << std::setw(6) << std::left << nombreDoctor << " | ";
            
            // Acortar diagnóstico si es muy largo
            std::string diagnostico = historial.diagnostico;
            if (diagnostico.length() > 30) {
                diagnostico = diagnostico.substr(0, 27) + "...";
            }
            std::cout << std::setw(30) << std::left << diagnostico << std::endl;
        }
    }
    
    std::cout << "╚════════╩════════════╩══════╩══════════════════════════════════════╩══════════╝" << std::endl;
     std::cout << "Total de registros activos: " << historialesActivos << std::endl;
    std::cout << "Total en archivo: " << header.cantidadRegistros << " (incluyendo eliminados)" << std::endl;
    
    archivo.close();
}
// Obtener última consulta
HistorialMedico buscarUltimaConsulta(int primeraConsultaID) {
    HistorialMedico actual = buscarConsultaPorID(primeraConsultaID);
    HistorialMedico ultima = actual;
    
    while (actual.siguienteConsultaId != -1) {
        actual = buscarConsultaPorID(actual.siguienteConsultaId);
        if (actual.id != -1) {
            ultima = actual;
        } else {
            break;
        }
    }
    return ultima;
}
//===========================================================
// 3. MÓDULO DE GESTIÓN DE DOCTORES
//===========================================================
// agregar doctor
bool agregarDoctor(Doctor nuevoDoctor) {
    ArchivoHeader header = leerHeader(FILE_DOCTORES);
    nuevoDoctor.id = header.siguienteId; 
    nuevoDoctor.fechaCreacion = obtenerTimestamp();
    nuevoDoctor.fechaModificacion = obtenerTimestamp();
    nuevoDoctor.eliminado = false; 
    ofstream archivo(FILE_DOCTORES, ios::binary | ios::app);
    if (!archivo.is_open()) {
        return false;
    }
    archivo.write(reinterpret_cast<const char*>(&nuevoDoctor), sizeof(Doctor));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    archivo.close();
    // Actualizar header
    header.cantidadRegistros++;
    header.siguienteId++; 
    header.registrosActivos++;
    bool exitoHeader = actualizarHeader(FILE_DOCTORES, header);
    return exitoHeader;
}
Doctor buscarDoctorPorID(int id) {
Doctor doctor;
    doctor.id = 0; // Marcar como no encontrado
    
    // Validar ID
    if (id < 1) {
        return doctor;
    }   
// 1. Leer header para saber cantidad de registros
ArchivoHeader header = leerHeader(FILE_DOCTORES);
ifstream archivo(FILE_DOCTORES,ios::binary);
    if (!archivo.is_open()) {
        return doctor;
    }
archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Doctor doctorActual;
        archivo.read(reinterpret_cast<char*>(&doctorActual), sizeof(Doctor));
        if (archivo.fail()) {
            break;
        }
if (doctorActual.id == id && !doctorActual.eliminado ) {
            doctor = doctorActual;
            break;
        }
    }
    archivo.close();
    return doctor;
}
Doctor leerDoctorPorIndice(int indice){
   Doctor doc;
   doc.id=-1; // marcar como no encontrado
   if (indice < 0) {
        return doc;
    }
ifstream archivo (FILE_DOCTORES,ios::binary);
if (!archivo.is_open()){
    return doc;
}
long posicion = sizeof(ArchivoHeader) + (indice * sizeof(Doctor));
archivo.seekg(posicion);

archivo.read(reinterpret_cast<char*>(&doc), sizeof(Doctor));
if (archivo.fail()){
    cerr<<"Error al leer el doctor"<<endl;
    doc.id=-1;
}
    archivo.close();
    return doc;
}

bool actualizarDoctor(Doctor doctorModificado) {
    int indice = buscarIndiceDoctorPorID(doctorModificado.id);
    if (indice == -1) {
        return false;
    }
    fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        return false;
    }
    long posicion = sizeof(ArchivoHeader) + (indice * sizeof(Doctor));
    archivo.seekp(posicion);
    doctorModificado.fechaModificacion = obtenerTimestamp();
    archivo.write(reinterpret_cast<const char*>(&doctorModificado), sizeof(Doctor));
    bool exito = !archivo.fail();
    archivo.close();
    return exito;
} 
//buscar idice de id
int buscarIndiceDoctorPorID(int id) {
    // 1. ABRIR archivo de doctores
    ifstream archivo(FILE_DOCTORES, ios::binary);
    if (!archivo.is_open()) {
        return -1;
    }
    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(ArchivoHeader));
    Doctor temp;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&temp, sizeof(Doctor));
        if (temp.id == id && !temp.eliminado) {
            archivo.close();
            return i;  // Índice encontrado
        }
    }
    // 4. CERRAR archivo
    archivo.close();
    return -1;  // No encontrado

}
    bool validarDatosDoctor(int aniosExperiencia, float costoConsulta) {
    if (aniosExperiencia < 0) {
        mostrarError("Los años de experiencia no pueden ser negativos");
        return false;
    }
    if (costoConsulta <= 0) {
        mostrarError("El costo de consulta debe ser mayor a 0");
        return false;
    }
    return true;
}
bool eliminarDoctor(int id){
    // 1. Buscar índice del doctor
    int indice = buscarIndiceDoctorPorID(id);
    if (indice == -1) {
        return false; // no se encontró el doctor
    }
    // 2. Abrir archivo en modo lectura/escritura
    fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        return false;
    }
    // 3. Posicionarse en el registro
    long posicion = sizeof(ArchivoHeader) + (indice * sizeof(Doctor));
    archivo.seekg(posicion);
    // 4. Leer el doctor completo
    Doctor doctor;
    archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    // Verificar si ya está eliminado
    if (doctor.eliminado) {
        archivo.close();
        return false;
    }
    // 5. Marcar: doctor.eliminado = true
    doctor.eliminado = true;
    doctor.fechaModificacion = time(0);
    doctor.disponible = false; // También marcar como no disponible
    // 6. Volver a posicionarse (seekp)
    archivo.seekp(posicion);
    // 7. Sobrescribir el registro modificado
    archivo.write(reinterpret_cast<const char*>(&doctor), sizeof(Doctor));
    
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    // 8. Actualizar header.registrosActivos1
    ArchivoHeader header = leerHeader(FILE_DOCTORES);
    header.registrosActivos--;
    
    if (!actualizarHeader(FILE_DOCTORES, header)) {
        archivo.close();
        return false;
    }
    // 9. Cerrar archivo
    archivo.close();
    return true;
 }
// Remover paciente de doctor
bool removerPacienteDeDoctor(int idDoctor, int idPaciente) {
    // 1. Buscar doctor
    Doctor doctor = buscarDoctorPorID(idDoctor);
    if (doctor.id == -1) return false;
    bool encontrado = false;
    // 2. BUSCAR Y ELIMINAR DEL ARRAY FIJO
    for (int i = 0; i < doctor.cantidadPacientes; i++) {
        if (doctor.pacientesIDs[i] == idPaciente) {
            // Desplazar elementos restantes
            for (int j = i; j < doctor.cantidadPacientes - 1; j++) {
                doctor.pacientesIDs[j] = doctor.pacientesIDs[j + 1];
            }
            doctor.cantidadPacientes--;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        mostrarError("Paciente no encontrado en la lista del doctor");
        return false;
    }
    // 3. GUARDAR CAMBIO
    doctor.fechaModificacion = time(0);
    return actualizarDoctor(doctor);
}
// Asignar paciente a doctor - ACCESO ALEATORIO
bool asignarPacienteADoctor(int idDoctor, int idPaciente) {
    // 1. Verificar que doctor existe
    Doctor doctor = buscarDoctorPorID(idDoctor);
    if (doctor.id == -1) {
        mostrarError("Doctor no encontrado");
        return false;
    }
    // 2. Verificar que paciente existe
    Paciente paciente = buscarPacientePorID(idPaciente);
    if (paciente.id == -1) {
        mostrarError("Paciente no encontrado");
        return false;
    }
    // 3. Verificar si ya está asignado
    for (int i = 0; i < doctor.cantidadPacientes; i++) {
        if (doctor.pacientesIDs[i] == idPaciente) {
            mostrarError("El paciente ya está asignado a este doctor");
            return false;
        }
    }
    // 4. Verificar capacidad del doctor
    if (doctor.cantidadPacientes >= 50) {
        mostrarError("El doctor ha alcanzado el límite de pacientes (50)");
        return false;
    }
    // 5. Agregar paciente al array del doctor
    doctor.pacientesIDs[doctor.cantidadPacientes] = idPaciente;
    doctor.cantidadPacientes++;
    doctor.fechaModificacion = time(0);
    
    // 6. Guardar cambios en archivo
    if (!actualizarDoctor(doctor)) {
        mostrarError("Error al actualizar el doctor");
        return false;
    }
    
    mostrarExito("Paciente asignado correctamente al doctor");
    return true;
}
void listarPacientesDeDoctor(int idDoctor) {
    // 1. BUSCAR DOCTOR
    Doctor doctor = buscarDoctorPorID(idDoctor);
    if (doctor.id == -1) {
        mostrarError("Doctor no encontrado");
        return;
    }

    std::cout << "\n╔════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║        PACIENTES ASIGNADOS AL DR. " << std::setw(25) << std::left 
              << (std::string(doctor.nombre) + " " + doctor.apellido).substr(0, 25) << "║" << std::endl;
    std::cout << "╠═════╦═════════════════════╦══════════════╦══════╦══════════╣" << std::endl;
    std::cout << "║ ID  ║ NOMBRE COMPLETO     ║ CÉDULA       ║ EDAD ║ CONSULTAS║" << std::endl;
    std::cout << "╠═════╬═════════════════════╬══════════════╬══════╬══════════╣" << std::endl;

    if (doctor.cantidadPacientes == 0) {
        std::cout << "║                     NO HAY PACIENTES ASIGNADOS                   ║" << std::endl;
    } else {
        for (int i = 0; i < doctor.cantidadPacientes; i++) {
            // 2. BUSCAR CADA PACIENTE EN ARCHIVO
            Paciente paciente = buscarPacientePorID(doctor.pacientesIDs[i]);
            if (paciente.id != -1 && !paciente.eliminado) {
                std::cout << "║ " << std::setw(3) << std::left << paciente.id << " ";
                std::cout << "║ " << std::setw(19) << std::left 
                         << (std::string(paciente.nombre) + " " + paciente.apellido).substr(0, 19) << " ";
                std::cout << "║ " << std::setw(12) << std::left << paciente.cedula << " ";
                std::cout << "║ " << std::setw(4) << std::left << paciente.edad << " ";
                std::cout << "║ " << std::setw(8) << std::left << paciente.cantidadConsultas << "║" << std::endl;
            }
        }
    }
    std::cout << "╚═════╩═════════════════════╩══════════════╩══════╩══════════╝" << std::endl;
    std::cout << "Total de pacientes asignados: " << doctor.cantidadPacientes << std::endl;
}

  void listarTodosDoctores() {
    // 1. Leer header para saber cantidad
    ArchivoHeader header = leerHeader(FILE_DOCTORES);
    // 2. ABRIR ARCHIVO
    ifstream archivo(FILE_DOCTORES, ios::binary);
    if (!archivo.is_open()) {
        mostrarError("No se pudo abrir archivo de doctores");
        return;
    }
    // Saltar header
    archivo.seekg(sizeof(ArchivoHeader));
    int doctoresActivos = 0;
    Doctor doctor;
    
     std::cout << "\n╔══════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                            LISTA DE DOCTORES                                 ║" << std::endl;
    std::cout << "╠═════╦═════════════════════╦══════════════╦════════════════╦══════╦═══════════╣" << std::endl;
    std::cout << "║ ID  ║ NOMBRE COMPLETO     ║ ESPECIALIDAD ║ TELÉFONO       ║ EXP  ║ COSTO     ║" << std::endl;
    std::cout << "╠═════╬═════════════════════╬══════════════╬════════════════╬══════╬═══════════╣" << std::endl;

    // 2. Bucle: leer cada doctor secuencialmente
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        
        if (archivo.fail()) break;
        
        // 3. Si !eliminado, mostrar en formato tabular
        if (!doctor.eliminado) {
            doctoresActivos++;
            
            // Formatear nombre completo
            std::string nombreCompleto = std::string(doctor.nombre) + " " + doctor.apellido;
            if (nombreCompleto.length() > 19) {
                nombreCompleto = nombreCompleto.substr(0, 16) + "...";
            }

            std::cout << "║ " << std::setw(3) << std::left << doctor.id << " ";
            std::cout << "║ " << std::setw(19) << std::left << nombreCompleto << " ";
            std::cout << "║ " << std::setw(12) << std::left << doctor.especialidad << " ";
            std::cout << "║ " << std::setw(14) << std::left << doctor.telefono << " ";
            std::cout << "║ " << std::setw(4) << std::left << doctor.aniosExperiencia << " ";
            std::cout << "║ " << std::setw(7) << std::left << doctor.costoConsulta << "║" << std::endl;
        }
    }

    // Mostrar mensaje si no hay doctores
    if (doctoresActivos == 0) {
        std::cout << "║                     NO HAY DOCTORES REGISTRADOS                      ║" << std::endl;
    }

    std::cout << "╚═════╩═════════════════════╩══════════════╩════════════════╩══════╩═══════════╝" << std::endl;
    std::cout << "Total de doctores activos: " << doctoresActivos << std::endl;
    std::cout << "Total en archivo: " << header.cantidadRegistros << " (incluyendo eliminados)" << std::endl;
    
    archivo.close();
}
bool modificarDoctorDesdeTeclado(int idDoctor) {
    // 1. Buscar paciente en archivo (NO en memoria)
    Doctor doctor = buscarDoctorPorID(idDoctor);
    if (doctor.id == -1) {
        mostrarError("Doctor no encontrado");
        return false;
    }
   
    std::cout << "\n=== ACTUALIZAR DATOS DEL DOCTOR ===" << std::endl;
    std::cout << "Doctor: " << doctor.nombre << " " << doctor.apellido << std::endl;
    std::cout << "Deje en blanco para mantener el valor actual" << std::endl;
    char buffer[100];
    int tempEdad;
    float tempCosto;
    
     // Actualizar teléfono
    std::cout << "Nuevo teléfono [" << doctor.telefono << "]: ";
    std::cin.getline(buffer, 100);
    if (std::strlen(buffer) > 0) {
    std::strncpy(doctor.telefono, buffer, 14);
        doctor.telefono[14] = '\0';
    }
    
    
    // Actualizar email
    std::cout << "Nuevo email [" << doctor.email << "]: ";
    std::cin.getline(buffer, 100);
    if (std::strlen(buffer) > 0) {
    if (validarEmail(buffer)) {
    std::strncpy(doctor.email, buffer, 49);
    doctor.email[49] = '\0';
        } else {
            mostrarError("Email no válido, manteniendo valor anterior");
        }
    }
// Actualizar horario
    std::cout<<"Nuevo horariode atencion ["<<doctor.horarioAtencion<<"]: ";
    std::cin.getline (buffer,100);
    if (std::strlen(buffer)>0){
    std::strncpy(doctor.horarioAtencion, buffer,49);
    doctor.horarioAtencion[49]='\0';
    }
//Actualizar años de experiencia
    std::cout<<"Nuevos años de experiencia ["<<doctor.aniosExperiencia<<"]: ";
    std::cin.getline (buffer,100);
    if (std::strlen(buffer)>0){
    tempEdad= atoi(buffer);
    if (tempEdad >=0){
    doctor.aniosExperiencia=tempEdad;
    } else {
    mostrarError("Años de experiencia no válidos, manteniendo valor anterior");
    }
    }
    
    // Actualizar costo de consulta
    std::cout<<"Nuevo costo de consulta ["<<doctor.costoConsulta<<"]: ";
    std::cin.getline (buffer,100);
    if (std::strlen(buffer)>0){
    tempCosto= atof(buffer);
    if (tempCosto >0){
    doctor.costoConsulta=tempCosto;
    } else {
    mostrarError("Costo de consulta no válido, manteniendo valor anterior");
    }
    }
if (actualizarDoctor(doctor)) {
mostrarExito("Datos del doctoractualizados correctamente");
return true;
  mostrarError("Error al guardar los cambios del doctor");
        return false;
   
   }

}
// Buscar y mostrar doctores por especialidad 
void buscarDoctoresPorEspecialidad(const char* especialidad) {
    // 1. Leer header para saber cantidad
    ArchivoHeader header = leerHeader(FILE_DOCTORES);
    
    // 2. ABRIR ARCHIVO
    ifstream archivo(FILE_DOCTORES, ios::binary);
    if (!archivo.is_open()) {
        mostrarError("No se pudo abrir archivo de doctores");
        return;
    }
    
    archivo.seekg(sizeof(ArchivoHeader));
    
    std::cout << "\n=== DOCTORES DE ESPECIALIDAD: " << especialidad << " ===" << std::endl;
    
    int encontrados = 0;
    Doctor doctor;
    
    // 3. LEER CADA DOCTOR DEL ARCHIVO
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        
        if (archivo.fail()) break;
        
        // 4. FILTRAR por especialidad y estado
        if (!doctor.eliminado && doctor.disponible && 
            mi_strcasecmp(doctor.especialidad, especialidad) == 0) {
            
            encontrados++;
            
            // Mostrar doctor encontrado
            std::cout << "ID: " << doctor.id << " | ";
            std::cout << "Nombre: " << doctor.nombre << " " << doctor.apellido << " | ";
            std::cout << "Años Exp: " << doctor.aniosExperiencia << " | ";
            std::cout << "Costo: $" << std::fixed << std::setprecision(2) << doctor.costoConsulta;
            
            if (strlen(doctor.telefono) > 0) {
                std::cout << " | Tel: " << doctor.telefono;
            }
            
            std::cout << std::endl;
        
    }
    
    if (encontrados == 0) {
        std::cout << "No se encontraron doctores de esta especialidad." << std::endl;
    } else {
        std::cout << "Total encontrados: " << encontrados << std::endl;
    }
    
    archivo.close();
    }
}
//===========================================================
// 4. MÓDULO DE GESTIÓN DE CITAS
//===========================================================
bool agendarNuevaCita(int pacienteID, int doctorID, const char* fecha, const char* hora, const char* motivo) {
    // VALIDACIONES INICIALES
    if (pacienteID <= 0 || doctorID <= 0 || fecha == nullptr || hora == nullptr || motivo == nullptr) {
        std::cerr << "Error: Parámetros inválidos para agendar cita" << std::endl;
        return false;
    }
    // 1. VERIFICAR QUE PACIENTE Y DOCTOR EXISTEN
    Paciente paciente = buscarPacientePorID(pacienteID);
    if (paciente.id == -1 || paciente.eliminado) {
        std::cerr << "Error: Paciente no encontrado o eliminado" << std::endl;
        return false;
    }
    Doctor doctor = buscarDoctorPorID(doctorID);
    if (doctor.id == -1 || doctor.eliminado || !doctor.disponible) {
        std::cerr << "Error: Doctor no encontrado, eliminado o no disponible" << std::endl;
        return false;
    }
    // 2. VERIFICAR DISPONIBILIDAD (fecha/hora no ocupada para el doctor)
    if (!verificarDisponibilidadDoctor(doctorID, fecha, hora)) {
        std::cerr << "Error: El doctor no está disponible en esa fecha y hora" << std::endl;
        return false;
    }
    // 3. CREAR NUEVA CITA
    Cita nuevaCita;
    // Obtener ID automático desde el header
    ArchivoHeader headerCitas = leerHeader(FILE_CITAS);
    nuevaCita.id = headerCitas.siguienteId;
    // Asignar datos básicos
    nuevaCita.PacienteID = pacienteID;
    nuevaCita.DoctorID = doctorID;
    std::strncpy(nuevaCita.fecha, fecha, 10);
    nuevaCita.fecha[10] = '\0';
    std::strncpy(nuevaCita.hora, hora, 5);
    nuevaCita.hora[5] = '\0';
    std::strncpy(nuevaCita.motivo, motivo, 149);
    nuevaCita.motivo[149] = '\0';
    // Estado inicial
    std::strncpy(nuevaCita.estado, "Agendada", 19);
    nuevaCita.estado[19] = '\0';
    nuevaCita.atendida = false;
    nuevaCita.consultaID = -1; // No tiene consulta asociada aún
    // Metadata
    nuevaCita.eliminado = false;
    nuevaCita.fechaCreacion = time(0);
    nuevaCita.fechaModificacion = time(0);
    // 4. GUARDAR CITA EN ARCHIVO 
    std::ofstream archivoCitas(FILE_CITAS, std::ios::binary | std::ios::app);
    if (!archivoCitas.is_open()) {
        std::cerr << "Error: No se pudo abrir archivo de citas para guardar" << std::endl;
        return false;
    }
    
    archivoCitas.write(reinterpret_cast<const char*>(&nuevaCita), sizeof(Cita));
    bool exitoEscritura = !archivoCitas.fail();
    archivoCitas.close();
    
    if (!exitoEscritura) {
        std::cerr << "Error: No se pudo guardar la cita en el archivo" << std::endl;
        return false;
    }
    
    // 5. ACTUALIZAR HEADER DE CITAS
    headerCitas.cantidadRegistros++;
    headerCitas.siguienteId++;
    headerCitas.registrosActivos++;
    if (!actualizarHeader(FILE_CITAS, headerCitas)) {
        std::cerr << "Error: No se pudo actualizar header de citas" << std::endl;
        return false;
    }
    
    // 6. ACTUALIZAR PACIENTE - agregar cita a su lista
    if (paciente.cantidadCitas < 20) { // pacientesIDs[20] - array fijo
        paciente.citasIDs[paciente.cantidadCitas] = nuevaCita.id;
        paciente.cantidadCitas++;
        paciente.fechaModificacion = time(0);
        
        if (!actualizarPaciente(paciente)) {
            std::cerr << "Error: No se pudo actualizar lista de citas del paciente" << std::endl;
            // Continuar aunque falle esta parte, la cita ya está guardada
        }
    } else {
        std::cerr << "Advertencia: Paciente alcanzó el límite de citas (20)" << std::endl;
    }
    
    // 7. ACTUALIZAR DOCTOR - agregar cita a su lista
    if (doctor.cantidadCitas < 30) { // citasIDs[30] - array fijo
        doctor.citasIDs[doctor.cantidadCitas] = nuevaCita.id;
        doctor.cantidadCitas++;
        doctor.fechaModificacion = time(0);
        
        if (!actualizarDoctor(doctor)) {
            std::cerr << "Error: No se pudo actualizar lista de citas del doctor" << std::endl;
            // Continuar aunque falle esta parte, la cita ya está guardada
        }
    } else {
        std::cerr << "Advertencia: Doctor alcanzó el límite de citas (30)" << std::endl;
    }
    
    std::cout << "✅ Cita agendada exitosamente. ID: " << nuevaCita.id << std::endl;
    return true;
}
bool verificarDisponibilidadDoctor(int doctorID, const char* fecha, const char* hora) {
    ArchivoHeader header = leerHeader(FILE_CITAS);
    std::ifstream archivo(FILE_CITAS, std::ios::binary);
    if (!archivo.is_open()) return false;
    
    archivo.seekg(sizeof(ArchivoHeader));
    Cita cita;
    
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
        if (archivo.fail()) break;
        
        // Verificar si el doctor ya tiene cita en misma fecha/hora y no está cancelada
        if (!cita.eliminado && 
            cita.DoctorID == doctorID && 
            strcmp(cita.fecha, fecha) == 0 && 
            strcmp(cita.hora, hora) == 0 &&
            strcmp(cita.estado, "Cancelada") != 0) {
            archivo.close();
            return false; // No disponible
        }
    }
    archivo.close();
    return true; // Disponible
}
 // Cancelar cita - ACCESO ALEATORIO
bool cancelarCita(int idCita) {
    // 1. Buscar la cita en archivo binario
    Cita cita = buscarCitaPorID(idCita);
    if (cita.id == -1) {
        mostrarError("Cita no encontrada");
        return false;
    }

    // 2. Validar estado de la cita
    if (strcmp(cita.estado, "Atendida") == 0) {
        mostrarError("No se puede cancelar una cita ya atendida");
        return false;
    }

    if (strcmp(cita.estado, "Cancelada") == 0) {
        mostrarError("La cita ya está cancelada");
        return false;
    }

    // 3. Cambiar estado a "Cancelada"
    strcpy(cita.estado, "Cancelada");
    cita.fechaModificacion = time(0);

    // 4. Actualizar cita en archivo binario
    if (!actualizarCita(cita)) {
        mostrarError("Error al actualizar la cita en el archivo");
        return false;
    }

    mostrarExito("Cita cancelada correctamente");
    return true;
}
// Atender cita - ACCESO ALEATORIO 
bool atenderCita(int idCita, const char* diagnostico, const char* tratamiento, const char* medicamentos, float costo) {
    // SOLO validaciones esenciales según requerimientos
    if (idCita <= 0) {
        mostrarError("ID de cita inválido");
        return false;
    }
    
    if (costo <= 0) {
        mostrarError("El costo debe ser mayor a 0");
        return false;
    }

    // 1. Buscar la cita en archivo binario
    Cita cita = buscarCitaPorID(idCita);
    if (cita.id == -1) {
        mostrarError("Cita no encontrada");
        return false;
    }

    // 2. Validar estado de la cita
    if (strcmp(cita.estado, "Atendida") == 0) {
        mostrarError("La cita ya fue atendida");
        return false;
    }

    if (strcmp(cita.estado, "Cancelada") == 0) {
        mostrarError("No se puede atender una cita cancelada");
        return false;
    }

    // 3. Obtener paciente y doctor desde archivos binarios
    Paciente paciente = buscarPacientePorID(cita.PacienteID);
    Doctor doctor = buscarDoctorPorID(cita.DoctorID);

    if (paciente.id == -1 || doctor.id == -1) {
        mostrarError("Error al obtener datos del paciente o doctor");
        return false;
    }

    // 4. Crear nueva consulta médica
    HistorialMedico nuevaConsulta;
    
    // Asignar ID automático
    ArchivoHeader headerHistorial = leerHeader(FILE_HISTORIALES);
    nuevaConsulta.id = headerHistorial.siguienteId;
    
    // Copiar datos directamente 
    strncpy(nuevaConsulta.diagnostico, diagnostico, 199);
    nuevaConsulta.diagnostico[199] = '\0';
    
    strncpy(nuevaConsulta.tratamiento, tratamiento, 199);
    nuevaConsulta.tratamiento[199] = '\0';
    
    strncpy(nuevaConsulta.medicamentos, medicamentos, 149);
    nuevaConsulta.medicamentos[149] = '\0';
    
    // Usar fecha y hora de la cita original
    strncpy(nuevaConsulta.fecha, cita.fecha, 10);
    nuevaConsulta.fecha[10] = '\0';
    
    strncpy(nuevaConsulta.hora, cita.hora, 5);
    nuevaConsulta.hora[5] = '\0';
    
    // Asignar relaciones
    nuevaConsulta.PacienteID = cita.PacienteID;
    nuevaConsulta.DoctorID = cita.DoctorID;
    nuevaConsulta.costo = costo;
    nuevaConsulta.siguienteConsultaId = -1;
    
    // Metadata
    nuevaConsulta.eliminado = false;
    nuevaConsulta.fecharegistro = time(0);

    // 5. AGREGAR CONSULTA DIRECTAMENTE al archivo
    ofstream archivoHistorial(FILE_HISTORIALES, ios::binary | ios::app);
    if (!archivoHistorial.is_open()) {
        mostrarError("Error al abrir archivo de historiales");
        return false;
    }
    
    archivoHistorial.write(reinterpret_cast<const char*>(&nuevaConsulta), sizeof(HistorialMedico));
    bool exitoEscritura = !archivoHistorial.fail();
    archivoHistorial.close();
    
    if (!exitoEscritura) {
        mostrarError("Error al guardar la consulta en el historial");
        return false;
    }
    
    // 6. ACTUALIZAR HEADER de historiales
    headerHistorial.cantidadRegistros++;
    headerHistorial.siguienteId++;
    headerHistorial.registrosActivos++;
    if (!actualizarHeader(FILE_HISTORIALES, headerHistorial)) {
        mostrarError("Error al actualizar header de historiales");
        return false;
    }

    // 7. ACTUALIZAR PACIENTE - manejar lista enlazada
    if (paciente.primerConsultaID == -1) {
        paciente.primerConsultaID = nuevaConsulta.id;
    } else {
        HistorialMedico ultimaConsulta = buscarUltimaConsulta(paciente.primerConsultaID);
        if (ultimaConsulta.id != -1) {
            ultimaConsulta.siguienteConsultaId = nuevaConsulta.id;
            actualizarConsulta(ultimaConsulta); // No verificar éxito - operación secundaria
        }
    }
    
    paciente.cantidadConsultas++;
    paciente.fechaModificacion = time(0);
    actualizarPaciente(paciente); // No verificar éxito - operación secundaria

    // 8. Actualizar estado de la cita
    strcpy(cita.estado, "Atendida");
    cita.atendida = true;
    cita.consultaID = nuevaConsulta.id;
    cita.fechaModificacion = time(0);

    if (!actualizarCita(cita)) {
        mostrarError("Error al actualizar el estado de la cita");
        return false;
    }

    mostrarExito("Cita atendida e historial médico creado correctamente");
    return true;
}


// Buscar cita por ID - ACCESO ALEATORIO
Cita buscarCitaPorID(int id) {
    Cita cita;
    cita.id = -1;
    
    if (id <= 0) return cita;
    
    ArchivoHeader header = leerHeader(FILE_CITAS);
    ifstream archivo(FILE_CITAS, ios::binary);
    if (!archivo.is_open()) return cita;
    
    archivo.seekg(sizeof(ArchivoHeader));
    
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Cita citaActual;
        archivo.read(reinterpret_cast<char*>(&citaActual), sizeof(Cita));
        
        if (archivo.fail()) break;
        
        if (citaActual.id == id && !citaActual.eliminado) {
            cita = citaActual;
            break;
        }
    }
    
    archivo.close();
    return cita;
}

// Actualizar cita en archivo - ACCESO ALEATORIO
bool actualizarCita(Cita citaModificada) {
    int indice = buscarIndiceCitaPorID(citaModificada.id);
    if (indice == -1) return false;
    
    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    
    long posicion = sizeof(ArchivoHeader) + (indice * sizeof(Cita));
    archivo.seekp(posicion);
    
    citaModificada.fechaModificacion = time(0);
    archivo.write(reinterpret_cast<const char*>(&citaModificada), sizeof(Cita));
    
    bool exito = !archivo.fail();
    archivo.close();
    return exito;
}

// Buscar índice de cita por ID
int buscarIndiceCitaPorID(int id) {
    ifstream archivo(FILE_CITAS, ios::binary);
    if (!archivo.is_open()) return -1;
    
    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    
    Cita temp;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(Cita));
        if (archivo.fail()) break;
        
        if (temp.id == id && !temp.eliminado) {
            archivo.close();
            return i;
        }
    }
    
    archivo.close();
    return -1;
}

// Obtener citas de paciente
Cita* leerCitasDePaciente(int pacienteID, int* cantidad) {
    *cantidad = 0;
    // 1. Leer paciente de pacientes.bin
    Paciente paciente = buscarPacientePorID(pacienteID);
    if (paciente.id == -1) {
        return nullptr;
    }
    // 2. Obtener paciente.cantidadCitas y paciente.citasIDs[]
    if (paciente.cantidadCitas == 0) {
        return nullptr;
    }
    
    // 3. Crear array dinámico de Citas (TEMPORAL - solo para esta operación)
    Cita* citas = new Cita[paciente.cantidadCitas];
    
    // 4. Para cada ID en citasIDs[]:
    int citasValidas = 0;
    for (int i = 0; i < paciente.cantidadCitas; i++) {
        int citaID = paciente.citasIDs[i];
        // Buscar cita por ID en citas.bin
        Cita cita = buscarCitaPorID(citaID);
        // Agregar al array si no está eliminada
        if (cita.id != -1 && !cita.eliminado) {
            citas[citasValidas] = cita;
            citasValidas++;
        }
    }
    // 5. Retornar array y cantidad real
    *cantidad = citasValidas;
    if (citasValidas == 0) {
        delete[] citas;  // Liberar memoria si no hay citas válidas
        return nullptr;
    }
    return citas;  // Array temporal que DEBE ser liberado por el llamador
}

// Obtener citas de doctor
Cita* leerCitasDeDoctor(int doctorID, int* cantidad) {
    *cantidad = 0;
    
    // 1. Leer doctor de doctores.bin
    Doctor doctor = buscarDoctorPorID(doctorID);
    if (doctor.id == -1) {
        return nullptr;
    }
    
    // 2. Obtener doctor.cantidadCitas y doctor.citasIDs[]
    if (doctor.cantidadCitas == 0) {
        return nullptr;
    }
    
    // 3. Crear array dinámico de Citas (TEMPORAL)
    Cita* citas = new Cita[doctor.cantidadCitas];
    
    // 4. Para cada ID en citasIDs[]:
    int citasValidas = 0;
    for (int i = 0; i < doctor.cantidadCitas; i++) {
        int citaID = doctor.citasIDs[i];
        
        // Buscar cita por ID en citas.bin
        Cita cita = buscarCitaPorID(citaID);
        
        // Agregar al array si no está eliminada
        if (cita.id != -1 && !cita.eliminado) {
            citas[citasValidas] = cita;
            citasValidas++;
        }
    }
    
    // 5. Retornar array y cantidad real
    *cantidad = citasValidas;
    
    if (citasValidas == 0) {
        delete[] citas;
        return nullptr;
    }
    return citas;
}
// Obtener citas por fecha
Cita* leerCitasPorFecha(const char* fecha, int* cantidad) {
    *cantidad = 0;
    
    // 1. Leer header para saber cantidad total de citas
    ArchivoHeader header = leerHeader(FILE_CITAS);
    if (header.cantidadRegistros == 0) {
        return nullptr;
    }
    
    // 2. Contar cuántas citas coinciden con la fecha
    std::ifstream archivoContar(FILE_CITAS, std::ios::binary);
    if (!archivoContar.is_open()) {
        return nullptr;
    }
    
    archivoContar.seekg(sizeof(ArchivoHeader));
    Cita citaTemp;
    int coincidencias = 0;
    
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivoContar.read(reinterpret_cast<char*>(&citaTemp), sizeof(Cita));
        if (archivoContar.fail()) break;
        
        if (!citaTemp.eliminado && strcmp(citaTemp.fecha, fecha) == 0) {
            coincidencias++;
        }
    }
    archivoContar.close();
    
    if (coincidencias == 0) {
        return nullptr;
    }
    
    // 3. Crear array dinámico de Citas (TEMPORAL)
    Cita* citas = new Cita[coincidencias];
    
    // 4. Leer citas que coinciden con la fecha
    std::ifstream archivoLeer(FILE_CITAS, std::ios::binary);
    if (!archivoLeer.is_open()) {
        delete[] citas;
        return nullptr;
    }
    
    archivoLeer.seekg(sizeof(ArchivoHeader));
    int indice = 0;
    
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivoLeer.read(reinterpret_cast<char*>(&citaTemp), sizeof(Cita));
        if (archivoLeer.fail()) break;
        
        if (!citaTemp.eliminado && strcmp(citaTemp.fecha, fecha) == 0) {
            citas[indice] = citaTemp;
            indice++;
        }
    }
    archivoLeer.close();
    
    // 5. Retornar array y cantidad real
    *cantidad = coincidencias;
    return citas;
}

// Listar citas pendientes
void listarCitasPendientes() {
    // 1. Leer header para saber cantidad de citas
    ArchivoHeader header = leerHeader(FILE_CITAS);
    
    // 2. ABRIR ARCHIVO de citas
    ifstream archivoCitas(FILE_CITAS, ios::binary);
    if (!archivoCitas.is_open()) {
        mostrarError("No se pudo abrir archivo de citas");
        return;
    }
    archivoCitas.seekg(sizeof(ArchivoHeader));
    
    
     std::cout << "\n╔══════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                              CITAS PENDIENTES                           ║" << std::endl;
    std::cout << "╠═════╦════════╦════════╦════════════╦═══════╦══════════════════╦═════════╣" << std::endl;
    std::cout << "║ ID  ║ PAC    ║ DOC    ║ FECHA      ║ HORA  ║ MOTIVO           ║ ESTADO  ║" << std::endl;
    std::cout << "╠═════╬════════╬════════╬════════════╬═══════╬══════════════════╬═════════╣" << std::endl;

    int citasPendientes = 0;
    Cita cita;
    
    // 3. LEER CADA CITA DEL ARCHIVO
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivoCitas.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
        
        if (archivoCitas.fail()) break;
        
        // 4. FILTRAR solo citas pendientes y no eliminadas
        if (!cita.eliminado && strcmp(cita.estado, "Agendada") == 0) {
            // 5. BUSCAR PACIENTE en archivo de pacientes
            Paciente paciente = buscarPacientePorID(cita.PacienteID);
            std::string nombrePaciente = "N/A";
            if (paciente.id != -1 && !paciente.eliminado) {
                nombrePaciente = std::string(paciente.nombre).substr(0, 1) + ". " + 
                                std::string(paciente.apellido).substr(0, 3);
            }
            
            // 6. BUSCAR DOCTOR en archivo de doctores
            Doctor doctor = buscarDoctorPorID(cita.DoctorID);
            std::string nombreDoctor = "N/A";
            if (doctor.id != -1 && !doctor.eliminado) {
                nombreDoctor = std::string(doctor.nombre).substr(0, 1) + ". " + 
                              std::string(doctor.apellido).substr(0, 3);
            }
            
            // 7. MOSTRAR CITA
            std::cout << "║ " << std::setw(3) << std::left << cita.id << " ";
            std::cout << "║ " << std::setw(6) << std::left << nombrePaciente << " ";
            std::cout << "║ " << std::setw(6) << std::left << nombreDoctor << " ";
            std::cout << "║ " << std::setw(10) << std::left << cita.fecha << " ";
            std::cout << "║ " << std::setw(5) << std::left << cita.hora << " ";
            
            // Acortar motivo si es muy largo
            std::string motivo = cita.motivo;
            if (motivo.length() > 30) {
                motivo = motivo.substr(0, 27) + "...";
            }
            std::cout << "║ " << std::setw(34) << std::left << motivo << " ";
            std::cout << "║ " << std::setw(7) << std::left << cita.estado << "║" << std::endl;
            
            citasPendientes++;
        }
    }

    if (citasPendientes == 0) {
        std::cout << "║                         NO HAY CITAS PENDIENTES                           ║" << std::endl;
    }

    std::cout << "╚═════╩════════╩════════╩════════════╩═══════╩════════════════════════════════════╩═════════╝" << std::endl;
    std::cout << "Total de citas pendientes: " << citasPendientes << std::endl;
    
    archivoCitas.close();
}

// Listar todas las citas - ACCESO ALEATORIO
void listarTodasCitas() {
    // 1. Leer header para saber cantidad
    ArchivoHeader header = leerHeader(FILE_CITAS);
    
    // 2. ABRIR ARCHIVO
    ifstream archivo(FILE_CITAS, ios::binary);
    if (!archivo.is_open()) {
        mostrarError("No se pudo abrir archivo de citas");
        return;
    }
    
    archivo.seekg(sizeof(ArchivoHeader));
    
    std::cout << "\n=== LISTA DE TODAS LAS CITAS ===" << std::endl;
    
    int citasActivas = 0;
    Cita cita;
    
    // 3. LEER CADA CITA DEL ARCHIVO
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
        
        if (archivo.fail()) break;
        
        // 4. Mostrar solo citas no eliminadas
        if (!cita.eliminado) {
            citasActivas++;
            
            // Buscar información de paciente y doctor
            Paciente paciente = buscarPacientePorID(cita.PacienteID);
            Doctor doctor = buscarDoctorPorID(cita.DoctorID);
            
            std::string nombrePaciente = (paciente.id != -1) ? 
                std::string(paciente.nombre) + " " + paciente.apellido : "N/A";
            
            std::string nombreDoctor = (doctor.id != -1) ? 
                std::string(doctor.nombre) + " " + doctor.apellido : "N/A";
            
            std::cout << "Cita #" << cita.id << " | ";
            std::cout << "Fecha: " << cita.fecha << " | ";
            std::cout << "Hora: " << cita.hora << " | ";
            std::cout << "Paciente: " << nombrePaciente << " | ";
            std::cout << "Doctor: " << nombreDoctor << " | ";
            std::cout << "Estado: " << cita.estado << std::endl;
        }
    }
    
    if (citasActivas == 0) {
        std::cout << "No hay citas registradas en el sistema." << std::endl;
    } else {
        std::cout << "\nTotal de citas activas: " << citasActivas << std::endl;
    }
    
    archivo.close();
}

//===========================================================

//FUNCIONES DE MANTENIMIENTO DE ARCHIVOS

//===========================================================
bool verificarIntegridadReferencial() {
    std::cout << "\n=== VERIFICANDO INTEGRIDAD REFERENCIAL ===" << std::endl;
    
    bool integridadOK = true;
    int problemasEncontrados = 0;

    // 1. VERIFICAR CITAS: que pacienteID y doctorID existan
    std::cout << "Verificando citas..." << std::endl;
    ArchivoHeader headerCitas = leerHeader(FILE_CITAS);
    ifstream archivoCitas(FILE_CITAS, ios::binary);
    
    if (archivoCitas.is_open()) {
        archivoCitas.seekg(sizeof(ArchivoHeader));
        Cita cita;
        
        for (int i = 0; i < headerCitas.cantidadRegistros; i++) {
            archivoCitas.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
            if (archivoCitas.fail()) break;
            
            if (!cita.eliminado) {
                // Verificar paciente
                Paciente paciente = buscarPacientePorID(cita.PacienteID);
                if (paciente.id == -1 || paciente.eliminado) {
                    std::cout << "  ❌ Cita #" << cita.id << ": Paciente ID " << cita.PacienteID << " no existe" << std::endl;
                    integridadOK = false;
                    problemasEncontrados++;
                }
                
                // Verificar doctor
                Doctor doctor = buscarDoctorPorID(cita.DoctorID);
                if (doctor.id == -1 || doctor.eliminado) {
                    std::cout << "  ❌ Cita #" << cita.id << ": Doctor ID " << cita.DoctorID << " no existe" << std::endl;
                    integridadOK = false;
                    problemasEncontrados++;
                }
            }
        }
        archivoCitas.close();
    }

    // 2. VERIFICAR HISTORIALES: que pacienteID y doctorID existan
    std::cout << "Verificando historiales médicos..." << std::endl;
    ArchivoHeader headerHistoriales = leerHeader(FILE_HISTORIALES);
    ifstream archivoHistoriales(FILE_HISTORIALES, ios::binary);
    
    if (archivoHistoriales.is_open()) {
        archivoHistoriales.seekg(sizeof(ArchivoHeader));
        HistorialMedico historial;
        
        for (int i = 0; i < headerHistoriales.cantidadRegistros; i++) {
            archivoHistoriales.read(reinterpret_cast<char*>(&historial), sizeof(HistorialMedico));
            if (archivoHistoriales.fail()) break;
            
            if (!historial.eliminado) {
                // Verificar paciente
                Paciente paciente = buscarPacientePorID(historial.PacienteID);
                if (paciente.id == -1 || paciente.eliminado) {
                    std::cout << "  ❌ Historial #" << historial.id << ": Paciente ID " << historial.PacienteID << " no existe" << std::endl;
                    integridadOK = false;
                    problemasEncontrados++;
                }
                
                // Verificar doctor
                Doctor doctor = buscarDoctorPorID(historial.DoctorID);
                if (doctor.id == -1 || doctor.eliminado) {
                    std::cout << "  ❌ Historial #" << historial.id << ": Doctor ID " << historial.DoctorID << " no existe" << std::endl;
                    integridadOK = false;
                    problemasEncontrados++;
                }
            }
        }
        archivoHistoriales.close();
    }

    // 3. VERIFICAR PACIENTES: que citasIDs[] sean válidos
    std::cout << "Verificando pacientes..." << std::endl;
    ArchivoHeader headerPacientes = leerHeader(FILE_PACIENTES);
    ifstream archivoPacientes(FILE_PACIENTES, ios::binary);
    
    if (archivoPacientes.is_open()) {
        archivoPacientes.seekg(sizeof(ArchivoHeader));
        Paciente paciente;
        
        for (int i = 0; i < headerPacientes.cantidadRegistros; i++) {
            archivoPacientes.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
            if (archivoPacientes.fail()) break;
            
            if (!paciente.eliminado) {
                // Verificar cada cita en el array del paciente
                for (int j = 0; j < paciente.cantidadCitas; j++) {
                    int citaID = paciente.citasIDs[j];
                    if (citaID != -1) { // -1 significa slot vacío
                        Cita cita = buscarCitaPorID(citaID);
                        if (cita.id == -1 || cita.eliminado) {
                            std::cout << "  ❌ Paciente #" << paciente.id << ": Cita ID " << citaID << " no existe" << std::endl;
                            integridadOK = false;
                            problemasEncontrados++;
                        }
                    }
                }
            }
        }
        archivoPacientes.close();
    }

    // 4. VERIFICAR DOCTORES: que citasIDs[] y pacientesIDs[] sean válidos
    std::cout << "Verificando doctores..." << std::endl;
    ArchivoHeader headerDoctores = leerHeader(FILE_DOCTORES);
    ifstream archivoDoctores(FILE_DOCTORES, ios::binary);
    
    if (archivoDoctores.is_open()) {
        archivoDoctores.seekg(sizeof(ArchivoHeader));
        Doctor doctor;
        
        for (int i = 0; i < headerDoctores.cantidadRegistros; i++) {
            archivoDoctores.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
            if (archivoDoctores.fail()) break;
            
            if (!doctor.eliminado) {
                // Verificar citas del doctor
                for (int j = 0; j < doctor.cantidadCitas; j++) {
                    int citaID = doctor.citasIDs[j];
                    if (citaID != -1) {
                        Cita cita = buscarCitaPorID(citaID);
                        if (cita.id == -1 || cita.eliminado) {
                            std::cout << "  ❌ Doctor #" << doctor.id << ": Cita ID " << citaID << " no existe" << std::endl;
                            integridadOK = false;
                            problemasEncontrados++;
                        }
                    }
                }
                
                // Verificar pacientes del doctor
                for (int j = 0; j < doctor.cantidadPacientes; j++) {
                    int pacienteID = doctor.pacientesIDs[j];
                    if (pacienteID != -1) {
                        Paciente paciente = buscarPacientePorID(pacienteID);
                        if (paciente.id == -1 || paciente.eliminado) {
                            std::cout << "  ❌ Doctor #" << doctor.id << ": Paciente ID " << pacienteID << " no existe" << std::endl;
                            integridadOK = false;
                            problemasEncontrados++;
                        }
                    }
                }
            }
        }
        archivoDoctores.close();
    }

    // 5. REPORTAR RESULTADOS
    std::cout << "\n=== RESULTADO DE LA VERIFICACIÓN ===" << std::endl;
    if (integridadOK) {
        std::cout << "✅ Integridad referencial: CORRECTA" << std::endl;
        std::cout << "No se encontraron problemas de referencias" << std::endl;
    } else {
        std::cout << "❌ Integridad referencial: CON PROBLEMAS" << std::endl;
        std::cout << "Se encontraron " << problemasEncontrados << " problemas de referencias" << std::endl;
        
        // 6. OFRECER REPARACIÓN AUTOMÁTICA
        std::cout << "\n¿Desea intentar reparación automática? (s/n): ";
        char opcion;
        std::cin >> opcion;
        std::cin.ignore();
        
        if (opcion == 's' || opcion == 'S') {
            return verificarIntegridadReferencial();
        }
    }
    
    return integridadOK;
}

bool repararIntegridadReferencial() {
    std::cout << "\n=== INICIANDO REPARACIÓN AUTOMÁTICA ===" << std::endl;
    int reparacionesRealizadas = 0;

    // REPARAR CITAS con referencias rotas
    ArchivoHeader headerCitas = leerHeader(FILE_CITAS);
    fstream archivoCitas(FILE_CITAS, ios::binary | ios::in | ios::out);
    
    if (archivoCitas.is_open()) {
        archivoCitas.seekg(sizeof(ArchivoHeader));
        Cita cita;
        
        for (int i = 0; i < headerCitas.cantidadRegistros; i++) {
            long posicion = archivoCitas.tellg();
            archivoCitas.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
            if (archivoCitas.fail()) break;
            
            if (!cita.eliminado) {
                bool necesitaReparar = false;
                
                // Verificar y reparar paciente
                Paciente paciente = buscarPacientePorID(cita.PacienteID);
                if (paciente.id == -1 || paciente.eliminado) {
                    cita.PacienteID = -1; // Marcar como referencia rota
                    necesitaReparar = true;
                }
                
                // Verificar y reparar doctor
                Doctor doctor = buscarDoctorPorID(cita.DoctorID);
                if (doctor.id == -1 || doctor.eliminado) {
                    cita.DoctorID = -1; // Marcar como referencia rota
                    necesitaReparar = true;
                }
                
                if (necesitaReparar) {
                    archivoCitas.seekp(posicion);
                    archivoCitas.write(reinterpret_cast<const char*>(&cita), sizeof(Cita));
                    archivoCitas.seekg(posicion + sizeof(Cita));
                    reparacionesRealizadas++;
                    std::cout << "  🔧 Cita #" << cita.id << ": Referencias reparadas" << std::endl;
                }
            }
        }
        archivoCitas.close();
    }

    // REPARAR HISTORIALES con referencias rotas
    ArchivoHeader headerHistoriales = leerHeader(FILE_HISTORIALES);
    fstream archivoHistoriales(FILE_HISTORIALES, ios::binary | ios::in | ios::out);
    
    if (archivoHistoriales.is_open()) {
        archivoHistoriales.seekg(sizeof(ArchivoHeader));
        HistorialMedico historial;
        
        for (int i = 0; i < headerHistoriales.cantidadRegistros; i++) {
            long posicion = archivoHistoriales.tellg();
            archivoHistoriales.read(reinterpret_cast<char*>(&historial), sizeof(HistorialMedico));
            if (archivoHistoriales.fail()) break;
            
            if (!historial.eliminado) {
                bool necesitaReparar = false;
                
                // Verificar y reparar paciente
                Paciente paciente = buscarPacientePorID(historial.PacienteID);
                if (paciente.id == -1 || paciente.eliminado) {
                    historial.PacienteID = -1;
                    necesitaReparar = true;
                }
                
                // Verificar y reparar doctor
                Doctor doctor = buscarDoctorPorID(historial.DoctorID);
                if (doctor.id == -1 || doctor.eliminado) {
                    historial.DoctorID = -1;
                    necesitaReparar = true;
                }
                
                if (necesitaReparar) {
                    archivoHistoriales.seekp(posicion);
                    archivoHistoriales.write(reinterpret_cast<const char*>(&historial), sizeof(HistorialMedico));
                    archivoHistoriales.seekg(posicion + sizeof(HistorialMedico));
                    reparacionesRealizadas++;
                    std::cout << "  🔧 Historial #" << historial.id << ": Referencias reparadas" << std::endl;
                }
            }
        }
        archivoHistoriales.close();
    }

    std::cout << "\n=== REPARACIÓN COMPLETADA ===" << std::endl;
    std::cout << "Reparaciones realizadas: " << reparacionesRealizadas << std::endl;
    
    return (reparacionesRealizadas > 0);
}
void hacerRespaldo() {
    const char* archivos[] = { "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin" };
    for (const char* nombre : archivos) {
        std::ifstream origen(nombre, std::ios::binary);
        std::ofstream destino((std::string("respaldo_") + nombre).c_str(), std::ios::binary);
        if (origen && destino) {
            destino << origen.rdbuf();
            std::cout << " Respaldo creado para " << nombre << "\n";
        } else {
            std::cout << " Error al respaldar " << nombre << "\n";
        }
    }
}

void restaurarRespaldo() {
    const char* archivos[] = { "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin" };
    for (const char* nombre : archivos) {
        std::ifstream respaldo((std::string("respaldo_") + nombre).c_str(), std::ios::binary);
        std::ofstream destino(nombre, std::ios::binary | std::ios::trunc);
        if (respaldo && destino) {
            destino << respaldo.rdbuf();
            std::cout << " Restaurado desde respaldo: " << nombre << "\n";
        } else {
            std::cout << " Error al restaurar " << nombre << "\n";
        }
    }
}

void mostrarEstadisticas() {
    const char* archivos[] = { "pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin" };
    for (const char* nombre : archivos) {
        std::ifstream archivo(nombre, std::ios::binary);
        if (!archivo.is_open()) {
            std::cout << " No se pudo abrir " << nombre << "\n";
            continue;
        }

        ArchivoHeader header;
        archivo.read((char*)&header, sizeof(header));
        std::cout  << nombre << ": " << header.cantidadRegistros  << "\n";
        archivo.close();
    }
}

//===========================================================
// 5. INTERFAZ DE USUARIO
//===========================================================
// Menú de pacientes
void menuPacientes() {
    int opcion; 
    char buffer[100]; 
    do {
        std::cout << "\n╔═════════════════════════════════════╗" << endl;
        std::cout << "║         GESTIÓN DE PACIENTES          ║" << endl;
        std::cout << "╠═══════════════════════════════════════╣" << endl;
        std::cout << "║ 1. Registrar nuevo paciente           ║" << endl;
        std::cout << "║ 2. Buscar paciente por ID             ║" << endl;
        std::cout << "║ 3. Buscar paciente por cédula         ║" << endl;
        std::cout << "║ 4. Buscar paciente por nombre         ║" << endl;
        std::cout << "║ 5. Ver historial médico completo      ║" << endl;
        std::cout << "║ 6.Actualizar datos del paciente       ║" << endl;
        std::cout << "║ 7. Listar todos los pacientes         ║" << endl;
        std::cout << "║ 8. Eliminar paciente                  ║" << endl;
        std::cout << "║ 0. Volver al menú principal           ║" << endl;
        std::cout << "╚═══════════════════════════════════════╝" << endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        limpiarBuffer();
        
               switch (opcion) {
            case 1: {
                // Registrar nuevo paciente
                Paciente nuevoPaciente = capturarDatosPaciente();
                
                std::cout << "Nombre: ";
                std::cin.getline(nuevoPaciente.nombre, 50);
                
                std::cout << "Apellido: ";
                std::cin.getline(nuevoPaciente.apellido, 50);
                
                std::cout << "Cédula: ";
                std::cin.getline(nuevoPaciente.cedula, 20);
                
                // Validar que no exista cédula
                if (ExistePacienteConCedula(nuevoPaciente.cedula)) {
                    mostrarError("Ya existe un paciente con esta cédula");
                    break;
                }
                
                std::cout << "Edad: ";
                std::cin >> nuevoPaciente.edad;
                std::cin.ignore();
                
                if (!validarEdad(nuevoPaciente.edad)) {
                    break;
                }
                
                std::cout << "Sexo (M/F): ";
                std::cin >> nuevoPaciente.sexo;
                std::cin.ignore();
                
                if (!validarSexo(nuevoPaciente.sexo)) {
                    break;
                }
                
                // Campos opcionales
                std::cout << "Teléfono (opcional): ";
                std::cin.getline(nuevoPaciente.telefono, 15);
                
                std::cout << "Email (opcional): ";
                std::cin.getline(nuevoPaciente.email, 50);
                
                std::cout << "Tipo de sangre (opcional): ";
                std::cin.getline(nuevoPaciente.tipoSangre, 5);
                
                std::cout << "Alergias (opcional): ";
                std::cin.getline(nuevoPaciente.alergias, 500);
                
                std::cout << "Observaciones (opcional): ";
                std::cin.getline(nuevoPaciente.observaciones, 500);
                
                if (agregarPaciente(nuevoPaciente)) {
                    mostrarExito("Paciente registrado correctamente");
                } else {
                    mostrarError("Error al registrar paciente");
                }
                break;
            }
            
            case 2: {
                // Buscar paciente por ID
                int id;
                std::cout << "Ingrese ID del paciente: ";
                std::cin >> id;
                std::cin.ignore();
                
                Paciente paciente = buscarPacientePorID(id);
                if (paciente.id != -1) {
                    std::cout << "\n=== DATOS DEL PACIENTE ===" << std::endl;
                    std::cout << "ID: " << paciente.id << std::endl;
                    std::cout << "Nombre: " << paciente.nombre << " " << paciente.apellido << std::endl;
                    std::cout << "Cédula: " << paciente.cedula << std::endl;
                    std::cout << "Edad: " << paciente.edad << std::endl;
                    std::cout << "Sexo: " << paciente.sexo << std::endl;
                    std::cout << "Teléfono: " << paciente.telefono << std::endl;
                    std::cout << "Email: " << paciente.email << std::endl;
                    std::cout << "Tipo de sangre: " << paciente.tipoSangre << std::endl;
                    std::cout << "Alergias: " << paciente.alergias << std::endl;
                    std::cout << "Observaciones: " << paciente.observaciones << std::endl;
                    std::cout << "Consultas realizadas: " << paciente.cantidadConsultas << std::endl;
                    std::cout << "Citas agendadas: " << paciente.cantidadCitas << std::endl;
                } else {
                    mostrarError("Paciente no encontrado");
                }
                break;
            }
            
            case 3: {
                // Buscar paciente por cédula
                char cedula[20];
                std::cout << "Ingrese cédula del paciente: ";
                std::cin.getline(cedula, 20);
                
                Paciente paciente = buscarPacientePorCedula(cedula);
                if (paciente.id != 0) {
                    std::cout << "\n=== DATOS DEL PACIENTE ===" << std::endl;
                    std::cout << "ID: " << paciente.id << std::endl;
                    std::cout << "Nombre: " << paciente.nombre << " " << paciente.apellido << std::endl;
                    std::cout << "Cédula: " << paciente.cedula << std::endl;
                    std::cout << "Edad: " << paciente.edad << std::endl;
                    std::cout << "Teléfono: " << paciente.telefono << std::endl;
                } else {
                    mostrarError("Paciente no encontrado");
                }
                break;
            }
             case 4: {
    // Buscar paciente por nombre
    char nombre[50];
    std::cout << "Ingrese nombre del paciente: ";
    std::cin.getline(nombre, 50);
    
    Paciente paciente = buscarPacientePorNombre(nombre);
    if (paciente.id != 0) {
        std::cout << "\n=== PACIENTE ENCONTRADO ===" << std::endl;
        std::cout << "ID: " << paciente.id << std::endl;
        std::cout << "Nombre: " << paciente.nombre << " " << paciente.apellido << std::endl;
        std::cout << "Cédula: " << paciente.cedula << std::endl;
        std::cout << "Edad: " << paciente.edad << std::endl;
        std::cout << "Sexo: " << paciente.sexo << std::endl;
        std::cout << "Teléfono: " << paciente.telefono << std::endl;
        std::cout << "Email: " << paciente.email << std::endl;
        std::cout << "Tipo de sangre: " << paciente.tipoSangre << std::endl;
        std::cout << "Consultas realizadas: " << paciente.cantidadConsultas << std::endl;
    } else {
        mostrarError("Paciente no encontrado");
    }
    break;
}
              case 5: {
    int id;
    std::cout << "Ingrese ID del paciente: ";
    std::cin >> id;
    std::cin.ignore();
    int cantidad;
    HistorialMedico* historial = leerHistorialCompleto(id, &cantidad);
    
    if (historial != NULL && cantidad > 0) {
        std::cout << "\n=== HISTORIAL MÉDICO ===" << std::endl;
        for (int i = 0; i < cantidad; i++) {
            std::cout << "Consulta #" << historial[i].id << " | ";
            std::cout << "Fecha: " << historial[i].fecha << " | ";
            std::cout << "Diagnóstico: " << historial[i].diagnostico << std::endl;
        }
        delete[] historial; // Liberar memoria
    } else {
        std::cout << "No se encontró historial médico para este paciente." << std::endl;
    }
    break;
}
                case 6: {
                // Modificar paciente
                int id;
                std::cout << "Ingrese ID del paciente a modificar: ";
                std::cin >> id;
                std::cin.ignore();
                
                if (modificarPacienteDesdeTeclado(id)) {
                    mostrarExito("Paciente modificado correctamente");
                } else {
                    mostrarError("Error al modificar paciente");
                }
                break;
            }
              case 7: {
                // Listar todos los pacientes
                listarTodosPacientes();
                break;
            }
            case 8: {
                // Eliminar paciente
                int id;
                std::cout << "Ingrese ID del paciente a eliminar: ";
                std::cin >> id;
                std::cin.ignore();
                
                std::cout << "¿Está seguro de eliminar este paciente? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                std::cin.ignore();
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (eliminarPaciente(id)) {
                        mostrarExito("Paciente eliminado correctamente");
                    } else {
                        mostrarError("Error al eliminar paciente");
                    }
                } else {
                    std::cout << "Eliminación cancelada" << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
                
            default:
                std::cout << "❌ Opción inválida. Intente nuevamente." << std::endl;
        }
        
        if (opcion != 9) {
            pausar();
        }
        
    } while (opcion != 0);
}
void menuDoctores() {
    int opcion;
    
    do {
        std::cout << "\n╔════════════════════════════════════════╗" << endl;
        std::cout << "║          GESTIÓN DE DOCTORES          ║" << endl;
        std::cout << "╠════════════════════════════════════════╣" << endl;
        std::cout << "║ 1. Registrar nuevo doctor             ║" << endl;
        std::cout << "║ 2. Buscar doctor por ID               ║" << endl;
        std::cout << "║ 3. Buscar doctores por especialidad   ║" << endl;
        std::cout << "║ 4. Asignar paciente a doctor          ║" << endl;
        std::cout << "║ 5. Ver pacientes asignados a doctor   ║" << endl;
        std::cout << "║ 6. Listar todos los doctores          ║" << endl;
        std::cout << "║ 7. Eliminar doctor                    ║" << endl;
        std::cout << "║ 8. Actualizar datos del doctor        ║" << endl;
        std::cout << "║ 0. Volver al menú principal           ║" << endl;
        std::cout << "╚════════════════════════════════════════╝" << endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        limpiarBuffer();
        
        switch (opcion) {
            case 1: {
                // Registrar nuevo doctor
                Doctor nuevoDoctor;
                
                // Inicializar arrays
                nuevoDoctor.cantidadPacientes = 0;
                nuevoDoctor.cantidadCitas = 0;
                for (int i = 0; i < 50; i++) nuevoDoctor.pacientesIDs[i] = -1;
                for (int i = 0; i < 30; i++) nuevoDoctor.citasIDs[i] = -1;
                std::cout << "Nombre: ";
                std::cin.getline(nuevoDoctor.nombre, 50);
                std::cout << "Apellido: ";
                std::cin.getline(nuevoDoctor.apellido, 50);
                std::cout << "Cédula profesional: ";
                std::cin.getline(nuevoDoctor.cedula, 20);
                std::cout << "Especialidad: ";
                std::cin.getline(nuevoDoctor.especialidad, 50);
                std::cout << "Años de experiencia: ";
                std::cin >> nuevoDoctor.aniosExperiencia;
                std::cin.ignore();
                std::cout << "Costo de consulta: ";
                std::cin >> nuevoDoctor.costoConsulta;
                std::cin.ignore();
                if (!validarDatosDoctor(nuevoDoctor.aniosExperiencia, nuevoDoctor.costoConsulta)) {
                    break;
                }
                
                // Campos opcionales
                std::cout << "Horario de atención (opcional): ";
                std::cin.getline(nuevoDoctor.horarioAtencion, 50);
                std::cout << "Teléfono (opcional): ";
                std::cin.getline(nuevoDoctor.telefono, 15);
                std::cout << "Email (opcional): ";
                std::cin.getline(nuevoDoctor.email, 50);
                nuevoDoctor.disponible = true;
                nuevoDoctor.eliminado = false;
                if (agregarDoctor(nuevoDoctor)) {
                    mostrarExito("Doctor registrado correctamente");
                } else {
                    mostrarError("Error al registrar doctor");
                }
                break;
            }
            
            case 2: {
                // Buscar doctor por ID
                int id;
                std::cout << "Ingrese ID del doctor: ";
                std::cin >> id;
                std::cin.ignore();
                
                Doctor doctor = buscarDoctorPorID(id);
                if (doctor.id != -1) {
                    std::cout << "\n=== DATOS DEL DOCTOR ===" << std::endl;
                    std::cout << "ID: " << doctor.id << std::endl;
                    std::cout << "Nombre: " << doctor.nombre << " " << doctor.apellido << std::endl;
                    std::cout << "Cédula: " << doctor.cedula << std::endl;
                    std::cout << "Especialidad: " << doctor.especialidad << std::endl;
                    std::cout << "Años experiencia: " << doctor.aniosExperiencia << std::endl;
                    std::cout << "Costo consulta: $" << doctor.costoConsulta << std::endl;
                    std::cout << "Teléfono: " << doctor.telefono << std::endl;
                    std::cout << "Email: " << doctor.email << std::endl;
                    std::cout << "Horario: " << doctor.horarioAtencion << std::endl;
                    std::cout << "Disponible: " << (doctor.disponible ? "Sí" : "No") << std::endl;
                    std::cout << "Pacientes asignados: " << doctor.cantidadPacientes << std::endl;
                    std::cout << "Citas agendadas: " << doctor.cantidadCitas << std::endl;
                } else {
                    mostrarError("Doctor no encontrado");
                }
                break;
            }
            
            case 3: {
                // Buscar doctor por especialidad
                char especialidad[50];
                std::cout << "Ingrese especialidad: ";
                std::cin.getline(especialidad, 50);
                
                buscarDoctoresPorEspecialidad(especialidad);
                break;
            }
            
            case 4: {
                // Asignar paciente a doctor
                int idDoctor, idPaciente;
                std::cout << "Ingrese ID del doctor: ";
                std::cin >> idDoctor;
                std::cout << "Ingrese ID del paciente: ";
                std::cin >> idPaciente;
                std::cin.ignore();
                
                if (asignarPacienteADoctor(idDoctor, idPaciente)) {
                    mostrarExito("Paciente asignado correctamente al doctor");
                } else {
                    mostrarError("Error al asignar paciente al doctor");
                }
                break;
            }
            
            case 5: {
                // Ver pacientes asignados
                int id;
                std::cout << "Ingrese ID del doctor: ";
                std::cin >> id;
                std::cin.ignore();
                
                listarPacientesDeDoctor(id);
                break;
            }
            
            case 6: {
                // Listar todos los doctores
                listarTodosDoctores();
                break;
            }
            
            case 7: {
                // Eliminar doctor
                int id;
                std::cout << "Ingrese ID del doctor a eliminar: ";
                std::cin >> id;
                std::cin.ignore();
                
                std::cout << "¿Está seguro de eliminar este doctor? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                std::cin.ignore();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (eliminarDoctor(id)) {
                        mostrarExito("Doctor eliminado correctamente");
                    } else {
                        mostrarError("Error al eliminar doctor");
                    }
                } else {
                    std::cout << "Eliminación cancelada" << std::endl;
                }
                break;
            }
            
            case 8: {
                // Modificar doctor
                int id;
                std::cout << "Ingrese ID del doctor a modificar: ";
                std::cin >> id;
                std::cin.ignore();
                
                if (modificarDoctorDesdeTeclado(id)) {
                    mostrarExito("Doctor modificado correctamente");
                } else {
                    mostrarError("Error al modificar doctor");
                }
                break;
            }
            
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
                
            default:
                std::cout << "❌ Opción inválida. Intente nuevamente." << std::endl;
        }
        
        if (opcion != 0) {
            pausar();
        }
        
    } while (opcion != 0);
}
    void menuCitas() {
    int opcion;    
    
    do {
         std::cout << "\n╔════════════════════════════════════════╗" << endl;
         std::cout << "║           GESTIÓN DE CITAS            ║" << endl;
         std::cout << "╠════════════════════════════════════════╣" << endl;
         std::cout << "║ 1. Agendar nueva cita                 ║" << endl;
         std::cout << "║ 2. Cancelar cita                      ║" << endl;
         std::cout << "║ 3. Atender cita                       ║" << endl;
         std::cout << "║ 4. Ver citas de un paciente           ║" << endl;
         std::cout << "║ 5. Ver citas de un doctor             ║" << endl;
         std::cout << "║ 6. Ver citas de una fecha             ║" << endl;
         std::cout << "║ 7. Ver citas pendientes               ║" << endl;
         std::cout << "║ 0. Volver al menú principal           ║" << endl;
         std::cout << "╚════════════════════════════════════════╝" << endl;
         std::cout << "Seleccione una opción: ";
         std::cin >> opcion;
        limpiarBuffer();
        
        switch (opcion) {
            case 1: {
                // Agendar nueva cita
                int pacienteID, doctorID;
                char fecha[11], hora[6], motivo[150];
                
                std::cout << "\n=== AGENDAR NUEVA CITA ===" << std::endl;
                std::cout << "ID del paciente: ";
                std::cin >> pacienteID;
                std::cout << "ID del doctor: ";
                std::cin >> doctorID;
                limpiarBuffer();
                
                std::cout << "Fecha (YYYY-MM-DD): ";
                std::cin.getline(fecha, 11);
                
                std::cout << "Hora (HH:MM): ";
                std::cin.getline(hora, 6);
                
                std::cout << "Motivo: ";
                std::cin.getline(motivo, 150);
                
                if (agendarNuevaCita(pacienteID, doctorID, fecha, hora, motivo)) {
                    mostrarExito("Cita agendada correctamente");
                } else {
                    mostrarError("Error al agendar cita");
                }
                break;
            }
            
            case 2: {
                // Cancelar cita
                int idCita;
                std::cout << "\n=== CANCELAR CITA ===" << std::endl;
                std::cout << "ID de la cita a cancelar: ";
                std::cin >> idCita;
                limpiarBuffer();
                
                if (cancelarCita(idCita)) {
                    mostrarExito("Cita cancelada correctamente");
                } else {
                    mostrarError("Error al cancelar cita");
                }
                break;
            }
            
                case 3: {
                // Atender cita
                int idCita;
                char diagnostico[200], tratamiento[200], medicamentos[150];
                float costo;
                
                std::cout << "\n=== ATENDER CITA ===" << std::endl;
                std::cout << "ID de la cita a atender: ";
                std::cin >> idCita;
                limpiarBuffer();
                
                std::cout << "Diagnóstico: ";
                std::cin.getline(diagnostico, 200);
                
                std::cout << "Tratamiento: ";
                std::cin.getline(tratamiento, 200);
                
                std::cout << "Medicamentos: ";
                std::cin.getline(medicamentos, 150);
                
                std::cout << "Costo de la consulta: ";
                std::cin >> costo;
                limpiarBuffer();
                
                if (atenderCita(idCita, diagnostico, tratamiento, medicamentos, costo)) {
                    mostrarExito("Cita atendida correctamente");
                } else {
                    mostrarError("Error al atender cita");
                }
                break;

            }
case 4: {
    // Ver citas de un doctor
    int doctorID;
    std::cout << "\n=== CITAS DE DOCTOR ===" << std::endl;
    std::cout << "ID del doctor: ";
    std::cin >> doctorID;
    limpiarBuffer();
    
    int cantidad;
    Cita* citas = leerCitasDeDoctor(doctorID, &cantidad);
    
    if (citas != NULL) {
        Doctor doctor = buscarDoctorPorID(doctorID);
        std::cout << "\nCitas del Dr. " << doctor.nombre << " " << doctor.apellido << ":" << std::endl;
        
        for (int i = 0; i < cantidad; i++) {
            Paciente paciente = buscarPacientePorID(citas[i].PacienteID);
            std::string nombrePaciente = (paciente.id != -1) ? 
                std::string(paciente.nombre) + " " + paciente.apellido : "N/A";
            
            std::cout << "Cita #" << citas[i].id << " | ";
            std::cout << "Fecha: " << citas[i].fecha << " | ";
            std::cout << "Hora: " << citas[i].hora << " | ";
            std::cout << "Paciente: " << nombrePaciente << " | ";
            std::cout << "Estado: " << citas[i].estado << std::endl;
        }
        std::cout << "Total: " << cantidad << " citas" << std::endl;
        
        delete[] citas;
    } else {
        std::cout << "No se encontraron citas para este doctor." << std::endl;
    }
    break;
    }
            
                      case 6: {
                // Ver citas de una fecha
                char fecha[11];
                std::cout << "\n=== CITAS POR FECHA ===" << std::endl;
                std::cout << "Fecha (YYYY-MM-DD): ";
                std::cin.getline(fecha, 11);
                
                int cantidad;
                Cita* citas = leerCitasPorFecha(fecha, &cantidad);
                
                if (citas != NULL) {
                    std::cout << "\n=== CITAS PARA " << fecha << " ===" << std::endl;
                    for (int i = 0; i < cantidad; i++) {
                        Paciente paciente = buscarPacientePorID(citas[i].PacienteID);
                        Doctor doctor = buscarDoctorPorID(citas[i].DoctorID);
                        
                        std::cout << "Cita #" << citas[i].id << " | ";
                        std::cout << "Hora: " << citas[i].hora << " | ";
                        std::cout << "Paciente: " << paciente.nombre << " " << paciente.apellido << " | ";
                        std::cout << "Doctor: " << doctor.nombre << " " << doctor.apellido << " | ";
                        std::cout << "Estado: " << citas[i].estado << std::endl;
                    }
                    std::cout << "Total: " << cantidad << " citas" << std::endl;
                    
                    delete[] citas;
                } else {
                    std::cout << "No hay citas para esta fecha." << std::endl;
                }
                break;
            }
            
            case 7: {
                // Ver citas pendientes
                listarCitasPendientes();
                break;
            }
            
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
                
            default:
                std::cout << "❌ Opción inválida. Intente nuevamente." << std::endl;
        }
        
        if (opcion != 0) {
            pausar();
        }
        
    } while (opcion != 0);
}
void menuMantenimiento() {
    int opcion;
    do {
        std::cout << "\n=== MANTENIMIENTO DE ARCHIVOS ===" << std::endl;
        std::cout << "1. Verificar integridad de archivos" << std::endl;
        std::cout << "2. Verificar integridad referencial" << std::endl;
        std::cout << "3. Compactar archivo de pacientes" << std::endl;
        std::cout << "4. Compactar archivo de doctores" << std::endl;
        std::cout << "5. Compactar archivo de citas" << std::endl;
        std::cout << "6. Compactar archivo de historiales" << std::endl;;
        std::cout << "7. Reiniciar archivo paciente" << std::endl;
        std::cout << "8. Reiniciar archivo doctores" << std::endl;;
        std::cout << "9. reiniciar archivo citas" << std::endl;
        std::cout << "10. hacer respaldo" << std::endl;
        std::cout << "11. restaurar respaldo" << std::endl;
        std::cout << "12. mostrar estadisticas" << std::endl;
        std::cout << "13. volver a menu principal" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: {
                // Verificar integridad de archivos
                if (verificarIntegridadArchivos()) {
                    mostrarExito("Todos los archivos están en buen estado");
                } else {
                    mostrarError("Se encontraron problemas en algunos archivos");
                }
                break;
            }
            
            case 2: {
                // Verificar integridad referencial
                if (verificarIntegridadReferencial()) {
                    mostrarExito("Integridad referencial verificada correctamente");
                } else {
                    mostrarError("Se encontraron problemas de integridad referencial");
                }
                break;
            }
            
            case 3: {
                // Compactar archivo de pacientes
                std::cout << "¿Está seguro de compactar el archivo de pacientes? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                std::cin.ignore();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (compactarArchivoPacientes()) {
                        mostrarExito("Archivo de pacientes compactado exitosamente");
                    } else {
                        mostrarError("Error al compactar archivo de pacientes");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            
            case 4: {
                // Compactar archivo de doctores
                std::cout << "¿Está seguro de compactar el archivo de doctores? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                std::cin.ignore();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (compactarArchivoDoctores()) {
                        mostrarExito("Archivo de doctores compactado exitosamente");
                    } else {
                        mostrarError("Error al compactar archivo de doctores");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            case 5: {
                // Compactar archivo de citas
                std::cout << "¿Está seguro de compactar el archivo de citas? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                std::cin.ignore();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (compactarArchivoCitas()) {
                        mostrarExito("Archivo de citas compactado exitosamente");
                    } else {
                        mostrarError("Error al compactar archivo de citas");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            case 6: {
                // Compactar archivo de historiales
                std::cout << "¿Está seguro de compactar el archivo de historiales? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                std::cin.ignore();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (compactarArchivoHistoriales()) {
                        mostrarExito("Archivo de historiales compactado exitosamente");
                    } else {
                        mostrarError("Error al compactar archivo de historiales");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            case 7:
            //reiniciar archivo de paciente
            reiniciarArchivoPacientes();break;
            case 8:
            //reiniciar archivo doctor
            reiniciarArchivoDoctores();break;

            case 9:
            //reiniciar archivo doctor
            reiniciarArchivoDoctores();break;
            
            case 10:
            //hacer respaldo
            hacerRespaldo();
            case 11:
            //restaurar respaldo
            restaurarRespaldo();
            case 12:
            //mostrar estadisticas
            mostrarEstadisticas();
            case 13:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
                
            default:
                std::cout << "❌ Opción inválida. Intente nuevamente." << std::endl;
        }
        
        if (opcion != 13) {
            pausar();
        }
        
    } while (opcion != 13);
}


//=========================================================================
// PUNTO DE ENTRADA PRINCIPAL
// =========================================================================

void iniciarSistema() {
    // Inicializar hospital (sin puntero, por valor)
    Hospital hospital = inicializarHospital("Hospital Costanza");
    
    int opcion;
    do {
       // Menú principal

    std::cout << "\n╔══════════════════════════════════════╗" << endl;
    std::cout << "║   SISTEMA DE GESTIÓN HOSPITALARIA V2   ║" << endl;
    std::cout << "╠════════════════════════════════════════╣" << endl;
    std::cout << "║ 1. Gestión de Pacientes                ║" << endl;
    std::cout << "║ 2. Gestión de Doctores                 ║" << endl;
    std::cout << "║ 3. Gestión de Citas                    ║" << endl;
    std::cout << "║                                        ║" << endl;
    std::cout << "║ 4.Mantenimiento de Archivos            ║" << endl;
    std::cout << "║ 5.Guardar y Salir                      ║" << endl;
    std::cout << "╚════════════════════════════════════════╝" << endl;
    std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        limpiarBuffer();
        
        switch(opcion) {
            case 1:
                menuPacientes();  
                break;
            case 2:
                menuDoctores();  
                break;
            case 3:
                menuCitas();      
                break;
            
            case 4:
                menuMantenimiento();      // Nueva opción
                break;
            case 5:
                // GUARDAR Y SALIR
                if (guardarDatosHospital(hospital)) {
                    std::cout << "\n✅ Datos guardados correctamente." << std::endl;
                } else {
                    std::cout << "\n⚠️  Advertencia: Hubo problemas al guardar algunos datos." << std::endl;
                }
                std::cout << "👋 ¡Hasta luego!" << std::endl;
                break;
            default:
                mostrarError("Opción no válida");
        }
    } while (opcion != 5);  
}
int main() {
    iniciarSistema();
    return 0;
}
