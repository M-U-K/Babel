/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpClient.cpp
*/

#include <iostream>

#include "TcpListener.hpp"

tcp::Listener::Listener(std::string name, asio::ip::tcp::socket socket, tcp::Room& room)
    :   m_status{None},
        m_name{name},
        m_socket{std::move(socket)},
        m_room{room}
{
    std::cout << "Listener \"" << name << "\" listen " << ip() << ":" << port() << std::endl;
}

void tcp::Listener::start()
{
    m_room.join(m_name, shared_from_this());

    do_read_body();
}

void tcp::Listener::deliver(const tcp::Message& msg)
{
    bool write_in_progress = !m_write_msgs.empty();

    m_write_msgs.push_back(msg);
    if (!write_in_progress)
        do_write();
}

void tcp::Listener::do_read_body()
{
    auto self(shared_from_this());

    m_socket.async_read_some(
        asio::buffer(
            m_read_msg.data(),
            tcp::Message::BodyLength
        ),
        [this, self](asio::error_code error, std::size_t length)
        {
            // Check deconection
            if (!error) {
                // If not send to other participant
                // std::cout << "Client " << m_name << " (" << ip() << ":" << port() << ") -> " << m_read_msg.data() << std::endl;
                m_room.deliver(m_name, m_read_msg);
                m_read_msg.clean();

                // and switch to "waiting for message" mode
                do_read_body();
            }
            else {
                // If not kick the participant
                m_room.leave(m_name);
            }
        }
    );
}

void tcp::Listener::do_write()
{
    auto self(shared_from_this());

    asio::async_write(
        m_socket,
        asio::buffer(
            m_write_msgs.front().data(),
            m_write_msgs.front().length()
        ),
        [this, self](asio::error_code error, std::size_t /*length*/) {
            if (!error) {
                m_write_msgs.pop_front();
                if (!m_write_msgs.empty())
                    do_write();
            } else
                m_room.leave(m_name);
        }
    );
}

std::string tcp::Listener::ip() const
{
    return (m_socket.remote_endpoint().address().to_string());
}

unsigned short tcp::Listener::port() const
{
    return (m_socket.remote_endpoint().port());
}

std::string tcp::Listener::name() const
{
    return (m_name);
}

tcp::Listener::status_e tcp::Listener::status() const
{
    return (m_status);
}

void tcp::Listener::status(tcp::Listener::status_e value)
{
    m_status = value;
}