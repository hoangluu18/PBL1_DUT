 #include<iostream>
 #include<stdio.h>
 #include<conio.h>
 #include<process.h>
 #include<fstream>
 #include<string>
 #include<stdlib.h>
 #include<time.h>
 #include<vector>
 #include<algorithm>
 #include<iomanip>
 
 using namespace std;
 // khai bao hang so
 const int exit_the_loop = -99;
 // khai bao function
 int ma_hoadon();//hàm lấy mã hóa đơn theo ngày đặt đồ ăn

//void time_of_day(); //lấy thời gian thực

 int admin(); // quản lý các thao tác thêm sửa xóa đồ ăn

 int client();//quản lý các thao tác liên quan đến đặt đồ ăn và xem hóa đơn

 void get_code_bill(vector<int>&code_bill); //hàm lấy mã đồ ăn từ file lịch sử

 void see_bill();// hàm các thao tác xem hóa đơn từng ngày

 void order();// hàm có chức năng đặt đồ ăn
 
 void add_food();// thêm món ăn

 void delete_food();//xóa món ăn
 
 void edit_food();// sửa món ăn
 
 void show_food();// in ra danh sách món ăn

 string name_user;// luu ten tk dang nhap





//khai bao kieu foods
struct foods{
   
    int ma;
    string ten;
    int gia;
    int soluong;
    string donvi;// to va nho

    // định nghĩa phép so sánh mã
     bool operator<(const foods& other) const {
      return ma < other.ma;
    }
// cac thao tac tren struct
    
     // ham them struct
     void add(){
        
        cout<<"nhap ma so: \n"; 
        cin>>ma; cin.ignore();
        cout<<"nhap ten mon: \n";
        getline(cin,ten);
        cout<<"nhap gia san pham: \n";
        cin>>gia; cin.ignore();
        cout<<"nhap so luong: \n";
        cin>>soluong; cin.ignore();
        cout<<"to  hay nho : ";
       getline(cin,donvi); 
     }
};
  foods food;  // khai bao food

// khai bao struct quan li dang nhap tai khoan

struct login
{
    string user_name;
    string password;

void get_account(vector<login>&account){
  ifstream file;
  file.open("login.txt");
  if(file.is_open() != true){
    cout<<" Vui long kiem tra lai file\n";
  }
  string line;
  
  while(getline(file,line)){
    int pos,pos2;
    login temp;
    pos = line.find("-");
    pos2 = line.find("\n");
    temp.user_name = line.substr(0,pos);
    temp.password = line.substr(pos+1,pos2);

    account.push_back(temp);
  }
  file.close();
 
}

void check_login(){
    system("cls");
  string username;
  string password;
  cout << "===== DANG NHAP =====" << endl;
    cout << "Ten nguoi dung: ";
    cin >> username;
    cout << "Mat khau: ";
    cin >> password; cin.ignore();
    
    vector<login>account;
    get_account(account);
    bool check = false;
    for(int i = 0 ; i <account.size();i++){
       if(username == account[i].user_name && password == account[i].password){
        check = true;
        break;
       }
    }
    if(check == false){
        cout<<"Ban da nhap sai ten hoac mat khau vui long nhap chinh xac, nhan tiep tuc de nhap lai\n";
        getch();
        check_login();
    }
    else{
      name_user = username;
    }
}

};

login taikhoan; // khai bao kieu login

//khai báo struct quản lí đặt món
struct pay
{
  int mahoadon;
  int ma; // ma do an
  string ten;
  int soluong;
  int tong;
  // kiem tra so nguyen
 bool is_integer(const std::string& s) {
	if(s == "0 0"){
		return true;
	}
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char* p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);// tuong duong *p == NULL
}
// kiem tra tranh rò rỉ 

