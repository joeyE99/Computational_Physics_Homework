#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define a 16807
#define m 2147483647
#define b 0
#define r (m%a)
#define q (m/a)


//利用/dev/random 产生随机种子
int my_randomseed(int seed[],int n){     //seed为存储随机种子的数据，n为所需要种子的个数
    FILE * fp1 = fopen("/dev/random","r");
    for(int i=0;i<n;i++){
        fread(&seed[i], 1, sizeof(int), fp1);
    }
    fclose(fp1);
    return 0;
}




//写文件子程序，输入写成文件名称字符串str，数据来源于数组num，数据总数n
int my_filewriter_double(char str[],double num[],int n){
    FILE * fp;
    fp = fopen(str,"w+");

    for(int i=0;i<(n-1);i++)
    {
        fprintf(fp,"%lf ",num[i]);

    }
    fprintf(fp,"%lf",num[n-1]);    //最后一个数据后不加 ","
    fclose(fp);
    return 0;
}

int my_filereader_int(char str[],int num[],int n){
    FILE * fp;
    fp = fopen(str,"r");

    for(int i=0;i<n-1;i++)
    {
        fscanf(fp,"%d,",&num[i]);

    }
    fscanf(fp,"%d",&num[n-1]);    //最后一个数据后不加 ","
    fclose(fp);
    return 0;
}

// 16807 之 Schrage 方法产生随机数
int my_schrage(double ran[],int seed,int n){
    for (int i = 0; i < n - 1; i++) {
        if (seed >= 0) {
            ran[i] = seed / (double) m;
        } else {
            ran[i] = (seed + m) / (double) m;
        }
        if(seed == m-1){
            if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                seed = m + (b-a) % m;
            }
            else   seed =  (b-a) % m;

        }
        else seed = ((a * (seed % q) - r * (seed /  q)) + b % m ) % m;  //递推式
    }
    if (seed >= 0) {
        ran[n-1] = seed / (double) m;
    } else {
        ran[n-1] = (seed + m) / (double) m;
    }
    return 0;
}


//Fibonacci延迟器
int my_fibonacci(double ran[],int ranI[],int n,int o,int p){
    int temp;
    for(int i=1;i < p;i++){ //先把ran的前p-1项计算出来
        if (ranI[i] >= 0) {
            ran[i-1] = ranI[i] / (double) m;
        } else {
            ran[i-1] = (ranI[i] + m) / (double) m;
        }
    }
    for (int i = p; i <= n; i++) {   //ranI[i % p]存放的为第i项

        temp = (ranI[i % p] - ranI[i % p+(p-o)]) ;  //递推式

        if(temp >= 0) ranI[i % p] = temp ;
        else ranI[i % p] = temp + 1;  //递推得到的新结果放入ranI中i%p一项

        if (ranI[i % p] >= 0) {   //计算ran
            ran[i-1] = ranI[i % p] / (double) m;
        } else {
            ran[i-1] = (ranI[i % p] + m) / (double) m;
        }

    }
    return 0;
}


int main() {
    int N; //总随机数个数
    double x,y,z;  //用来存放X_{n-1},X_{n},X_{n+1}
    int flag = 0;  //记录满足条件的个数

    char str[50];   //用来进行输入检查时用来存放的临时数组
    printf("请输入您所需要的总点数：");
    while (!scanf("%d",&N)) {   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总点数：");
    }
    if(N >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");


    double *ran = malloc(sizeof(double) * N);  //用来存放随机数
    int o,p;   //Fibonacci方法的延迟整数对


    my_schrage(ran,1,N);   //16807方法产生随机数组并选取种子值为1

    for(int i = 0;i < (N-2);i++){   //计算满足关系式的比重
        x = ran[i];
        y = ran[i+1];
        z = ran[i+2];
        if(x < z && z < y) flag ++;
    }
    //my_filewriter_double("16807_ran.dat",ran,N);  //将产生的随机数组存储为文件
    printf("16807方法中满足条件的的比重为：%lf\n",flag/(double)(N-2));

    inputpq:printf("请输入Marsaglia方法的延迟整数对[p,q](建议输入97,33)(英文逗号隔开)：");
    while (!scanf("%d,%d",&o,&p)) {   //相对简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入Marsaglia方法的延迟整数对[p,q](建议值97,33)(英文逗号隔开)：");
    }

    int temp;
    if(o > p){    //使 p > o
        temp = o;
        o = p;
        p=temp;
    }
    if( N-p < 3 ) {    //排除N相对于p,q太小的情况发生
        printf("输入的p,q值相对于总点数太大了，请重试!\n");
        goto inputpq;
    }

    printf("计算比重时是否排除初始随机数值？是输入1，不是输入0：");
    int u; //是否排除初始随机数值得flag
    while (!scanf("%d",&u)||(u != 0 && u != 1) ) {    //相对简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("计算比重时是否排除初始随机数值？是输入1，不是输入0：");
    }

    if(N >1000000) printf("您输入的参数已接受，正在计算请稍等片刻~\n");
    free(ran);    //清除上面16807方法产生的数值
    ran = malloc(sizeof(double) * N);  //用来存放随机数
    int *ranI = malloc(sizeof(int) * p);    //用来存放递推数列



    my_filereader_int("ranI.txt",ranI,p);   //读取之前利用"/dev/random"产生的初始随机数组
    my_fibonacci(ran,ranI,N,o,p);    //Fibonacci方法产生随机数组
    //my_filewriter_double("Marsaglia_ran.dat",ran,N);

    flag = 0;
    if(u == 1) {
        for (int i = p; i < (N-2); i++) {
            x = ran[i];
            y = ran[i + 1];
            z = ran[i + 2];
            if (x < z && z < y) flag++;
        }
        printf("Marsaglia方法中满足条件的的比重为：%lf\n",flag/(double)(N-p-2));
    }
    if(u == 0) {
        for (int i = 0; i < (N-2); i++) {
            x = ran[i];
            y = ran[i + 1];
            z = ran[i + 2];
            if (x < z && z < y) flag++;
        }
        printf("Marsaglia方法中满足条件的的比重为：%lf\n",flag/(double)(N-2));
    }






    return 0;

}