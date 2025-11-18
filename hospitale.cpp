#include <iostream>
#include <cstring>
#include <ctime> 
#include <iomanip>
#include <cctype>
#include <fstream>
#include <cstddef>
using namespace std;

// =============================================
// CONSTANTES
// =============================================
const char FILE_HOSPITAL[] = "hospital.bin";
const char FILE_PACIENTES[] = "pacientes.bin";
const char FILE_DOCTORES[] = "doctores.bin";
const char FILE_CITAS[] = "citas.bin";
const char FILE_HISTORIALES[] = "historiales.bin";

struct ArchivoHeader {
    int cantidadRegistros;
    int siguienteId;
    int registrosActivos;
    int version;
};

// =============================================
// CLASE PACIENTE
// =============================================
class Paciente {
private:
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
    int cantidadConsultas;
    int primerConsultaID;
    int cantidadCitas;
    int citasIDs[20];
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    Paciente();
    
    // Getters
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedula() const;
    int getEdad() const;
    char getSexo() const;
    const char* getTelefono() const;
    const char* getEmail() const;
    bool getEliminado() const;
    int getCantidadCitas() const;
    int getCantidadConsultas() const;
    int getPrimerConsultaID() const;
    time_t getFechaModificacion() const;
    
    // Setters
    void setId(int id);
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setCedula(const char* cedula);
    void setEdad(int edad);
    void setSexo(char sexo);
    void setTelefono(const char* telefono);
    void setEmail(const char* email);
    void setEliminado(bool eliminado);
    void setFechaModificacion(time_t tiempo);
    void setFechaCreacion(time_t tiempo);
    void setCantidadConsultas(int cantidad);
    void setPrimerConsultaID(int id);
    
    bool agregarCitaID(int citaID);
    bool validarDatos() const;
    static size_t obtenerTamano();
};

Paciente::Paciente() {
    id = 0;
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(cedula, "");
    edad = 0;
    sexo = ' ';
    strcpy(tipoSangre, "");
    strcpy(telefono, "");
    strcpy(direccion, "");
    strcpy(email, "");
    strcpy(alergias, "");
    strcpy(observaciones, "");
    activo = true;
    cantidadConsultas = 0;
    primerConsultaID = -1;
    cantidadCitas = 0;
    for(int i = 0; i < 20; i++) citasIDs[i] = -1;
    eliminado = false;
    fechaCreacion = time(0);
    fechaModificacion = time(0);
}

// Getters
int Paciente::getId() const { return id; }
const char* Paciente::getNombre() const { return nombre; }
const char* Paciente::getApellido() const { return apellido; }
const char* Paciente::getCedula() const { return cedula; }
int Paciente::getEdad() const { return edad; }
char Paciente::getSexo() const { return sexo; }
const char* Paciente::getTelefono() const { return telefono; }
const char* Paciente::getEmail() const { return email; }
bool Paciente::getEliminado() const { return eliminado; }
int Paciente::getCantidadCitas() const { return cantidadCitas; }
int Paciente::getCantidadConsultas() const { return cantidadConsultas; }
int Paciente::getPrimerConsultaID() const { return primerConsultaID; }
time_t Paciente::getFechaModificacion() const { return fechaModificacion; }


// Setters
void Paciente::setId(int id) { this->id = id; }
void Paciente::setNombre(const char* nombre) { strncpy(this->nombre, nombre, 49); this->nombre[49] = '\0'; }
void Paciente::setApellido(const char* apellido) { strncpy(this->apellido, apellido, 49); this->apellido[49] = '\0'; }
void Paciente::setCedula(const char* cedula) { strncpy(this->cedula, cedula, 19); this->cedula[19] = '\0'; }
void Paciente::setEdad(int edad) { this->edad = edad; }
void Paciente::setSexo(char sexo) { this->sexo = sexo; }
void Paciente::setTelefono(const char* telefono) { strncpy(this->telefono, telefono, 14); this->telefono[14] = '\0'; }
void Paciente::setEmail(const char* email) { strncpy(this->email, email, 49); this->email[49] = '\0'; }
void Paciente::setEliminado(bool eliminado) { this->eliminado = eliminado; }
void Paciente::setFechaModificacion(time_t tiempo) { fechaModificacion = tiempo; }
void Paciente::setFechaCreacion(time_t tiempo) { fechaCreacion = tiempo; }
void Paciente::setCantidadConsultas(int cantidad) { cantidadConsultas = cantidad; }
void Paciente::setPrimerConsultaID(int id) { primerConsultaID = id; }

bool Paciente::agregarCitaID(int citaID) {
    if(cantidadCitas < 20) {
        citasIDs[cantidadCitas] = citaID;
        cantidadCitas++;
        return true;
    }
    return false;
}

bool Paciente::validarDatos() const {
    return strlen(nombre) > 0 && strlen(apellido) > 0 && strlen(cedula) > 0 && edad >= 0;
}

size_t Paciente::obtenerTamano() { return sizeof(Paciente); }

// =============================================
// CLASE DOCTOR
// =============================================
class Doctor {
private:
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
    int cantidadPacientes;
    int pacientesIDs[50];
    int cantidadCitas;
    int citasIDs[30];
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    Doctor();
    
    // Getters
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getEspecialidad() const;
    float getCostoConsulta() const;
    bool getDisponible() const;
    bool getEliminado() const;
    int getCantidadPacientes() const;
    int getCantidadCitas() const;
    time_t getFechaModificacion() const;
    int getAniosExperiencia() const;
    const char* getTelefono() const;
    
    // Setters
    void setId(int id);
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setEspecialidad(const char* especialidad);
    void setCostoConsulta(float costo);
    void setDisponible(bool disp);
    void setEliminado(bool elim);
    void setFechaModificacion(time_t tiempo);
    void setFechaCreacion(time_t tiempo);
    void setAniosExperiencia(int anos);
    void setTelefono(const char* telefono);
    bool actualizarPacientesIDs(int mapaIDs[]);
    bool agregarPacienteID(int pacienteID);
    bool agregarCitaID(int citaID);
    bool validarDatos() const;
    static size_t obtenerTamano();
};

Doctor::Doctor() {
    id = 0;
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(cedula, "");
    strcpy(especialidad, "");
    aniosExperiencia = 0;
    costoConsulta = 0;
    strcpy(horarioAtencion, "");
    strcpy(telefono, "");
    strcpy(email, "");
    disponible = true;
    cantidadPacientes = 0;
    cantidadCitas = 0;
    for(int i = 0; i < 50; i++) pacientesIDs[i] = -1;
    for(int i = 0; i < 30; i++) citasIDs[i] = -1;
    eliminado = false;
    fechaCreacion = time(0);
    fechaModificacion = time(0);
}

// Getters
int Doctor::getId() const { return id; }
const char* Doctor::getNombre() const { return nombre; }
const char* Doctor::getApellido() const { return apellido; }
const char* Doctor::getEspecialidad() const { return especialidad; }
float Doctor::getCostoConsulta() const { return costoConsulta; }
bool Doctor::getDisponible() const { return disponible; }
bool Doctor::getEliminado() const { return eliminado; }
int Doctor::getCantidadPacientes() const { return cantidadPacientes; }
int Doctor::getCantidadCitas() const { return cantidadCitas; }
time_t Doctor::getFechaModificacion() const { return fechaModificacion; }
int Doctor::getAniosExperiencia() const { return aniosExperiencia; }
bool actualizarPacientesIDs(int mapaIDs[]);
bool actualizarCitasIDs(int mapaIDs[]);

// Setters
void Doctor::setId(int id) { this->id = id; }
void Doctor::setNombre(const char* nombre) { strncpy(this->nombre, nombre, 49); this->nombre[49] = '\0'; }
void Doctor::setApellido(const char* apellido) { strncpy(this->apellido, apellido, 49); this->apellido[49] = '\0'; }
void Doctor::setEspecialidad(const char* especialidad) { strncpy(this->especialidad, especialidad, 49); this->especialidad[49] = '\0'; }
void Doctor::setCostoConsulta(float costo) { costoConsulta = costo; }
void Doctor::setDisponible(bool disp) { disponible = disp; }
void Doctor::setEliminado(bool elim) { eliminado = elim; }
void Doctor::setFechaModificacion(time_t tiempo) { fechaModificacion = tiempo; }
void Doctor::setFechaCreacion(time_t tiempo) { fechaCreacion = tiempo; }
void Doctor::setAniosExperiencia(int anos) { aniosExperiencia = anos; }
bool Doctor::agregarPacienteID(int pacienteID) {
    if(cantidadPacientes < 50) {
        pacientesIDs[cantidadPacientes] = pacienteID;
        cantidadPacientes++;
        return true;
    }
    return false;
}

bool Doctor::agregarCitaID(int citaID) {
    if(cantidadCitas < 30) {
        citasIDs[cantidadCitas] = citaID;
        cantidadCitas++;
        return true;
    }
    return false;
}

bool Doctor::validarDatos() const {
    return strlen(nombre) > 0 && strlen(apellido) > 0 && strlen(especialidad) > 0 && costoConsulta >= 0;
}

size_t Doctor::obtenerTamano() { return sizeof(Doctor); }

// =============================================
// CLASE CITA
// =============================================
class Cita {
private:
    int id;
    int PacienteID;
    int DoctorID;
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];
    char observaciones[200];
    bool atendida;
    int consultaID;     
    char diagnostico[100];
    char tratamiento[100];
    char medicamentos[100];
    float costo;
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    Cita();
    
    // Getters
    int getId() const;
    int getPacienteID() const;
    int getDoctorID() const;
    const char* getFecha() const;
    const char* getHora() const;
    const char* getEstado() const;
    bool getAtendida() const;
    bool getEliminado() const;
    const char* getDiagnostico() const;
    const char* getTratamiento() const;
    const char* getMedicamentos() const;
    const char* getMotivo() const;
    time_t getFechaCreacion() const;  
    float getCosto() const;
    void setCosto(float costo);
    time_t getFechaModificacion() const;
    
    // Setters
    void setId(int id);
    void setPacienteID(int id);
    void setDoctorID(int id);
    void setFecha(const char* fecha);
    void setHora(const char* hora);
    void setMotivo(const char* motivo);
    void setEstado(const char* estado);
    void setAtendida(bool atendida);
    void setEliminado(bool elim);
    void setFechaModificacion(time_t tiempo);
    void setConsultaID(int id);
    void setDiagnostico(const char* diagnostico);
    void setTratamiento(const char* tratamiento);
    void setMedicamentos(const char* medicamentos);
    void setFechaCreacion(time_t tiempo); 

    bool validarDatos() const;
    static size_t obtenerTamano();
};

Cita::Cita() {
    id = 0;
    PacienteID = -1;
    DoctorID = -1;
    strcpy(fecha, "");
    strcpy(hora, "");
    strcpy(motivo, "");
    strcpy(estado, "Agendada");
    strcpy(observaciones, "");
    atendida = false;
    consultaID = -1;
    eliminado = false;
    fechaCreacion = time(0);
    fechaModificacion = time(0);
}

// Getters
int Cita::getId() const { return id; }
int Cita::getPacienteID() const { return PacienteID; }
int Cita::getDoctorID() const { return DoctorID; }
const char* Cita::getFecha() const { return fecha; }
const char* Cita::getHora() const { return hora; }
const char* Cita::getEstado() const { return estado; }
bool Cita::getAtendida() const { return atendida; }
bool Cita::getEliminado() const { return eliminado; }

// Setters
void Cita::setId(int id) { this->id = id; }
void Cita::setPacienteID(int id) { PacienteID = id; }
void Cita::setDoctorID(int id) { DoctorID = id; }
void Cita::setFecha(const char* fecha) { strncpy(this->fecha, fecha, 10); this->fecha[10] = '\0'; }
void Cita::setHora(const char* hora) { strncpy(this->hora, hora, 5); this->hora[5] = '\0'; }
void Cita::setMotivo(const char* motivo) { strncpy(this->motivo, motivo, 149); this->motivo[149] = '\0'; }
void Cita::setEstado(const char* estado) { strncpy(this->estado, estado, 19); this->estado[19] = '\0'; }
void Cita::setAtendida(bool atendida) { this->atendida = atendida; }
void Cita::setEliminado(bool elim) { eliminado = elim; }
void Cita::setFechaModificacion(time_t tiempo) { fechaModificacion = tiempo; }
void Cita::setConsultaID(int id) { consultaID = id; }

bool Cita::validarDatos() const {
    return PacienteID > 0 && DoctorID > 0 && strlen(fecha) > 0 && strlen(hora) > 0;

}
void Cita::setDiagnostico(const char* diagnostico) {
    strncpy(this->diagnostico, diagnostico, 99);
    this->diagnostico[99] = '\0';
}

void Cita::setTratamiento(const char* tratamiento) {
    strncpy(this->tratamiento, tratamiento, 99);
    this->tratamiento[99] = '\0';
}

void Cita::setMedicamentos(const char* medicamentos) {
    strncpy(this->medicamentos, medicamentos, 99);
    this->medicamentos[99] = '\0';
}

