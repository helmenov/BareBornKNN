/*========================================================================*/
/*  100��β����ե�����ȥ�٥�ե�������ɤ߹���ǵ�Υ��׻�����ƥ���   */
/*========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 784

int main(void)
{
    int i,j,Image;                              //�� �롼�����ѿ�
    unsigned char Pix[100][28][28];             //�� �Х��ʥ�����ǡ�����Ǽ��
    char buff[128];
    char filename[100];                         //�� �ե�����͡����Ǽ��
    FILE *fp;                                   //�� �ե�����ݥ���
    double fsum, Pvec[100][DIM];
    int tes_label[100];

    for(Image=0;Image<100;Image++){
    
	/* sprintf�ؿ��ǥե�����̾��������� */
	sprintf(filename,"./test_data/d%d.pgm",Image);
	//	printf("���� %s�򳫤��ޤ�\n",filename);
    
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

    //�� ��٥�ǡ������ɤ߹���
    fp=fopen("test_label.txt", "rb" );
    for(i=0;i<100;i++){
	fgets(buff,128,fp);
	sscanf(buff,"%d",&tes_label[i]);
    }

    //�� �����ͤ��Ѵ�(��:0 ��:1)���ơ��������٥��ȥ������
    for(Image=0;Image<100;Image++){
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pvec[Image][28*i+j] = (255 - Pix[Image][i][j]) / 255.0;
	    }
	}
    }

    //�� �٥��ȥ�����Ǥ��¤� 1��������
    for(Image=0;Image<100;Image++){
	fsum = 0;
	for(i=0;i<DIM;i++){
	    fsum += Pvec[Image][i];
	}
	for(i=0;i<DIM;i++){
	    Pvec[Image][i] /= fsum;
	}
    }

    //�� �����ܤβ����Ȥ���ʳ��β����δ֤ε�Υ��׻�
    for(Image=0;Image<100;Image++){
	fsum=0;
	for(i=0;i<DIM;i++){
	    fsum += (Pvec[0][i]-Pvec[Image][i])
		*(Pvec[0][i]-Pvec[Image][i]);
	}
	printf("No.%d  label:%d  dist:%.4f\n", 
	       Image+1, tes_label[Image], sqrt(fsum) );
    }

    return(0);
}
