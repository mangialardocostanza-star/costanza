Sistema para gestionar la línea de sucesión de una familia mafiosa utilizando estructura de árbol binario. 
Implementa las reglas complejas de sucesión automática por muerte, encarcelamiento o edad.

#compilacion
cd PROYECTOEDD
cd src
g++ -std=c++11 -o ../bin/mafia_succession main.cpp tree.cpp node.cpp. #Ejecucion cd ../bin
./mafia_succession. 

Funcionalidades
Carga de CSV a árbol binario
Línea de sucesión ( de solo vivos)
Sucesión automática (sea por muerte, cárcel o edad)
Edición de datos (sin ID)
Persistencia en CSV

Reglas de Sucesión
Sucesor en su propio árbol
Sucesor en el otro hijo del jefe
Compañero sin sucesores
Sucesor en árbol del tío
Jefe con dos sucesores
Búsqueda entre encarcelados
Jefe >70 años o preso → sucesor

Datos de prueba : 30 familiares tanto de la familia corleone como aliados 
