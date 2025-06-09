#ifndef SYSTEM_H
#define SYSTEM_H

#include "user.h"
#include "otp_manager.h"
#include "storage.h"
#include "transaction_log.h"
#include <vector>

using namespace std;

class System {
public:
    System();
    void run();

private:
    vector<User> users;
    Storage storage;
    OTPManager otp;
    int nextWalletId;
    User *currentUser;
    TransactionLog tlog;

    void doRegister();      // Đăng ký tài khoản mới
    void doLogin();         // Đăng nhập
    void userMenu();        // Menu cho user thường
    void adminMenu();       // Menu cho admin
    void doShowWallet();    // Hiển thị thông tin ví và lịch sử giao dịch
    void doChangeName();    // Thay đổi tên đăng nhập
    void doChangePassword();// Thay đổi mật khẩu
    void doTransfer();      // Chuyển điểm giữa các ví
    void listUsers();       // Danh sách tất cả người dùng (admin)
    User* findUser(const string &uname); // Tìm user theo username
};

#endif // SYSTEM_H

