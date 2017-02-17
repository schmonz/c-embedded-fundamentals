void mock_reset_all(void);

int open(const char *, int, ...);
#define O_WRONLY 77
void mock_open_fake_return_value(int);
int mock_open_spy_numcalls(void);
const char* mock_open_spy_path(void);
int mock_open_spy_oflag(void);

int ioctl(int, unsigned long, void *);
#define GPIOTOGGLE 66
struct gpio_req {
    int gp_pin;
};
void mock_ioctl_fake_return_value(int);
int mock_ioctl_spy_numcalls(void);
int mock_ioctl_spy_fd(void);
int mock_ioctl_spy_request(void);
int mock_ioctl_spy_pin(void);

int close(int);
int mock_close_spy_numcalls(void);
int mock_close_spy_fd(void);
