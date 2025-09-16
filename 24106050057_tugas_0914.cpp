#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

double hitungMean(const double data[], int n);
double hitungMedian(const double data[], int n);
void hitungModus(const double data[], int n, double hasilModus[], int& jumlahModus);
void hitungKuartil(const double data[], int n, double& q1, double& q2, double& q3);
using namespace std;

int main() {
    const int KAPASITAS_MAKS = 1000;
    double data[KAPASITAS_MAKS];
    int n = 0;

    cout << "Masukkan semua data dalam satu baris (pisahkan dengan spasi):" << endl;

    string line;
    getline(cin, line);
    stringstream ss(line);
    double number;

    while (n < KAPASITAS_MAKS && ss >> number) {
        data[n] = number;
        n++;
    }

    if (n == 0) {
        cout << "Tidak ada data yang dimasukkan." << endl;
        return 1;
    }
    
    sort(data, data + n);

    cout << "\n--- Hasil Perhitungan ---\n";

    cout << "Mean (Rata-rata)   : " << hitungMean(data, n) << endl;
    cout << "Median (Nilai Tengah): " << hitungMedian(data, n) << endl;

    double hasilModus[KAPASITAS_MAKS];
    int jumlahModus = 0;
    hitungModus(data, n, hasilModus, jumlahModus);

    cout << "Modus                : ";
    if (jumlahModus == 0) {
        cout << "Tidak ada modus." << endl;
    } else {
        for (int i = 0; i < jumlahModus; ++i) {
            cout << hasilModus[i] << (i == jumlahModus - 1 ? "" : ", ");
        }
        cout << endl;
    }

    double q1, q2, q3;
    if (n >= 3) {
        hitungKuartil(data, n, q1, q2, q3);
        cout << "Kuartil 1 (Q1)       : " << q1 << endl;
        cout << "Kuartil 2 (Q2/Median): " << q2 << endl;
        cout << "Kuartil 3 (Q3)       : " << q3 << endl;
    } else {
        cout << "Kuartil tidak dapat dihitung (data kurang dari 3)." << endl;
    }
    
    cout << "-------------------------\n";

    return 0;
}


double hitungMean(const double data[], int n) {
    double total = 0;
    for (int i = 0; i < n; ++i) {
        total += data[i];
    }
    return total / n;
}

double hitungMedian(const double data[], int n) {
    if (n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        return data[n / 2];
    }
}

void hitungModus(const double data[], int n, double hasilModus[], int& jumlahModus) {
    jumlahModus = 0;
    if (n == 0) return;

    int maxFreq = 0, currentFreq = 1;
    for (int i = 1; i < n; ++i) {
        if (data[i] == data[i-1]) currentFreq++;
        else {
            if (currentFreq > maxFreq) maxFreq = currentFreq;
            currentFreq = 1;
        }
    }
    if (currentFreq > maxFreq) maxFreq = currentFreq;

    if (maxFreq <= 1) return;

    currentFreq = 1;
    for (int i = 1; i < n; ++i) {
        if (data[i] == data[i-1]) currentFreq++;
        else {
            if (currentFreq == maxFreq) hasilModus[jumlahModus++] = data[i-1];
            currentFreq = 1;
        }
    }
    if (currentFreq == maxFreq) hasilModus[jumlahModus++] = data[n-1];
}

void hitungKuartil(const double data[], int n, double& q1, double& q2, double& q3) {
    q2 = hitungMedian(data, n);

    double pos1 = 0.25 * (n + 1);
    int index1 = (int)pos1 - 1;
    double sisa1 = pos1 - (int)pos1;
    if (sisa1 == 0) q1 = data[index1];
    else q1 = data[index1] + sisa1 * (data[index1 + 1] - data[index1]);

    double pos3 = 0.75 * (n + 1);
    int index3 = (int)pos3 - 1;
    double sisa3 = pos3 - (int)pos3;
    if (sisa3 == 0) q3 = data[index3];
    else q3 = data[index3] + sisa3 * (data[index3 + 1] - data[index3]);
}