int inputNumber(vector<foods>&check) {
	
    string s;
    while (true) {
		
        getline(cin, s);
		    if(is_integer(s) == false){
			  cout<<"vui long nhap lai: ";
			  continue;
		    }
        if (s == "0 0") {
            return exit_the_loop;
        }
        try {
            bool tiep_tuc = true;
            int num = stoi(s);
            for(int i = 0; i<check.size();i++){
              if(num == check[i].ma){
                tiep_tuc = false;
                break;
              }
            }
            if(tiep_tuc== true){
              cout<<"vui long nhap lai:\n";continue;}
            else return num;
           
        }
        catch (invalid_argument e) {
            cout << "vui long nhap lai: ";
        }

    }
}
  string get_name(vector<foods>&check,int index ){
     for(int i = 0 ; i<check.size();i++){
       if(index == check[i].ma){
          return check[i].ten;
       }
     }
     return "";
  }

  // kiem tra xem so luong nhap vao co hop le khong
  void check_numfood(int &numfood,vector<foods>&danhSachDoan,int index,int &total){
    
     
      while(numfood < 0){
        cout<<"Nhap khong hop le: \n";
        cin>>numfood; cin.ignore();
        continue;
      }
      
          for(int i = 0; i<danhSachDoan.size();i++){
            if(danhSachDoan[i].ma == index){
              while(numfood > danhSachDoan[i].soluong){
                cout<<"So luong vuot qua cho phep nhap lai\n";
                cin>>numfood; cin.ignore();
              }
                danhSachDoan[i].soluong-=numfood;
                total =numfood * danhSachDoan[i].gia;
                break;
            }
          }
      }

};


//khai bao bien kiem tra quan li khach hang

pay kiemtra;

void get_vector_foods(vector<foods> &danhSachDoan);//hàm lấy dữ liệu đồ ăn từ file

 //khai báo xong funcition



 void get_code_bill(vector<int>&code_bill){
      
      ifstream file("save_code_bill.txt");
      string line;
      getline(file,line);
      if(line == ""){
        code_bill.push_back(0);
        return;
      }
      else{
        try
        {
           code_bill.push_back(stoi(line));
           while(getline(file,line)){
           code_bill.push_back(stoi(line));
           line.clear();
          }
        }
        catch(const std::exception& e)
        {
          cout<<"Vui long kiem tra lai file get_code_bill.txt tranh sai sot \n";
          file.close();
          return;
        }
      }
      file.close();
}

int ma_hoadon() { 
  vector<int>code_bill;
  get_code_bill(code_bill);
  
  static int count = code_bill[code_bill.size()-1]%1000;
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  
  if(code_bill.size() > 1){
    if(code_bill[code_bill.size()-1] /1000000 !=  t->tm_mday)// nếu khác ngày thì có nghĩ là đã sang ngày mới
    {
       count  =  0;
    }
  }
    return (t->tm_mday*1000+(t->tm_mon+1)*100+t->tm_year-100)*1000+(++count);
  
}

 
  



void get_vector_foods(vector<foods>&danhSachDoan){
     system("cls"); 
    fstream file("pbl.in",ios::in);
    string line;
        if(file.is_open()== false){
          cout<<"khong mo duoc file\n";
        }
          int count = 2;
        while(count--){
          string temp;
          getline(file,temp);
        }
        try{
        while (getline(file, line)) {
        foods d;
        string token;
        int pos;

        // Lấy giá trị của trường ma
        pos = line.find("|");
        token = line.substr(0, pos-1);
        d.ma = stoi(token);
        line.erase(0, pos + 2);

        // Lấy giá trị của trường ten
        pos = line.find("|");
        d.ten = line.substr(0, pos-1);
        line.erase(0, pos + 2);

        // Lấy giá trị của trường gia
        pos = line.find("|");
        token = line.substr(0, pos-1);
        d.gia = stoi(token);
        line.erase(0, pos + 2);
        // lay gia tri cua truong soluong
        pos = line.find("|");
        token = line.substr(0,pos-1);
        d.soluong = stoi(token);
        line.erase(0,pos+2);

        //Lấy giá trị của trường donvi
       pos = line.find("|");
       d.donvi = line.substr(0,pos-1);
       line.erase(0,pos+2);

        // Thêm struct vào vector
        danhSachDoan.push_back(d);
    }
        }
         catch (invalid_argument e) {
            file.close();
            danhSachDoan.clear();
            cout<<"Lay du lieu bi loi vui long kiem tra lai file pbl.in\n";
            cout<<"Nhan bat ki de tro ve menu\n";
            getch();
            return;
        }
}

