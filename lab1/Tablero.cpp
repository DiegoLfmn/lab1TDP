#include "Tablero.h"

Tablero::Tablero() {
    paredes = nullptr;
    blockConfigs = nullptr;
    exitConfigs = nullptr;
    numBlocks = 0;
    numExits = 0;
    width = 0;
    height = 0;
    stepLimit = 0;
    nombre = "";
}

Tablero::~Tablero() {
    if (paredes != nullptr) {
        for (int i = 0; i < height; i++) delete[] paredes[i];
        delete[] paredes;
    }
    if (blockConfigs != nullptr) {
        for (int i = 0; i < numBlocks; i++) {
            if (blockConfigs[i].geometry != nullptr) delete[] blockConfigs[i].geometry;
        }
        delete[] blockConfigs;
    }
    if (exitConfigs != nullptr) delete[] exitConfigs;
}
// extreamos el numero entero que esta despues de una etiqueta en caso que sea width o height, etc
int Tablero::extraerEntero(string linea, string etiqueta){
    size_t pos = linea.find(etiqueta);
    if(pos == string::npos) return 0;

    pos += etiqueta.length();

    while(pos < linea.length() && linea[pos] == ' ' || linea[pos] == '='){
        pos++;
    }

    size_t fin = linea.find(' ',pos);
    if(fin == string::npos) fin = linea.length();

    if(pos >= fin) return 0;
    
    return stoi(linea.substr(pos, fin - pos));

    /*
    try {
        return stoi(linea.substr(pos, fin - pos));
    }
    catch (...)
    {
        return 0;
    }
    
    
    */
}
// extreamos caracter para el color
char Tablero::extraerCaracter(string linea, string etiqueta){
    size_t pos = linea.find(etiqueta);
    if(pos == string::npos) return ' ';

    pos += etiqueta.length();
    while(pos < linea.length() && linea[pos] == ' ' || linea[pos] == '='){
        pos++;
    }
    if(pos < linea.length()){
        return linea[pos];
    }
    return ' ';
}

bool Tablero::cargarArchivo(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    
    string line, section = "";
    int blockIndex = 0;
    int wallRow = 0;

    while (getline(file, line)) {
        if(!line.empty() && line.back() == '\r') line.pop_back();
        if(line.empty()) continue;
        if(line[0] == '[') {
            section = line;
            continue;
        }
        if (section == "[META]") {
            if (line.find("WIDTH") != string::npos) width = extraerEntero(line, "WIDTH");
            else if (line.find("HEIGHT") != string::npos) height = extraerEntero(line, "HEIGHT");
            else if (line.find("STEP_LIMIT") != string::npos) stepLimit = extraerEntero(line, "STEP_LIMIT");
            else if (line.find("NAME") != string::npos) {
                size_t pos = line.find("NAME");
                pos += 4;
                while (pos < line.length() && (line[pos] == ' ' || line[pos] == '=')) pos++;
                nombre = line.substr(pos);
            }
        }
        else if (section == "[WALL]") {
            if (width <= 0 || height <= 0) continue; // Protección si los metadatos fallaron

            if (paredes == nullptr) {
                paredes = new char*[height];
                for(int i = 0; i < height; i++) paredes[i] = new char[width];
            }

            if (wallRow < height) {
                for (int col = 0; col < width; col++) {
                    if (col < line.length()) paredes[wallRow][col] = line[col];
                    else paredes[wallRow][col] = ' '; // Relleno con espacios si la línea es corta
                }
                wallRow++;
            }
        }
        else if (section == "[BLOCK]") {
            if (blockConfigs == nullptr) blockConfigs = new BlockConfig[30]; // Margen seguro

            size_t firstSpace = line.find(' ');
            if (firstSpace == string::npos) continue; // Si la línea está mal, la saltamos

            int id = 0;
            try { id = stoi(line.substr(0, firstSpace)); } catch(...) {}

            char color = extraerCaracter(line, "COLOR");
            int w = extraerEntero(line, "WIDTH");
            int h = extraerEntero(line, "HEIGHT");
            int ix = extraerEntero(line, "INIT_X");
            int iy = extraerEntero(line, "INIT_Y");

            bool* geometria = nullptr;
            if (w > 0 && h > 0) {
                geometria = new bool[w * h]; 
                for(int i = 0; i < (w * h); i++) geometria[i] = false; // Llenamos de 0 por seguridad

                size_t geoPos = line.find("GEOMETRY");
                if (geoPos != string::npos) {
                    geoPos += 8;
                    while (geoPos < line.length() && (line[geoPos] == ' ' || line[geoPos] == '=')) geoPos++;
                    
                    int contador = 0;
                    while(geoPos < line.length() && contador < (w * h)) {
                        if (line[geoPos] == '1') { geometria[contador] = true; contador++; }
                        else if (line[geoPos] == '0') { geometria[contador] = false; contador++; }
                        geoPos++;
                    }
                }
            }

            blockConfigs[blockIndex].id = id;
            blockConfigs[blockIndex].color = color;
            blockConfigs[blockIndex].width = w;
            blockConfigs[blockIndex].height = h;
            blockConfigs[blockIndex].init_x = ix;
            blockConfigs[blockIndex].init_y = iy;
            blockConfigs[blockIndex].geometry = geometria;
            
            blockIndex++;
            numBlocks = blockIndex;
        }
        
        //salida
        else if (section == "[EXIT]") {
            if (exitConfigs == nullptr) exitConfigs = new ExitConfig[30]; // Margen seguro

            exitConfigs[numExits].color = extraerCaracter(line, "COLOR");
            exitConfigs[numExits].x = extraerEntero(line, "X");
            exitConfigs[numExits].y = extraerEntero(line, "Y");
            exitConfigs[numExits].orientation = extraerCaracter(line, "ORIENTATION");
            exitConfigs[numExits].li = extraerEntero(line, "LI");
            exitConfigs[numExits].lf = extraerEntero(line, "LF");
            exitConfigs[numExits].step = extraerEntero(line, "STEP");

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
        inicialBlocks[i].x = blockConfigs[i].init_x;
        inicialBlocks[i].y = blockConfigs[i].init_y;
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
                cout << paredes[i][j];
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
