#include "otp_manager.h"
#include <random>
#include <unordered_map>
#include <iostream>

using namespace std;

// Bản đồ tạm lưu OTP đã sinh cho từng user
static unordered_map<string, string> otpMap;

// Sinh mã OTP 6 chữ số cho user và lưu vào otpMap
string OTPManager::generate(const string &user) {
    random_device rd;            // Thiết bị sinh số ngẫu nhiên
    mt19937 gen(rd());           // Trình sinh số ngẫu nhiên
    uniform_int_distribution<> dis(100000, 999999);  // Khoảng [100000,999999]
    string code = to_string(dis(gen));

    // Lưu mã OTP cho user
    otpMap[user] = code;

    // In debug ra console (thực tế có thể gửi qua SMS/email)
    cout << "[DEBUG] Mã OTP của " << user << ": " << code << endl;
    return code;
}

// Kiểm tra OTP người dùng nhập so với otpMap
bool OTPManager::validate(const string &user, const string &input) {
    auto it = otpMap.find(user);
    if (it != otpMap.end() && it->second == input) {
        otpMap.erase(it);  // Xóa OTP sau khi dùng
        return true;
    }
    return false;
}