void save_vector_foods(vector<foods>&danhSachDoan){
      ofstream file1("pbl.in", ios::out);
      if (!file1.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }
          // in ra intro
         file1<<"               MENU CHO NHÂN VIÊN\n MÃ | TÊN MÓN | ĐƠN GIÁ(VND) | SỐ LƯỢNG | ĐƠN VỊ(TO,NHỎ)\n";
        // luu hoa don vao file
        for (auto& d : danhSachDoan) {
             file1 << d.ma << " | " << d.ten << " | " << d.gia << " | " << d.soluong << " | " << d.donvi << endl;
         }
    
     
     file1.close();
}


  
void add_food(){
  system("cls");
  fstream file("pbl.in", ios::out | ios::app);
if(file.is_open()) {
   food.add();
   file <<food.ma<<" | "<<food.ten<<" | "<<food.gia<<" | "<<food.soluong<<" | "<<food.donvi<<endl;
   file.close();
  
}
else {
   cout << "Khong mo duoc file!\n";
}  
  
   cout<<"Da them mon an thanh cong nhan 'y' de them mon, bat ki de thoat\n";
   char tt;
   tt = getche();
   if(tt == 'y'){
     add_food();
   }
}

// ham xoa do an
void delete_food(){
    
     system("cls");

     vector<foods> danhSachDoan;
     get_vector_foods(danhSachDoan);
     if(danhSachDoan.empty() == true )return;
     show_food();
    int check;
    cout<<"\nnhap ma can xoa: \n";
    cin>>check; cin.ignore();
   
   
    for(int i = 0; i<danhSachDoan.size();i++){
        if(danhSachDoan[i].ma == check){
            danhSachDoan.erase(danhSachDoan.begin()+i);
        }
    }
      ofstream file1("pbl.in", ios::out);
      if (!file1.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }
     save_vector_foods(danhSachDoan);
     system("cls");
     show_food();
     cout<<"nhap y de tiep tuc xoa , nhap bat ki de thoat: ";
     char tt;
      tt = getche();
     if(tt != 'y'){ 
      return;
     }
     delete_food();
    }



void show_food(){
    system("cls"); 
    vector<foods> danhSachDoan;
    get_vector_foods(danhSachDoan);
    if(danhSachDoan.empty() == true ) {
        return;
    }
    // In dữ liệu
    cout << "Danh sach mon an:" << endl;
    cout << left << setw(10) << "Ma" << setw(20) << "Ten mon" << setw(15) << "Gia(VND)" << setw(15) << "So luong" << setw(10) << "Don vi" << endl;
    for (int i = 0; i < danhSachDoan.size(); i++) {
    cout<<left<<setw(10)<<danhSachDoan[i].ma<<setw(20)<<danhSachDoan[i].ten<<setw(15)<<danhSachDoan[i].gia<<setw(15)<<danhSachDoan[i].soluong<<setw(10)<<danhSachDoan[i].donvi<<endl;
}
    
}

