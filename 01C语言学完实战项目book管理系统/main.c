#include <stdio.h>//����ͷ�ļ�
#include<string.h>//����ͷ�ļ�
#include<ctype.h>//ר��ר�Ŵ����ַ���

typedef struct Node
{
	char BookName[50];//����
	int BookNumber;//���
	float BookPrice;//����
	struct Node* next;//ָ����һ���ڵ��ָ��
}Node;
Node* AppendNode(Node* head, char* BookName, float BookPrice, int BookNumber);
void QueryNode(Node* head, char* BookName);
void ModifyNode(Node* head, char* BookName, float BookPrice);
Node* DeleteNode(Node* head, char* BookName);
int main()
{
	Node* head = NULL;//����ͷָ��
	char szBookName[50];
	float fBookPrice = 0;
	float fNewBookPrice = 0;
	int nBookNumber = 0;
	int Readflag = 0;
	while (1)
	{
		printf("��ѡ������Ҫʹ�õĹ��ܣ�\n");
		printf("1.����鼮��Ϣ\n");
		printf("2.��ѯ�鼮��Ϣ\n");
		printf("3.�޸��鼮��Ϣ\n");
		printf("4.ɾ���鼮��Ϣ\n");
		scanf("%d", &Readflag);
		switch (Readflag)
		{
		case 1:
			printf("������������");
			scanf("%s", szBookName);
			printf("���붨�ۣ�");
			scanf("%f", &fBookPrice);
			printf("������ţ�");
			scanf("%d", &nBookNumber);
			head = AppendNode(head, szBookName, fBookPrice, nBookNumber);
			break;
		case 2:
			printf("������������");
			scanf("%s", szBookName);
			QueryNode(head, szBookName);
			break;
		case 3:
			printf("������������");
			scanf("%s", szBookName);
			printf("�������¶��ۣ�");
			scanf("%f", &fNewBookPrice);
			ModifyNode(head, szBookName, fNewBookPrice);
			break;
		case 4:
			printf("������������");
			scanf("%s", szBookName);
			head = DeleteNode(head, szBookName);
			break;
		default:
			break;
		}

	}
	return 0;
}

Node* AppendNode(Node* head, char* BookName, float BookPrice, int BookNumber)//ĩβ��ӽڵ�
{
	Node* pNewNode = NULL;//����һ���½ڵ�ָ��
	Node* pHeadNode = head;//����һ��ָ��ͷָ���ָ��
	pNewNode = (Node*)malloc(sizeof(Node));//����һ���µĽڵ㲢�����ڴ�
	if (pNewNode == NULL)//���û������ɹ�
	{
		printf("memory malloc failed!\n");
		exit(0);
	}
	if (head == NULL)//���û��ͷ�ڵ�
	{
		head = pNewNode;//����һ��ͷ�ڵ�
	}
	else
	{
		while (pHeadNode->next != NULL)
		{
			pHeadNode = pHeadNode->next;
		}
		pHeadNode->next = pNewNode;
	}
	strcpy(pNewNode->BookName, BookName);
	pNewNode->BookPrice = BookPrice;
	pNewNode->BookNumber = BookNumber;
	pNewNode->next = NULL;
	return head;
}

void QueryNode(Node* head, char* BookName)//��ѯ����
{
	int flag = 0;
	if (head == NULL)//���ͷָ��Ϊ��
	{
		printf("head == NULL!");
		exit(0);
	}
	if (strcmp(BookName, head->BookName) == 0)
	{
		printf("������%s\n���ۣ�%f\n��ţ�%d\n", head->BookName, head->BookPrice, head->BookNumber);
		flag = 1;
	}
	while (head->next != NULL)
	{
		head = head->next;
		if (strcmp(BookName, head->BookName) == 0)
		{
			printf("������%s\n���ۣ�%f\n��ţ�%d\n", head->BookName, head->BookPrice, head->BookNumber);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("Query failed!");
	}
}

void ModifyNode(Node* head, char* BookName, float BookPrice)
{
	int flag = 0;
	if (head == NULL)//���ͷָ��Ϊ��
	{
		printf("head == NULL!");
		exit(0);
	}
	if (strcmp(BookName, head->BookName) == 0)
	{
		head->BookPrice = BookPrice;
		printf("�¶��ۣ�%f\n", head->BookName, head->BookPrice, head->BookNumber);
		flag = 1;
	}
	while (head->next != NULL)
	{
		head = head->next;
		if (strcmp(BookName, head->BookName) == 0)
		{
			printf("�¶��ۣ�%f\n", head->BookName, head->BookPrice, head->BookNumber);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("Modify failed!");
	}
}

Node* DeleteNode(Node* head, char* BookName)
{
	Node* pNode = NULL;
	if (head == NULL)//���ͷָ��Ϊ��
	{
		printf("head == NULL!");
		exit(0);
	}
	if (strcmp(BookName, head->BookName) == 0)
	{
		if (head->next != NULL)
		{
			pNode = head->next;
			free(head);
			return pNode;
		}
		else
		{
			printf("List NNLL!");
			return NULL;
		}
	}
	if (strcmp(BookName, head->next->BookName) == 0);
	{
		if (head->next->next != NULL)
		{
			pNode = head->next->next;
			head->next = head;
			return head;
		}
	}
	while (head->next->next != NULL)
	{
		if (strcmp(BookName, head->next->next->BookName) == 0)
		{
			pNode = head->next->next->next;
			head->next->next = pNode;
			return head;
		}
	}
}
