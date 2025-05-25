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

void TambahData(const char namaproduk[], int stokproduk, float hargaproduk);
void BacaFile();
void SimpanKeFile();
void HapusLinkedList();
void sortingNama();
void Bagi2List(dataproduk* kepala, dataproduk** setengahkanan, dataproduk** setengahkiri);
void MergeSort(dataproduk** kepalasorting);
void HapusProduk(const char hapusnamaproduk[]);
void TampilkanProduk();
void EditProduk(const char editproduk[]);
void CariDataLinear(const char carinama[]);
void bubbleSort();
void transaksi();

int main() {
    int pilihmenu, jumlahdata, stokproduk;
    char namaproduk[100];
    float hargaproduk;
    BacaFile();
    do {
        cout << "========= MENU =========" << endl;
        cout << "1. INPUT DATA PRODUK" << endl;
        cout << "2. HAPUS DATA PRODUK" << endl;
        cout << "3. EDIT DATA PRODUK" << endl;
        cout << "4. TAMPILKAN DATA PRODUK" << endl;
        cout << "5. URUTKAN DATA PRODUK" << endl;
        cout << "6. CARI DATA PRODUK" << endl;
        cout << "7. TRANSAKSI" << endl;
        cout << "8. KELUAR DARI PROGRAM" << endl;
        cout << "========================" << endl;
        cout << "Pilih menu: "; cin >> pilihmenu;
        cin.ignore();
        system("cls");

        switch (pilihmenu) {
            case 1:
                    cout << "Masukkan jumlah data produk yang ingin diinput: "; cin >> jumlahdata;
                    cin.ignore();
                    for (int i = 0; i < jumlahdata; i++) {
                        cout << "Data produk ke-" << (i + 1) << endl;
                        cout << "   Nama produk : "; cin.getline(namaproduk, 100);
                        cout << "   Stok produk : "; cin >> stokproduk;
                        cout << "   Harga produk: "; cin >> hargaproduk;
                        cin.ignore();
                        if (stokproduk < 0 || hargaproduk < 0) {
                            cout << "Input tidak boleh negatif!\n";
                            continue;
                        }
                        TambahData(namaproduk, stokproduk, hargaproduk);
                        cout << "\n";
                    }
                    SimpanKeFile();
                    system("pause");
                    system("cls");
                break;
            case 2: 
                    TampilkanProduk();
                    char hapusnamaproduk[100];
                    cout << "Pilih nama produk yang ingin dihapus : "; cin.getline(hapusnamaproduk, 100);
                    HapusProduk(hapusnamaproduk);
                    SimpanKeFile();
                    system("pause");
                    system("cls");
                break;
            case 3: {
                    TampilkanProduk();
                    char editproduk[100];
                    cout << "\nMasukkan nama produk yang ingin diedit: "; cin.getline(editproduk, 100);
                    EditProduk(editproduk);
                    system("pause");
                    system("cls");
                break;
                }
            case 4: 
                    TampilkanProduk();
                    system("pause");
                    system("cls");
                break;
            case 5:
                    int pilihSort;
                    cout << "==========================\n";
                    cout << "Menu Pengurutan\n";
                    cout << "==========================\n";
                    cout << "1. BERDASARKAN ABJAD (A-Z)\n";
                    cout << "2. BERDASARKAN HARGA\n";
                    cout << "==========================\n";
                    cout << "Pilih menu: "; cin >> pilihSort;
                    cout << " ";
                    if (pilihSort == 1) { 
                        
                        sortingNama();
                        SimpanKeFile();
                        TampilkanProduk();
                        system("pause");
                        system("cls");
                    } else if (pilihSort == 2) { 
                        
                        bubbleSort();
                        SimpanKeFile();
                        cout << "Data berhasil diurutkan berdasarkan harga\n";
                        TampilkanProduk();
                        system("pause");
                        system("cls");
                    } else {
                        cout << "Pilihan tidak valid!" << endl;
                    }
                break;
            case 6:  {
                    char carinama[100];
                    cout << "Masukkan nama produk yang ingin dicari: "; cin.getline(carinama, 100);
                    CariDataLinear(carinama);
                    system("pause");
                    system("cls");
                    break;
                }
            case 7:
                    transaksi();
                    system("pause");
                    system("cls");
                    break;
            case 8:
                    cout << "Terima kasih telah menggunakan program ini." << endl;
                    HapusLinkedList();
                return 0;

            default:
                    cout << "Menu tidak tersedia. Silakan pilih kembali." << endl;
                break;
        }
    } while (pilihmenu != 8);

    return 0;
}

