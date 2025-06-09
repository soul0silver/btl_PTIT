
#include "system.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr))); //dùng để khởi tạo seed cho hàm rand(), 
                                                 //đảm bảo mỗi lần chạy chương trình dãy số ngẫu nhiên sinh ra sẽ khác nhau.
    System sys;
    sys.run(); // Chạy chương trình
    return 0;
}