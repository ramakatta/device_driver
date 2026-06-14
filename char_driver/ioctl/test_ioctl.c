#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "ioctl_const.h"

#define DEV "/dev/my_cdrv"

static int fd = -1;

/* ---------- menu ---------- */
static void menu()
{
    printf("\n=========== DRIVER TEST MENU ===========\n");
    printf("1. Open device\n");
    printf("2. Close device\n");
    printf("3. Write data\n");
    printf("4. Read data\n");
    printf("5. Seek (lseek)\n");
    printf("6. Fill ZERO (ioctl)\n");
    printf("7. Fill CHAR (ioctl)\n");
    printf("8. Get SIZE (ioctl)\n");
    printf("9. Set SIZE (ioctl)\n");
    printf("10. Encrypt (ioctl)\n");
    printf("11. Decrypt (ioctl)\n");
    printf("12. Reset offset (seek 0)\n");
    printf("13. Exit\n");
    printf("========================================\n");
    printf("Enter choice: ");
}

/* ---------- open ---------- */
static void open_dev()
{
    fd = open(DEV, O_RDWR);
    if (fd < 0)
        perror("open");
    else
        printf("Opened fd=%d\n", fd);
}

/* ---------- close ---------- */
static void close_dev()
{
    if (fd >= 0) {
        close(fd);
        fd = -1;
        printf("closed\n");
    }
}

/* ---------- write ---------- */
static void do_write()
{
    char buf[256];

    printf("Enter string: ");
    scanf(" %[^\n]", buf);

    ssize_t ret = write(fd, buf, strlen(buf));

    if (ret < 0)
        perror("write");
    else
        printf("written %zd bytes\n", ret);
}

/* ---------- read ---------- */
static void do_read()
{
    char buf[256];
    memset(buf, 0, sizeof(buf));

    ssize_t ret = read(fd, buf, sizeof(buf) - 1);

    if (ret < 0)
        perror("read");
    else {
        printf("read %zd bytes\n", ret);
        printf("data: %s\n", buf);
    }
}

/* ---------- seek ---------- */
static void do_seek()
{
    long off;
    int whence;

    printf("Enter offset: ");
    scanf("%ld", &off);

    printf("Enter whence (0=SET,1=CUR,2=END): ");
    scanf("%d", &whence);

    off_t ret = lseek(fd, off, whence);

    if (ret < 0)
        perror("lseek");
    else
        printf("new offset = %ld\n", ret);
}

/* ---------- reset ---------- */
static void reset_seek()
{
    if (lseek(fd, 0, SEEK_SET) < 0)
        perror("reset seek");
    else
        printf("offset reset to 0\n");
}

/* ---------- ioctl helpers ---------- */
static void ioctl_zero()
{
    if (ioctl(fd, MY_FILL_ZERO) < 0)
        perror("FILL_ZERO");
}

static void ioctl_char()
{
    char c;
    printf("Enter char: ");
    scanf(" %c", &c);

    if (ioctl(fd, MY_FILL_CHAR, &c) < 0)
        perror("FILL_CHAR");
}

static void ioctl_get_size()
{
    unsigned int size;

    if (ioctl(fd, MY_GET_SIZE, &size) < 0)
        perror("GET_SIZE");
    else
        printf("size = %u\n", size);
}

static void ioctl_set_size()
{
    unsigned int size;

    printf("Enter size: ");
    scanf("%u", &size);

    if (ioctl(fd, MY_SET_SIZE, &size) < 0)
        perror("SET_SIZE");
}

static void ioctl_encrypt()
{
    char key;

    printf("Enter key: ");
    scanf("%c", &key);

    if (ioctl(fd, MY_ENCRYPT, &key) < 0)
        perror("ENCRYPT");
}

static void ioctl_decrypt()
{
    char key;

    printf("Enter key: ");
    scanf("%c", &key);

    if (ioctl(fd, MY_DECRYPT, &key) < 0)
        perror("DECRYPT");
}

/* ---------- main ---------- */
int main()
{
    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {

        case 1: open_dev(); break;
        case 2: close_dev(); break;
        case 3: do_write(); break;
        case 4: do_read(); break;
        case 5: do_seek(); break;
        case 6: ioctl_zero(); break;
        case 7: ioctl_char(); break;
        case 8: ioctl_get_size(); break;
        case 9: ioctl_set_size(); break;
        case 10: ioctl_encrypt(); break;
        case 11: ioctl_decrypt(); break;
        case 12: reset_seek(); break;

        case 13:
            if (fd >= 0) close(fd);
            return 0;

        default:
            printf("Invalid choice\n");
        }
    }
}
