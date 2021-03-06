﻿#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
							//宏定义&全局变量&函数声明
#define LEN sizeof(struct Movie)
int n = 0, m,nm=5,ti=4;
struct Movie * creat(void);
void search(struct Movie * head);
struct Movie * numsearch(struct Movie * head);
struct Movie * filmsearch(struct Movie * head);
struct Movie * namesearch(struct Movie * head);
struct Movie * agersearch(struct Movie * head);
struct Movie * typesearch(struct Movie * head);
struct Movie * countrysearch(struct Movie * head);
void hot_order(struct Movie * head);
void output(struct Movie * head);
void order(struct Movie * head);
void del(struct Movie * head);
void change(struct Movie * head);
void add(struct Movie * head);
struct Movie * entersys(void);
void exitsys(struct Movie * head);
int login(void);
void regis(void);
int user_infor_read_cmp(struct user tep);
void user_infor_write(struct user tep);

struct Movie				//定义影片结构体，包含编号、年代、导演名、主演名、热度、产国、类型、片名;下一节点指针
{
	long num;
	int age;
	char dir_nam[10];
	char lead_actor_name[10];
	int hot;
	char country[5];
	char type[5];
	char film_name[10];
	struct Movie * next;
};
union imfor_var				//定义共用体（联合），包含整形和字符串，用于在函数间传递输入查询信息。
{
	int age;
	char eve[15];
}ran_con;
struct user
{
	int acc;
	char pas[21];
}now_user;
							//影院管理系统-----主函数部分------
int main(void)
{
	int op,us;
	struct Movie * head;
	while (1)
	{	
		printf("\t\t\t\t\t进入影院管理系统");
		printf("请选择：1、登陆\n2、注册");
		scanf("%d", &op);
		getchar();
		if (op == 1)
		{
			us=login();
			if(us!=2)
			break;
		}
		else if (op == 2)
		{
			regis();
			printf("注册完成！\n载入账户");
			break;
		}
		else
			printf("请输入正确的指令！\n");
	}
	if (us == 1)//普通用户
	{
		printf("登陆成功！用户类型：普通用户\n请选择：1、进入管理系统\n");
		scanf("%d", &op);
		getchar();
		if (op == 1)
		{
			head=entersys();
			printf("信息载入完毕！\n");
			while (1)
			{
				printf("请选择：1、进入查找模式\n2、热度排行榜\n3、退出系统\n");
				scanf("%d", &op);
				getchar();
				switch (op)
				{
				case 1:search(head); break;
				case 2:; break;
				case 3:exitsys(head); exit(0); break;
				default:printf("输入正确指令！");
				}
			}
		}
	}
	if (us == 0)//管理员
	{
		head = entersys();
		printf("登陆成功！用户类型：管理员\n");
		while (1)
		{
			printf("请选择：1、查找\n2、删除\n3、修改\n4、插入\n5、重新录入系统信息\n6、退出系统\n");
			scanf("%d", &op);
			getchar();
			switch (op)
			{
			case 1:search(head); break;
			case 2:del(head); break;
			case 3:change(head); break;
			case 4:add(head); break;
			case 5:head = creat(); break;
			case 6:exitsys(head); exit(0); break;
			default:printf("请输入正确指令！");
			}
		}
	}
}

										//------调用函数部分----
										//信息录入链表
struct Movie * creat(void)
{
	struct Movie * p1, * p2;
	struct Movie * head=NULL;
	n = 0;
	p1 = p2 = (struct Movie *)malloc(LEN);
	printf("开始录入影片信息：（编号，年代，导演名，主演名，类型，热度，产国，片名,遇'0'则止）\n");
	scanf("%ld,%d,%s,%s,%s,%d,%s,%s", &p1->num, &p1->age, &p1->dir_nam, &p1->lead_actor_name, &p1->type,&p1->hot,&p1->country,&p1->film_name);
	while (p1->num != 0)
	{
		n += 1;
		if (n == 1)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (struct Movie *)malloc(LEN);
		scanf("%ld,%d,%s,%s,%s,%d,%s,%s", &p1->num, &p1->age, &p1->dir_nam, &p1->lead_actor_name, &p1->type, &p1->hot, &p1->country, &p1->film_name);
		getchar();
	}
	p2->num = NULL;
	return(head);
}


									//查找目标节点或符合条件的子链
