#include "atm_ui.h"

//Menu
void menu(node root, node myAccount)
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    char *option[] = {"0. Thoát", "1. Gửi tiền", "2. Chuyển tiền", "3. Rút tiền", "4. Xem tài khoản"};
    int optionCount = sizeof(option)/ sizeof(option[0]);
    
    while (1)
    {
        int menuEntryCount = 4;
        int choice = -1;
        char input[100];
        int clear = 0;
        
        while (menuEntryCount > 0)
        {
            system("cls");
            printf("\n\n");
            printf("\t\t\t╔════════════════════════════════════════════════════════╗\n"); 
            printf("\t\t\t║                     MENU GIAO DỊCH                     ║\n");
            printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
            
            for (int i = 1; i < optionCount; i++) {
                printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(option[i]), option[i]);
            }
            printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(option[0]), option[0]);
            printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
            
            char *msg;
            if (menuEntryCount == 4) msg = "Vui lòng chọn chức năng từ 0 đến 4";
            else if (menuEntryCount > 1) {
                static char buf[100];
                sprintf(buf, "Lựa chọn sai! Bạn còn %d lần nhập", menuEntryCount);
                msg = buf;
            } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";

            printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
            printf("\t\t\t║  Nhập lựa chọn của bạn: [   ]                          ║\n");
            printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
            
    
            printf("\033[2A\r\t\t\t\033[28C");

            if (fgets(input, sizeof(input), stdin) == NULL) continue;
            
            if (input[0] == '\n') {
                menuEntryCount--;
                continue;
            }
            
            int len = strlen(input);
            clear = 0;
            if (input[len - 1] == '\n') {
                input[len - 1] = '\0';
                len--;
            } else {
                clear = clear_buffer(); 
            }
            
            if (len > 1 || clear == 1 || input[0] < '0' || input[0] > '4') 
                {
                    menuEntryCount--;
                    continue; 
                }
            
            choice = input[0] - '0';
            break;
        }
        if (menuEntryCount == 0) 
            {
                printf("\n\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                return; 
            }
            
        printf("\n\n");
        

        switch (choice) {
            case 1: guitien(root, myAccount); break;
            case 2: chuyentien(root, myAccount); break;
            case 3: ruttien(root, myAccount); break;
            case 4: xemtaikhoan(myAccount); break;
            case 0: 
            default:
                printf("\t\tĐã hủy / Kết thúc giao dịch. \n");
                return; 
        }
        
    
        char yn_input[100];
        int ynEntryCount = 3;
        int clear_yn;
        char yn = 'X';
        
        while (ynEntryCount > 0) {
            printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
            printf("\t\t\t║              BẠN CÓ MUỐN TIẾP TỤC GIAO DỊCH KHÔNG?     ║\n");
            printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
            
            char *yn_msg;
            if (ynEntryCount == 3) yn_msg = "Nhập Y (Có) hoặc N (Không)";
            else if (ynEntryCount > 1) {
                static char yn_buf[100];
                sprintf(yn_buf, "Lựa chọn sai! Bạn còn %d lần nhập", ynEntryCount);
                yn_msg = yn_buf;
            } else yn_msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";

            printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(yn_msg), yn_msg);
            printf("\t\t\t║  Lựa chọn của bạn: [   ]                               ║\n");
            printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
            
            printf("\033[2A\r\t\t\t\033[23C"); 

            if (fgets(yn_input, sizeof(yn_input), stdin) == NULL) continue;
            if (yn_input[0] == '\n') { ynEntryCount--; printf("\n\n"); continue; } 
            
            int len = strlen(yn_input);
            clear_yn = 0;
            if (yn_input[len - 1] == '\n') {
                yn_input[len - 1] = '\0';
                len--;
            } else {
                clear_yn = clear_buffer(); 
            }
            
            if (len > 1 || clear_yn == 1) {
                ynEntryCount--; 
                printf("\n\n");
                continue; 
            }
            
            yn = yn_input[0];
            if (yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n') {
                printf("\n\n"); 
                break;
            }
            
            ynEntryCount--;
            printf("\n\n");
        }
        
        if (ynEntryCount == 0) {
            printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
            return;
        }
        if (yn == 'N' || yn == 'n') {
            printf("\n\t\t\t*** CẢM ƠN QUÝ KHÁCH ĐÃ SỬ DỤNG DỊCH VỤ ***\n\n");
            return;
        }
    }
}
//Hàm đăng nhập với vai trò khách
void GuestLogin(node root,char *shutdown )
{
    char target[MAX_ACC_LEN], yesno ='Y';
    int loginCount = 4;
    char stk_Admin[MAX_ACC_LEN]="06121234";
    char shutdown1='N';
    int KT=0;
    do 
    {
        if (KT) loginCount = 4;
        man_hinh_chao_mung();
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║        VUI LÒNG ĐĂNG NHẬP ĐỂ BẮT ĐẦU GIAO DỊCH             ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════════╣\n");
        char *msg;
        if (loginCount == 4) msg = "";
        else if (loginCount > 1) {
            static char buf[100];
            sprintf(buf, "Tài khoản sai! Bạn còn %d lần nhập", loginCount);
            msg = buf;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";

        printf("\t\t\t║  %-*s║\n", 58 + tinhOffset(msg), msg);
        printf("\t\t\t║  Số tài khoản: [                  ]                        ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[19C"); 

        loginCount -= 1;

        if (fgets(target,sizeof(target),stdin)==NULL) 
        {
            continue;
        }
        if (target[0]=='\n')	
        {
            continue;
        }


        int len = strlen(target);
        if (target[len - 1] == '\n') 
        {
            target[len - 1] = '\0'; 
        } 
        else 
        {
            clear_buffer();
        }

        
        if (strcmp(target,stk_Admin)==0)
        {
            KT=1;
            AdministratorLogin(&shutdown1);
            (*shutdown)=shutdown1;
            if (*shutdown == 'Y') {
                return; 
            }
        }
        else
        {
        node temp = findNode(root, target);

        if (temp != NULL)
        {
            KT=1;
            char mapin[10];
            int pinEntryCount = 4;
            do
            {
                system("cls");
                printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                printf("\t\t\t║                  XÁC THỰC TÀI KHOẢN                    ║\n");
                printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
                    
                char *pin_msg;
                if (pinEntryCount == 4) pin_msg = "Vui lòng nhập mã PIN (6 số)";
                else if (pinEntryCount > 1) 
                {
                    static char p_buf[100];
                    sprintf(p_buf, "Sai mã PIN! Bạn còn %d lần nhập", pinEntryCount);
                    pin_msg = p_buf;
                }
                 else pin_msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";

                printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(pin_msg), pin_msg);
                printf("\t\t\t║  (O:hiện mã) Mã PIN:                                   ║\n");
                printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
                printf("\033[2A\r\t\t\t\033[23C");
                pinEntryCount-=1;
                nhap_mk(mapin, 10);
                if (strlen(mapin) == 0) continue;
                int len=strlen(mapin);
                if (mapin[len-1]=='\n')
                {
                	mapin[len-1]='\0';
				}
				else
				{
					clear_buffer();
				}
            } while (strcmp(temp ->Data -> Pin, mapin ) !=0 && pinEntryCount>0);

            if (strcmp(temp ->Data -> Pin, mapin) ==0) 
            {
                printf("\n\n");
                menu(root, temp);
                return;
            }

            if (pinEntryCount == 0) 
            {
                printf("\n\n\t\t\t*** HẾT SỐ LẦN NHẬP MÃ PIN! ***\n\n");
                Sleep(2000);
                return;
            }
        }
        else
        {
            printf("\n\n\t\t\t*** KHÔNG TÌM THẤY SỐ TÀI KHOẢN ***\n\n");
            Sleep(1500);
            return;
        } 
        }
    } while ( loginCount > 0);

    if (loginCount == 0)
    {
        printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. KHÓA TẠM THỜI! ***\n\n");
        Sleep(2000);
    }
}

