#include <stdio.h>
#include <string.h>

typedef struct Student
{
	int id=0;
	int age=0;
	char name[30];
};

int main()
{
	Student stu;
	printf("���������ѧ�ţ�");
	scanf("%d", &stu.id);
	printf("������������䣺");
	scanf("%d", &stu.age);
	strcpy(stu.name, "Elven");
	printf("ѧ�ţ�%d\n", stu.id);
	printf("���䣺%d\n", stu.age);
	printf("���֣�%s\n", stu.name);
	return 0;
}