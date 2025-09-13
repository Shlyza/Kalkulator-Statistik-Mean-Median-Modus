#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// ==========================================================
// FUNGSI BUATAN PENGGANTI DARI LIBRARY LAIN
// ==========================================================

// 1. Pengganti std::sort dari <algorithm>
//    Kita buat fungsi sorting sendiri dengan Bubble Sort.
void urutkanData(std::vector<double>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                // Tukar elemen
                double temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

// ==========================================================
// FUNGSI STATISTIK YANG SUDAH DIMODIFIKASI
// ==========================================================

// Fungsi Mean (tanpa std::accumulate)
double hitungMean(const std::vector<double>& data) {
    if (data.empty()) return 0;
    double total = 0;
    // Menggunakan loop manual sebagai pengganti std::accumulate
    for (int i = 0; i < data.size(); ++i) {
        total += data[i];
    }
    return total / data.size();
}

// Fungsi Median (tanpa std::sort)
double hitungMedian(std::vector<double> data) {
    if (data.empty()) return 0;
    // Menggunakan fungsi sorting buatan sendiri
    urutkanData(data);
    int n = data.size();
    if (n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        return data[n / 2];
    }
}

// Fungsi Modus (tanpa std::map dan std::sort)
std::vector<double> hitungModus(std::vector<double> data) {
    std::vector<double> modus;
    if (data.empty()) return modus;

    // Menggunakan fungsi sorting buatan sendiri
    urutkanData(data);

    int maxFreq = 0;
    int currentFreq = 0;
    
    // Iterasi untuk mencari frekuensi tertinggi
    for (int i = 0; i < data.size(); ++i) {
        currentFreq++;
        // Jika elemen berikutnya beda atau sudah di akhir vector
        if (i == data.size() - 1 || data[i] != data[i + 1]) {
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
            }
            currentFreq = 0; // Reset counter
        }
    }

    if (maxFreq <= 1) { // Tidak ada modus jika semua angka unik
        return modus;
    }

    // Iterasi kedua untuk mengumpulkan semua nilai modus
    currentFreq = 0;
    for (int i = 0; i < data.size(); ++i) {
        currentFreq++;
        if (i == data.size() - 1 || data[i] != data[i + 1]) {
            if (currentFreq == maxFreq) {
                modus.push_back(data[i]);
            }
            currentFreq = 0;
        }
    }
    return modus;
}


// Fungsi Kuartil (tanpa std::sort dan floor)
void hitungKuartil(std::vector<double> data, double& q1, double& q2, double& q3) {
    if (data.size() < 3) {
        q1 = q2 = q3 = 0;
        return;
    }
    // Menggunakan fungsi sorting buatan sendiri
    urutkanData(data);
    int n = data.size();
    q2 = hitungMedian(data);

    double pos1 = 0.25 * (n + 1);
    // Menggunakan (int) sebagai pengganti floor()
    int index1 = (int)pos1 - 1;
    double sisa1 = pos1 - (int)pos1;
    if(sisa1 == 0){
        q1 = data[pos1 - 1];
    } else {
        q1 = data[index1] + sisa1 * (data[index1 + 1] - data[index1]);
    }

    double pos3 = 0.75 * (n + 1);
    // Menggunakan (int) sebagai pengganti floor()
    int index3 = (int)pos3 - 1;
    double sisa3 = pos3 - (int)pos3;
     if (sisa3 == 0) {
        q3 = data[pos3 - 1];
    } else {
        q3 = data[index3] + sisa3 * (data[index3 + 1] - data[index3]);
    }
}


// Fungsi main tetap sama, tidak perlu diubah
int main() {
    std::vector<double> data;
    std::string line;

    std::cout << "=== Kalkulator Statistik (Versi Minimalis) ===\n";
    std::cout << "Masukkan semua data dalam satu baris (pisahkan dengan spasi): " << std::endl;
    
    std::getline(std::cin, line);

    std::stringstream ss(line);
    double number;

    while (ss >> number) {
        data.push_back(number);
    }

    if (data.empty()) {
        std::cout << "Tidak ada data yang dimasukkan." << std::endl;
        return 1;
    }

    std::cout << "\n--- Hasil Perhitungan ---\n";

    std::cout << "Mean (Rata-rata)   : " << hitungMean(data) << std::endl;
    std::cout << "Median (Nilai Tengah): " << hitungMedian(data) << std::endl;

    std::vector<double> modus = hitungModus(data);
    std::cout << "Modus                : ";
    if (modus.empty()) {
        std::cout << "Tidak ada modus." << std::endl;
    } else {
        for (int i = 0; i < modus.size(); ++i) {
            std::cout << modus[i] << (i == modus.size() - 1 ? "" : ", ");
        }
        std::cout << std::endl;
    }

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