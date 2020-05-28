/*============================================================*/
/*  �ƥ��ȥǡ�����2000��ζ��եǡ����Ȥε�Υ�����������ɽ������   */
/*============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const unsigned int NumTesImg = 100;
const unsigned int NumTrImg = 2000;
const unsigned int SizeRow = 28;
const unsigned int SizeCol = 28;
const unsigned int SizeBuff = 128;
const unsigned int LenFilename = 100;
const unsigned char WHITE = 255;
const unsigned int RefImgNo = 1;

#define DIM (SizeRow * SizeCol)

int main(void)
{
	int iRow, iCol, iDim, p,q;		//�� �롼�����ѿ�
	unsigned char *Pix_tes; //�� �Х��ʥ�����ǡ�����Ǽ��
	unsigned char *Pix_tr;	//�� �Х��ʥ�����ǡ�����Ǽ��
	char buff[SizeBuff];
	char filename[LenFilename]; //�� �ե�����͡����Ǽ��
	FILE *fp;					//�� �ե�����ݥ���
	int iTesImg, iTrImg;
	int tes_label[NumTesImg], tr_label[NumTrImg];
	double fsum, *tes_vec, *tr_vec;

	int dist_no[NumTrImg], dist_nobuf;
	double dist_val[NumTrImg], dist_valbuf;
	int dist_class[NumTrImg], dist_classbuf;

	Pix_tes = calloc(NumTesImg * DIM, sizeof(unsigned char));
	Pix_tr = calloc(NumTrImg * DIM, sizeof(unsigned char));
	tes_vec = calloc(NumTesImg * DIM, sizeof(double));
	tr_vec = calloc(NumTrImg * DIM, sizeof(double));

	for (iTesImg = 0; iTesImg < NumTesImg; iTesImg++)
	{
		/* sprintf�ؿ��ǥե�����̾��������� */
		sprintf(filename, "./test_data/d%d.pgm", iTesImg);

		fp = fopen(filename, "rb"); //�� �ե�����򳫤�
		fgets(buff, SizeBuff, fp);	//�� �ե�����μ��������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� �������������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� ���統���ͤ��ɤ߹���

		//�� �����ǡ������ɤ߹���
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix_tes[iTesImg * DIM + iRow * SizeCol + iCol] = fgetc(fp);
			}
		}
		fclose(fp);
	}

	for (iTrImg = 0; iTrImg < NumTrImg; iTrImg++)
	{
		/* sprintf�ؿ��ǥե�����̾��������� */
		sprintf(filename, "./train_data/d%d.pgm", iTrImg);

		fp = fopen(filename, "rb"); //�� �ե�����򳫤�
		fgets(buff, SizeBuff, fp);	//�� �ե�����μ��������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� �������������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� ���統���ͤ��ɤ߹���

		//�� �����ǡ������ɤ߹���
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix_tr[iTrImg * DIM + iRow * SizeCol + iCol] = fgetc(fp);
			}
		}
		fclose(fp);
	}

	//�� ��٥�ǡ������ɤ߹���
	fp = fopen("test_label.txt", "rb");
	for (iTesImg = 0; iTesImg < NumTesImg; iTesImg++)
	{
		fgets(buff, SizeBuff, fp);
		sscanf(buff, "%d", &tes_label[iTesImg]);
	}
	fp = fopen("train_label.txt", "rb");
	for (iTrImg = 0; iTrImg < NumTrImg; iTrImg++)
	{
		fgets(buff, SizeBuff, fp);
		sscanf(buff, "%d", &tr_label[iTrImg]);
	}

	// ���ȿž
	for (iTesImg = 0; iTesImg < NumTesImg; iTesImg++)
	{
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				tes_vec[iTesImg * DIM + iRow * SizeCol + iCol] =
					(WHITE - (double)Pix_tes[iTesImg * DIM + iRow * SizeCol + iCol]) / WHITE;
			}
		}
	}
	for (iTrImg = 0; iTrImg < NumTrImg; iTrImg++)
	{
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				tr_vec[iTrImg * DIM + iRow * SizeCol + iCol] =
					(WHITE - (double)Pix_tr[iTrImg * DIM + iRow * SizeCol + iCol]) / WHITE;
			}
		}
	}

	// �٥��ȥ� ������

	for (iTesImg = 0; iTesImg < NumTesImg; iTesImg++)
	{
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += tes_vec[iTesImg * DIM + iDim];
		}
		for (iDim = 0; iDim < DIM; iDim++)
		{
			tes_vec[iTesImg * DIM + iDim] /= fsum;
		}
	}
	for (iTrImg = 0; iTrImg < NumTrImg; iTrImg++)
	{
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += tr_vec[iTrImg * DIM + iDim];
		}
		for (iDim = 0; iDim < DIM; iDim++)
		{
			tr_vec[iTrImg * DIM + iDim] /= fsum;
		}
	}

	//�� ��Υ�׻�

	for (iTesImg = 0; iTesImg < NumTesImg; iTesImg++)
	{

		for (iTrImg = 0; iTrImg < NumTrImg; iTrImg++)
		{
			fsum = 0;
			for (iDim = 0; iDim < DIM; iDim++)
			{
				fsum += (tes_vec[iTesImg * DIM + iDim] - tr_vec[iTrImg * DIM + iDim]) * (tes_vec[iTesImg * DIM + iDim] - tr_vec[iTrImg * DIM + iDim]);
			}
			dist_no[iTrImg] = iTrImg;
			dist_val[iTrImg] = fsum;
			dist_class[iTrImg] = tr_label[iTrImg];
		}

		for (p = 0; p < NumTrImg - 1; p++)
		{ //��������˥����Ȥ���
			for (q = p + 1; q < NumTrImg; q++)
			{
				if (dist_val[p] > dist_val[q])
				{
					int_pswap(dist_no,p,q);
					double_pswap(dist_val,p,q);
					int_pswap(dist_class,p,q);
				}
			}
		}

		for (iTrImg = 0; iTrImg < NumTrImg; iTrImg++)
		{
			printf("order %3d  lab:%d  val:%.4f  dataNo.:%d\n",
				   iTrImg + 1, dist_class[iTrImg], sqrt(dist_val[iTrImg]), dist_no[iTrImg] + 1);
		}
	}
	return 0;
}

void int_pswap(int* ptr, int p, int q)
{
	int buf;
	buf = ptr[p];
	ptr[p] = ptr[q];
	ptr[q] = buf;
}

void double_pswap(double* ptr, int p, int q)
{
	double buf;
	buf = ptr[p];
	ptr[p] = ptr[q];
	ptr[q] = buf;
}