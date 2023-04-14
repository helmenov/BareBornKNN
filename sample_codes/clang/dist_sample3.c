/*====================================================================*/
/*  2000枚の教師データと，100枚のテストデータを読み込み距離を計算するテスト   */
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
	int iRow, iCol, iDim, iImg; //■ ループ用変数
	unsigned char *Pix_tes;		//■ バイナリ画像データ格納用
	unsigned char *Pix_tr;		//■ バイナリ画像データ格納用
	char buff[SizeBuff];
	char filename[LenFilename]; //■ ファイルネーム格納用
	FILE *fp;					//■ ファイルポインタ
	int tes_i, tr_i;
	int tes_label[NumTesImg], tr_label[NumTrImg];

	double fsum, *tes_vec, *tr_vec;

	Pix_tes = calloc(NumTesImg * DIM, sizeof(unsigned char));
	Pix_tr = calloc(NumTrImg * DIM, sizeof(unsigned char));
	tes_vec = calloc(NumTesImg * DIM, sizeof(double));
	tr_vec = calloc(NumTrImg * DIM, sizeof(double));

	for (iImg = 0; iImg < NumTesImg; iImg++)
	{
		/* sprintf関数でファイル名を作成する */
		sprintf(filename, "./test_data/d%d.pgm", iImg);

		fp = fopen(filename, "rb"); //■ ファイルを開く
		fgets(buff, SizeBuff, fp);	//■ ファイルの識別符号を読み込み
		fgets(buff, SizeBuff, fp);	//■ 画像サイズの読み込み
		fgets(buff, SizeBuff, fp);	//■ 最大輝度値の読み込み

		//■ 画像データの読み込み
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
		/* sprintf関数でファイル名を作成する */
		sprintf(filename, "./train_data/d%d.pgm", iImg);

		fp = fopen(filename, "rb"); //■ ファイルを開く
		fgets(buff, SizeBuff, fp);	//■ ファイルの識別符号を読み込み
		fgets(buff, SizeBuff, fp);	//■ 画像サイズの読み込み
		fgets(buff, SizeBuff, fp);	//■ 最大輝度値の読み込み

		//■ 画像データの読み込み
		for (iRow = 0; iRow < SizeRow; iRow++)
		{
			for (iCol = 0; iCol < SizeCol; iCol++)
			{
				Pix_tr[iImg * DIM + iRow * SizeCol + iCol] = fgetc(fp);
			}
		}
		fclose(fp);
	}

	//■ ラベルデータの読み込み
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

	// 白黒反転
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

	// ベクトル 正規化

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

	//■ 距離計算
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
