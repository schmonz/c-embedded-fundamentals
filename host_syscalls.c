static int open_ret_var = 77;
static int num_mock_open_calls = 0;

int open(const char *path, int oflag, ...)
{
    (void)path;
    (void)oflag;
    num_mock_open_calls++;
    return open_ret_var;
}
 void set_num_mock_open_calls(int num_calls) 
{
    num_mock_open_calls = num_calls;
}

int get_num_mock_open_calls()
{
    return num_mock_open_calls;
}
