#include <bits/stdc++.h>
using namespace std;

struct Produk {
    int id;
    string nama;
    string kategori;
    double harga;
};

struct ItemKeranjang {
    Produk produk;
    int jumlah;
};

struct Transaksi {
    int idTransaksi;
    vector<ItemKeranjang> item;
    double subtotal;
    double biayaPengiriman;
    double total;
    int tujuan;
};

class TokoOnline {
private:
    vector<Produk> produk;
    vector<ItemKeranjang> keranjang;
    vector<Transaksi> riwayatTransaksi;
    int counterTransaksi;

    const int V = 10;
    vector<vector<pair<int, int>>> graf;

public:
    TokoOnline() {
        inisialisasiProduk();
        inisialisasiGraf();
        counterTransaksi = 1;
    }

    void inisialisasiProduk() {
        produk = {
            {1, "Smartphone Samsung Galaxy S23", "Elektronik", 12000000},
            {2, "Laptop ASUS ROG Zephyrus G14", "Elektronik", 25000000},
            {3, "TV LED LG 43 Inch", "Elektronik", 6500000},
            {4, "Earbuds Apple AirPods Pro", "Elektronik", 3500000},
            {5, "Kamera DSLR Canon EOS 90D", "Elektronik", 17000000},
            {6, "Sepeda MTB Polygon", "Fitness", 5000000},
            {7, "Dumbbell 5kg", "Fitness", 200000},
            {8, "Matras Yoga", "Fitness", 250000},
            {9, "Mesin Elliptical", "Fitness", 7500000},
            {10, "Resistance Band", "Fitness", 100000},
            {11, "Serum Wajah Vitamin C", "Kecantikan", 150000},
            {12, "Masker Wajah Aloe Vera", "Kecantikan", 75000},
            {13, "Lipstik Matte L'Oréal", "Kecantikan", 120000},
            {14, "Parfum Chanel", "Kecantikan", 2500000},
            {15, "Sabun Cuci Muka Himalaya", "Kecantikan", 35000},
            {16, "Roti Tawar Serba Roti", "Konsumsi", 15000},
            {17, "Kopi Arabica 100g", "Konsumsi", 50000},
            {18, "Mie Instan", "Konsumsi", 5000},
            {19, "Susu UHT Indomilk 1 Liter", "Konsumsi", 18000},
            {20, "Teh Kotak Sosro 500ml", "Konsumsi", 7500}
        };
    }

    void inisialisasiGraf() {
        graf.resize(V);
        addEdge(0, 1, 2);
        addEdge(0, 2, 4);
        addEdge(1, 2, 1);
        addEdge(1, 3, 7);
        addEdge(2, 4, 3);
        addEdge(3, 4, 2);
        addEdge(3, 5, 1);
        addEdge(4, 6, 5);
        addEdge(5, 7, 3);
        addEdge(6, 8, 2);
        addEdge(7, 8, 2);
        addEdge(8, 9, 4);
    }

    void addEdge(int u, int v, int w) {
        graf[u].push_back(make_pair(v, w));
        graf[v].push_back(make_pair(u, w));
    }

    int hitungJarakTerpendek(int asal, int tujuan) {
        vector<int> jarak(V, numeric_limits<int>::max());
        vector<bool> dikunjungi(V, false);

        jarak[asal] = 0;

        for (int hitung = 0; hitung < V - 1; hitung++) {
            int u = -1;
            for (int i = 0; i < V; i++) {
                if (!dikunjungi[i] && (u == -1 || jarak[i] < jarak[u])) {
                    u = i;
                }
            }

            if (u == -1) break;
            dikunjungi[u] = true;

            for (auto& tetangga : graf[u]) {
                int v = tetangga.first;
                int berat = tetangga.second;

                if (!dikunjungi[v] && jarak[u] != numeric_limits<int>::max() 
                    && jarak[u] + berat < jarak[v]) {
                    jarak[v] = jarak[u] + berat;
                }
            }
        }

        return jarak[tujuan];
    }

    void tampilkanProdukTersortir(const string& berdasarkan) {
        vector<Produk> produkTersortir = produk;

        if (berdasarkan == "kategori") {
            sort(produkTersortir.begin(), produkTersortir.end(), 
                [](const Produk& a, const Produk& b) {
                    return a.kategori < b.kategori;
                });
        } else if (berdasarkan == "harga") {
            sort(produkTersortir.begin(), produkTersortir.end(), 
                [](const Produk& a, const Produk& b) {
                    return a.harga < b.harga;
                });
        }

        cout << "\nDaftar Produk:" << endl;
        cout << setw(5) << "ID" << setw(35) << "Nama" 
             << setw(15) << "Kategori" << setw(15) << "Harga" << endl;
        cout << string(70, '-') << endl;

        for (const auto& p : produkTersortir) {
            cout << setw(5) << p.id 
                 << setw(35) << p.nama 
                 << setw(15) << p.kategori 
                 << setw(15) << fixed << setprecision(0) << p.harga << endl;
        }
    }