void edit_food(){
  system("cls");
    vector<foods> danhSachDoan;
    get_vector_foods(danhSachDoan);
    if(danhSachDoan.empty() == true )return;
   show_food();
   int check;
  cout<<"nhap ma can sua: ";
  cin>>check; cin.ignore();
 
  
    for(int i = 0 ; i< danhSachDoan.size();i++){
        if(check == danhSachDoan[i].ma){
            foods temp;
            temp.add();
            danhSachDoan[i] = temp;
        }
    }
    save_vector_foods(danhSachDoan);
     system("cls");
     show_food();
     cout<<"Ban tiep tuc sua khong, y tiep tuc,con lai thoat\n";
     char tt;
     tt = getche();
     if(tt != 'y')return;
     edit_food();
    }
 



   
  void order(){
    system("cls");
    // khai bao struct tm lay thoi gian thuc
     time_t now = time(NULL);
     struct tm *t = localtime(&now);
     // khai bao vector quan li do an va hoa don
    vector<foods> danhSachDoan;  vector<pay>hoa_don;
    int sum = 0; // tong thanh toan
    get_vector_foods(danhSachDoan);

    int order = 0; // biến tính số lượng món ăn quý khách đã chọn xong
  do{
      bool exit_do = false;
      //khai bao
     
      int temp_ma;
      int numfood;
      int total = 0 ; //toong tien
      //in ra  danh sach
      system("cls");
      cout << "\tChao mung quy khach den voi nha hang!" << endl;
      cout << "Danh sach mon an:" << endl;
      cout << left << setw(10) << "Ma" << setw(20) << "Ten mon" << setw(15) << "Gia(VND)" << setw(15) << "So luong" << setw(10) << "Don vi" << endl;
      for(int i = 0; i<danhSachDoan.size();i++){
       if(danhSachDoan[i].soluong > 0)// số lượng = 0 thì không in ra
      cout << left << setw(10) << danhSachDoan[i].ma << setw(20) << danhSachDoan[i].ten << setw(15) <<danhSachDoan[i].gia << setw(15) << danhSachDoan[i].soluong << setw(10) <<danhSachDoan[i].donvi << endl;
     }
     while (true)
    {
    cout<<"Moi quy khach chon ma do an can chon: (0 0 to exit) ";
  
    temp_ma = kiemtra.inputNumber(danhSachDoan);
    if(temp_ma == exit_the_loop){
      exit_do = true;
    }
    break;
    }
    if(exit_do == true)break;
    string temp_name = kiemtra.get_name(danhSachDoan,temp_ma);
    cout<<"Moi quy khach chon so luong mon: "<<temp_name<<"\n";
     cin>>numfood; cin.ignore();
     kiemtra.check_numfood(numfood,danhSachDoan,temp_ma,total);
     // lưu vào biến tạm
     pay temp;
     //temp.mahoadon = ma_hoadon();
     temp.ma = temp_ma;
     temp.ten =temp_name;
     temp.soluong = numfood;
     temp.tong = total;
     // day vao vector
     hoa_don.push_back(temp);
     order++;
  }
    while(order < 5 );
    save_vector_foods(danhSachDoan);
    system("cls");
    // hien ra hoa don 
    cout<<"            HOA DON CUA QUY KHACH\n";
    cout<<"-------------------------------------------\n";
    cout << left << setw(4) << "Ma" << setw(15) << "Ten Mon An" << setw(15) << "So luong" << setw(15) << "Tong" << endl;
    for(auto& d : hoa_don){
      	 cout<<left<<setw(4)<<d.ma<<setw(15)<<d.ten<<setw(15)<<d.soluong<<setw(15)<<d.tong<<endl;
         sum = sum + d.tong;
    }
    cout<<"Tong: "<<sum<<" VND"<<endl;
   

    //luu lai vector danhsachdoan vao file de cap nhat lai
    cout<<"Ban co muon thanh toan khong: (y) de thanh toan, con lai de thoat: ";
    if(char tt = getch() != 'y' ){
       return;
    }
    //luu so tien thu ngan cua nhan vien vao file
  
     ifstream file(name_user);
     if(!file.is_open()){
     file.close();
     ofstream file1(name_user);
     file1<<sum;
     file1.close();
  }
  else{
     string line;
     getline(file,line);
     file.close();
     int sum1 = sum;
     sum1 = sum1+  stoi(line) ;
     ofstream file1(name_user, ios::out);
     file1<<sum1;
     file1.close();

  }
    // lay ten khach  va in ra chi tiet hoa don
    system("cls");
    string customer_name ; 
    int ma_hoa_don; ma_hoa_don = ma_hoadon();
    cout<<"\nVui long nhap ten khach hang: ";
    getline(cin,customer_name);
    cout<<"            HOA DON KHACH HANG\n";
    cout<<"Ma hoa don: "<<ma_hoa_don<<endl;
    cout<<"Ten khach hang: "<<customer_name<<endl;
    cout<<"Ngay ban: "<< (t->tm_mday)<<" - " <<(t->tm_mon+1)<<" - 20"<<t->tm_year-100<<endl; 
    cout<<"So mon: "<<hoa_don.size()<<endl;
    cout<<"Tong tien: "<<sum<<" VND"<<endl;
    cout<<"Nguoi thu tien: "<<name_user<<endl;
    cout<<"            Chi tiet hoa don\n";
    cout << left << setw(4) << "Ma" << setw(15) << "Ten Mon An" << setw(15) << "So luong" << setw(15) << "Tong" << endl;
    for(auto& d : hoa_don){
      	 cout<<left<<setw(4)<<d.ma<<setw(15)<<d.ten<<setw(15)<<d.soluong<<setw(15)<<d.tong<<endl;
         
    }
    cout<<"Tong: "<<sum<<" VND"<<endl;

    // luu ma hoa don vao file
    string code_bill = to_string(ma_hoa_don);
    fstream outfile("save_code_bill.txt",ios::app);
    outfile<<code_bill<<endl;
    outfile.close();
    // luu hoa don vao file
    ofstream save;  
    save.open(to_string(ma_hoa_don));
    save<<"            HOA DON KHACH HANG\n";
    save<<"Ma hoa don: "<<ma_hoa_don<<endl;
    save<<"Ten khach hang: "<<customer_name<<endl;
    save<<"Ngay ban: "<< (t->tm_mday)<<" - " <<(t->tm_mon+1)<<" - 20"<<t->tm_year-100<<endl; 
    save<<"So mon: "<<hoa_don.size()<<endl;
    save<<"Tong tien: "<<sum<<" VND"<<endl;
    save<<"Nguoi thu tien: "<<name_user<<endl;
    save<<"            Chi tiet hoa don\n";
    save << left << setw(4) << "Ma" << setw(15) << "Ten Mon An" << setw(15) << "So luong" << setw(15) << "Tong" << endl;
    for(auto& d : hoa_don){
      	 save<<left<<setw(4)<<d.ma<<setw(15)<<d.ten<<setw(15)<<d.soluong<<setw(15)<<d.tong<<endl;
         
    }
    save<<"Tong: "<<sum<<" VND"<<endl;
     hoa_don.clear();
     save.close();

     //thong bao ket thuc
     cout<<"Da luu hoa don, nhan bat ki de thoat\n";
     getch();
    
}
  // hàm in hóa đơn theo ngày