void search(struct Movie * head)
{
	int option;
	struct Movie * tep_head;
	int End = 0;
	char already_choice[4][20] = {"姓名：未选择","年代：未选择","类型：未选择","产国：未选择"};
	char tep_choice[10];
	int i = 0;
	int j;
	printf("请选择查找方式：\n");
	printf("1、编号查找\n2、片名查找\n3、范围查询\n");
	scanf("%d", &option);
	getchar();
	if (option == 1)
		numsearch(head);
	else if (option == 2)
		filmsearch(head);
	else
	{
		tep_head = head;
		printf("选择范围：\n1、导演/主演名查找\n2、年代查找\n3、类型查找\n4、产国查找");
		scanf("%d", &option);
		getchar();
		while (End != 1)
		{
			switch (option)
			{
			case 1:
				tep_head = namesearch(tep_head);
				strcpy(already_choice[i], "姓名：");
				strcat(already_choice[i], ran_con.eve);
				if (i <3) i += 1;
				break;
			case 2:
				tep_head = agersearch(tep_head); 
				strcpy(already_choice[i], "年代：");
				strcat(already_choice[i], ran_con.eve);
				if (i <3) i += 1;
				break;
			case 3:
				tep_head = typesearch(tep_head);
				strcpy(already_choice[i], "类型：");
				strcat(already_choice[i], ran_con.eve);
				if (i <3) i += 1;
				break;
			case 4:
				tep_head = countrysearch(tep_head);
				strcpy(already_choice[i], "产国：");
				strcat(already_choice[i], ran_con.eve);
				if (i <3) i += 1;
				break;
			default:
				printf("请输入正确的指令!\n\t再次选择\n");
			}
			for (j = 0; j < 4; j++)
				printf("%s", already_choice[i]);
			printf("\n是否继续缩小范围？(0——继续||1——退出)");
			scanf("%d", &End);
			if (End == 0)
			{
				printf("选择范围：\n1、导演/主演名查找\n2、年代查找\n3、产国查找");
				scanf("%d", &option);
			}
		}
	}
}
struct Movie * numsearch(struct Movie * head)		//编号查找函数
{
	if (head != NULL)
		{
			struct Movie* p1;
			long a;
			int i=0;
			printf("请输入要查找的编号：");
			scanf("%ld", &a);
			getchar();
			for (p1=head;p1!=NULL;p1=p1->next)
			{
				if (p1->num == a)
				{
					p1->hot += 1;
					printf("%ld,%d,%s,%s,%s,%d,%s,%s", p1->num, p1->age, p1->dir_nam, p1->lead_actor_name, p1->type, p1->hot, p1->country, p1->film_name);
					return p1;
				}
				else
					i++;
			}
			if (i == n)
				printf("未找到该影片信息！");
		}
	else
		printf("系统未载入信息！");
}
struct Movie * filmsearch(struct Movie * head)
{
	if (head != NULL)
	{
		char tep_film[10];
		struct Movie * p1;
		int i = 0;
		printf("输入你想查找的片名：");
		scanf("%s", tep_film);
		getchar();
		for (p1 = head; p1 != NULL; p1 = p1->next)
		{
			if (!strcmp(p1->film_name, tep_film))
			{
				p1->hot += 1;
				printf("%ld,%d,%s,%s,%s,%d,%s,%s", p1->num, p1->age, p1->dir_nam, p1->lead_actor_name, p1->type, p1->hot, p1->country, p1->film_name);
				return p1;
			}
			else
				i++;
		}
		if (i == n)
			printf("未找到该影片信息！");
	}
	else
		printf("系统未载入信息！");
}
struct Movie * namesearch(struct Movie * head)				//姓名查找函数
{
	if (head != NULL)
	{
		struct Movie* p1, *p2, *p3;
		struct Movie* tep_head = NULL;
		int i=0;
		m = 0;
		printf("请输入要查找的导演/主演姓名：");
		scanf("%s",&ran_con.eve);
		getchar();
		for (p1 = head; p1 != NULL; p1 = p1->next)
		{
			if ((!strcmp(p1->dir_nam,ran_con.eve))|| (!strcmp(p1->lead_actor_name, ran_con.eve)))
			{
				if (tep_head == NULL)
				{
					tep_head = (struct Movie*)malloc(LEN);
					*tep_head = *p1;
					tep_head->next = NULL;
					p2 = tep_head;
				}
				else
				{
					p3= (struct Movie*)malloc(LEN);
					*p3 = *p1;
					p3->next = NULL;
					p2->next = p3;
					p2 = p3;
				}
				m += 1;
			}
			else
				i++;
		}
		if (i == n)
			printf("未找到该与该人物有关的影片信息！");
		else
		{
			output(tep_head);
			return tep_head;
		}
	}
	else
		printf("系统未载入信息！");
}
struct Movie * agersearch(struct Movie * head)				//年代查找函数
{
	if (head != NULL)
	{
		struct Movie * p1,* p2,* p3;
		struct Movie * tep_head=NULL;
		int i=0;
		char temp[15];
		m = 0;
		printf("请输入要查找的年代：");
		scanf("%d",&ran_con.age);
		getchar();
		for (p1 = head; p1 != NULL; p1 = p1->next)
		{
			if (p1->age==ran_con.age)
			{
				if (tep_head == NULL)
				{
					tep_head = (struct Movie*)malloc(LEN);
					*tep_head = *p1;
					tep_head->next = NULL;
					p2 = tep_head;
				}
				else
				{
					p3 = (struct Movie*)malloc(LEN);
					*p3 = *p1;
					p3->next = NULL;
					p2->next = p3;
					p2 = p3;
				}
				m += 1;
			}
			else
				i++;
		}
		if (i == n)
			printf("未找到该年代影片信息！");
		else
		{
			output(tep_head);
			return tep_head;
		}
		itoa(ran_con.age, temp, 10);
		strcpy(ran_con.eve, temp);
	}
	else
		printf("系统未载入信息！");
}
struct Movie * typesearch(struct Movie * head)
{
	if (head != NULL)
	{
		struct Movie* p1, *p2, *p3;
		struct Movie* tep_head = NULL;
		int i = 0;
		m = 0;
		printf("请输入要查找的类型：");
		scanf("%s", &ran_con.eve);
		getchar();
		for (p1 = head; p1 != NULL; p1 = p1->next)
		{
			if ((!strcmp(p1->type, ran_con.eve)))
			{
				if (tep_head == NULL)
				{
					tep_head = (struct Movie*)malloc(LEN);
					*tep_head = *p1;
					tep_head->next = NULL;
					p2 = tep_head;
				}
				else
				{
					p3 = (struct Movie*)malloc(LEN);
					*p3 = *p1;
					p3->next = NULL;
					p2->next = p3;
					p2 = p3;
				}
				m += 1;
			}
			else
				i++;
		}
		if (i == n)
			printf("未找到该类型的影片信息！");
		else
		{
			output(tep_head);
			return tep_head;
		}
	}
	else
		printf("系统未载入信息！");
}
struct Movie * countrysearch(struct Movie * head)
{
	if (head != NULL)
	{
		struct Movie* p1, *p2, *p3;
		struct Movie* tep_head = NULL;
		int i = 0;
		m = 0;
		printf("请输入要查找的产国：");
		scanf("%s", &ran_con.eve);
		getchar();
		for (p1 = head; p1 != NULL; p1 = p1->next)
		{
			if ((!strcmp(p1->country, ran_con.eve)))
			{
				if (tep_head == NULL)
				{
					tep_head = (struct Movie*)malloc(LEN);
					*tep_head = *p1;
					tep_head->next = NULL;
					p2 = tep_head;
				}
				else
				{
					p3 = (struct Movie*)malloc(LEN);
					*p3 = *p1;
					p3->next = NULL;
					p2->next = p3;
					p2 = p3;
				}
				m += 1;
			}
			else
				i++;
		}
		if (i == n)
			printf("未找到该国家的影片信息！");
		else
		{
			output(tep_head);
			return tep_head;
		}
	}
	else
		printf("系统未载入信息！");
}
void hot_order(struct Movie * head)
{
	printf("热度排行榜");
	order(head);
	output(head);
}

									//链表输出
