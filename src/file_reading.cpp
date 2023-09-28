#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "file_reading.h"

enum BufferError get_file_size(FILE *file, size_t *size);

enum BufferError read_buffer(struct Buffer *buf, const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL) return ERR_FILE_ACCESS;

	size_t filesize = 0;
	enum BufferError err = get_file_size(file, &filesize);
	if (err < 0) return err;
	buf->size = filesize + 2;

	buf->data = (char *) calloc(buf->size, sizeof(char));
	if (buf->data == NULL) return ERR_BUF_MEM;

	size_t read_chars = fread(buf->data + 1, sizeof(char), buf->size - 2, file);
	if (read_chars != buf->size - 2 || ferror(file)) return ERR_FILE_READING;
	buf->data[0] = '\0';
	buf->data[buf->size - 1] = '\0';

	fclose(file);

	return NO_BUF_ERR;
}

enum BufferError get_file_size(FILE *file, size_t *size)
{
	int fd = fileno(file);
	struct stat stbuf;
	if (fstat(fd, &stbuf) == -1) return ERR_FILE_ACCESS;
	*size = (size_t) stbuf.st_size;
	return NO_BUF_ERR;
}

size_t count_in_buffer(struct Buffer buf, char c)
{
	size_t num_chars = 0;
	char *iter_buf = buf.data + 1;
	while (*iter_buf != '\0') {
		if (*iter_buf++ == c)
			num_chars++; 
	}
	return num_chars;
}

void split_buffer(char **splits, struct Buffer *buf, char sep)
{
	char *iter_buf = buf->data + 1;
	*splits = iter_buf;
	size_t cnt = 0;

	while (*iter_buf != '\0') {
		if (*iter_buf == sep) {
			fprintf(stderr, "reading %lu line\n", ++cnt);
			*iter_buf = '\0';
			*++splits = iter_buf + 1;
		}
		iter_buf++;
	}

	*++splits = iter_buf + 1;
	fputs("im not stuck dont worry!\n", stderr);
}

void destroy_buffer(struct Buffer *buf)
{
	free(buf->data);
	buf->data = NULL;
	buf->size = 0;
}

enum TextError text_ctor(struct Text *text, struct Buffer *buf)
{
	text->num_lines = count_in_buffer(*buf, '\n') + 1;
	fprintf(stderr, "there are %lu lines in text\n", text->num_lines);
	
	text->lines = (char**) calloc(text->num_lines + 1, sizeof(char*));
	if (text->lines == NULL) return ERR_TXT_MEM;

	split_buffer(text->lines, buf, '\n');

	return NO_TXT_ERR;
}

void text_dtor(struct Text *text)
{
	free(text->lines);
	text->lines = NULL;
	text->num_lines = 0;
}
