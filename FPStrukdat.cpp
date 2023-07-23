#include <iostream>
#include <string>
#include <algorithm>
#include <conio.h>

#define RED "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"

using namespace std;

const int MAX_BOOKING = 100;

// Struktur data tiket pesawat
struct Tiket {
    string nama, NIK;
    string kelas;
    int nomorKursi;
    string pesawat;
    string rute;
    string fasilitas;
    string jadwal;
    double harga;
    bool boking;
};

struct Pembayaran {
	int top = -1;
    string nama[MAX_BOOKING];
    string NIK[MAX_BOOKING];
    string jadwal[MAX_BOOKING];
    string kelas[MAX_BOOKING];
    int nomorKursi[MAX_BOOKING];
    string pesawat[MAX_BOOKING];
    string rute[MAX_BOOKING];
    double harga[MAX_BOOKING];
};

Pembayaran pembayaran;

// Fungsi untuk mencari tiket berdasarkan nomor kursi
bool cariTiket(const Tiket* tiket, int jumlahTiket, int nomorKursi) {
    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].nomorKursi == nomorKursi) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk membandingkan tiket berdasarkan nomor kursi (digunakan dalam sorting)
bool bandingkanNomorKursi(const Tiket& tiket1, const Tiket& tiket2) {
    return tiket1.nomorKursi < tiket2.nomorKursi;
}

// Fungsi untuk membandingkan tiket berdasarkan harga (digunakan dalam sorting)
bool bandingkanHarga(const Tiket& tiket1, const Tiket& tiket2) {
    return tiket1.harga < tiket2.harga;
}

// Fungsi untuk menampilkan tiket
void tampilkanTiket(const Tiket& tiket) {
    cout << "==========================================" << endl;
    cout << "Nama\t\t: Mr. " << tiket.nama << endl;
    cout << "NIK\t\t: " << tiket.NIK << endl;
    cout << "Kelas\t\t: " << tiket.kelas << endl;
    cout << "Nomor Kursi\t: " << tiket.nomorKursi << endl;
    cout << "Pesawat\t\t: " << tiket.pesawat << endl;
    cout << "Rute\t\t: " << tiket.rute << endl;
    cout << "Fasilitas\t: " << tiket.fasilitas << endl;
    cout << "Jadwal\t\t: " << tiket.jadwal <<endl;
    cout << "Harga\t\t: " << tiket.harga << endl;

    if (tiket.boking) {
        cout << "Status\t\t: "<<YELLOW<<"booking" <<RESET<< endl;
    } else {
        cout << "Status\t\t: "<<GREEN<<"Lunas" <<RESET<< endl;
    }

    cout << "==========================================" << endl;
    cout << endl << endl;
}

// Fungsi untuk menghitung harga tiket berdasarkan kelas, jenis pesawat, dan rute
double hitungHargaTiket(string kelas, string pesawat, string rute) {
    double harga = 0.0;

    // Menentukan harga berdasarkan kelas
    if (kelas == "Ekonomi") {
        harga += 100.0;
    } else if (kelas == "Bisnis") {
        harga += 200.0;
    } else if (kelas == "Eksekutif") {
        harga += 300.0;
    }

    // Menentukan harga berdasarkan jenis pesawat
    if (pesawat == "Boeing 737") {
        harga += 50.0;
    } else if (pesawat == "Airbus A320") {
        harga += 75.0;
    } else if (pesawat == "Boeing 777") {
        harga += 100.0;
    } else if (pesawat == "Airbus A380") {
        harga += 125.0;
    }

    // Menentukan harga berdasarkan rute
    if (rute == "YOGYAKARTA - BIMA") {
        harga += 150.0;
    } else if (rute == "YOGYAKARTA - LAMPUNG") {
        harga += 100.0;
    } else if (rute == "YOGYAKARTA - SURABAYA") {
        harga += 150.0;
    } else if (rute == "YOGYAKARTA - KEBUMEN") {
        harga += 200.0;
    }

    return harga;
}

