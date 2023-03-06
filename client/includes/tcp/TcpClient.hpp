/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpClient.hpp
*/

#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QPushButton>

#include <iostream>
#include <variant>

#include "UdpClient.hpp"
#include "UdpServer.hpp"

namespace tcp
{

    class Client
        :   public QObject
    {
        Q_OBJECT

        public:
            enum UdpStatus { SERVER, CLIENT };

        private:
            QTcpSocket *socket;
            std::string m_caller;
            std::variant<void *, udp::Server, udp::Client> m_udp;
            UdpStatus m_udpStatus;

        public slots:
            void onReadyRead();
            void connected();

        public:
            static std::string Address;
            static unsigned short Port;

            Client();
            ~Client();

            bool connectTo();
            QByteArray IntToArray(qint32 source);
            bool writeData(const std::string& data);
            std::string caller();
            void caller(std::string value);

            UdpStatus udpStatus() const;
            void createServer();
            void createClient(const std::string& address, unsigned short port);
            udp::Server& udpServer();
            udp::Client& udpClient();

    }; // class Client

} // namespace tcp

#endif // __TCPCLIENT_H__