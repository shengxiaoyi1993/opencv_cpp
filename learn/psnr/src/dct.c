#include "dct.h"
#include <math.h>

// #define SQRT_2  1.414<<8
#define Pi 3.1415926
int g_movebit;
double g_sqrt2;
int g_a_1_1;
int g_b_1_1;
int g_a_1_3;
int g_b_1_3;
int g_a_s2_6;
int g_b_s2_6;
int g_subba_1_1;
int g_subba_1_3;
int g_subba_s2_6;
int g_addab_1_1;
int g_addab_1_3;
int g_addab_s2_6;

int g_sqrt2_m;
int g_m_total;
int g_m_step;
int g_m_remain;
int g_m_magsrc;




int init(unsigned int v_movebit){
  g_movebit = v_movebit;
  g_sqrt2=sqrt(2);
  g_sqrt2_m=g_sqrt2*(1<<g_movebit);
  g_m_magsrc=10;

  g_a_1_1=(1*cos(1*Pi/16))*(1<<g_movebit);
  g_b_1_1=(1*sin(1*Pi/16))*(1<<g_movebit);
  g_a_1_3=(1*cos(3*Pi/16))*(1<<g_movebit);
  g_b_1_3=(1*sin(3*Pi/16))*(1<<g_movebit);
  g_a_s2_6=(g_sqrt2*cos(6*Pi/16))*(1<<g_movebit);
  g_b_s2_6=(g_sqrt2*sin(6*Pi/16))*(1<<g_movebit);
  g_subba_1_1=g_b_1_1-g_a_1_1;
  g_subba_1_3=g_b_1_3-g_a_1_3;
  g_subba_s2_6=g_b_s2_6-g_a_s2_6;
  g_addab_1_1=g_b_1_1+g_a_1_1;
  g_addab_1_3=g_b_1_3+g_a_1_3;
  g_addab_s2_6=g_b_s2_6+g_a_s2_6;

  printf("g_subba_1_1:%d\n", g_subba_1_1);
  printf("g_subba_1_3:%d\n", g_subba_1_3);
  printf("g_subba_s2_6:%d\n", g_subba_s2_6);
  printf("g_addab_1_1:%d\n", g_addab_1_1);
  printf("g_addab_1_3:%d\n", g_addab_1_3);
  printf("g_addab_s2_6:%d\n", g_addab_s2_6);

  g_m_step=0;
  g_m_total=g_m_step<<1;
  g_m_remain=g_movebit-g_m_step;

  printf("g_m_step:%d\n", g_m_step);
  printf("g_m_total:%d\n", g_m_total);
  printf("g_m_remain:%d\n", g_m_remain);


}

void dst_BasicTransform_0(int vsrc_0,int vsrc_1,int* pdst_0,int* pdst_1){
  *pdst_0=(vsrc_0+vsrc_1)<<g_m_step;
  *pdst_1=(vsrc_0-vsrc_1)<<g_m_step;
}

void dst_BasicTransform_1_k1n1(int vsrc_0,int vsrc_1,int* pdst_0,int* pdst_1){
  int sum_tmp=vsrc_0+vsrc_1;
  *pdst_0=(g_subba_1_1*vsrc_1+g_a_1_1*sum_tmp)>>g_m_remain;
  *pdst_1=(-g_addab_1_1*vsrc_0+g_a_1_1*sum_tmp)>>g_m_remain;
}
void dst_BasicTransform_1_k1b3(int vsrc_0,int vsrc_1,int* pdst_0,int* pdst_1){
  int sum_tmp=vsrc_0+vsrc_1;

  *pdst_0=(g_subba_1_3*vsrc_1+g_a_1_3*sum_tmp)>>g_m_remain;
  *pdst_1=(-g_addab_1_3*vsrc_0+g_a_1_3*sum_tmp)>>g_m_remain;
}
void dst_BasicTransform_1_ks2b6(int vsrc_0,int vsrc_1,int* pdst_0,int* pdst_1){
  int sum_tmp=vsrc_0+vsrc_1;

  *pdst_0=(g_subba_s2_6*vsrc_1+g_a_s2_6*sum_tmp)>>g_m_remain;
  *pdst_1=(-g_addab_s2_6*vsrc_0+g_a_s2_6*sum_tmp)>>g_m_remain;
}

