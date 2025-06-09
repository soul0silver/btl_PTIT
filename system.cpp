#include "system.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <filesystem>
using namespace std;

// Constructor: tải dữ liệu người dùng và xác định walletId tiếp theo
System::System()
    : storage("users.dat"), nextWalletId(1), currentUser(nullptr) {
    users = storage.load();
    for(const auto &u: users) {
        nextWalletId = max(nextWalletId, u.walletId + 1);
    }
}

// Vòng lặp chính hiển thị menu chính
void System::run() {
    while(true) {
        cout << "--- Menu Chính ---\n";
        cout << "1. Đăng ký\n2. Đăng nhập\n3. Sao lưu dữ liệu\n4. Phục hồi dữ liệu\n5. Thoát\nChọn: ";
        int c; cin >> c;
        switch(c) {
            case 1: doRegister(); break;
            case 2: doLogin(); break;
            case 3: storage.backup(); break;
            case 4: storage.restore(); break;
            default: return;
        }
    }
}

// Đăng ký tài khoản mới, nhập thông tin và khởi tạo ví
void System::doRegister() {
    string uname; cout << "Nhập tên đăng nhập: "; cin >> uname;
    if(findUser(uname)) { cout << "Người dùng đã tồn tại!\n"; return; }
    cout << "Tự động tạo mật khẩu? (1=có): "; int a; cin >> a;
    string pwd; bool isTemp = false;
    if(a == 1) {
        pwd = to_string(rand() % 900000 + 100000);
        isTemp = true;
        cout << "Mật khẩu được tạo: " << pwd << "\n";
    } else {
        cout << "Nhập mật khẩu: "; cin >> pwd;
    }
    cout << "Là quản trị viên? (1=có): "; cin >> a;
    cout << "Nhập số tiền ví: "; int v; cin >> v;
    if (v < 0){
        cout << "Số tiền ví không hợp lệ\n";
        return;
    }
    // Tạo user và lưu
    User u{uname, hashPassword(pwd), a==1, nextWalletId++, v, isTemp};
    users.push_back(u);
    storage.save(users);
    cout << "Đăng ký thành công với số dư ban đầu" << " " << v << " " << "điểm. Mã ví của bạn là " << u.walletId << "\n";
}

// Đăng nhập, kiểm tra mật khẩu và phân quyền
void System::doLogin() {
    string uname; cout << "Tên đăng nhập: "; cin >> uname;
    User *u = findUser(uname);
    if(!u) { cout << "Không tìm thấy người dùng.\n"; return; }
    string pwd; cout << "Mật khẩu: "; cin >> pwd;
    if(u->passwordHash != hashPassword(pwd)) { cout << "Sai thông tin đăng nhập.\n"; return; }
    // Yêu cầu đổi mật khẩu tạm
    if(u->tempPassword) {
        cout << "Vui lòng đổi mật khẩu tạm thời: "; string np; cin >> np;
        u->passwordHash = hashPassword(np);
        u->tempPassword = false;
        storage.save(users);
    }
    currentUser = u;
    cout << "Chào mừng, " << u->username << "!\n";
    // Chạy menu theo quyền
    if (currentUser->isAdmin)
        adminMenu();
    else
        userMenu();
}

// Menu cho user thường
void System::userMenu() {
    int c;
    do {
        cout << "--- Menu Người dùng ---\n";
        cout << "1. Xem thông tin ví\n2. Đổi tên\n3. Đổi mật khẩu\n4. Chuyển điểm\n5. Đăng xuất\nChọn: ";
        cin >> c;
        switch(c) {
            case 1: doShowWallet(); break;
            case 2: doChangeName(); break;
            case 3: doChangePassword(); break;
            case 4: doTransfer(); break;
        }
    } while(c != 5);
}