void Cita::setCosto(float costo) {
    this->costo = costo;
}

size_t Cita::obtenerTamano() { return sizeof(Cita); }

// =============================================
// CLASE HISTORIALMEDICO
// =============================================
class HistorialMedico {
private:
    int id;
    int PacienteID;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int DoctorID;
    float costo;
    int siguienteConsultaId;
    bool eliminado;
    time_t fecharegistro;

public:
    HistorialMedico();
    
    // Getters
    int getId() const;
    int getPacienteID() const;
    const char* getFecha() const;
    const char* getHora() const;
    const char* getDiagnostico() const;
    const char* getTratamiento() const;
    int getDoctorID() const;
    float getCosto() const;
    int getSiguienteConsultaId() const;
    bool getEliminado() const;
    
    // Setters
    void setId(int id);
    void setPacienteID(int id);
    void setFecha(const char* fecha);
    void setHora(const char* hora);
    void setDiagnostico(const char* diagnostico);
    void setTratamiento(const char* tratamiento);
    void setMedicamentos(const char* medicamentos);
    void setDoctorID(int id);
    void setCosto(float costo);
    void setSiguienteConsultaId(int id);
    void setEliminado(bool elim);
    void setFecharegistro(time_t tiempo);
    
    bool validarDatos() const;
    static size_t obtenerTamano();
};

HistorialMedico::HistorialMedico() {
    id = 0;
    PacienteID = -1;
    strcpy(fecha, "");
    strcpy(hora, "");
    strcpy(diagnostico, "");
    strcpy(tratamiento, "");
    strcpy(medicamentos, "");
    DoctorID = -1;
    costo = 0;
    siguienteConsultaId = -1;
    eliminado = false;
    fecharegistro = time(0);
}

// Getters
int HistorialMedico::getId() const { return id; }
int HistorialMedico::getPacienteID() const { return PacienteID; }
const char* HistorialMedico::getFecha() const { return fecha; }
const char* HistorialMedico::getHora() const { return hora; }
const char* HistorialMedico::getDiagnostico() const { return diagnostico; }
const char* HistorialMedico::getTratamiento() const { return tratamiento; }
int HistorialMedico::getDoctorID() const { return DoctorID; }
float HistorialMedico::getCosto() const { return costo; }
int HistorialMedico::getSiguienteConsultaId() const { return siguienteConsultaId; }
bool HistorialMedico::getEliminado() const { return eliminado; }

// Setters
void HistorialMedico::setId(int id) { this->id = id; }
void HistorialMedico::setPacienteID(int id) { PacienteID = id; }
void HistorialMedico::setFecha(const char* fecha) { strncpy(this->fecha, fecha, 10); this->fecha[10] = '\0'; }
void HistorialMedico::setHora(const char* hora) { strncpy(this->hora, hora, 5); this->hora[5] = '\0'; }
void HistorialMedico::setDiagnostico(const char* diagnostico) { strncpy(this->diagnostico, diagnostico, 199); this->diagnostico[199] = '\0'; }
void HistorialMedico::setTratamiento(const char* tratamiento) { strncpy(this->tratamiento, tratamiento, 199); this->tratamiento[199] = '\0'; }
void HistorialMedico::setMedicamentos(const char* medicamentos) { strncpy(this->medicamentos, medicamentos, 149); this->medicamentos[149] = '\0'; }
void HistorialMedico::setDoctorID(int id) { DoctorID = id; }
void HistorialMedico::setCosto(float costo) { this->costo = costo; }
void HistorialMedico::setSiguienteConsultaId(int id) { siguienteConsultaId = id; }
void HistorialMedico::setEliminado(bool elim) { eliminado = elim; }
void HistorialMedico::setFecharegistro(time_t tiempo) { fecharegistro = tiempo; }

bool HistorialMedico::validarDatos() const {
    return PacienteID > 0 && DoctorID > 0 && strlen(diagnostico) > 0 && costo >= 0;
}

size_t HistorialMedico::obtenerTamano() { return sizeof(HistorialMedico); }

// =============================================
// CLASE HOSPITAL
// =============================================
class Hospital {
private:
    char nombre[100];
    char direccion[150];
    char telefono[15];
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;
    int totalPacientesRegistrados;
    int totalDoctoresRegistrados;
    int totalCitasAgendadas;
    int totalConsultasRealizadas;

public:
    Hospital();
    Hospital(const char* nombre, const char* direccion, const char* telefono);
    
    // Getters
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const;
    int getSiguienteIdPaciente() const;
    int getSiguienteIdDoctor() const;
    int getSiguienteIdCita() const;
    int getSiguienteIdConsulta() const;
    int getTotalPacientesRegistrados() const;
    int getTotalDoctoresRegistrados() const;
    int getTotalCitasAgendadas() const;
    int getTotalConsultasRealizadas() const;
    
    // Setters
    void setNombre(const char* nombre);
    void setDireccion(const char* direccion);
    void setTelefono(const char* telefono);
    
    // Generadores de IDs
    int generarIdPaciente();
    int generarIdDoctor();
    int generarIdCita();
    int generarIdConsulta();
    
    // Incrementadores
    void incrementarPacientesRegistrados();
    void incrementarDoctoresRegistrados();
    void incrementarCitasAgendadas();
    void incrementarConsultasRealizadas();
    
    bool validarDatos() const;
    void mostrarInformacion() const;
    void mostrarEstadisticas() const;
    static size_t obtenerTamano();
};

Hospital::Hospital() {
    strcpy(nombre, "Hospital General");
    strcpy(direccion, "");
    strcpy(telefono, "");
    siguienteIdPaciente = 1;
    siguienteIdDoctor = 1;
    siguienteIdCita = 1;
    siguienteIdConsulta = 1;
    totalPacientesRegistrados = 0;
    totalDoctoresRegistrados = 0;
    totalCitasAgendadas = 0;
    totalConsultasRealizadas = 0;
}

Hospital::Hospital(const char* nombre, const char* direccion, const char* telefono) {
    strncpy(this->nombre, nombre, 99);
    this->nombre[99] = '\0';
    strncpy(this->direccion, direccion, 149);
    this->direccion[149] = '\0';
    strncpy(this->telefono, telefono, 14);
    this->telefono[14] = '\0';
    siguienteIdPaciente = 1;
    siguienteIdDoctor = 1;
    siguienteIdCita = 1;
    siguienteIdConsulta = 1;
    totalPacientesRegistrados = 0;
    totalDoctoresRegistrados = 0;
    totalCitasAgendadas = 0;
    totalConsultasRealizadas = 0;
}

// Getters
const char* Hospital::getNombre() const { return nombre; }
const char* Hospital::getDireccion() const { return direccion; }
const char* Hospital::getTelefono() const { return telefono; }
int Hospital::getSiguienteIdPaciente() const { return siguienteIdPaciente; }
int Hospital::getSiguienteIdDoctor() const { return siguienteIdDoctor; }
int Hospital::getSiguienteIdCita() const { return siguienteIdCita; }
int Hospital::getSiguienteIdConsulta() const { return siguienteIdConsulta; }
int Hospital::getTotalPacientesRegistrados() const { return totalPacientesRegistrados; }
int Hospital::getTotalDoctoresRegistrados() const { return totalDoctoresRegistrados; }
int Hospital::getTotalCitasAgendadas() const { return totalCitasAgendadas; }
int Hospital::getTotalConsultasRealizadas() const { return totalConsultasRealizadas; }

// Setters
void Hospital::setNombre(const char* nombre) { strncpy(this->nombre, nombre, 99); this->nombre[99] = '\0'; }
void Hospital::setDireccion(const char* direccion) { strncpy(this->direccion, direccion, 149); this->direccion[149] = '\0'; }
void Hospital::setTelefono(const char* telefono) { strncpy(this->telefono, telefono, 14); this->telefono[14] = '\0'; }

// Generadores de IDs
int Hospital::generarIdPaciente() { return siguienteIdPaciente++; }
int Hospital::generarIdDoctor() { return siguienteIdDoctor++; }
int Hospital::generarIdCita() { return siguienteIdCita++; }
int Hospital::generarIdConsulta() { return siguienteIdConsulta++; }

// Incrementadores
void Hospital::incrementarPacientesRegistrados() { totalPacientesRegistrados++; }
void Hospital::incrementarDoctoresRegistrados() { totalDoctoresRegistrados++; }
void Hospital::incrementarCitasAgendadas() { totalCitasAgendadas++; }
void Hospital::incrementarConsultasRealizadas() { totalConsultasRealizadas++; }

bool Hospital::validarDatos() const {
    return strlen(nombre) > 0 && strlen(telefono) > 0;
}

void Hospital::mostrarInformacion() const {
    cout << "\n=== INFORMACIÓN DEL HOSPITAL ===" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Teléfono: " << telefono << endl;
}

void Hospital::mostrarEstadisticas() const {
    cout << "\n=== ESTADÍSTICAS DEL SISTEMA ===" << endl;
    cout << "Pacientes registrados: " << totalPacientesRegistrados << endl;
    cout << "Doctores registrados: " << totalDoctoresRegistrados << endl;
    cout << "Citas agendadas: " << totalCitasAgendadas << endl;
    cout << "Consultas realizadas: " << totalConsultasRealizadas << endl;
}

size_t Hospital::obtenerTamano() { return sizeof(Hospital); }

// =============================================
// CLASE VALIDACIONES
// =============================================
class Validaciones {
public:
    static bool validarFecha(const char* fecha);
    static bool validarHora(const char* hora);
    static bool validarCedula(const char* cedula);
    static bool validarEmail(const char* email);
    static bool validarEdad(int edad);
    static bool validarSexo(char sexo);
    static int compararFechas(const char* fecha1, const char* fecha2);
    static int mi_strcasecmp(const char* s1, const char* s2);
};

bool Validaciones::validarFecha(const char* fecha) {
    int año, mes, dia;
    if(strlen(fecha) != 10) return false;
    if(fecha[4] != '-' || fecha[7] != '-') return false;
    
    for(int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (fecha[i] < '0' || fecha[i] > '9') return false;
    }
    
    año = (fecha[0]-'0')*1000 + (fecha[1]-'0')*100 + (fecha[2]-'0')*10 + (fecha[3]-'0');
    mes = (fecha[5]-'0')*10 + (fecha[6]-'0');
    dia = (fecha[8]-'0')*10 + (fecha[9]-'0');
    
    if (año < 1900 || año > 2100) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30) return false;
    } else if (mes == 2) {
        bool esBisiesto = (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0);
        if (esBisiesto) {
            if (dia > 29) return false;
        } else {
            if (dia > 28) return false;
        }
    }
    return true;
}

bool Validaciones::validarHora(const char* hora) {
    if (strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;
    
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (hora[i] < '0' || hora[i] > '9') return false;
    }
    
    int HH = (hora[0] - '0') * 10 + (hora[1] - '0');
    int MM = (hora[3] - '0') * 10 + (hora[4] - '0');
    
    return (HH >= 0 && HH <= 23) && (MM >= 0 && MM <= 59);
}

bool Validaciones::validarCedula(const char* cedula) {
    if (!cedula || strlen(cedula) == 0 || strlen(cedula) > 20) return false;
    return true;
}

bool Validaciones::validarEmail(const char* email) {
    if(strlen(email) == 0) return false;
    bool tienearroba = false;
    bool tienepunto = false;
    for(int i = 0; email[i] != '\0'; i++) {
        if(email[i] == '@') tienearroba = true;
        else if(email[i] == '.' && tienearroba) tienepunto = true;
    }
    return tienearroba && tienepunto;
}

bool Validaciones::validarEdad(int edad) {
    return (edad >= 0 && edad <= 120);
}

bool Validaciones::validarSexo(char sexo) {
    return (sexo == 'M' || sexo == 'F');
}

int Validaciones::compararFechas(const char* fecha1, const char* fecha2) {
    for (int i = 0; i < 10; i++) {
        if (fecha1[i] < fecha2[i]) return -1;
        if (fecha1[i] > fecha2[i]) return 1;
    }
    return 0;
}

