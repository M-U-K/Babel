/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** main.cpp
*/

#include <iostream>
#include <stdexcept>
#include "TcpServer.hpp"


static inline unsigned short stous(char const *str)
{
    int test = std::stoi(str);

    if (test < 0 || test > 65534)
        throw std::invalid_argument("wrong size");
    return test;
}

int main(int ac, char const **av)
{
    try
    {
        if (ac != 2)
            throw std::invalid_argument("not enough arguments");
        uint_least16_t port = stous(av[1]);

        tcp::Server server(port);
        server();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}