// Đổi mật khẩu với xác thực OTP
void System::doChangePassword() {
    cout << "Nhập mật khẩu mới: "; string np; cin >> np;
    currentUser->passwordHash = hashPassword(np);
    cout << "Đang tạo OTP...\n";
    otp.generate(currentUser->username);
    cout << "Nhập mã OTP đã nhận: "; string code; cin >> code;
    if(!otp.validate(currentUser->username, code)) { cout << "OTP không hợp lệ.\n"; return; }
    storage.save(users);
    cout << "Đổi mật khẩu thành công.\n";
}

// Chuyển điểm giữa các ví, ghi log giao dịch
void System::doTransfer() {
    cout << "Nhập mã ví đích: "; int wid; cin >> wid;
    User *to = nullptr; for(auto &u: users) if(u.walletId == wid) to = &u;
    if(!to) { cout << "Không tìm thấy ví.\n"; return; }
    cout << "Số điểm: "; long long amt; cin >> amt;
    if(currentUser->balance < amt) { cout << "Số dư không đủ.\n"; return; }
    cout << "Đang tạo OTP...\n";
    otp.generate(currentUser->username);
    cout << "Nhập mã OTP đã nhận: "; string code; cin >> code;
    if(!otp.validate(currentUser->username, code)) { cout << "OTP không hợp lệ.\n"; return; }
    long long balA = currentUser->balance, balB = to->balance;
    currentUser->balance -= amt;
    to->balance += amt;
    storage.save(users);
    tlog.record(currentUser->username, currentUser->walletId,
                to->username, to->walletId, amt);
    cout << "Chuyển điểm thành công.\n";
}

// Menu dành cho admin
void System::adminMenu(){
    int c;
    do {
        cout << "--- Menu Quản trị viên ---\n";
        cout << "1. Xem thông tin ví\n2. Đăng ký tài khoản\n3. Đổi mật khẩu\n4. Chuyển điểm\n5. Xem danh sách người dùng\n6. Đăng xuất\nChọn: ";
        cin >> c;
        switch(c) {
            case 1: doShowWallet(); break;
            case 2: doRegister(); break;
            case 3: doChangePassword(); break;
            case 4: doTransfer(); break;
            case 5: listUsers(); break;
        }
    } while(c != 6);
}

// Hiển thị thông tin ví và lịch sử giao dịch riêng
void System::doShowWallet() {
    cout << "Tên người dùng: " << currentUser->username << ", Mã ví: " << currentUser->walletId << ", Số dư: " << currentUser->balance << "\n";
    string fn = "trans_" + to_string(currentUser->walletId) + ".log";
    ifstream in(fn);
    cout << "\n===== LỊCH SỬ GIAO DỊCH =====\n";
    if (!in) {
        cout << "Chưa có giao dịch nào.\n";
    } else {
        string line;
        while (getline(in, line)) {
            cout << line << "\n";
        }
    }
    cout << "===========================\n";
}

// Đổi tên với OTP xác thực
void System::doChangeName() {
    cout << "Nhập tên mới: "; string newName; cin >> newName;
    if(findUser(newName)) {
        cout << "Tên này đã tồn tại.\n";
        return;
    }
    currentUser->username = newName;
    cout << "Đang tạo OTP...\n";
    otp.generate(currentUser->username);
    cout << "Nhập mã OTP đã nhận: "; string code; cin >> code;
    if(!otp.validate(currentUser->username, code)) { cout << "OTP không hợp lệ.\n"; return; }
    storage.save(users);
    cout << "Đổi tên thành công.\n";
}

// Danh sách tất cả người dùng (admin)
void System::listUsers() {
    cout << "Danh sách người dùng:\n";
    for(const auto &u: users) cout << u.username << " (Ví " << u.walletId << ") Số dư=" << u.balance << " Admin=" << u.isAdmin << "\n";
}

// Tìm user theo username
User* System::findUser(const string &uname) {
    for(auto &u: users) if(u.username == uname) return &u;
    return nullptr;
}