int Validaciones::mi_strcasecmp(const char* s1, const char* s2) {
    while(*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
        if(c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

// =============================================
// CLASE GESTORARCHIVOS
// =============================================
class GestorArchivos {
public:
    static time_t obtenerTimestamp();
    static void mostrarError(const char* mensaje);
    static void mostrarExito(const char* mensaje);
    static void pausar();
    static void limpiarBuffer();
    static bool inicializarHeader(const char* nombreArchivo);
    static ArchivoHeader leerHeader(const char* nombreArchivo);
    static bool actualizarHeader(const char* nombreArchivo, ArchivoHeader header);
    static bool verificarArchivo(const char* nombreArchivo);
    static bool inicializarArchivo(const char* nombreArchivo);
    static bool verificarIntegridadArchivos();
    static long getPosicionPaciente(int indice);
    static long getPosicionDoctor(int indice);
    static long getPosicionCita(int indice);
    static long getPosicionHistorial(int indice);
    static bool compactarArchivoPacientes();
    static bool compactarArchivoDoctores();
    static bool compactarArchivoCitas();
    static bool compactarArchivoHistoriales();
    static bool actualizarReferenciasPacientes(int mapaIDs[]);
    static bool actualizarReferenciasEnDoctores(int mapaIDs[]);
    static bool actualizarReferenciasEnCitas(int mapaIDs[]);
    static bool actualizarReferenciasEnHistoriales(int mapaIDs[]);
    static bool actualizarReferenciasDoctores(int mapaIDs[]);
    static bool actualizarReferenciasDoctoresEnCitas(int mapaIDs[]);
    static bool actualizarReferenciasDoctoresEnHistoriales(int mapaIDs[]);
    static void reiniciarArchivoPacientes();
    static void reiniciarArchivoDoctores();
    static void reiniciarArchivoCitas();
    static void hacerRespaldo();
    static void restaurarRespaldo();
    static void mostrarEstadisticas();
    static bool verificarIntegridadReferencial();
    static bool repararIntegridadReferencial();
   private:
    static bool compactarArchivo(const char* nombreArchivo, size_t tamanoRegistro, bool (*actualizarReferencias)(int[]));

    
    
};

time_t GestorArchivos::obtenerTimestamp() {
    return time(0);
}

void GestorArchivos::mostrarError(const char* mensaje) {
    cout << "Error: " << mensaje << endl;
}

void GestorArchivos::mostrarExito(const char* mensaje) {
    cout << "Exito: " << mensaje << endl;
}

void GestorArchivos::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void GestorArchivos::limpiarBuffer() {
    while (cin.get() != '\n');
}

bool GestorArchivos::inicializarHeader(const char* nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary | ios::out);
    if (!archivo.is_open()) return false;
    
    ArchivoHeader header = {0, 1, 0, 1};
    archivo.write(reinterpret_cast<const char*>(&header), sizeof(ArchivoHeader));
    archivo.close();
    return archivo.good();
}

ArchivoHeader GestorArchivos::leerHeader(const char* nombreArchivo) {
    ArchivoHeader header = {0, 0, 0, 0};
    ifstream archivo(nombreArchivo, ios::binary | ios::in);
    if (!archivo.is_open()) return header;
    
    archivo.seekg(0, ios::end);
    streampos fileSize = archivo.tellg();
    archivo.seekg(0, ios::beg);
    
    if (fileSize < static_cast<streampos>(sizeof(ArchivoHeader))) {
        archivo.close();
        return header;
    }
    
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    archivo.close();
    return header;
}

bool GestorArchivos::actualizarHeader(const char* nombreArchivo, ArchivoHeader header) {
    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    
    archivo.seekp(0, ios::beg);
    archivo.write(reinterpret_cast<const char*>(&header), sizeof(ArchivoHeader));
    bool exito = archivo.good();
    archivo.close();
    return exito;
}

bool GestorArchivos::verificarArchivo(const char* nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) return false;
    
    archivo.seekg(0, ios::end);
    long tamaño = archivo.tellg();
    archivo.close();
    return (tamaño >= (long)sizeof(ArchivoHeader));
}

bool GestorArchivos::inicializarArchivo(const char* nombreArchivo) {
    return inicializarHeader(nombreArchivo);
}

bool GestorArchivos::verificarIntegridadArchivos() {
    cout << "\n=== VERIFICANDO INTEGRIDAD DE ARCHIVOS ===" << endl;
    bool todosOK = true;
    const char* archivos[] = {FILE_HOSPITAL, FILE_PACIENTES, FILE_DOCTORES, FILE_CITAS, FILE_HISTORIALES};
    const char* nombres[] = {"Hospital", "Pacientes", "Doctores", "Citas", "Historiales"};
    
    for (int i = 0; i < 5; i++) {
        if (verificarArchivo(archivos[i])) {
            cout << "✅ " << nombres[i] << ": OK" << endl;
        } else {
            cout << "❌ " << nombres[i] << ": Error o archivo corrupto" << endl;
            todosOK = false;
        }
    }
    
    if (todosOK) {
        cout << "\n✅ Todos los archivos están en buen estado." << endl;
    } else {
        cout << "\n⚠️  Se encontraron problemas en algunos archivos." << endl;
    }
    return todosOK;
}
bool GestorArchivos::verificarIntegridadReferencial() {
    cout << "Verificando integridad referencial..." << endl;
    bool todoCorrecto = true;
    
    // Verificar referencias entre citas y pacientes/doctores
    ArchivoHeader headerCitas = leerHeader(FILE_CITAS);
    ifstream archivoCitas(FILE_CITAS, ios::binary);
    
    if (archivoCitas.is_open()) {
        archivoCitas.seekg(sizeof(ArchivoHeader));
        Cita cita;
        
        for (int i = 0; i < headerCitas.cantidadRegistros; i++) {
            archivoCitas.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
            if (archivoCitas.fail()) break;
            
            if (!cita.getEliminado()) {
                // Verificar que el paciente existe - usando búsqueda directa
                bool pacienteExiste = false;
                ArchivoHeader headerPacientes = leerHeader(FILE_PACIENTES);
                ifstream archivoPacientes(FILE_PACIENTES, ios::binary);
                
                if (archivoPacientes.is_open()) {
                    archivoPacientes.seekg(sizeof(ArchivoHeader));
                    Paciente paciente;
                    
                    for (int j = 0; j < headerPacientes.cantidadRegistros; j++) {
                        archivoPacientes.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
                        if (archivoPacientes.fail()) break;
                        
                        if (!paciente.getEliminado() && paciente.getId() == cita.getPacienteID()) {
                            pacienteExiste = true;
                            break;
                        }
                    }
                    archivoPacientes.close();
                }
                
                if (!pacienteExiste) {
                    cout << "❌ Cita " << cita.getId() << " referencia a paciente inexistente: " << cita.getPacienteID() << endl;
                    todoCorrecto = false;
                }
                
                // Verificar que el doctor existe - usando búsqueda directa
                bool doctorExiste = false;
                ArchivoHeader headerDoctores = leerHeader(FILE_DOCTORES);
                ifstream archivoDoctores(FILE_DOCTORES, ios::binary);
                
                if (archivoDoctores.is_open()) {
                    archivoDoctores.seekg(sizeof(ArchivoHeader));
                    Doctor doctor;
                    
                    for (int j = 0; j < headerDoctores.cantidadRegistros; j++) {
                        archivoDoctores.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
                        if (archivoDoctores.fail()) break;
                        
                        if (!doctor.getEliminado() && doctor.getId() == cita.getDoctorID()) {
                            doctorExiste = true;
                            break;
                        }
                    }
                    archivoDoctores.close();
                }
                
                if (!doctorExiste) {
                    cout << "❌ Cita " << cita.getId() << " referencia a doctor inexistente: " << cita.getDoctorID() << endl;
                    todoCorrecto = false;
                }
            }
        }
        archivoCitas.close();
    }
    
    if (todoCorrecto) {
        cout << "✅ Integridad referencial verificada correctamente" << endl;
    } else {
        cout << "⚠️  Se encontraron problemas de integridad referencial" << endl;
    }
    
    return todoCorrecto;
}

long GestorArchivos::getPosicionPaciente(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(Paciente));
}

long GestorArchivos::getPosicionDoctor(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(Doctor));
}

long GestorArchivos::getPosicionCita(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(Cita));
}

long GestorArchivos::getPosicionHistorial(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(HistorialMedico));
}
bool GestorArchivos::compactarArchivo(const char* nombreArchivo, size_t tamanoRegistro, bool (*actualizarReferencias)(int[])) {
    // Crear archivo temporal
    char tempFile[100];
    snprintf(tempFile, sizeof(tempFile), "temp_%s", nombreArchivo);
    
    ofstream archivoTemp(tempFile, ios::binary);
    if (!archivoTemp.is_open()) {
        cout << "Error: No se pudo crear archivo temporal" << endl;
        return false;
    }

    // Leer header original
    ArchivoHeader headerOriginal = leerHeader(nombreArchivo);
    ifstream archivoOriginal(nombreArchivo, ios::binary);
    if (!archivoOriginal.is_open()) {
        archivoTemp.close();
        cout << "Error: No se pudo abrir archivo original" << endl;
        return false;
    }

    // Preparar nuevo header
    ArchivoHeader nuevoHeader;
    nuevoHeader.cantidadRegistros = 0;
    nuevoHeader.siguienteId = headerOriginal.siguienteId;
    nuevoHeader.registrosActivos = 0;
    nuevoHeader.version = headerOriginal.version;

    // Escribir nuevo header
    archivoTemp.write((char*)&nuevoHeader, sizeof(ArchivoHeader));

    // Saltar header en archivo original
    archivoOriginal.seekg(sizeof(ArchivoHeader));

    // Mapa para re-indexar IDs
    int mapaIDs[1000] = {0}; // Asumimos máximo 1000 registros
    int nuevoID = 1;

    // Buffer para leer registros
    char* buffer = new char[tamanoRegistro];

    // Leer registro por registro
    for (int i = 0; i < headerOriginal.cantidadRegistros; i++) {
        archivoOriginal.read(buffer, tamanoRegistro);
        if (archivoOriginal.fail()) {
            break;
        }

        // Verificar si el registro está eliminado
        // Asumimos que el campo "eliminado" está al final del registro
        bool eliminado = *((bool*)(buffer + tamanoRegistro - sizeof(bool)));
        
        if (!eliminado) {
            // Actualizar ID (asumimos que el ID está al inicio del registro)
            int idViejo = *((int*)buffer);
            *((int*)buffer) = nuevoID;
            mapaIDs[idViejo] = nuevoID;

            // Escribir registro compactado
            archivoTemp.write(buffer, tamanoRegistro);
            
            nuevoHeader.cantidadRegistros++;
            nuevoHeader.registrosActivos++;
            nuevoID++;
        }
    }

    // Liberar buffer
    delete[] buffer;
    archivoOriginal.close();
    archivoTemp.close();

    // Actualizar header del archivo temporal
    fstream archivoTempUpdate(tempFile, ios::binary | ios::in | ios::out);
    if (archivoTempUpdate.is_open()) {
        archivoTempUpdate.seekp(0);
        archivoTempUpdate.write((char*)&nuevoHeader, sizeof(ArchivoHeader));
        archivoTempUpdate.close();
    }

    // Eliminar original y renombrar
    if (remove(nombreArchivo) != 0) {
        cout << "Error: No se pudo eliminar archivo original" << endl;
        remove(tempFile);
        return false;
    }

    if (rename(tempFile, nombreArchivo) != 0) {
        cout << "Error: No se pudo renombrar archivo temporal" << endl;
        return false;
    }

    // Actualizar referencias si es necesario
    if (actualizarReferencias != NULL) {
        if (!actualizarReferencias(mapaIDs)) {
            cout << "Error: No se pudieron actualizar referencias" << endl;
            return false;
        }
    }

    cout << "Archivo compactado exitosamente" << endl;
    cout << "Registros antes: " << headerOriginal.cantidadRegistros << endl;
    cout << "Registros despues: " << nuevoHeader.cantidadRegistros << endl;
    cout << "Espacio liberado: " 
         << (headerOriginal.cantidadRegistros - nuevoHeader.cantidadRegistros) * tamanoRegistro 
         << " bytes" << endl;

    return true;
}

bool GestorArchivos::compactarArchivoPacientes() {
    cout << "\n=== COMPACTANDO ARCHIVO DE PACIENTES ===" << endl;
    return compactarArchivo(FILE_PACIENTES, sizeof(Paciente), actualizarReferenciasPacientes);
}

bool GestorArchivos::compactarArchivoDoctores() {
    cout << "\n=== COMPACTANDO ARCHIVO DE DOCTORES ===" << endl;
    return compactarArchivo(FILE_DOCTORES, sizeof(Doctor), actualizarReferenciasDoctores);
}

bool GestorArchivos::compactarArchivoCitas() {
    cout << "\n=== COMPACTANDO ARCHIVO DE CITAS ===" << endl;
    return compactarArchivo(FILE_CITAS, sizeof(Cita), NULL);
}

bool GestorArchivos::compactarArchivoHistoriales() {
    cout << "\n=== COMPACTANDO ARCHIVO DE HISTORIALES ===" << endl;
    return compactarArchivo(FILE_HISTORIALES, sizeof(HistorialMedico), NULL);
}
bool GestorArchivos::actualizarReferenciasPacientes(int mapaIDs[]) {
    bool exitoTotal = true;
    
    cout << "Actualizando referencias de pacientes..." << endl;
    
    // 1. Actualizar en doctores
    exitoTotal = exitoTotal && actualizarReferenciasEnDoctores(mapaIDs);
    
    // 2. Actualizar en citas
    exitoTotal = exitoTotal && actualizarReferenciasEnCitas(mapaIDs);
    
    // 3. Actualizar en historiales
    exitoTotal = exitoTotal && actualizarReferenciasEnHistoriales(mapaIDs);
    
    return exitoTotal;
}

