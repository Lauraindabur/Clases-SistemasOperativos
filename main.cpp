#include <iostream>  //incluya salida por consola 
using namespace std; //para usar el espacio de nombres std

struct Persona{
        string nombre;  //tipo string para cadenas de texto
        int edad;
        double altura;
   };

int main(){
    
    /*
    int valor= 100; //declaracion varibale entera
    int *ptr_valor;  //declaracion de un puntero entero 


    ptr_valor = &valor;  // apunta a la direcciond e memoria de valor y en esa direccion esta el 100

    std::cout << &valor <<"-->Valor:  M[" << &valor << "] = " << valor << std::endl;

    std :: cout <<"ptr_valor : M["<< ptr_valor << "] = "<< *ptr_valor << std :: endl;
    std :: cout <<&ptr_valor <<"-->ptr_valor : M["<< ptr_valor << "] = "<< *ptr_valor << std :: endl;
    
    cout << "esto es:" << *ptr_valor<< endl;
    cout << "esto es:" << ptr_valor<< endl;
    cout << "esto es:" << &valor << endl;
    */
    //--------------------------------------------------------------------------
    //-----------------ARRAYS DESDE APUNTADORES-------------------
    
    int *array_cpp = new int[5]; //crea un array de 5 enteros que por el * es diamico asigna espacio heap
    for (int i=0; i<5; i++){
        array_cpp[i]=(i+1)*100;  //inicializa el array con valores del 1 al 5
    }

    cout << "Array en C++ en heap o dinamicamente.... la sge direccion est en stack "<< &array_cpp << endl;
    for (int i=0; i<5; i++){
        cout << "M["<<&array_cpp[i]<<"] = " << array_cpp[i] <<"contendio se guarda en heap"<< endl; //imprime el array
        cout << "array_cpp[" << i << "]:" << array_cpp[i] << endl;
        cout << array_cpp << endl; //imprime la direccion de memoria del array
    }
    

    delete[] array_cpp; //libera la memoria del array dinamico

    //--------------------------------------------------------------------------
    //--------------------------ESTRUCTURAS EN C++--------------------------
   

   Persona persona1;  //memoria stack 
   persona1.nombre= "Jedi";
   persona1.edad= 25;
   persona1.altura = 1.75;
   
   Persona *ptr_persona2= new Persona; //memoria heap ponemos new porque es obligaorio por el *
   ptr_persona2->nombre= "ideJ";  // con -> nos da los atributos
   ptr_persona2->edad=30;
   ptr_persona2->altura=1.80;

   cout << "Persona1: " << "nombre: " << persona1.nombre  << ", edad: " << persona1.edad  << ", altura: " << persona1.altura << endl;
   cout << "Persona2: " << "nombre: " << ptr_persona2->nombre  << ", edad: " << ptr_persona2->edad  << ", altura: " << ptr_persona2->altura << endl;
   delete ptr_persona2; //libera la memoria del objeto en heap

    return 0;  

    
}
