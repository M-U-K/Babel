/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpClient.hpp
*/

#ifndef __TCPILISTENER_H__
#define __TCPILISTENER_H__

#include <memory>
#include <string>
#include <asio.hpp>

#include "TcpMessage.hpp"

// namespace asio = boost::asio;

namespace tcp
{

    class IListener
    {

        public:
            enum status_e { None, Calling, Called, InCall };

            virtual ~IListener() = default;

            virtual void start() = 0;
            virtual void deliver(const Message& msg) = 0;

            virtual std::string ip() const = 0;
            virtual unsigned short port() const = 0;
            virtual std::string name() const = 0;
            virtual status_e status() const = 0;
            virtual void status(status_e value) = 0;
    };

    typedef std::shared_ptr<IListener> Listener_ptr;

}

#endif // __TCPILISTENER_H__