/* Exercise 5-13. Write the program tail, which prints the last n lines of its input. By default, n
is set to 10, let us say, but it can be changed by an optional argument so that
"tail -n" prints the last n lines. The program should behave rationally no matter how unreasonable the
input or the value of n. Write the program so it makes the best use of available storage; lines
should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
fixed size. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define PROGRAM_NAME "tail"
#define DEFAULT_TAIL_LINES 10
#define MAX_LINE_LEN 1000
#define ERR_USAGE -1
#define ERR_MEM -2

static long tail_lc = DEFAULT_TAIL_LINES;

void parse_args(int *argc, char *argv[]);
void usage(void);
void write_lines(char *lines[], unsigned long entries_count);
int get_line(char *s, int lim);
unsigned int tail_alloc(char *lines[], unsigned int lim);

bool queue_init(long max_size);
bool queue_enqueue(char *value);
char *queue_dequeue(void);
void queue_destroy(void);

int main(int argc, char *argv[])
{
	char **lines;
	unsigned long entries_count;

	parse_args(&argc, argv);
	if (argc == -2) {
		return 0;
	} else if (argc != 0) {
		usage();
		return ERR_USAGE;
	}

	if (tail_lc == LONG_MAX || tail_lc == LONG_MIN || (lines = malloc(sizeof(char *) * tail_lc)) == NULL) {
		printf(PROGRAM_NAME": Value too large for defined data type\n");
		return ERR_MEM;
	}

	if ((entries_count = tail_alloc(lines, tail_lc)))
		write_lines(lines, entries_count);

	free(lines);
	return 0;
}
void parse_args(int *argc, char *argv[])
{
	char *s_end, c;
	while (--*argc > 0) {
		if (strcmp(*argv, "-h") == 0 || strcmp(*argv, "--help") == 0) {
			usage();
			*argc = -2;
			return;
		} else if (strcmp(*argv, "-n") == 0 || strcmp(*argv, "--lines")) {
			if (--*argc > 0) {
				if ((tail_lc = strtol(*++argv, &s_end, 10)) < 0)
					tail_lc *= -1;
				if (*s_end != '\0')
					*argc = -1;
			}
		} else {
			printf(PROGRAM_NAME": illegal option '%c'\n", c);
			*argc = -1;
			return;
		}
	}
}
void write_lines(char *lines[], unsigned long entries_count)
{
	for (int i = 0; i < entries_count; ++i)
		printf("%s", lines[i]);
}

void usage(void)
{
	printf("usage: " PROGRAM_NAME " [OPTION]...\n"
	       "Print the last 10 lines of STDIN to STDOUT.\n"
	       "  -n	output the last NUM lines, instead of the last %d;\n", DEFAULT_TAIL_LINES);
}

unsigned int tail_alloc(char *lines[], unsigned int lim)
{
	char buf[MAX_LINE_LEN], *p, **lines_start;
	int char_count;

	if (!queue_init(lim))
		return 0;

	while ((char_count = get_line(buf, MAX_LINE_LEN)) > 0
	    && (p = malloc(sizeof(char) * (char_count + 1))) != NULL) {
		strcpy(p, buf);
		if (!queue_enqueue(p)) {
			free(queue_dequeue());
			queue_enqueue(p);
		}
	}

	lines_start = lines;
	while ((p = queue_dequeue()) != NULL)
		*lines++ = p;

	queue_destroy();
	return lines - lines_start;
}

int get_line(char *s, int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';
	return i;
}

static char **values;
static unsigned int head, tail, entries_count, size;

static bool queue_empty(void);
static bool queue_full(void);

bool queue_init(long max_size)
{
	if (max_size <= 0)
		return false;

	size = max_size;
	entries_count = 0;
	head = 0;
	tail = 0;
	values = malloc(sizeof(char *) * size);
	return (values != NULL);
}

bool queue_empty(void)
{
	return (entries_count == 0);
}

bool queue_full(void)
{
	return (entries_count == size);
}

void queue_destroy(void)
{
	free(values);
}

bool queue_enqueue(char *value)
{
	if (queue_full())
		return false;

	values[tail] = value;
	tail = (tail + 1) % size;
	++entries_count;
	return true;
}

char *queue_dequeue(void)
{
	char *result;

	if (queue_empty())
		return NULL;

	result = values[head];
	head = (head + 1) % size;
	--entries_count;
	return result;
}