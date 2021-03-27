#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<io.h>
#pragma warning(disable : 4996)
void menu(FILE* f, char* name, int n);
void sum(FILE* f, char* name, int n);
void output(FILE* f, char* name, int n);
void rewrite(FILE* f, char* name, int n);
int main() {
	FILE* f;
	int n;
	int* mas;
	char name[20];
	printf("Input name of file\n");
	gets_s(name, 20);
	printf("Input amount of number\n");
	do {
		while (!scanf("%d", &n)) {
			rewind(stdin);
			printf("Input number bigger than 0\n");
		}
	} while (n < 0);
	mas = (int*)calloc(n, sizeof(int));
	printf("Input %d numbers\n", n);
	for (int i = 0; i < n; i++) {
		while (!scanf("%d", &mas[i])) {
			rewind(stdin);
			printf("input correct number\n");
		}
	}

	rewind(stdin);
	if (!(f = fopen(name, "w+b"))) {
		printf("Error");
		return 0;

	}
	fwrite(mas, sizeof(int), n, f);
	menu(f, name, n);
	fclose(f);
	return 0;

}
void menu(FILE* f, char* name, int n) {

	int ch;
	puts("\nType:\n 1-Output\n 2-Search\n 3-Rewrite tabs");
	scanf_s("%d", &ch);
	switch (ch)
	{
	case 1: output(f, name, n); break;
	case 2: sum(f, name, n); break;
	case 3: rewrite(f, name, n); break;
	}
}
void output(FILE* f, char* name, int n) {
	system("cls");
	int j;
	rewind(f);
	while (2) {
		fread(&j, sizeof(int), 1, f);
		if (feof(f)) break;
		printf("%d", j);
	}
	printf("\n");
	menu(f, name, n);
}
void sum(FILE* f, char* name, int n)
{
	int i = 0, j;
	rewind(f);
	while (2) {
		fread(&j, sizeof(int), 1, f);
		if (feof(f)) break;
		if (j % 2 == 0) {
			i += j;
		}
	}
	printf("Sum of *** numbers = %d\n", i);

	menu(f, name, n);
}
void rewrite(FILE* f, char* name, int n)
{
	fclose(f);
	if (!(f = fopen(name, "r+b"))) {
		printf("Error\n");
		return 0;
	}
	int min = 0, j, trig = 0;
	fpos_t i1 = 0;
	rewind(f);
	while (!feof(f)) {
		fread(&j, sizeof(int), 1, f);
		if (feof(f)) break;
		if (j % 2 == 0) {
			min = j;
			trig = 1;
			break;
		}
	}
	rewind(f);
	while (!feof(f)) {
		fread(&j, sizeof(int), 1, f);
		if (feof(f)) break;
		if (j < min) {
			min = j;
		}
	}
	rewind(f);
	int i = 0, a = 0;
	for (i = 0; i < n; i++)
	{
		fseek(f, i * sizeof(a), SEEK_SET);
		fread(&a, sizeof(a), 1, f);
		if (a % 2 == 0) {
			a = min;
			fseek(f, i * sizeof(a), SEEK_SET);
			fwrite(&a, sizeof(a), 1, f);
		}
	}
	system("cls");
	rewind(f);
	while (!feof(f)) {
		fread(&j, sizeof(int), 1, f);
		if (feof(f)) break;
		printf("%d", j);
	}
	printf("\n");
	menu(f, name, n);
}