void dst_BasicTransform_2(int vsrc_0,int* pdst_0){
  *pdst_0=(vsrc_0*g_sqrt2_m)>>g_m_remain;
}

void dctTransform_8_1_stage0(int *max_src,int *max_dst){
  dst_BasicTransform_0(max_src[0],max_src[7],&max_dst[0],&max_dst[7]);
  dst_BasicTransform_0(max_src[1],max_src[6],&max_dst[1],&max_dst[6]);
  dst_BasicTransform_0(max_src[2],max_src[5],&max_dst[2],&max_dst[5]);
  dst_BasicTransform_0(max_src[3],max_src[4],&max_dst[3],&max_dst[4]);

}
void dctTransform_8_1_stage1(int *max_src,int *max_dst){
  dst_BasicTransform_0(max_src[0],max_src[3],&max_dst[0],&max_dst[3]);
  dst_BasicTransform_0(max_src[1],max_src[2],&max_dst[1],&max_dst[2]);
  dst_BasicTransform_1_k1b3(max_src[4],max_src[7],&max_dst[4],&max_dst[7]);
  dst_BasicTransform_1_k1n1(max_src[5],max_src[6],&max_dst[5],&max_dst[6]);
}

void dctTransform_8_1_stage2(int *max_src,int *max_dst){
  dst_BasicTransform_0(max_src[0],max_src[1],&max_dst[0],&max_dst[1]);
  dst_BasicTransform_1_ks2b6(max_src[2],max_src[3],&max_dst[2],&max_dst[3]);
  dst_BasicTransform_0(max_src[4],max_src[6],&max_dst[4],&max_dst[6]);
  dst_BasicTransform_0(max_src[7],max_src[5],&max_dst[7],&max_dst[5]);
}

void dctTransform_8_1_stage3(int *max_src,int *max_dst){
  max_dst[0]=max_src[0]<<g_m_step;
  max_dst[1]=max_src[1]<<g_m_step;
  max_dst[2]=max_src[2]<<g_m_step;
  max_dst[3]=max_src[3]<<g_m_step;
  dst_BasicTransform_0(max_src[7],max_src[4],&max_dst[7],&max_dst[4]);
  dst_BasicTransform_2(max_src[5],&max_dst[5]);
  dst_BasicTransform_2(max_src[6],&max_dst[6]);
}

void dctTransform_8_1_stage4(int *max_src,int *max_dst){
  // max_dst[0]=max_src[0];
  // max_dst[4]=max_src[1];
  // max_dst[2]=max_src[2];
  // max_dst[6]=max_src[3];
  // max_dst[7]=max_src[4];
  // max_dst[3]=max_src[5];
  // max_dst[5]=max_src[6];
  // max_dst[1]=max_src[7];

  max_dst[0]=max_src[0];
  max_dst[1]=max_src[7];
  max_dst[2]=max_src[2];
  max_dst[3]=max_src[5];
  max_dst[4]=max_src[1];
  max_dst[5]=max_src[6];
  max_dst[6]=max_src[3];
  max_dst[7]=max_src[4];
}


void dctTransform_8_1(int *max_src,int *max_dst){


  int tmp[8];
  tmp[0]=max_src[0]<<g_m_magsrc;
  tmp[1]=max_src[1]<<g_m_magsrc;
  tmp[2]=max_src[2]<<g_m_magsrc;
  tmp[3]=max_src[3]<<g_m_magsrc;
  tmp[4]=max_src[4]<<g_m_magsrc;
  tmp[5]=max_src[5]<<g_m_magsrc;
  tmp[6]=max_src[6]<<g_m_magsrc;
  tmp[7]=max_src[7]<<g_m_magsrc;


  dctTransform_8_1_stage0(tmp,max_dst);
  dctTransform_8_1_stage1(max_dst,tmp);
  dctTransform_8_1_stage2(tmp,max_dst);
  dctTransform_8_1_stage3(max_dst,tmp);
  dctTransform_8_1_stage4(tmp,max_dst);

  max_dst[0]>>=g_m_magsrc;
  max_dst[1]>>=g_m_magsrc;
  max_dst[2]>>=g_m_magsrc;
  max_dst[3]>>=g_m_magsrc;
  max_dst[4]>>=g_m_magsrc;
  max_dst[5]>>=g_m_magsrc;
  max_dst[6]>>=g_m_magsrc;
  max_dst[7]>>=g_m_magsrc;

}


