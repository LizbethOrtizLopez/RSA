//Algoritmo RSA para encriptado y desencriptado de archivos de texto
//Lizbeth Ortiz López
//A00227346

#include <bits/stdc++.h>

using namespace std;

int numeros[] ={2,3,5,7,11,13,17,19,23,29,31,37,47};

int p, q, n, piN, e, d;

string texto_entrada, texto_entrada1;
string nombre_archivo;

vector <string> texto_cifrado;
vector <int> texto_descifrado;

void lectura(string nombre)
{
    texto_entrada="";
    ifstream archivo_entrada;
    archivo_entrada.open(nombre+=".txt",ios::in); //Abrir el archivo en modo lectura

    if(archivo_entrada.fail()){
        cout<<"Error al momento de abrir el archivo";
        exit(1);
    }
    while(!archivo_entrada.eof()){
        getline(archivo_entrada,texto_entrada1);
        texto_entrada+=texto_entrada1;
    }
    archivo_entrada.close();
}

void guardarArchivo(string nombre, vector<string> texto, string causa)
{
    ofstream archivo;
    archivo.open(nombre+=".txt",ios::out);

    if (archivo.fail())
    {
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }
    for (int i=0;i<texto.size();i++)
    {
        archivo<<texto.at(i)<<" ";
    }
    cout<<"Archivo "<<causa<<" guardado con exito en: "<<nombre<<'\n';
    archivo.close();
}

void lectura_encriptada(string nombre)
{
    ifstream archivo_entrada;
    archivo_entrada.open(nombre+=".txt",ios::in);

    int number;

    if (!archivo_entrada.is_open()) {
        cout<<"No se pudo abrir el archivo"<<'\n';
        exit(1);
    }

    while (archivo_entrada >> number) {
        texto_descifrado.push_back(number);
    }
}

void num_pq()
{
    int rad = rand()%12;
    int aux = rad;
    p = numeros[rad];
    do{
        rad = rand()%12;
    }while(rad==aux);

    q = numeros[rad];
}

int mcd(long long int a, long long int b)
{
    if (b!=0) return mcd(b, a%b);
    return a;
}

int e_funcion(long long int phi)
{
    e = 2;
    while (e<phi)
    {
        if (mcd(e,phi)==1){
           return e;
        }
        e++;
    }
    return e;
}

//ax + by = mcd (a,b)
tuple<long long int, long long int, long long int> euclides(long long int a, long long int b)
{
    if (a == 0) return make_tuple(b,0,1); //e y piN son coprimos

    long long int mcd, x, y;
    tie(mcd, x, y) = euclides (b% a, a);
    return make_tuple(mcd, y - (b/a) * x, x); // (mcd, x, y)
}

int modPow(long long int base, long long int exp, long long int mod)
{
    long long int r = 1;
    while (--exp>=0)
    {
        r*=base;
        r%=mod;
    }
    return r;
}

void encriptar()
{
    //obtener p y q
    num_pq();

    //modulo de llave pública y privada
    n= p*q;

    //piN
    piN = (p-1)*(q-1);

    //llave publica
    e = e_funcion(piN);
    d = get<1>(euclides(e, piN));
    while (d<0) d+=piN; //si d es negativo basta con sumar piN para volverlo coprimo

    cout<<"esta es mi p: "<<p<<'\n';
    cout<<"esta es mi q: "<<q<<'\n';
    cout<<"esta es n: "<<n<<'\n';
    cout<<"esta es mi piN: "<<piN<<'\n';
    cout<<"esta es mi e: "<<e<<'\n';
    cout<<"esta es mi d: "<<d<<'\n';


    for (int i=0;i<texto_entrada.size();i++)
    {
        long long int aux = modPow(texto_entrada.at(i),e,n);
        texto_cifrado.push_back(to_string(aux));
    }

    string name = "Encriptado";
    guardarArchivo(name+=nombre_archivo,texto_cifrado,"encriptado");
}


void desencriptar()
{
    string name = "Encriptado";
    lectura_encriptada(name+=nombre_archivo);

    string texto_final="";
    vector <string> tex_fin;

    for (int i=0;i<texto_descifrado.size();i++)
    {
        texto_final+=(char)(modPow(texto_descifrado.at(i),d,n));
    }

    tex_fin.push_back(texto_final);
    string name1 ="Desencriptado";
    guardarArchivo(name1+=nombre_archivo,tex_fin,"desencriptado");
}

int main()
{
    cout<<"Ingrese archivo a encriptar: "<<'\n';
    cin>>nombre_archivo;
    lectura(nombre_archivo);
    encriptar();
    desencriptar();
    return 0;
}
