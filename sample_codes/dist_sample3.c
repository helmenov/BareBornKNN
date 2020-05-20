/*====================================================================*/
/*  2000��ζ��եǡ����ȡ�100��Υƥ��ȥǡ������ɤ߹��ߵ�Υ��׻�����ƥ���   */
/*====================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 784

int main(void)
{
    int i,j,Image;                              //�� �롼�����ѿ�
    unsigned char *Pix_tes;                     //�� �Х��ʥ�����ǡ�����Ǽ��
    unsigned char *Pix_tr;                      //�� �Х��ʥ�����ǡ�����Ǽ��
    char buff[128];
    char filename[100];                         //�� �ե�����͡����Ǽ��
    FILE *fp;                                   //�� �ե�����ݥ���
    int tes_i, tr_i;
    int tes_label[100], tr_label[2000];

    double fsum, *tes_vec, *tr_vec;

    Pix_tes = calloc( 100*28*28, sizeof(unsigned char));
    Pix_tr  = calloc( 2000*28*28, sizeof(unsigned char));
    tes_vec = calloc( 100*DIM, sizeof(double));
    tr_vec  = calloc( 2000*DIM, sizeof(double));


    for(Image=0;Image<100;Image++){
	/* sprintf�ؿ��ǥե�����̾��������� */
	sprintf(filename,"./test_data/d%d.pgm",Image);
    
	fp=fopen(filename, "rb" );            //�� �ե�����򳫤�
	fgets(buff,128,fp);                   //�� �ե�����μ��������ɤ߹���
	fgets(buff,128,fp);                   //�� �������������ɤ߹���
	fgets(buff,128,fp);                   //�� ���統���ͤ��ɤ߹���
    
	//�� �����ǡ������ɤ߹���
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pix_tes[Image*DIM+i*28+j] = fgetc(fp);
	    }
	}
	fclose(fp);
    }

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
		Pix_tr[Image*DIM+i*28+j] = fgetc(fp);
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
    fp=fopen("train_label.txt", "rb" );
    for(i=0;i<2000;i++){
	fgets(buff,128,fp);
	sscanf(buff,"%d",&tr_label[i]);
    }

    // ���ȿž
    for(Image=0;Image<100;Image++){
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		tes_vec[Image*DIM+i*28+j] = 
		    (255 - Pix_tes[Image*DIM+i*28+j]) / 255.0;
	    }
	}
    }
    for(Image=0;Image<2000;Image++){
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		tr_vec[Image*DIM+i*28+j] = 
		    (255 - Pix_tr[Image*DIM+i*28+j]) / 255.0;
	    }
	}
    }

    // �٥��ȥ� ������

    for(Image=0;Image<100;Image++){
	fsum = 0;
	for(i=0;i<DIM;i++){
	    fsum += tes_vec[Image*DIM+i];
	}
	for(i=0;i<DIM;i++){
	    tes_vec[Image*DIM+i] /= fsum;
	}
    }
    for(Image=0;Image<2000;Image++){
	fsum = 0;
	for(i=0;i<DIM;i++){
	    fsum += tr_vec[Image*DIM+i];
	}
	for(i=0;i<DIM;i++){
	    tr_vec[Image*DIM+i] /= fsum;
	}
    }

    //�� ��Υ�׻�
    for(tr_i=0;tr_i<2000;tr_i++){
	tes_i = 0;
	fsum=0;
	for(i=0;i<DIM;i++){
	    fsum += (tes_vec[tes_i*DIM+i]-tr_vec[tr_i*DIM+i])
		*(tes_vec[tes_i*DIM+i]-tr_vec[tr_i*DIM+i]);
	}
	printf("No.%d  label:%d  dist:%.4f\n", 
	       tr_i+1, tr_label[tr_i], sqrt(fsum) );
    }
    return(0);
}