bool GestorArchivos::actualizarReferenciasEnDoctores(int mapaIDs[]) {
    cout << " - Actualizando doctores..." << endl;
    
    ArchivoHeader header = leerHeader(FILE_DOCTORES);
    fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) {
        cout << "   Error: No se pudo abrir archivo de doctores" << endl;
        return false;
    }

    archivo.seekg(sizeof(ArchivoHeader));
    Doctor doctor;
    int actualizados = 0;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read((char*)&doctor, sizeof(Doctor));
        if (archivo.fail()) {
            break;
        }

        // Actualizar IDs de pacientes en el array del doctor
        bool modificado = doctor.actualizarPacientesIDs(mapaIDs);

        if (modificado) {
            archivo.seekp(posicion);
            archivo.write((char*)&doctor, sizeof(Doctor));
            archivo.seekg(posicion + sizeof(Doctor));
            actualizados++;
        }
    }

    archivo.close();
    cout << "   Doctores actualizados: " << actualizados << endl;
    return true;
}

bool GestorArchivos::actualizarReferenciasEnCitas(int mapaIDs[]) {
    cout << " - Actualizando citas..." << endl;
    
    ArchivoHeader header = leerHeader(FILE_CITAS);
    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) {
        cout << "   Error: No se pudo abrir archivo de citas" << endl;
        return false;
    }

    archivo.seekg(sizeof(ArchivoHeader));
    Cita cita;
    int actualizados = 0;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read((char*)&cita, sizeof(Cita));
        if (archivo.fail()) {
            break;
        }

        // Actualizar ID del paciente en la cita
        if (mapaIDs[cita.getPacienteID()] != 0) {
            cita.setPacienteID(mapaIDs[cita.getPacienteID()]);
            
            archivo.seekp(posicion);
            archivo.write((char*)&cita, sizeof(Cita));
            archivo.seekg(posicion + sizeof(Cita));
            actualizados++;
        }
    }

    archivo.close();
    cout << "   Citas actualizadas: " << actualizados << endl;
    return true;
}

bool GestorArchivos::actualizarReferenciasEnHistoriales(int mapaIDs[]) {
    cout << " - Actualizando historiales..." << endl;
    
    ArchivoHeader header = leerHeader(FILE_HISTORIALES);
    fstream archivo(FILE_HISTORIALES, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) {
        cout << "   Error: No se pudo abrir archivo de historiales" << endl;
        return false;
    }

    archivo.seekg(sizeof(ArchivoHeader));
    HistorialMedico historial;
    int actualizados = 0;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read((char*)&historial, sizeof(HistorialMedico));
        if (archivo.fail()) {
            break;
        }

        // Actualizar ID del paciente en el historial
        if (mapaIDs[historial.getPacienteID()] != 0) {
            historial.setPacienteID(mapaIDs[historial.getPacienteID()]);
            
            archivo.seekp(posicion);
            archivo.write((char*)&historial, sizeof(HistorialMedico));
            archivo.seekg(posicion + sizeof(HistorialMedico));
            actualizados++;
        }
    }

    archivo.close();
    cout << "   Historiales actualizados: " << actualizados << endl;
    return true;
}

bool GestorArchivos::actualizarReferenciasDoctores(int mapaIDs[]) {
    bool exitoTotal = true;
    
    cout << "Actualizando referencias de doctores..." << endl;
    
    // 1. Actualizar en citas
    exitoTotal = exitoTotal && actualizarReferenciasDoctoresEnCitas(mapaIDs);
    
    // 2. Actualizar en historiales
    exitoTotal = exitoTotal && actualizarReferenciasDoctoresEnHistoriales(mapaIDs);
    
    return exitoTotal;
}

bool GestorArchivos::actualizarReferenciasDoctoresEnCitas(int mapaIDs[]) {
    cout << " - Actualizando citas (doctores)..." << endl;
    
    ArchivoHeader header = leerHeader(FILE_CITAS);
    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) {
        cout << "   Error: No se pudo abrir archivo de citas" << endl;
        return false;
    }

    archivo.seekg(sizeof(ArchivoHeader));
    Cita cita;
    int actualizados = 0;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read((char*)&cita, sizeof(Cita));
        if (archivo.fail()) {
            break;
        }

        // Actualizar ID del doctor en la cita
        if (mapaIDs[cita.getDoctorID()] != 0) {
            cita.setDoctorID(mapaIDs[cita.getDoctorID()]);
            
            archivo.seekp(posicion);
            archivo.write((char*)&cita, sizeof(Cita));
            archivo.seekg(posicion + sizeof(Cita));
            actualizados++;
        }
    }

    archivo.close();
    cout << "   Citas actualizadas: " << actualizados << endl;
    return true;
}

bool GestorArchivos::actualizarReferenciasDoctoresEnHistoriales(int mapaIDs[]) {
    cout << " - Actualizando historiales (doctores)..." << endl;
    
    ArchivoHeader header = leerHeader(FILE_HISTORIALES);
    fstream archivo(FILE_HISTORIALES, ios::binary | ios::in | ios::out);
    
    if (!archivo.is_open()) {
        cout << "   Error: No se pudo abrir archivo de historiales" << endl;
        return false;
    }

    archivo.seekg(sizeof(ArchivoHeader));
    HistorialMedico historial;
    int actualizados = 0;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        long posicion = archivo.tellg();
        archivo.read((char*)&historial, sizeof(HistorialMedico));
        if (archivo.fail()) {
            break;
        }

        // Actualizar ID del doctor en el historial
        if (mapaIDs[historial.getDoctorID()] != 0) {
            historial.setDoctorID(mapaIDs[historial.getDoctorID()]);
            
            archivo.seekp(posicion);
            archivo.write((char*)&historial, sizeof(HistorialMedico));
            archivo.seekg(posicion + sizeof(HistorialMedico));
            actualizados++;
        }
    }

    archivo.close();
    cout << "   Historiales actualizados: " << actualizados << endl;
    return true;
}
void GestorArchivos::hacerRespaldo() {
    cout << "\n=== HACIENDO RESPALDO ===" << endl;
    
    const char* archivos[] = {"pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin", "hospital.bin"};
    
    for(int i = 0; i < 5; i++) {
        // Crear nombre de respaldo
        char nombreRespaldo[50];
        sprintf(nombreRespaldo, "respaldo_%s", archivos[i]);
        
        // Abrir archivo original
        ifstream original(archivos[i], ios::binary);
        if(!original.is_open()) {
            cout << "Error: No se pudo abrir " << archivos[i] << endl;
            continue;
        }
        
        // Crear archivo de respaldo
        ofstream respaldo(nombreRespaldo, ios::binary);
        if(!respaldo.is_open()) {
            cout << "Error: No se pudo crear respaldo de " << archivos[i] << endl;
            original.close();
            continue;
        }
        
        // Copiar todo el contenido
        char buffer[1024];
        while(original.read(buffer, 1024)) {
            respaldo.write(buffer, original.gcount());
        }
        
        original.close();
        respaldo.close();
        cout << "✅ " << archivos[i] << " respaldado" << endl;
    }
    
    cout << "Respaldo completado" << endl;
}

void GestorArchivos::restaurarRespaldo() {
    cout << "\n=== RESTAURANDO RESPALDO ===" << endl;
    
    const char* archivos[] = {"pacientes.bin", "doctores.bin", "citas.bin", "historiales.bin", "hospital.bin"};
    
    for(int i = 0; i < 5; i++) {
        // Nombre del respaldo
        char nombreRespaldo[50];
        sprintf(nombreRespaldo, "respaldo_%s", archivos[i]);
        
        // Verificar si existe el respaldo
        ifstream verificar(nombreRespaldo, ios::binary);
        if(!verificar.is_open()) {
            cout << "⚠️  No existe respaldo de " << archivos[i] << endl;
            continue;
        }
        verificar.close();
        
        // Abrir respaldo
        ifstream respaldo(nombreRespaldo, ios::binary);
        if(!respaldo.is_open()) {
            cout << "Error: No se pudo abrir respaldo de " << archivos[i] << endl;
            continue;
        }
        
        // Crear archivo destino
        ofstream destino(archivos[i], ios::binary | ios::trunc);
        if(!destino.is_open()) {
            cout << "Error: No se pudo crear " << archivos[i] << endl;
            respaldo.close();
            continue;
        }
        
        // Copiar todo el contenido
        char buffer[1024];
        while(respaldo.read(buffer, 1024)) {
            destino.write(buffer, respaldo.gcount());
        }
        
        respaldo.close();
        destino.close();
        cout << "✅ " << archivos[i] << " restaurado" << endl;
    }
    
    cout << "Restauracion completada" << endl;
}

void GestorArchivos::mostrarEstadisticas() {
    cout << "\n=== ESTADISTICAS DEL SISTEMA ===" << endl;
    
    // Leer headers de todos los archivos
    ArchivoHeader hPacientes = leerHeader(FILE_PACIENTES);
    ArchivoHeader hDoctores = leerHeader(FILE_DOCTORES);
    ArchivoHeader hCitas = leerHeader(FILE_CITAS);
    ArchivoHeader hHistoriales = leerHeader(FILE_HISTORIALES);
    
    // Mostrar estadísticas
    cout << "PACIENTES:" << endl;
    cout << "  - Registros totales: " << hPacientes.cantidadRegistros << endl;
    cout << "  - Registros activos: " << hPacientes.registrosActivos << endl;
    cout << "  - Proximo ID: " << hPacientes.siguienteId << endl;
    
    cout << "DOCTORES:" << endl;
    cout << "  - Registros totales: " << hDoctores.cantidadRegistros << endl;
    cout << "  - Registros activos: " << hDoctores.registrosActivos << endl;
    cout << "  - Proximo ID: " << hDoctores.siguienteId << endl;
    
    cout << "CITAS:" << endl;
    cout << "  - Registros totales: " << hCitas.cantidadRegistros << endl;
    cout << "  - Registros activos: " << hCitas.registrosActivos << endl;
    cout << "  - Proximo ID: " << hCitas.siguienteId << endl;
    
    cout << "HISTORIALES:" << endl;
    cout << "  - Registros totales: " << hHistoriales.cantidadRegistros << endl;
    cout << "  - Registros activos: " << hHistoriales.registrosActivos << endl;
    cout << "  - Proximo ID: " << hHistoriales.siguienteId << endl;
    
    // Mostrar información del hospital
    Hospital hospital;
    ifstream archivoHospital(FILE_HOSPITAL, ios::binary);
    if(archivoHospital.is_open()) {
        archivoHospital.read((char*)&hospital, sizeof(Hospital));
        archivoHospital.close();
        
        cout << "\n=== ESTADISTICAS GLOBALES ===" << endl;
        cout << "Total pacientes registrados: " << hospital.getTotalPacientesRegistrados() << endl;
        cout << "Total doctores registrados: " << hospital.getTotalDoctoresRegistrados() << endl;
        cout << "Total citas agendadas: " << hospital.getTotalCitasAgendadas() << endl;
        cout << "Total consultas realizadas: " << hospital.getTotalConsultasRealizadas() << endl;
    }
}

void GestorArchivos::reiniciarArchivoPacientes() {
    cout << "\n=== REINICIANDO ARCHIVO DE PACIENTES ===" << endl;
    
    ofstream archivo(FILE_PACIENTES, ios::binary | ios::trunc);
    if(!archivo.is_open()) {
        cout << "Error: No se pudo crear archivo" << endl;
        return;
    }
    
    ArchivoHeader header;
    header.cantidadRegistros = 0;
    header.siguienteId = 1;
    header.registrosActivos = 0;
    header.version = 1;
    
    archivo.write((char*)&header, sizeof(ArchivoHeader));
    archivo.close();
    
    cout << "Archivo de pacientes reiniciado" << endl;
    cout << "Todos los pacientes han sido eliminados" << endl;
}

void GestorArchivos::reiniciarArchivoDoctores() {
    cout << "\n=== REINICIANDO ARCHIVO DE DOCTORES ===" << endl;
    
    ofstream archivo(FILE_DOCTORES, ios::binary | ios::trunc);
    if(!archivo.is_open()) {
        cout << "Error: No se pudo crear archivo" << endl;
        return;
    }
    
    ArchivoHeader header;
    header.cantidadRegistros = 0;
    header.siguienteId = 1;
    header.registrosActivos = 0;
    header.version = 1;
    
    archivo.write((char*)&header, sizeof(ArchivoHeader));
    archivo.close();
    
    cout << "Archivo de doctores reiniciado" << endl;
    cout << "Todos los doctores han sido eliminados" << endl;
}

void GestorArchivos::reiniciarArchivoCitas() {
    cout << "\n=== REINICIANDO ARCHIVO DE CITAS ===" << endl;
    
    ofstream archivo(FILE_CITAS, ios::binary | ios::trunc);
    if(!archivo.is_open()) {
        cout << "Error: No se pudo crear archivo" << endl;
        return;
    }
    
    ArchivoHeader header;
    header.cantidadRegistros = 0;
    header.siguienteId = 1;
    header.registrosActivos = 0;
    header.version = 1;
    
    archivo.write((char*)&header, sizeof(ArchivoHeader));
    archivo.close();
    
    cout << "Archivo de citas reiniciado" << endl;
    cout << "Todas las citas han sido eliminadas" << endl;
}

