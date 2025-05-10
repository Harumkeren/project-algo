#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

struct dataproduk {
    char namaproduk[100];
    int stokproduk;
    float hargaproduk;
    dataproduk* next;
};

dataproduk *kepala = NULL, *ekor = NULL;
FILE* databarang;

void tambahadataLL(const char namaproduk[], int stokproduk, float hargaproduk);
void membacafile();
void simpanKeFile();
void hapusLinkedList();

int main() {
    int pilihmenu, jumlahdata;
    char namaproduk[100];
    int stokproduk;
    float hargaproduk;

    do {
        cout << "===== MENU =====" << endl;
        cout << "1. INPUT DATA PRODUK" << endl;
        cout << "2. HAPUS DATA PRODUK" << endl;
        cout << "3. EDIT DATA PRODUK" << endl;
        cout << "4. TAMPILKAN DATA PRODUK" << endl;
        cout << "5. URUTKAN DATA PRODUK" << endl;
        cout << "6. CARI DATA PRODUK" << endl;
        cout << "7. KELUAR DARI PROGRAM" << endl;
        cout << "Pilih menu: ";
        cin >> pilihmenu;
        cin.ignore();
        system("cls");

        switch (pilihmenu) {
            case 1:
                membacafile();
                cout << "Masukkan jumlah data produk yang ingin diinput: ";
                cin >> jumlahdata;
                cin.ignore();
                for (int i = 0; i < jumlahdata; i++) {
                    cout << "Data produk ke-" << (i + 1) << endl;
                    cout << "   Nama produk : "; cin.getline(namaproduk, 100);
                    cout << "   Stok produk : "; cin >> stokproduk;
                    cout << "   Harga produk: "; cin >> hargaproduk;
                    cin.ignore();
                    tambahadataLL(namaproduk, stokproduk, hargaproduk);
                    cout << "\n";
                }
                simpanKeFile();
                break;
            case 4: {
                membacafile();
                if (kepala == NULL) {
                    cout << "DATA PRODUK SAAT INI KOSONG, INPUT TERLEBIH DAHULU." << endl;
                    system("pause");
                    system("cls");
                    break;
                }
                int nomorurut = 1;
                dataproduk* tampil = kepala;
                while (tampil != NULL) {
                    cout << nomorurut++ << ". Nama produk   : " << tampil->namaproduk << endl;
                    cout << "   Stok produk   : " << tampil->stokproduk << endl;
                    cout << "   Harga produk  : " << fixed << setprecision(2) << tampil->hargaproduk << endl;
                    tampil = tampil->next;
                }
                system("pause");
                system("cls");
                break;
            }

            case 7:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                hapusLinkedList();
                return 0;

            default:
                cout << "Menu tidak tersedia. Silakan pilih kembali." << endl;
                break;
        }
    } while (pilihmenu != 0);

    return 0;
}

void tambahadataLL(const char namaproduk[], int stokproduk, float hargaproduk) {
    dataproduk* NodeBaru = new dataproduk();
    strcpy(NodeBaru->namaproduk, namaproduk);
    NodeBaru->stokproduk = stokproduk;
    NodeBaru->hargaproduk = hargaproduk;
    NodeBaru->next = NULL;
    if (kepala == NULL) {
        kepala = ekor = NodeBaru;
    } else {
        ekor->next = NodeBaru;
        ekor = NodeBaru;
    }
}

void hapusLinkedList() {
    dataproduk* hapus = kepala;
    while (hapus != NULL) {
        dataproduk* sementara = hapus;
        hapus = hapus->next;
        delete sementara;
    }
    kepala = ekor = NULL;
}

void simpanKeFile() {
    databarang = fopen("Databarangtoko.dat", "wb");
    if (databarang == NULL) {
        cout << "Gagal menyimpan data ke file." << endl;
        return;
    }
    dataproduk* simpan = kepala;
    while (simpan != NULL) {
        fwrite(simpan->namaproduk, sizeof(char), 100, databarang);
        fwrite(&simpan->stokproduk, sizeof(int), 1, databarang);
        fwrite(&simpan->hargaproduk, sizeof(float), 1, databarang);
        simpan = simpan->next;
    }
    fclose(databarang);
}

void membacafile() {
    hapusLinkedList();
    char namaproduk[100];
    int stokproduk;
    float hargaproduk;
    databarang = fopen("Databarangtoko.dat", "rb");
    if (databarang == NULL) {
        databarang = fopen("Databarangtoko.dat", "wb");
        if (databarang != NULL) fclose(databarang);
        return;
    }
    while (fread(namaproduk, sizeof(char), 100, databarang) == 100 &&
           fread(&stokproduk, sizeof(int), 1, databarang) == 1 &&
           fread(&hargaproduk, sizeof(float), 1, databarang) == 1) {
        tambahadataLL(namaproduk, stokproduk, hargaproduk);
    }
    fclose(databarang);
}
