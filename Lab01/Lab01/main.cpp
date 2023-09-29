#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

const int word_lenght = 30;


struct WordsWithCounter
{
	char word[word_lenght + 1];//For symbol '\0'
	int count;
	struct WordsWithCounter *next;
};

struct WordsWithCounter *check_words(struct WordsWithCounter *main, const char *word)
{
	if (main == NULL)
	{
		struct WordsWithCounter *elem = (WordsWithCounter*)malloc(sizeof(struct WordsWithCounter));
		if (elem != NULL)
		{
			elem->count = 1;
			strncpy(elem->word, word, word_lenght);
			elem->word[word_lenght] = '\0';
			elem->next = NULL;
		}
		return elem;
	}
	struct WordsWithCounter *curr = main;
	struct WordsWithCounter *last = NULL;
	while (curr != NULL)
	{
		if (strncmp(curr->word, word, word_lenght) == 0)
		{

			curr->count++;
			return main;
		}
		last = curr;
		curr = curr->next;
	}
	struct WordsWithCounter *new_elem = (WordsWithCounter*)malloc(sizeof(struct WordsWithCounter));
	if (new_elem != NULL)
	{
		new_elem->count = 1;
		strncpy(new_elem->word, word, word_lenght);
		new_elem->word[word_lenght] = '\0';
		new_elem->next = NULL;
	}
	if (new_elem != NULL)
	{
		last->next = new_elem;
	}
	return main;
}


void show(struct WordsWithCounter *main, int count)
{
	struct WordsWithCounter *curr = main;
	while (curr != NULL)
	{
		if (curr->count == count)
		{
			printf("%s\n", curr->word);
		}
		curr = curr->next;
	}
}


int read_file(const char *input_file)
{
	FILE *input = fopen(input_file, "r");
	if (input == NULL)
	{
		printf("File read error\n", input_file);
		return -1;
	}
	int max_number = 0;
	struct WordsWithCounter *list = NULL;
	char word_buf[word_lenght + 1] = "";
	int buf_p = 0;
	int c = char("");
	while (c != EOF)
	{
		c = fgetc(input);

		if (!isalpha(c) && c != '-')
		{

			if (buf_p > 0)
			{
				word_buf[buf_p] = '\0';
				list = check_words(list, word_buf);
				buf_p = 0;
			}
		}
		else
		{
			if (buf_p < word_lenght)
			{

				word_buf[buf_p++] = tolower(c);
			}
			else
			{

				while (isalpha(c) || c == '-')
				{
					c = fgetc(input);
				}
				buf_p = 0;
			}
		}
	}

	fclose(input);

	struct WordsWithCounter *current = list;

	//Find max wordcount
	while (current != NULL)
	{
		max_number = (current->count > max_number) ? current->count : max_number;
		current = current->next;
	}

	printf("\nWords with the bigest count %d:\n", max_number);
	show(list, max_number);

	//Clean list
	while (list != NULL)
	{
		struct WordsWithCounter *temp = list;
		list = list->next;
		free(temp);
	}

	return 0;
}

int main()
{
	const char *input_file = "d:/work/test.txt";
	if (read_file(input_file) == -1)
	{
		printf("Error");
		return -1;
	}

	return 0;
}
