#include "storage.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor nhận tên file lưu trữ dữ liệu người dùng
Storage::Storage(const string &f)
    : filename(f) {}

// Đọc danh sách người dùng từ file, trả về vector<User>
vector<User> Storage::load() {
    vector<User> users;
    ifstream in(filename);             // Mở file để đọc
    if (!in) return users;             // Nếu không mở được, trả về rỗng

    User u;
    // Đọc từng record của User theo định dạng: username passwordHash isAdmin walletId balance tempPassword
    while (in >> u.username >> u.passwordHash >> u.isAdmin
              >> u.walletId >> u.balance >> u.tempPassword) {
        users.push_back(u);
    }
    return users;
}

// Ghi đè danh sách người dùng lên file
void Storage::save(const vector<User> &users) {
    ofstream out(filename, ios::trunc);  // Mở file ở chế độ xóa nội dung cũ
    for (const auto &u : users) {
        out << u.username     << ' '
            << u.passwordHash << ' '
            << u.isAdmin      << ' '
            << u.walletId     << ' '
            << u.balance      << ' '
            << u.tempPassword<< '\n';
    }
}

// Tạo bản sao lưu file dữ liệu: filename.bak
void Storage::backup() {
    string backupFile = filename + ".bak";
    ifstream src(filename, ios::binary);  // Mở file nguồn (binary)
    ofstream dst(backupFile, ios::binary); // Mở file đích
    dst << src.rdbuf();                    // Sao chép toàn bộ nội dung
    cout << "Đã tạo bản sao lưu tại " << backupFile << endl;
}

// Phục hồi file dữ liệu từ bản sao lưu: filename.bak
void Storage::restore() {
    string backupFile = filename + ".bak";
    ifstream src(backupFile, ios::binary); // Mở file backup
    ofstream dst(filename, ios::binary);   // Mở file gốc (ghi đè)
    dst << src.rdbuf();                    // Phục hồi nội dung
    cout << "Đã phục hồi dữ liệu từ " << backupFile << endl;
}
