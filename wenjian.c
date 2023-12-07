#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
作者:
时间:
描述:学生信息管理系统
	1.定义学生信息结构体
		1.学号
		2.姓名
		3.成绩
	2.定义一个结构体类型数组保存学生信息	
*/
//定义学生信息结构体
struct student{
	int num;
	char name[20];
	float score;
};
struct node{
	struct student stu;
	struct node *pnext;
};
//定义学生信息管理数组
struct node *phead = NULL;
enum {ADD=1,DEL,UPDATE,QUERY,OUT};


void menu(void);
int checkNum(int num);
void add(void);
void del(void);
void update(void);
void query(void);
void sort(void);
void addFIle(void);
void readFile(void);
int main(){
		readFile();
		menu();
		return 0;
}

//菜单
void menu(void){
		int num=0;
		char ch='n';
		start:
		do{
		printf("********欢迎使用学生信息管理系统************\n");
		printf("************1.新增学生信息****************\n");
		printf("************2.删除学生信息****************\n");
		printf("************3.修改学生信息****************\n");
		printf("************4.查询学生信息****************\n");
		printf("************5.退出****************\n");
		printf("请选择你要操作的编号:");
		scanf("%d",&num);
		switch(num){
			case ADD:
				printf("************新增学生信息****************\n");
				add();
				break;
			case DEL:
				printf("************删除学生信息****************\n");
				del();
				break;
			case UPDATE:
				printf("************修改学生信息****************\n");
				update();
				break;
			case QUERY:
				printf("************查询学生信息****************\n");
				query();
				break;
			case OUT:
				printf("************退出****************\n");
				return;
			default :
				printf("输入有误，请重新输入！\n");
				goto start;
		}
		getchar();
		printf("是否返回菜单?(y/n)\n");
		scanf("%c",&ch);
		}while(ch == 'y');
		
}
//新增
void add(void){
		char ch ='n';
		do{
		int no=0;
		struct node *ptemp = phead;
		struct node *pnew = malloc(sizeof(struct node));
		
		struct student stus;
		start:
		printf("请输入学生学号:");
		scanf("%d",&no);
		printf("====>%d\n",checkNum(no));
		if(!checkNum(no)){
			goto start;
		}
		stus.num = no;
		printf("请输入学生姓名:");
		scanf("%s",stus.name);
		printf("请输入学生成绩:");
		scanf("%f",&stus.score);
		//对新节点进行赋值
		pnew->pnext = NULL;
		pnew->stu = stus;
		//插入节点
		if(phead == NULL){
			phead = pnew;
		}else{
			while(ptemp->pnext!=NULL){
				ptemp = ptemp->pnext;
			}
			ptemp->pnext = pnew;
		}
		getchar();
		
		printf("是否继续添加?(y/n)");
		scanf("%c",&ch);
	}while(ch == 'y');
	addFIle();
}
//检查学号是否存在
int checkNum(int num){
	struct node *ptemp = phead;
	if(phead == NULL){
		return 1;
	}
	while(ptemp !=NULL){
		if(ptemp->stu.num == num){
			return 0;
		}
		ptemp= ptemp ->pnext;
	}
	
	return 1;
}




//删除
void del(void){
	struct node *ptemp = phead;
	struct node *pdel=NULL;
	int num=0;
	if(phead == NULL){
		printf("数据为空!\n");
		return;
	}
	printf("请输入您要删除的学生学号:");
	scanf("%d",&num);
	
	//判断第一个节点是否是要删除的节点
	if(phead->stu.num == num){
		pdel = phead;
		phead = phead->pnext;
		free(pdel);
		printf("已删除\n");
		addFIle();
		return;
	}
	while(ptemp->pnext !=NULL){
		if(ptemp->pnext->stu.num == num){
			pdel = ptemp->pnext;
			ptemp ->pnext = ptemp->pnext->pnext;
			free(pdel);
			printf("已删除\n");
			addFIle();
			return;
		}
		ptemp = ptemp->pnext;
	}
	printf("查无此人，无法删除!\n");
}
void update(void){
	
}

//查询
void query(void){
	sort();
	struct node *ptemp = phead;
	printf("学号\t\t姓名\t\t成绩\n");
	while(ptemp != NULL){
		printf("%d\t\t%s\t\t%.2f\n",ptemp->stu.num,ptemp->stu.name,ptemp->stu.score);
		ptemp = ptemp->pnext;
	}
}

/*
排序--选择排序
*/
void sort(void){
	struct node *first = NULL;
	struct node *second = NULL;
	for(first=phead;first!=NULL;first=first->pnext){
		for(second = first->pnext;second!=NULL;second=second->pnext){
			if(first->stu.score < second->stu.score){
				//不动链表，动数据
				struct student stus = first->stu;
				first->stu=second->stu;
				second->stu = stus;
			}
		}
	}
}

/*
保存数据到文件中
*/
void addFIle(void){
	struct node *ptemp = phead;  //操作节点
	FILE *fp = fopen("student.csv","w+");
	if(fp == NULL){
		perror("fopen");
		return;
	}
	if(phead == NULL){
		return;
	}
	while(ptemp !=NULL){
		fprintf(fp,"%d\t%s\t%.2f\n",ptemp->stu.num,ptemp->stu.name,ptemp->stu.score);
		ptemp = ptemp->pnext;
	}
	//关闭文件流
	fclose(fp);	
	
}

void readFile(void){
	FILE *fp = fopen("student.csv","r");
	if(fp == NULL){
		perror("fopen");
		return;
	}
	fseek(fp,0,SEEK_SET);
	
	while(!feof(fp)){
		struct node *ptemp = phead; 
		struct node *pnew=malloc(sizeof(struct node));
		pnew->pnext = NULL;
		fscanf(fp,"%d\t%s\t%f\n",&pnew->stu.num,pnew->stu.name,&pnew->stu.score);
		if(phead == NULL){
			phead = pnew;
			
		}else{
			while(ptemp->pnext !=NULL){
				ptemp = ptemp->pnext;
			}
			ptemp->pnext = pnew;
		}
	}
	query();
}

































