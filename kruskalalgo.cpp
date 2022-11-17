#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

    int cities[26][26];
    int build [26][26];
    int destroy[26][26];
    int col = 0;
    int row = 0;
    int cost = 0;

void printVector(vector<int> pathData) {
    for (int i = 0; i<(int)pathData.size(); i++) {
        cout << pathData[i] << " ";
    }
    cout << endl;
}

void printPath() {
    for (int j = 0; j < row; j++) {
        for (int k = 0; k < col; k++) {
            cout << cities[j][k] << " ";
        }
        cout << endl;
    }
}   

void bubbleSort(vector<int> &array,int currentRow, int dataDB[][26]) {
    //cout << "array ke 0 BEFORE : " << array[0] << endl;
    for (int i=0; i<(int)array.size()-1; i++) {
        for (int j=0; j<(int)array.size()-i-1; j++) {
            if (dataDB[currentRow][array[j]] > dataDB[currentRow][array[j+1]]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] =  temp;
            }
        }
    } //cout << "array ke 0 AFTER : " << array[0] << endl;
}
void bubbleSortDestroy(vector<int> &array,int currentColumn, int dataDB[][26]) {
    for (int i=0; i<(int)array.size()-1; i++) {
        for (int j=0; j<(int)array.size()-i-1; j++) {
            if (dataDB[array[j]][currentColumn] > dataDB[array[j+1]][currentColumn]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] =  temp;
            }
        }
    }
}

void destroyPath() {
    for (int i=0; i<row; i++) {
        vector<int> pathData; 
        for (int j=0; j<col; j++) {
            if (cities[i][j] == 1) {
                pathData.push_back(j);
            }
        }
        if (pathData.size() > 1) {
            bubbleSort(pathData,i,destroy);
            cout << "pathData index ke NOL" << pathData[0] << endl;
            cout << "pathData index terakhir, panjang data dikurang satu" << pathData[(int)pathData.size()-1] << endl;

            int count_Destroy = 0;
            for (int k=0; k<(int)pathData.size() && count_Destroy < (int)pathData.size()-1; k++) {
                vector<int> commonDestroy;
                for (int m=0; m<row; m++) {
                    if (cities[m][pathData[k]] == 1) {
                        commonDestroy.push_back(m);
                    }
                }
                bubbleSortDestroy(commonDestroy,pathData[k],destroy);
                for (int o=0; o<(int)commonDestroy.size(); o++) {
                    int count =0;
                    for (int n = 0; n<col; n++) {
                        if (cities[commonDestroy[o]][n] == 1) {
                            count++;
                        }
                    }
                    if (count < 2) {
                        continue;
                    }
                    count = 0;
                    for (int l = 0; l<col; l++) {
                        if (cities[pathData.at(k)][l] == 1) {
                            //cout << "disini" << endl;
                            count++;
                        }
                    }
                    if (count > 1) {
                        cout << "commonDestroy ke o" << commonDestroy[o] << endl;
                        cout << "pathData ke K" << pathData[k] << endl;
                        cities[commonDestroy[o]][pathData.at(k)] = 0;
                        cities[pathData.at(k)][commonDestroy[o]] = 0;
                        cost += destroy[commonDestroy[o]][pathData.at(k)];
                        count_Destroy++;
                        break;
                    }
                }
            }
        }
    }
    cout << "Destroy Cost: " << cost << endl;
}


