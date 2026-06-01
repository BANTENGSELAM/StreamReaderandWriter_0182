#include <iostream>
#include <fstream> 
#include <string>
using namespace std;

int main ()
{
    // deklarasi variable baris dan NamaFile
    string baris, NamaFile;

    // membuat input untuk menangkap nama file
    cout << "Masukkan Nama file : ";
    cin >> NamaFile;

    // membuat file dalam mode menulis 
    ofstream outfile;
    // menunjuk ke sebuah nama file dengan eksistensi txt
    outfile.open(NamaFile + ".txt", ios::out);

    cout << ">= Menulis file, \'q\' untuk keluar" << endl;

    // looping untuk menulis isi file
    while (true)
    {

        cout << "- ";
    }
}