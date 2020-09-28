//
//  main.c
//  problem 13
//
//  Created by Joey on 2019/10/31.
//  Copyright © 2019 杨旭鹏. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define a 16807
#define b 0
#define m 2147483647
#define r (m%a)
#define q (m/a)
#define Pi 3.1415926
#define ROUND(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))
#define GETMATELEM(base,i,j,imax) ((*(base + (i) * (imax) + (j)))) //取二维数组元素
#define LEN 1500  //DLA位置数组的 X or Y 轴长度的一半


//利用/dev/random 产生"真"随机数
int my_realrandom(int ran[],int n){
    FILE *fp1 = fopen("/dev/random","r");
    for(int i=0;i<n;i++){
        fread(&ran[i], 1, 4, fp1);
    }
    fclose(fp1);
    return 0;
}



int my_filewriter_int(char str[],int num[],int n){
    FILE * fp;
    fp = fopen(str,"w+");
    
    for(int i=0;i<n;i++)
    {
        if (i == (n-1)){
            fprintf(fp,"%d",num[i]);
            break;
        }
        fprintf(fp,"%d,",num[i]);
        
    }
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



// Schrage 方法产生随机数
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






// Schrage 方法迭代器
int my_schrage_iter(int seed){
    if(seed == m-1){
        if(a >=  b){    //由于Schrage方法只对z in (0,m-1)成立，故这里要讨论z == m-1的情况
            seed = m + (b-a) % m;
        }
        else   seed =  (b-a) % m;

    }
    else seed = ((a * (seed % q) - r * (seed /  q)) + b % m ) % m;  //递推式
    
    return seed;
}


int randomparticle(double ran,int min,int *i,int *j){   //产生随机粒子的初始位置
    double theta = 2*Pi*ran;  //为了使初始位置更加均匀，我们取圆形边界，产生均匀分布的随机角度值
    double x = min*cos(theta);  //以min为半径，计算此初始位置相对于原点的x,y值
    double xf = x-floor(x);  //x的小数部分
    double y = min*sin(theta);
    double yf = y-floor(y);  //y的小数部分
    *i = (int)( LEN + floor(x) + floor(2*xf) ); //结束后，i,j变为初始位置的矩阵坐标
    *j = (int)( LEN + floor(y) + floor(2*yf) );
    
    
    /*   //一下为正方形边界
    int n = (int)floor(8*min*ran); //粒子位于边缘处的哪个位置
    //printf("n= %d\n",n);
    
    if (n < 2*min+1){  //一下过程均为找到此位置的行号和列好
        *i = LEN-min;
        *j = LEN-min+n;
        return 0;
    }
    else n -= 2*min;
    if (n < 2*min+1){
        *i = LEN-min+n;
        *j = LEN+min;
        return 0;
    }
    else n -= 2*min;
    if (n < 2*min+1){
        *i = LEN+min;
        *j = LEN+min-n;
        return 0;
    }
    else n -= 2*min;
    *i = LEN+min-n;
    *j = LEN-min;
    */
    return 0;
}


int particleRW(int *o,int *p,int max,int *position,int seed){ //产生的随机粒子随机行走器 //o,p为初始粒子的位置，max为判定粒子逃逸的范围，position为总位置坐标数组
    int i = *o;
    int j = *p;
    double ran;
    int flag = 0;
    for(int k = -1;k<2;k++){  //查看粒子周围是否有团簇粒子，有的话flag != 0
        for(int l = -1;l<2;l++){
            flag += GETMATELEM(position, (i-k), (j-l), (2*LEN+1));
        }
    }
    while (flag == 0 && sqrt( pow(i-LEN,2)+pow(j-LEN,2) ) < max ){  //粒子周围没有团簇粒子且在逃逸区域以内，则继续随机行走
        if (seed >= 0) {
            ran = seed / (double) m;
        }
        else {
            ran = (seed + m) / (double) m;
        }
        if(ran<0.25) j +=1 ;   //4个方向随机行走
        else if(ran<0.5 && ran >= 0.25) j -= 1;
        else if(ran<0.75 && ran>=0.5 ) i += 1;
        else i -= 1;
        seed = my_schrage_iter(seed);
        for(int k = -1;k<2;k++){  //查看粒子周围是否有团簇粒子，有的话flag != 0
            for(int l = -1;l<2;l++){
                flag += GETMATELEM(position, (i-k), (j-l), (2*LEN+1));
            }
        }
    }
    if(flag == 0) return 1;  //此时粒子逃逸，需要重新模拟
    *o = i;
    *p = j;
    return 0;   //结束后i,j变为此粒子最终的位置
}

int boxcount(int* position,int *count,int Len,int maxr){  //盒计数法统计N，Len为位置二维数组的半径，maxr，为统计范围的半径
    int flag = 0;
    int n = 0;  //区域内是否有粒子的累加器
    int len;
    if( (2*Len) < 2*maxr ){
        printf("LEN is too short to count");
        return 1;
    }
    for(int i = 1; i < 2*maxr + 1; i = i*2){
        len = 2*maxr/i;
        for(int k = 0 ;k < i ; k++){  //方格计数
            for(int l = 0 ;l < i ; l++){
                n = 0;
                for(int o = Len - maxr + len*k; o < Len - maxr +len*(k+1); o++){
                    for(int p = Len - maxr + len*l; p < Len - maxr +len*(l+1); p++ ){
                        n += GETMATELEM(position, o, p, (2*Len+1));
                    }
                }

                if (n != 0) count[flag] += 1;
            }
        }
        flag++;
    }
    return 0;
}


int sandboxcount(int*position, int*count,int rmax,int Len){ //sandbox法统计N，rmax为统计区域的半径最大值，Len为位置二维矩阵的半径
    int radius = 5;  //起始统计范围半径为5
    int flag = 0;
    int n = 0;
    for(;radius < rmax + 1;radius += 5){  //统计范围半径依次增加5
        n = 0;
        for(int i = Len - radius; i < Len + radius; i++){
            for(int j = Len - radius; j < Len + radius; j++){
                n += GETMATELEM(position, i, j, (2*Len+1));
            }
        }
        count[flag] = n;
        flag++;
    }
    return 0;
}


    
int main(int argc, const char * argv[]) {
   
    /*
    int N = 50000;  //粒子总数
    int min,max;  //分别对应产生粒子的区域和判断粒子逃逸的范围
    min = 5;
    max = 205 ;
    int i,j;
    int *position = malloc(sizeof(int)*(2*LEN+1)*(2*LEN+1));  //存放位置坐标的数组
    
    for(int i =0;i<(2*LEN+1)*(2*LEN+1);i++){   //位置坐标初始化
        position[i] = 0;
    }
 
    GETMATELEM(position, (LEN), (LEN), (2*LEN+1)) = 1; //设定原点(0,0)处初始有一粒子
    
    int *seed = malloc(sizeof(int)*N);  //随机数种子
    my_realrandom(seed, N);
    double *ran = malloc(sizeof(double)*N);  //每次粒子的初始位置
    my_schrage(ran, seed[0], N);
    int flag = 0;
    for(int k =0;k<N;k++){
        flag = 0;
        randomparticle(ran[k], min,&i, &j);
        flag = particleRW(&i, &j, max, position, seed[k]);
        if(flag == 1){
            while (flag == 1) {
                flag = 0;
                my_realrandom(&seed[k], 1);
                flag = particleRW(&i, &j, max, position, seed[k]);
            }
        }
        GETMATELEM(position, (i), (j), (2*LEN+1)) = 1;
        if(abs(i-LEN) > min-5) min = 5 + abs(i-LEN);
        if(abs(j-LEN) > min-5) min = 5 + abs(j-LEN);
        max = min + 200 ;
    }
    my_filewriter_int("p.dat", position, (2*LEN+1)*(2*LEN+1));
   */
    
    
    int len = 512;
    int Len = 1500;
    int *position = malloc(sizeof(int)*(2*Len+1)*(2*Len+1));
    int *count1 = malloc(sizeof(int)*11);  //盒计数法统计N存放数组
    int *count2 = malloc(sizeof(int)*60);  //Sandbox法统计N存放数组
    
    for (int i = 0;i<11;i++){  //数组初始化
        count1[i] = 0;
    }
    
    for (int i = 0;i<60;i++){    //数组初始化
           count2[i] = 0;
       }
    
    my_filereader_int("p-1500-5*104改变max/5-205.dat", position, (2*Len+1)*(2*Len+1)); //读取之前生成的位置矩阵

    boxcount(position, count1, Len, len);
    sandboxcount(position, count2, 300,Len);
    
    my_filewriter_int("box.txt", count1, 11);
    my_filewriter_int("sandbox.txt", count2, 60);
     
     
    return 0;
}
