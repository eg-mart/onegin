#include <stdio.h>

int compare_str(const char *str1, const char *str2);

int compare_str(const char *str1, const char *str2)
{
	while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int main()
{
	const char *filename = "onegin.txt";

	struct stat stbuf;

	if (stat(filename, &stbuf) == -1) {
		fprintf(stderr, "error accesing %s\n", filename);
		return 1;
	}

	FILE *file = fopen(filename, "r");
	if (file == NULL) return 1;

	char *filedata = (char *) calloc((size_t) stbuf.st_size + 1, sizeof(char));
	if (filedata == NULL) return 1;

	size_t read_chars = fread(filedata, sizeof(char), (size_t) stbuf.st_size, file);
	if (read_chars != (size_t) stbuf.st_size || ferror(file)) {
		printf("error: file couldn't be fully read\n");
		return 1;
	}
	filedata[stbuf.st_size] = '\0';

	size_t num_lines = 0;
	char *iter = filedata;
	while (*iter != '\0')
		if (*iter++ == '\n')
			num_lines++; 
	
	char **lines = (char **) calloc(num_lines + 1, sizeof(char *));
	if (lines == NULL) return 1;

	*lines = filedata;
	char *iter_data = filedata;
	char **iter_lines = lines;
	while (*iter_data != '\0') {
		if (*iter_data == '\n') {
			*iter_data = '\0';
			if (*(iter_data + 1) != '\n')
				*++iter_lines = iter_data + 1;
		}
		iter_data++;
	}

	printf("first and third lines: \n%s\n%s\n", lines[0], lines[1]);

	free(lines);
	free(filedata);
}
