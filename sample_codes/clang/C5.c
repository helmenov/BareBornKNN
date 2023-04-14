/*=============================================*/
/*    画像ファイルを順番に開くプログラム       */
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
	int iRow, iCol, iImg;				 //■ ループ用変数
	unsigned char Pix[SizeRow][SizeCol]; //■ バイナリ画像データ格納用
	char buff[SizeBuff];
	char filename[LenFilename]; //■ ファイルネーム格納用
	FILE *fp;					//■ ファイルポインタ

	for (iImg = 0; iImg < NumImg; iImg++)
	{

		/* sprintf関数でファイル名を作成する */
		sprintf(filename, "./test_data/d%d.pgm", iImg);
		printf("画像 %sを開きます\n", filename);

		fp = fopen(filename, "rb");	   //■ ファイルを開く
		fgets(buff, sizeof(buff), fp); //■ ファイルの識別符号を読み込み
		fgets(buff, sizeof(buff), fp); //■ 画像サイズの読み込み
		fgets(buff, sizeof(buff), fp); //■ 最大輝度値の読み込み

		//■ 画像データの読み込み
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix[iRow][iCol] = fgetc(fp);
			}
		}

		fclose(fp);

		printf("画像 %sの一番初めの画素のR値は%dです\n", filename, Pix[0][0]);
	}

	return 0;
}
