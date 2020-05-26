/*=============================================*/
/*    �����ե��������֤˳����ץ����       */
/*=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SizeRow 28
#define SizeCol 28
#define SizeBuff 128
#define LenFilename 100
#define NumImg 15

int main(void)
{
	int iRow, iCol, iImg;				 //�� �롼�����ѿ�
	unsigned char Pix[SizeRow][SizeCol]; //�� �Х��ʥ�����ǡ�����Ǽ��
	char buff[SizeBuff];
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
				Pix[iRow][iCol] = fgetc(fp);
			}
		}

		fclose(fp);

		printf("���� %s�ΰ��ֽ��β��Ǥ�R�ͤ�%d�Ǥ�\n", filename, Pix[0][0]);
	}

	return 0;
}