void output(struct Movie * head)
{
	struct Movie * p;
	printf("共有%d个结果。\n", m);
	p = head;
	if (head != NULL)
	{
		do
		{
			printf("%ld,%d,%s,%s,%s,%d,%s,%s", p->num, p->age, p->dir_nam, p->lead_actor_name, p->type, p->hot, p->country, p->film_name);
			p = p->next;
		} while (p != NULL);
	}
	else
		printf("错误！！！");
}			
									//链表排序(冒泡)
void order(struct Movie * head)
{
	if ((head->next == NULL) || (head->next->next == NULL))
		return;
	struct  Movie *thead,* pre, *cur, *tnext, *end, *tep;
	thead = head;
	end = NULL;
	while (thead->next != end)
	{
		for (pre = thead, cur = pre->next, tnext = cur->next; tnext != end; pre->next, cur = cur->next, tnext = tnext->next)
		{
			if (cur->hot < tnext->hot)
			{
				cur->next = tnext->next;
				pre->next = tnext;
				tnext->next = cur;
				tep = tnext;
				tnext = cur;
				cur = tep;
			}
		}
		end = cur;
	}
}
									//节点删除
void del(struct Movie * head)						
{
	long a;
	struct Movie * p1;
	struct Movie * p2 = head;
	if (head == NULL)
		printf("系统未载入信息！");
	else
	{
		printf("请输入要删除的编号：\n");
		scanf("%ld", &a);
		getchar();
		if (head->num == a)
		{
			p1 = head;
			head = head->next;
			free(p1);
			printf("已删除！\n"), n -= 1;
		}
		else
		{
			for (p2; p2->next; p2 = p2->next)
			{
				if (p2->next->num == a)
				{
					p1 = p2->next;
					p2->next = p1->next;
					free(p1);
				}
				printf("已删除！\n"), n -= 1;
			}
		}
	}
}
									//节点修改(应先应用查找函数推荐编号或片名）