void buildPath() {
    for (int i=0; i<row; i++) {
        vector<int> buildData;
        for (int j=0; j<col; j++) {
            if (cities[i][j] == 0 && i != j) {
                buildData.push_back(j);
            }
        }
        bubbleSort(buildData,i,build);
        for (int k=0; k<(int)buildData.size(); k++) {
            bool built = false;
            int l = 0;
            for (l=0; l<row; l++) {
                if (cities[l][buildData[k]] == 1) {
                    built = true;
                    break;
                }
            }
            bool builtPath = false;
            if (built) {
                if (cities[i][l] == 0) {
                    bool check = true;
                    vector<int> commonPath;
                    commonPath.push_back(i);
                    // int array[26];
                    // for (int m=0; m<col; m++) {
                    //     array[m]=cities[i][m];
                    // }
                    int indexLine = i;
                    //bool allowBuild = true;
                    while (check) {
                        int n = 0;
                        for (n=0; n<col; n++) {
                            if (cities[indexLine][n] == 1) {
                                if (!count(commonPath.begin(),commonPath.end(),n)) {
                                    // cout << "indexLine : " << indexLine << endl;
                                    // cout << "nilai n: " << n << endl;
                                    // cout << "Sesuatu 1" << endl;
                                    indexLine = n;
                                    commonPath.push_back(n);
                                    // for (int o=0; o<col; o++) {
                                    //     array[o] = cities[n][o];
                                    // }
                                    if (n == l) {
                                        //cout << "Sesuatu 2" << endl;
                                        check = false;
                                        //allowBuild = false;
                                        break;
                                    }
                                    break;
                                }
                                //cout << "AFTER indexLine : " << indexLine << endl;
                                //cout << "AFTER nilai n: " << n << endl;
                            }
                        }
                        if (n == col) {
                                check = false;
                                cities[i][buildData[k]] = 1;
                                cities[buildData[k]][i] = 1;
                                cost += build[i][buildData[k]];
                                // cout << "i-if: " << i << endl;
                                // cout << "buildData[k]" << buildData[k] << endl;
                                builtPath = true;
                            }
                        //cout << "APAKAH FOR LOOP PERNAH SELESAI?" << endl;
                    }
                }
            }
            else {
                cities[i][buildData[k]] = 1;
                cities[buildData[k]][i] = 1;
                cost += build[i][buildData[k]];
                // cout << "i-else: " << i << endl;
                // cout << "buildData[k]" << buildData[k] << endl;
                builtPath = true;
            }
            if (builtPath) {
                break;
            }
        }
    }
    cout << "Build Cost: " << cost << endl;
}

int main() {
    string a;
    getline(cin,a);
    istringstream stringVar(a);
    string output = "";
    string word = "";
    int counter = 0;
    while (stringVar >> output) {
        col = 0;
        row = 0;
        //cout << output << endl;
        for (int i=0; output[i] != '\0'; i++) {
            if (counter == 0) {
                //cout << output[i] << endl;
                if (output[i] == ',') {
                    row++;
                    col = 0;
                }
                else {
                    int data = output[i] - '0';
                    cities[row][col] = data;
                    col++;
                }
            }
            else if (counter == 1) {
                //cout << output[i] << endl;
                if (output[i] == ',') {
                    row++;
                    col = 0;
                }
                else {
                    if (output[i] <= 'Z') {
                        int priceB = output[i] - 'A';
                        build[row][col] = priceB;
                    }
                    else if (output[i] >= 'a') {
                        int priceB = output[i] - 'A'-6;
                        build[row][col] = priceB;
                    }
                    col++;
                }
            }
            else if (counter == 2) {
                //cout << output[i] << endl;
                if (output[i] == ',') {
                    row++;
                    col = 0;
                }
                else {
                    if (output[i] <= 'Z') {
                        int priceD = output[i] - 'A';
                        destroy[row][col] = priceD;
                    }
                    else if (output[i] >= 'a') {
                        int priceD = output[i] - 'A'-6;
                        destroy[row][col] = priceD;
                    }
                    col++;
                }
            }
        }
        row++;
        counter++;
    }
    cout << "Before Destroy" << endl;
    printPath();
    destroyPath();
    cout << "After Destroy" << endl;
    printPath();

    cout << "Before Build" << endl;
    printPath();
    buildPath();
    cout << "After Build" << endl;
    printPath();
    cout << cost << endl;
}
