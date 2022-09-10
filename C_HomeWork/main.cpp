#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#define DIGIT	4

int generate_random();
void input_array(int* array, int num);

int main()
{
	srand((unsigned int)time(NULL));

	int random = generate_random();
	int answer = 0;
	int answer_array[DIGIT] = {};
	int random_array[DIGIT] = {};
	int Hit = 0;
	int Blow = 0;
	int play_num = 0;
	bool clear = false;

	FILE* fp = NULL;

	input_array(random_array, random);
	//printf("%d\n", random);

	while (!clear)
	{
		Hit = 0;
		Blow = 0;
		printf("4桁の整数を入力してください\n>");
		scanf_s("%d", &answer);

		input_array(answer_array, answer);

		for (int i = 0; i < DIGIT; i++)
		{
			if (answer_array[i] == random_array[i])
			{
				Hit++;
				continue;
			}
			for (int j = 0; j < DIGIT; j++)
			{
				if (i == j)
				{
					continue;
				}
				if (answer_array[i] == random_array[j])
				{
					Blow++;
					break;
				}
			}
		}

		printf("Hit：%d\n", Hit);
		printf("Blow：%d\n\n", Blow);
		play_num++;

		if (Hit == 4)
		{
			clear = true;
		}
	}

	printf("Game Clear!!\n");

	if (0 == fopen_s(&fp, "SaveDate/SaveDate.txt", "a"))
	{
		fprintf(fp, "%d\n", play_num);
		fclose(fp);
	}
	else
	{
		if (0 == fopen_s(&fp, "SaveDate/SaveDate.txt", "w"))
		{
			fprintf(fp, "%d\n", play_num);
			fclose(fp);
		}
		else
		{
			printf("ファイルを開けませんでした");
		}
	}
}

int generate_random()
{
	int randomAll = 0;
	int randomNums[DIGIT] = {};
	for (int i = 0; i < DIGIT; i++)
	{
		int randomNum = rand() % 10;
		randomNums[i] = randomNum;
		for (int j = 0; j < i ; j++)
		{
			if (randomNums[j] == randomNum)
			{
				i--;
				break;
			}
		}
		randomAll += randomNum * (int)pow(10, i);
	}

	return randomAll;
}

void input_array(int* array, int num)
{
	for (int i = 0; i < DIGIT; i++)
	{
		array[i] = (num % (int)pow(10, i + 1) - num % (int)pow(10, i)) / pow(10, i);
	}
}