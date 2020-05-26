/*===================================================================*/
/*  calloc��Ȥä��������ݤ���2000��ζ��եǡ������ɤ߹���ƥ���   */
/*===================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SizeBuff 128
#define LenFilename 100
#define NumTrainImg 2000
#define SizeRow 28
#define SizeCol 28

int main(void)
{
	int iRow, iCol, iImg; //�� �롼�����ѿ�

	unsigned char *Pix_tr; //�� �Х��ʥ�����ǡ�����Ǽ��
	char buff[SizeBuff];
	char filename[LenFilename]; //�� �ե�����͡����Ǽ��
	FILE *fp;					//�� �ե�����ݥ���

	Pix_tr = calloc(NumTrainImg * SizeRow * SizeCol, sizeof(unsigned char));

	for (iImg = 0; iImg < NumTrainImg; iImg++)
	{
		/* sprintf�ؿ��ǥե�����̾��������� */
		sprintf(filename, "./train_data/d%d.pgm", iImg);

		fp = fopen(filename, "rb");	   //�� �ե�����򳫤�
		fgets(buff, sizeof(buff), fp); //�� �ե�����μ��������ɤ߹���
		fgets(buff, sizeof(buff), fp); //�� �������������ɤ߹���
		fgets(buff, sizeof(buff), fp); //�� ���統���ͤ��ɤ߹���

		//�� �����ǡ������ɤ߹���
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix_tr[iImg * SizeRow * SizeCol + iRow * SizeCol + iCol] = fgetc(fp);
			}
		}
		fclose(fp);
	}

	return 0;
}