// Fungsi untuk membeli tiket stack
void beliTiket(Tiket* tiket, int& jumlahTiket , string nama, string jadwal, string NIK, string kelas, int nomorKursi, string pesawat, string rute, bool boking) {
    pembayaran.top++;
    
    tiket[jumlahTiket].nama = nama;
    tiket[jumlahTiket].NIK = NIK;
    tiket[jumlahTiket].jadwal = jadwal;
    tiket[jumlahTiket].kelas = kelas;
    tiket[jumlahTiket].nomorKursi = nomorKursi;
    tiket[jumlahTiket].pesawat = pesawat;
    tiket[jumlahTiket].rute = rute;
    tiket[jumlahTiket].harga = hitungHargaTiket(kelas, pesawat, rute);
    tiket[jumlahTiket].boking = boking;
    
    pembayaran.nama[pembayaran.top] = nama;
    pembayaran.NIK[pembayaran.top] = NIK;
    pembayaran.jadwal[pembayaran.top] = jadwal;
    pembayaran.kelas[pembayaran.top] = kelas;
	pembayaran.nomorKursi[pembayaran.top] = nomorKursi;
    pembayaran.pesawat[pembayaran.top] = pesawat;
    pembayaran.rute[pembayaran.top] = rute;
    pembayaran.harga[pembayaran.top] = hitungHargaTiket(kelas, pesawat, rute);

    // Menentukan fasilitas berdasarkan kelas
    if (kelas == "Bisnis") {
        tiket[jumlahTiket].fasilitas = "Makanan Tambahan";
    } else if (kelas == "Eksekutif") {
        tiket[jumlahTiket].fasilitas = "Layanan Fasilitas VIP Dan\n\t\t  Makanan Tambahan";
    } else {
        tiket[jumlahTiket].fasilitas = "Tidak Ada Fasilitas Tambahan";
    }

    jumlahTiket++;
}

// Fungsi untuk menghitung PPN pada tiket kelas pesawat
double hitungPPN(double harga) {
    return harga * 0.1; // 10% PPN
}

// Fungsi untuk menghapus tiket berdasarkan nama pemesan
void hapusTiket(Tiket* tiket, int& jumlahTiket, string nama) {
    bool tiketDitemukan = false;
    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].nama == nama) {
            cout << "Tiket dengan nama pemesan " << nama << " berhasil dihapus." << endl;
            // Menggeser elemen-elemen setelah tiket yang akan dihapus
            for (int j = i; j < jumlahTiket - 1; j++) {
                tiket[j] = tiket[j + 1];
            }
            jumlahTiket--;
            tiketDitemukan = true;
            break;
        }
    }
    if (!tiketDitemukan) {
        cout << "Tiket dengan nama pemesan " << nama << " tidak ditemukan." << endl;
    }

    // Menampilkan semua data pemesan tiket


    cout << "Data Pemesan Tiket: " << endl;
    if (jumlahTiket > 0) {
        for (int i = 0; i < jumlahTiket; i++) {
            cout << "Tiket ke-" << (i + 1) << ":" << endl;
            tampilkanTiket(tiket[i]);
        }
    } else {
        cout << "Data pemesan tiket masih kosong." << endl;
    }
    getche();
}

// Fungsi untuk melakukan sorting berdasarkan harga tiket
void sortingHarga(Tiket* tiket, int jumlahTiket) {
    // Implementasi Bubble Sort
    for (int i = 0; i < jumlahTiket - 1; i++) {
        for (int j = 0; j < jumlahTiket - i - 1; j++) {
            if (tiket[j].harga > tiket[j + 1].harga) {
                swap(tiket[j], tiket[j + 1]);
            }
        }
    }

    cout << "Tiket berhasil diurutkan berdasarkan harga." << endl;
    cout << "Data Pemesan Tiket: " << endl;
    if (jumlahTiket > 0) {
        for (int i = 0; i < jumlahTiket; i++) {
            cout << "Tiket ke-" << (i + 1) << ":" << endl;
            tampilkanTiket(tiket[i]);
        }
    } else {
        cout << "Data pemesan tiket masih kosong." << endl;
    }
    getche();
}

// Fungsi untuk melakukan boking tiket
void bokingTiket(Tiket* tiket, int& jumlahTiket, string nama, string NIK, string jadwal, string kelas, int nomorKursi, string pesawat, string rute) {
    beliTiket(tiket, jumlahTiket, nama, jadwal, NIK, kelas, nomorKursi, pesawat, rute, true);
}

