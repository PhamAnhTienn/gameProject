#include <iostream>
#include <string>
using namespace std;

void dfs(int start, const string &pw, string cur) {
    cout << cur << endl; // In ra tất cả các subset bắt đầu từ chuỗi con cur
    for (int i = start; i < pw.size(); ++i) {
        cur.push_back(pw[i]); // Thêm ký tự mới vào chuỗi cur
        dfs(i + 1, pw, cur); // Gọi đệ quy với vị trí bắt đầu từ i + 1
        cur.pop_back(); // Loại bỏ ký tự vừa thêm vào cur để thử các ký tự tiếp theo
    }
}

int main() {
    int n;
    cin >> n;
    
    string pw;
    cin >> pw;
    
    dfs(0, pw, ""); // Gọi hàm dfs để bắt đầu duyệt từ vị trí 0, với chuỗi cur ban đầu là rỗng
    
    return 0;
}
