
#define O_WRONLY 0xff

int open(const char *path, int oflag, ...);
int get_num_mock_open_calls(void);
void set_num_mock_open_calls(int num_calls);
char* get_last_mock_open_path(void);
