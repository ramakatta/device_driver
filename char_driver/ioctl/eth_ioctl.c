#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

int main() {

    int sockfd;
    struct ifreq ifr;

    /* Create socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    /* Interface name */
    strncpy(ifr.ifr_name, "enp43s0", IFNAMSIZ-1);

    /* Get MAC Address */
    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) == 0) {
        unsigned char *mac =
            (unsigned char *)ifr.ifr_hwaddr.sa_data;

        printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
               mac[0], mac[1], mac[2],
               mac[3], mac[4], mac[5]);
    }

    /* Get Interface Flags */
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) == 0) {

        if (ifr.ifr_flags & IFF_UP)
            printf("Interface is UP\n");
        else
            printf("Interface is DOWN\n");
    }

    close(sockfd);
    return 0;
}

