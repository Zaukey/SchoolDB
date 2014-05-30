#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NIN 1000
#define STLEN 256
#define KAMO_MAX 20
#define NAME_MAX 50

typedef char *String;

struct Data{
	int no;
	String name;
	int point[KAMO_MAX];
	float ave;
	int rank;
	struct Data *next;
};
typedef struct Data DATA; 


void init(void);
void Rel(void);
void Create(void);
void Display(void);
void Input(void);
void Output(void);
void Add(void);
void Del(void);
void Edit(void);
void addData(int i, String c, int p[]);
void delData(int i);
void Rank(void);
void Closer(void);


DATA *head;
int kamo;
int preno;
String kstr,kam[KAMO_MAX];


int main()
{
	init();
	int n=1;
	while(n!=0){
		puts("");
		puts("");
		puts("/_/_/_/_/_/_/_/_/_/_/_/_/_/");
		puts("1.データの作成");
		puts("2.データの追加");
		puts("3.データの削除");
		puts("4.データの表示");
		puts("5.データをセーブする");
		puts("6.データをロードする");
		puts("7.データの編集");
		puts("0.終了");
		puts("/_/_/_/_/_/_/_/_/_/_/_/_/_/");
		puts("");
		printf("→");
		fflush(stdin);
		scanf("%d",&n);
		fflush(stdin);
		switch(n){
			case 0 :puts("END"); break;
			case 1 :Create(); break;
			case 2 :Add(); break;
			case 3 :Del(); break;
			case 4 :Display(); break;
			case 5 :Output(); break;
			case 6 :Input(); break;
			case 7 :Edit(); break;
			default :puts("正しい値を入力してください"); break;
		}
	}
	return 0;
}

void init(){
	int i;
	for(i=0;i<kamo;i++) kam[i]=NULL;
	kamo=0; preno=0;
	head=NULL;
}

void Rel(){
	DATA *d,*n;
	n=head;
	while(n){
		d=n;
		n=n->next;
		free(d);
	}
}

void Create(){
	
	int i=0;
	init();
	Rel();
	fflush(stdin);
	
	kstr = (String)malloc(STLEN);
	
	puts("登録する科目名を入力してください");
	printf("→");
	scanf("%s",kstr);
	fflush(stdin);
	
	while(strcmp(kstr,"0")){
		kam[i] =(String)malloc(STLEN);
		strcpy(kam[i],kstr);
		printf("→");
		scanf("%s",kstr);
		fflush(stdin);
		i++;
	}
	kamo=i;
	Add();
	
}

void Display(){
	DATA *d;
	int i;
	d=head;
	
	if(d==NULL){
		puts("データを作成するか、ファイルを読み込んでください");
		return;
	}
	
	printf("--------------------------------------------------------------------\n");
	printf("  %8s  %10s","出席番号","  名前  ");
	for(i=0;i<kamo;i++) printf("%10s",kam[i]);
	printf("% 8s% 4s\n","  平均値","  順位");
	printf("--------------------------------------------------------------------\n");
	for(d=head;d!=NULL;d=d->next){
		printf("%8d %10s",d->no,d->name);
		for(i=0;i<kamo;i++) printf("%8d",d->point[i]);
		printf("%8.2f %4d",d->ave,d->rank);
		printf("\n");
	}
	
	printf("--------------------------------------------------------------------\n");
}

void Input()
{
	FILE *f;
	DATA *d;
	String fn,namae;
	int i,j,k,po[KAMO_MAX];
	
	init();
	Rel();
	
	puts("ファイル名を入力してください");
	fn=(String)malloc(STLEN);
	printf("→");
	scanf("%s",fn);
	fflush(stdin);
	strcat(fn,".txt");
	f=fopen(fn,"r");
	
	while(f==NULL){
		printf("入力した名前のファイルが存在しません\n");
		printf("正しいファイル名を入力してください\n");
		printf("→");
		scanf("%s",fn);
		fflush(stdin);
		if(strcmp(fn,"0")==0){
			printf("キャンセルします");
			return;
		}
		strcat(fn,".txt");
		f=fopen(fn,"r");
	}
	
	fscanf(f,"%d\n",&preno);
	fscanf(f,"%d\n",&kamo);
	for(i=0;i<kamo;i++){
		kam[i]=(String)malloc(STLEN);
		fscanf(f,"%s\n",kam[i]);
	}
	for(k=0;k<preno;k++){
		fscanf(f,"%d\n",&j);
		namae=(String)malloc(STLEN);
		fscanf(f,"%s\n",namae);
		for(i=0;i<kamo;i++) fscanf(f,"%d¥n",&po[i]);
		addData(j,namae,po);
	}
	Rank();
	printf("ロード成功\n");
	
}

