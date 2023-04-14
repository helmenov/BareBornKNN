/*======================================================*/
/*             rotation.h interpolation by C            */
/*              Programed by Seiji Hotta                */
/*        Last revised by S.Hotta on Apr 18, 2002.      */
/*======================================================*/
#define PI 3.14159265

/*===================================*/
/* void NN_affine()：  最近傍法       */
/*===================================*/
void NN_affine(
	unsigned char **i_image, // input image
	unsigned char **o_image, // output image
	int xsize,				 // x size of image
	int ysize,				 // y size of image
	double theta,			 // angle
	double scale_x,			 // scale_x
	double scale_y)			 // scale_y
{

	int i, j;
	int ys, xs;
	int v, u;
	double m, n;
	double yy, xx;

	ys = ysize / 2;
	xs = xsize / 2;

	for (i = -ys; i < ys; i++)
	{
		for (j = -xs; j < xs; j++)
		{
			v = i;
			u = j;

			yy = (u * sin(theta * (PI / 180.0)) + v * cos(theta * (PI / 180.0))) / scale_y;
			xx = (u * cos(theta * (PI / 180.0)) - v * sin(theta * (PI / 180.0))) / scale_x;

			if (i > 0)
				m = yy + 0.5;
			else
				m = yy - 0.5; /* 最近傍法 */
			if (j > 0)
				n = xx + 0.5;
			else
				n = xx - 0.5;

			if ((m >= -ys) && (m < ys) && (n >= -xs) && (n < xs))
				o_image[i + (int)ys][j + (int)xs] = i_image[(int)(m + ys)][(int)(n + xs)];
			else
				o_image[i + (int)ys][j + (int)xs] = 0;
		}
	}
} // end_of_NN_affin

/*===================================*/
/* void Linear_affine()：線形補間法 */
/*===================================*/
void Linear_affine(
	unsigned char **i_image, // input image
	unsigned char **o_image, // output image
	int xsize,				 // x size of image
	int ysize,				 // y size of image
	double theta,			 // angle
	double scale_x,
	double scale_y) // scale
{

	int i, j;
	int ys, xs;
	int v, u;
	double m, n, p, q;
	double d;
	double yy, xx;

	ys = ysize / 2;
	xs = xsize / 2;

	for (i = -ys; i < ys; i++)
	{
		for (j = -xs; j < xs; j++)
		{
			v = i;
			u = j;

			yy = (u * sin(theta * (PI / 180.0)) + v * cos(theta * (PI / 180.0))) / scale_y;
			xx = (u * cos(theta * (PI / 180.0)) - v * sin(theta * (PI / 180.0))) / scale_x;

			if (yy > 0.0)
				m = yy;
			else
				m = yy - 1;
			if (xx > 0.0)
				n = xx;
			else
				n = xx - 1;

			q = yy - m;
			p = xx - n;

			if ((m >= -ys) && (m < ys) && (n >= -xs) && (n < xs))
			{
				d = (1.0 - q) * ((1.0 - p) * i_image[(int)m + ys][(int)n + xs] + p * i_image[(int)m + ys][(int)n + 1 + xs]) + q * ((1.0 - p) * i_image[(int)m + 1 + ys][(int)n + xs] + p * i_image[(int)m + 1 + ys][(int)n + 1 + xs]);
			}
			else
				d = 0.0;

			if (d < 0.0)
				d = 0.0;
			if (d > 255.0)
				d = 255.0;

			o_image[i + (int)ys][j + (int)xs] = (unsigned char)d;
		}
	}

} // end_of_Linear_affine

