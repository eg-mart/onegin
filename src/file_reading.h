#ifndef FILE_READING
#define FILE_READING

struct Buffer {
	size_t size;
	char *data;
};

struct Text {
	size_t num_lines;
	char **lines;
};

enum BufferError {
	NO_BUF_ERR = 0,
	ERR_BUF_MEM = -1,
	ERR_FILE_ACCESS = -2,
	ERR_FILE_READING = -3,
};

enum TextError {
	NO_TXT_ERR = 0,
	ERR_TXT_MEM = -1,
};

enum BufferError read_buffer(struct Buffer *buf, const char *filename);
void destroy_buffer(struct Buffer *buf);
size_t count_in_buffer(struct Buffer buf, char c);
void split_buffer(char **splits, struct Buffer *buf, char sep);

enum TextError text_ctor(struct Text *text, struct Buffer *buf);
void text_dtor(struct Text *text);

#endif