void Output()
{
	FILE *f;
	DATA *d;
	String fn;
	fn=(String)malloc(STLEN);
	int i;
	
	if(head==NULL){
		printf("データがありません");
		return;
	}
	
	puts("ファイル名を入力してください");
	printf("→");
	scanf("%s",fn);
	fflush(stdin);
	strcat(fn,".txt");
	f=fopen(fn,"w");
	
	fprintf(f,"%d\n%d\n",preno,kamo);
	for(i=0;i<kamo;i++) fprintf(f,"%s\n",kam[i]);
	
	for(d=head;d!=NULL;d=d->next){
		fprintf(f,"%d\n",d->no);
		fprintf(f,"%s\n",d->name);
		for(i=0;i<kamo;i++) fprintf(f,"%d\n",d->point[i]);
	}
	puts("セーブしました");
	fclose(f);
}

void Add()
{
	if(kamo==0){
		puts("データを作成するか、ファイルを読み込んでください");
		return;
	}
	String name[NIN];
	int i,s[KAMO_MAX];
	printf("No%dの名前を入力してください\n",(preno++)+1);
	printf("→");
	
	name[preno]=(String)malloc(STLEN);
	scanf("%s",name[preno]);
	fflush(stdin);
	while(strcmp(name[preno],"0")!=0){
		puts("点数を入力してください");
		for(i=0;i<kamo;i++){
			printf("%s : ",kam[i]);
			scanf("%d",&s[i]);
			fflush(stdin);
		}
		addData(preno,name[preno],s);
		printf("No%dの名前を入力してください\n",(preno++)+1);
		printf("→");
		name[preno]=(String)malloc(STLEN);
		scanf("%s",name[preno]);
		fflush(stdin);
	}
	preno--;
	Rank();
}

void Del()
{
	String del;
	del=(String)malloc(STLEN);
	puts("削除する出席番号を入力してください");
	printf("→");
	scanf("%s",del);
	fflush(stdin);
	delData(atoi(del));
	printf("No%sのデータを削除しました\n",del);
	Closer();
	puts("出席番号を詰めました");
	Rank();
	preno--;
}

void Edit()
{
	DATA *d;
	String hname;
	int no,cho,i,j;
	puts("編集したいデータの出席番号を入力してください");
	printf("→");
	scanf("%d",&no);
	fflush(stdin);
	
	if(no<=0){
		puts("キャンセルします");
		return;
	}
	
	if(preno>=no){
		d=head;
		while(d->no<no) d=d->next;
		puts("編集する要素を選んでください");
		printf("1.名前 ");
		for(i=0;i<kamo;i++) printf("%d.%s ",i+2,kam[i]);
		printf("\n→");
		scanf("%d",&cho);
		fflush(stdin);
		if(cho==1){
			puts("新しい名前を入力してください");
			hname = (String)malloc(STLEN);
			scanf("%s",hname);
			fflush(stdin);
			strcpy(d->name,hname);
		}else{
			printf("新しい%sの点数を入力してください\n",kam[cho-2]);
			printf("→");
			scanf("%d",&(d->point[cho-2]));
		}
		puts("変更完了");
		
	}else{
		puts("正しい出席番号を入力してください");
		Edit();
	}
	Rank();
}


void addData(int i, String c, int p[]){
	DATA *d,*pre;
	int k;
	
	if((d = (DATA *)malloc(sizeof(DATA)))==NULL){
		printf("領域を確保できません\n");
		exit(1);
	}
	d->next=NULL;
	d->no=i;
	d->name = (String)malloc(STLEN);
	strcpy(d->name,c);
	
	for(k=0;k<kamo;k++) d->point[k]=p[k];
	
	if(head==NULL) head=d;
	else{
		for(pre=head;pre->next!=NULL;pre=pre->next);
		pre->next=d;
	}
}

void delData(int i){
	DATA *d;
	
	for(d=head;d!=NULL;d=d->next){
		if(d->no==i){
			if(d->next!=NULL){
				head->next=d->next;
				free(d);
				return;
			}
			head->next=NULL;
			free(d);
			return;
		}
	}
	printf("No%dのデータが見つかりません\n",i);
}

void Rank(){
	DATA *d,*n,*j;
	int k,sum;
	n=head;
	while(n){
		d=n;
		n=n->next;
		d->rank=1;
		sum=0;
		for(k=0;k<kamo;k++){
			sum+=d->point[k];
		}
		d->ave=(float)sum/(float)kamo;
	}
	
	for(d=head;d!=NULL;d=d->next){
		for(j=head;j!=NULL;j=j->next){
			if(d->ave < j->ave){
				d->rank++;
			}
		}
	}
}

void Closer(){
	DATA *d;
	int i=0;
	d=head;
	while(d!=NULL){
		d->no=++i;
		d=d->next;
	}
}