// =============================================
// OPERACIONES PACIENTES
// =============================================
class OperacionesPacientes {
public:
    static bool agregarPaciente(Paciente& nuevoPaciente);
    static Paciente buscarPacientePorID(int id);
    static Paciente buscarPacientePorCedula(const char* cedula);
    static bool existePacienteConCedula(const char* cedula);
    static int buscarIndiceDeID(int id);
    static bool actualizarPaciente(Paciente& pacienteModificado);
    static bool eliminarPaciente(int id);
    static void listarTodosPacientes();
};

bool OperacionesPacientes::agregarPaciente(Paciente& nuevoPaciente) {
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES);
    nuevoPaciente.setId(header.siguienteId);
    nuevoPaciente.setFechaCreacion(GestorArchivos::obtenerTimestamp());
    nuevoPaciente.setFechaModificacion(GestorArchivos::obtenerTimestamp());
    nuevoPaciente.setEliminado(false);
    
    ofstream archivo(FILE_PACIENTES, ios::binary | ios::app);
    if (!archivo.is_open()) return false;
    
    archivo.write(reinterpret_cast<const char*>(&nuevoPaciente), sizeof(Paciente));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    header.cantidadRegistros++;
    header.siguienteId++;
    header.registrosActivos++;
    bool exitoHeader = GestorArchivos::actualizarHeader(FILE_PACIENTES, header);
    archivo.close();
    return exitoHeader;
}

Paciente OperacionesPacientes::buscarPacientePorID(int id) {
    Paciente paciente;
    if (id < 1) return paciente;
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES);
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) return paciente;
    
    archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Paciente pacienteActual;
        archivo.read(reinterpret_cast<char*>(&pacienteActual), sizeof(Paciente));
        if (archivo.fail()) break;
        
        if (pacienteActual.getId() == id && !pacienteActual.getEliminado()) {
            paciente = pacienteActual;
            break;
        }
    }
    archivo.close();
    return paciente;
}

Paciente OperacionesPacientes::buscarPacientePorCedula(const char* cedula) {
    Paciente paciente;
    if (strlen(cedula) == 0) return paciente;
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES);
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) return paciente;
    
    archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Paciente pacienteActual;
        archivo.read(reinterpret_cast<char*>(&pacienteActual), sizeof(Paciente));
        if (archivo.fail()) break;
        
        if (Validaciones::mi_strcasecmp(pacienteActual.getCedula(), cedula) == 0 && !pacienteActual.getEliminado()) {
            paciente = pacienteActual;
            break;
        }
    }
    archivo.close();
    return paciente;
}

bool OperacionesPacientes::existePacienteConCedula(const char* cedula) {
    Paciente p = buscarPacientePorCedula(cedula);
    return p.getId() != 0;
}

int OperacionesPacientes::buscarIndiceDeID(int id) {
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) return -1;
    
    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    Paciente temp;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(Paciente));
        if (temp.getId() == id && !temp.getEliminado()) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}

bool OperacionesPacientes::actualizarPaciente(Paciente& pacienteModificado) {
    int indice = buscarIndiceDeID(pacienteModificado.getId());
    if (indice == -1) return false;
    
    fstream archivo(FILE_PACIENTES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    
    long posicion = GestorArchivos::getPosicionPaciente(indice);
    archivo.seekp(posicion);
    pacienteModificado.setFechaModificacion(GestorArchivos::obtenerTimestamp());
    archivo.write(reinterpret_cast<const char*>(&pacienteModificado), sizeof(Paciente));
    archivo.close();
    return true;
}

bool OperacionesPacientes::eliminarPaciente(int id) {
    int indice = buscarIndiceDeID(id);
    if (indice == -1) {
        GestorArchivos::mostrarError("Paciente no encontrado");
        return false;
    }
    
    fstream archivo(FILE_PACIENTES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) {
        GestorArchivos::mostrarError("No se pudo abrir el archivo de pacientes");
        return false;
    }
    
    long posicion = GestorArchivos::getPosicionPaciente(indice);
    archivo.seekg(posicion);
    Paciente paciente;
    archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
    if (archivo.fail()) {
        archivo.close();
        GestorArchivos::mostrarError("Error al leer el registro del paciente");
        return false;
    }
    
    if (paciente.getEliminado()) {
        archivo.close();
        GestorArchivos::mostrarError("El paciente ya está eliminado");
        return false;
    }
    
    paciente.setEliminado(true);
    paciente.setFechaModificacion(time(0));
    archivo.seekp(posicion);
    archivo.write(reinterpret_cast<const char*>(&paciente), sizeof(Paciente));
    
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES);
    header.registrosActivos--;
    if (!GestorArchivos::actualizarHeader(FILE_PACIENTES, header)) {
        archivo.close();
        return false;
    }
    
    archivo.close();
    return true;
}

void OperacionesPacientes::listarTodosPacientes() {
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES);
    ifstream archivo(FILE_PACIENTES, ios::binary);
    if (!archivo.is_open()) {
        GestorArchivos::mostrarError("No se pudo abrir archivo de pacientes");
        return;
    }
    
    archivo.seekg(sizeof(ArchivoHeader));
    int pacientesActivos = 0;
    Paciente paciente;
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    LISTA DE PACIENTES                      ║" << endl;
    cout << "╠═════╦═════════════════════╦══════════════╦══════╦══════════╣" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO     ║ CÉDULA       ║ EDAD ║ CONSULTAS║" << endl;
    cout << "╠═════╬═════════════════════╬══════════════╬══════╬══════════╣" << endl;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
        if (archivo.fail()) break;
        
        if (!paciente.getEliminado()) {
            pacientesActivos++;
            string nombreCompleto = string(paciente.getNombre()) + " " + paciente.getApellido();
            if (nombreCompleto.length() > 19) {
                nombreCompleto = nombreCompleto.substr(0, 16) + "...";
            }
            
            cout << "║ " << setw(3) << left << paciente.getId() << " ";
            cout << "║ " << setw(19) << left << nombreCompleto << " ";
            cout << "║ " << setw(12) << left << paciente.getCedula() << " ";
            cout << "║ " << setw(4) << left << paciente.getEdad() << " ";
            cout << "║ " << setw(8) << left << paciente.getCantidadConsultas() << "║" << endl;
        }
    }

    if (pacientesActivos == 0) {
        cout << "║              NO HAY PACIENTES REGISTRADOS               ║" << endl;
    }

    cout << "╚═════╩═════════════════════╩══════════════╩══════╩══════════╝" << endl;
    cout << "Total de pacientes activos: " << pacientesActivos << endl;
    archivo.close();
}
bool Doctor::actualizarPacientesIDs(int mapaIDs[]) {
    bool modificado = false;
    
    // Si tu clase Doctor tiene un array de pacientesIDs
    for (int i = 0; i < cantidadPacientes; i++) {
        int idViejo = pacientesIDs[i];
        if (mapaIDs[idViejo] != 0) {
            pacientesIDs[i] = mapaIDs[idViejo];
            modificado = true;
        }
    }
    
    return modificado;
}
// =============================================
// OPERACIONES DOCTORES
// =============================================
class OperacionesDoctores {
public:
    static bool agregarDoctor(Doctor& nuevoDoctor);
    static Doctor buscarDoctorPorID(int id);
    static int buscarIndiceDoctorPorID(int id);
    static bool actualizarDoctor(Doctor& doctorModificado);
    static bool eliminarDoctor(int id);
    static void listarTodosDoctores();
    static int buscarDoctoresPorEspecialidad(const char* especialidad, Doctor resultados[], int maxResultados);
    static int obtenerDoctoresDisponibles(Doctor resultados[], int maxResultados);
    static int contarDoctoresActivos();
    static bool existeDoctor(int id);
    static int obtenerTodosDoctores(Doctor resultados[], int maxResultados);
    static int buscarDoctoresPorNombre(const char* nombre, Doctor resultados[], int maxResultados);
    static void mostrarDoctoresArray(Doctor doctores[], int cantidad);
};
const char* Doctor::getTelefono() const {
    return telefono;
}

void Doctor::setTelefono(const char* telefono) {
    strncpy(this->telefono, telefono, 14);
    this->telefono[14] = '\0';
}
bool OperacionesDoctores::agregarDoctor(Doctor& nuevoDoctor) {
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    nuevoDoctor.setId(header.siguienteId);
    nuevoDoctor.setFechaCreacion(GestorArchivos::obtenerTimestamp());
    nuevoDoctor.setFechaModificacion(GestorArchivos::obtenerTimestamp());
    nuevoDoctor.setEliminado(false);
    
    ofstream archivo(FILE_DOCTORES, ios::binary | ios::app);
    if (!archivo.is_open()) return false;
    
    archivo.write(reinterpret_cast<const char*>(&nuevoDoctor), sizeof(Doctor));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    header.cantidadRegistros++;
    header.siguienteId++;
    header.registrosActivos++;
    bool exitoHeader = GestorArchivos::actualizarHeader(FILE_DOCTORES, header);
    archivo.close();
    return exitoHeader;
}

Doctor OperacionesDoctores::buscarDoctorPorID(int id) {
    Doctor doctor;
    if (id < 1) return doctor;
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    ifstream archivo(FILE_DOCTORES, ios::binary);
    if (!archivo.is_open()) return doctor;
    
    archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Doctor doctorActual;
        archivo.read(reinterpret_cast<char*>(&doctorActual), sizeof(Doctor));
        if (archivo.fail()) break;
        
        if (doctorActual.getId() == id && !doctorActual.getEliminado()) {
            doctor = doctorActual;
            break;
        }
    }
    archivo.close();
    return doctor;
}

int OperacionesDoctores::buscarIndiceDoctorPorID(int id) {
    ifstream archivo(FILE_DOCTORES, ios::binary);
    if (!archivo.is_open()) return -1;
    
    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    Doctor temp;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(Doctor));
        if (temp.getId() == id && !temp.getEliminado()) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}

bool OperacionesDoctores::actualizarDoctor(Doctor& doctorModificado) {
    int indice = buscarIndiceDoctorPorID(doctorModificado.getId());
    if (indice == -1) return false;
    
    fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    
    long posicion = GestorArchivos::getPosicionDoctor(indice);
    archivo.seekp(posicion);
    doctorModificado.setFechaModificacion(GestorArchivos::obtenerTimestamp());
    archivo.write(reinterpret_cast<const char*>(&doctorModificado), sizeof(Doctor));
    bool exito = !archivo.fail();
    archivo.close();
    return exito;
}

bool OperacionesDoctores::eliminarDoctor(int id) {
    int indice = buscarIndiceDoctorPorID(id);
    if (indice == -1) return false;
    
    fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    
    long posicion = GestorArchivos::getPosicionDoctor(indice);
    archivo.seekg(posicion);
    Doctor doctor;
    archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    if (doctor.getEliminado()) {
        archivo.close();
        return false;
    }
    
    doctor.setEliminado(true);
    doctor.setFechaModificacion(time(0));
    doctor.setDisponible(false);
    
    archivo.seekp(posicion);
    archivo.write(reinterpret_cast<const char*>(&doctor), sizeof(Doctor));
    
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    header.registrosActivos--;
    if (!GestorArchivos::actualizarHeader(FILE_DOCTORES, header)) {
        archivo.close();
        return false;
    }
    
    archivo.close();
    return true;
}
int OperacionesDoctores::buscarDoctoresPorEspecialidad(const char* especialidad, Doctor resultados[], int maxResultados) {
    int encontrados = 0;
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    ifstream archivo(FILE_DOCTORES, ios::binary);
    
    if (!archivo.is_open()) return 0;
    
    archivo.seekg(sizeof(ArchivoHeader));
    Doctor doctor;
    
    for (int i = 0; i < header.cantidadRegistros && encontrados < maxResultados; i++) {
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        if (archivo.fail()) break;
        
        if (!doctor.getEliminado() && strcmp(doctor.getEspecialidad(), especialidad) == 0) {
            resultados[encontrados] = doctor;
            encontrados++;
        }
    }
    
    archivo.close();
    return encontrados;
}
// Método para obtener doctores disponibles
int OperacionesDoctores::obtenerDoctoresDisponibles(Doctor resultados[], int maxResultados) {
    int encontrados = 0;
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    ifstream archivo(FILE_DOCTORES, ios::binary);
    
    if (!archivo.is_open()) return 0;
    
    archivo.seekg(sizeof(ArchivoHeader));
    Doctor doctor;
    
    for (int i = 0; i < header.cantidadRegistros && encontrados < maxResultados; i++) {
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        if (archivo.fail()) break;
        
        if (!doctor.getEliminado() && doctor.getDisponible()) {
            resultados[encontrados] = doctor;
            encontrados++;
        }
    }
    
    archivo.close();
    return encontrados;
}

// Método para contar doctores activos
int OperacionesDoctores::contarDoctoresActivos() {
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    return header.registrosActivos;
}

// Método para verificar si un doctor existe
bool OperacionesDoctores::existeDoctor(int id) {
    return buscarIndiceDoctorPorID(id) != -1;
}

