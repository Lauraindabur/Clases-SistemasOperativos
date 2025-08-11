#include <iostream>
using namespace std;

void SumaValor(int a, int b){ //por valor se usan mas posivicones de memoria 
    
    cout << "Suma... A->M[" << &a << "] = " << a << endl;
    a= a +b;
    cout << "B->M[" << &b << "] = " << b << endl;  //oara mirar si me cambia la direccion o algo 
    cout << "Suma... A->M[" << &a << "] = " << a << endl;
}

void Sumare(int *a,int *b){
    cout << "Suma... A->M[" << &a << "] = " << a << endl; //por referencia se usan menos posiviones de memoria 
    *a = *a + *b;
    cout << "B->M[" << &b << "] = " << b << endl;  //oara mirar si me cambia la direccion o algo 
    cout << "Suma... A->M[" << &a << "] = " << a << endl;


}

int main(){
    int a=4;
    int b=126;
    cout << "main... A->M[" << &a << "] = " << a << endl;  //po valor se usan mas varibales apra hacer una operacion mas sencilla 
    cout << "main... B->M[" << &b << "] = " << b << endl;
    SumaValor(a,b);


    cout << "----------------------------- " << endl;

    cout << "main... A->M[" << &a << "] = " << a << endl;  //aqui ya no cambia porque es por valor
    cout << "main... B->M[" << &b << "] = " << b << endl;
    Sumare(a,b); //aqui si cambia porque es por referencia y se usa menos memoria
    
    

    return 0;
}