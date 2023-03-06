/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpClient.cpp
*/

#include <sstream>

#include "Client.hpp"
#include "TcpClient.hpp"
#include "InteractionWindow.hpp"
#include "ContactWindow.hpp"

std::string tcp::Client::Address = "0.0.0.0";
unsigned short tcp::Client::Port = 5008;

tcp::Client::Client()
    :   socket{new QTcpSocket(this)},
        m_caller{},
        m_udpStatus{CLIENT},
        m_udp{}
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
}

tcp::Client::~Client()
{}

void tcp::Client::onReadyRead()
{
    std::string msg = socket->readAll().data();

    std::cout << "Receive from server : " << msg << std::endl;

    std::size_t cmd_sep = msg.find_first_of('-');
    std::size_t target_sep = msg.find_first_of('-', cmd_sep + 1);
    std::size_t address_sep = msg.find_first_of('-', target_sep + 1);

    std::string cmd = msg.substr(0, cmd_sep);
    std::string target = msg.substr(cmd_sep + 1, target_sep - cmd_sep - 1);

    std::stringstream ss(target);

    if (cmd == "users" || cmd == "new") {
        while (ss.good()) {
            std::string name;
            std::getline(ss, name, ',');
            if (babel::Client::getName() != name && !name.empty())
                babel::Client::GetApp()->getContactSection()->addContact(name);
        }
    }
    if (cmd == "calling") {
        babel::Client::StartCall();
        m_caller = target;
    }
    if (cmd == "called") {
        babel::Client::StartCall();
        m_caller = target;
        // std::string callerAddress = msg.substr(target_sep + 1, address_sep - target_sep - 1);
        // unsigned short callerPort = static_cast<unsigned short>(std::stoul(msg.substr(address_sep + 1)));
        // createClient(callerAddress, callerPort);
    }
    if (cmd == "accept") {
        m_caller = target;
        babel::Client::getCallWindow()->close();
        babel::Client::GetApp()->getInteractionSection()->getButtonSection()->setInCall(true);
    }
    // if (cmd == "acceptDone")
    //     m_udpClient.connectToHost(m_callerAddress, m_callerPort);
    if (cmd == "hangup") {
        m_caller = "";
        babel::Client::getCallWindow()->close();
        babel::Client::GetApp()->getInteractionSection()->getButtonSection()->setInCall(false);
    }
}

bool tcp::Client::connectTo()
{
    std::cout << "Try to connect to " << Address << ":" << Port << std::endl;

    socket->connectToHost(Address.c_str(), Port);

    if (!socket->waitForConnected(5000)) {
        std::cout << "Can't connected" << std::endl;
        return (false);
    }
    std::cout << "Connected" << std::endl;

    writeData(babel::Client::getName());

    return (true);
}

QByteArray tcp::Client::IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return (temp);
}

bool tcp::Client::writeData(const std::string& data)
{
    std::cout << "Send <" << data << "> to server" << std::endl;

    if(socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(QByteArray(data.c_str()), data.size()); //write the data itself
        return (socket->waitForBytesWritten());
    }
    else
        return (false);
}

std::string tcp::Client::caller()
{
    return (m_caller);
}

void tcp::Client::caller(std::string value)
{
    m_caller = value;
}

void tcp::Client::connected()
{}

tcp::Client::UdpStatus tcp::Client::udpStatus() const
{
    return (m_udpStatus);
}

void tcp::Client::createServer()
{
    m_udpStatus = SERVER;
    m_udp.emplace<udp::Server>();
}

void tcp::Client::createClient(const std::string& address, unsigned short port)
{
    m_udpStatus = CLIENT;
    m_udp.emplace<udp::Client>(address, port);
}

udp::Server& tcp::Client::udpServer()
{
    if (m_udpStatus == SERVER)
        return (std::get<udp::Server>(m_udp));
    std::cerr << "You try to get udp server but the udp type is client" << std::endl;
    throw std::exception();
}

udp::Client& tcp::Client::udpClient()
{
    if (m_udpStatus == CLIENT)
        return (std::get<udp::Client>(m_udp));
    std::cerr << "You try to get udp client but the udp type is server" << std::endl;
    throw std::exception();
}