#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<time.h>
#define N 10000
using namespace std;
__int64 gcd(__int64 m,__int64 n);//计算数组中的数和用户输入的一个数的最大公约数
__int64 Judge_Prime(__int64 n,int t);//判断用户输入的数是否为
__int64 Jacobi(__int64 a,__int64 n);//计算雅克比符号
__int64 quick_mod(__int64 a,__int64 n);//用快速幂指数求模
void ISSu(__int64 n);
void NTSu(__int64 n);
int main()
{
	__int64 t;//
	__int64 n;//定义需要判断的数
	int b;//用来判断用户想要进行的操作
	while(1)//为了实现可以测试多个数据，进行while循环
	{
		do
		{
			cout<<"                \t\t\t◇欢迎使用程序设Solovay-Strassen素判定方法◇"<<endl;
			cout<<"\t\t\t*===================================================================*"<<endl;
		    cout<<"\t\t\t|  ○输入数据进行素数判断请输1       ○打开文件进行素数判断请输2    |"<<endl;
			cout<<"\t\t\t|                                                                   |"<<endl;	
			cout<<"\t\t\t|                        ○退出程序请输0                            |"<<endl;	
			cout<<"\t\t\t|                                                                   |"<<endl;	
			cout<<"\t\t\t*===================================================================*"<<endl;	
			while(scanf("%d",&b)==NULL)//用户输入b选择所需进行的操作
			{
				fflush(stdin);
				cout<<"◇输入错误(不要包含字母及其他字符)，请重新输入：";
			}
		}while(b!=1&&b!=0&&b!=2);
		if(b==0) return 0;//用户选择-1是，程序退出
		if(b==2)
		{
			__int64 a[N];
			int c=0,i=0;
			FILE * fp;
			fp = fopen("sj.txt","r");
			if(fp==NULL)
			{
				cout<<"◇文件打开失败，退出程序！"<<endl;
				exit(1);
			}
			while(fscanf(fp,"%I64d",&a[i])!=EOF)
				i++;
			fclose(fp);
			for(int j=0;j<i;j++)
			{
				if(Judge_Prime(a[j],100)) ISSu(a[j]);
				else NTSu(a[j]);
			}
		}
		if(b==1)//如果用户选择进行判断素数，则进行一下判断
		{
			cout<<"◇请输入您要判断的数：";
			while(scanf("%I64d",&n)==NULL)
			{
				fflush(stdin);
				cout<<"◇输入错误(不要包含字母及其他字符)，请重新输入：";
			}
			while(n<=1||(__int64(n)!=n)||(n%2==0))//对用户输入的数进行过滤
			{
				cout<<endl<<"◇请输入大于1的奇数：";
				scanf("%I64d",&n);
				continue;
			}
			cout<<endl<<"◇请输入您要测试的次数，如果要判断的数很大，建议值为(100-1000)：";
			while(scanf("%I64d",&t)==NULL)
			{
				fflush(stdin);
				cout<<"◇输入错误(不要包含字母及其他字符)，请重新输入：";
			}
			while(t<1||(__int64(t)!=t)||(t>=n-1))//对用户输入的随机数进行过滤
			{
				cout<<endl<<"◇请输入大于等于1小于n-1的数：";
				scanf("%I64d",&t);
				continue;
			}
			cout<<endl;
			if(Judge_Prime(n,t))//如果该数为素数则，进入if语句
			{
				ISSu(n);
			}
			else
			{
				NTSu(n);
			}
			printf("\n");
		}
	}
	return 0;
}

__int64 Judge_Prime(__int64 n,int t)
{
	__int64 s;
	__int64 a[N],r,j;//a数组用来储存随机数，r用来赋值为快速取模的结果，j赋值为雅克比符号的结果
	__int64 Marked[N];//定义一个用来记录随机数的数组，以防随机数重复
	srand((unsigned int)time(NULL));//定义一个系统时间为基础的随机数
	for(int i=0;i<t;i++)//进行t次判断
	{
		bool f;
		do
		{
			f=0;
			do
			{
				a[i]=rand()%n;//赋值随机数
			}while(a[i]<=2||a[i]>=n-1);//限定随机数值得范围
			for(int j=0;j<i;j++)
			{
				if(a[i]==Marked[j])
				{
					f=1;
					break;
				}
			}//如果随机数重复则重新赋值
		}while(f);
		Marked[i]=a[i];
		__int64 g=gcd(a[i],n);//判断随机数与要判断的数有无最大公约数
		if(g==1)//如果两数互素的话就进行雅克比符号与快速幂指数的运算判断
		{
			r=quick_mod(a[i],n);//r赋值为随机数与n的幂指数取余运算的结果
			if(!(r==1||r==n-1))//如果r!=1而且r!=-1的话，n不是素数，退出循环
			{
				s=0;
				break;
			}
			j=Jacobi(a[i],n);//j赋值为雅克比符号的计算结果
			if(j<0)
				j=j+n;
			if(r!=j)//如果r不等于j，n不是素数，退出循环
			{
				s=0;
				break;
			}
			else
				s=1;
		}
		else//如果有一个随机数与要判断的数的最大公约数不是1，则该数不是素数
		{
			s=0;
			break;
		}
	}
	return s;//返回s的值
}

