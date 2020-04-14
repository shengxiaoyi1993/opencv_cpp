#ifndef CONTROL_RUNWAY_H
#define CONTROL_RUNWAY_H

#ifdef __cplusplus             //告诉编译器，这部分代码按C语言的格式进行编译，而不是C++的
extern "C"{
#endif

  #include "stdio.h"

  int init(unsigned int v_movebit);

  void dst_BasicTransform_0(int vsrc_0,int vsrc_1,int* pdst_0,int* pdst_1);
  void dst_BasicTransform_1(int vsrc_0,int vsrc_1,int* pdst_0,int* pdst_1);
  void dst_BasicTransform_2(int vsrc_0,int* pdst_0);

  void dctTransform_8_1(int *max_src,int *max_dst);
  void dctTransform_8_1_stage0(int *max_src,int *max_dst);
  void dctTransform_8_1_stage1(int *max_src,int *max_dst);
  void dctTransform_8_1_stage2(int *max_src,int *max_dst);
  void dctTransform_8_1_stage3(int *max_src,int *max_dst);
  void dctTransform_8_1_stage4(int *max_src,int *max_dst);

  void dctTransform_64_2(int *max_src,int *max_dst);

  /**
   * [transposeMatrix_8_8 仅用于对[8*8]的矩阵进行转置]
   * @param max_src [description]
   * @param max_dst [description]
   */
  void transposeMatrix_8_8(int *max_src,int * max_dst);

  void dctTransform_64_2_v(const char *max_src,int * max_dst);
  void dctTransform_64_2_v_withfloat(const char *max_src,int * max_dst);


  void printList(int * v_list, int size);

  void dctTransform_8_1_withfloat(int *max_src,int *max_dst);

  void dctTransform_64_2_with_flost(int *max_src,int *max_dst);

  // void dctTransform_64_2_flost_direct(int *max_src,int *max_dst);



  #ifdef __cplusplus
  }

  #endif



#endif
