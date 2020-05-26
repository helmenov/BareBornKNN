/*========================================================================*/
/*  100��β����ե�����ȥ�٥�ե�������ɤ߹���ǵ�Υ��׻�����ƥ���   */
/*========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NumImg 100
#define SizeRow 28
#define SizeCol 28
#define SizeBuff 128
#define LenFilename 100
#define DIM (SizeRow * SizeCol)
#define WHITE 255
#define RefImgNo 1

int main(void)
{
	int iRow, iCol, iDim, iImg;					 //�� �롼�����ѿ�
	unsigned char Pix[NumImg][SizeRow][SizeCol]; //�� �Х��ʥ�����ǡ�����Ǽ��
	char buff[SizeBuff];
	char filename[LenFilename]; //�� �ե�����͡����Ǽ��
	FILE *fp;					//�� �ե�����ݥ���
	double fsum, Pvec[NumImg][DIM];
	int tes_label[NumImg];

	for (iImg = 0; iImg < NumImg; iImg++)
	{

		/* sprintf�ؿ��ǥե�����̾��������� */
		sprintf(filename, "./test_data/d%d.pgm", iImg);
		//	printf("���� %s�򳫤��ޤ�\n",filename);

		fp = fopen(filename, "rb");	   //�� �ե�����򳫤�
		fgets(buff, sizeof(buff), fp); //�� �ե�����μ��������ɤ߹���
		fgets(buff, sizeof(buff), fp); //�� �������������ɤ߹���
		fgets(buff, sizeof(buff), fp); //�� ���統���ͤ��ɤ߹���

		//�� �����ǡ������ɤ߹���
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix[iImg][iRow][iCol] = fgetc(fp);
			}
		}
		fclose(fp);
	}

	//�� ��٥�ǡ������ɤ߹���
	fp = fopen("test_label.txt", "rb");
	for (iImg = 0; iImg < NumImg; iImg++)
	{
		fgets(buff, sizeof(buff), fp);
		sscanf(buff, "%d", &tes_label[iImg]);
	}

	//�� �����ͤ��Ѵ�(��:0 ��:1)���ơ��������٥��ȥ������
	for (iImg = 0; iImg < NumImg; iImg++)
	{
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pvec[iImg][SizeCol * iRow + iCol] = (WHITE - (double)Pix[iImg][iRow][iCol]) / WHITE;
			}
		}
	}

	//�� �٥��ȥ�����Ǥ��¤� 1��������
	for (iImg = 0; iImg < NumImg; iImg++)
	{
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += Pvec[iImg][iDim];
		}
		for (iDim = 0; iDim < DIM; iDim++)
		{
			Pvec[iImg][iDim] /= fsum;
		}
	}

	//�� �����ܤβ����Ȥ���ʳ��β����δ֤ε�Υ��׻�
	for (iImg = 0; iImg < NumImg; iImg++)
	{
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += (Pvec[RefImgNo - 1][iDim] - Pvec[iImg][iDim]) * (Pvec[RefImgNo - 1][iDim] - Pvec[iImg][iDim]);
		}
		printf("No.%d  label:%d  dist:%.4f\n",
			   iImg + 1, tes_label[iImg], sqrt(fsum));
	}

	return 0;
}
