#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <exception>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase[0] = "Televisi LED";
        etalase[1] = "Kulkas 2 Pintu";
        etalase[2] = "Mesin Cuci";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            throw "Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!";
        }
    }
};


void tampilkanGudang() {
    ifstream infile;
    infile.open("gudang.txt");
    string baris;
    int nomor = 1;

    cout << "\n=== DAFTAR BARANG DI GUDANG ===" << endl;
    if (infile.is_open()) {
        bool adaBarang = false;
        while (getline(infile, baris)) {
            if (!baris.empty()) {
                cout << nomor << ". " << baris << endl;
                nomor++;
                adaBarang = true;
            }
        }
        if (!adaBarang) {
            cout << "[Gudang Kosong]" << endl;
        }
        infile.close();
    } else {
        cout << "[Belum ada data gudang.txt / File belum dibuat]" << endl;
    }
    cout << "===============================" << endl;
}

int main() {
    TokoElektronik toko;
    int pilihan;
    string namaBarang;

    do {
        tampilkanGudang();

        cout << "\n=== MENU MANAJEMEN GIBRAN JAYA ===" << endl;
        cout << "1. Tambah Barang Baru (Create)" << endl;
        cout << "2. Ubah Data Barang (Update)" << endl;
        cout << "3. Hapus Data Barang (Delete)" << endl;
        cout << "4. Jalankan Simulasi Etalase (Exception Handling)" << endl;
        cout << "5. Keluar Aplikasi" << endl;
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;
        cin.ignore(); 

        if (pilihan == 1) {
           
            ofstream outfile;
           
            outfile.open("gudang.txt", ios::app); 
            
            cout << "Masukkan nama barang baru: ";
            getline(cin, namaBarang);
            
            if (!namaBarang.empty()) {
                outfile << namaBarang << endl;
                cout << "Barang berhasil ditambahkan!" << endl;
            }
            outfile.close();
        }
        else if (pilihan == 2) {
            
            ifstream infile("gudang.txt");
            ofstream tempfile("temp.txt"); 
            
            int targetNo, currentNo = 1;
            string baris;
            bool ditemukan = false;

            cout << "Masukkan nomor urut barang yang ingin diuabh: ";
            cin >> targetNo;
            cin.ignore();

            if (infile.is_open()) {
                while (getline(infile, baris)) {
                    if (currentNo == targetNo) {
                        cout << "Data lama: " << baris << endl;
                        cout << "Masukkan data baru: ";
                        getline(cin, namaBarang);
                        tempfile << namaBarang << endl;
                        ditemukan = true;
                    } else {
                        tempfile << baris << endl;
                    }
                    currentNo++;
                }
                infile.close();
                tempfile.close();

                
                remove("gudang.txt");
                rename("temp.txt", "gudang.txt");

                if (ditemukan) cout << "Barang berhasil diperbarui!" << endl;
                else cout << "Nomor barang tidak ditemukan!" << endl;
            } else {
                cout << "Gagal membuka file gudang" << endl;
            }
        }
        else if (pilihan == 3) {
            
            ifstream infile("gudang.txt");
            ofstream tempfile("temp.txt");
            
            int targetNo, currentNo = 1;
            string baris;
            bool ditemukan = false;

            cout << "Masukkan nomor urut barang yang ingin dihapus: ";
            cin >> targetNo;
            cin.ignore();

            if (infile.is_open()) {
                while (getline(infile, baris)) {
                    if (currentNo == targetNo) {
                        cout << "Menghapus barang: " << baris << endl;
                        ditemukan = true; 
                    } else {
                        tempfile << baris << endl;
                    }
                    currentNo++;
                }
                infile.close();
                tempfile.close();

                remove("gudang.txt");
                rename("temp.txt", "gudang.txt");

                if (ditemukan) cout << "Barang berhasil dihapus!" << endl;
                else cout << "Nomro barang tidak ditemukan!" << endl;
            } else {
                cout << "Gagal membuka file gudang!" << endl;
            }
        }
        else if (pilihan == 4) {
            
            cout << "\n--- MEMULAI SIMULASI ETALASE ---" << endl;

            
            cout << "Skenario 1: Mengambil barang di rak indeks ke-1..." << endl;
            try {
                string produk = toko.ambilProduk(1);
                cout << "Hasil: Berhasil mengambil -> " << produk << endl;
            }
            catch (const string& pesanError) {
                cout << "Hasil: " << pesanError << endl;
            }

            cout << endl;

            
            cout << "Skenario 2: Mengambil barang di rak indeks ke-5..." << endl;
            try {
                string produk = toko.ambilProduk(5);
                cout << "Hasil: Berhasil mengambil -> " << produk << endl;
            }
            catch (const string& pesanError) {
                
                cout << "Hasil: " << pesanError << endl;
            }
            cout << "--------------------------------" << endl;
        }
        else if (pilihan == 5) {
            cout << "Terima kasih telah menggunakan sistem Gibran Jaya!" << endl;
        }
        else {
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 5);

    return 0;
}