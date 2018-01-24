/* 
  Name: Create Images like mnist dataset
  Deswcription: this function create pictures like mnist datasets
  copyright:UESTC quantitative medical lab
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>
#pragma comment(lib, "wsock32.lib")

 void OutPut_Format_unit32(uint32_t num, FILE *P);
 const int LEN = 28;
 const int WIDTH = 28;
 float x_target = 7.0;
 float y_target = 7.0;
 float r_target = 3.0;
 const int  MAGIC_NUMBER_IMGS = 2051;
 const int  MAGIC_NUMBER_LABELS = 2049;
const int TRAIN_NUM = 60000;
const int TEST_NUM = 10000;
int main()
{
	srand(time(NULL));
	FILE *fp_train_data = NULL; FILE*fp_train_label = NULL;
	FILE *fp_test_data = NULL; FILE*fp_test_label = NULL;
	fp_train_data = fopen("train-images.idx3-ubyte","wb");  //training Data
	fp_train_label = fopen("train-labels.idx1-ubyte", "wb");  //train Label
	fp_test_data = fopen("t10k-images.idx3-ubyte", "wb");  //Test Data
	fp_test_label = fopen("t10k-labels.idx1-ubyte", "wb");  //Test Lebel
	if (fp_train_data == NULL || fp_train_label == NULL || fp_test_data == NULL || fp_test_label == NULL)
	{
		printf("File open Error!\n");
		exit(1);
	}
	int *pixel = (int*)calloc(TRAIN_NUM*LEN*WIDTH, sizeof(int));
	int *train_label = (int*)calloc(TRAIN_NUM, sizeof(int));

	// 制造训练数据 S
#if 1
	//写入标签文件头
	OutPut_Format_unit32(MAGIC_NUMBER_LABELS, fp_train_label);
	OutPut_Format_unit32(TRAIN_NUM, fp_train_label);
	//写入数据文件头
	OutPut_Format_unit32(MAGIC_NUMBER_IMGS, fp_train_data);
	OutPut_Format_unit32(TRAIN_NUM, fp_train_data);
	OutPut_Format_unit32(LEN, fp_train_data);
	OutPut_Format_unit32(WIDTH, fp_train_data);

	for (int i = 0; i < TRAIN_NUM; i++)
	{
		int K = (int)rand() * 10 / RAND_MAX;  
		if (K == 10)  K -= 1;   //标签 0-9
		train_label[i] = K;
		fwrite(&train_label[i], sizeof(uint8_t), 1, fp_train_label);

		x_target = ((float)rand() * (LEN - r_target) + r_target) / RAND_MAX; // r_target --  LEN-r_target   
		y_target = ((float)rand() * (WIDTH - r_target) + r_target) / RAND_MAX; // r_target -- WIDTH-r_target  
		for (int y = 0; y < WIDTH; y++)
		{
			for (int x = 0; x < LEN; x++)
			{
				if (sqrt(pow((y - y_target), 2) + pow((x - x_target), 2)) <= r_target)
				{
					pixel[y*LEN + x] =  140+K*10; // 20-29
				}
				else
				{
					pixel[y*LEN + x] = 0;
				}
				
			  fwrite(&pixel[y*LEN + x],sizeof(uint8_t),1,fp_train_data);
			}
		}
	}
	fclose(fp_train_data);
	fclose(fp_train_label);

#endif

	//  制造测试数据
#if 1 
	//写入标签文件头
	OutPut_Format_unit32(MAGIC_NUMBER_LABELS, fp_test_label);
	OutPut_Format_unit32(TEST_NUM, fp_test_label);
	//写入数据文件头
	OutPut_Format_unit32(MAGIC_NUMBER_IMGS, fp_test_data);
	OutPut_Format_unit32(TEST_NUM, fp_test_data);
	OutPut_Format_unit32(LEN, fp_test_data);
	OutPut_Format_unit32(WIDTH, fp_test_data);

	for (int i = 0; i < TEST_NUM; i++)
	{
		int K = (int)rand() * 10 / RAND_MAX;
		if (K == 10)  K -= 1;   //标签 0-9
		train_label[i] = K;
		fwrite(&train_label[i], sizeof(uint8_t), 1, fp_test_label);
		x_target = ((float)rand() * (LEN - r_target) + r_target) / RAND_MAX; // r_target --  LEN-r_target   
		y_target = ((float)rand() * (WIDTH - r_target) + r_target) / RAND_MAX; // r_target -- WIDTH-r_target 
		for (int y = 0; y < WIDTH; y++)
		{
			for (int x = 0; x < LEN; x++)
			{
  
				if (sqrt(pow((y - y_target), 2) + pow((x - x_target), 2)) <= r_target)
				{
					pixel[y*LEN + x] = 140 + K*10; // 20-29
				}
				else
				{
					pixel[y*LEN + x] = 0;
				}

				fwrite(&pixel[y*LEN + x], sizeof(uint8_t), 1, fp_test_data);
			}
		}
	}
	fclose(fp_test_data);
	fclose(fp_test_label);
#endif

	puts("Success...\n");
}


void OutPut_Format_unit32(uint32_t num,FILE *P)
{

	uint32_t m = htonl(num);
	fwrite(&m, sizeof(uint32_t), 1, P);

}

