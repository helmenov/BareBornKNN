/*===================================================================*/
/*  calloc��Ȥä��������ݤ���2000��ζ��եǡ������ɤ߹���ƥ���   */
/*===================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int i,j,Image;                              //�� �롼�����ѿ�

    unsigned char *Pix_tr;                      //�� �Х��ʥ�����ǡ�����Ǽ��
    char buff[128];
    char filename[100];                         //�� �ե�����͡����Ǽ��
    FILE *fp;                                   //�� �ե�����ݥ���

    Pix_tr  = calloc( 2000*28*28, sizeof(unsigned char));

    for(Image=0;Image<2000;Image++){
	/* sprintf�ؿ��ǥե�����̾��������� */
	sprintf(filename,"./train_data/d%d.pgm",Image);
    
	fp=fopen(filename, "rb" );            //�� �ե�����򳫤�
	fgets(buff,128,fp);                   //�� �ե�����μ��������ɤ߹���
	fgets(buff,128,fp);                   //�� �������������ɤ߹���
	fgets(buff,128,fp);                   //�� ���統���ͤ��ɤ߹���
    
	//�� �����ǡ������ɤ߹���
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pix_tr[Image*28*28+i*28+j] = fgetc(fp);
	    }
	}
	fclose(fp);
    }


    return(0);
}
