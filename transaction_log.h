#ifndef TRANSACTION_LOG_H
#define TRANSACTION_LOG_H

#include <string>

using namespace std;

// Lớp quản lý ghi lại các giao dịch chuyển điểm thành file log riêng cho mỗi ví
class TransactionLog {
public:
    TransactionLog() = default; // Constructor mặc định

    // Ghi một giao dịch từ ví nguồn (fromWalletId) của người dùng fromUser
    // đến ví đích (toWalletId) của người dùng toUser với số điểm amount
    void record(const string &fromUser, int fromWalletId,
                const string &toUser,   int toWalletId,
                long long amount);

private:
    // Mỗi ví sẽ dùng file riêng dạng trans_<walletId>.log, nên không cần trường filename chung
};

#endif // TRANSACTION_LOG_H