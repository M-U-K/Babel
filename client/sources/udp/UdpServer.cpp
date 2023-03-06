/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** UdpServer.cpp
*/

#include <iostream>
#include <QNetworkDatagram>
#include <QNetworkInterface>

#include "UdpServer.hpp"

udp::Server::Server()
    :   m_socket{new QUdpSocket()},
        m_address{},
        m_port{}
{
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    if (!m_socket->bind(QHostAddress("0.0.0.0"))) {
        std::cerr << "Can't bind socket" << std::endl;
        return;
    }
    m_address = QNetworkInterface::allAddresses()[2]; // TODO
    m_port = m_socket->localPort();
    std::cout << "Launch udp server at " << m_address.toString().toStdString() << ":" << m_port;
}

udp::Server::~Server()
{
    delete (m_socket);
}

void udp::Server::onReadyRead()
{
    QByteArray Buffer;
    Buffer.resize(m_socket->pendingDatagramSize());

    // m_socket->readDatagram(Buffer.data(), Buffer.size(), &m_address, &m_port);
}

std::string udp::Server::address() const
{
    return (std::string(m_address.toString().toLocal8Bit().data()));
}

unsigned short udp::Server::port() const
{
    return (m_port);
}