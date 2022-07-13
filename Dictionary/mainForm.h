#pragma once
//#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>


std::string fileDATA = "fileDATA.txt";
FILE* file;
int i;

struct DATA_123 //Struct lưu danh sách theo thứ tự thêm vào
{
	int stt;
	std::string tvt;
	std::string tg;
};
struct DATA_abc //Struct lưu danh sách theo thứ tự alphabet
{
	int abc;
	std::string tvt;
	std::string tg;
};
// Tạo vector để lưu 2 danh sách
// T đã tính đến phương án gộp vào 1 vector nhưng vấn đề là khó
// cho việc sắp xếp và in ra. Hoặc là do t chưa nghĩ ra
std::vector<DATA_123> DATABASE_123;
DATA_123 temp_123; //Biến này phục vụ cho việc tạo struct 2 kiểu trên và sắp xếp
std::vector<DATA_abc> DATABASE_abc;
DATA_abc temp_abc; // tương tự

namespace Dictionary {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace std;
	using namespace System::IO;
	

	/// <summary>
	/// Summary for mainForm
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
	public:
		mainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		DATA_123 TaoData_123(int stt, std::string tvt, std::string tg) {
			DATA_123* data_123 = new DATA_123;
			data_123->stt = stt;
			data_123->tvt = tvt;
			data_123->tg = tg;
			return *data_123;
		}
		DATA_abc TaoData_abc(int abc, std::string tvt, std::string tg) {
			DATA_abc* data_abc = new DATA_abc;
			data_abc->abc = abc;
			data_abc->tvt = tvt;
			data_abc->tg = tg;
			return *data_abc;
		}
		//In ra màn hình 
		void display_data() {
			listView1->Items->Clear(); // xóa toàn bộ bảng hiển thị 
			// 0 là in theo thứ tự thêm vào 123
			if (type_sort == 0) { 
				for (int i = 0; i < DATABASE_123.size(); i++) {
					/*Vì để add được vào bảng, phải dùng hàm với tham số là 
					String^ (của C++ CLI). Nên dưới đây là các thao tác chuyển từ 
					int, std::string sang String 
					*/
					String^ str1 = (i + 1).ToString();
					String^ str2 = gcnew String(DATABASE_123[i].tvt.c_str());
					String^ str3 = gcnew String(DATABASE_123[i].tg.c_str());
					//Add vào bảng
					listViewItem = gcnew Windows::Forms::ListViewItem(str1);
					listViewItem->SubItems->Add(str2);
					listViewItem->SubItems->Add(str3);
					this->listView1->Items->Add(this->listViewItem);
				}
			}
			//1 là in theo thứ tự alphabet
			else if (type_sort == 1) { 				
				for (int i = 0; i < DATABASE_abc.size(); i++) {
					String^ str1 = (i + 1).ToString();
					String^ str2 = gcnew String(DATABASE_abc[i].tvt.c_str());
					String^ str3 = gcnew String(DATABASE_abc[i].tg.c_str());

					listViewItem = gcnew Windows::Forms::ListViewItem(str1);
					listViewItem->SubItems->Add(str2);
					listViewItem->SubItems->Add(str3);
					this->listView1->Items->Add(this->listViewItem);
				}
			}
		}
		// Hàm đổi vị trí 2 vector của vector DATABASE_abc
		void swap(int i, int j)
		{
			string tmp = DATABASE_abc[i].tvt;
			DATABASE_abc[i].tvt = DATABASE_abc[j].tvt;
			DATABASE_abc[j].tvt = tmp;
			tmp = DATABASE_abc[i].tg;
			DATABASE_abc[i].tg = DATABASE_abc[j].tg;
			DATABASE_abc[j].tg = tmp;
			int _tmp = DATABASE_abc[i].abc;
			DATABASE_abc[i].abc = DATABASE_abc[j].abc;
			DATABASE_abc[j].abc = _tmp; 
		}
		void Partition(int left, int right)
		{
			// Kiểm tra xem nếu vector có 1 phần tử thì không cần sắp xếp
			if (left >= right)
				return;

			string pivot = DATABASE_abc[(left + right) / 2].tvt; // Chọn phần tử chính giữa dãy làm chốt

			// i là vị trí đầu và j là cuối đoạn
			int i = left, j = right;
			while (i < j)
			{
				while (DATABASE_abc[i].tvt < pivot) // Nếu phần tử bên trái nhỏ hơn pivot thì ok, bỏ qua
					i++;
				while (DATABASE_abc[j].tvt > pivot) // Nếu phần tử bên phải nhỏ hơn pivot thì ok, bỏ qua
					j--;

				// Sau khi kết thúc hai vòng while ở trên thì chắc chắn
				// vị trí DATABASE_abc[i].tvt phải lớn hơn pivot và DATABASE_abc[j].tvt phải nhỏ hơn pivot
				// nếu i < j
				if (i <= j)
				{
					if (i < j) // nếu i != j (tức không trùng thì mới cần hoán đổi)
						swap(i, j); // Thực hiện đổi chổ ta được DATABASE_abc[i].tvt < pivot và DATABASE_abc[j].tvt > pivot
					i++;
					j--;
				}
			}

			// Gọi đệ quy sắp xếp dãy bên trái pivot
			Partition(left, j);
			// Gọi đệ quy sắp xếp dãy bên phải pivot
			Partition(i, right);
		}