void change(struct Movie * head)
{
	int op;
	struct Movie * p1;
	char t_dir[10],t_lea[10],t_cour[5],t_type[5],t_nam[10];
	int t_num, t_age;
	while (1)
	{
		printf("选择修改方式：1、编号寻找后修改\n2、片名查找后修改");
		scanf("%d", &op);
		if (op == 1)
		{
			p1 = numsearch(head);
			break;
		}
		else if (op == 2)
		{
			p1 = filmsearch(head);
			break;
		}
		else
			printf("指令输入错误，返回。");
	}
	while (1)
	{
		printf("选择当前影片需要修改的值：1、编号\n2、年代\n3、导演名\n4、主演名\n5、产国\n6、类型\n7、片名\n8、退出修改\n");
		scanf("%d", &op);
		getchar();
		printf("输入目标值");
		switch (op)
		{
		case 1:
			scanf("%ld",&t_num);
			p1->num = t_num;
			break;
		case 2:
			scanf("%d",&t_age);
			p1->age = t_age;
			break;
		case 3:
			scanf("%s", t_dir);
			strcpy(p1->dir_nam,t_dir); 
			break;
		case 4:
			scanf("%s",t_lea);
			strcpy(p1->lead_actor_name, t_lea);
			break;
		case 5:
			scanf("%s",t_cour);
			strcpy(p1->country, t_cour);
			break;
		case 6:
			scanf("%s",t_type);
			strcpy(p1->type, t_type);
			break;
		case 7:
			scanf("%s",t_nam);
			strcpy(p1->film_name, t_nam);
			break;
		case 8:
			break;
		default:printf("输入正确的指令！");
		}
		getchar();
		if (op == 8)
			break;
	}
}
									//节点插入（尾插）
void add(struct Movie * head)
{
	struct Movie * p1 = head;
	struct Movie * p2 = (struct Movie *)malloc(LEN);
	printf("输入要添加的影片信息：（编号，年代，导演名，主演名，类型，热度，产国，片名）");
	scanf("%ld,%d,%s,%s,%s,%d,%s,%s", &p1->num, &p1->age, &p1->dir_nam, &p1->lead_actor_name, &p1->type, &p1->hot, &p1->country, &p1->film_name);
	getchar();
	p2->next = NULL;
	while (p1->next != NULL)
		p1 = p1->next;
	p1->next = p2;
	p1 = p2;
	n += 1;
}

									//进入管理系统（数据从文件进入链表)
