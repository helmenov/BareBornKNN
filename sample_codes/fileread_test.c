/*=============================================================*/
/*  100��β����ե�������ɤ߹���������Ÿ������ץ����   */
/*=============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int i,j,Image;                              //�� �롼�����ѿ�
    unsigned char Pix[100][28][28];             //�� �Х��ʥ�����ǡ�����Ǽ��
    char buff[128];
    char filename[100];                         //�� �ե�����͡����Ǽ��
    FILE *fp;                                   //�� �ե�����ݥ���
  
    for(Image=0;Image<100;Image++){
    
	/* sprintf�ؿ��ǥե�����̾��������� */
	sprintf(filename,"./test_data/d%d.pgm",Image);
	printf("���� %s�򳫤��ޤ�\n",filename);
    
	fp=fopen(filename, "rb" );            //�� �ե�����򳫤�
	fgets(buff,128,fp);                   //�� �ե�����μ��������ɤ߹���
	fgets(buff,128,fp);                   //�� �������������ɤ߹���
	fgets(buff,128,fp);                   //�� ���統���ͤ��ɤ߹���
    
	//�� �����ǡ������ɤ߹���
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pix[Image][i][j] = fgetc(fp);
	    }
	}

	fclose(fp);
    }

    return(0);
}