// Método para obtener todos los doctores
int OperacionesDoctores::obtenerTodosDoctores(Doctor resultados[], int maxResultados) {
    int total = 0;
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    ifstream archivo(FILE_DOCTORES, ios::binary);
    
    if (!archivo.is_open()) return 0;
    
    archivo.seekg(sizeof(ArchivoHeader));
    Doctor doctor;
    
    for (int i = 0; i < header.cantidadRegistros && total < maxResultados; i++) {
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        if (archivo.fail()) break;
        resultados[total] = doctor;
        total++;
    }
    
    archivo.close();
    return total;
}

// Método para buscar doctores por nombre (búsqueda parcial)
int OperacionesDoctores::buscarDoctoresPorNombre(const char* nombre, Doctor resultados[], int maxResultados) {
    int encontrados = 0;
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    ifstream archivo(FILE_DOCTORES, ios::binary);
    
    if (!archivo.is_open()) return 0;
    
    archivo.seekg(sizeof(ArchivoHeader));
    Doctor doctor;
    
    for (int i = 0; i < header.cantidadRegistros && encontrados < maxResultados; i++) {
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        if (archivo.fail()) break;
        
        if (!doctor.getEliminado()) {
            // Búsqueda case-insensitive
            char nombreDoctor[50];
            strcpy(nombreDoctor, doctor.getNombre());
            for (int j = 0; nombreDoctor[j]; j++) {
                nombreDoctor[j] = tolower(nombreDoctor[j]);
            }
            
            char nombreBuscado[50];
            strcpy(nombreBuscado, nombre);
            for (int j = 0; nombreBuscado[j]; j++) {
                nombreBuscado[j] = tolower(nombreBuscado[j]);
            }
            
            if (strstr(nombreDoctor, nombreBuscado) != NULL) {
                resultados[encontrados] = doctor;
                encontrados++;
            }
        }
    }
    
    archivo.close();
    return encontrados;
}

void OperacionesDoctores::listarTodosDoctores() {
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_DOCTORES);
    ifstream archivo(FILE_DOCTORES, ios::binary);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir archivo de doctores" << endl;
        return;
    }
    
    archivo.seekg(sizeof(ArchivoHeader));
    int doctoresActivos = 0;
    Doctor doctor;
    
    cout << "\n╔═════╦═══════════════════════╦════════════════╦══════════════╦════════════╗" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO       ║ ESPECIALIDAD   ║ AÑOS EXP.    ║ COSTO      ║" << endl;
    cout << "╠═════╬═══════════════════════╬════════════════╬══════════════╬════════════╣" << endl;

    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
        if (archivo.fail()) break;
        
        if (!doctor.getEliminado()) {
            doctoresActivos++;
            
            // Crear nombre completo
            char nombreCompleto[100];
            snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s", 
                     doctor.getNombre(), doctor.getApellido());
            
            // Truncar si es muy largo
            if (strlen(nombreCompleto) > 21) {
                nombreCompleto[18] = '.';
                nombreCompleto[19] = '.';
                nombreCompleto[20] = '.';
                nombreCompleto[21] = '\0';
            }

            cout << "║ " << setw(3) << left << doctor.getId() << " ";
            cout << "║ " << setw(21) << left << nombreCompleto << " ";
            cout << "║ " << setw(14) << left << doctor.getEspecialidad() << " ";
            cout << "║ " << setw(12) << left << doctor.getAniosExperiencia() << " ";
            cout << "║ $" << setw(8) << left << fixed << setprecision(2) << doctor.getCostoConsulta() << "║" << endl;
        }
    }

    if (doctoresActivos == 0) {
        cout << "║                     NO HAY DOCTORES REGISTRADOS                      ║" << endl;
    }

    cout << "╚═════╩═══════════════════════╩════════════════╩══════════════╩════════════╝" << endl;
    cout << "Total de doctores activos: " << doctoresActivos << endl;
    archivo.close();
}
void OperacionesDoctores::mostrarDoctoresArray(Doctor doctores[], int cantidad) {
    if (cantidad == 0) {
        cout << "No se encontraron doctores." << endl;
        return;
    }
    
    cout << "\n╔═════╦═══════════════════════╦════════════════╦══════════════╦════════════╗" << endl;
    cout << "║ ID  ║ NOMBRE COMPLETO       ║ ESPECIALIDAD   ║ AÑOS EXP.    ║ COSTO      ║" << endl;
    cout << "╠═════╬═══════════════════════╬════════════════╬══════════════╬════════════╣" << endl;

    for (int i = 0; i < cantidad; i++) {
        // Crear nombre completo
        char nombreCompleto[100];
        snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s", 
                 doctores[i].getNombre(), doctores[i].getApellido());
        
        // Truncar si es muy largo
        if (strlen(nombreCompleto) > 21) {
            nombreCompleto[18] = '.';
            nombreCompleto[19] = '.';
            nombreCompleto[20] = '.';
            nombreCompleto[21] = '\0';
        }

        cout << "║ " << setw(3) << left << doctores[i].getId() << " ";
        cout << "║ " << setw(21) << left << nombreCompleto << " ";
        cout << "║ " << setw(14) << left << doctores[i].getEspecialidad() << " ";
        cout << "║ " << setw(12) << left << doctores[i].getAniosExperiencia() << " ";
        cout << "║ $" << setw(8) << left << fixed << setprecision(2) << doctores[i].getCostoConsulta() << "║" << endl;
    }
    cout << "╚═════╩═══════════════════════╩════════════════╩══════════════╩════════════╝" << endl;
    cout << "Total encontrados: " << cantidad << endl;
}
// =============================================
// OPERACIONES CITAS
// =============================================
class OperacionesCitas {
public:
    static bool agregarCita(Cita& nuevaCita);
    static Cita buscarCitaPorID(int id);
    static int buscarIndiceCitaPorID(int id);
    static bool actualizarCita(Cita& citaModificada);
    static bool eliminarCita(int id);
    static bool cancelarCita(int idCita);
    static bool atenderCita(int idCita, const char* diagnostico, const char* tratamiento, 
    const char* medicamentos, float costo);
    private:
    static void mostrarError(const char* mensaje);
    static void mostrarExito(const char* mensaje);
    
};

bool OperacionesCitas::agregarCita(Cita& nuevaCita) {
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_CITAS);
    nuevaCita.setId(header.siguienteId);
    nuevaCita.setFechaCreacion(GestorArchivos::obtenerTimestamp());
    nuevaCita.setFechaModificacion(GestorArchivos::obtenerTimestamp());
    nuevaCita.setEliminado(false);
    
    ofstream archivo(FILE_CITAS, ios::binary | ios::app);
    if (!archivo.is_open()) return false;
    
    archivo.write(reinterpret_cast<const char*>(&nuevaCita), sizeof(Cita));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    header.cantidadRegistros++;
    header.siguienteId++;
    header.registrosActivos++;
    bool exitoHeader = GestorArchivos::actualizarHeader(FILE_CITAS, header);
    archivo.close();
    return exitoHeader;
}
const char* Cita::getMotivo() const {
    return motivo;
}

void Cita::setFechaCreacion(time_t fecha) {
    this->fechaCreacion = fecha;
}
Cita OperacionesCitas::buscarCitaPorID(int id) {
    Cita cita;
    if (id < 1) return cita;
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_CITAS);
    ifstream archivo(FILE_CITAS, ios::binary);
    if (!archivo.is_open()) return cita;
    
    archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    for (int i = 0; i < header.cantidadRegistros; i++) {
        Cita citaActual;
        archivo.read(reinterpret_cast<char*>(&citaActual), sizeof(Cita));
        if (archivo.fail()) break;
        
        if (citaActual.getId() == id && !citaActual.getEliminado()) {
            cita = citaActual;
            break;
        }
    }
    archivo.close();
    return cita;
}

int OperacionesCitas::buscarIndiceCitaPorID(int id) {
    ifstream archivo(FILE_CITAS, ios::binary);
    if (!archivo.is_open()) return -1;
    
    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    Cita temp;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(Cita));
        if (temp.getId() == id && !temp.getEliminado()) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}

bool OperacionesCitas::actualizarCita(Cita& citaModificada) {
    int indice = buscarIndiceCitaPorID(citaModificada.getId());
    if (indice == -1) return false;
    
    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    
    long posicion = GestorArchivos::getPosicionCita(indice);
    archivo.seekp(posicion);
    citaModificada.setFechaModificacion(GestorArchivos::obtenerTimestamp());
    archivo.write(reinterpret_cast<const char*>(&citaModificada), sizeof(Cita));
    bool exito = !archivo.fail();
    archivo.close();
    return exito;
}

bool OperacionesCitas::eliminarCita(int id) {
    int indice = buscarIndiceCitaPorID(id);
    if (indice == -1) return false;
    
    fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    
    long posicion = GestorArchivos::getPosicionCita(indice);
    archivo.seekg(posicion);
    Cita cita;
    archivo.read(reinterpret_cast<char*>(&cita), sizeof(Cita));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    if (cita.getEliminado()) {
        archivo.close();
        return false;
    }
    
    cita.setEliminado(true);
    cita.setFechaModificacion(time(0));
    
    archivo.seekp(posicion);
    archivo.write(reinterpret_cast<const char*>(&cita), sizeof(Cita));
    
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_CITAS);
    header.registrosActivos--;
    if (!GestorArchivos::actualizarHeader(FILE_CITAS, header)) {
        archivo.close();
        return false;
    }
    
    archivo.close();
    return true;
}

// =============================================
// OPERACIONES HISTORIAL
// =============================================
class OperacionesHistorial {
public:
    static bool agregarHistorial(HistorialMedico& nuevoHistorial);
    static HistorialMedico buscarHistorialPorID(int id);
};

bool OperacionesHistorial::agregarHistorial(HistorialMedico& nuevoHistorial) {
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_HISTORIALES);
    nuevoHistorial.setId(header.siguienteId);
    nuevoHistorial.setFecharegistro(GestorArchivos::obtenerTimestamp());
    nuevoHistorial.setEliminado(false);
    
    ofstream archivo(FILE_HISTORIALES, ios::binary | ios::app);
    if (!archivo.is_open()) return false;
    
    archivo.write(reinterpret_cast<const char*>(&nuevoHistorial), sizeof(HistorialMedico));
    if (archivo.fail()) {
        archivo.close();
        return false;
    }
    
    header.cantidadRegistros++;
    header.siguienteId++;
    header.registrosActivos++;
    bool exitoHeader = GestorArchivos::actualizarHeader(FILE_HISTORIALES, header);
    archivo.close();
    return exitoHeader;
}

HistorialMedico OperacionesHistorial::buscarHistorialPorID(int id) {
    HistorialMedico historial;
    if (id < 1) return historial;
    
    ArchivoHeader header = GestorArchivos::leerHeader(FILE_HISTORIALES);
    ifstream archivo(FILE_HISTORIALES, ios::binary);
    if (!archivo.is_open()) return historial;
    
    archivo.seekg(sizeof(ArchivoHeader), ios::beg);
    for (int i = 0; i < header.cantidadRegistros; i++) {
        HistorialMedico historialActual;
        archivo.read(reinterpret_cast<char*>(&historialActual), sizeof(HistorialMedico));
        if (archivo.fail()) break;
        
        if (historialActual.getId() == id && !historialActual.getEliminado()) {
            historial = historialActual;
            break;
        }
    }
    archivo.close();
    return historial;
}
bool OperacionesCitas::cancelarCita(int idCita) {
    // 1. Buscar la cita en archivo binario
    Cita cita = buscarCitaPorID(idCita);
    if (cita.getId() == 0) {
        mostrarError("Cita no encontrada");
        return false;
    }

    // 2. Validar estado de la cita
    if (strcmp(cita.getEstado(), "Atendida") == 0) {
        mostrarError("No se puede cancelar una cita ya atendida");
        return false;
    }

    if (strcmp(cita.getEstado(), "Cancelada") == 0) {
        mostrarError("La cita ya está cancelada");
        return false;
    }

    // 3. Cambiar estado a "Cancelada"
    cita.setEstado("Cancelada");
    cita.setFechaModificacion(time(0));

    // 4. Actualizar cita en archivo binario
    if (!actualizarCita(cita)) {
        mostrarError("Error al actualizar la cita en el archivo");
        return false;
    }

    mostrarExito("Cita cancelada correctamente");
    return true;
}

bool OperacionesCitas::atenderCita(int idCita, const char* diagnostico, const char* tratamiento, 
    const char* medicamentos, float costo) {
    // SOLO validaciones esenciales 
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
    if (cita.getId() == 0) {
        mostrarError("Cita no encontrada");
        return false;
    }

    // 2. Validar estado de la cita
    if (strcmp(cita.getEstado(), "Atendida") == 0) {
        mostrarError("La cita ya fue atendida");
        return false;
    }

    if (strcmp(cita.getEstado(), "Cancelada") == 0) {
        mostrarError("No se puede atender una cita cancelada");
        return false;
    }

    // 3. Actualizar datos de la atención
    cita.setDiagnostico(diagnostico);
    cita.setTratamiento(tratamiento);
    cita.setMedicamentos(medicamentos);
    cita.setCosto(costo);
    cita.setEstado("Atendida");
    cita.setFechaModificacion(time(0));

    // 4. Actualizar cita en archivo binario
    if (!actualizarCita(cita)) {
        mostrarError("Error al actualizar la cita en el archivo");
        return false;
    }

    mostrarExito("Cita atendida correctamente");
    return true;
}

