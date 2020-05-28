/*=============================================================*/
/*  100枚の画像ファイルを読み込んで距離を計算するテスト   */
/*=============================================================*/
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
	int iRow, iCol, iImg, iDim;							 //■ ループ用変数
	unsigned char Pix[NumImg][SizeRow][SizeCol]; //■ バイナリ画像データ格納用
	char buff[SizeBuff];
	char filename[LenFilename]; //■ ファイルネーム格納用
	FILE *fp;					//■ ファイルポインタ
	double fsum, Pvec[NumImg][DIM];

	for (iImg = 0; iImg < NumImg; iImg++)
	{

		/* sprintf関数でファイル名を作成する */
		sprintf(filename, "..\\MNIST\\test_data\\d%d.pgm", iImg);
		printf("画像 %sを開きます\n",filename);

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

	//■ 画素値を変換(白:0 黒:1)して，１次元ベクトルに代入
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

	//■ ベクトルの要素の和を 1に正規化
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

	//■ RefImgNo 枚目の画像とそれ以外の画像の間の距離を計算
	for (iImg = 0; iImg < NumImg; iImg++)
	{
		fsum = 0;
		for (iDim = 0; iDim < DIM; iDim++)
		{
			fsum += (Pvec[RefImgNo - 1][iDim] - Pvec[iImg][iDim]) * (Pvec[RefImgNo - 1][iDim] - Pvec[iImg][iDim]);
		}
		printf("No.%d  dist:%.4f\n", iImg + 1, sqrt(fsum));
	}

	return 0;
}