    void tambahkanKeKeranjang(int idProduk, int jumlah) {
        auto it = find_if(produk.begin(), produk.end(),
            [idProduk](const Produk& p) { return p.id == idProduk; });

        if (it != produk.end()) {
            auto itKeranjang = find_if(keranjang.begin(), keranjang.end(),
                [idProduk](const ItemKeranjang& item) { 
                    return item.produk.id == idProduk; 
                });

            if (itKeranjang != keranjang.end()) {
                itKeranjang->jumlah += jumlah;
            } else {
                keranjang.push_back({*it, jumlah});
            }
            cout << "Produk berhasil ditambahkan ke keranjang!" << endl;
        } else {
            cout << "Produk tidak ditemukan!" << endl;
        }
    }

    void cariProduk(int id) {
        auto it = find_if(produk.begin(), produk.end(),
            [id](const Produk& p) { return p.id == id; });

        if (it != produk.end()) {
            cout << "\nProduk ditemukan:" << endl;
            cout << "ID: " << it->id << endl;
            cout << "Nama: " << it->nama << endl;
            cout << "Kategori: " << it->kategori << endl;
            cout << "Harga: Rp." << fixed << setprecision(0) << it->harga << endl;
        } else {
            cout << "Produk tidak ditemukan!" << endl;
        }
    }

    void lihatKeranjang() {
        if (keranjang.empty()) {
            cout << "Keranjang belanja kosong!" << endl;
            return;
        }

        cout << "\nIsi Keranjang:" << endl;
        cout << setw(5) << "ID" << setw(35) << "Nama" 
             << setw(10) << "Jumlah" << setw(15) << "Harga" 
             << setw(15) << "Total" << endl;
        cout << string(80, '-') << endl;

        double total = 0;
        for (const auto& item : keranjang) {
            double totalItem = item.produk.harga * item.jumlah;
            total += totalItem;

            cout << setw(5) << item.produk.id 
                 << setw(35) << item.produk.nama 
                 << setw(10) << item.jumlah 
                 << setw(15) << fixed << setprecision(0) << item.produk.harga 
                 << setw(15) << totalItem << endl;
        }
        cout << string(80, '-') << endl;
        cout << "Total: Rp." << fixed << setprecision(0) << total << endl;
    }

    void hapusDariKeranjang(int idProduk) {
        auto it = remove_if(keranjang.begin(), keranjang.end(),
            [idProduk](const ItemKeranjang& item) { 
                return item.produk.id == idProduk; 
            });

        if (it != keranjang.end()) {
            keranjang.erase(it, keranjang.end());
            cout << "Produk berhasil dihapus dari keranjang!" << endl;
        } else {
            cout << "Produk tidak ditemukan dalam keranjang!" << endl;
        }
    }

    double hitungBiayaPengiriman(int tujuan) {
        int jarak = hitungJarakTerpendek(0, tujuan);
        return jarak * 3000.0;
    }

    void bayar(int tujuan) {
        if (keranjang.empty()) {
            cout << "Keranjang belanja kosong!" << endl;
            return;
        }

        double subtotal = 0;
        for (const auto& item : keranjang) {
            subtotal += item.produk.harga * item.jumlah;
        }

        double biayaPengiriman = hitungBiayaPengiriman(tujuan);
        double total = subtotal + biayaPengiriman;

        Transaksi transaksi;
        transaksi.idTransaksi = counterTransaksi++;
        transaksi.item = keranjang;
        transaksi.subtotal = subtotal;
        transaksi.biayaPengiriman = biayaPengiriman;
        transaksi.total = total;
        transaksi.tujuan = tujuan;

        riwayatTransaksi.push_back(transaksi);

        cout << "\nPembayaran Berhasil!" << endl;
        cout << "ID Transaksi: " << transaksi.idTransaksi << endl;
        cout << "Subtotal: Rp." << fixed << setprecision(0) << subtotal << endl;
        cout << "Biaya Pengiriman: Rp." << biayaPengiriman << endl;
        cout << "Total: Rp." << total << endl;

        keranjang.clear();
    }

