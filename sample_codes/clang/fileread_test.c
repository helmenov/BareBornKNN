/*=============================================================*/
/*  100��β����ե�������ɤ߹���������Ÿ������ץ����   */
/*=============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NumImg 100
#define SizeRow 28
#define SizeCol 28
#define SizeBuf 128
#define LenFilename 100

int main(void)
{
	int iRow, iCol, iImg;						 //�� �롼�����ѿ�
	unsigned char Pix[NumImg][SizeRow][SizeCol]; //�� �Х��ʥ�����ǡ�����Ǽ��
	char buff[SizeBuf];
	char filename[LenFilename]; //�� �ե�����͡����Ǽ��
	FILE *fp;					//�� �ե�����ݥ���

	for (iImg = 0; iImg < NumImg; iImg++)
	{

		/* sprintf�ؿ��ǥե�����̾��������� */
		sprintf(filename, "./test_data/d%d.pgm", iImg);
		printf("���� %s�򳫤��ޤ�\n", filename);

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

	return 0;
}
