/*=============================================================*/
/*  100枚の画像ファイルを読み込んで配列に展開するプログラム   */
/*=============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int i,j,Image;                              //■ ループ用変数
    unsigned char Pix[100][28][28];             //■ バイナリ画像データ格納用
    char buff[128];
    char filename[100];                         //■ ファイルネーム格納用
    FILE *fp;                                   //■ ファイルポインタ
  
    for(Image=0;Image<100;Image++){
    
	/* sprintf関数でファイル名を作成する */
	sprintf(filename,"./test_data/d%d.pgm",Image);
	printf("画像 %sを開きます\n",filename);
    
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

    return(0);
}