		// Hàm sắp xếp nhanh
		void QuickSort(int n)
		{
			Partition(0, n - 1);
		}
		// Hàm sắp xếp chọn
		void SelectionSort(int m, int n) {
			for (int i = m; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (DATABASE_abc[i].tvt > DATABASE_abc[j].tvt) {
						swap(i, j);
					}
				}
			}
		}
		//Hàm đọc file dữ liệu(Chỉ đọc 1 lần đầu tiên khi mở app)
		//Lưu dữ liệu vào 2 vector là vector sx theo 123 và sx theo alphabet
		void readFile(String^ fileName) {
			StreamReader^ DataIn = File::OpenText(fileName);
			String^ DataStr;
			//khai báo biến để sử dụng hàm sscanf bên dưới
			int stt = 0;
			char tuviettat[15] = { 0 }, tugoc[45] = { 0 };
			//Mỗi while đọc 1 hàng trong file text
			while ((DataStr = DataIn->ReadLine()) != nullptr)
			{
				//chuyển DataStr(kiểu String^) sang string
				char cStr[50] = { 0 };
				if (DataStr->Length < sizeof(cStr)) sprintf(cStr, "%s", DataStr);
				//cStr là char hoặc string, còn phần trong ngoặc "" không thể là string
				sscanf(cStr, "[%d] %s %[^.]", &stt, tuviettat, tugoc);
				// biến temp là biến có kiểu DATA chứa dữ liệu của từng hàng
				temp_abc = TaoData_abc(stt, std::string(tuviettat), std::string(tugoc));
				temp_123 = TaoData_123(stt, std::string(tuviettat), std::string(tugoc));
				//push từng hàng vào vector DATABASE_
				DATABASE_abc.push_back(temp_abc);
				DATABASE_123.push_back(temp_123);
			}
			DataIn->Close();// đóng file

			//Sắp xếp vector ABC theo alphabet theo giải thuật sắp xếp chọn(SelectionSort)
			//SelectionSort(0, DATABASE_abc.size());
			//Sắp xếp vector ABC theo alphabet theo giải thuật sắp xếp nhanh(QuickSort)
			QuickSort(DATABASE_abc.size());
		}
		//Phần design, không cần hiểu sâu
		void checkbox() {
			if (checkBox1->Checked == true && checkBox2->Checked == false) {
				checkBox2->Enabled = false;
			}
			if (checkBox1->Checked == false && checkBox2->Checked == true) {
				checkBox1->Enabled = false;
			}
			if (checkBox1->Checked == false && checkBox2->Checked == false) {
				checkBox1->Enabled = true;
				checkBox2->Enabled = true;
			}
		}
		//
		// Tìm kiếm tuần tự
		//Hàm search theo từ viết tắt, trả về vị trí tìm đc
		int SearchTVT(std::vector<DATA_123> database, std::string word) {
			for (int i = 0; i < database.size(); i++) {
				if (database[i].tvt == word) {
					return i;
				}
			}
			return -1; // K tìm thấy
		}
		//Hàm search theo từ gốc, trả về vị trí tìm đc
		int SearchTG(std::vector<DATA_123> database, std::string word) {
			for (int i = 0; i < database.size(); i++) {
				if (database[i].tg == word) {
					return i;
				}
			}
			return -1;
		}
		
		//Tìm kiếm nhị phân
		int BSearchTVT(vector<DATA_abc> database, string word, int m, int n) {
			if (m > n) return -1;
			int k = (m + n) / 2;
			if (word == database[m].tvt) return m;
			else {
				if (word < database[m].tvt) return BSearchTVT(database, word, m, k - 1);
				else return BSearchTVT(database, word, m + 1, n);
			}
		}
		int BinarySearchTVT(vector<DATA_abc> database, string word) {
			return BSearchTVT(database, word, 0, database.size() - 1);
		}

	public:
		// Thể hiện kiểu sắp xếp hiện tại trên bảng hiển thị
		// 0 là 123, mặc định khi mở app
		// 1 là abc
		bool type_sort = 0;
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	System::Windows::Forms::ListViewItem^ listViewItem;//dung cho listView
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ txtTVT;
	private: System::Windows::Forms::TextBox^ txtTG;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader2;
	private: System::Windows::Forms::ColumnHeader^ columnHeader3;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panelLOGO;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Panel^ PanelTitleBar;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ button4;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(mainForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->txtTVT = (gcnew System::Windows::Forms::TextBox());
			this->txtTG = (gcnew System::Windows::Forms::TextBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->panelLOGO = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->PanelTitleBar = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			this->panelLOGO->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->panel3->SuspendLayout();
			this->PanelTitleBar->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->button1, L"button1");
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Name = L"button1";
			this->button1->TabStop = false;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &mainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->button2, L"button2");
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Name = L"button2";
			this->button2->TabStop = false;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &mainForm::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->button3, L"button3");
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Name = L"button3";
			this->button3->TabStop = false;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &mainForm::button3_Click);
			// 
			// txtTVT
			// 
			this->txtTVT->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->txtTVT->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->txtTVT, L"txtTVT");
			this->txtTVT->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			this->txtTVT->Name = L"txtTVT";
			this->txtTVT->Click += gcnew System::EventHandler(this, &mainForm::txtTVT_Click);
			// 
			// txtTG
			// 
			this->txtTG->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->txtTG->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->txtTG, L"txtTG");
			this->txtTG->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			this->txtTG->Name = L"txtTG";
			this->txtTG->Tag = L"";
			this->txtTG->Click += gcnew System::EventHandler(this, &mainForm::txtTG_Click);
			// 
			// listView1
			// 
			this->listView1->Activation = System::Windows::Forms::ItemActivation::OneClick;
			resources->ApplyResources(this->listView1, L"listView1");
			this->listView1->BackColor = System::Drawing::Color::White;
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3
			});
			this->listView1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			this->listView1->FullRowSelect = true;
			this->listView1->GridLines = true;
			this->listView1->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listView1->HideSelection = false;
			this->listView1->MultiSelect = false;
			this->listView1->Name = L"listView1";
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &mainForm::listView1_ItemSelectionChanged);
			// 
			// columnHeader1
			// 
			resources->ApplyResources(this->columnHeader1, L"columnHeader1");
			// 
			// columnHeader2
			// 
			resources->ApplyResources(this->columnHeader2, L"columnHeader2");
			// 
			// columnHeader3
			// 
			resources->ApplyResources(this->columnHeader3, L"columnHeader3");
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->button6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button6->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->button6, L"button6");
			this->button6->ForeColor = System::Drawing::Color::White;
			this->button6->Name = L"button6";
			this->button6->TabStop = false;
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &mainForm::button6_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->button5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button5->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->button5, L"button5");
			this->button5->ForeColor = System::Drawing::Color::White;
			this->button5->Name = L"button5";
			this->button5->TabStop = false;
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &mainForm::button5_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->panel1->Controls->Add(this->button8);
			this->panel1->Controls->Add(this->button7);
			this->panel1->Controls->Add(this->panelLOGO);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->button6);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button5);
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->panel1->Name = L"panel1";
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->button8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button8->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->button8, L"button8");
			this->button8->ForeColor = System::Drawing::Color::White;
			this->button8->Name = L"button8";
			this->button8->TabStop = false;
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &mainForm::button8_Click);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->button7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button7->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->button7, L"button7");
			this->button7->ForeColor = System::Drawing::Color::White;
			this->button7->Name = L"button7";
			this->button7->TabStop = false;
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &mainForm::button7_Click);
			// 
			// panelLOGO
			// 
			this->panelLOGO->Controls->Add(this->pictureBox1);
			resources->ApplyResources(this->panelLOGO, L"panelLOGO");
			this->panelLOGO->Name = L"panelLOGO";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(4)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			resources->ApplyResources(this->pictureBox1, L"pictureBox1");
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::White;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->textBox1, L"textBox1");
			this->textBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->textBox1->Name = L"textBox1";
			this->textBox1->Click += gcnew System::EventHandler(this, &mainForm::textBox1_Click);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &mainForm::textBox1_KeyDown);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->panel3->Controls->Add(this->listView1);
			resources->ApplyResources(this->panel3, L"panel3");
			this->panel3->Name = L"panel3";
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			resources->ApplyResources(this->panel4, L"panel4");
			this->panel4->Name = L"panel4";
			// 
			// panel5
			// 
			this->panel5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			resources->ApplyResources(this->panel5, L"panel5");
			this->panel5->Name = L"panel5";
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			this->label1->Name = L"label1";
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			this->label2->Name = L"label2";
			// 
			// PanelTitleBar
			// 
			this->PanelTitleBar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			this->PanelTitleBar->Controls->Add(this->button4);
			this->PanelTitleBar->Controls->Add(this->checkBox2);
			this->PanelTitleBar->Controls->Add(this->checkBox1);
			this->PanelTitleBar->Controls->Add(this->textBox1);
			resources->ApplyResources(this->PanelTitleBar, L"PanelTitleBar");
			this->PanelTitleBar->Name = L"PanelTitleBar";
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::White;
			this->button4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			resources->ApplyResources(this->button4, L"button4");
			this->button4->Name = L"button4";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &mainForm::button4_Click);
			// 
			// checkBox2
			// 
			resources->ApplyResources(this->checkBox2, L"checkBox2");
			this->checkBox2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->TabStop = false;
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &mainForm::checkBox2_CheckedChanged);
			// 
			// checkBox1
			// 
			resources->ApplyResources(this->checkBox1, L"checkBox1");
			this->checkBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->TabStop = false;
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &mainForm::checkBox1_CheckedChanged);
			// 
			// mainForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->Controls->Add(this->PanelTitleBar);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel5);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->txtTG);
			this->Controls->Add(this->txtTVT);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel1);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"mainForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Load += gcnew System::EventHandler(this, &mainForm::mainForm_Load);
			this->panel1->ResumeLayout(false);
			this->panelLOGO->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->panel3->ResumeLayout(false);
			this->PanelTitleBar->ResumeLayout(false);
			this->PanelTitleBar->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

