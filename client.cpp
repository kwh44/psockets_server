//
// Created by kwh44 on 11/24/19.
//

#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.hpp"

int start_client(const std::string &service_type, const std::string &server_address, uint port,
                 const std::string &message) {
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(server_address.c_str());
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        std::cerr << "Connection error" << std::endl;
        close(sock);
        return EXIT_FAILURE;
    }
    send(sock, service_type.c_str(), service_type.size(), 0);
    if (service_type == "m") send(sock, message.c_str(), message.size(), 0);
    char response[100];
    response[recv(sock, response, 100, 0)] = '\0';
    printf("Server: %s\n", response);
    return 0;
}

int main(int argc, char *argv[]) {
    std::string address(argv[1]);
    std::string type(argv[2]);
    std::string message;
    if (type == "m" && argc > 3) {
        for (size_t i = 3; i < argc - 1; ++i) {
            message += std::string(argv[i]) + ' ';
        }
        message += std::string(argv[argc - 1]) + '\0';
    }
    start_client(type, address, 8001, message);
    return 0;
}

