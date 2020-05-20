/*===================================================================*/
/*  callocを使って配列を確保し、2000枚の教師データを読み込むテスト   */
/*===================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int i,j,Image;                              //■ ループ用変数

    unsigned char *Pix_tr;                      //■ バイナリ画像データ格納用
    char buff[128];
    char filename[100];                         //■ ファイルネーム格納用
    FILE *fp;                                   //■ ファイルポインタ

    Pix_tr  = calloc( 2000*28*28, sizeof(unsigned char));

    for(Image=0;Image<2000;Image++){
	/* sprintf関数でファイル名を作成する */
	sprintf(filename,"./train_data/d%d.pgm",Image);
    
	fp=fopen(filename, "rb" );            //■ ファイルを開く
	fgets(buff,128,fp);                   //■ ファイルの識別符号を読み込み
	fgets(buff,128,fp);                   //■ 画像サイズの読み込み
	fgets(buff,128,fp);                   //■ 最大輝度値の読み込み
    
	//■ 画像データの読み込み
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pix_tr[Image*28*28+i*28+j] = fgetc(fp);
	    }
	}
	fclose(fp);
    }


    return(0);
}
