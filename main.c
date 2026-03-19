#include "atm_types.h"

char TransactionList[GIAODICHPHIEN][INFORM_LEN];
int admin_index = 0;

// Dán hàm menu() vào đây
// Dán hàm khoidong() vào đây

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8); 
    
    node root = NULL;
    root = input(root);
    khoidong(root);
    
    return 0;
}
