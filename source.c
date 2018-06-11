#include<stdio.h>
//优先关系表
//1表示大于，-1表示小于，0表示等于，2表示没有关系
int find(int a,int b)
{
    int table[6][6]={1,-1,-1,-1, 1,1,
                     1, 1,-1,-1, 1,1,
                     1, 1, 2, 2, 1,1,
                    -1,-1,-1,-1, 0,1,
                     1, 1, 2, 2, 1,1,
                    -1,-1,-1,-1,-1,0};
    return table[a-1][b-1];
}
//根据返回的数值去优先关系表里面查找优先关系
//不是非终结符返回0
int in_vt(char c)
{
   int n;
   switch(c)
   {
       case '+': n = 1; break;
       case '*': n = 2; break;
       case 'i': n = 3; break;
       case '(': n = 4; break;
       case ')': n = 5; break;
       case '#': n = 6; break;
       default : n = 0;
   }
   return n;
}
//出错判断
int judge(char *p,int k,char *psc)
{
    if(k == 1 && p[k] == '#' && (*psc == '+' || *psc == '*')){
        printf("\n运算符前面没有操作数！\n");
        return 0;
    }
    if((*psc == '+' || *psc == '*') && (*(psc + 1) == '+' || *(psc + 1) == '*')){
        printf("\n运算符号相邻！\n");
        return 0;
    }
    if(*psc == '#' && (*(psc - 1) == '+' || *(psc - 1) == '*')){
        printf("\n运算符后面没有操作数！\n");
        return 0;
    }
    return 1;
}

int main()
{
   int  k;//栈顶指针
   char s[30]={'\0'};//分析栈
   char *ss;
   char in_c[50] = {'\0'};//输入串
   char *psc;//指向当前输入符号
   int  j;
   char q;
   int  flag;
   int  n;
   while(1){
        printf("\n************************************\n");
        printf("请输入要归约的字符串(以‘#’结束)：");
        scanf("%s",in_c);
        n = 1;//记录步骤
        k = 1;
        s[k] = '#';
        s[k+1] = '\0';    //初始化
        ss = s + 1;       //指向栈底
        psc = in_c;
        printf("\n步骤\t栈内字符\t\t优先关系\t当前符号\t剩余输入串\t\t\t移进或归约\n");
        while(1){
            if(judge(s,k,psc) == 0){
                printf("\n出错！\n");
                break;
            }
            if(in_vt(s[k]))
                j = k;
            else
                j = k - 1;
            flag = find(in_vt(s[j]),in_vt(*psc));
            if(flag == 1){  //如果s[j] > 当前输入字符
                do{
                    q = s[j];
                    if(in_vt(s[j-1]))
                        j--;
                    else
                        j = j - 2;
                }while(find(in_vt(s[j]),in_vt(q)) != -1);
               printf("(%d)\t%-24s>\t\t%c\t\t%-32s归约\n",n++,ss,*psc,psc+1);
               k = j + 1;
               s[k] = 'N';
               s[k+1] = '\0';
               continue;
          }
          else if(flag == -1)
               {
                   printf("(%d)\t%-24s<\t\t%c\t\t",n++,ss,*psc);
                   k++;
                   s[k] = *psc;
                   s[k+1] = '\0';
                   psc++;
                   printf("%-32s移进\n",psc);
                   continue;
               }
               else if(flag == 0)
                    {
                          if(s[j] == '#')
                          {
                               printf("(%d)\t%-24s=\t\t#\t\t\t\t\t\t接受\n",n,ss);
                               printf("\n归约成功！\n");
                               break;
                          }
                          else
                          {
                               printf("(%d)\t%-24s=\t\t%c\t\t",n++,ss,*psc);
                               k++;
                               s[k] = *psc;
                               s[k+1] = '\0';
                               psc++;
                               printf("%-32s移进\n",psc);
                               continue;
                          }
                     }
                     else
                     {
                          printf("(%d)\t%-24s无\t\t%c\t\t%-32s\\\n",n++,ss,*psc,psc+1);
                          printf("\n错误！\n");
                          break;
                     }



   }

}


 return 0;
}
