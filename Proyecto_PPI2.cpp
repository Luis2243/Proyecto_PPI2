#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>
#include<locale.h>

using namespace std;

class Auto{
private:
    static int contador;
    int id;
    string marca;
    string modelo;
    int ano;
    string color;
    string precio;
    vector<string> caracteristicas;

public:
    //Constructor que asigna autom�ticamente el identificador �nico
    Auto(string marca, string modelo, int ano, string color, string precio, vector<string> caracteristicas){
        id = ++contador;
        this->marca = marca;
        this->modelo = modelo;
        this->ano = ano;
        this->color = color;
        this->precio = precio;
        this->caracteristicas = caracteristicas;
    }

    //M�todo para mostrar las propiedades del auto
    void mostrarInformacion(){
        cout << "ID: " << id << endl;
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "A�o: " << ano << endl;
        cout << "Color: " << color << endl;
        cout << "Precio: $" << precio << endl;
        cout << "Caracter�sticas:" << endl;
        for(const auto &caracteristica : caracteristicas){
            cout << "- " << caracteristica << endl;
        }
    }

    //M�todo para obtener la marca del auto
    string obtenerMarca() const{
        return marca;
    }

    //M�todo para actualizar la informaci�n del auto
    void actualizarInformacion(){
        cout << "Ingrese la nueva informaci�n para el auto con ID\n" << id << ":" << endl;

        cin.ignore(); //Limpiar el buffer

        cout << "Nueva marca del auto: ";
        getline(cin, marca);

        cout << "Nuevo modelo del auto: ";
        getline(cin, modelo);

        cout << "Nuevo a�o del auto: ";
        cin >> ano;

        cin.ignore(); //Limpiar el buffer

        cout << "Nuevo color del auto: ";
        getline(cin, color);

        cout << "Nuevo precio del auto (puede contener comas y puntos): $";
        getline(cin, precio);

        cout << "N�mero de nuevas caracter�sticas del auto: ";
        int numCaracteristicas;
        cin >> numCaracteristicas;

        cin.ignore(); //Limpiar el buffer

        cout << "Ingrese las nuevas caracter�sticas una por una (puede escribir varias l�neas):" << endl;
        caracteristicas.clear();
        for(int i = 0; i < numCaracteristicas; ++i){
            string caracteristica;
            getline(cin, caracteristica);
            caracteristicas.push_back(caracteristica);
        }

        cout << "Informaci�n actualizada con �xito." << endl;
    }

    //M�todo para obtener el ID del auto
    int obtenerID() const{
        return id;
    }

    //M�todo para obtener el precio del auto
    string obtenerPrecio() const{
        return precio;
    }
};

//Inicializaci�n del contador est�tico
int Auto::contador = 0;

//Declaraci�n de la funci�n imprimirSumaPrecios
void imprimirSumaPrecios(const vector<Auto *> &autos);

//Funciones adicionales

//Funci�n para buscar autos por marca y devolver un vector con los resultados
vector<Auto *> buscarPorMarca(const vector<Auto *> &autos, const string &marcaBuscada){
    vector<Auto *> resultados;
    for(const auto &autoPtr : autos){
        if(autoPtr->obtenerMarca() == marcaBuscada){
            resultados.push_back(autoPtr);
        }
    }
    return resultados;
}

//Funci�n para buscar un auto por ID y devolver un puntero al objeto
Auto *buscarPorID(const vector<Auto *> &autos, int idBuscado){
    for(const auto &autoPtr : autos){
        if(autoPtr->obtenerID() == idBuscado){
            return autoPtr;
        }
    }
    return nullptr;
}

//Funci�n para eliminar un auto por ID
void eliminarPorID(vector<Auto *> &autos, int idEliminar){
    auto it = remove_if(autos.begin(), autos.end(), [idEliminar](Auto *autoPtr){
        if(autoPtr->obtenerID() == idEliminar){
            delete autoPtr; //Liberar la memoria del objeto eliminado
            return true;
        }
        return false;
    });

    autos.erase(it, autos.end()); //Eliminar del vector

    if(it != autos.end()){
        cout << "Auto eliminado con �xito." << endl;
    }else{
        cout << "No se encontr� ning�n auto con el ID especificado." << endl;
    }
}

//Operaci�n para imprimir la suma de precios de autos espec�ficos por ID
void imprimirSumaPreciosEspecificos(const vector<Auto *> &autos, const vector<int> &ids){
    if(autos.empty()){
        cout << "No hay autos registrados." << endl;
        return;
    }

    //Obtener los precios de los autos espec�ficos y eliminar comas
    vector<string> precios;
    for(int id : ids){
        Auto *autoPtr = buscarPorID(autos, id);
        if(autoPtr){
            string precioSinComa = autoPtr->obtenerPrecio();
            precioSinComa.erase(remove(precioSinComa.begin(), precioSinComa.end(), ','), precioSinComa.end());
            precios.push_back(precioSinComa);
        }
    }

    //Calcular la suma de precios
    double sumaPrecios = accumulate(precios.begin(), precios.end(), 0.0,
                                     [](double suma, const string &precio){
                                         return suma + stod(precio);
                                     });

    //Mostrar el resultado con dos decimales
    cout << fixed << setprecision(2);
    cout << "Suma de precios de autos espec�ficos: $" << sumaPrecios << endl;
}