__int64 Jacobi(__int64 a,__int64 n)
{
	__int64 e=0,a1,n1;
	__int64 s=0;
	if(a==0||a==1)
		return 1;
	//temp=a;
	while(a%2==0)
	{
		a/=2;
		e++;
	}
	a1=a;
	if(e%2==0)
		s=1;
	else
	{
		if(n%8==1||n%8==7)
			s=1;
		else if(n%8==3||n%8==5)
			s=-1;
	}
	if(n%4==3&&a1%4==3)
		s=-s;
	n1=n%a1;
	if(a1==1)
		return s;
	else
		return s*Jacobi(n1,a1);
}	
                                                       
__int64 quick_mod(__int64 a,__int64 n)
{
	__int64 ans=1;                                          //定义一个变量，用来存储模的积的运算的结果
	__int64 k=(n-1)/2;                                      //将幂次赋值为(n-1)/2
	a%=n;													//对刚进来的a进行取模运算，避免后面第一次求平方运算溢出
	while(k)												//当>=1的时候执行while循环语句
	{
		if(k&1)												//对二进制下的 k 进行按位与1运算，求二进制下 k 的最低位是否为1
			ans=ans*a%n;									//将模的积运算后的值赋值给变量ans
		k>>=1;												//二进制下的 k 右移一位，相当于十进制下的 k 除以2
		a=a*a%n;											//对a进行一次平方模n的运算，为了下一位的模的积的运算做准备
	}
	return ans%n;											//返回模的积取模的值即a^k mod n的值
}

__int64 gcd(__int64 a,__int64 n)//计算数组中的数和用户输入的一个数的最大公约数
{
	__int64 r;
	do
	{
		r=a%n;
		a=n;
		n=r;
	}while(r);
	return a;
}

void ISSu(__int64 n)
{
	int i,m;
	printf("○%I64d是素数\n",n);
	do
	{
		cout<<endl<<"◇如果您需要将结果保存至Su.txt文件中，请输入1，否则请输入2：";//用户进行选择是否保存至文件
		while(scanf("%d",&i)==NULL)
		{
			fflush(stdin);
			cout<<"◇输入错误(不要包含字母及其他字符)，请重新输入：";
		}
	}while(i!=1&&i!=2);
	if(i==1)//如果用户进行保存，则进入保存文件的操作
	{
		FILE *fp=fopen("Su.txt","at+");//读写打开一个文本文件，允许读或在文本末追加数据
		if(fp==NULL)
		{
			cout<<endl<<"◇文件打开失败，退出程序！"<<endl;
			exit(1);
		}
		fprintf(fp,"%I64d是素数\n",n);
		if(fp!=NULL)
			cout<<endl<<"◇文件保存成功！"<<endl;
		else
			cout<<endl<<"◇文件保存失败！"<<endl;
		fclose(fp);
		do
		{
			cout<<endl<<"◇如果您需要打开Su.txt文件，请输入1，否则请输入2：";
			while(scanf("%d",&m)==NULL)
			{
				fflush(stdin);
				cout<<"◇输入错误(不要包含字母及其他字符)，请重新输入：";
			}
		}while(m!=1&&m!=2);
		if(m==1)
		{
			ifstream in("Su.txt");
			string line;
			if(in)
			{
				cout<<endl;
				while(getline(in,line))
				{
					cout<<line<<endl;
				}
			}
			else
			{
				cout<<"◇没有该文件"<<endl;
			}
			in.close();
		}
	}
}

void NTSu(__int64 n)
{
	int j,k;
	printf("○%I64d不是素数\n",n);
	do
	{
		cout<<endl<<"◇如果您需要将结果保存至NSu.txt文件中，请输入1，否则请输入2：";
		while(scanf("%d",&j)==NULL)
		{
			fflush(stdin);
			cout<<"◇输入错误(不要包含字母及其他字符)，请重新输入：";
		}
	}while(j!=1&&j!=2);
	if(j==1)
	{
		FILE *fp=fopen("◇NSu.txt","at+");
		if(fp==NULL)
		{
			cout<<endl<<"◇文件打开失败，退出程序！"<<endl;
			exit(1);
		}
		fprintf(fp,"%I64d不是素数\n",n);
		if(fp!=NULL)
			cout<<endl<<"◇文件保存成功！"<<endl;
		else
			cout<<endl<<"◇文件保存失败！"<<endl;
		fclose(fp);
		do
		{
			cout<<endl<<"◇如果您需要打开NSu.txt文件，请输入1，否则请输入2：";
			while(scanf("%d",&k)==NULL)
			{
				fflush(stdin);
				cout<<"◇输入错误(不要包含字母及其他字符)，请重新输入：";
			}
		}while(k!=1&&k!=2);
		if(k==1)
		{
			ifstream in("NSu.txt");
			string line;
			if(in)
			{
				cout<<endl;
				while(getline(in,line))
				{
					cout<<line<<endl;
				}
			}
			else
			{
				cout<<"◇没有该文件"<<endl;
			}
			in.close();
		}
	}
}

