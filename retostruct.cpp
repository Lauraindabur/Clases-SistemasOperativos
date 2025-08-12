#include <iostream>       // Para entrada/salida estándar (cout, cin)
#include <vector>         // Para usar contenedor vector
#include <random>         // Generación de números aleatorios
#include <chrono>         // Medición de tiempos de ejecución
#include <algorithm>      // Para funciones como max() y fill()
#include <string>         // Manejo de strings
#include <iomanip>        // Para formateo de salida (setw, setprecision)

using namespace std;
using namespace std::chrono;

/**
 * Estructura que representa un elemento con tres tipos de datos diferentes.
 * Se usa para demostrar el impacto del paso por valor vs referencia.
 */
struct Elemento {
    int valor;        // Valor entero principal
    float extra;      // Valor flotante adicional
    char info[10];    // Información adicional como cadena de caracteres
    
    // Constructor que inicializa los valores
    Elemento() : valor(0), extra(0.0f) {
        fill(info, info + 10, '\0'); // Rellena el array de chars con nulls
    }
};

/**
 * Genera un vector de elementos con valores aleatorios.
 * {parametro}: n Cantidad de elementos a generar
 * {retorno}:   Vector con los elementos generados
 */
vector<Elemento> generarDatos(size_t n) {
    random_device rd;        // Dispositivo de aleatoriedad hardware-based
    mt19937 gen(rd());       // Motor de generación Mersenne Twister
    uniform_int_distribution<int> dist_valor(1, 100);      // Distribución para el valor entero
    uniform_real_distribution<float> dist_extra(0.0f, 1.0f); // Distribución para el valor float
    
    vector<Elemento> datos(n); // Vector de n elementos
    
    // Llena cada elemento con valores aleatorios
    for (auto& elem : datos) {
        elem.valor = dist_valor(gen);    // Asigna valor entero aleatorio
        elem.extra = dist_extra(gen);    // Asigna valor float aleatorio
        snprintf(elem.info, 10, "ID%d", elem.valor); // Crea info basada en el valor
    }
    return datos;
}

/**
 * Estructura para almacenar resultados de la suma por valor.
 * Incluye memoria utilizada para análisis de performance.
 */
struct Resultados {
    long long sumaValorInt;    // Acumulador para valores enteros
    double sumaValorFloat;     // Acumulador para valores flotantes
    size_t memoria_utilizada;  // Memoria usada durante la operación
};

/**
 * Suma los elementos recibidos por valor (haciendo una copia completa).
 * {parametro}: datos Vector de elementos (se copia completamente)
 * {retorno}:   Estructura con los resultados y memoria usada
 */
Resultados sumarPorValor(vector<Elemento> datos) {
    Resultados res;
    res.sumaValorInt = 0;
    res.sumaValorFloat = 0.0;
    // Calcula memoria como tamaño del vector copiado
    res.memoria_utilizada = datos.size() * sizeof(Elemento);
    
    // Suma todos los valores
    for (const auto& elem : datos) {
        res.sumaValorInt += elem.valor;
        res.sumaValorFloat += elem.extra;
    }
    return res;
}

/**
 * Estructura para almacenar resultados de la suma por referencia.
 */
struct ResultadosReferencia {
    long long sumaRefInt;      // Acumulador para valores enteros
    double sumaRefFloat;       // Acumulador para valores flotantes
    size_t memoria_utilizada;  // Memoria usada (solo la referencia)
};

/**
 * Suma los elementos recibidos por referencia (sin copiar).
 * {parametro}: datos Referencia al vector original
 * {parametro}: res Estructura donde se almacenan los resultados
 */
void sumarPorReferencia(const vector<Elemento>& datos, ResultadosReferencia& res) {
    res.sumaRefInt = 0;
    res.sumaRefFloat = 0.0;
    // Memoria es solo el tamaño de la referencia (puntero)
    res.memoria_utilizada = sizeof(datos);
    
    // Suma todos los valores
    for (const auto& elem : datos) {
        res.sumaRefInt += elem.valor;
        res.sumaRefFloat += elem.extra;
    }
}

/**
 * Muestra una muestra de los datos generados (primeros y últimos 3 elementos).
 * {parametro}: datos Vector con los datos a mostrar
 */
void mostrarEstadisticas(const vector<Elemento>& datos) {
    cout << "Muestra de datos - Primeros 3 elementos:\n";
    for (int i = 0; i < 3 && i < datos.size(); ++i) {
        cout << "Valor: " << setw(3) << datos[i].valor 
             << ", Extra: " << fixed << setprecision(4) << datos[i].extra
             << ", Info: " << datos[i].info << endl;
    }
    
    cout << "\nMuestra de datos - Últimos 3 elementos:\n";
    for (int i = max(0, (int)datos.size() - 3); i < datos.size(); ++i) {
        cout << "Valor: " << setw(3) << datos[i].valor 
             << ", Extra: " << fixed << setprecision(4) << datos[i].extra
             << ", Info: " << datos[i].info << endl;
    }
}

/**
 * Formatea y muestra el consumo de memoria en unidades apropiadas (GB, MB, KB o bytes).
 * {parametro}: bytes Cantidad de bytes a mostrar
 */
void mostrarConsumoMemoria(size_t bytes) {
    cout << fixed << setprecision(2);
    if (bytes >= 1024 * 1024 * 1024) {
        cout << (bytes / (1024.0 * 1024 * 1024)) << " GB";
    } else if (bytes >= 1024 * 1024) {
        cout << (bytes / (1024.0 * 1024)) << " MB";
    } else if (bytes >= 1024) {
        cout << (bytes / 1024.0) << " KB";
    } else {
        cout << bytes << " bytes";
    }
}