void see_bill(){
  system("cls");
   vector<int>code_bill;
   get_code_bill(code_bill);
   cout<<"\tXEM HOA DON \n";
   cout<<"1.Xem hoa don can tim \n";
   cout<<"2.Xem tat ca hoa don trong ngay \n";
   cout<<"3.Thong ke thu ngan cua cac nhan vien trong thang\n";
   char tt = getche();
   switch(tt){
     case '2':{
      system("cls");
      bool check = false;
      cout<<"\nNhap ngay can xem hoa don theo dinh dang (ngaythangnam vd:16523)\n";
      int getday; cin>>getday;cin.ignore();
      system("cls");
      for(int i = 0; i<code_bill.size();i++){
            if(code_bill[i]/1000 == getday){
              check = true;
              cout<<"Ma: "<<code_bill[i]<<endl;
              string temp = to_string(code_bill[i]);
           	  fstream file(temp); // Mở file để đọc
              string content; // Tạo chuỗi để chứa nội dung của file
              string line;
           while (getline(file, line)) { // Đọc từng dòng trong file
            content += line + "\n"; // Thêm nội dung từng dòng vào chuỗi
            }
          file.close(); // Đóng file sau khi đọc xong
          cout<<content<<"\n\n\n";
        }
      }
      if(check == false){
        cout<<"Khong co hoa don trong ngay do nhap bat ki de thoat\n";
      }
      else cout<<"Nhap bat ki de thoat\n";
      break;
     }

     case '1':{
         system("cls");
        bool check = false;
        cout<<"Nhap ma hoa don ban muon xem theo dinh dang (ngaythangnam+abc vd: 16523001): ";
        int getcode; cin>>getcode;
        system("cls");
        for(int i = 0; i<code_bill.size();i++){
            if(code_bill[i] == getcode){
              check = true;
              cout<<"Ma: "<<code_bill[i]<<endl;
              string temp = to_string(code_bill[i]);
           	  fstream file(temp); // Mở file để đọc
              string content; // Tạo chuỗi để chứa nội dung của file
              string line;
           while (getline(file, line)) { // Đọc từng dòng trong file
            content += line + "\n"; // Thêm nội dung từng dòng vào chuỗi
            }
          file.close(); // Đóng file sau khi đọc xong
          cout<<content<<"\n\n\n";
        }
      }
      if(check == false){
        cout<<"Khong co hoa don trong ngay do nhan bat ki de thoat\n";
      }
      else cout<<"Nhap bat ki de thoat\n";
        break;
     }

     case '3':{
      system("cls");
       vector<login> information;
    
    taikhoan.get_account(information);
    for(int i = 0 ; i <information.size();i++){
        string name = information[i].user_name;
        fstream file(name,ios::in);
    if (!file.is_open()) {
        cout << "Nhan vien: " <<information[i].user_name<<" khong giao dich trong thang nay" << endl;
       
    } else {
        string line;
        getline(file, line);
        int sum = 0;
        sum += stoi(line);
        file.close();
       cout<<"Nhan vien: "<<information[i].user_name<<" thu ngan trong thang voi so tien la: "<<sum<<" VND\n";
    }
    }
    cout<<"Nhan bat ki de thoat\n";
     }
   }

   
}



  int client(){
    system("cls");
    char tt;
    cout<<"Menu danh cho quan ly dat hang va thanh toan\n";
    cout<<"1.Dat mon va thanh toan\n";
    cout<<"2.Tra cuu hoa don\n";
    cout<<"3.Tro ve menu\n";
    tt = getche();
    switch (tt)
    {
    case '1':{
        order();
        break;
      }
     

    case '2':{
       see_bill();
       getch();
      break;
      }
     
    case '3':{
       break;
      }
     
    default: cout<<"\a"; client();
      
    }
    return 0;
  }