// Fungsi untuk melakukan pembayaran tiket yang telah diboking
void bayarTiket(Tiket* tiket, int jumlahTiket, string nama) {
    bool tiketDitemukan = false;
    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].nama == nama && tiket[i].boking) {
            tiketDitemukan = true;

            cout << "==========================================" << endl;
            cout << "Informasi Tiket:" << endl;
            tampilkanTiket(tiket[i]);

            double totalHarga = tiket[i].harga;
            double ppn = hitungPPN(totalHarga);

            cout << "==========================================" << endl;
            cout << "Total Harga\t: " << totalHarga << endl;
            cout << "PPN (10%)\t: " << ppn << endl;
            cout << "==========================================" << endl;
            cout << "Total Pembayaran: " << totalHarga + ppn << endl;
            cout << "==========================================" << endl;

            char pilihan;
            cout << "Apakah Anda ingin melanjutkan pembayaran? (Y/N): ";
            cin >> pilihan;
            if (pilihan == 'Y' || pilihan == 'y') {
                cout << GREEN << "Pembayaran Berhasil." << RESET << endl;
                tiket[i].boking = false;
                tiket[i].nama = "Mr. " + tiket[i].nama + " (Lunas)";
            } else {
                cout << YELLOW << "Pembayaran Dibatalkan." << RESET << endl;
            }
            break;
        }
    }
    if (!tiketDitemukan) {
        cout << "Tiket dengan nama pemesan " << nama << " tidak ditemukan atau tidak dalam status boking." << endl;
    }
    getche();
}

// Stack
bool isEmpty() {
	return (pembayaran.top == -1);
}