/**
 * Función principal que ejecuta la comparación entre paso por valor y referencia.
 * {parametro}: argc Contador de argumentos
 * {parametro}: argv Array de argumentos
 * {retorno}:   Código de salida
 */
int main(int argc, char* argv[]) {
    // Tamaño por defecto del dataset (5 millones de elementos)
    size_t N = 5'000'000;
    
    // Procesamiento de argumentos de línea de comandos
    if (argc > 1) {
        try {
            long input = stol(argv[1]);
            if (input > 0) {
                N = static_cast<size_t>(input); // Usar el valor proporcionado
            } else {
                cerr << "Advertencia: Valor debe ser positivo. Usando valor por defecto." << endl;
            }
        } catch (...) {
            cerr << "Advertencia: Entrada no válida. Usando valor por defecto." << endl;
        }
    }
    
    // Generación del dataset
    cout << "Generando " << N << " estructuras Elemento...\n";
    cout << "Tamaño de la estructura: " << sizeof(Elemento) << " bytes ("
         << "int: " << sizeof(int) << " bytes, "
         << "float: " << sizeof(float) << " bytes, "
         << "char[10]: " << sizeof(char[10]) << " bytes)\n";
    
    vector<Elemento> datos = generarDatos(N);
    mostrarEstadisticas(datos);
    
    // Variables para almacenar resultados
    Resultados resValor;
    ResultadosReferencia resRef;
    
    // Benchmark: Paso por valor (con copia)
    cout << "\nEjecutando suma por valor (copia " << N << " estructuras)...\n";
    auto inicioValor = high_resolution_clock::now();
    resValor = sumarPorValor(datos);
    auto finValor = high_resolution_clock::now();
    auto duracionValor = duration_cast<milliseconds>(finValor - inicioValor);
    
    // Benchmark: Paso por referencia (sin copia)
    cout << "Ejecutando suma por referencia (sin copia)...\n";
    auto inicioRef = high_resolution_clock::now();
    sumarPorReferencia(datos, resRef);
    auto finRef = high_resolution_clock::now();
    auto duracionRef = duration_cast<milliseconds>(finRef - inicioRef);
    
    // Mostrar resultados de las sumas
    cout << "\nRESULTADOS DE SUMA:\n";
    cout << "-----------------------------------------------------\n";
    cout << "| Método           | Enteros       | Flotantes      |\n";
    cout << "-----------------------------------------------------\n";
    cout << "| Por valor        | " << setw(13) << resValor.sumaValorInt << " | " 
         << fixed << setprecision(2) << setw(14) << resValor.sumaValorFloat << " |\n";
    cout << "| Por referencia   | " << setw(13) << resRef.sumaRefInt << " | " 
         << setw(14) << resRef.sumaRefFloat << " |\n";
    cout << "-----------------------------------------------------\n";
    
    // Cálculo detallado de memoria usada
    const size_t bytes_int = N * sizeof(int);
    const size_t bytes_float = N * sizeof(float);
    const size_t bytes_char = N * sizeof(char[10]);
    const size_t bytes_total = bytes_int + bytes_float + bytes_char;
    
    cout << "\nCONSUMO DETALLADO DE MEMORIA:\n";
    cout << "• Memoria original:       ";
    mostrarConsumoMemoria(bytes_total);
    cout << " (" << bytes_total << " bytes)\n";
    
    cout << "• Memoria por valor:      ";
    mostrarConsumoMemoria(resValor.memoria_utilizada);
    cout << " (copia completa)\n";
    
    cout << "• Memoria por ref:        ";
    mostrarConsumoMemoria(resRef.memoria_utilizada);
    cout << " (solo referencia)\n";
    
    cout << "• Memoria total (valor):  ";
    mostrarConsumoMemoria(bytes_total + resValor.memoria_utilizada);
    cout << " (original + copia)\n";
    
    cout << "• Memoria total (ref):    ";
    mostrarConsumoMemoria(bytes_total + resRef.memoria_utilizada);
    cout << " (original + referencia)\n";
    
    // Comparación de tiempos de ejecución
    long maxDenominator = max(1L, duracionRef.count());
    cout << "\nCOMPARACIÓN DE RENDIMIENTO:\n";
    cout << "• Tiempo por valor:       " << duracionValor.count() << " ms\n";
    cout << "• Tiempo por referencia:  " << duracionRef.count() << " ms\n";
    cout << "• La referencia es " << static_cast<double>(duracionValor.count()) / maxDenominator
         << " veces más rápida\n";
    cout << "• Diferencia absoluta:    " << (duracionValor - duracionRef).count() << " ms\n";
    
    // Validación que ambos métodos producen los mismos resultados
    cout << "\nVALIDACIÓN:\n";
    cout << "• Diferencia int:   " << abs(resValor.sumaValorInt - resRef.sumaRefInt) << "\n";
    cout << "• Diferencia float: " << scientific << setprecision(2) 
         << abs(resValor.sumaValorFloat - resRef.sumaRefFloat) << "\n";
    cout << "• Resultados " << (resValor.sumaValorInt == resRef.sumaRefInt && 
                              abs(resValor.sumaValorFloat - resRef.sumaRefFloat) < 0.01 ? 
                              "consistentes" : "inconsistentes") << endl;
    
    return 0;
}