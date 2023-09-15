#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "file_reading.h"

size_t count_sep_in_str(const char *str, char c);

enum TextError read_text(struct Text *text, const char *filename)
{
	struct stat stbuf;

	if (stat(filename, &stbuf) == -1) return ERR_FILE_ACCESS;
	text->buffer_size = (size_t) stbuf.st_size + 1;

	FILE *file = fopen(filename, "r");
	if (file == NULL) return ERR_FILE_ACCESS;

	text->buffer = (char *) calloc(text->buffer_size, sizeof(char));
	if (text->buffer == NULL) return ERR_MEM;

	size_t read_chars = fread(text->buffer, sizeof(char), text->buffer_size - 1, file);
	if (read_chars != text->buffer_size - 1 || ferror(file)) return ERR_FILE_READING;
	text->buffer[text->buffer_size - 1] = '\0';

	text->num_lines = count_sep_in_str(text->buffer, '\n');
	
	text->lines = (struct Line *) calloc(text->num_lines + 1, sizeof(struct Line));
	if (text->lines == NULL) return ERR_MEM;

	*text->lines = { 0, text->buffer};
	char *iter_data = text->buffer;
	struct Line *iter_lines = text->lines;
	size_t cur_line_len = 0;
	
	while (*iter_data != '\0') {
		cur_line_len++;
		if (*iter_data == '\n') {
			if (iter_lines->len == 0)
				iter_lines->len = cur_line_len;
			*iter_data = '\0';
			if (*(iter_data + 1) != '\n') {
				cur_line_len = 0;
				*++iter_lines = { 0, iter_data + 1};
			}
		}
		iter_data++;
	}

	fclose(file);

	return NO_TXT_ERR;
}

size_t count_sep_in_str(const char *str, char c)
{
	size_t num_chars = 0;
	while (*str != '\0')
		if (*str++ == c)
			if (*str != '\n')
				num_chars++; 
	return num_chars;
}

void destroy_text(struct Text *text)
{
	free(text->lines);
	free(text->buffer);

	text->lines = NULL;
	text->buffer = NULL;

	text->num_lines = 0;
	text->buffer_size = 0;
}