// =============================================
// MÉTODOS PRIVADOS
// =============================================

void OperacionesCitas::mostrarError(const char* mensaje) {
    cout << "❌ Error: " << mensaje << endl;
}

void OperacionesCitas::mostrarExito(const char* mensaje) {
    cout << "✅ " << mensaje << endl;
}
// =============================================
// FUNCIONES DEL SISTEMA
// =============================================
Hospital inicializarHospital(const char* nombre) {
    Hospital hospital;
    ifstream archivo(FILE_HOSPITAL, ios::binary);
    if (!archivo.is_open()) {
        cout << "Inicializando sistema hospitalario por primera vez..." << endl;
        hospital.setNombre("Hospital Coco 2");
        hospital.setDireccion("");
        hospital.setTelefono("");
        return hospital;
    }
    
    archivo.read(reinterpret_cast<char*>(&hospital), sizeof(Hospital));
    archivo.close();
    
    if (!GestorArchivos::verificarArchivo(FILE_PACIENTES)) {
        GestorArchivos::inicializarArchivo(FILE_PACIENTES);
    }
    if (!GestorArchivos::verificarArchivo(FILE_DOCTORES)) {
        GestorArchivos::inicializarArchivo(FILE_DOCTORES);
    }
    if (!GestorArchivos::verificarArchivo(FILE_CITAS)) {
        GestorArchivos::inicializarArchivo(FILE_CITAS);
    }
    if (!GestorArchivos::verificarArchivo(FILE_HISTORIALES)) {
        GestorArchivos::inicializarArchivo(FILE_HISTORIALES);
    }
    
    return hospital;
}

bool guardarDatosHospital(Hospital& hospital) {
    ofstream archivo(FILE_HOSPITAL, ios::binary);
    if (!archivo.is_open()) return false;
    
    archivo.write(reinterpret_cast<const char*>(&hospital), sizeof(Hospital));
    archivo.close();
    return true;
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

// =============================================
// MENÚS DEL SISTEMA
// =============================================
void menuPacientes(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n╔═════════════════════════════════════╗" << endl;
        cout << "║         GESTIÓN DE PACIENTES          ║" << endl;
        cout << "╠═══════════════════════════════════════╣" << endl;
        cout << "║ 1. Registrar nuevo paciente           ║" << endl;
        cout << "║ 2. Buscar paciente por ID             ║" << endl;
        cout << "║ 3. Buscar paciente por cédula         ║" << endl;
        cout << "║ 4. Buscar paciente por nombre         ║" << endl;
        cout << "║ 5. Ver historial médico completo      ║" << endl;
        cout << "║ 6. Actualizar datos del paciente      ║" << endl;
        cout << "║ 7. Listar todos los pacientes         ║" << endl;
        cout << "║ 8. Eliminar paciente                  ║" << endl;
        cout << "║ 0. Volver al menú principal           ║" << endl;
        cout << "╚═══════════════════════════════════════╝" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch (opcion) {
            case 1: {
                Paciente nuevoPaciente = capturarDatosPaciente();
                
                if (OperacionesPacientes::existePacienteConCedula(nuevoPaciente.getCedula())) {
                    GestorArchivos::mostrarError("Ya existe un paciente con esta cédula");
                    break;
                }
                
                if (!Validaciones::validarEdad(nuevoPaciente.getEdad())) {
                    GestorArchivos::mostrarError("La edad debe estar entre 0 y 120 años");
                    break;
                }
                
                if (!Validaciones::validarSexo(nuevoPaciente.getSexo())) {
                    GestorArchivos::mostrarError("El sexo debe ser 'M' o 'F'");
                    break;
                }
                
                if (OperacionesPacientes::agregarPaciente(nuevoPaciente)) {
                    hospital.incrementarPacientesRegistrados();
                    GestorArchivos::mostrarExito("Paciente registrado correctamente");
                } else {
                    GestorArchivos::mostrarError("Error al registrar paciente");
                }
                break;
            }
            
            case 2: {
                int id;
                cout << "Ingrese ID del paciente: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Paciente paciente = OperacionesPacientes::buscarPacientePorID(id);
                if (paciente.getId() != 0) {
                    cout << "\n=== DATOS DEL PACIENTE ===" << endl;
                    cout << "ID: " << paciente.getId() << endl;
                    cout << "Nombre: " << paciente.getNombre() << " " << paciente.getApellido() << endl;
                    cout << "Cédula: " << paciente.getCedula() << endl;
                    cout << "Edad: " << paciente.getEdad() << endl;
                    cout << "Sexo: " << paciente.getSexo() << endl;
                    cout << "Teléfono: " << paciente.getTelefono() << endl;
                    cout << "Email: " << paciente.getEmail() << endl;
                } else {
                    GestorArchivos::mostrarError("Paciente no encontrado");
                }
                break;
            }
            
            case 3: {
                char cedula[20];
                cout << "Ingrese cédula del paciente: ";
                cin.getline(cedula, 20);
                
                Paciente paciente = OperacionesPacientes::buscarPacientePorCedula(cedula);
                if (paciente.getId() != 0) {
                    cout << "\n=== DATOS DEL PACIENTE ===" << endl;
                    cout << "ID: " << paciente.getId() << endl;
                    cout << "Nombre: " << paciente.getNombre() << " " << paciente.getApellido() << endl;
                    cout << "Cédula: " << paciente.getCedula() << endl;
                    cout << "Edad: " << paciente.getEdad() << endl;
                    cout << "Teléfono: " << paciente.getTelefono() << endl;
                } else {
                    GestorArchivos::mostrarError("Paciente no encontrado");
                }
                break;
            }
            
            case 4: {
                char nombre[50];
                cout << "Ingrese nombre del paciente: ";
                cin.getline(nombre, 50);
                
                ArchivoHeader header = GestorArchivos::leerHeader(FILE_PACIENTES);
                ifstream archivo(FILE_PACIENTES, ios::binary);
                bool encontrado = false;
                
                if (archivo.is_open()) {
                    archivo.seekg(sizeof(ArchivoHeader));
                    Paciente paciente;
                    
                    for (int i = 0; i < header.cantidadRegistros; i++) {
                        archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
                        if (archivo.fail()) break;
                        
                        if (!paciente.getEliminado() && Validaciones::mi_strcasecmp(paciente.getNombre(), nombre) == 0) {
                            cout << "\n=== PACIENTE ENCONTRADO ===" << endl;
                            cout << "ID: " << paciente.getId() << endl;
                            cout << "Nombre: " << paciente.getNombre() << " " << paciente.getApellido() << endl;
                            cout << "Cédula: " << paciente.getCedula() << endl;
                            cout << "Edad: " << paciente.getEdad() << endl;
                            cout << "Sexo: " << paciente.getSexo() << endl;
                            cout << "Teléfono: " << paciente.getTelefono() << endl;
                            cout << "Email: " << paciente.getEmail() << endl;
                            encontrado = true;
                            break;
                        }
                    }
                    archivo.close();
                }
                
                if (!encontrado) {
                    GestorArchivos::mostrarError("Paciente no encontrado");
                }
                break;
            }
            
            case 5: {
                int id;
                cout << "Ingrese ID del paciente: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Paciente paciente = OperacionesPacientes::buscarPacientePorID(id);
                if (paciente.getId() == 0) {
                    GestorArchivos::mostrarError("Paciente no encontrado");
                    break;
                }

                cout << "\n=== HISTORIAL MÉDICO DEL PACIENTE ===" << endl;
                cout << "Paciente: " << paciente.getNombre() << " " << paciente.getApellido() << endl;
                cout << "Esta funcionalidad requiere implementación adicional." << endl;
                break;
            }
            
            case 6: {
                int id;
                cout << "Ingrese ID del paciente a modificar: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Paciente paciente = OperacionesPacientes::buscarPacientePorID(id);
                if (paciente.getId() == 0) {
                    GestorArchivos::mostrarError("Paciente no encontrado");
                    break;
                }
                
                cout << "Modificando datos del paciente: " << paciente.getNombre() << " " << paciente.getApellido() << endl;
                Paciente pacienteModificado = capturarDatosPaciente();
                pacienteModificado.setId(id);
                
                if (OperacionesPacientes::actualizarPaciente(pacienteModificado)) {
                    GestorArchivos::mostrarExito("Paciente modificado correctamente");
                } else {
                    GestorArchivos::mostrarError("Error al modificar paciente");
                }
                break;
            }
            
            case 7: {
                OperacionesPacientes::listarTodosPacientes();
                break;
            }
            
            case 8: {
                int id;
                cout << "Ingrese ID del paciente a eliminar: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                cout << "¿Está seguro de eliminar este paciente? (s/n): ";
                char confirmacion;
                cin >> confirmacion;
                GestorArchivos::limpiarBuffer();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (OperacionesPacientes::eliminarPaciente(id)) {
                        GestorArchivos::mostrarExito("Paciente eliminado correctamente");
                    } else {
                        GestorArchivos::mostrarError("Error al eliminar paciente");
                    }
                } else {
                    cout << "Eliminación cancelada" << endl;
                }
                break;
            }
            
            case 0:
                cout << "Volviendo al menú principal..." << endl;
                break;
                
            default:
                cout << "❌ Opción inválida. Intente nuevamente." << endl;
        }
        
        if (opcion != 0) {
            GestorArchivos::pausar();
        }
        
    } while (opcion != 0);
}

// =============================================
// MENÚ DOCTORES
// =============================================

void menuDoctores() {
    int opcion;
    Doctor doctor;
    
    do {
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║           MENÚ DOCTORES             ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║ 1. Agregar doctor                   ║" << endl;
        cout << "║ 2. Buscar doctor por ID             ║" << endl;
        cout << "║ 3. Buscar doctor por nombre         ║" << endl;
        cout << "║ 4. Listar todos los doctores        ║" << endl;
        cout << "║ 5. Listar doctores por especialidad ║" << endl;
        cout << "║ 6. Actualizar doctor                ║" << endl;
        cout << "║ 7. Eliminar doctor                  ║" << endl;
        cout << "║ 0. Volver al menú principal         ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        cout << "Opción: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1: {
                cout << "\n=== AGREGAR DOCTOR ===" << endl;
                
                if (OperacionesDoctores::agregarDoctor(doctor)) {
                    cout << "✅ Doctor agregado exitosamente!" << endl;
                } else {
                    cout << "❌ Error al agregar doctor" << endl;
                }
                break;
            }
            
            case 2: {
                cout << "\n=== BUSCAR DOCTOR POR ID ===" << endl;
                int id;
                cout << "ID del doctor: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                doctor = OperacionesDoctores::buscarDoctorPorID(id);
                if (doctor.getId() != 0) {
                    cout << "\n--- DOCTOR ENCONTRADO ---" << endl;
                   
                } else {
                    cout << "❌ Doctor no encontrado" << endl;
                }
                break;
            }
            
            case 3: {
                cout << "\n=== BUSCAR DOCTOR POR NOMBRE ===" << endl;
                char nombre[50];
                cout << "Nombre a buscar: ";
                cin.getline(nombre, 50);
                
                Doctor resultados[100];
                int cantidad = OperacionesDoctores::buscarDoctoresPorNombre(nombre, resultados, 100);
                OperacionesDoctores::mostrarDoctoresArray(resultados, cantidad);
                break;
            }
            
            case 4: {
                cout << "\n=== LISTAR TODOS LOS DOCTORES ===" << endl;
                OperacionesDoctores::listarTodosDoctores();
                break;
            }
            
            case 5: {
                cout << "\n=== DOCTORES POR ESPECIALIDAD ===" << endl;
                char especialidad[30];
                cout << "Especialidad: ";
                cin.getline(especialidad, 30);
                
                Doctor resultados[100];
                int cantidad = OperacionesDoctores::buscarDoctoresPorEspecialidad(especialidad, resultados, 100);
                OperacionesDoctores::mostrarDoctoresArray(resultados, cantidad);
                break;
            }
            
            case 6: {
                cout << "\n=== ACTUALIZAR DOCTOR ===" << endl;
                int id;
                cout << "ID del doctor a actualizar: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                doctor = OperacionesDoctores::buscarDoctorPorID(id);
                if (doctor.getId() != 0) {
                    cout << "\n--- DOCTOR ACTUAL ---" << endl;
                    // Llama a tu función para mostrar info del doctor
                    
                    // Aquí llamas a tu función para ingresar nuevos datos
                    Doctor doctorActualizado; // = tuFuncionIngresarDatos();
                    doctorActualizado.setId(id); // Mantener el mismo ID
                    
                    if (OperacionesDoctores::actualizarDoctor(doctorActualizado)) {
                        cout << "✅ Doctor actualizado exitosamente!" << endl;
                    } else {
                        cout << "❌ Error al actualizar doctor" << endl;
                    }
                } else {
                    cout << "❌ Doctor no encontrado" << endl;
                }
                break;
            }
            
            case 7: {
                cout << "\n=== ELIMINAR DOCTOR ===" << endl;
                int id;
                cout << "ID del doctor a eliminar: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                cout << "¿Está seguro de eliminar este doctor? (s/n): ";
                char confirmacion;
                cin >> confirmacion;
               GestorArchivos::limpiarBuffer();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (OperacionesDoctores::eliminarDoctor(id)) {
                        cout << "✅ Doctor eliminado exitosamente!" << endl;
                    } else {
                        cout << "❌ Error al eliminar doctor" << endl;
                    }
                } else {
                    cout << "Eliminación cancelada" << endl;
                }
                break;
            }
            
            case 0: {
                cout << "Volviendo al menú principal..." << endl;
                break;
            }
            
            default: {
                cout << "❌ Opción inválida" << endl;
                break;
            }
        }
        
        if (opcion != 0) {
           GestorArchivos::pausar();
        }
        
    } while (opcion != 0);
}
           

