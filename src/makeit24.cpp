#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
using namespace std;

struct solution{
    vector<int> angka;
    vector<string> op;
    int tipe;
};

void displaySolution (vector<solution> listSolusi) {
    for (int i; i< size(listSolusi); i++){
        if (listSolusi[i].tipe == 0) {
            cout<< "( ( " << listSolusi[i].angka[0] << " " << listSolusi[i].op[0] << " ";
            cout<< listSolusi[i].angka[1] << " ) " << listSolusi[i].op[1] << " ";
            cout<< listSolusi[i].angka[2] << " ) " << listSolusi[i].op[2] << " ";
            cout<< listSolusi[i].angka[3] << "\n";
        }
        if (listSolusi[i].tipe == 1) {
            cout<< "( " << listSolusi[i].angka[0] << " " << listSolusi[i].op[0] << " ";
            cout<< "( " << listSolusi[i].angka[1] << " " << listSolusi[i].op[1] << " ";
            cout<< listSolusi[i].angka[2] << " ) ) " << listSolusi[i].op[2] << " ";
            cout<< listSolusi[i].angka[3] << "\n";
        }
        if (listSolusi[i].tipe == 2) {
            cout<< listSolusi[i].angka[0] << " " << listSolusi[i].op[0] << " ( ( ";
            cout<< listSolusi[i].angka[1] << " " << listSolusi[i].op[1] << " " << listSolusi[i].angka[2]<< " ) " ;
            cout<< listSolusi[i].op[2] << " " << listSolusi[i].angka[3] << ")\n";
        }
        if (listSolusi[i].tipe == 3) {
            cout<< listSolusi[i].angka[0] << " " << listSolusi[i].op[0] << " ( ";
            cout<< listSolusi[i].angka[1] << " " << listSolusi[i].op[1] << " ( " << listSolusi[i].angka[2] << " ";
            cout<< listSolusi[i].op[2] << " " << listSolusi[i].angka[3] << " ) )\n";
        }
        if (listSolusi[i].tipe == 4) {
            cout<< "( " << listSolusi[i].angka[0] << " " << listSolusi[i].op[0] << " " << listSolusi[i].angka[1] <<  " ) ";
            cout<< listSolusi[i].op[1] ;
            cout<< " ( " << listSolusi[i].angka[2] << " "<< listSolusi[i].op[2] << " " << listSolusi[i].angka[3] << " )\n";
        }
    }
}

float calculate(int bil1, int bil2, string op) {
    float hasil;
    if (op == "+"){
        hasil = bil1 + bil2;
    }
    else if (op == "-"){
        hasil = bil1 - bil2;
    }
    else if (op == "*"){
        hasil = bil1 * bil2;
    }
    else if (op == "/" && bil2 != 0){
        hasil = bil1 / bil2;
    }
    else {
        hasil = -999999;
    }
    return hasil;
}

vector<solution> evaluate (vector<int> angka, vector<string> operasi){ 
    float x,y,z;
    vector<solution> result;
    vector<vector<int>> urutan = {{0,1,2,3},{1,2,0,3},{1,2,3,0},{2,3,1,0}};
    vector<vector<int>> urutanOp = {{0,1,2},{1,0,2},{1,2,0},{2,1,0}};

    solution solusi;
    solusi.angka = angka;
    solusi.op =  operasi;
    //pengecekan dengan 1 kelompok berisi 3 angka
    for(int i=0; i<size(urutan); i++) {
        x = calculate(angka[urutan[i][0]],angka[urutan[i][1]],operasi[urutanOp[i][0]]);
        if (urutan[i][2] > urutan[i][1]) {
            y = calculate(x,angka[urutan[i][2]],operasi[urutanOp[i][1]]);
            if(urutan[i][3] >urutan[i][2]){
                z = calculate(y,angka[urutan[i][3]],operasi[urutanOp[i][2]]);
            }
            else {
                z = calculate(angka[urutan[i][3]],y,operasi[urutanOp[i][2]]);
            }
        }
        else {
            y = calculate(angka[urutan[i][2]],x,operasi[urutanOp[i][1]]);
            if(urutan[i][3] >urutan[i][2]){
                z = calculate(y,angka[urutan[i][3]],operasi[urutanOp[i][2]]);
            }
            else {
                z = calculate(angka[urutan[i][3]],y,operasi[urutanOp[i][2]]);
            }
        }
        if (z==24) {
            solusi.tipe = i;
            result.push_back(solusi);
        }
        x = 0;
        y = 0;
        z = 0;
    }
    
    //pengecekan 2 kelompok berisi 2 angka
    x = calculate(angka[0],angka[1],operasi[0]);
    y = calculate(angka[2],angka[3],operasi[2]);
    z = calculate(x,y,operasi[1]);
    if (z == 24) {
        solusi.tipe = 4;
        result.push_back(solusi);
    }
    x = 0;
    y = 0;
    z = 0;
    return result;
}

bool isIn (vector<vector<int>> listbesar, vector<int> listangka){
    bool ada = false;
    int i = 0;
    while (!ada && i < size(listbesar)){
        int count = 0;
        for (int j=0; j<size(listbesar[i]); j++) {
            if (listangka[j] == listbesar[i][j]){
                count += 1;
            }
        }
        if (count == 4) {
            ada = true;
        }
        i++;
    }
    //ada = true or i >= size(listbesar)
    return ada;
}

