#include <windows.h>
class MyClass
{
public:
	MyClass()
	{
		::MessageBox(NULL, "���ǹ��캯��", "Elven", NULL);
	}
};
MyClass a;
int main()
{
	::MessageBox(NULL, "����main����", "Main", NULL);
	return 0;
}