/*============================================================*/
/*  テストデータと2000枚の教師データとの距離が小さい順に表示する   */
/*============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIM 784

int main(void)
{
    int i,j,k,Image;                            //■ ループ用変数
    unsigned char *Pix_tes;                     //■ バイナリ画像データ格納用
    unsigned char *Pix_tr;                      //■ バイナリ画像データ格納用
    char buff[128];
    char filename[100];                         //■ ファイルネーム格納用
    FILE *fp;                                   //■ ファイルポインタ
    int tes_i, tr_i;
    int tes_label[100], tr_label[2000];
    double fsum, *tes_vec, *tr_vec;

    int    dist_no[2000], dist_nobuf;
    double dist_val[2000], dist_valbuf;
    int    dist_class[2000], dist_classbuf;


    Pix_tes = calloc( 100*28*28, sizeof(unsigned char));
    Pix_tr  = calloc( 2000*28*28, sizeof(unsigned char));
    tes_vec = calloc( 100*DIM, sizeof(double));
    tr_vec  = calloc( 2000*DIM, sizeof(double));


    for(Image=0;Image<100;Image++){
	/* sprintf関数でファイル名を作成する */
	sprintf(filename,"./test_data/d%d.pgm",Image);
    
	fp=fopen(filename, "rb" );            //■ ファイルを開く
	fgets(buff,128,fp);                   //■ ファイルの識別符号を読み込み
	fgets(buff,128,fp);                   //■ 画像サイズの読み込み
	fgets(buff,128,fp);                   //■ 最大輝度値の読み込み
    
	//■ 画像データの読み込み
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		Pix_tes[Image*DIM+i*28+j] = fgetc(fp);
	    }
	}
	fclose(fp);
    }

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
		Pix_tr[Image*DIM+i*28+j] = fgetc(fp);
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
    fp=fopen("train_label.txt", "rb" );
    for(i=0;i<2000;i++){
	fgets(buff,128,fp);
	sscanf(buff,"%d",&tr_label[i]);
    }

    // 白黒反転
    for(Image=0;Image<100;Image++){
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		tes_vec[Image*DIM+i*28+j] = 
		    (255 - Pix_tes[Image*DIM+i*28+j]) / 255.0;
	    }
	}
    }
    for(Image=0;Image<2000;Image++){
	for(i=0;i<28;i++){
	    for(j=0;j<28;j++){
		tr_vec[Image*DIM+i*28+j] = 
		    (255 - Pix_tr[Image*DIM+i*28+j]) / 255.0;
	    }
	}
    }

    // ベクトル 正規化

    for(Image=0;Image<100;Image++){
	fsum = 0;
	for(i=0;i<DIM;i++){
	    fsum += tes_vec[Image*DIM+i];
	}
	for(i=0;i<DIM;i++){
	    tes_vec[Image*DIM+i] /= fsum;
	}
    }
    for(Image=0;Image<2000;Image++){
	fsum = 0;
	for(i=0;i<DIM;i++){
	    fsum += tr_vec[Image*DIM+i];
	}
	for(i=0;i<DIM;i++){
	    tr_vec[Image*DIM+i] /= fsum;
	}
    }


    //■ 距離計算

    for(tes_i=0;tes_i<1;tes_i++){


	for(tr_i=0;tr_i<2000;tr_i++){
	    fsum=0;
	    for(i=0;i<DIM;i++){
		fsum += (tes_vec[tes_i*DIM+i]-tr_vec[tr_i*DIM+i])
		    *(tes_vec[tes_i*DIM+i]-tr_vec[tr_i*DIM+i]);
	    }
	    dist_no[tr_i] = tr_i;
	    dist_val[tr_i] = fsum;
	    dist_class[tr_i] = tr_label[tr_i];
	}


	for(k=0;k<2000-1;k++){  //小さい順にソートする
	    for( i=k+1 ; i<2000 ; i++){
		if( dist_val[k] > dist_val[i] ){
		    dist_nobuf = dist_no[k];
		    dist_no[k] = dist_no[i];
		    dist_no[i] = dist_nobuf;

		    dist_valbuf = dist_val[k];
		    dist_val[k] = dist_val[i];
		    dist_val[i] = dist_valbuf;

		    dist_classbuf = dist_class[k];
		    dist_class[k] = dist_class[i];
		    dist_class[i] = dist_classbuf;
		}
	    }
	}

	for(j=0;j<2000;j++){
	    printf("order %3d  lab:%d  val:%.4f  dataNo.:%d\n", 
	       j+1, dist_class[j], sqrt(dist_val[j]), dist_no[j]+1);
	}

    }
    return(0);
}
