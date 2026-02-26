# 🎓 Đồ án C: Hệ thống ATM & Cây nhị phân tìm kiếm (BST)

Đây là kho lưu trữ mã nguồn cho các đồ án lập trình C thuộc chương trình đào tạo ngành Công nghệ Thông tin - Đại học Bách Khoa, Đại học Đà Nẵng. Dự án bao gồm hai đề tài độc lập được tổ chức trong cùng một hệ thống quản lý phiên bản.

---

## 📂 Đề tài 701: Trình mô phỏng Hệ thống Giao dịch ATM
**Thư mục mã nguồn:** `/topic_701_atm/`

Dự án mô phỏng toàn diện vòng đời hoạt động của một máy ATM trong một ngày, từ lúc khởi động bởi nhân viên IT cho đến khi đóng máy. Sử dụng kỹ thuật mảng song song (parallel arrays) và thao tác Đọc/Ghi file (File I/O).

### ✨ Chức năng cốt lõi
* **Dành cho Nhân viên ngân hàng (IT Admin):**
    * Khởi động máy (Startup): Tự động đọc dữ liệu khách hàng (Account, PIN, Balance) từ file đầu vào.
    * Tắt máy (Shutdown): Yêu cầu mã bảo mật, sau đó kết xuất toàn bộ lịch sử giao dịch trong ngày ra file lưu trữ.
* **Dành cho Khách hàng (Customer):**
    * Xác thực bảo mật (Account Number & PIN).
    * Thực hiện giao dịch: Rút tiền, Gửi tiền, Xem số dư.
    * Kiểm soát rủi ro: Giới hạn số lần giao dịch tối đa trong ngày của mỗi tài khoản. Cập nhật số dư (balance) realtime sau mỗi giao dịch thành công.

---

## 🌳 Đề tài 602: Thư viện Cây nhị phân tìm kiếm (Binary Search Tree)
**Thư mục mã nguồn:** `/topic_602_bst/`

Xây dựng thư viện C/C++ cung cấp các thao tác nền tảng trên cấu trúc dữ liệu Cây nhị phân tìm kiếm (BST) và chương trình mô phỏng trực quan hoạt động của cấu trúc này.

### ✨ Các thao tác hỗ trợ
* Khởi tạo cây, Chèn (Insert) node mới.
* Tìm kiếm (Search) một giá trị trên cây.
* Xóa (Delete) node (xử lý đủ các trường hợp: node lá, node có 1 con, node có 2 con).
* Duyệt cây (Traversal): Pre-order, In-order, Post-order.

---
