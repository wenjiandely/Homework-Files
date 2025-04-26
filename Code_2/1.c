//李仪2023105003
//time : 2025/4/21
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main ()
{
    int rArray[20];
    srand( (unsigned)time( NULL ) );
    int i,j,flag,k;
    for (i=0;i<20;i++)
    {
        rArray[i]=rand() % 50+1;
    }
    char cArray[51];
    memset (cArray,0,sizeof(cArray));
    printf ("20个随机数及其棒图：\n\n");
    for (i=0;i<20;i++)
    {
        memset(cArray,0,sizeof (cArray));
        for (j=0;j<rArray[i];j++)
        {

           cArray[j]= '*';
        }
        
        
        printf("[%2d]   %2d  %s\n", i,rArray[i],cArray);
    }
    printf("等待键盘输入回车键或者任意键，进行冒泡排序");
    if(getchar()=='\n')
    {
        for (i=0; i<19;i++)
        {

            flag=0;
            for (j=0;j<19-i;j++)
            {

                if (rArray[j]<rArray[j+1])
                {
                    k=rArray[j];
                    rArray[j]=rArray[j+1];
                    rArray[j+1]=k;
                    flag=1;


                }
                

            }
        if (flag==0) break;
        }
            for (i=0;i<20;i++)
        {
            memset(cArray,0,sizeof (cArray));
            for (j=0;j<rArray[i];j++)
            {

                cArray[j]= '*';
            }
            
            
            printf("[%2d]   %2d  %s\n", i,rArray[i],cArray);
        }
    }

    return  0;
}
