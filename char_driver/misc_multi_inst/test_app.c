#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAX_INSTANCES 4
#define BUF_SIZE 256

static int fd[MAX_INSTANCES] = {-1, -1, -1, -1};

/* -------- menu -------- */
static void menu()
{
    printf("\n=========== MULTI MISC TEST ===========\n");
    printf("1. Open all devices\n");
    printf("2. Close all devices\n");
    printf("3. Write to instance\n");
    printf("4. Read from instance\n");
    printf("5. Write all instances\n");
    printf("6. Read all instances\n");
    printf("7. Test isolation (write different data)\n");
    printf("8. Exit\n");
    printf("=======================================\n");
    printf("Enter choice: ");
}

/* -------- open all -------- */
static void open_all()
{
    char path[64];

    for (int i = 0; i < MAX_INSTANCES; i++) {
        snprintf(path, sizeof(path), "/dev/multi_misc%d", i);

        fd[i] = open(path, O_RDWR);
        if (fd[i] < 0)
            perror(path);
        else
            printf("Opened %s fd=%d\n", path, fd[i]);
    }
}

/* -------- close all -------- */
static void close_all()
{
    for (int i = 0; i < MAX_INSTANCES; i++) {
        if (fd[i] >= 0) {
            close(fd[i]);
            fd[i] = -1;
            printf("Closed instance %d\n", i);
        }
    }
}

/* -------- write single -------- */
static void write_instance()
{
    int idx;
    char buf[BUF_SIZE];

    printf("Enter instance (0-%d): ", MAX_INSTANCES - 1);
    scanf("%d", &idx);

    if (idx < 0 || idx >= MAX_INSTANCES || fd[idx] < 0) {
        printf("Invalid instance\n");
        return;
    }

    printf("Enter data: ");
    scanf(" %[^\n]", buf);

    ssize_t ret = write(fd[idx], buf, strlen(buf));

    if (ret < 0)
        perror("write");
    else
        printf("written %zd bytes to instance %d\n", ret, idx);
}

/* -------- read single -------- */
static void read_instance()
{
    int idx;
    char buf[BUF_SIZE];

    printf("Enter instance (0-%d): ", MAX_INSTANCES - 1);
    scanf("%d", &idx);

    if (idx < 0 || idx >= MAX_INSTANCES || fd[idx] < 0) {
        printf("Invalid instance\n");
        return;
    }

    memset(buf, 0, sizeof(buf));

    lseek(fd[idx], 0, SEEK_SET);   // important for repeat reads

    ssize_t ret = read(fd[idx], buf, sizeof(buf) - 1);

    if (ret < 0)
        perror("read");
    else
        printf("instance %d: [%s]\n", idx, buf);
}

/* -------- write all -------- */
static void write_all()
{
    char buf[BUF_SIZE];

    printf("Enter data for ALL instances: ");
    scanf(" %[^\n]", buf);

    for (int i = 0; i < MAX_INSTANCES; i++) {
        if (fd[i] < 0)
            continue;

        ssize_t ret = write(fd[i], buf, strlen(buf));

        if (ret < 0)
            perror("write");
        else
            printf("instance %d wrote %zd bytes\n", i, ret);
    }
}

/* -------- read all -------- */
static void read_all()
{
    char buf[BUF_SIZE];

    for (int i = 0; i < MAX_INSTANCES; i++) {

        if (fd[i] < 0)
            continue;

        memset(buf, 0, sizeof(buf));

        lseek(fd[i], 0, SEEK_SET);

        ssize_t ret = read(fd[i], buf, sizeof(buf) - 1);

        if (ret < 0)
            perror("read");
        else
            printf("instance %d -> %s\n", i, buf);
    }
}

/* -------- isolation test -------- */
static void test_isolation()
{
    char buf[BUF_SIZE];

    printf("Testing isolation...\n");

    for (int i = 0; i < MAX_INSTANCES; i++) {
        if (fd[i] < 0)
            continue;

        snprintf(buf, sizeof(buf), "DATA_FROM_INSTANCE_%d", i);

        write(fd[i], buf, strlen(buf));
    }

    printf("Reading back...\n");

    for (int i = 0; i < MAX_INSTANCES; i++) {
        if (fd[i] < 0)
            continue;

        memset(buf, 0, sizeof(buf));

        lseek(fd[i], 0, SEEK_SET);
        read(fd[i], buf, sizeof(buf) - 1);

        printf("Instance %d stored: %s\n", i, buf);
    }
}

/* -------- main -------- */
int main()
{
    int choice;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {

        case 1: open_all(); break;
        case 2: close_all(); break;
        case 3: write_instance(); break;
        case 4: read_instance(); break;
        case 5: write_all(); break;
        case 6: read_all(); break;
        case 7: test_isolation(); break;

        case 8:
            close_all();
            return 0;

        default:
            printf("Invalid choice\n");
        }
    }
}

