#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

// Struct lưu trữ thông tin tài khoản người dùng
struct User {
    string username;     // Tên đăng nhập (unique)
    string passwordHash; // Hash của mật khẩu
    bool isAdmin;        // Quyền: true = admin, false = user thường
    int walletId;        // Mã định danh ví điểm
    long long balance;   // Số dư điểm trong ví
    bool tempPassword;   // Đánh dấu mật khẩu có phải do hệ thống tự sinh không
};

// Hàm băm mật khẩu (ví dụ sử dụng std::hash, không dùng cho môi trường production)
string hashPassword(const string &pwd);

#endif // USER_H
