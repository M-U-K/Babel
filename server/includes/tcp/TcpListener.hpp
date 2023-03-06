/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** tcpClient.hpp
*/

#ifndef __TCPLISTENER_H__
#define __TCPLISTENER_H__

#include "TcpIListener.hpp"
#include "TcpRoom.hpp"

namespace tcp
{

    class Listener
        :   public IListener,
            public std::enable_shared_from_this<Listener>
    {

        public:
            Listener(std::string name, asio::ip::tcp::socket socket, Room& room);
            ~Listener() = default;

            void start() override;
            void deliver(const Message& msg) override;

            [[nodiscard]] std::string ip() const override;
            [[nodiscard]] unsigned short port() const override;
            [[nodiscard]] std::string name() const override;
            [[nodiscard]] status_e status() const override;
            void status(status_e value) override;

        private:
            status_e m_status;
            std::string m_name;

            asio::ip::tcp::socket m_socket;
            Room& m_room;
            Message m_read_msg;
            Message_queue m_write_msgs;

            void do_read_body();
            void do_write();

    }; // class Listener

} // namespace tcp

#endif // __TCPLISTENER_H__