struct Movie * entersys (void)
{
	FILE *fp;
	struct Movie * p1,* p2,* head;
	char s;
	char t_num[11],t_age[5],t_hot[4],
	int st=0,i=0;
	fp = fopen("movie.txt", "r");
	while(!feof(fp))
	{
		p1 = (struct Movie *)malloc(LEN);
		if (st == 0)
		{
			head = p1;
			p2 = p1;
			st += 1;
		}
		else
		{
			p2->next = p1;
			p2 = p1;
		}
		fgets(t_num, 11, fp);
		p1->num = atol(t_num);
		getc(fp);
		fgets(t_age, 5, fp);
		p1->age = atoi(t_age);
		while (1)
		{
			s = fgetc(fp);
			if (s == ' ')
				break;
			else
			{
				p1->dir_nam[i] = s;
				i += 1;
			}
		}
		while (1)
		{
			s = fgetc(fp);
			if (s == ' ')
				break;
			else
			{
				p1->lead_actor_name[i] = s;
				i += 1;
			}
		}
		fgets(t_hot, 4, fp);
		p1->hot = atoi(t_hot);
		while (1)
		{
			s = fgetc(fp);
			if (s == ' ')
				break;
			else
			{
				p1->country[i] = s;
				i += 1;
			}
		}
		while (1)
		{
			s = fgetc(fp);
			if (s == ' ')
				break;
			else
			{
				p1->type[i] = s;
				i += 1;
			}
		}
		while (1)
		{
			s = fgetc(fp);
			if (s == '\n')
				break;
			else
			{
				p1->film_name[i] = s;
				i += 1;
			}
		}
		getc(fp);
	}
	fclose(fp);
}
									//退出管理系统（数据从链表录入 文件）
void exitsys(struct Movie * head)
{
	FILE *fp;
	fp = fopen("movie.txt", "w");
	struct Movie * p;
	p = head;
	char t_num[11];
	char t_age[5];
	char t_hot[4];
	while (p != NULL)
	{
		ltoa(p->num, t_num, 10);
		itoa(p->age, t_age, 10);
		itoa(p->hot, t_hot, 10);
		fputs(t_num, fp);
		fputs(" ", fp);
		fputs(t_age, fp);
		fputs(" ", fp);
		fputs(p->dir_nam, fp);
		fputs(" ", fp);
		fputs(p->lead_actor_name, fp);
		fputs(" ", fp);
		fputs(t_hot, fp);
		fputs(" ", fp);
		fputs(p->country, fp);
		fputs(" ", fp);
		fputs(p->type, fp);
		fputs(" ", fp);
		fputs(p->film_name, fp);
		fputs("\n", fp);
		fputs(" ", fp);
		p = p->next;
	}
	fclose(fp);
}

									//登陆模块


int login(void)
{
	struct user tep;
	int ju;
	printf("请输入账号：");
	scanf("%d", &tep.acc);
	getchar();
	printf("请输入密码：");
	scanf("%s", tep.pas);
	getchar();
	ju=user_infor_read_cmp(tep);
	return ju;
}
void regis(void)
{
	struct user tep;
	printf("输入注册的账号：（纯数字，最多十位，不可以0开头）");
	scanf("%d", &tep.acc);
	getchar();
	printf("输入密码：（不超过20位)");
	scanf("%s",tep.pas);
	getchar();
	user_infor_write(tep);
}
				//用户文件
 int user_infor_read_cmp(struct user tep)
{
	 FILE * fp;
	 char a[11];
	 char b[21];
	 char s;
	 int i = 0, n, j;
	 fp=fopen( "user.txt", "r");
	 while (1)
	 {
		fgets(a, 11, fp);
		n = atoi(a);
		getc(fp);
		while (1)
		{
			s = fgetc(fp);
			if (s == '\n')
			break;
			else
			{
				b[i] = s;
				i += 1;
			}
		}
		if (tep.acc == n)
		{
			if (!strcmp(tep.pas, b))
				if (b[0] == '0')
				{
					now_user = tep;
					fclose(fp);		
					return 0;
				}
				else
				{
					now_user = tep;
					fclose(fp);
					return 1;
				}
			else
			{
				ti -= 1;
				if (ti > 0)
				{
					printf("密码有误请重试，剩余%d次", ti);
					fclose(fp);
					return 2;
				}
				else
				{
					fclose(fp);
					exit(0);
				}
			}
		}
		else
			j += 1;
		if (j == nm)
		{
			printf("账号输入错误！");
			fclose(fp);
			return 2;
		}
	 }
	 fclose(fp);
}

 void user_infor_write(struct user tep)
 {
	 FILE * fp;
	 fp = fopen("user.txt", "a");
	 struct user tep ;
	 char tep_acc[11];
	 itoa(tep.acc, tep_acc, 10);
	 fputs(tep_acc, fp);
	 fputs(" ", fp);
	 fputs(tep.pas, fp);
	 fputs("\n", fp);
	 fclose(fp);
	 nm += 1;
	 now_user = tep;
 }