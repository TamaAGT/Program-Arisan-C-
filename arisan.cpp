#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std; 

// Program Arisan Ibu-Ibu RT

class Queue{
private:
    int depan; 
    int belakang;
    int arr[100];

public:
    // Konstruktor untuk queue
    Queue(){
        depan = -1; 
        belakang = -1;
        for(int i = 0; i < 100; i++){
            arr[i] = 0;
        }
    }

    bool kosong(){
        if(depan == -1 && belakang == -1){
            return true; 
        } else {
        return false;
        }
    }

    bool penuh(){
        if(belakang == sizeof(arr) - 1){
            return true; 
        }
        return false; 
    }

    void enqueue(int val){
        if(penuh()){
            cout << "Data Penuh" << endl;
            return; 
        }
        else if(kosong()){
            depan = 0;
            belakang = 0;
            arr[belakang] = val;
        }
        else {
            belakang++;
            arr[belakang] = val; 
        }
    }

    int dequeue(){
        int x; 
        
        if(kosong()){
            cout << "Data masih kosong" << endl; 
            return 0;
        }
        else if(depan == belakang){
            x = arr[depan];
            arr[depan] = 0;
            depan = -1; 
            belakang = -1;
        }
        else {
            x = arr[depan];
            depan++;
        }
        return x;
    }

    int hitung(){
        return (belakang - depan + 1);
    }

    void cetak(){
        for(int i = 0; i < sizeof(arr); i++){
            cout << arr[i] << endl;
        }
    }
};

class Node{
public:
    int indeks;
    string nama; 
    string alamat;
    int jml_ikut;
    Node* next; 
};

// Variabel global untuk indeks anggota
int no_indeks = 0;

void insertAnggota(Node** head_ref, string nama, string alamat, int jml_ikut){
    no_indeks++;

    Node* newNode = new Node();
    Node* temp = *head_ref; 

    newNode->indeks = no_indeks;
    newNode->nama = nama; 
    newNode->alamat = alamat; 
    newNode->jml_ikut = jml_ikut;
    newNode->next = NULL;

    // Apabila nilai dari node kosong
    if(*head_ref == NULL){
        *head_ref = newNode; 
        return;
    }   
    // Iterasi ke node paling belakang
    while(temp->next != NULL){
        temp = temp->next;
    }
    // Menyisipkan node pada baris paling belakang
    temp->next = newNode;

    return; 

}

void hapusNode(Node** head_ref, int id){
    Node* temp = *head_ref; 
    Node* prev = NULL; 
    // Apabila data ada pada ujung Node
    if(temp != NULL && temp->indeks == id){
        *head_ref = temp->next; 
        delete temp;
        return;
    }
    // Menelusuri linked list
    while(temp != NULL && temp->indeks != id){
        prev = temp;
        temp = temp->next; 
    }
    // Jika data tidak ditemukan
    if(temp == NULL){
        cout << "Data tidak ditemukan" << endl;
        return; 
    }
    prev->next = temp->next;
    //hapus memori
    delete temp; 
}

int hitung(Node* head_ref){
    int jumlah = 0;

    while(head_ref != NULL){
        if(head_ref->jml_ikut > 0){
            jumlah++;
        }
        head_ref = head_ref->next; 
    }
    return jumlah;
}

bool konfirmasi(Node* head_ref, int id, bool &option){
    char input;

    while(head_ref != NULL){
        if(head_ref->indeks == id){
            cout << "Yakin ingin menghapus anggota?" << endl;
            cout << "+---------+-----------------------------+---------------------------------------+--------------+"<< endl;
	        cout << "|" << setw(5) << "ID" << setw(5) << "|" << setw(15) << "NAMA" << setw(15) << "|" 
             << setw(20) << "ALAMAT" << setw(20) << "|" << setw(9) << "JATAH" << setw(6) << "|" << endl;
	        cout << "+---------+-----------------------------+---------------------------------------+---------------" << endl;
            cout << "|" << setw(5) << head_ref->indeks << setw(5) << "|" << setw(29) <<  head_ref->nama << "|" << setw(39) << head_ref->alamat<< "|" << setw(7) << head_ref->jml_ikut << setw(8) << "|" << endl;
            cout << "+---------+-----------------------------+---------------------------------------+---------------" << endl;
            cout << "Input (Y/T) : ";
            cin >> input;
            if(input == 'y' || input == 'Y'){
                option = true;
                return option; 
            }
        }
        head_ref = head_ref->next; 
    }
    option = false; 
    return option; 
}

