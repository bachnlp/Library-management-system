
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// ===== Cấu trúc dữ liệu =====
struct Book {
    string isbn, title, author, category, status;
    int year;
    Book* next;
// ===== Khai báo hàm tạo =====
    Book(string i = "", string t = "", string a = "", string c = "", string s = "available", int y = 0)
        : isbn(i), title(t), author(a), category(c), status(s), year(y), next(nullptr) {}
};

struct Student {
    string id, password, name;
    Student* next;
// ===== Khai báo hàm tạo =====
    Student(string i = "", string p = "", string n = "")
        : id(i), password(p), name(n), next(nullptr) {}
};

struct Staff {
    string id, name, username, password, email, phone, role, status;
    Staff* next;
// ===== Khai báo hàm tạo =====
    Staff(string i = "", string n = "", string u = "", string p = "", string e = "", string ph = "", string r = "", string s = "")
        : id(i), name(n), username(u), password(p), email(e), phone(ph), role(r), status(s), next(nullptr) {}
};

struct BorrowRecord {
    string userID, isbn, dueDate;
    BorrowRecord* next;
// ===== Khai báo hàm tạo =====
    BorrowRecord(string u = "", string i = "", string d = "")
        : userID(u), isbn(i), dueDate(d), next(nullptr) {}
};

// ===== Hash Table cho Book =====
class BookHashTable {
private:
    static const int TABLE_SIZE = 19;
    vector<Book*> table;
// ===== Hàm băm =====
    int hashFunction(const string& key) const {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }

public:
// ===== Hàm tạo(Constructor) =====
    BookHashTable() {
        size_t i = 0;
        table.resize(TABLE_SIZE);
        while (i < TABLE_SIZE) {
            table[i] = nullptr;
            ++i;
        }
    }

    void insert(const string& isbn, Book* book) {
        int index = hashFunction(isbn);
        book->next = table[index];
        table[index] = book;
    }

    Book* search(const string& isbn) {
        int index = hashFunction(isbn);
        Book* current = table[index];
        while (current != nullptr) {
            if (current->isbn == isbn) return current;
            current = current->next;
        }
        return nullptr;
    }

    void display() const {
        size_t i = 0;
        while (i < TABLE_SIZE) {
            Book* current = table[i];
            while (current != nullptr) {
                cout << "ISBN: " << current->isbn << ", Title: " << current->title << ", Status: " << current->status << endl;
                current = current->next;
            }
            ++i;
        }
    }

