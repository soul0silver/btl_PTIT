#ifndef STORAGE_H
#define STORAGE_H

#include "user.h"
#include <vector>
#include <string>

using namespace std;

// Lớp Storage quản lý lưu trữ dữ liệu User:
// - load(): đọc danh sách người dùng từ file
// - save(): ghi danh sách người dùng vào file
// - backup(): tạo bản sao lưu file dữ liệu
// - restore(): phục hồi từ bản sao lưu
class Storage {
public:
    // Constructor nhận tên file lưu dữ liệu
    explicit Storage(const string &filename);

    // Đọc dữ liệu người dùng từ file, trả về vector<User>
    vector<User> load();

    // Ghi dữ liệu người dùng xuống file, ghi đè nội dung cũ
    void save(const vector<User> &users);

    // Tạo bản sao lưu file dữ liệu (filename.bak)
    void backup();

    // Phục hồi file dữ liệu từ bản sao lưu (filename.bak)
    void restore();

private:
    string filename;  // Tên file chứa dữ liệu người dùng
};

#endif // STORAGE_H