void menuCitas(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n╔════════════════════════════════════════╗" << endl;
        cout << "║           GESTIÓN DE CITAS            ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "║ 1. Agendar nueva cita                 ║" << endl;
        cout << "║ 2. Buscar cita por ID                 ║" << endl;
        cout << "║ 3. Cancelar cita                      ║" << endl;
        cout << "║ 4. Ver citas de un paciente           ║" << endl;
        cout << "║ 5. Ver citas de un doctor             ║" << endl;
        cout << "║ 6. Ver citas pendientes               ║" << endl;
        cout << "║ 0. Volver al menú principal           ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch (opcion) {
            case 1: {
                Cita nuevaCita = capturarDatosCita();
                
                // Verificar que paciente y doctor existen
                Paciente paciente = OperacionesPacientes::buscarPacientePorID(nuevaCita.getPacienteID());
                Doctor doctor = OperacionesDoctores::buscarDoctorPorID(nuevaCita.getDoctorID());
                
                if (paciente.getId() == 0) {
                    GestorArchivos::mostrarError("Paciente no encontrado");
                    break;
                }
                
                if (doctor.getId() == 0) {
                    GestorArchivos::mostrarError("Doctor no encontrado");
                    break;
                }
                
                if (!Validaciones::validarFecha(nuevaCita.getFecha())) {
                    GestorArchivos::mostrarError("Fecha no válida");
                    break;
                }
                
                if (!Validaciones::validarHora(nuevaCita.getHora())) {
                    GestorArchivos::mostrarError("Hora no válida");
                    break;
                }
                
                if (OperacionesCitas::agregarCita(nuevaCita)) {
                    // Agregar cita al paciente
                    paciente.agregarCitaID(nuevaCita.getId());
                    OperacionesPacientes::actualizarPaciente(paciente);
                    
                    // Agregar cita al doctor
                    doctor.agregarCitaID(nuevaCita.getId());
                    OperacionesDoctores::actualizarDoctor(doctor);
                    
                    hospital.incrementarCitasAgendadas();
                    GestorArchivos::mostrarExito("Cita agendada correctamente");
                } else {
                    GestorArchivos::mostrarError("Error al agendar cita");
                }
                break;
            }
            
            case 2: {
                int id;
                cout << "Ingrese ID de la cita: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Cita cita = OperacionesCitas::buscarCitaPorID(id);
                if (cita.getId() != 0) {
                    cout << "\n=== DATOS DE LA CITA ===" << endl;
                    cout << "ID: " << cita.getId() << endl;
                    cout << "Paciente ID: " << cita.getPacienteID() << endl;
                    cout << "Doctor ID: " << cita.getDoctorID() << endl;
                    cout << "Fecha: " << cita.getFecha() << endl;
                    cout << "Hora: " << cita.getHora() << endl;
                    cout << "Motivo: " << cita.getMotivo() << endl;
                    cout << "Estado: " << cita.getEstado() << endl;
                } else {
                    GestorArchivos::mostrarError("Cita no encontrada");
                }
                break;
            }
            
            case 3: {
                int id;
                cout << "Ingrese ID de la cita a cancelar: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Cita cita = OperacionesCitas::buscarCitaPorID(id);
                if (cita.getId() == 0) {
                    GestorArchivos::mostrarError("Cita no encontrada");
                    break;
                }
                
                cita.setEstado("Cancelada");
                if (OperacionesCitas::actualizarCita(cita)) {
                    GestorArchivos::mostrarExito("Cita cancelada correctamente");
                } else {
                    GestorArchivos::mostrarError("Error al cancelar cita");
                }
                break;
            }
            
            case 4: {
                int id;
                cout << "Ingrese ID del paciente: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Paciente paciente = OperacionesPacientes::buscarPacientePorID(id);
                if (paciente.getId() == 0) {
                    GestorArchivos::mostrarError("Paciente no encontrado");
                    break;
                }
                
                cout << "\n=== CITAS DEL PACIENTE ===" << endl;
                cout << "Paciente: " << paciente.getNombre() << " " << paciente.getApellido() << endl;
                cout << "Total de citas: " << paciente.getCantidadCitas() << endl;
                // Aquí se implementaría la búsqueda de citas por paciente
                break;
            }
            
            case 5: {
                int id;
                cout << "Ingrese ID del doctor: ";
                cin >> id;
                GestorArchivos::limpiarBuffer();
                
                Doctor doctor = OperacionesDoctores::buscarDoctorPorID(id);
                if (doctor.getId() == 0) {
                    GestorArchivos::mostrarError("Doctor no encontrado");
                    break;
                }
                
                cout << "\n=== CITAS DEL DOCTOR ===" << endl;
                cout << "Doctor: " << doctor.getNombre() << " " << doctor.getApellido() << endl;
                cout << "Total de citas: " << doctor.getCantidadCitas() << endl;
                // Aquí se implementaría la búsqueda de citas por doctor
                break;
            }
            
            case 6: {
                cout << "\n=== CITAS PENDIENTES ===" << endl;
                // Implementar listado de citas pendientes
                cout << "Funcionalidad en desarrollo..." << endl;
                break;
            }
            
            case 0:
                cout << "Volviendo al menú principal..." << endl;
                break;
                
            default:
                cout << "❌ Opción inválida. Intente nuevamente." << endl;
        }
        
        if (opcion != 0) {
            GestorArchivos::pausar();
        }
        
    } while (opcion != 0);
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
        cout << "10. Reiniciar pacientes" << endl;
        cout << "11. Reiniciar doctores" << endl;
        cout << "12. Reiniciar citas" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch (opcion) {
            case 1: {
                // Verificar integridad de archivos
                std::cout << "\n=== VERIFICANDO INTEGRIDAD DE ARCHIVOS ===" << std::endl;
                if (GestorArchivos::verificarIntegridadArchivos()) {
                    GestorArchivos::mostrarExito("Todos los archivos están en buen estado");
                } else {
                    GestorArchivos::mostrarError("Se encontraron problemas en algunos archivos");
                }
                break;
            }
            
            case 2: {
                // Verificar integridad referencial
                std::cout << "\n=== VERIFICANDO INTEGRIDAD REFERENCIAL ===" << std::endl;
                if (GestorArchivos::verificarIntegridadReferencial()) {
                    GestorArchivos::mostrarExito("Integridad referencial verificada correctamente");
                } else {
                    GestorArchivos::mostrarError("Se encontraron problemas de integridad referencial");
                }
                break;
            }
            
            case 3: {
                // Compactar archivo de pacientes
                std::cout << "\n=== COMPACTAR ARCHIVO DE PACIENTES ===" << std::endl;
                std::cout << "¿Está seguro de compactar el archivo de pacientes? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                GestorArchivos::limpiarBuffer();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (GestorArchivos::compactarArchivoPacientes()) {
                        GestorArchivos::mostrarExito("Archivo de pacientes compactado exitosamente");
                    } else {
                        GestorArchivos::mostrarError("Error al compactar archivo de pacientes");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            
            case 4: {
                // Compactar archivo de doctores
                std::cout << "\n=== COMPACTAR ARCHIVO DE DOCTORES ===" << std::endl;
                std::cout << "¿Está seguro de compactar el archivo de doctores? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                GestorArchivos::limpiarBuffer();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (GestorArchivos::compactarArchivoDoctores()) {
                        GestorArchivos::mostrarExito("Archivo de doctores compactado exitosamente");
                    } else {
                        GestorArchivos::mostrarError("Error al compactar archivo de doctores");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            
            case 5: {
                // Compactar archivo de citas
                std::cout << "\n=== COMPACTAR ARCHIVO DE CITAS ===" << std::endl;
                std::cout << "¿Está seguro de compactar el archivo de citas? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                GestorArchivos::limpiarBuffer();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (GestorArchivos::compactarArchivoCitas()) {
                        GestorArchivos::mostrarExito("Archivo de citas compactado exitosamente");
                    } else {
                        GestorArchivos::mostrarError("Error al compactar archivo de citas");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            
            case 6: {
                // Compactar archivo de historiales
                std::cout << "\n=== COMPACTAR ARCHIVO DE HISTORIALES ===" << std::endl;
                std::cout << "¿Está seguro de compactar el archivo de historiales? (s/n): ";
                char confirmacion;
                std::cin >> confirmacion;
                GestorArchivos::limpiarBuffer();
                
                if (confirmacion == 's' || confirmacion == 'S') {
                    if (GestorArchivos::compactarArchivoHistoriales()) {
                        GestorArchivos::mostrarExito("Archivo de historiales compactado exitosamente");
                    } else {
                        GestorArchivos::mostrarError("Error al compactar archivo de historiales");
                    }
                } else {
                    std::cout << "Operación cancelada." << std::endl;
                }
                break;
            }
            
          case 7:
                cout << "¿Hacer respaldo de todos los datos? (s/n): ";
                char conf;
                cin >> conf;
                if(conf == 's' || conf == 'S') {
                    GestorArchivos::hacerRespaldo();
                } else {
                    cout << "Cancelado" << endl;
                }
                break;
                
            case 8:
                cout << "¿Restaurar desde respaldo? (s/n): ";
                cin >> conf;
                if(conf == 's' || conf == 'S') {
                    GestorArchivos::restaurarRespaldo();
                } else {
                    cout << "Cancelado" << endl;
                }
                break;
                
            case 9:
                GestorArchivos::mostrarEstadisticas();
                break;
                
            case 10:
                cout << "¿REINICIAR ARCHIVO DE PACIENTES? (ESCRIBE 'SI'): ";
                char confirm[10];
                cin.getline(confirm, 10);
                if(strcmp(confirm, "SI") == 0) {
                    GestorArchivos::reiniciarArchivoPacientes();
                } else {
                    cout << "Cancelado" << endl;
                }
                break;
                
            case 11:
                cout << "¿REINICIAR ARCHIVO DE DOCTORES? (ESCRIBE 'SI'): ";
                cin.getline(confirm, 10);
                if(strcmp(confirm, "SI") == 0) {
                    GestorArchivos::reiniciarArchivoDoctores();
                } else {
                    cout << "Cancelado" << endl;
                }
                break;
                
            case 12:
                cout << "¿REINICIAR ARCHIVO DE CITAS? (ESCRIBE 'SI'): ";
                cin.getline(confirm, 10);
                if(strcmp(confirm, "SI") == 0) {
                    GestorArchivos::reiniciarArchivoCitas();
                } else {
                    cout << "Cancelado" << endl;
                }
                break;
                
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
                
            default:
                cout << "Opcion invalida" << endl;
        }
        
        if(opcion != 0) {
           GestorArchivos::pausar();
        }
        
    } while(opcion != 0);
}

// =============================================
// FUNCIÓN PRINCIPAL
// =============================================
int main() {
    Hospital hospital = inicializarHospital("Hospital Coco 2");
    
    int opcion;
    do {
        cout << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║   SISTEMA DE GESTIÓN HOSPITALARIA V2   ║" << endl;
        cout << "╠════════════════════════════════════════╣" << endl;
        cout << "║ 1. Gestión de Pacientes                ║" << endl;
        cout << "║ 2. Gestión de Doctores                 ║" << endl;
        cout << "║ 3. Gestión de Citas                    ║" << endl;
        cout << "║ 4. Mantenimiento de Archivos           ║" << endl;
        cout << "║ 5. Guardar y Salir                     ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        GestorArchivos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                menuPacientes(hospital);
                break;
            case 2:
                menuDoctores();
                break;
            case 3:
                menuCitas(hospital);
                break;
            case 4:
                menuMantenimiento(hospital);
                break;
            case 5:
                if (guardarDatosHospital(hospital)) {
                    cout << "\n✅ Datos guardados correctamente." << endl;
                } else {
                    cout << "\n⚠️  Advertencia: Hubo problemas al guardar algunos datos." << endl;
                }
                cout << "👋 ¡Hasta luego!" << endl;
                break;
            default:
                GestorArchivos::mostrarError("Opción no válida");
        }
    } while (opcion != 5);
    
    return 0;
}