void TambahData(const char namaproduk[], int stokproduk, float hargaproduk) {
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

void HapusLinkedList() {
    dataproduk* hapus = kepala;
    while (hapus != NULL) {
        dataproduk* sementara = hapus;
        hapus = hapus->next;
        delete sementara;
    }
    kepala = ekor = NULL;
}

void SimpanKeFile() {
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
    } fclose(databarang);
}

void BacaFile() {
    HapusLinkedList();
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
        TambahData(namaproduk, stokproduk, hargaproduk);
    } fclose(databarang);
}

void sortingNama() {
    if (kepala == NULL || kepala->next == NULL) {
        cout << "Tidak ada cukup data untuk diurutkan.\n";
        return;
    }
    MergeSort(&kepala);
    cout << "Data berhasil diurutkan berdasarkan nama (A-Z).\n";
    SimpanKeFile();
}

void HapusProduk(const char hapusnamaproduk[]) {
    if (kepala == NULL) {
        cout << "Linked List kosong!\n";
        return;
    }
    if (strcmp(kepala->namaproduk, hapusnamaproduk) == 0) {
        dataproduk* nodehapus = kepala;
        kepala = kepala->next;
        delete nodehapus;
        cout << "Node dengan nama '" << hapusnamaproduk << "' berhasil dihapus dari awal.\n";
        return;
    }
    dataproduk* nodebantu = kepala;
    while (nodebantu->next != NULL && strcmp(nodebantu->next->namaproduk, hapusnamaproduk) != 0) {
        nodebantu = nodebantu->next;
    }
    if (nodebantu->next == NULL) {
        cout << "Node dengan nama '" << hapusnamaproduk << "' tidak ditemukan.\n";
    } else {
        dataproduk* nodehapus = nodebantu->next;
        nodebantu->next = nodehapus->next;
        if (nodehapus == ekor) {
            ekor = nodebantu;
        }
        delete nodehapus;
        cout << "Node dengan nama '" << hapusnamaproduk << "' berhasil dihapus.\n";
    }
}

void TampilkanProduk() {
        
    if (kepala == NULL) {
        cout << "DATA PRODUK SAAT INI KOSONG, INPUT TERLEBIH DAHULU." << endl;
        system("pause");
        system("cls");
        return;
    }
    int nomorurut = 1;
    dataproduk* nodetampilkandata = kepala;
    cout << "DAFTAR BARANG YANG TERSEDIA DI TOKO ABCD\n";
    cout << setfill('=') << setw(76) << "=" << setfill(' ') << endl;
    cout << left << setw(5) << "NO"
    << setw(2) << "|"
    << setw(40) << "NAMA PRODUK"
    << setw(2) << "|"
    << setw(8) << "STOK"
    << setw(4) << "|"
    << setw(14) << "HARGA" 
    << setw(6) << "|"<< endl;
    cout << setfill('=') << setw(76) << "=" << setfill(' ') << endl;
    while (nodetampilkandata != nullptr) {
        cout << left << setw(5) << nomorurut++
            << setw(2) << "|"
            << setw(40) << nodetampilkandata->namaproduk
            << setw(2) << "|"
            << setw(8) << nodetampilkandata->stokproduk
            << setw(4) << "| Rp."
            << setw(13) << nodetampilkandata->hargaproduk 
            << setw(6) << "|"<< endl;

        nodetampilkandata = nodetampilkandata->next;
    }
    cout << setfill('=') << setw(76) << "=" << setfill(' ') << endl;
}

