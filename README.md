# Hệ Thống Đăng Nhập, Đăng Ký và Quản Lý Ví Điểm Thưởng

## 1. Giới Thiệu Dự Án

Dự án này xây dựng một **hệ thống đăng nhập và đăng ký** tài khoản kết hợp với **quản lý ví điểm thưởng**, cho phép người dùng:

- Đăng ký và đăng nhập bảo mật (hỗ trợ mật khẩu tự sinh, đổi mật khẩu, OTP xác thực)
- Quản lý số điểm trong ví, chuyển và nhận điểm giữa các ví với cơ chế ghi lại lịch sử giao dịch
- Sao lưu và phục hồi dữ liệu tài khoản

Toàn bộ logic nghiệp vụ được triển khai bằng C++ với file-based storage và transaction log riêng cho từng ví.

## 2. Thành Viên Tham Gia

- **K24DTCN585 - Nguyễn Đạt**
  - Phụ trách: Đăng ký, đăng nhập, transaction log
- **K24DTCN596 - Ngô Quang Hiếu**
  - Phụ trách: Storage (sao lưu & phục hồi)
- **K24DTCN621 - Hồ Trí Phú**
  - Phụ trách: System & OTP Manager

## 3. Phân Tích & Đặc Tả Chức Năng

Chi tiết phân tích, quy trình nghiệp vụ và đặc tả chức năng đã được mô tả đầy đủ trong tài liệu dự án.

## 4. Cài Đặt & Biên Dịch

1. **Yêu cầu**
   - Trình biên dịch C++17 trở lên
2. **Clone project**
   git clone <https://github.com/soul0silver/btl_PTIT.git>
3. **Biên dịch**
    g++ user.cpp otp_manager.cpp storage.cpp transaction_log.cpp system.cpp main.cpp -o wallet_app
## 5. Hướng Dẫn Chạy & Sử Dụng
1. **Chạy ứng dụng**
   ./wallet_app
## Menu chính

1. **Đăng ký**  
2. **Đăng nhập**  
3. **Sao lưu dữ liệu**  
4. **Phục hồi dữ liệu**  
5. **Thoát**  

---

## Menu Người dùng

1. **Xem thông tin ví**  
   - Mã ví  
   - Số dư  
   - Lịch sử giao dịch  
2. **Đổi tên tài khoản**  
3. **Đổi mật khẩu**  
4. **Chuyển điểm** (OTP xác thực)  
5. **Đăng xuất**  

---

## Menu Quản trị viên

1. **Xem thông tin ví**
   - Mã ví  
   - Số dư  
   - Lịch sử giao dịch 
2. **Đăng ký tài khoản**  
3. **Đổi mật khẩu**  
4. **Chuyển điểm**  
5. **Xem danh sách người dùng**
6. **Đăng xuất**  
