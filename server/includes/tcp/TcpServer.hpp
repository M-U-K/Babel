/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpServer.hpp
*/

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <asio.hpp>

#include "TcpRoom.hpp"
#include "Database.hpp"

namespace tcp
{

    class Server
    {

        public:
            Server(uint_least16_t port);
            ~Server() = default;

            void operator()()
            {
                handle_connection();
                m_io_context.run();
            }

        private:
            void handle_connection();

            asio::io_context m_io_context;
            asio::ip::tcp::endpoint m_endpoint;
            asio::ip::tcp::acceptor m_acceptor;
            Room m_room;
            babel::Database database;


    }; // class Server

} // namespace tcp

#endif // __TCPSERVER_H__