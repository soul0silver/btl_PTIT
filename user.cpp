#include "user.h"
#include <functional>

using namespace std;

// Hàm băm mật khẩu người dùng
// Sử dụng std::hash để tạo giá trị hash từ chuỗi mật khẩu,
// sau đó chuyển đổi thành chuỗi để lưu trữ
string hashPassword(const string &pwd) {
    auto h = hash<string>{}(pwd);        // Tính hash của mật khẩu
    return to_string(h);                 // Chuyển hash thành chuỗi và trả về
}