#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

//#define FAST
#ifdef FAST
typedef float mat_t;
#else
typedef double mat_t;
#endif // FAST


#define FREE_ARRAY(data) do{if((data)!=NULL) {free(data); (data)=NULL;}}while(0)

void show(mat_t* src, int rows, int cols) 
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
#ifdef FAST
			printf("%0.4f ", src[i*cols + j]);
#else
			printf("%0.4lf ", src[i*cols + j]);
#endif
		}
		printf("\n");
	}
}
template<typename _tp> void swap(_tp &a, _tp &b)
{
	_tp t = a;
	a = b;
	b = t;
}
void Trapezoidal(mat_t *src, int rows, int cols, bool normalization = true)
{
	int height = rows;
	int width = cols;
	int *ZeroNum = (int*)malloc(2 * height * sizeof(int));
	mat_t *t = (mat_t*)malloc(rows*cols * sizeof(mat_t));
	for (int count = 0; count < height; count++) {
		for (int i = 0; i < height; i++) {
			int count_ = 0;
			for (int j = 0; j < width; j++) {
				if (src[i*width + j] == 0)
					count_++;
				else break;
			}
			ZeroNum[i * 2] = i;
			ZeroNum[i * 2 + 1] = count_;
		}
		for (int i = 0; i < height - 1; i++) {
			for (int j = i + 1; j < height; j++) {
				if (ZeroNum[i * 2 + 1] > ZeroNum[j * 2 + 1]) {
					swap(ZeroNum[i * 2], ZeroNum[j * 2]);
					swap(ZeroNum[i * 2 + 1], ZeroNum[j * 2 + 1]);
				}
			}
		}
		memset(t, 0, rows*cols * sizeof(mat_t));
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				t[j + i * width] = src[j + ZeroNum[i * 2] * width];
			}
		}
		memcpy(src, t, rows*cols * sizeof(mat_t));
		if ((width - ZeroNum[count * 2 + 1]) != (width - count))
			continue;
		if (normalization && src[count + count * width] != 1) {
			mat_t m = 1 / src[count + count * width];
			for (int i = 0; i < width; i++) {
				if (src[i + count * width] == 0)continue;
				src[i + count * width] *= m;
			}
		}
		for (int i = count + 1; i < height; i++) {
			if ((width - ZeroNum[i * 2 + 1]) != (width - count))continue;
			mat_t m = src[count + i * width] / src[count + count * width];
			for (int j = ZeroNum[i * 2 + 1]; j < width; j++) {
				if (src[j + count * width] == 0)continue;
				src[j + i * width] -= m * src[j + count * width];
			}
		}
	}
	FREE_ARRAY(ZeroNum);
	FREE_ARRAY(t);
}

mat_t det(mat_t* src, int rows, int cols)
{
	int n = rows;
	if (n == 1)
		return src[0];
	else {
		mat_t* mat = (mat_t*)malloc(rows*cols * sizeof(mat_t));
		memcpy(mat, src, rows*cols * sizeof(mat_t));
		Trapezoidal(mat, rows, cols, false);
		mat_t answer = 1;
		for (int i = 0; i < n; i++) {
			answer *= mat[i*cols + i];
			if (isinf(answer))break;
		}
		FREE_ARRAY(mat);
		return answer;
	}
}

int Rank(mat_t* src, int h_, int w_)
{
	int rank = h_;
	for (int i = 0; i < h_; i++) {
		int count = 0;
		for (int j = 0; j < w_; j++) {
			if (src[j + i * w_] == 0) {
				count++;
			}
		}
		if (count == h_)
			rank--;
	}
	return rank;
}

void RowSimplest(mat_t* src, int rows, int cols, int *rank = NULL)
{
	Trapezoidal(src, rows, cols);
	int height = rows;
	int width = cols;
	for (int i = 1; i < height; i++) {
		bool flag = false;
		int j;
		for (j = 0; j < width; j++) {
			if (src[i*width + j] != 0) {
				flag = true;
				break;
			}
		}
		if (!flag)continue;
		for (int k = i - 1; k >= 0; k--) {
			mat_t m = src[j + k * width] / src[j + i * width];
			for (int l = j; l < width; l++) {
				src[l + k * width] -= m * src[l + i * width];
			}
		}
	}
	if (rank) {
		*rank = Rank(src, rows, cols);
	}
}

void inv(mat_t* src, int rows, int cols)
{
	mat_t determinant = det(src, rows, cols);
	if (isnan(determinant) || determinant == 0) {
		return;
	}
	else {
		int new_cols = cols * 2;
		int idx = cols;
		mat_t *mat = (mat_t*)malloc(rows*new_cols * sizeof(mat_t));
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				mat[i * new_cols + j] = src[i * cols + j];
			}
			for (int j = cols; j < new_cols; j++) {
				mat[i * new_cols + j] = 0;
			}
			mat[i * new_cols + idx++] = 1;
		}
		RowSimplest(mat, rows, new_cols);
		idx = cols;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				src[i * cols + j] = mat[i * new_cols + idx + j];
			}
		}
		FREE_ARRAY(mat);
	}
}

int main()
{
	int rows = 3, cols = 3;
	srand((unsigned int)time(0));
	mat_t mat[9];
	for (int i = 0; i < 9; i++)
		mat[i] = mat_t(rand() % 10 + 1);
	show(mat, rows, cols);
	printf("\n");
	inv(mat, rows, cols);
	show(mat, rows, cols);
	return 0;
}
