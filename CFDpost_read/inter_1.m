clear;clc;clf;
x1=0;r1=255;b1=0;
x2=1;r2=0;b2=255;
xx=linspace(x1,x2,200);
RGB12=[r1,0,b1;r2,0,b2];
PP=255*ones(numel(xx),numel(xx),3);
for NxN=1:numel(xx)
    x=xx(NxN);
    scale=[x2-x,x-x1];
    RGB=scale*RGB12;
    PP(NxN,NxN,1:3)=RGB';
end
PP=uint8(PP);
imshow(PP)