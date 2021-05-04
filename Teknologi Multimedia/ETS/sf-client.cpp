// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

#define PORT 8080

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[] = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    char str[255];
    scanf("%[^\n]s", str);
    send(sock , str , strlen(str) , 0 );
    printf("Your message has been sent\n");

    int before;
    float total,ratio;
    valread = read( sock , &before, sizeof(before));
    sleep(1);
    valread = read( sock , &total, sizeof(total));
    sleep(1);
    valread = read( sock , &ratio, sizeof(ratio));
    sleep(1);

    printf("\n\n\tBefore Compression: %d bits/symbol\n", before);
    printf("\tAfter  Compression: %0.6f bits/symbol\n", total);
    printf("\tCompression ratio : %0.6f\n\n\n", ratio);

    return 0;
}
