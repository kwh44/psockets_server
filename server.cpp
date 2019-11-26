//
// Created by kwh44 on 11/13/19.
//

#include <iostream>
#include <algorithm>
#include<sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <zconf.h>
#include "utils.hpp"

void start_server(int port_number) {
    const size_t buffer_size = 65535;
    char buf[buffer_size];
    char hello_message[] = "Hello\n";
    struct sockaddr_in server{};
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port_number);
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr *) &server, sizeof(server));
    listen(sd, 1);
    for (;sd;) {
        int psd = accept(sd, 0, 0);
        int cc = recv(psd, buf, buffer_size, 0);
        buf[cc] = '\0';
        if (buf[0] == 'd') {
            auto date_msg = date();
            send(psd, date_msg.c_str(), date_msg.size(), 0);
        } else if (buf[0] == 't') {
            auto time_msg = time();
            send(psd, time_msg.c_str(), time_msg.size(), 0);
        } else if (buf[0] == 'h') {
            send(psd, hello_message, 5, 0);
        } else if (buf[0] == 'm') {
            auto words_num = std::to_string(1 + std::count(buf + 1, buf + cc, ' '));
            send(psd, words_num.c_str(), words_num.size(), 0);
        }
        close(psd);
        buf[0] = '\0';
    }
}

int main(int argc, char *argv[]) {
    int port_number = 8001;
    std::cout << "Server is running.\nYou can echo you message to http://localhost:" << port_number << "/\n";
    start_server(port_number);
    return 0;
}