void daftarAnggota(Node* head_ref){
        cout << "+---------+-----------------------------+---------------------------------------+--------------+"<< endl;
        cout << "|" << setw(5) << "ID" << setw(5) << "|" << setw(15) << "NAMA" << setw(15) << "|" 
        << setw(20) << "ALAMAT" << setw(20) << "|" << setw(9) << "JATAH" << setw(6) << "|" << endl;
        cout << "+---------+-----------------------------+---------------------------------------+---------------" << endl;
   
    while(head_ref != NULL){
       cout << "|" << setw(5) << head_ref->indeks << setw(5) << "|" << setw(29) <<  head_ref->nama << "|" << setw(39) << head_ref->alamat<< "|" << setw(7) << head_ref->jml_ikut << setw(8) << "|" << endl;
       cout << "+---------+-----------------------------+---------------------------------------+---------------" << endl;
        head_ref = head_ref->next; 
    }
}

int acakPemenang(Node* anggota){
    int max, min = 1, random;
    // Membuat agar var max sesuati dengan jumlah anggota
    max = hitung(anggota);
    // Memastikan program memberikan nilai acak berbeda setiap program diajalankan
    srand(time(NULL));
    // Menagacak indeks yang akan keluar
    random = rand() % max + min;
    return random;
}

void pemenang(Node* anggota, int &indeks, int random){
    int iterasi = 0;

    while(anggota != NULL){ 
        if(anggota->jml_ikut > 0){
            iterasi++;
            if(iterasi == random){
                cout << "+----------------------------------------+" << endl;
                cout << "|           P E M E N A N G              |" << endl;
                cout << "+----------------------------------------+" << endl << endl;
                cout << "  Nama    : " << anggota->nama << endl; 
                cout << "  Alamat  : " << anggota->alamat << endl << endl; 
                cout << "+----------------------------------------+" << endl; 
                //Input data ke queue
                indeks = (anggota->indeks); 
                anggota->jml_ikut--;
                return;
            }
        }
        anggota = anggota->next;
    }
}

void daftarPem(int indeks, Queue pemenang, Node* head_ref){
    int id;
    Node* anggota; 

    cout << "+---------+-----------------------------+---------------------------------------+"<< endl;
    cout << "|" << setw(5) << "ID" << setw(5) << "|" << setw(15) << "NAMA" << setw(15) << "|" 
    << setw(20) << "ALAMAT" << setw(20) << "|" << endl;
    cout << "+---------+-----------------------------+---------------------------------------+" << endl;

    for(int i = 0; i < indeks; i++){
        id = pemenang.dequeue();
        anggota = head_ref;
        while(anggota != NULL){
            if(anggota->indeks == id){ 
                 cout << "|" << setw(5) << anggota->indeks << setw(5) << "|" << setw(29) <<  anggota->nama << "|" << setw(39) << anggota->alamat<< "|" << endl;
                 cout << "+---------+-----------------------------+---------------------------------------" << endl;           
            }
            anggota = anggota->next; 
        }
    } 
}

void keluar(){
    char pilihan;
    cout << "Yakin ingin keluar (Y/T) : ";
    cin >> pilihan; 

    if(pilihan == 'y' || pilihan == 'Y'){
        exit(1);
    }
}