void EditProduk(const char editproduk[]){
    dataproduk* nodeedit = kepala;
    while (nodeedit != NULL && strcmp(nodeedit->namaproduk, editproduk) != 0) {
        nodeedit = nodeedit->next;
    }
    if (nodeedit == NULL) {
        cout << "Produk dengan nama '" << editproduk << "' tidak ditemukan.\n";
    } else {
        char namabaru[100];
        cout << "Data ditemukan. Masukkan data baru.\n";
        cout << "   Nama produk baru (kosongkan jika tidak ingin diubah): "; cin.getline(namabaru, 100);
        if (namabaru[0] != '\0') {
            strcpy(nodeedit->namaproduk, namabaru);
        }
        cout << "   Stok produk baru: "; cin >> nodeedit->stokproduk;
        cout << "   Harga produk baru: "; cin >> nodeedit->hargaproduk;
        cin.ignore();
        cout << "Data berhasil diedit.\n";
        SimpanKeFile();
    }
}

dataproduk* Pengurutan(dataproduk* setengahkanan, dataproduk* setengahkiri) {
    if (setengahkanan == NULL) return setengahkiri;
    if (setengahkiri == NULL) return setengahkanan;
    dataproduk* hasil = NULL;
    if (strcmp(setengahkanan->namaproduk, setengahkiri->namaproduk) <= 0) {
        hasil = setengahkanan;
        hasil->next = Pengurutan(setengahkanan->next, setengahkiri);  
    } else {
        hasil = setengahkiri;
        hasil->next = Pengurutan(setengahkanan, setengahkiri->next);
    }
    return hasil;
}

void Bagi2List(dataproduk* kepala, dataproduk** setengahkanan, dataproduk** setengahkiri) {
    dataproduk *pelan, *cepat;
    if (kepala == NULL || kepala->next == NULL) {
        *setengahkanan = kepala;
        *setengahkiri = NULL;
    } else {
        pelan = kepala;
        cepat = kepala->next;
        while (cepat != NULL) {
            cepat = cepat->next;
            if (cepat != NULL) {
                pelan = pelan->next;
                cepat = cepat->next;
            }
        }
        *setengahkanan = kepala;
        *setengahkiri = pelan->next;
        pelan->next = NULL;
    }
}

void MergeSort(dataproduk** kepalasorting) {
    dataproduk *kepala = *kepalasorting;
    dataproduk *setengahkanan;
    dataproduk *setengahkiri;
    if (kepala == NULL || kepala->next == NULL) {
        return;
    }
    Bagi2List(kepala, &setengahkanan, &setengahkiri);
    MergeSort(&setengahkanan);
    MergeSort(&setengahkiri);
    *kepalasorting = Pengurutan(setengahkanan, setengahkiri);
}

