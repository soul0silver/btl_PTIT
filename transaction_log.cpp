#include "transaction_log.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <filesystem>  
using namespace std;

void TransactionLog::record(const string &fromUser, int fromWalletId,
                            const string &toUser,   int toWalletId,
                            long long amount) {
    // Tạo timestamp
    auto now = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t(now);

    // Xây entry
    ostringstream ss;
    ss << ctime(&tt)
       << "Từ:     " << fromUser << " (Ví " << fromWalletId << ")\n"
       << "Đến:    " << toUser   << " (Ví " << toWalletId   << ")\n"
       << "Số điểm: " << amount   << " điểm\n"
       << "--------------------------\n";
    string entry = ss.str();

    // Ghi vào file ví nguồn
    {
        string fn = "trans_" + to_string(fromWalletId) + ".log";
        ofstream out(fn, ios::app);
        if (out) out << entry;
    }
    // Ghi vào file ví đích
    {
        string fn = "trans_" + to_string(toWalletId) + ".log";
        ofstream out(fn, ios::app);
        if (out) out << entry;
    }
}
