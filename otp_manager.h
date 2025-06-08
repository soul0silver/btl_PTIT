#ifndef OTP_MANAGER_H
#define OTP_MANAGER_H

#include <string>

using namespace std;

// Lớp quản lý One-Time Password (OTP) để xác thực hai lớp
class OTPManager {
public:
    // Sinh mã OTP cho user, trả về chuỗi mã gồm 6 chữ số
    // Mã được lưu tạm để validate
    string generate(const string &user);

    // Kiểm tra mã OTP người dùng nhập vào
    // Trả về true nếu hợp lệ, false nếu sai hoặc hết hạn
    bool validate(const string &user, const string &input);
};

#endif // OTP_MANAGER_H
