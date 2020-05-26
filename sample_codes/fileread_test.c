/*=============================================================*/
/*  100枚の画像ファイルを読み込んで配列に展開するプログラム   */
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
	int iRow, iCol, iImg;						 //■ ループ用変数
	unsigned char Pix[NumImg][SizeRow][SizeCol]; //■ バイナリ画像データ格納用
	char buff[SizeBuf];
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
				Pix[iImg][iRow][iCol] = fgetc(fp);
			}
		}

		fclose(fp);
	}

	return 0;
}
