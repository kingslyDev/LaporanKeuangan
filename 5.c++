#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Transaksi {
    string jenis;
    double jumlah;
    string keterangan;

    
    Transaksi(const string& jenis, double jumlah, const string& keterangan)
        : jenis(jenis), jumlah(jumlah), keterangan(keterangan) {}
};

class Keuangan {
private:
    double saldo;

public:
    Keuangan() : saldo(0.0) {}

    void catatPendapatan(double jumlah, const string& keterangan) {
        saldo += jumlah;
        Transaksi transaksi("Pendapatan", jumlah, keterangan);
        simpanTransaksi(transaksi);
    }

    void catatPengeluaran(double jumlah, const string& keterangan) {
        saldo -= jumlah;
        Transaksi transaksi("Pengeluaran", jumlah, keterangan);
        simpanTransaksi(transaksi);
    }

    void simpanTransaksi(const Transaksi& transaksi) {
        ofstream file("transaksi.txt", ios::app);
        if (file.is_open()) {
            file << transaksi.jenis << " " << fixed << setprecision(2) << transaksi.jumlah << " " << transaksi.keterangan << endl;
            file.close();
        } else {
            cerr << "Gagal membuka file transaksi.txt" << endl;
        }
    }

    void tampilkanLaporan() {
    ifstream file("transaksi.txt");
    if (file.is_open()) {
        cout << "========================LAPORAN KEUANGAN ========================" << endl;
        cout << "Saldo saat ini: " << fixed << setprecision(2) << saldo << endl;
        cout << "-------------------------------------------------" << endl;
        cout << setw(15) << "Jenis" << setw(20) << "Jumlah" << setw(15) << "Keterangan" << endl;
        cout << "-------------------------------------------------" << endl;

        string jenis;
        double jumlah;
        string keterangan;

        while (file >> jenis >> jumlah >> ws && getline(file, keterangan, '\n')) {
            cout << setw(15) << jenis << setw(15) << fixed << setprecision(2) << jumlah << setw(20) << keterangan << endl;
        }

        cout << "=================================================================" << endl;
        file.close();
    } else {
        cerr << "Gagal membuka file transaksi.txt" << endl;
    }
}

};

int main() {
    Keuangan keuangan;

    char pilihan;
    double jumlah;
    string keterangan;

    do {
        cout << "Pilih tindakan (P/Pendapatan, K/Pengeluaran, L/Laporan, S/Selesai): ";
        cin >> pilihan;

        switch (pilihan) {
            case 'P':
            case 'p':
                cout << "Masukkan jumlah pendapatan (rupiah tanpa koma): ";
                cin >> jumlah;
                cout << "Masukkan keterangan: ";
                cin.ignore();  // Ignore newline from previous input
                getline(cin, keterangan);
                keuangan.catatPendapatan(jumlah, keterangan);
                break;

            case 'K':
            case 'k':
                cout << "Masukkan jumlah pengeluaran (bentuk rupiah tanpa koma): ";
                cin >> jumlah;
                cout << "Masukkan keterangan: ";
                cin.ignore();  // Ignore newline from previous input
                getline(cin, keterangan);
                keuangan.catatPengeluaran(jumlah, keterangan);
                break;

            case 'L':
            case 'l':
                keuangan.tampilkanLaporan();
                break;

            case 'S':
            case 's':
                cout << "Program selesai." << endl;
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

    } while (pilihan != 'S' && pilihan != 's');

    return 0;
}
