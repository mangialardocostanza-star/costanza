#!/bin/bash
echo "==========================================="
echo "    COMPILANDO SISTEMA HOSPITALARIO"
echo "==========================================="
echo "Archivos a compilar:"
ls *.cpp | xargs -n 4 echo "   "
echo ""

echo "--- COMPILANDO ---"
g++ -Wall -Wextra -g3 *.cpp -o hospital

if [ -f "hospital" ]; then
    echo ""
    echo "✅ ¡COMPILACIÓN EXITOSA!"
    echo ""
    echo "==========================================="
    echo "    EJECUTANDO SISTEMA HOSPITALARIO"
    echo "==========================================="
    ./hospital
else
    echo ""
    echo "❌ ERRORES DE COMPILACIÓN:"
    echo ""
    g++ -Wall -Wextra -g3 *.cpp -o hospital 2>&1
fi