//Hàm đăng nhập với vai trò Lập trình viên
void AdministratorLogin(char *shutdown)
{
    char admin_pin[7] = "000000";
    char Pin_Entry[10];
    int Pin_Entry_Count = 4;
    int clear=0;

    do 
    {
        clear=0;
        system("cls");
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                 CHÀO MỪNG QUẢN TRỊ VIÊN                ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        
        char *msg;
        if (Pin_Entry_Count == 4) msg = "Vui lòng nhập mã bảo mật Admin để tắt máy";
        else if (Pin_Entry_Count > 1) {
            static char a[100];
            sprintf(a, "Sai mã bảo mật! Bạn còn %d lần nhập", Pin_Entry_Count);
            msg = a;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";

        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
        printf("\t\t\t║  (O:hiện mã) Mã bảo mật:                               ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[27C");
        Pin_Entry_Count -= 1;
		nhap_mk(Pin_Entry, 10); 
        if (strlen(Pin_Entry) == 0) continue;
        if (Pin_Entry[0]=='\n')	
        {
            continue;
        }
        int len = strlen(Pin_Entry);
        if (Pin_Entry[len - 1] == '\n') 
        {
            Pin_Entry[len - 1] = '\0'; 
        } 
        else 
        {
            clear = clear_buffer(); 
        }
        if (strcmp(Pin_Entry, admin_pin) != 0)
        {
                continue;
        }
    } while ((strcmp(Pin_Entry, admin_pin) != 0 || clear != 0) && Pin_Entry_Count >= 0);

    if (strcmp(Pin_Entry, admin_pin) == 0 && clear == 0)
    {
        (*shutdown) = 'Y';
    }
    else
    {
        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP MÃ BẢO MẬT. ! ***\n\n");
        Sleep(2000);
    }
    return;
}

//Hàm bật máy ATM
void khoidong(node root)
{
    // xóa sạch output khi bắt đàau chạy 
    //In ô nhập mã khởi động 
    system("cls");
    char shutdown = 'N';
    int clear=0;
    int passEntryCount = 4;
    char pass[10];
    char admin_pass[7]="000000";
    int KT=0;
    do 
    {
        system("cls");
        display_about();
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                      HỆ THỐNG ATM                      ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        
        char *msg;
        if (passEntryCount == 4) msg = "Vui lòng nhập mã bảo mật Admin để bật máy";
        else if (passEntryCount > 1) {
            static char b[100];
            sprintf(b, "Sai mã bảo mật! Còn %d lần nhập", passEntryCount);
            msg = b;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";

        printf("\t\t\t║  %-*s║\n", 54+tinhOffset(msg) , msg);
        printf("\t\t\t║  (O:hiện mã) Mã bảo mật:                               ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[27C");
        passEntryCount -= 1;
        nhap_mk(pass, 10);
        if (strlen(pass) == 0) continue;
        if (pass[0]=='\n')	
        {
            continue;
        }
        int len = strlen(pass);
        if (pass[len - 1] == '\n') 
        {
            pass[len - 1] = '\0'; 
        } 
        else 
        {
            clear = clear_buffer(); 
        }
        if (strlen(pass)<6 || strcmp(pass, admin_pass) != 0 ) 
        {
            continue;
        }
        
    } while ((strcmp(pass, admin_pass) != 0 || clear != 0) && passEntryCount > 0);

    //kiểm tra mã khởi động 
    if (strcmp(pass, admin_pass) == 0 && clear == 0)
    {
        system("cls");
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║           >>> KHỞI ĐỘNG HỆ THỐNG THÀNH CÔNG <<<        ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
        KT=1;
        Sleep(1500);
    }
    else
    {
        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP MÃ BẢO MẬT. SHUTTING DOWN... ***\n\n");
    }


    if (KT)
    {
        char *today_str = today();
        cr_file(today_str);
        do
        {
            GuestLogin(root,&shutdown);
    
        } while (shutdown != 'Y');
        system("cls");
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║          MÁY ĐANG TẮT... CẢM ƠN QUÝ KHÁCH!             ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
    }
}