    void lihatRiwayatTransaksi() {
        if (riwayatTransaksi.empty()) {
            cout << "Belum ada riwayat transaksi!" << endl;
            return;
        }

        cout << "\nRiwayat Transaksi:" << endl;
        cout << setw(5) << "ID" << setw(15) << "Subtotal" 
             << setw(15) << "Pengiriman" << setw(15) << "Total" << endl;
        cout << string(50, '-') << endl;

        for (const auto& transaksi : riwayatTransaksi) {
            cout << setw(5) << transaksi.idTransaksi 
                 << setw(15) << fixed << setprecision(0) << transaksi.subtotal 
                 << setw(15) << transaksi.biayaPengiriman 
                 << setw(15) << transaksi.total << endl;
        }
    }

    void lihatDetailTransaksi(int idTransaksi) {
        auto it = find_if(riwayatTransaksi.begin(), riwayatTransaksi.end(),
            [idTransaksi](const Transaksi& transaksi) { 
                return transaksi.idTransaksi == idTransaksi; 
            });

        if (it == riwayatTransaksi.end()) {
            cout << "Transaksi tidak ditemukan!" << endl;
            return;
        }

        cout << "\nDetail Transaksi #" << it->idTransaksi << endl;
        cout << string(80, '-') << endl;
        cout << "Daftar Produk:" << endl;
        cout << setw(35) << "Nama" << setw(10) << "Jumlah" 
             << setw(15) << "Harga" << setw(15) << "Total" << endl;
        cout << string(80, '-') << endl;

        for (const auto& item : it->item) {
            cout << setw(35) << item.produk.nama 
                 << setw(10) << item.jumlah 
                 << setw(15) << fixed << setprecision(0) << item.produk.harga 
                 << setw(15) << (item.produk.harga * item.jumlah) << endl;
        }

        cout << string(80, '-') << endl;
        cout << "Subtotal: Rp." << it->subtotal << endl;
        cout << "Biaya Pengiriman: Rp." << it->biayaPengiriman << endl;
        cout << "Total: Rp." << it->total << endl;
        cout << "Tujuan Pengiriman: Kota " << it->tujuan << endl;
    }
};

int main() {
    TokoOnline toko;
    int pilihan;

    while (true) {
        cout << "\nToko Online" << endl;
        cout << "1. Lihat Produk (Sort)" << endl;
        cout << "2. Tambah ke Keranjang" << endl;
        cout << "3. Cari Produk" << endl;
        cout << "4. Lihat Keranjang" << endl;
        cout << "5. Hapus dari Keranjang" << endl;
        cout << "6. Checkout" << endl;
        cout << "7. Lihat Riwayat Transaksi" << endl;
        cout << "8. Lihat Detail Transaksi" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1: {
                cout << "\nSort berdasarkan:" << endl;
                cout << "1. Kategori" << endl;
                cout << "2. Harga" << endl;
                cout << "Pilihan: ";
                int pilihanSort;
                cin >> pilihanSort;

                if (pilihanSort == 1) {
                    toko.tampilkanProdukTersortir("kategori");
                } else if (pilihanSort == 2) {
                    toko.tampilkanProdukTersortir("harga");
                } else {
                    cout << "Pilihan tidak valid!" << endl;
                }
                break;
            }
            case 2: {
                cout << "Masukkan ID Produk: ";
                int id;
                cin >> id;
                cout << "Masukkan Jumlah: ";
                int jumlah;
                cin >> jumlah;
                toko.tambahkanKeKeranjang(id, jumlah);
                break;
            }
            case 3: {
                cout << "Masukkan ID Produk: ";
                int id;
                cin >> id;
                toko.cariProduk(id);
                break;
            }
            case 4: {
                toko.lihatKeranjang();
                break;
            }
            case 5: {
                cout << "Masukkan ID Produk: ";
                int id;
                cin >> id;
                toko.hapusDariKeranjang(id);
                break;
            }
            case 6: {
                cout << "Masukkan tujuan pengiriman (ID kota): ";
                int tujuan;
                cin >> tujuan;
                toko.bayar(tujuan);
                break;
            }
            case 7: {
                toko.lihatRiwayatTransaksi();
                break;
            }
            case 8: {
                cout << "Masukkan ID Transaksi: ";
                int idTransaksi;
                cin >> idTransaksi;
                toko.lihatDetailTransaksi(idTransaksi);
                break;
            }
            case 9:
                cout << "Terima kasih telah berbelanja!" << endl;
                return 0;
        }
    }
}
