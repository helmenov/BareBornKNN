/*====================================================================*/
/*  2000��ζ��եǡ����ȡ�100��Υƥ��ȥǡ������ɤ߹��ߵ�Υ��׻�����ƥ���   */
/*====================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NumTesImg 100
#define NumTrImg 2000
#define SizeRow 28
#define SizeCol 28
#define SizeBuff SizeBuff
#define LenFilename 100
#define DIM (SizeRow * SizeCol)
#define WHITE 255
#define RefImgNo 1

int main(void)
{
	int iRow, iCol, iDim, iImg; //�� �롼�����ѿ�
	unsigned char *Pix_tes;		//�� �Х��ʥ�����ǡ�����Ǽ��
	unsigned char *Pix_tr;		//�� �Х��ʥ�����ǡ�����Ǽ��
	char buff[SizeBuff];
	char filename[LenFilename]; //�� �ե�����͡����Ǽ��
	FILE *fp;					//�� �ե�����ݥ���
	int tes_i, tr_i;
	int tes_label[NumTesImg], tr_label[NumTrImg];

	double fsum, *tes_vec, *tr_vec;

	Pix_tes = calloc(NumTesImg * DIM, sizeof(unsigned char));
	Pix_tr = calloc(NumTrImg * DIM, sizeof(unsigned char));
	tes_vec = calloc(NumTesImg * DIM, sizeof(double));
	tr_vec = calloc(NumTrImg * DIM, sizeof(double));

	for (iImg = 0; iImg < NumTesImg; iImg++)
	{
		/* sprintf�ؿ��ǥե�����̾��������� */
		sprintf(filename, "./test_data/d%d.pgm", iImg);

		fp = fopen(filename, "rb"); //�� �ե�����򳫤�
		fgets(buff, SizeBuff, fp);	//�� �ե�����μ��������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� �������������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� ���統���ͤ��ɤ߹���

		//�� �����ǡ������ɤ߹���
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix_tes[iImg * DIM + iRow * SizeCol + iCol] = fgetc(fp);
			}
		}
		fclose(fp);
	}

	for (iImg = 0; iImg < NumTrImg; iImg++)
	{
		/* sprintf�ؿ��ǥե�����̾��������� */
		sprintf(filename, "./train_data/d%d.pgm", iImg);

		fp = fopen(filename, "rb"); //�� �ե�����򳫤�
		fgets(buff, SizeBuff, fp);	//�� �ե�����μ��������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� �������������ɤ߹���
		fgets(buff, SizeBuff, fp);	//�� ���統���ͤ��ɤ߹���

		//�� �����ǡ������ɤ߹���
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix_tr[iImg * DIM + iRow * SizeCol + iCol] = fgetc(fp);
			}
		}
		fclose(fp);
	}

	//�� ��٥�ǡ������ɤ߹���
	fp = fopen("test_label.txt", "rb");
	for (iImg = 0; iImg < NumTesImg; iImg++)
	{
		fgets(buff, SizeBuff, fp);
		sscanf(buff, "%d", &tes_label[iImg]);
	}
	fp = fopen("train_label.txt", "rb");
	for (iImg = 0; iImg < NumTrImg; iImg++)
	{
		fgets(buff, SizeBuff, fp);
		sscanf(buff, "%d", &tr_label[iImg]);
	}

	// ���ȿž
	for (iImg = 0; iImg < NumTesImg; iImg++)
	{
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				tes_vec[iImg * DIM + iRow * SizeCol + iCol] =
					(WHITE - (double)Pix_tes[iImg * DIM + iRow * SizeCol + iCol]) / WHITE;
			}
		}
	}
	for (iImg = 0; iImg < NumTrImg; iImg++)
	{
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				tr_vec[iImg * DIM + iRow * SizeCol + iCol] =
					(WHITE - (double)Pix_tr[iImg * DIM + iRow * SizeCol + iCol]) / WHITE;
			}
		}
	}

	// �٥��ȥ� ������

	for (iImg = 0; iImg < NumTesImg; iImg++)
	{
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += tes_vec[iImg * DIM + iDim];
		}
		for (iDim = 0; iDim < DIM; iDim++)
		{
			tes_vec[iImg * DIM + iDim] /= fsum;
		}
	}
	for (iImg = 0; iImg < NumTrImg; iImg++)
	{
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += tr_vec[iImg * DIM + iDim];
		}
		for (iDim = 0; iDim < DIM; iDim++)
		{
			tr_vec[iImg * DIM + iDim] /= fsum;
		}
	}

	//�� ��Υ�׻�
	for (tr_i = 0; tr_i < NumTrImg; tr_i++)
	{
		tes_i = 0;
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += (tes_vec[tes_i * DIM + iDim] - tr_vec[tr_i * DIM + iDim]) * (tes_vec[tes_i * DIM + iDim] - tr_vec[tr_i * DIM + iDim]);
		}
		printf("No.%d  label:%d  dist:%.4f\n",
			   tr_i + 1, tr_label[tr_i], sqrt(fsum));
	}
	return 0;
}