//Operaci�n para imprimir la suma de precios de todos los autos
void imprimirSumaPrecios(const vector<Auto *> &autos){
    if(autos.empty()){
        cout << "No hay autos registrados." << endl;
        return;
    }

    //Obtener los precios de todos los autos y eliminar comas
    vector<string> precios;
    transform(autos.begin(), autos.end(), back_inserter(precios),
              [](const Auto *autoPtr){
                  string precioSinComa = autoPtr->obtenerPrecio();
                  precioSinComa.erase(remove(precioSinComa.begin(), precioSinComa.end(), ','), precioSinComa.end());
                  return precioSinComa;
              });

    //Calcular la suma de precios
    double sumaPrecios = accumulate(precios.begin(), precios.end(), 0.0,
                                     [](double suma, const string &precio){
                                         return suma + stod(precio);
                                     });

    //Mostrar el resultado con dos decimales
    cout << fixed << setprecision(2);
    cout << "Suma de precios de todos los autos: $" << sumaPrecios << endl;
}

int main(){
    setlocale(LC_ALL, "");

    vector<Auto *> autos; //Vector para almacenar punteros a objetos Auto

    cout << "PROYECTO DE PROGRAMACION PARA INGENIEROS II" << endl;

    char opcion;
    do{
        cout << "\n1. Crear nuevo auto" << endl;
        cout << "2. Mostrar informaci�n de autos existentes" << endl;
        cout << "3. Leer auto por ID" << endl;
        cout << "4. Leer autos por marca" << endl;
        cout << "5. Actualizar informaci�n de auto por ID" << endl;
        cout << "6. Eliminar auto por ID" << endl;
        cout << "7. Imprimir suma de precios de autos" << endl;
        cout << "8. Imprimir suma de precios de autos espec�ficos por ID" << endl;
        cout << "9. Salir" << endl;
        cout << "\nIngrese su opci�n: ";
        cin >> opcion;
        cout << endl;

        switch (opcion){
        case '1': {
            string marca, modelo, color, precio;
            int ano;
            vector<string> caracteristicas;

            cin.ignore(); //Limpiar el buffer

            cout << "Ingrese la marca del auto: ";
            getline(cin, marca);

            cout << "Ingrese el modelo del auto: ";
            getline(cin, modelo);

            cout << "Ingrese el a�o del auto: ";
            cin >> ano;

            cin.ignore(); //Limpiar el buffer

            cout << "Ingrese el color del auto: ";
            getline(cin, color);

            cout << "Ingrese el precio del auto (puede contener comas y puntos): $";
            getline(cin, precio);

            int numCaracteristicas;
            cout << "Ingrese el n�mero de caracter�sticas del auto: ";
            cin >> numCaracteristicas;
            cin.ignore(); //Limpiar el buffer
            cout << "Ingrese las caracter�sticas una por una (puede escribir varias l�neas):" << endl;
            for(int i = 0; i < numCaracteristicas; ++i){
                string caracteristica;
                getline(cin, caracteristica);
                caracteristicas.push_back(caracteristica);
            }

            Auto *nuevoAuto = new Auto(marca, modelo, ano, color, precio, caracteristicas);
            autos.push_back(nuevoAuto);
            cout << endl;
            cout << "Auto creado con �xito." << endl;
            break;
        }
        case '2':
            if(autos.empty()){
                cout << "No hay autos registrados." << endl;
            }else{
                cout << "\nInformaci�n de autos existentes:" << endl;
                cout << endl;
                for(const auto &autoPtr : autos){
                    autoPtr->mostrarInformacion();
                    cout << "-----------------------------" << endl;
                }
            }
            break;
        case '3':{
            int idBuscado;
            cout << "Ingrese el ID del auto que desea buscar: ";
            cin >> idBuscado;
            cout << endl;
            //Buscar el auto por ID
            Auto *autoEncontrado = buscarPorID(autos, idBuscado);
            if(autoEncontrado){
                autoEncontrado->mostrarInformacion();
            }else{
                cout << "No se encontr� ning�n auto con el ID especificado." << endl;
            }
            break;
        }
        case '4':{
            string marcaBuscada;
            cout << "Ingrese la marca que desea buscar: ";
            cin.ignore();
            getline(cin, marcaBuscada);
            //Buscar autos por marca
            vector<Auto *> resultados = buscarPorMarca(autos, marcaBuscada);
            if(resultados.empty()){
                cout << "\nNo se encontraron autos con la marca especificada." << endl;
            }else{
                cout << "\nAutos encontrados por marca '" << marcaBuscada << "':\n" << endl;
                for(const auto &autoPtr : resultados){
                    autoPtr->mostrarInformacion();
                    cout << "-----------------------------" << endl;
                }
            }
            break;
        }
        case '5':{
            int idActualizar;
            cout << "Ingrese el ID del auto que desea actualizar: ";
            cin >> idActualizar;
            cout << endl;

            Auto *autoActualizar = buscarPorID(autos, idActualizar);
            if(autoActualizar){
                autoActualizar->actualizarInformacion();
            }else{
                cout << "No se encontr� ning�n auto con el ID especificado." << endl;
            }
            break;
        }
        case '6':{
            int idEliminar;
            cout << "Ingrese el ID del auto que desea eliminar: ";
            cin >> idEliminar;
            cout << endl;

            eliminarPorID(autos, idEliminar);
            break;
        }
        case '7':
            imprimirSumaPrecios(autos);
            break;
        case '8':{
            int numAutos;
            cout << "Ingrese el n�mero de autos para los que desea calcular la suma de precios: ";
            cin >> numAutos;

            vector<int> ids;
            cout << "Ingrese los IDs de los autos uno por uno:" << endl;
            for(int i = 0; i < numAutos; ++i){
                int id;
                cin >> id;
                ids.push_back(id);
            }

            imprimirSumaPreciosEspecificos(autos, ids);
            break;
        }
        case '9':
            //Liberar la memoria al salir del programa
            for (const auto &autoPtr : autos){
                delete autoPtr;
            }
            autos.clear(); //Limpiar el vector
            break;
        default:
            cout << "Opci�n no v�lida. Intente de nuevo." << endl;
            break;
        }
    } while(opcion != '9');

    return 0;
}