int main() {
    const int JUMLAH_TIKET_MAKS = 100;
    Tiket tiketPesawat[JUMLAH_TIKET_MAKS];
    int jumlahTiket = 0;

    bool sedangBerjalan = true;
    while (sedangBerjalan) {
        cout << "\t\t\t\t\t\t\t==================================" << endl;
        cout << "\t\t\t\t\t\t\t=>    PEMBELIAN TIKET PESAWAT   <=" << endl;
        cout << "\t\t\t\t\t\t\t==================================" << endl;
        cout << "\t\t\t\t\t\t\t=   1. Beli Tiket                =" << endl;
        cout << "\t\t\t\t\t\t\t=   2. Boking Tiket              =" << endl;
        cout << "\t\t\t\t\t\t\t=   3. Cari Tiket                =" << endl;
        cout << "\t\t\t\t\t\t\t=   4. Tampilkan Semua Tiket     =" << endl;
        cout << "\t\t\t\t\t\t\t=   5. Hapus Tiket               =" << endl;
        cout << "\t\t\t\t\t\t\t=   6. Sorting Harga Tiket       =" << endl;
        cout << "\t\t\t\t\t\t\t=   7. Pembayaran                =" << endl;
        cout << "\t\t\t\t\t\t\t=   8. Keluar                    =" << endl;
        cout << "\t\t\t\t\t\t\t==================================" << endl;
        cout << "\t\t\t\t\t\t\tMasukkan pilihan Anda: ";
        int pilihan;
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1: {
            	system("cls");
			    int jumlahTiketDibeli;
			    cout << "\t\t\t\t\t\t\t\t============================="<<endl;
			    cout << "\t\t\t\t\t\t\t  Masukkan jumlah tiket yang ingin dibeli: ";
			    cin >> jumlahTiketDibeli;
			    system("cls");
			   
				    for (int i = 0; i < jumlahTiketDibeli; i++) {
				        string nama, NIK, jadwal, kelas;
				        int nomorKursi;
				        string pesawat, rute;
							
							system("cls");
					        cout << "Masukkan Nama Penumpang\t: ";
					        cin.ignore();
					        getline(cin, nama);
		                    
		                    cout << "Masukkan NIK Penumpang\t: ";
		                    getline(cin, NIK);
		          
		                    system("cls");
							cout << "======================================================" << endl;
		                    cout << "==          TANGGAL          |         JAM          ==" << endl;
		                    cout << "======================================================" << endl;
		                    cout << "==      1. 21.11.2022        |        10.00         ==" << endl;
							cout << "==      2. 22.11.2022        |        15.00         ==" << endl;
							cout << "==      3. 23.11.2022        |        11.00         ==" << endl;
							cout << "==      4. 24.11.2022        |        16.00         ==" << endl;
		                    cout << "======================================================" << endl;
		                    cout << endl;
		                    int pilihanJadwal;
		                    cout << "Pilih Jadwal Keberangkatan: ";
		                    cin >> pilihanJadwal;
		                    if (pilihanJadwal == 1) {
		                        jadwal = "21.11.2022\nJam\t\t: 10.00";
		                    } else if (pilihanJadwal == 2) {
		                        jadwal = "22.11.2022\nJam\t\t: 15.00";
		                    } else if (pilihanJadwal == 3) {
		                        jadwal = "23.11.2022\nJam\t\t: 11.00";
		                    } else if (pilihanJadwal == 4) {
		                        jadwal = "24.11.2022\nJam\t\t: 16.00";
		                    } else {
		                        cout <<RED<< "Jadwal Tidak Valid."<<RESET <<endl;
		                        continue;
		                    }
		                
					        cout << "======================================================" << endl;
					        cout << "==   Ekonomi    |    Bisnis    |      Eksekutif     ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "==  TIDAK ADA   |    MAKANAN   | MAKANAN + LAYANAN  ==" << endl;
					        cout << "==              |              |                    ==" << endl;
					        cout << "==   100.0      |     200.0    |        300.0       ==" << endl;
					        cout << "==              |              |                    ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "Masukkan jenis kelas (Ekonomi/Bisnis/Eksekutif): ";
					        cin >> kelas;
					        cout << "Masukkan nomor kursi: ";
					        cin >> nomorKursi;
		
					        // Memilih rute keberangkatan
					        system("cls");
					        cout << "======================================================" << endl;
					        cout << "==       KEBERANGKATAN       |        TUJUAN        ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "==      1. YOGYAKARTA        |         BIMA         ==" << endl;
					        cout << "==      2. YOGYAKARTA        |        LAMPUNG       ==" << endl;
					        cout << "==      3. YOGYAKARTA        |        SURABAYA      ==" << endl;
					        cout << "==      4. YOGYAKARTA        |        KEBUMEN       ==" << endl;
					        cout << "======================================================" << endl;
					        cout << endl;
					        int pilihanRute;
					        cout << "Masukkan Nomor Rute: ";
					        cin >> pilihanRute;
					        if (pilihanRute == 1) {
					            rute = "YOGYAKARTA - BIMA";
					        } else if (pilihanRute == 2) {
					            rute = "YOGYAKARTA - LAMPUNG";
					        } else if (pilihanRute == 3) {
					            rute = "YOGYAKARTA - SURABAYA";
					        } else if (pilihanRute == 4) {
					            rute = "YOGYAKARTA - KEBUMEN";
					        } else {
					            cout << RED << "Rute Tidak Valid." << RESET << endl;
					            continue;
					        }
					
							// Memilih jenis pesawat
						    cout << "======================================================" << endl;
					        cout << "==                   NAMA PESAWAT                   ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "==                  1. BOEING 737                   ==" << endl;
					        cout << "==                  2. AIRBUS A320                  ==" << endl;
					        cout << "==                  3. BOEING 777                   ==" << endl;
					        cout << "==                  4. AIRBUS A380                  ==" << endl;
					        cout << "======================================================" << endl;
					
					        int pilihanPesawat;
					        cout << "Masukkan Nomor Pesawat: ";
					        cin >> pilihanPesawat;
					        if (pilihanPesawat == 1) {
					            pesawat = "Boeing 737";
					        } else if (pilihanPesawat == 2) {
					            pesawat = "Airbus A320";
					        } else if (pilihanPesawat == 3) {
					            pesawat = "Boeing 777";
					        } else if (pilihanPesawat == 4) {
					            pesawat = "Airbus A380";
					        } else {
					            cout << RED << "Jenis Pesawat Tidak Valid." << RESET << endl;
					            continue;
					        }
		
		        		// Mengecek apakah kursi sudah terisi
				        if (cariTiket(tiketPesawat, jumlahTiket, nomorKursi)) {
				            cout << "Kursi Dengan Nomor " << nomorKursi << " Sudah Terisi. Pilih kursi lain." << endl;
				            continue;
				        }
				
				        beliTiket(tiketPesawat, jumlahTiket, nama, jadwal, NIK, kelas, nomorKursi, pesawat, rute, false);
				    }
				     // Tampilkan informasi tiket dan melakukan pembayaran
				        cout << "\nInformasi Tiket yang Dibeli:\n" << endl;
					    for (int i = 0; i < jumlahTiket; i++) {
					        cout << "Tiket ke-" << (i + 1) << ":" << endl;
					        tampilkanTiket(tiketPesawat[i]);
					        cout << endl;
					    }
					    
					    double totalHarga = 0.0;
					    for (int i = 0; i < jumlahTiket; i++) {
					        totalHarga += tiketPesawat[i].harga;
					    }

				
				        //double totalHarga = tiketPesawat[jumlahTiket - 1].harga;
				        double ppn = hitungPPN(totalHarga);
				
				        cout << "==========================================" << endl;
				        cout << "Total Harga\t: " << totalHarga << endl;
				        cout << "PPN (10%)\t: " << ppn << endl;
				        cout << "==========================================" << endl;
				        cout << "Total Pembayaran: " << totalHarga + ppn << endl;
				        cout << "==========================================" << endl;
				        
				        if (jumlahTiketDibeli > 3) {
				        double totalHarga = 0.0;
				        for (int i = jumlahTiket - jumlahTiketDibeli; i < jumlahTiket; i++) {
				            totalHarga += tiketPesawat[i].harga;
				        }
				
				        // Menghitung diskon dan total harga setelah diskon
				        double diskon = 0.1 * totalHarga; // 10% diskon
				        totalHarga -= diskon;
				        cout << "==========================================" << endl;
				        cout <<YELLOW<< "Anda mendapatkan diskon 10%." <<RESET<< endl;
				        cout << "Total harga setelah diskon: "<<GREEN<< totalHarga <<RESET<< endl;
				        cout << "==========================================" << endl;
				   	 	}
				
				        char pilihanBayar;
				        cout << "Apakah Anda ingin melanjutkan pembayaran? (Y/N): ";
				        cin >> pilihanBayar;
				        if (pilihanBayar == 'Y' || pilihanBayar == 'y') {
				            cout << GREEN << "Pembayaran Berhasil." << RESET << endl;
				           for (int i = 0; i < jumlahTiket; i++) {
					            tiketPesawat[i].boking = false;
					            tiketPesawat[i].nama = "Mr. " + tiketPesawat[i].nama + " (Lunas)";
        						}
				        } else {
				            cout << YELLOW << "Pembayaran Dibatalkan." << RESET << endl;
				        };
				
				    // Diskon jika membeli lebih dari 3 tiket
				   
				    
				    cout << "Terima Kasih Telah Membeli Tiket." << endl;
				    getche();
				    system("cls");
				    break;
				}
            case 2: {
            	system("cls");
                int jumlahTiketBoking;
                cout << "Masukkan jumlah tiket yang ingin diboking: ";
                cin >> jumlahTiketBoking;
                cout << endl;

                for (int i = 0; i < jumlahTiketBoking; i++) {
                    string nama, NIK, jadwal, kelas;
				        int nomorKursi;
				        string pesawat, rute;
							
							system("cls");
					        cout << "Masukkan Nama Penumpang\t: ";
					        cin.ignore();
					        getline(cin, nama);
		                    
		                    cout << "Masukkan NIK Penumpang\t: ";
		                    getline(cin, NIK);
		          
		                    system("cls");
							cout << "======================================================" << endl;
		                    cout << "==          TANGGAL          |         JAM          ==" << endl;
		                    cout << "======================================================" << endl;
		                    cout << "==      1. 21.11.2022        |        10.00         ==" << endl;
							cout << "==      2. 22.11.2022        |        15.00         ==" << endl;
							cout << "==      3. 23.11.2022        |        11.00         ==" << endl;
							cout << "==      4. 24.11.2022        |        16.00         ==" << endl;
		                    cout << "======================================================" << endl;
		                    cout << endl;
		                    int pilihanJadwal;
		                    cout << "Pilih Jadwal Keberangkatan: ";
		                    cin >> pilihanJadwal;
		                    if (pilihanJadwal == 1) {
		                        jadwal = "21.11.2022\nJam\t\t: 10.00";
		                    } else if (pilihanJadwal == 2) {
		                        jadwal = "22.11.2022\nJam\t\t: 15.00";
		                    } else if (pilihanJadwal == 3) {
		                        jadwal = "23.11.2022\nJam\t\t: 11.00";
		                    } else if (pilihanJadwal == 4) {
		                        jadwal = "24.11.2022\nJam\t\t: 16.00";
		                    } else {
		                        cout <<RED<< "Jadwal Tidak Valid."<<RESET <<endl;
		                        continue;
		                    }
		                
					        cout << "======================================================" << endl;
					        cout << "==   Ekonomi    |    Bisnis    |      Eksekutif     ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "==  TIDAK ADA   |    MAKANAN   | MAKANAN + LAYANAN  ==" << endl;
					        cout << "==              |              |                    ==" << endl;
					        cout << "==   100.0      |     200.0    |        300.0       ==" << endl;
					        cout << "==              |              |                    ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "Masukkan jenis kelas (Ekonomi/Bisnis/Eksekutif): ";
					        cin >> kelas;
					        cout << "Masukkan nomor kursi: ";
					        cin >> nomorKursi;
		
					        // Memilih rute keberangkatan
					        system("cls");
					        cout << "======================================================" << endl;
					        cout << "==       KEBERANGKATAN       |        TUJUAN        ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "==      1. YOGYAKARTA        |         BIMA         ==" << endl;
					        cout << "==      2. YOGYAKARTA        |        LAMPUNG       ==" << endl;
					        cout << "==      3. YOGYAKARTA        |        SURABAYA      ==" << endl;
					        cout << "==      4. YOGYAKARTA        |        KEBUMEN       ==" << endl;
					        cout << "======================================================" << endl;
					        cout << endl;
					        int pilihanRute;
					        cout << "Masukkan Nomor Rute: ";
					        cin >> pilihanRute;
					        if (pilihanRute == 1) {
					            rute = "YOGYAKARTA - BIMA";
					        } else if (pilihanRute == 2) {
					            rute = "YOGYAKARTA - LAMPUNG";
					        } else if (pilihanRute == 3) {
					            rute = "YOGYAKARTA - SURABAYA";
					        } else if (pilihanRute == 4) {
					            rute = "YOGYAKARTA - KEBUMEN";
					        } else {
					            cout << RED << "Rute Tidak Valid." << RESET << endl;
					            continue;
					        }
					
							// Memilih jenis pesawat
						    cout << "======================================================" << endl;
					        cout << "==                   NAMA PESAWAT                   ==" << endl;
					        cout << "======================================================" << endl;
					        cout << "==                  1. BOEING 737                   ==" << endl;
					        cout << "==                  2. AIRBUS A320                  ==" << endl;
					        cout << "==                  3. BOEING 777                   ==" << endl;
					        cout << "==                  4. AIRBUS A380                  ==" << endl;
					        cout << "======================================================" << endl;
					
					        int pilihanPesawat;
					        cout << "Masukkan Nomor Pesawat: ";
					        cin >> pilihanPesawat;
					        if (pilihanPesawat == 1) {
					            pesawat = "Boeing 737";
					        } else if (pilihanPesawat == 2) {
					            pesawat = "Airbus A320";
					        } else if (pilihanPesawat == 3) {
					            pesawat = "Boeing 777";
					        } else if (pilihanPesawat == 4) {
					            pesawat = "Airbus A380";
					        } else {
					            cout << RED << "Jenis Pesawat Tidak Valid." << RESET << endl;
					            continue;
					        }

                    // Mengecek apakah kursi sudah terisi
                    if (cariTiket(tiketPesawat, jumlahTiket, nomorKursi)) {
                        cout << "Kursi Dengan Nomor " << nomorKursi << " Sudah Terisi. Pilih kursi lain." << endl;
                        continue;
                    }

                    bokingTiket(tiketPesawat, jumlahTiket, nama, NIK, jadwal, kelas, nomorKursi, pesawat, rute);
                    cout << endl;
                    cout << GREEN << "Tiket Berhasil Diboking." << RESET << endl << endl << endl;
                }

                cout << "Terima Kasih Telah Melakukan Boking Tiket." << endl;
                getche();
                system("cls");
                break;
            }
            case 3: {
            	system("cls");
            	int nomorKursi;
	               for (int i = 0; i < jumlahTiket; i++) {
	                        cout << "Tiket ke-" << (i + 1) << ":" << endl;
	                        tampilkanTiket(tiketPesawat[i]);
                    }
                cout << "Masukkan Nomor Kursi: ";
                cin >> nomorKursi;
                if (cariTiket(tiketPesawat, jumlahTiket, nomorKursi)) {
                    cout << GREEN << "Tiket Ditemukan." << RESET << endl;
                    cout << "Informasi Tiket:" << endl;
                    for (int i = 0; i < jumlahTiket; i++) {
                        if (tiketPesawat[i].nomorKursi == nomorKursi) {
                            tampilkanTiket(tiketPesawat[i]);
                            break;
                        }
                    }
                } else {
                    cout << RED << "Tiket Tidak Ditemukan." << RESET << endl;
                }
                getche();
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
                cout << "Data Pemesan Tiket: " << endl;
                if (jumlahTiket > 0) {
                    for (int i = 0; i < jumlahTiket; i++) {
                        cout << "Tiket ke-" << (i + 1) << ":" << endl;
                        tampilkanTiket(tiketPesawat[i]);
                    }
                } else {
                    cout << "Data pemesan tiket masih kosong." << endl;
                }
                getche();
                system("cls");
                break;
            }
            case 5: {
                string nama;
                cout << "Masukkan Nama Pemesan Tiket yang akan dihapus: ";
                cin.ignore();
                getline(cin, nama);
                hapusTiket(tiketPesawat, jumlahTiket, nama);
                getche();
                system("cls");
                break;
            }
            case 6: {
                sortingHarga(tiketPesawat, jumlahTiket);
                getche();
                system("cls");
                break;
            }
            case 7: {
                string nama;
                int pilihan2;
                string pilihan3;
                
		        cout << "=============================" << endl;
		        cout << ">>>      PEMBAYARAN       <<=" << endl;
		        cout << "=============================" << endl;
		        cout << "= 1. Bayar Tiket            =" << endl;
		        cout << "= 2. Batalkan Tiket         =" << endl;
		        cout << "= 3. Kembali                =" << endl;
		        cout << "=============================" << endl;
		        cout << "Masukkan pilihan Anda: ";
		        cin >> pilihan2;
                
                if(pilihan2 == 1) {
	                cout << "Masukkan Nama Pemesan Tiket yang akan dibayar: ";
	                cin.ignore();
	                getline(cin, nama);
	                bayarTiket(tiketPesawat, jumlahTiket, nama);
	                getche();
	                system("cls");
	        	} else if(pilihan2 == 2) {
	        		if(isEmpty()) {
	        			cout << "Belum ada tiket yang dibayar." << endl;
					} else {
		        		cout << "Tiket Terakhir Dibayar : " << endl;
		        		
		        		cout << pembayaran.nama[pembayaran.top] << ", " << pembayaran.harga[pembayaran.top] << endl;
						
						cout << endl << "Batalkan transaksi terakhir? [Y/N] : ";
						cin >> pilihan3;
						
						if(pilihan3 == "Y" || pilihan3 == "y") {
						    for (int i = 0; i < jumlahTiket; i++) {
						        if (tiketPesawat[i].nomorKursi == pembayaran.nomorKursi[pembayaran.top]) {
									pembayaran.top--;
									tiketPesawat[i].boking = true;
						        }
						    }
							
							cout << "Transaksi berhasil dibatalkan. Dana dikembalikan ke rek. anda" << endl;
			                getche();
			                system("cls");
						}
					}
				}
                break;
            }
            case 8: {
                sedangBerjalan = false;
                break;
            }
            default: {
                cout << RED << "Pilihan Tidak Valid. Silakan Coba Lagi." << RESET << endl;
                getche();
                system("cls");
                break;
            }
        }
    }

    return 0;
}
