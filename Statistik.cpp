#include <iostream>
#include <vector>
#include <string>    // Diperlukan untuk std::string dan getline
#include <sstream>   // Diperlukan untuk std::stringstream
#include <numeric>
#include <algorithm>
#include <map>
#include <cmath>

// --- Semua fungsi hitung (Mean, Median, Modus, Kuartil) tetap sama ---

// Fungsi untuk menghitung Rata-rata (Mean)
double hitungMean(const std::vector<double>& data) {
    if (data.empty()) return 0;
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Fungsi untuk menghitung Median
double hitungMedian(std::vector<double> data) {
    if (data.empty()) return 0;
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    if (n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        return data[n / 2];
    }
}

// Fungsi untuk menghitung Modus (Versi Kompatibel)
std::vector<double> hitungModus(const std::vector<double>& data) {
    std::map<double, int> frekuensi;
    for (double nilai : data) {
        frekuensi[nilai]++;
    }
    int maxFreq = 0;
    for (auto const& pair : frekuensi) { 
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
        }
    }
    std::vector<double> modus;
    if (maxFreq > 1) { 
        for (auto const& pair : frekuensi) { 
            if (pair.second == maxFreq) {
                modus.push_back(pair.first);
            }
        }
    }
    return modus;
}

// Fungsi untuk menghitung Kuartil (Q1, Q2, Q3)
void hitungKuartil(std::vector<double> data, double& q1, double& q2, double& q3) {
    if (data.size() < 3) { // Kuartil tidak terdefinisi dengan baik untuk data < 3
        q1 = q2 = q3 = 0;
        return;
    }
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    q2 = hitungMedian(data);
    double pos1 = 0.25 * (n + 1);
    if (pos1 == floor(pos1)) {
        q1 = data[pos1 - 1];
    } else {
        int index = floor(pos1) - 1;
        double sisa = pos1 - floor(pos1);
        q1 = data[index] + sisa * (data[index + 1] - data[index]);
    }
    double pos3 = 0.75 * (n + 1);
     if (pos3 == floor(pos3)) {
        q3 = data[pos3 - 1];
    } else {
        int index = floor(pos3) - 1;
        double sisa = pos3 - floor(pos3);
        q3 = data[index] + sisa * (data[index + 1] - data[index]);
    }
}

// ==========================================================
// FUNGSI MAIN YANG SUDAH DIMODIFIKASI
// ==========================================================
int main() {
    std::vector<double> data;
    std::string line;

    std::cout << "=== Kalkulator Statistik Data Tunggal ===\n";
    std::cout << "Masukkan semua data dalam satu baris (pisahkan dengan spasi): " << std::endl;
    
    // 1. Membaca seluruh baris input
    std::getline(std::cin, line);

    // 2. Menggunakan stringstream untuk memecah baris menjadi angka
    std::stringstream ss(line);
    double number;

    // 3. Loop untuk memasukkan setiap angka ke vector
    while (ss >> number) {
        data.push_back(number);
    }

    // Pengecekan jika pengguna tidak memasukkan data sama sekali
    if (data.empty()) {
        std::cout << "Tidak ada data yang dimasukkan." << std::endl;
        return 1;
    }

    std::cout << "\n--- Hasil Perhitungan ---\n";

    // Menghitung dan menampilkan Mean
    std::cout << "Mean (Rata-rata)   : " << hitungMean(data) << std::endl;

    // Menghitung dan menampilkan Median
    std::cout << "Median (Nilai Tengah): " << hitungMedian(data) << std::endl;

    // Menghitung dan menampilkan Modus
    std::vector<double> modus = hitungModus(data);
    std::cout << "Modus                : ";
    if (modus.empty()) {
        std::cout << "Tidak ada modus." << std::endl;
    } else {
        for (size_t i = 0; i < modus.size(); ++i) {
            std::cout << modus[i] << (i == modus.size() - 1 ? "" : ", ");
        }
        std::cout << std::endl;
    }

    // Menghitung dan menampilkan Kuartil
    double q1, q2, q3;
    hitungKuartil(data, q1, q2, q3);
    if(data.size() >= 3){
        std::cout << "Kuartil 1 (Q1)       : " << q1 << std::endl;
        std::cout << "Kuartil 2 (Q2/Median): " << q2 << std::endl;
        std::cout << "Kuartil 3 (Q3)       : " << q3 << std::endl;
    } else {
        std::cout << "Kuartil tidak dapat dihitung (data kurang dari 3)." << std::endl;
    }
    
    std::cout << "-------------------------\n";

    return 0;
}