/*========================================*/
/* void Spline_affine()：スプライン補間法 */
/*========================================*/
void Spline_affine(
	unsigned char **i_image, // input image
	unsigned char **o_image, // output image
	int xsize,				 // x size of image
	int ysize,				 // y size of image
	double theta,			 // angle
	double scale_x,
	double scale_y) // scale
{

	int i, j;
	int ys, xs;
	int v, u;
	double m, n, p, q;
	double d;
	double yy, xx;
	double c1, c2, c3, c4, c5, c6, c7, c8;

	ys = ysize / 2;
	xs = xsize / 2;

	for (i = -ys; i < ys; i++)
	{
		for (j = -xs; j < xs; j++)
		{
			v = i;
			u = j;
			yy = (u * sin(theta * (PI / 180.0)) + v * cos(theta * (PI / 180.0))) / scale_y;
			xx = (u * cos(theta * (PI / 180.0)) - v * sin(theta * (PI / 180.0))) / scale_x;

			if (yy > 0)
				m = yy;
			else
				m = yy - 1;
			if (xx > 0)
				n = xx;
			else
				n = xx - 1;

			if ((m >= -ys) && (m < ys) && (n >= -xs) && (n < xs))
			{

				c1 = (m - 1) - yy;
				c2 = m - yy;
				c3 = (m + 1) - yy;
				c4 = (m + 2) - yy;
				c5 = (n - 1) - xx;
				c6 = n - xx;
				c7 = (n + 1) - xx;
				c8 = (n + 2) - xx;

				if (c1 < 0)
					c1 = -c1;
				if (0 <= c1 && c1 < 1)
					c1 = 1 - 2 * c1 * c1 + c1 * c1 * c1;
				else if (1 <= c1 && c1 < 2)
					c1 = 4 - 8 * c1 + 5 * c1 * c1 - c1 * c1 * c1;
				else if (2 <= c1)
					c1 = 0;

				if (c2 < 0)
					c2 = -c2;
				if (0 <= c2 && c2 < 1)
					c2 = 1 - 2 * c2 * c2 + c2 * c2 * c2;
				else if (1 <= c2 && c2 < 2)
					c2 = 4 - 8 * c2 + 5 * c2 * c2 - c2 * c2 * c2;
				else if (2 <= c2)
					c2 = 0;

				if (c3 < 0)
					c3 = -c3;
				if (0 <= c3 && c3 < 1)
					c3 = 1 - 2 * c3 * c3 + c3 * c3 * c3;
				else if (1 <= c3 && c3 < 2)
					c3 = 4 - 8 * c3 + 5 * c3 * c3 - c3 * c3 * c3;
				else if (2 <= c3)
					c3 = 0;

				if (c4 < 0)
					c4 = -c4;
				if (0 <= c4 && c4 < 1)
					c4 = 1 - 2 * c4 * c4 + c4 * c4 * c4;
				else if (1 <= c4 && c4 < 2)
					c4 = 4 - 8 * c4 + 5 * c4 * c4 - c4 * c4 * c4;
				else if (2 <= c4)
					c4 = 0;

				if (c5 < 0)
					c5 = -c5;
				if (0 <= c5 && c5 < 1)
					c5 = 1 - 2 * c5 * c5 + c5 * c5 * c5;
				else if (1 <= c5 && c5 < 2)
					c5 = 4 - 8 * c5 + 5 * c5 * c5 - c5 * c5 * c5;
				else if (2 <= c5)
					c5 = 0;

				if (c6 < 0)
					c6 = -c6;
				if (0 <= c6 && c6 < 1)
					c6 = 1 - 2 * c6 * c6 + c6 * c6 * c6;
				else if (1 <= c6 && c6 < 2)
					c6 = 4 - 8 * c6 + 5 * c6 * c6 - c6 * c6 * c6;
				else if (2 <= c6)
					c6 = 0;

				if (c7 < 0)
					c7 = -c7;
				if (0 <= c7 && c7 < 1)
					c7 = 1 - 2 * c7 * c7 + c7 * c7 * c7;
				else if (1 <= c7 && c7 < 2)
					c7 = 4 - 8 * c7 + 5 * c7 * c7 - c7 * c7 * c7;
				else if (2 <= c7)
					c7 = 0;

				if (c8 < 0)
					c8 = -c8;
				if (0 <= c8 && c8 < 1)
					c8 = 1 - 2 * c8 * c8 + c8 * c8 * c8;
				else if (1 <= c8 && c8 < 2)
					c8 = 4 - 8 * c8 + 5 * c8 * c8 - c8 * c8 * c8;
				else if (2 <= c8)
					c8 = 0;

				if ((int)m + ys + 2 < ysize && (int)n + xs + 2 < xsize && (int)m + ys + 1 < ysize && (int)n + xs + 1 < xsize &&
					(int)m + ys - 1 >= 0 && (int)n + xs - 1 >= 0)
				{

					d = i_image[(int)m + ys - 1][(int)n + xs - 1] * c1 * c5 + i_image[(int)m + ys - 1][(int)n + xs] * c1 * c6 +
						i_image[(int)m + ys - 1][(int)n + xs + 1] * c1 * c7 + i_image[(int)m + ys - 1][(int)n + xs + 2] * c1 * c8 +
						i_image[(int)m + ys][(int)n + xs - 1] * c2 * c5 + i_image[(int)m + ys][(int)n + xs] * c2 * c6 +
						i_image[(int)m + ys][(int)n + xs + 1] * c2 * c7 + i_image[(int)m + ys][(int)n + xs + 2] * c2 * c8 +
						i_image[(int)m + ys + 1][(int)n + xs - 1] * c3 * c5 + i_image[(int)m + ys + 1][(int)n + xs] * c3 * c6 +
						i_image[(int)m + ys + 1][(int)n + xs + 1] * c3 * c7 + i_image[(int)m + ys + 1][(int)n + xs + 2] * c3 * c8 +
						i_image[(int)m + ys + 2][(int)n + xs - 1] * c4 * c5 + i_image[(int)m + ys + 2][(int)n + xs] * c4 * c6 +
						i_image[(int)m + ys + 2][(int)n + xs + 1] * c4 * c7 + i_image[(int)m + ys + 2][(int)n + xs + 2] * c4 * c8;
				}
			}
			else
				d = 0.0;
			if (d < 0.0)
				d = 0.0;
			if (d > 255.0)
				d = 255.0;
			o_image[i + ys][j + xs] = (unsigned char)d;
		}
	}

} //end_of_Spline_affine