//Nút thêm
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	//Hai ô Từ gốc và Từ viết tắt bị trống
	if (txtTVT->Text == "" || txtTG -> Text == "") {
		MessageBox::Show("Can't perform this operation");
		return;
	}
	for (int i = 0; i < DATABASE_123.size(); i++) {
		//Chuyển std::string sang String^
		String^ str2 = gcnew String(DATABASE_123[i].tvt.c_str());
		String^ str3 = gcnew String(DATABASE_123[i].tg.c_str());
		//Đã tồn tại từ này
		if (str2 == (txtTVT->Text) && str3 == (txtTG->Text)) {
			MessageBox::Show("This word already exists");
			return;
		}
		//Đã tồn tại từ gốc này
		else if (str3 == (txtTG->Text)) {
			MessageBox::Show("Original already exists");
			return;
		}
		//Đã tồn tại từ viết tắt này
		else if (str2 == (txtTVT->Text)) {
			MessageBox::Show("Acronyms already exists");
			return;
		}
	}
	
	//Lấy dữ liệu trong 2 ô textbox từ viết tắt và từ gốc
	char* cStr1 = new char[txtTVT->Text->Length + 1];
	sprintf(cStr1, "%s", txtTVT->Text);
	char* cStr2 = new char[txtTG->Text->Length + 1];	
	sprintf(cStr2, "%s", txtTG->Text);
	
	//Khi thêm từ mới vào, nhận dữ liệu người dùng nhập vào tại 2 ô tvt, tg
	// Tạo một biến kiểu vector DATABASE_123 và DATABASE_abc
	// Nếu là kiểu DATABASE_123 thì push ngay vào cuối
	// Nếu là kiểu DATABASE_abc thì push
	temp_123 = TaoData_123(DATABASE_123.size() + 1, cStr1, cStr2);
	DATABASE_123.push_back(temp_123);
	temp_abc = TaoData_abc(DATABASE_123.size(), cStr1, cStr2);
	//int p là vị trí thêm vào của từ mới trong ds sắp xếp theo alphabet
	int p = -1;
	//Duyệt toàn bộ vector, nếu tvt của từ mới < tvt của từ thứ i
	//Thêm từ mới vào trước vị trí i, dùng insert
	for (int i = 0; i < DATABASE_abc.size(); i++) {
		if (cStr1 < DATABASE_abc[i].tvt) {
			DATABASE_abc.insert(DATABASE_abc.begin() + i, temp_abc);
			p = i;//VT thêm vào
			break;
		}	
	}
	//Nếu cả vector không có tvt của từ thứ i > tvt của từ mới thì
	//Thêm vào cuối vector DATABASE_abc
	if (p == -1) {
		DATABASE_abc.push_back(temp_abc);
		p = DATABASE_abc.size()-1;//VT thêm vào
	}
	
	//Xoa du lieu con tro
	delete[] cStr1;
	delete[] cStr2;
	if (type_sort == 0) {
		p = DATABASE_123.size();

		MessageBox::Show("Added success");
		display_data();
		listView1->Items[p - 1]->Selected = 1;
		listView1->Items[p - 1]->Focused = 1;
		listView1->Items[p - 1]->EnsureVisible();
		PanelTitleBar->Focus();
	}
	else if (type_sort == 1) {

		MessageBox::Show("Added success");
		display_data();
		listView1->Items[p]->Selected = 1;
		listView1->Items[p]->Focused = 1;
		listView1->Items[p]->EnsureVisible();
		PanelTitleBar->Focus();
	}
}

