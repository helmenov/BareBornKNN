/* rand関数で一様乱数を発生させ表示するプログラムと，乱数をファイルに書き出すプログラムを 参考に示します．*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef CONST_SEED
#define MySeed 2020
#else
#define MySeed ((unsigned)time(NULL))
#endif

#define SizeSeries 10

int main(void)
{
  int i;
  FILE *fp;

  /* 現在時間で乱数ジェネレータを初期化する */
  srand(MySeed);

  /* rand()は0からRAND_MAXまでの数値を1つ返す*/
  for (i = 0; i < SizeSeries; i++)
    printf("%d\n", rand());

  /* ファイルの書き出し */
  fp = fopen("test.dat", "w");
  if (fp == NULL)
  {
    fprintf(stderr, "ファイルを開けません.");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < SizeSeries; i++)
    fprintf(fp, "%d\n", rand());
  fclose(fp);

  return 0;
}
