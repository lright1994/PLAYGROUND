
clear;clc;clf
%每一个由5个参数来描述，坐标(x,y)和颜色(R,G,B)
x1=0;y1=0;% P1坐标
R1=255;G1=0;B1=0;%P1颜色
x2=400;y2=500;% P2坐标 P2为三角形的大角顶点
R2=0;G2=255;B2=0;%P2颜色
x3=1000;y3=0;% P3坐标
R3=0;G3=0;B3=255;%P3颜色
RGB123=[R1,R2,R3;G1,G2,G3;B1,B2,B3];%颜色矩阵
k12=(y2-y1)/(x2-x1);% 线段P1P2的斜率
b12=0;%线段P1P2截距
k23=(y3-y2)/(x3-x2);%线段P2P3的斜率
b23=(y3-y2)/(x3-x2)*(-x3);%线段P2P3的截距
xx=linspace(x1,x3,501);
yy=linspace(0,y2,501);
PP=255*ones(numel(xx),numel(yy),3);
for NxN=1:numel(xx)
x=xx(NxN);
for NyN=1:numel(yy)
y=yy(NyN);
Flag=0;
if x<x2&x>=x1&y<=x*k12+b12&y>=0%判断是否在三角形内
Flag=1;
end
if x>=x2&x<=x3&y<=x*k23+b23&y>=0%判断是否在三角形内
Flag=1;
end
if Flag==1
M=(y2-y1)*(x3-x1)-(y3-y1)*(x2-x1);
u=[(y-y1)*(x3-x1)-(y3-y1)*(x-x1)]/M;%解线性方程组
v=[(y2-y1)*(x-x1)-(y-y1)*(x2-x1)]/M;
Scale=[1-u-v;u;v];
RGB=RGB123*Scale;%加权平均
PP(NyN,NxN,1:3)=RGB';
end
end
end
PP=uint8(PP);
imshow(PP)