    void remove(const string& isbn) {
        int index = hashFunction(isbn);
        Book* current = table[index];
        Book* prev = nullptr;

        while (current != nullptr) {
            if (current->isbn == isbn) {
                if (prev != nullptr) prev->next = current->next;
                else table[index] = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void createBook(const string& isbn, const string& title, const string& author, const string& category, const string& status, int year) {
        if (!search(isbn)) {
            insert(isbn, new Book(isbn, title, author, category, status, year));
            cout << "[THANH CONG] Da them sach: " << title << endl;
        } else {
            cerr << "[THAT BAI] Sach voi ISBN " << isbn << " da ton tai!\n";
        }
    }

    void readBook(const string& isbn) {
        Book* book = search(isbn);
        if (book != nullptr) {
            cout << "ISBN: " << book->isbn << ", Title: " << book->title << ", Author: " << book->author
                 << ", Category: " << book->category << ", Status: " << book->status
                 << ", Year: " << book->year << endl;
        } else {
            cerr << "[CANH BAO] Khong tim thay sach voi ISBN " << isbn << "!\n";
        }
    }

    void updateBook(const string& isbn, const string& title, const string& author, const string& category, const string& status, int year) {
        Book* book = search(isbn);
        if (book != nullptr) {
            book->title = title;
            book->author = author;
            book->category = category;
            book->status = status;
            book->year = year;
            cout << "[THANH CONG] Da cap nhat thong tin sach: " << title << endl;
        } else {
            cerr << "[THAT BAI] Khong tim thay sach voi ISBN " << isbn << " de cap nhat!\n";
        }
    }

    void deleteBook(const string& isbn) {
        remove(isbn);
        cout << "[THANH CONG] Da xoa sach voi ISBN " << isbn << endl;
    }

    // ===== Sắp xếp sách theo ISBN sử dụng Bubble Sort =====
    void sortByISBN() const {
        // Thu thập tất cả sách vào một vector
        vector<Book*> bookList;
        for (size_t i = 0; i < TABLE_SIZE; ++i) {
            Book* current = table[i];
            while (current != nullptr) {
                bookList.push_back(current);
                current = current->next;
            }
        }

        // thuật toán bubble sort, dựa trên isbn
        size_t n = bookList.size();
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (bookList[j]->isbn > bookList[j + 1]->isbn) {
                    swap(bookList[j], bookList[j + 1]);
                }
            }
        }

        // Hiển thị danh sách đã sắp xếp
        if (bookList.empty()) {
            cerr << "[CANH BAO] Khong co sach nao trong thu vien!\n";
        } else {
            cout << "[THANH CONG] Danh sach sach duoc sap xep theo ISBN:\n";
            for (Book* book : bookList) {
                cout << "ISBN: " << book->isbn << ", Title: " << book->title << ", Status: " << book->status << endl;
            }
        }
    }

    static const int getTableSize() { return TABLE_SIZE; }

    const vector<Book*>& getTable() const { return table; }

// ===== Hàm hủy(Destructor) =====
    ~BookHashTable() {
        size_t i = 0;
        while (i < TABLE_SIZE) {
            Book* current = table[i];
            while (current != nullptr) {
                Book* temp = current;
                current = current->next;
                delete temp;
            }
            ++i;
        }
    }
};

// ===== Hash Table cho Student =====
class StudentHashTable {
private:
    static const int TABLE_SIZE = 19;
    vector<Student*> table;

    int hashFunction(const string& key) const {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }

public:
// ===== Hàm tạo(Constructor) =====
    StudentHashTable() {
        size_t i = 0;
        table.resize(TABLE_SIZE);
        while (i < TABLE_SIZE) {
            table[i] = nullptr;
            ++i;
        }
    }

    void insert(const string& id, Student* student) {
        int index = hashFunction(id);
        student->next = table[index];
        table[index] = student;
    }

    Student* search(const string& id) {
        int index = hashFunction(id);
        Student* current = table[index];
        while (current != nullptr) {
            if (current->id == id) return current;
            current = current->next;
        }
        return nullptr;
    }

    void display() const {
        size_t i = 0;
        while (i < TABLE_SIZE) {
            Student* current = table[i];
            while (current != nullptr) {
                cout << "ID: " << current->id << ", Name: " << current->name << endl;
                current = current->next;
            }
            ++i;
        }
    }

