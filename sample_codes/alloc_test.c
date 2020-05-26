/*===================================================================*/
/*  callocを使って配列を確保し、2000枚の教師データを読み込むテスト   */
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
	int iRow, iCol, iImg; //■ ループ用変数

	unsigned char *Pix_tr; //■ バイナリ画像データ格納用
	char buff[SizeBuff];
	char filename[LenFilename]; //■ ファイルネーム格納用
	FILE *fp;					//■ ファイルポインタ

	Pix_tr = calloc(NumTrainImg * SizeRow * SizeCol, sizeof(unsigned char));

	for (iImg = 0; iImg < NumTrainImg; iImg++)
	{
		/* sprintf関数でファイル名を作成する */
		sprintf(filename, "./train_data/d%d.pgm", iImg);

		fp = fopen(filename, "rb");	   //■ ファイルを開く
		fgets(buff, sizeof(buff), fp); //■ ファイルの識別符号を読み込み
		fgets(buff, sizeof(buff), fp); //■ 画像サイズの読み込み
		fgets(buff, sizeof(buff), fp); //■ 最大輝度値の読み込み

		//■ 画像データの読み込み
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
