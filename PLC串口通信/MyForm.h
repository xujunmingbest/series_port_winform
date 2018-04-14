#pragma once
#include <iostream>
using namespace std;
namespace PLC串口通信 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	/// <summary>
	/// MyForm 摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
#define FASONG 0
#define JIESHOU 1
#define XITONG 2
	public:
		MyForm(void)
		{
			InitializeComponent();
			CheckForIllegalCrossThreadCalls = false;
			output(XITONG, "-----准备就绪-----");
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

		void serialPort1Open() {
			serialPort1->Close();
			if (asd) {
				asd->Abort();
			}
			try{
				serialPort1->PortName = textBox1->Text;
				serialPort1->ReceivedBytesThreshold = 1;
				serialPort1->DataBits = 8;
				serialPort1->Parity = System::IO::Ports::Parity::None; //无奇偶校验位
				//serialPort1->StopBits = System::IO::Ports::StopBits::One;//设置停止位为1
				serialPort1->Open(); //串口打开
			}
			catch(System::Exception ^e){
				output(XITONG,"串口打开失败");
				return;
			}
			output(XITONG, textBox1->Text+"串口打开成功");
			asd = gcnew Thread(gcnew ThreadStart(this, &MyForm::Recv));
			asd->Start();
			asd->IsBackground = true;
		}
		void serialPort1Close() {
			serialPort1->Close();
			output(XITONG, "串口关闭");
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::Button^  button3;
			 Thread^ asd;
		void Send() {
			int len = richTextBox2->Text->Length;
			char *b = new char[len * 2 + 1];
			memset(b, 0x00, len * 2 + 1);
			snprintf(b, len * 2 + 1, "%s", richTextBox2->Text);
			int alen = strlen(b);
			cli::array<unsigned char>^ buffer = gcnew cli::array<unsigned char>(alen);
			for (int i = 0; i < len * 2; i++)
			{
				if (b[i] != 0x00) {
					buffer[i] = b[i];
				}
				else {
					break;
				}
			}
			delete[] b;
			try {
				serialPort1->Write(buffer, 0, alen);//发送指令0x55
				if (alen == 0) {
					throw"发送0字节";
				}
			}
			catch (System::Exception ^e) {
				return;
			}
			output(FASONG, richTextBox2->Text);
		}
		void Recv() {
			button2->Enabled = false;
			while (1) {
				cli::array<unsigned char>^ r1buff;
				r1buff = gcnew cli::array<unsigned char>(1);
				cli::array<unsigned char>^ rbuff;
				rbuff = gcnew cli::array<unsigned char>(100);
				int recvlen;
				try {
					recvlen = serialPort1->Read(r1buff, 0, 1);// 估计是可以返回 字符串的 读取个数
					if (recvlen <= 0) {
						throw "串口退出";
					}
					recvlen += serialPort1->Read(rbuff, 0, 100);// 估计是可以返回 字符串的 读取个数
					if (recvlen <= 0) {
						throw "串口退出";
					}
				}
				catch(System::Exception ^e){
					Console::Write(e->ToString());
					button2->Enabled = true;
					return;
				}
				cli::array<unsigned char>^ buff = gcnew cli::array<unsigned char>(101);
				r1buff->CopyTo(buff, 0);
				rbuff->CopyTo(buff, 1);
				cli::pin_ptr<unsigned char> c = &buff[0];
				char *pinp = (char *)c;
				cout << "接收长度:" << recvlen << endl;
				output(JIESHOU, gcnew String(pinp));
			}
		}


	private: System::IO::Ports::SerialPort^  serialPort1;
	protected:
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RichTextBox^  richTextBox2;











	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->richTextBox1->Location = System::Drawing::Point(3, 21);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(903, 491);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->richTextBox1);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->groupBox1->Location = System::Drawing::Point(0, 312);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(909, 515);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"串口日志";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(21, 86);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(92, 35);
			this->button1->TabIndex = 4;
			this->button1->Text = L"点击发送";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(119, 86);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(229, 96);
			this->richTextBox2->TabIndex = 5;
			this->richTextBox2->Text = L"";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(100, 23);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(285, 25);
			this->textBox1->TabIndex = 6;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(18, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 15);
			this->label1->TabIndex = 7;
			this->label1->Text = L"com口名字";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(21, 127);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(92, 35);
			this->button2->TabIndex = 8;
			this->button2->Text = L"串口打开";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(21, 168);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(92, 35);
			this->button3->TabIndex = 11;
			this->button3->Text = L"串口关闭";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(909, 827);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MyForm";
			this->Text = L"串口PLC通信";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}


			 void output(int log_type,String^ in) {
				 String ^o;
				 switch (log_type) {
				 case FASONG:o = "发送:" + in; break;
				 case JIESHOU:o = "接收:" + in; break;
				 case XITONG:o = "系统消息:" + in; break;
				 }
				 richTextBox1->AppendText(o + "\n");
				 richTextBox1->SelectionStart = richTextBox1->TextLength - o->Length - 1;
				 richTextBox1->SelectionLength = o->Length;
				 switch (log_type){
				 case FASONG:richTextBox1->SelectionColor = Color::Blue; break;
				 case JIESHOU:richTextBox1->SelectionColor = Color::Red; break;
				 case XITONG:richTextBox1->SelectionColor = Color::Green; break;
				 }
				 richTextBox1->SelectionStart = richTextBox1->Text->Length;
				 richTextBox1->SelectionLength = 0;
				 richTextBox1->Focus();
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	serialPort1Open();

}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	serialPort1Close();

}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	Send();

}
};
}