private: System::Void listView1_ItemSelectionChanged(System::Object^ sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^ e) {
	// Khi chọn vào 1 từ trong bảng, từ viết tắt và từ gốc của từu được chọn sẽ được hiển thị trên 2 ô textbox
	if (listView1->SelectedItems->Count > 0) {
		txtTVT->Text = listView1->SelectedItems[0]->SubItems[1]->Text;
		txtTG->Text = listView1->SelectedItems[0]->SubItems[2]->Text;
	}
}
//Nút Sửa
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	
	if (listView1->SelectedItems->Count > 0) {
		if (txtTVT->Text == "" || txtTG->Text == "") {
			MessageBox::Show("Can't perform this operation");
			return;
		}
		char cStr[4] = { 0 };
		sprintf(cStr, "%s", listView1->SelectedItems[0]->Text);
		int _stt = std::stoi(std::string(cStr)); // chuyển đối tượng được chọn thành số kiểu int để xác định vị trí xóa
		//MessageBox::Show(listView1->SelectedItems[0]->Text);
		char* cStr1 = new char[txtTVT->Text->Length + 1];
		sprintf(cStr1, "%s", txtTVT->Text);
		char* cStr2 = new char[txtTG->Text->Length + 1];
		sprintf(cStr2, "%s", txtTG->Text);

		for (int i = 0; i < DATABASE_123.size(); i++) {
			if (cStr1 == DATABASE_123[i].tvt || cStr2 == DATABASE_123[i].tg) {
				MessageBox::Show("This word already exists");
				return;
			}
		}
		//Lúc bảng đang ở chế độ sắp xếp 123
		//Vì sao phải chia ra 2 chế độ? Vì lúc ở chế độ 123, người dùng chọn 1 từ và
		//sửa từ đó ở DATABASE_123 theo _stt thì bên vector DATABASE_abc không biết từ đó là từ nào
		//Chúng ta phải truy cập từ đó bằng duyệt toàn bộ DATABASE_abc, so sánh stt(tức biến abc) nào = _stt thì
		//xóa nó và thêm từ mới vừa chỉnh sửa vào.
		if (type_sort == 0) {
			//Người dùng chọn đối tượng nào thì sửa đối tượng đó trên DATABASE_123
			DATABASE_123[_stt - 1].tvt = cStr1;
			DATABASE_123[_stt - 1].tg = cStr2;
			//
			int p = -1;
			for (int i = 0; i < DATABASE_abc.size(); i++) {
				//so sánh stt(tức biến abc)  = _stt thì xóa nó
				if (DATABASE_abc[i].abc == _stt) {
					temp_abc = TaoData_abc(DATABASE_abc[i].abc, cStr1, cStr2);
					DATABASE_abc.erase(DATABASE_abc.begin() + i);
					break;
				}
			}
			//Sắp xếp từ mới được thêm, vào DATABASE_abc
			for (int i = 0; i < DATABASE_abc.size(); i++) {
				if (cStr1 < DATABASE_abc[i].tvt) {
					DATABASE_abc.insert(DATABASE_abc.begin() + i, temp_abc);
					p = i;
					break;
				}
			}	
			//Nếu từ mới không bé hơn từ nào thì thêm vào cuối vector
			if (p == -1) {
				DATABASE_abc.push_back(temp_abc);
				p = DATABASE_abc.size() - 1;
			}
			//Xoa du lieu con tro
			delete[] cStr1;
			delete[] cStr2;

			MessageBox::Show("Edited success");
			display_data();
			listView1->Items[_stt - 1]->Selected = 1;
			listView1->Items[_stt - 1]->Focused = 1;
			listView1->Items[_stt - 1]->EnsureVisible();
			PanelTitleBar->Focus();
		}
		else if (type_sort == 1) {
			//Ngược trường hợp trên 1 chút
			DATABASE_123[(DATABASE_abc[_stt - 1].abc) - 1].tvt = cStr1;
			DATABASE_123[(DATABASE_abc[_stt - 1].abc) - 1].tg = cStr2;
			
			temp_abc = TaoData_abc(DATABASE_abc[_stt - 1].abc, cStr1, cStr2);
			DATABASE_abc.erase(DATABASE_abc.begin() + _stt - 1);
			int p = -1;
			for (int i = 0; i < DATABASE_abc.size(); i++) {
				if (cStr1 < DATABASE_abc[i].tvt) {
					DATABASE_abc.insert(DATABASE_abc.begin() + i, temp_abc);
					p = i;
					break;
				}				
			}
			if (p == -1) {
				DATABASE_abc.push_back(temp_abc);
				p = DATABASE_abc.size() - 1;
			}
			//Xoa du lieu con tro
			delete[] cStr1;
			delete[] cStr2;

			MessageBox::Show("Edited success");
			display_data();
			listView1->Items[p]->Selected = 1;
			listView1->Items[p]->Focused = 1;
			listView1->Items[p]->EnsureVisible();
			PanelTitleBar->Focus();
		}		
	}
	else {
		MessageBox::Show("Please select the object to edit");
	}
}
//Nút Xóa
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	if (listView1->SelectedItems->Count > 0) {
		char cStr[4] = { 0 };
		sprintf(cStr, "%s", listView1->SelectedItems[0]->Text);
		int _stt = std::stoi(std::string(cStr)); // chuyển đối tượng được chọn thành số kiểu int để xác định vị trí xóa
		
		if (type_sort == 0) {
			
			for (int i = _stt; i < DATABASE_123.size(); i++) {
				(DATABASE_123[i].stt)--;
			}
			DATABASE_123.erase(DATABASE_123.begin() + _stt - 1);

			for (int i = 0; i < DATABASE_abc.size(); i++) {
				if (DATABASE_abc[i].abc == _stt) {				
					DATABASE_abc.erase(DATABASE_abc.begin() + i);
					break;
				}
			}
			for (int i = 0; i < DATABASE_abc.size(); i++) {
				if (DATABASE_abc[i].abc > _stt) {
					(DATABASE_abc[i].abc)--;					
				}
			}			

		}
		else if (type_sort == 1) {
			
			for (int i = (DATABASE_abc[_stt - 1].abc); i < DATABASE_123.size(); i++) {				
				(DATABASE_123[i].stt)--;			
			}
			DATABASE_123.erase(DATABASE_123.begin() + (DATABASE_abc[_stt - 1].abc) - 1);
			
			for (int i = 0; i < DATABASE_abc.size(); i++) {
				if (DATABASE_abc[i].abc > (DATABASE_abc[_stt - 1].abc)) {
					(DATABASE_abc[i].abc)--;
				}
			}
			DATABASE_abc.erase(DATABASE_abc.begin() + _stt - 1);
		}

		MessageBox::Show("Removed success");
		display_data();
		PanelTitleBar->Focus();
	}
	else {
		MessageBox::Show("Please select the object to remove");
	}
}
//Nut Tim kiem
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {

	if (textBox1->Text == "Search words here..." || textBox1->Text == "") {
		MessageBox::Show("You need to enter the word you want to find");
		return;
	}
	if (checkBox1->Checked == false && checkBox2->Checked == false) {
		MessageBox::Show("You need to choose a word type");
		return;
	}

	char* TCT = new char[textBox1->Text->Length + 1];
	sprintf(TCT, "%s", textBox1->Text);
	int tt;
	if (checkBox1->Checked == true) {//Tim theo tu viet tat
		//tt = SearchTVT(DATABASE_123, std::string(TCT));
		tt = BinarySearchTVT(DATABASE_abc, std::string(TCT));

		if (tt == -1) {
			MessageBox::Show("Can't find this word");
		}
		else {
			MessageBox::Show("This word was found");
			if (type_sort == 1) {
				listView1->Items[tt]->Selected = 1;
				listView1->Items[tt]->Focused = 1;
				listView1->Items[tt]->EnsureVisible();
			}
			else if (type_sort == 0) {
				for (int i = 0; i < DATABASE_abc.size(); i++) {
					if (DATABASE_abc[tt].abc == DATABASE_123[i].stt) {
						listView1->Items[i]->Selected = 1;
						listView1->Items[i]->Focused = 1;
						listView1->Items[i]->EnsureVisible();
						break;
					}
				}

			}
		}
	}
	else {
		tt = SearchTG(DATABASE_123, std::string(TCT)); // Tim theo tu goc
		if (tt == -1) {
			MessageBox::Show("Can't find this word");
		}
		else {
			MessageBox::Show("This word was found");
			if (type_sort == 0) {
				listView1->Items[tt]->Selected = 1;
				listView1->Items[tt]->Focused = 1;
				listView1->Items[tt]->EnsureVisible();
			}
			else if (type_sort == 1) {
				for (int i = 0; i < DATABASE_abc.size(); i++) {
					if (tt + 1 == DATABASE_abc[i].abc) {
						listView1->Items[i]->Selected = 1;
						listView1->Items[i]->Focused = 1;
						listView1->Items[i]->EnsureVisible();
						break;
					}
				}

			}
			
		}
	}
	/*if (tt == -1) {
		MessageBox::Show("Can't find this word");
	}
	else {
		MessageBox::Show("This word was found");
		if (type_sort == 0) {
			listView1->Items[tt]->Selected = 1;
			listView1->Items[tt]->Focused = 1;
			listView1->Items[tt]->EnsureVisible();
		}
		else if (type_sort == 1) {
			for (int i = 0; i < DATABASE_abc.size(); i++) {
				if (tt + 1 == DATABASE_abc[i].abc) {
					listView1->Items[i]->Selected = 1;
					listView1->Items[i]->Focused = 1;
					listView1->Items[i]->EnsureVisible();
					break;
				}
			}

		}
		
	}*/
	delete[] TCT;
}

