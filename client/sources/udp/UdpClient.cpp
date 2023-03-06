/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** UdpClient.cpp
*/

#include <iostream>
#include <QNetworkDatagram>

#include "UdpClient.hpp"

udp::Client::Client(const std::string& address, unsigned short port)
    :   m_socket{new QUdpSocket(this)},
        m_address{QHostAddress(address.c_str())},
        m_port{port}
{
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    std::cout << "Try connect with udp to : " << m_address.toString().toStdString() << ":" << m_port << std::endl;
    m_socket->bind(m_address, m_port);
    if (!m_socket->waitForConnected(30000)) {
        std::cerr << "Can't connected" << std::endl;
        throw std::exception();
    }
    std::cout << "Connected" << std::endl;

    m_socket->writeDatagram("Hello", 5, m_address, m_port);
}

udp::Client::~Client()
{}

void udp::Client::onReadyRead()
{
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();

        qDebug() << datagram.data();
        // processTheDatagram(datagram);
    }
};