    void remove(const string& id) {
        int index = hashFunction(id);
        Student* current = table[index];
        Student* prev = nullptr;

        while (current != nullptr) {
            if (current->id == id) {
                if (prev != nullptr) prev->next = current->next;
                else table[index] = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void createStudent(const string& id, const string& password, const string& name) {
        if (!search(id)) {
            insert(id, new Student(id, password, name));
            cout << "[THANH CONG] Da them sinh vien: " << name << endl;
        } else {
            cerr << "[THAT BAI] Sinh vien voi ID " << id << " da ton tai!\n";
        }
    }

    static const int getTableSize() { return TABLE_SIZE; }

    const vector<Student*>& getTable() const { return table; }

// ===== Hàm hủy(Destructor) =====
    ~StudentHashTable() {
        size_t i = 0;
        while (i < TABLE_SIZE) {
            Student* current = table[i];
            while (current != nullptr) {
                Student* temp = current;
                current = current->next;
                delete temp;
            }
            ++i;
        }
    }
};

// ===== Hash Table cho Staff =====
class StaffHashTable {
private:
    static const int TABLE_SIZE = 19;
    vector<Staff*> table;

    int hashFunction(const string& key) const {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }

public:
// ===== Hàm tạo(Constructor) =====
    StaffHashTable() {
        size_t i = 0;
        table.resize(TABLE_SIZE);
        while (i < TABLE_SIZE) {
            table[i] = nullptr;
            ++i;
        }
    }

    void insert(const string& id, Staff* staff) {
        int index = hashFunction(id);
        staff->next = table[index];
        table[index] = staff;
    }

    Staff* search(const string& id) {
        int index = hashFunction(id);
        Staff* current = table[index];
        while (current != nullptr) {
            if (current->id == id) return current;
            current = current->next;
        }
        return nullptr;
    }

    void display() const {
        size_t i = 0;
        while (i < TABLE_SIZE) {
            Staff* current = table[i];
            while (current != nullptr) {
                cout << "ID: " << current->id << ", Name: " << current->name << ", Role: " << current->role << ", Status: " << current->status << endl;
                current = current->next;
            }
            ++i;
        }
    }

    void remove(const string& id) {
        int index = hashFunction(id);
        Staff* current = table[index];
        Staff* prev = nullptr;

        while (current != nullptr) {
            if (current->id == id) {
                if (prev != nullptr) prev->next = current->next;
                else table[index] = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void createStaff(const string& id, const string& name, const string& username, const string& password, const string& email, const string& phone, const string& role) {
        if (!search(id)) {
            insert(id, new Staff(id, name, username, password, email, phone, role, "active"));
            cout << "[THANH CONG] Da them nhan vien: " << name << endl;
        } else {
            cerr << "[THAT BAI] Nhan vien voi ID " << id << " da ton tai!\n";
        }
    }

    static const int getTableSize() { return TABLE_SIZE; }

    const vector<Staff*>& getTable() const { return table; }

// ===== Hàm hủy(Destructor) =====
    ~StaffHashTable() {
        size_t i = 0;
        while (i < TABLE_SIZE) {
            Staff* current = table[i];
            while (current != nullptr) {
                Staff* temp = current;
                current = current->next;
                delete temp;
            }
            ++i;
        }
    }
};

// ===== Quản lý Mượn Trả Sách =====
class BorrowManager {
private:
    static const int TABLE_SIZE = 19;
    vector<BorrowRecord*> table;

    int hashFunction(const string& userID) const {
        int sum = 0;
        for (char c : userID) sum += c;
        return sum % TABLE_SIZE;
    }

    string getCurrentTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        ostringstream oss;
        oss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
// ===== Hàm tạo(Constructor) =====
    BorrowManager() {
        size_t i = 0;
        table.resize(TABLE_SIZE);
        while (i < TABLE_SIZE) {
            table[i] = nullptr;
            ++i;
        }
    }

    void borrowBook(BookHashTable& books, const string& userID, const string& isbn, const string& dueDate) {
        Book* book = books.search(isbn);
        if (book != nullptr) {
            if (book->status == "issued") {
                cout << "[THAT BAI] Sach nay da duoc muon.\n";
            } else if (book->status == "available") {
                book->status = "issued";
                cout << "[THANH CONG] Da muon sach " << book->title << endl;
                saveBorrowRecordToCSV(userID, isbn, dueDate, getCurrentTime());
            }
        } else {
            cerr << "[THAT BAI] Sach khong ton tai.\n";
        }
    }

    void returnBook(BookHashTable& books, const string& userID, const string& isbn) {
        Book* book = books.search(isbn);
        if (book != nullptr) {
            if (book->status == "available") {
                cout << "[THAT BAI] Sach nay chua co ai muon.\n";
            } else if (book->status == "issued") {
                book->status = "available";
                cout << "[THANH CONG] Da tra sach.\n";
            }
        } else {
            cerr << "[THAT BAI] Sach khong ton tai.\n";
        }
    }

    void saveBorrowRecordToCSV(const string& userID, const string& isbn, const string& dueDate, const string& borrowTime) {
        string filename = "borrowData.csv";
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            if (file.tellp() == 0) {
                file << "userID,isbn,dueDate,borrowTime\n";
            } file << userID << "," << isbn << "," << dueDate << "," << borrowTime << "\n";
            file.close();
            cerr << "[THANH CONG] Da luu thong tin muon sach.\n";
        } else cerr << "[THAT BAI] Thong tin muon sach chua duoc luu.\n";
    }
    
    void displayAllBorrowedBooks() {
        string fileName = "borrowData.csv";
        ifstream file(fileName);
        bool found = false;
        if(file.is_open()) {
            string line;
            getline(file, line);
            cout << "Danh dach sach da muon: \n";
            while(getline(file, line)) {
                if(line == "userID,isbn,dueDate,borrowTime") continue;
                stringstream ss(line);
                string userID, isbn, dueDate, borrowTime;
                getline(ss, userID, ',');
                getline(ss, isbn, ',');
                getline(ss, dueDate, ',');
                getline(ss, borrowTime, ',');
                if(!userID.empty() && !isbn.empty()) {
                    found = true;
                    cout << "ID: " << userID << ", isbn:" << isbn << ", dueDate: " << dueDate << ", Borrow time: " << borrowTime << endl;
                }
            } file.close();
            if (!found) cerr << "[CANH BAO] Khong co sach duoc muon.\n";
        } else cerr << "[THAT BAI] Du lieu khong duoc luu.\n";
    }
// ===== Hàm hủy(Destructor) =====
    ~BorrowManager() {
        size_t i = 0;
        while (i < TABLE_SIZE) {
            BorrowRecord* current = table[i];
            while (current != nullptr) {
                BorrowRecord* temp = current;
                current = current->next;
                delete temp;
            } ++i;
        }
    }
};

// ===== Đọc dữ liệu từ CSV =====
void loadBooks(BookHashTable& books, const string& filename) {
    ifstream file("Book.csv");
    if (!file.is_open()) {
        cerr << "[CANH BAO] Khong the mo file " << filename << "!\n";
        return;
    }

    string line;
    getline(file, line); // Bo header
    while (getline(file, line)) {
        stringstream ss(line);
        string isbn, title, author, category, status;
        int year = 0;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, category, ',');
        getline(ss, status, ',');
        ss >> year;

        if (!books.search(isbn)) {
            books.insert(isbn, new Book(isbn, title, author, category, status, year));
        }
    }
    file.close();
}

void loadStudents(StudentHashTable& students, const string& filename) {
    ifstream file("Student.csv");
    if (!file.is_open()) {
        cerr << "[CANH BAO] Khong the mo file " << filename << "!\n";
        return;
    }

    string line;
    getline(file, line); // Bo header
    while (getline(file, line)) {
        stringstream ss(line);
        string id, password, name;

        getline(ss, id, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');

        if (!students.search(id)) {
            students.insert(id, new Student(id, password, name));
        }
    }
    file.close();
}

void loadStaff(StaffHashTable& staff, const string& filename) {
    ifstream file("Staff.csv");
    if (!file.is_open()) {
        cout << "[CANH BAO] Khong the mo file " << filename << "!\n";
        return;
    }

    string line;
    getline(file, line); // Bo header
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, username, password, email, phone, role, status;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, role, ',');
        getline(ss, status, ',');

        if (!staff.search(id)) {
            staff.insert(id, new Staff(id, name, username, password, email, phone, role, status));
        }
    }
    file.close();
}

// ===== Hệ thống đăng nhập =====
class LoginSystem {
private:
    string loggedInUserID;
    string userRole; // "student", "staff", or "admin"

public:
    LoginSystem() : loggedInUserID(""), userRole("") {}

    bool login(StudentHashTable& students, StaffHashTable& staff) {
        int roleChoice;
        string id, password;

        cout << "Chon quyen truy cap:\n";
        cout << "1. Sinh vien\n";
        cout << "2. Nhan vien\n";
        cout << "3. Admin\n";
        cout << "Nhap lua chon: ";
        cin >> roleChoice;
        cin.ignore();

        if (roleChoice != 1 && roleChoice != 2 && roleChoice != 3) {
            cerr << "[THAT BAI] Lua chon khong hop le!\n";
            return false;
        }

        cout << "Nhap ID: ";
        getline(cin, id);
        cout << "Nhap mat khau: ";
        getline(cin, password);

        if (roleChoice == 1) {
            Student* student = students.search(id);
            if (student && student->password == password) {
                loggedInUserID = id;
                userRole = "student";
                cout << "[THANH CONG] Dang nhap voi vai tro sinh vien!\n";
                return true;
            }
        } else if (roleChoice == 2) {
            Staff* staffMember = staff.search(id);
            if (staffMember && staffMember->password == password) {
                loggedInUserID = id;
                userRole = "staff";
                cout << "[THANH CONG] Dang nhap voi vai tro nhan vien!\n";
                return true;
            }
        } else if (roleChoice == 3) {
            Staff* staffMember = staff.search(id);
            if (staffMember && staffMember->password == password && (id == "ST001" || id == "ST004")) {
                loggedInUserID = id;
                userRole = "admin";
                cout << "[THANH CONG] Dang nhap voi vai tro admin!\n";
                return true;
            }
        }

        cout << "[THAT BAI] ID hoac mat khau khong chinh xac!\n";
        return false;
    }

    string getLoggedInUserID() const { return loggedInUserID; }
    string getUserRole() const { return userRole; }
};

// ===== Hàm lưu dữ liệu =====
void saveData(const BookHashTable& books, const StudentHashTable& students, const StaffHashTable& staff, const BorrowManager& borrowManager) {
    // Lưu Book
    ofstream bookFile("Book.csv");
    if (bookFile.is_open()) {
        bookFile << "isbn,title,author,category,status,year\n";
        size_t i = 0;
        const vector<Book*>& bookTable = books.getTable();
        while (i < BookHashTable::getTableSize()) {
            Book* current = bookTable[i];
            while (current != nullptr) {
                bookFile << current->isbn << "," << current->title << "," << current->author << "," << current->category << ","
                         << current->status << "," << current->year << "\n";
                current = current->next;
            }
            ++i;
        }
        bookFile.close();
    } else {
        cout << "[THAT BAI] Du lieu chua duoc luu!\n";
    }

    // Lưu Student
    ofstream studentFile("Student.csv");
    if (studentFile.is_open()) {
        studentFile << "id,password,name\n";
        size_t i = 0;
        const vector<Student*>& studentTable = students.getTable();
        while (i < StudentHashTable::getTableSize()) {
            Student* current = studentTable[i];
            while (current != nullptr) {
                studentFile << current->id << "," << current->password << "," << current->name << "\n";
                current = current->next;
            }
            ++i;
        }
        studentFile.close();
    } else {
        cout << "[THAT BAI] Du lieu chua duoc luu!\n";
    }

    // Lưu Staff
    ofstream staffFile("Staff.csv");
    if (staffFile.is_open()) {
        staffFile << "id,name,username,password,email,phone,role,status\n";
        size_t i = 0;
        const vector<Staff*>& staffTable = staff.getTable();
        while (i < StaffHashTable::getTableSize()) {
            Staff* current = staffTable[i];
            while (current != nullptr) {
                staffFile << current->id << "," << current->name << "," << current->username << "," << current->password << ","
                          << current->email << "," << current->phone << "," << current->role << "," << current->status << "\n";
                current = current->next;
            }
            ++i;
        }
        staffFile.close();
    } else {
        cout << "[THAT BAI] Du lieu chua duoc luu!\n";
    }
}

// ===== Menu cho sinh vien =====
void showStudentMenu() {
    cout << "\n=== QUAN LY THU VIEN - [SINH VIEN] ===\n";
    cout << "1. Xem danh sach sach\n";
    cout << "2. Muon sach\n";
    cout << "3. Tra sach\n";
    cout << "4. Tra cuu thong tin sach\n";
    cout << "5. Thoat\n";
    cout << "Chon chuc nang: ";
}

// ===== Menu cho nhan vien =====
void showStaffMenu() {
    cout << "\n=== QUAN LY THU VIEN - [NHAN VIEN] ===\n";
    cout << "1. Xem danh sach sach\n";
    cout << "2. Xem danh sach sach da muon\n";
    cout << "3. Them sach moi\n";
    cout << "4. Tra cuu thong tin sach\n";
    cout << "5. Cap nhat thong tin sach\n";
    cout << "6. Xoa sach\n";
    cout << "7. Sap xep sach \n"; 
    cout << "8. Thoat\n";
    cout << "Chon chuc nang: ";
}

// ===== Menu cho admin =====
void showAdminMenu() {
    cout << "\n=== QUAN LY THU VIEN - [ADMIN] ===\n";
    cout << "1. Xem sinh vien\n";
    cout << "2. Xem nhan vien\n";
    cout << "3. Them sinh vien\n";
    cout << "4. Them nhan vien\n";
    cout << "5. Xoa sinh vien\n";
    cout << "6. Xoa nhan vien\n";
    cout << "7. Thoat\n";
    cout << "Chon chuc nang: ";
}

// ===== Chuong trinh chinh =====
int main() {
    BookHashTable books;
    StudentHashTable students;
    StaffHashTable staff;
    BorrowManager borrowManager;
    LoginSystem loginSystem;

    loadBooks(books, "Book.csv");
    loadStudents(students, "Student.csv");
    loadStaff(staff, "Staff.csv");

    // Yeu cau dang nhap truoc
    while (!loginSystem.login(students, staff)) {
        cout << "Vui long thu lai hoac thoat!\n";
    }

    string userRole = loginSystem.getUserRole();
    string userID = loginSystem.getLoggedInUserID();
    string isbn, dueDate, title, author, category, status;
    int year;
    string id, password, name, username, email, phone, role;

    if (userRole == "student") {
        int choice;
        do {
            showStudentMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: // Xem danh sach sach
                    books.display();
                    break;
                case 2: // Muon sach
                    cout << "Nhap ISBN sach: ";
                    getline(cin, isbn);
                    cout << "Nhap han tra (YYYY-MM-DD): ";
                    getline(cin, dueDate);
                    borrowManager.borrowBook(books, userID, isbn, dueDate);
                    saveData(books, students, staff, borrowManager);
                    break;
                case 3: // Tra sach
                    cout << "Nhap ISBN sach: ";
                    getline(cin, isbn);
                    borrowManager.returnBook(books, userID, isbn);
                    saveData(books, students, staff, borrowManager);
                    break;
                case 4: // Xem thong tin sach
                    cout << "Nhap ISBN de tra cuu: ";
                    getline(cin, isbn);
                    books.readBook(isbn);
                    break;
                case 5: // Thoat
                    cout << "Thoat chuong trinh!\n";
                    saveData(books, students, staff, borrowManager);
                    break;
                default:
                    cout << "[THAT BAI] Lua chon khong hop le.\n";
            }
        } while (choice != 5);
    } else if (userRole == "staff") {
        int choice;
        do {
            showStaffMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: // Xem danh sach sach
                    books.display();
                    break;
                case 2: // Xem tat ca sach da muon
                    borrowManager.displayAllBorrowedBooks();
                    break;
                case 3: // Them sach moi
                    cout << "Nhap ISBN: ";
                    getline(cin, isbn);
                    cout << "Nhap tieu de: ";
                    getline(cin, title);
                    cout << "Nhap tac gia: ";
                    getline(cin, author);
                    cout << "Nhap danh muc: ";
                    getline(cin, category);
                    cout << "Nhap trang thai: ";
                    getline(cin, status);
                    cout << "Nhap nam xuat ban: ";
                    cin >> year;
                    cin.ignore();
                    books.createBook(isbn, title, author, category, status, year);
                    saveData(books, students, staff, borrowManager);
                    break;
                case 4: // Xem thong tin sach
                    cout << "Nhap ISBN de tra cuu: ";
                    getline(cin, isbn);
                    books.readBook(isbn);
                    break;
                case 5: // Cap nhat thong tin sach
                    cout << "Nhap ISBN de cap nhat: ";
                    getline(cin, isbn);
                    cout << "Nhap tieu de moi: ";
                    getline(cin, title);
                    cout << "Nhap tac gia moi: ";
                    getline(cin, author);
                    cout << "Nhap danh muc moi: ";
                    getline(cin, category);
                    cout << "Nhap trang thai moi: ";
                    getline(cin, status);
                    cout << "Nhap nam xuat ban moi: ";
                    cin >> year;
                    cin.ignore();
                    books.updateBook(isbn, title, author, category, status, year);
                    saveData(books, students, staff, borrowManager);
                    break;
                case 6: // Xoa sach
                    cout << "Nhap ISBN de xoa: ";
                    getline(cin, isbn);
                    books.deleteBook(isbn);
                    saveData(books, students, staff, borrowManager);
                    break;
                case 7: // Sắp xếp sách theo ISBN
                    books.sortByISBN();
                    break;
                case 8: // Thoat
                    cout << "Thoat chuong trinh!\n";
                    saveData(books, students, staff, borrowManager);
                    break;
                default:
                    cout << "[THAT BAI] Lua chon khong hop le.\n";
            }
        } while (choice != 8);
    } else if (userRole == "admin") {
        int choice;
        do {
            showAdminMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: // Xem sinh vien
                    students.display();
                    break;
                case 2: // Xem nhan vien
                    staff.display();
                    break;
                case 3: // Them sinh vien
                    cout << "Nhap ID: ";
                    getline(cin, id);
                    cout << "Nhap mat khau: ";
                    getline(cin, password);
                    cout << "Nhap ten: ";
                    getline(cin, name);
                    students.createStudent(id, password, name);
                    saveData(books, students, staff, borrowManager);
                    break;
                case 4: // Them nhan vien
                    cout << "Nhap ID: ";
                    getline(cin, id);
                    cout << "Nhap ten: ";
                    getline(cin, name);
                    cout << "Nhap username: ";
                    getline(cin, username);
                    cout << "Nhap mat khau: ";
                    getline(cin, password);
                    cout << "Nhap email: ";
                    getline(cin, email);
                    cout << "Nhap so dien thoai: ";
                    getline(cin, phone);
                    cout << "Nhap vai tro: ";
                    getline(cin, role);
                    staff.createStaff(id, name, username, password, email, phone, role);
                    saveData(books, students, staff, borrowManager);
                    break;
                case 5: // Xoa sinh vien
                    cout << "Nhap ID sinh vien de xoa: ";
                    getline(cin, id);
                    students.remove(id);
                    cout << "Da xoa sinh vien voi ID " << id << " thanh cong!\n";
                    saveData(books, students, staff, borrowManager);
                    break;
                case 6: // Xoa nhan vien
                    cout << "Nhap ID nhan vien de xoa: ";
                    getline(cin, id);
                    staff.remove(id);
                    cout << "Da xoa nhan vien voi ID " << id << " thanh cong!\n";
                    saveData(books, students, staff, borrowManager);
                    break;
                case 7: // Thoat
                    cout << "Thoat chuong trinh!\n";
                    saveData(books, students, staff, borrowManager);
                    break;
                default:
                    cout << "[THAT BAI] Lua chon khong hop le.\n";
            }
        } while (choice != 7);
    }

    return 0;
}