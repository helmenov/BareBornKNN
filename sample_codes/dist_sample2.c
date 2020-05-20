/*========================================================================*/
/*  100枚の画像ファイルとラベルファイルを読み込んで距離を計算するテスト   */
/*========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 784

int main(void)
{
    int i,j,Image;                              //■ ループ用変数
    unsigned char Pix[100][28][28];             //■ バイナリ画像データ格納用
    char buff[128];
    char filename[100];                         //■ ファイルネーム格納用
    FILE *fp;                                   //■ ファイルポインタ
    double fsum, Pvec[100][DIM];
    int tes_label[100];

    for(Image=0;Image<100;Image++){
    
	/* sprintf関数でファイル名を作成する */
	sprintf(filename,"./test_data/d%d.pgm",Image);
	//	printf("画像 %sを開きます\n",filename);
    
	fp=fopen(filename, "rb" );            //■ ファイルを開く
	fgets(buff,128,fp);                   //■ ファイルの識別符号を読み込み
	fgets(buff,128,fp);                   //■ 画像サイズの読み込み
	fgets(buff,128,fp);                   //■ 最大輝度値の読み込み
    
	//■ 画像データの読み込み
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pix[Image][i][j] = fgetc(fp);
	    }
	}
	fclose(fp);
    }

    //■ ラベルデータの読み込み
    fp=fopen("test_label.txt", "rb" );
    for(i=0;i<100;i++){
	fgets(buff,128,fp);
	sscanf(buff,"%d",&tes_label[i]);
    }

    //■ 画素値を変換(白:0 黒:1)して，１次元ベクトルに代入
    for(Image=0;Image<100;Image++){
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pvec[Image][28*i+j] = (255 - Pix[Image][i][j]) / 255.0;
	    }
	}
    }

    //■ ベクトルの要素の和を 1に正規化
    for(Image=0;Image<100;Image++){
	fsum = 0;
	for(i=0;i<DIM;i++){
	    fsum += Pvec[Image][i];
	}
	for(i=0;i<DIM;i++){
	    Pvec[Image][i] /= fsum;
	}
    }

    //■ １枚目の画像とそれ以外の画像の間の距離を計算
    for(Image=0;Image<100;Image++){
	fsum=0;
	for(i=0;i<DIM;i++){
	    fsum += (Pvec[0][i]-Pvec[Image][i])
		*(Pvec[0][i]-Pvec[Image][i]);
	}
	printf("No.%d  label:%d  dist:%.4f\n", 
	       Image+1, tes_label[Image], sqrt(fsum) );
    }

    return(0);
}
