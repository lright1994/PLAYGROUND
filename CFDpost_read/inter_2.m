
clear;clc;clf
%ÿһ����5������������������(x,y)����ɫ(R,G,B)
x1=0;y1=0;% P1����
R1=255;G1=0;B1=0;%P1��ɫ
x2=400;y2=500;% P2���� P2Ϊ�����εĴ�Ƕ���
R2=0;G2=255;B2=0;%P2��ɫ
x3=1000;y3=0;% P3����
R3=0;G3=0;B3=255;%P3��ɫ
RGB123=[R1,R2,R3;G1,G2,G3;B1,B2,B3];%��ɫ����
k12=(y2-y1)/(x2-x1);% �߶�P1P2��б��
b12=0;%�߶�P1P2�ؾ�
k23=(y3-y2)/(x3-x2);%�߶�P2P3��б��
b23=(y3-y2)/(x3-x2)*(-x3);%�߶�P2P3�Ľؾ�
xx=linspace(x1,x3,501);
yy=linspace(0,y2,501);
PP=255*ones(numel(xx),numel(yy),3);
for NxN=1:numel(xx)
x=xx(NxN);
for NyN=1:numel(yy)
y=yy(NyN);
Flag=0;
if x<x2&x>=x1&y<=x*k12+b12&y>=0%�ж��Ƿ�����������
Flag=1;
end
if x>=x2&x<=x3&y<=x*k23+b23&y>=0%�ж��Ƿ�����������
Flag=1;
end
if Flag==1
M=(y2-y1)*(x3-x1)-(y3-y1)*(x2-x1);
u=[(y-y1)*(x3-x1)-(y3-y1)*(x-x1)]/M;%�����Է�����
v=[(y2-y1)*(x-x1)-(y-y1)*(x2-x1)]/M;
Scale=[1-u-v;u;v];
RGB=RGB123*Scale;%��Ȩƽ��
PP(NyN,NxN,1:3)=RGB';
end
end
end
PP=uint8(PP);
imshow(PP)
