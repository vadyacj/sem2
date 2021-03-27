#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include<io.h>
#pragma warning(disable : 4996)
void menu(FILE* f, char* name);
void search(FILE* f, char* name);
void output(FILE* f, char* name);
void rewrite(FILE* f, char* name);
int main() {
	char name[20];
	int i = 0, i1 = 0;
	char type[5] = ".txt";
	FILE* f;
	printf("Input name of file: ");
	gets_s(name, 20);
	while (name[i]) {
		i++;
	}
	while (type[i1]) {
		name[i] = type[i1];
		i++;
		i1++;
	}
	name[i] = '\0';
	if (!(f = fopen(name, "w+"))) {
		printf("Error\n");
		return 0;
	}
	char text[100];
	do {
		i = 0;
		int error = 0;
		printf("Input words: ");
		gets_s(text, 100);
		while (text[i]) {
			if (text[i] >= '0' && text[i] <= '9') {
				printf("Error\n");
				error = 1;
				break;
			}
			i++;
		}
		if (error == 0) {
			break;
		}
	} while (1);
	fprintf(f, "%s", text);
	rewind(f);
	if (!(f = fopen(name, "a+"))) {
		printf("Error\n");
		return 0;
	}
	menu(f, name);
	fclose(f);
	return 0;

}
void menu(FILE* f, char* name) {

	int ch;
	puts("\nType:\n 1-Output\n 2-Search\n 3-Rewrite tabs");
	scanf_s("%d", &ch);
	switch (ch)
	{
		case 1: output(f, name); break;
		case 2: search(f, name); break;
		case 3: rewrite(f, name); break;
	}
}
void output(FILE* f, char* name) {
	system("cls");
	rewind(f);
	char s;
	printf("File %s\n", name);
	while (!feof(f)) {
		fscanf(f, "%c", &s);
		if (feof(f)) {
			break;
		}
		printf("%c", s);
	}
	printf("\n\n");
	menu(f, name);
}
void search(FILE* f, char* name)
{
	system("cls");
	int b = 0;
	char s;
	system("cls");
	rewind(f);
	puts("Enter letter what U search\n");
	char sym;
	sym = getche();

	while (!feof(f)) {
		fscanf(f, "%c", &s);
		if (sym == s) {
			b++;
		}
	}
	printf("%4d", b);
	menu(f, name);
}
void rewrite(FILE* f, char* name) 
{
	fclose(f);
	if (!(f = fopen(name, "r+"))) {
		printf("Error\n");
		return 0;
	}
	
	system("cls");
	puts("Choose the symbol: ");
	int i = 0;
	char s, a;
	char sym;
	sym = getche();
	while (!feof(f)) {
		fscanf(f, "%c", &s);
		i++;
		fseek(f, i * sizeof(a), SEEK_SET);
		fread(&a, sizeof(a), 1, f);
		if (a == ' ') {
			a = sym;
			fseek(f, i * sizeof(a), SEEK_SET);
			fwrite(&a, sizeof(a), 1, f);
		}
	}
	rewind(f);
	char c;
	printf("\nFile %s\n", name);
	while (!feof(f)) {
		fscanf(f, "%c", &c);
		if (feof(f)) {
			break;
		}
		printf("%c", c);
	}
	menu(f, name);
}