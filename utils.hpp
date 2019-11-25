//
// Created by kwh44 on 11/24/19.
//

#ifndef PSOCKETS_SERVER_UTILS_HPP
#define PSOCKETS_SERVER_UTILS_HPP

#include <string>
#include <chrono>
#include <ctime>

std::string date() {
    std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string data_time(std::ctime(&end_time));
    auto start = data_time.find(' ', 1 + data_time.find(' ', 1 + data_time.find(' ')));
    auto end = data_time.find(' ', 1 + start);
    data_time.erase(start, end - start);
    data_time.pop_back();
    return data_time;
}


std::string time() {
    std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string data_time(std::ctime(&end_time));
    auto start = data_time.find(' ', 1 + data_time.find(' ', 1 + data_time.find(' ')));
    auto end = data_time.find(' ', 1 + start);
    std::string time(data_time.substr(start + 1, end - start - 1));
    return time;
}

#endif //PSOCKETS_SERVER_UTILS_HPP
