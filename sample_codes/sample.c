/*======================================================*/
/*                      rotation                        */
/*              Programed by Seiji Hotta                */
/*        Last revised by S.Hotta on May  31, 2001.     */
/*======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define  PI 3.14159265
#include "rotation.h"

void main(void)
{
  int           i,j;                 // For loop
  int           xsize=28,ysize=28;   // �摜�T�C�Y
  double        theta=0;             // ��]�p�x�i�x�j
  double        scale_x=2.0;         // �������̔{��
  double        scale_y=0.5;         // �c�����̔{��
  unsigned char **Image;             // input image
  unsigned char **after;             // output image
  char          filename[100];       // filename
  char          buff[128];
  FILE          *fp;                 // file pointer
  
  /* read binary image */
  sprintf(filename,"../test_image/sample.pgm");
  
  if(( fp=fopen(filename, "rb" ))==NULL){
    fprintf(stderr,"%s can't open! \n",filename);
    exit(-1);
  }
  
  /* �������̊m�� */
  Image = (unsigned char**)calloc(ysize+1,sizeof(unsigned char*));
  after = (unsigned char**)calloc(ysize+1,sizeof(unsigned char*));
  if( Image == NULL || after == NULL){
    puts("Memory allocate error!!");
    exit(1);
  }
  for(i=0;i<=ysize;i++){
    Image[i] = (unsigned char*)calloc(xsize+1,sizeof(unsigned char));
    after[i] = (unsigned char*)calloc(xsize+1,sizeof(unsigned char));
    if( Image[i] == NULL || after[i] == NULL){
      puts("Memory allocate error!!");
      exit(1);
    }
  }
 
 	fgets(buff,128,fp);                        //�� �t�@�C���̎��ʕ�����ǂݍ���
  fgets(buff,128,fp);                        //�� �摜�T�C�Y�̓ǂݍ���
  fgets(buff,128,fp);
  
  for(j=0;j<ysize;j++)
  	fread(Image[j],sizeof(unsigned char),xsize,fp);
  
  fclose(fp);
  
  /* image processing */
  //NN_affine(Image,after,xsize,ysize,theta,scale_x,scale_y);
  //Linear_affine(Image,after,xsize,ysize,theta,scale_x,scale_y);
  Spline_affine(Image,after,xsize,ysize,theta,scale_x,scale_y);
  /* write binary image */
  
  sprintf(filename,"output.pgm");
  
  if(( fp=fopen(filename, "wb" ))==NULL){
    fprintf(stderr,"%s can't open\n",filename);
    exit(-1);
  }
  
  fprintf(fp,"P5\n");                        //�� �t�@�C���̎��ʕ�������������
  fprintf(fp,"%d %d\n",ysize,xsize);         //�� �摜�T�C�Y����������
  fprintf(fp,"255\n");                       //�� �ő�P�x�l����������

  for(j=0;j<ysize;j++)
    fwrite(after[j],sizeof(unsigned char),xsize,fp);
  fclose(fp);
  
  
  /* �̈�̊J�� */
  for(i=0;i<=ysize;i++){
    free(Image[i]);
    free(after[i]);
  }

  free(Image);
  free(after);
  
}/*end_main*/