void dctTransform_64_2(int *max_src,int *max_dst){

  int max_tmp_0[64]={0};
  int max_tmp_1[64]={0};

  // printf("%s\n", "total: ");
  // printList(max_src,64);

int m=0;
  // for(m=0;m<64;m++){
  //   max_tmp_0[m]=max_src[m]<<g_m_magsrc;
  // }

  int i;
  for( i=0;i<8;i++){
    dctTransform_8_1(max_src+i*8,max_tmp_1+i*8);
  }
  transposeMatrix_8_8(max_tmp_1,max_tmp_0);
  int j;
  for( j=0;j<8;j++){
    dctTransform_8_1(max_tmp_0+j*8,max_tmp_1+j*8);
  }

  transposeMatrix_8_8(max_tmp_1,max_dst);

  for(m=0;m<64;m++){
    max_dst[m]>>=3;
  }


  // transposeMatrix_8_8(max_src,max_tmp_0);
  //
  // int i;
  // for( i=0;i<8;i++){
  //   dctTransform_8_1(max_tmp_0+i*8,max_tmp_1+i*8);
  // }
  // transposeMatrix_8_8(max_tmp_1,max_tmp_0);
  //
  // int j;
  // for( j=0;j<8;j++){
  //   dctTransform_8_1(max_tmp_0+j*8,max_dst+j*8);
  // }


  // int seq=0;
  // for(seq=0;seq<64;seq++){
  //   max_dst[seq]>>=(g_m_total<<1);
  // }

}

void transposeMatrix_8_8(int *max_src,int * max_dst){
  int i;
  for( i=0;i<8;i++){
    int j;
    for( j=0;j<8;j++){
      max_dst[i*8+j]=max_src[j*8+i];
    }
  }
}


void dctTransform_64_2_v_withfloat(const char *max_src,int * max_dst){
  int max_src_tmp[64];

int i;
  for ( i = 0; i < 64; i++) {
    max_src_tmp[i]=(int)max_src[i];
  }
  dctTransform_64_2_with_flost(max_src_tmp,max_dst);
}



void dctTransform_64_2_v(const char *max_src,int * max_dst){
  int max_src_tmp[64];
  // int  max_dst_tmp[64];

int i;
  for ( i = 0; i < 64; i++) {
    max_src_tmp[i]=(int)max_src[i];
  }
  dctTransform_64_2(max_src_tmp,max_dst);
// int j;
// for (j = 0; j < 64; j++) {
//   max_dst[j]=(int)max_dst_tmp[j];
// }
//
// int j;
// for (j = 0; j < 64; j++) {
//   max_dst[j]=(short)max_src[j];
// }

}

void printList(int * v_list, int size){
  int i=0;
  for(;i<size;i++){
    printf("%d ", v_list[i]);
  }
  printf("\n");
}


double U(int value){
  if(value==0){
    return sqrt(0.5);
  }
  else{
    return 1;
  }
}

void dctTransform_8_1_withfloat(int *max_src,int *max_dst){

  double array_out[8]={0};
  int i=0;
  for( i=0;i<8;i++){
    int n;
      for( n=0;n<8;n++){
        array_out[i]+=sqrt(2)*U(i)*max_src[n]*cos((2*n+1)*i*Pi/16);
      }
  }
  for ( i = 0; i < 8; i++) {
    max_dst[i]=array_out[i];
  }

}


void dctTransform_64_2_with_flost(int *max_src,int *max_dst){
  int max_tmp_0[64]={0};
  int max_tmp_1[64]={0};

  // printf("%s\n", "total: ");
  // printList(max_src,64);

int m=0;

  int i;
  for( i=0;i<8;i++){
    dctTransform_8_1_withfloat(max_src+i*8,max_tmp_1+i*8);
  }
  transposeMatrix_8_8(max_tmp_1,max_tmp_0);
  int j;
  for( j=0;j<8;j++){
    dctTransform_8_1_withfloat(max_tmp_0+j*8,max_tmp_1+j*8);
  }

  transposeMatrix_8_8(max_tmp_1,max_dst);

  for(m=0;m<64;m++){
    max_dst[m]>>=3;
  }

}
