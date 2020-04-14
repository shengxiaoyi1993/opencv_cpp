

# README

- this project is designed to test the opencv-lib and provide a form to build a
project with similar format.  

# 流程
- 根据`doc/dac16fss.pdf`理解算法流程
- 根据根据碟形图的算法流程进行一维DCT编码，但碟形图中有错误
```
Figure 3: (a) s(7) 中的KN算子 参数错误(2^(1/2),1)应为（2^(1/2),6）。
推导出正确参数的过程见文档`doc/A Fast Computational Algorithm for the Discrete Cosine Transform.pdf`
根据文中提供的公式，推导N=4时的参数，能够计算出n=6
```
- 然后进行二维DCT编码,如果使用蝶形图上的一维变换或者对应的一维变换公式，需要注意，计算出二维变换结果后除以8