int admin(){
    system("cls");
    char tt;
    cout<<"Menu danh cho nhan vien\n";
    cout<<"1. Them do an\n";
    cout<<"2. Xoa do an\n";
    cout<<"3. Sua doi do an\n";
    cout<<"4. Xem thuc don\n";
    cout<<"5. Tro ve menu\n";
    tt = getche();
   switch(tt){
      case '1':{
           add_food();
          break;  
      }
      case '2':{
           delete_food();
         break;
      }
      case '3':{
          edit_food();
        break;
      }
      case '4':{
        show_food();
        cout<<"Nhan tiep tuc de thoat\n";
        getch();
      }
      case '5':{

        break;
      }
      default: cout<<'\a'; admin();
   }
return 0;
}


 int main(){
   taikhoan.check_login();
  /// trước là check_login() thì giờ thay = như trên
   
   system("cls");
    char ch;//cout<<name_user<<endl;
   
    do{ 
        cout << "Menu:\n";
        cout << "1. Quan ly dat hang va thanh toan\n";
        cout << "2. Quan ly thuc don va mon an\n";
        cout << "3. Exit\n";
        cout << "Nhap lua chon cua ban: ";
        ch = getche();
        switch (ch)
        {
           case '1':{
              client();
             break;
           }
           case '2':{
               admin();
             break;
           }
           case '3':{

             exit(0);
             
           }
           default:cout<<"\a";
        }
        system("cls");
    } while(ch != 3);
    return 0;
 }