vector<vector<int>> permutation (vector<int> listangka) {
    vector<vector<int>> result;
    for (int i=0; i<size(listangka); i++){
        for(int j=0; j<size(listangka); j++){
            if (j != i){
                for(int k=0; k<size(listangka); k++){
                    if (k != i && k != j ){
                        vector<int> listbaru;
                        listbaru.push_back(listangka[i]);
                        listbaru.push_back(listangka[j]);
                        listbaru.push_back(listangka[k]);
                        listbaru.push_back(listangka[6-i-j-k]);
                        if (!isIn(result,listbaru)) {
                            result.push_back(listbaru);
                        }
                    }
                }
            }
        }
    }
    return result;
}

vector<vector<string>> acakOp (vector<string> listOp) {
    vector<vector<string>> result;
    for (int i=0; i<size(listOp); i++){
        for(int j=0; j<size(listOp); j++){
            for(int k=0; k<size(listOp); k++){
                vector<string> listbaru;
                listbaru.push_back(listOp[i]);
                listbaru.push_back(listOp[j]);
                listbaru.push_back(listOp[k]);
                result.push_back(listbaru);
            }
        }
    }
    return result;
}

//mengubah string menjadi integer
vector<int> convertToInt (vector<string> kartu){    
    vector<int> kartuangka;
    for (int i=0; i<size(kartu); i++){
        if (kartu[i] == "A") {
            kartuangka.push_back(1);
        }
        else if(kartu[i] == "2"){
            kartuangka.push_back(2);
        }
        else if(kartu[i] == "3"){
            kartuangka.push_back(3);
        }
        else if(kartu[i] == "4"){
            kartuangka.push_back(4);
        }
        else if(kartu[i] == "5"){
            kartuangka.push_back(5);
        }
        else if(kartu[i] == "6"){
            kartuangka.push_back(6);
        }
        else if(kartu[i] == "7"){
            kartuangka.push_back(7);
        }
        else if(kartu[i] == "8"){
            kartuangka.push_back(8);
        }
        else if(kartu[i] == "9"){
            kartuangka.push_back(9);
        }
        else if(kartu[i] == "10"){
            kartuangka.push_back(10);
        }
        else if(kartu[i] == "J"){
            kartuangka.push_back(11);
        }
        else if(kartu[i] == "Q"){
            kartuangka.push_back(12);
        }
        else if(kartu[i] == "K"){
            kartuangka.push_back(13);
        }
    }
    return kartuangka;
}

//memisahkan kartu yang dimasukkan
vector<string> split (const string &stringawal) {
    vector<string> stringakhir;
    char delimeter = ' ';
    stringstream ss (stringawal);
    string item;

    while (getline (ss, item, delimeter)) {
        stringakhir.push_back(item);
    }
    return stringakhir;
}

//validasi input
bool validation (const vector<string> &kartu) {
    bool valid = true;
    int i;
    i = 0;
    while (i<size(kartu) && valid == true){
        if (kartu[i] != "A" && kartu[i] != "2" && kartu[i] != "3" && kartu[i] != "4" && kartu[i] != "5" && kartu[i] != "6" && kartu[i] != "7" && kartu[i] != "8" && kartu[i] != "9" && kartu[i] != "10" && kartu[i] != "J" && kartu[i] != "Q" && kartu[i] != "K"){
            valid = false;
        }
        i++;
    }
    return valid;
}

//input random
vector<int> random(){
    srand(time(NULL));
    string card[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    vector<string> karturand;
    vector<int> kartuint;
    for (int i = 0; i<4;i++){
        int idx = rand()%13;
        karturand.push_back(card[idx]);
    }
    for (int i=0;i<4;i++){
        cout << karturand[i] << " ";
    }
    cout << "\n";
    kartuint = convertToInt(karturand);
    //mekanisme random
    return kartuint;
}

//input dari pengguna
vector<int> self(){
    string cards;
    vector<string> splitted;
    vector<int> splittedInt;
    //mekanisme parse string dan validasi input
    do {
        cout << "Masukkan kartu anda: ";
        getline(cin,cards);
        splitted = split(cards);
        if (size(splitted) != 4 || !validation(splitted)){
            cout << "Masukan salah! Silakan ulangi lagi\n";
        }
        else {
            splittedInt = convertToInt(splitted);
        }
    } while(size(splitted) != 4 || !validation(splitted));
    return splittedInt;
}

//main program
int main() {
    int mech;
    vector<int> card ;
    vector<string> kartu;
    vector<string> operation = {"+","-","*","/"};
    int jumlahSolusi = 0;

    //mekanisme pemilihan kartu
    do {
        cout << "Pilih cara anda memasukkan kartu" << "\n";
        cout << "1. Random" << "\n";
        cout << "2. Input sendiri" << "\n";
        cin >> mech;
        if (mech != 2 && mech != 1){
            cout << "Masukkan anda salah! \n";
        }
    } while (mech != 2 && mech !=1);
    if (mech == 1) {
        card = random();
    }
    else if (mech == 2) {
        card = self();
    }

    //pengacakan angka
    vector<vector<int>> resultCard = permutation(card);

    //pengacakan operasi
    vector<vector<string>> op = acakOp(operation);

    vector<solution> solutionList;
    for (int i=0; i<size(resultCard); i++){
        for(int j=0; j<size(op); j++){
            vector<solution> solutionListTemp = evaluate(resultCard[i],op[j]);
            for(int k = 0; k<size(solutionListTemp);k++) {
                solutionList.push_back(solutionListTemp[k]);
            }
        }
    }
    cout << size(solutionList) << " solutions found!\n";
    displaySolution(solutionList);
    return 0;
}