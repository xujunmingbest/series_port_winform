#include "MyForm.h"



using namespace PLC����ͨ��;
[STAThreadAttribute]
void main() {
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm);

}