void bubbleSort() {
    if (kepala == NULL || kepala->next == NULL){ 
    return;
    }
    bool swapped;
    dataproduk *ptr1;
    dataproduk *lptr = NULL;
    int pilihsort;
    cout << "----------------------------------------------------------" << endl;
    cout << "MENU PENGURUTAN HARGA" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "1. DARI YANG PALING MURAH KE YANG PALING MAHAL (ASCENDING)" << endl;
    cout << "2. DARI YANG PALING MAHAL KE YANG PALING MURAH (DESCENDING)" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Pilih metode: "; cin >> pilihsort;
    switch (pilihsort) {
    case 1:
        do {
        swapped = false;
        ptr1 = kepala;

        while (ptr1->next != lptr) {
            if (ptr1->hargaproduk > ptr1->next->hargaproduk) {
                swap(ptr1->namaproduk, ptr1->next->namaproduk);
                swap(ptr1->stokproduk, ptr1->next->stokproduk);
                swap(ptr1->hargaproduk, ptr1->next->hargaproduk);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
        break;
    case 2:
        do {
        swapped = false;
        ptr1 = kepala;

        while (ptr1->next != lptr) {
            if (ptr1->hargaproduk < ptr1->next->hargaproduk) {
                swap(ptr1->namaproduk, ptr1->next->namaproduk);
                swap(ptr1->stokproduk, ptr1->next->stokproduk);
                swap(ptr1->hargaproduk, ptr1->next->hargaproduk);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
        break;
    default:
        cout << "Pilihan menu sort tidak valid." << endl;
        break;
    }
    
}

void CariDataLinear(const char carinama[]) {
    
    dataproduk* Nodecari = kepala;
    bool ditemukan = false;

    while (Nodecari != NULL) {
        if (strcmp(Nodecari->namaproduk, carinama) == 0) {
            cout << "Produk ditemukan:\n";
            cout << "   Nama Produk  : " << Nodecari->namaproduk << endl;
            cout << "   Stok Produk  : " << Nodecari->stokproduk << endl;
            cout << "   Harga Produk : " << Nodecari->hargaproduk << endl;
            ditemukan = true;
            break;
        }
        Nodecari = Nodecari->next;
    }

    if (!ditemukan) {
        cout << "Produk dengan nama '" << carinama << "' tidak ditemukan.\n";
    }
}

void transaksi() {
    if (kepala == NULL) {
        cout << "\n=====================================\n";
        cout << "  Tidak ada produk tersedia untuk transaksi.\n";
        cout << "=====================================\n";
        return;
    }

    char transNama[100];
    int jumlahTrans;
    float total = 0;
    bool transLagi = true;

    struct Transaksi {
        char nama[100];
        int jumlah;
        float harga;
    } keranjang[100];

    int idx = 0;

    while (transLagi) {
        cout << "\n========== Daftar Produk ==========\n";
        TampilkanProduk();
        cout << setfill('=') << setw(69) << "=" << setfill(' ') << endl;

        cout << "\nMasukkan nama produk yang ingin dibeli: ";
        cin.getline(transNama, 100);

        dataproduk* produk = kepala;
        while (produk != NULL && strcmp(produk->namaproduk, transNama) != 0) {
            produk = produk->next;
        }

        if (produk == NULL) {
            cout << "\n>> Produk tidak ditemukan. Coba lagi.\n";
        } else {
            cout << "Masukkan jumlah yang ingin dibeli: ";
            cin >> jumlahTrans;
            cin.ignore();

            if (jumlahTrans > produk->stokproduk) {
                cout << "\n>> Stok tidak mencukupi. Stok tersedia: " << produk->stokproduk << "\n";
            } else if (jumlahTrans <= 0) {
                cout << "\n>> Jumlah produk tidak valid. Harus lebih dari 0.\n";
            } else {
                produk->stokproduk -= jumlahTrans;
                strcpy(keranjang[idx].nama, produk->namaproduk);
                keranjang[idx].jumlah = jumlahTrans;
                keranjang[idx].harga = produk->hargaproduk;
                total += jumlahTrans * produk->hargaproduk;
                idx++;
                cout << "\n>> Produk berhasil ditambahkan ke keranjang.\n";
            }
        }

        char pilihan;
        cout << "\nBeli produk lain? (y/n): ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 'n' || pilihan == 'N') {
            transLagi = false;
        }
    }

    if (idx == 0) {
        cout << "\n>> Tidak ada transaksi yang dilakukan.\n";
        return;
    }

    SimpanKeFile();

    cout << "\n=====================================\n";
    cout << "               NOTA                 \n";
    cout << "=====================================\n";
    for (int i = 0; i < idx; i++) {
        cout << left << setw(20) << keranjang[i].nama 
             << "x" << setw(3) << keranjang[i].jumlah 
             << "= Rp" << fixed << setprecision(2) 
             << (keranjang[i].jumlah * keranjang[i].harga) << "\n";
    }
    cout << "-------------------------------------\n";
    cout << "TOTAL:\t\t\tRp" << fixed << setprecision(2) << total << "\n";
    cout << "=====================================\n";
}
