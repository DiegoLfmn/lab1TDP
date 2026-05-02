#include "Tablero.h"

Tablero::Tablero() {
    paredes = nullptr;
    blockConfigs = nullptr;
    numBlocks = 0;
    exitConfigs = nullptr;
    numExits = 0; 
    
    width = 0;
    height = 0;
    stepLimit = 0;
    nombre = "";
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
int Tablero::extraerEntero(string linea, string etiqueta){
    size_t pos = linea.find(etiqueta);
    if(pos == string::npos) return 0;
    pos += etiqueta.length();
    size_t fin = linea.find(' ',pos);
    if(fin == string::npos) fin = linea.length();
    return stoi(linea.substr(pos, fin - pos));
}
// extreamos caracter para el color
char Tablero::extraerCaracter(string linea, string etiqueta){
    size_t pos = linea.find(etiqueta);
    if(pos == string::npos) return ' ';
    pos += etiqueta.length();
    return linea[pos];
}

bool Tablero::cargarArchivo(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    
    string line, section = "";
    int blockIndex = 0;
    while (getline(file, line)) {
        if(!line.empty() && line.back() == '\r') {
            line.pop_back(); // Eliminar el carácter de retorno de carro
        }
        if (line.empty()) continue;

        if (line[0] == '['){
            section = line;
            continue;   
        }
        if(section == "[META]"){
            if(line.find("WIDTH") != string::npos){
                width = extraerEntero(line, "WIDTH= ");
            } else if(line.find("HEIGHT") != string::npos){
                height = extraerEntero(line, "HEIGHT= ");
            } else if(line.find("STEP_LIMIT") != string::npos){
                stepLimit = extraerEntero(line, "STEP_LIMIT= ");
            } else if (line.find("NAME") != string::npos){
                nombre = line.substr(line.find("NAME= ") + 6);
            }
            
        }
        else if (section == "[BLOCK]"){
            if (blockConfigs == nullptr){
                blockConfigs = new BlockConfig[20]; // maximo 100 bloques
            }
            // id extraida
            int id = stoi(line.substr(0,line.find(' ')));
        
            // extramos atributos 
            char color = extraerCaracter(line, "COLOR= ");
            int w = extraerEntero(line, "WIDTH= ");
            int h = extraerEntero(line, "HEIGHT= ");
            int init_x = extraerEntero(line, "INIT_X= ");
            int init_y = extraerEntero(line, "INIT_Y= ");

            // gemoetria de obtenida a partir de la "matriz"
            bool *gemetria = new bool[w * h];
            size_t geoPos = line.find("GEOMETRY= ") + 10;
            if(geoPos != string::npos){
                geoPos += 9; // saltamos "GEOMETRY= " y el espacio
                int contador = 0;
                while(geoPos != string::npos){
                    if(line[geoPos] == '1'){
                        gemetria[contador] = true;
                        contador++;
                    } else if (line[geoPos] == '0'){
                        gemetria[contador] = false;
                        contador++;
                    }
                    geoPos++;
                }
            }

            // guardar arregllo interno del tablero
            blockConfigs[blockIndex].id = id;
            blockConfigs[blockIndex].color = color;
            blockConfigs[blockIndex].width = w;
            blockConfigs[blockIndex].height = h;
            blockConfigs[blockIndex].init_x = init_x;
            blockConfigs[blockIndex].init_y = init_y;
            blockConfigs[blockIndex].geometry = gemetria;
            blockIndex++;
            numBlocks = blockIndex;
        }
        //salida
        else if(section == "[EXIT]"){
            if(exitConfigs == nullptr){
                exitConfigs = new ExitConfig[20]; // maximo 20 salidas
            }

            char color = extraerCaracter(line, "COLOR= ");
            int x = extraerEntero(line, "X= ");
            int y = extraerEntero(line, "Y= ");
            char orientation = extraerCaracter(line, "ORIENTATION= ");
            int li = extraerEntero(line, "LI= ");
            int lf = extraerEntero(line, "LF= ");
            int step = extraerEntero(line, "STEP= ");


            //guardamos arreglo interno de salidas
            exitConfigs[numExits].color = color;
            exitConfigs[numExits].x = x;
            exitConfigs[numExits].y = y;
            exitConfigs[numExits].orientation = orientation;
            exitConfigs[numExits].li = li;
            exitConfigs[numExits].lf = lf;
            exitConfigs[numExits].step = step;
            numExits++;
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

void Tablero::printTablero(){
    cout << "METADATOS" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Step Limit: " << stepLimit << endl;

    cout << "\nPAREDES" << endl;
    if(paredes != nullptr){
        for(int i=0;i< height;i++){
            for(int j = 0; j< width; j++){
                cout << paredes[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No hay paredes definidas." << endl;
    }
    

    cout << "\nBLOQUES LEIDOS  " << endl;
    for(int i =0; i <numBlocks;i++){
        cout << "Bloque " << blockConfigs[i].id << " (Color " << blockConfigs[i].color 
             << ") empieza en X:" << blockConfigs[i].init_x << " Y:" << blockConfigs[i].init_y << endl;
    }

    cout << "\nSALIDAS LEIDAS " << endl;
    for(int i =0; i < numExits; i++){
        cout << "Salida " << exitConfigs[i].color << " en X:" << exitConfigs[i].x << " Y:" << exitConfigs[i].y << endl;
    }

}
