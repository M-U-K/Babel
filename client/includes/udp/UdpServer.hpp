/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** UdpServer.hpp
*/

#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__

#include <QUdpSocket>
#include <QHostAddress>

namespace udp
{

    class Server
        :   public QObject
    {
        Q_OBJECT

        private:
            QUdpSocket *m_socket;
            QHostAddress m_address;
            quint16 m_port;

        public slots:
            void onReadyRead();

        public:
            Server();
            ~Server();

            std::string address() const;
            unsigned short port() const;

    }; // class Server

} // namespace udp

#endif // __UDPSERVER_H__