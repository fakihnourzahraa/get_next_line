# get_next_line

A C function that reads one line at a time from a file descriptor, retaining leftover data between calls using a static buffer.

---

## About

`get_next_line` returns the next line from a given file descriptor each time it is called. It works correctly regardless of buffer size, handles multiple successive calls on the same fd, and the bonus version supports reading from multiple file descriptors simultaneously.

---

## Function Signature

```c
char *get_next_line(int fd);
```

Returns the next line including the terminating `\n` (if present), or `NULL` on EOF or error. The caller is responsible for freeing the returned string.

---

## How It Works

Each call to `get_next_line` follows this flow:

1. **Read into buffer** — `read()` fills a fixed-size buffer of `BUFFER_SIZE` bytes at a time
2. **Accumulate** — chunks are joined onto a persistent `excess` string using `ft_strjoin`
3. **Stop early** — reading halts as soon as a `\n` is found in the buffer
4. **Extract the line** — everything up to and including `\n` is returned as the line
5. **Save the remainder** — anything after `\n` is kept in `excess` for the next call
6. **EOF handling** — when `read()` returns `0`, whatever remains in `excess` is returned as the final line

---

## Buffer Size

`BUFFER_SIZE` is defined in the header with a default of `4`. It can be overridden at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The function works correctly with any positive `BUFFER_SIZE`, from `1` to very large values.

---

## Bonus — Multiple File Descriptors

The bonus version replaces the single `static char *excess` with a `static char *excess[1024]`, indexed by `fd`. This allows independent state tracking for up to 1024 file descriptors simultaneously.

```c
// Reading from two files at once
char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);
```

---

## Usage

```c
#include "get_next_line.h"

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## File Structure

```
get_next_line/
├── get_next_line.h               # Header — BUFFER_SIZE define, prototypes
├── get_next_line.c               # Core function (single fd)
├── get_next_line_utils.c         # ft_strlen, ft_strdup, ft_strjoin, ft_substr
├── get_next_line_bonus.h         # Bonus header
├── get_next_line_bonus.c         # Core function (multiple fds via excess[1024])
└── get_next_line_utils_bonus.c   # Utility functions for bonus
```

---

## Edge Cases Handled

- `BUFFER_SIZE` of `1` (reads byte by byte)
- Files with no trailing newline (last line still returned)
- Empty files (returns `NULL` immediately)
- `read()` error (frees `excess`, returns `NULL`)
- Invalid fd (`-1`) or non-positive `BUFFER_SIZE`

---

*Made with lots of coffee and debugging at 42 Beirut*
