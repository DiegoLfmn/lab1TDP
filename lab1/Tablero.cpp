#include "Tablero.h"

Tablero::Tablero() {
    paredes = nullptr;
    blockConfigs = nullptr;
    numBlocks = 0;
    exitConfigs = nullptr;
    numExits = 0;   
}

Tablero::~Tablero() {
    if (paredes != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] paredes[i];
        }
        delete[] paredes;
    }

    for(int i =0 ;i <numBlocks; i++){
        delete[] blockConfigs[i].geometry;
    }
    delete[] blockConfigs;
    delete[] exitConfigs;
}
// extreamos el numero entero que esta despues de una etiqueta en caso que sea width o height, etc
int extraerEntero(string linea, string etiqueta){
    size_t pos = linea.find(etiqueta);
    if(pos == string::npos) return 0;
    pos += etiqueta.length();
    size_t fin = linea.find(' ',pos);
    if(fin == string::npos) fin = linea.length();
    return stoi(linea.substr(pos, fin - pos));
}
// extreamos caracter para el color
char extraerCaracter(string linea, string etiqueta){
    size_t pos = linea.find(etiqueta);
    if(pos == string::npos) return ' ';
    pos += etiqueta.length();
    return linea[pos];
}

bool Tablero::cargarArchivo(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    
    string line, section;
    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '['){
            section = line;
            continue;   
        }
        if (section == "[WALL]"){
            if (paredes == nullptr){
                paredes = new char*[height];
                for (int i = 0; i < height; i++) {
                    paredes[i] = new char[width];
                }
            }
        }
    }
    file.close();
    return true;   
}


State* Tablero:: generarEstadoInicial(){
    BlockState* inicialBlocks = new BlockState[numBlocks];

    for(int i =0 ; i < numBlocks; i++){
        inicialBlocks[i].id = blockConfigs[i].id;
    }
    return new State(inicialBlocks, numBlocks, 0, "",nullptr, 0);


}
