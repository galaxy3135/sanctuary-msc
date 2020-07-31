#include "c_util.h"
#include <malloc.h>

int char_length_of(const char* chars) {
	int i = 0;
	while (*chars++ != END_OF_CHAR) {
		i++;
	}
	return i;
}

int read_text_file(const char* file, char* container) {
	int buf_s = _msize(container);
	int ct = 0;
	FILE* fp;
	fopen_s(&fp, file, "r");
	if (fp == NULL) {
		return 0;
	}
	char in = fgetc(fp);
	while (in != EOF) {
		if (ct == buf_s -1) {
			if (realloc(container, _msize(container) + buf_s) == NULL) {
				break;
			}
			ct = 0;
		}
		*container++ = in;
		in = fgetc(fp);
	}
	*container = '\0';
	fclose(fp);
	return 0;
}


char* read_text_file(const char* file)
{
	int bf_s = 1024;
	int ct = 0;
	char* result = (char*)malloc(1024 * sizeof(char));
	if (result == NULL) {
		return NULL;
	}
	FILE* fp;
	fopen_s(&fp, file, "r");
	if (fp == NULL) {
		return 0;
	}
	char in = fgetc(fp);
	while (in != EOF) {
		if (ct == bf_s - 1) {
			bf_s += bf_s;
			if (realloc(result, bf_s) == NULL) {
				break;
			}
		}
		*(result+ct++) = in;
		in = fgetc(fp);
	}
	*(result+ct) = '\0';
	fclose(fp);
	return result;
}
