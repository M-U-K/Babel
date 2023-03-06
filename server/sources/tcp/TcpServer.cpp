/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpServer.cpp
*/

//windows version target for compiler
#ifdef WIN32
#include <SDKDDKVer.h>
#endif

#include <iostream>
#include "Database.hpp"

using namespace babel;

#include "TcpServer.hpp"
#include "TcpListener.hpp"

tcp::Server::Server(uint_least16_t port)
    :   m_io_context(),
        m_endpoint(asio::ip::tcp::v4(), port),
        m_acceptor(m_io_context, m_endpoint),
        m_room()
{
    std::cout << "Starting server at address " << m_endpoint << std::endl;
}

void tcp::Server::handle_connection()
{
    std::cout << "Waiting for connection ..." << std::endl;

    m_acceptor.async_accept(
        [this] (asio::error_code error, asio::ip::tcp::socket socket) {
            if (!error) {
                std::cout << "New connection !" << std::endl;

                char buffer[101] = {0};
                socket.read_some(asio::buffer(buffer, 100));

                socket.write_some(asio::buffer("users-" + database.get_all_name()));

                std::string new_user(buffer);
                try {
                    if (database.get<fields::id, std::string, int>(new_user) == -1) {
                        database.create_user(new_user);
                        m_room.deliverToAll(tcp::Message("new-" + new_user));
                    }
                }
                catch (...) {
                    database.create_user(new_user);
                    m_room.deliverToAll(tcp::Message("new-" + new_user));
                }

                std::make_shared<tcp::Listener>(std::string(buffer), std::move(socket), m_room)->start();
            }
            handle_connection();
        }
    );
}