//Nut Sap Xep AlphaBelt
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	type_sort = 1;
	display_data();
}
// Nut Sap Xep theo thu tu them vao
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	type_sort = 0;
	display_data();
}
// Nut Exit
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	DATABASE_123.clear();
	DATABASE_abc.clear();
	Application::Exit();
}
// Nut Luu
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
	std::ofstream fp;
	fp.open(fileDATA.c_str(), std::ios::out | std::ios::trunc);
	fp.seekp(0, std::ios::beg);

	for (int i = 0; i < DATABASE_123.size(); i++) {
		fp << "[" << DATABASE_123[i].stt << "] " << DATABASE_123[i].tvt << " " << DATABASE_123[i].tg << ".\n";
	}
	fp.close();
	MessageBox::Show("Saved success");
	//DATABASE_123.clear();
	//DATABASE_abc.clear();
}
private: System::Void mainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	readFile("fileDATA.txt"); //Đọc file ngay khi mở app
	display_data();
	//PanelTitleBar->Focus();
}

private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	checkbox();
}
private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	checkbox();
}
private: System::Void txtTVT_Click(System::Object^ sender, System::EventArgs^ e) {
	txtTVT->SelectAll();
}	
private: System::Void txtTG_Click(System::Object^ sender, System::EventArgs^ e) {
	txtTG->SelectAll();
}

private: System::Void textBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	textBox1->Clear();
	textBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
		static_cast<System::Int32>(static_cast<System::Byte>(76)));
}
	
private: System::Void textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Enter)
	{
		button4->PerformClick();
	}
}

};
}
