/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** UdpClient.hpp
*/

#ifndef __UDPCLIENT_H__
#define __UDPCLIENT_H__

#include <QUdpSocket>
#include <QHostAddress>

namespace udp
{

    class Client
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
            explicit Client(const std::string& address, unsigned short port);
            ~Client();

    };

}

#endif // __UDPCLIENT_H__