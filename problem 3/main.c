#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define a 16807
#define b 0
#define m 2147483647
#define r (m%a)
#define q (m/a)
#define Pi 3.1415926



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

int my_filewriter(char str[],double num[],int n){
    FILE * fp;
    fp = fopen(str,"w+");

    for(int i=0;i<n;i++)
    {
        if (i == (n-1)){
            fprintf(fp,"%lf",num[i]);
            break;
        }
        fprintf(fp,"%lf,",num[i]);

    }
    fclose(fp);
    return 0;
}


int my_schrage_sphere(int seed[],double rantheta[],double ranphi[],int n){
    for (int i = 0; i < n; i++) {
        if(seed[0] == m-1){
            if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                seed[0] = m + (b-a) % m;
            }
            else   seed[0] =  (b-a) % m;

        }
        if(seed[1] == m-1){
            if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
                seed[1] = m + (b-a) % m;
            }
            else   seed[1] =  (b-a) % m;

        }
        seed[0] = ((a * (seed[0] % q) - r * (seed[0] /  q)) + b % m ) % m;
        seed[1] =((a * (seed[1] % q) - r * (seed[1] /  q)) + b % m ) % m;
        if (seed[0] >= 0) {
            rantheta[i] = acos(2 * (seed[0] / (double)m) - 1);
        }
        else{
            rantheta[i] = acos(2 * ((seed[0] + m) / (double)m) - 1);
        }

        if (seed[1] >= 0) {
            ranphi[i] = 2 * Pi * seed[1] / (double)m;
        }
        else{
            ranphi[i] = 2 * Pi * (seed[1] + m) / (double)m;
        }


    }

}



//Fibonacci延迟器
int my_fibonacci_theta(double ran[],int ranI[],int n,int o,int p){
    int temp;

    for (int i = p; i < n; i++) {   //ranI[i % p]存放的为第i项

        temp = (ranI[i % p] - ranI[(i % p+(p-o)) % p]) ;  //递推式

        if(temp >= 0) ranI[i % p] = temp ;
        else ranI[i % p] = temp + 1;  //递推得到的新结果放入ranI中i%p一项

        if (ranI[i % p] >= 0) {   //计算ran
            ran[i-p] = ranI[i % p] / (double) m;

        } else {
            ran[i-p] = (ranI[i % p] + m) / (double) m;
        }
        ran[i-p] = acos(2*ran[i-p]-1);

    }
    return 0;
}

//Fibonacci延迟器
int my_fibonacci_phi(double ran[],int ranI[],int n,int o,int p){
    int temp;

    for (int i = p; i < n; i++) {   //ranI[i % p]存放的为第i项

        temp = ranI[i % p] - ranI[(i % p+(p-o)) % p];  //递推式

        if(temp >= 0) ranI[i % p] = temp ;
        else ranI[i % p] = temp + 1;  //递推得到的新结果放入ranI中i%p一项

        if (ranI[i % p] >= 0) {   //计算ran
            ran[i-p] = ranI[i % p] / (double) m;
        } else {
            ran[i-p] = (ranI[i % p] + m) / (double) m;
        }
        ran[i-p] = 2*Pi*ran[i-p];

    }
    return 0;
}

int main() {

    int N;
    char str[50];
    printf("请输入您所需要的总点数：");
    while (!scanf("%d",&N)){   //简单的输入检查
        gets(str);
        printf("\nInput error,please try again\n");
        printf("请输入您所需要的总点数：");
    }



    int seed[2] = {34028207,1677078722};  //设定初始种子值，来源于读取"/dev/random"

    double * rantheta = malloc(sizeof(double)*N);
    double * ranphi = malloc(sizeof(double)*N);





    int o,p;
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


    if(N > 1000000) printf("您输入的参数已接受，正在计算请稍后~\n");

    my_schrage_sphere(seed,rantheta,ranphi,N); //16807方法生成theta,phi
    
    my_filewriter("theta_16807.dat",rantheta,N);
    my_filewriter("phi_16807.dat",ranphi,N);
    
    free(rantheta);
    free(ranphi);
    
    rantheta = malloc(sizeof(double)*(N+p));
    ranphi = malloc(sizeof(double)*(N+p));

    int *ranI1 = malloc(sizeof(int) * p);      //用来存放递推数列
    int *ranI2 = malloc(sizeof(int) * p);
    my_filereader_int("ranI-1.txt",ranI1,p);   //读取之前利用"/dev/random"产生的初始随机数组
    my_filereader_int("ranI-2.txt",ranI2,p);

    my_fibonacci_theta(rantheta,ranI1,N+p,o,p);
    my_fibonacci_phi(ranphi,ranI2,N+p,o,p);


    my_filewriter("theta_fibo.dat",rantheta,N);
    my_filewriter("phi_fibo.dat",ranphi,N);



    return 0;
}