int main(){
    int pilih, jum_ikt, id, random, indeks, jm_pem = 0;
    bool lanjut = false;
    string nama, alamat;

    // Inisiasi list node untuk daftar anggota
    Node* anggota = NULL;
    // Inisiasi queue untuk daftar pemenang arisan
    Queue p1;

    // Ilustrasi daftar anggota arisan awal
    insertAnggota(&anggota, "Siti Kosyiah", "Jl. Kepatihan Gading 1", 1);
    insertAnggota(&anggota, "Riyantini", "Jl. Kemuning 19", 1);
    insertAnggota(&anggota, "Anifah Mei Khati", "Jl. Kepatihan Gading 2", 1);
    insertAnggota(&anggota, "Nur Fadilah", "Jl. Pramuka 10", 1);
    insertAnggota(&anggota, "Dwi Yantri Rahesanita", "Jl. Kasongan km. 14", 2);

    do{
        system("CLS");
        cout << "----- PROGRAM ARISAN  -----"<< endl << endl;
        cout << "[1] Tambah Anggota" << endl;
        cout << "[2] Hapus Anggota" << endl; 
        cout << "[3] Daftar Anggota" << endl;
        cout << "[4] Acak Pemenang" << endl;
        cout << "[5] Sudah Mendapat Arisan" << endl;
        cout << "[6] Keluar" << endl;
        cout << "Pilih : ";
        cin >> pilih;
        cin.ignore();
    
        switch(pilih){
            case 1:
                system("cls");
                cout << "===== TAMBAH ANGGOTA =====" << endl << endl; 
                cout << "Nama        : ";
                getline(cin, nama);
                cout << "Alamat      : ";
                getline(cin, alamat);
                cout << "Jumlah Ikut : ";
                cin >> jum_ikt;
                // Menambahkan data ke node
                insertAnggota(&anggota, nama, alamat, jum_ikt);
                cout << endl;
                cout << "Input anggota berhasil" << endl << endl;
                system("PAUSE");
            break;

            case 2:
                system("cls");
                cout << "==== HAPUS ANGGOTA ====" << endl << endl; 
                if(hitung(anggota) <= 0) {
                    cout << "Data Anggota Kosong" << endl << endl;
                }
                else {
                    cout << "Nama : ";
                    getline(cin, nama);
                    cout << "ID   : ";
                    cin >> id; 
                    // Memberikan konfirmasi atas data yang ingin dihapus
                    konfirmasi(anggota, id, lanjut);

                    if(lanjut == true){
                        // mengahapuse node apabila konfirmasi dinyatakan benar
                        hapusNode(&anggota, id);
                        cout << endl;
                        cout << "---- Data telah berhasil dihapus -----" << endl << endl; 
                    } else {
                        cout << "---- Maaf Data tidak ditemukan -----" << endl << endl; 
                    }
                    system("PAUSE");

                }
            break; 
            
            case 3:
                system("CLS");
                cout << "==== DAFTAR ANGGOTA ====" << endl << endl;
                daftarAnggota(anggota);
                cout << endl; 
                system("PAUSE");
            break; 
            
            case 4:
                system("CLS");
                cout << "==== ACAK PEMENANG ====" << endl << endl;
               
                if(hitung(anggota) > 0){
                     random = acakPemenang(anggota);
                     pemenang(anggota, indeks, random);
                     //memasukkan indeks pemenang ke queue
                     p1.enqueue(indeks);
                     //indeks jumlah pemenang
                     jm_pem++;
                }
                else {
                    cout << endl;
                    cout << "PROGRAM ARISAN TELAH SELESAI" << endl << endl;
                }
                system("PAUSE");
            break; 
            
            case 5:
                system("CLS");
                cout << "==== SUDAH MENDAPAT ARISAN ====" << endl << endl;
                daftarPem(jm_pem, p1, anggota);
                system("PAUSE");
            break; 
            
            case 6:
                system("CLS");
                cout << "==== KELUAR PROGRAM ====" << endl << endl; 
                keluar();
            break;

            default:
                system("CLS");
                cout << "Mohon masukkan indeks angka (1/2/3/4/5/6/7)" << endl << endl;
                system("PAUSE");
            break;   
        }

    } while(pilih != 0);

    return 0;

}