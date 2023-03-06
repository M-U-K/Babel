/*
** EPITECH PROJECT, 2021
** Client.cpp
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include "InteractionWindow.hpp"

std::string babel::Client::m_name = {};
std::string babel::Client::m_uuid;
std::unique_ptr<babel::CallWindow> babel::Client::m_call;
std::unique_ptr<babel::CallingWindow> babel::Client::m_calling;
std::unique_ptr<babel::AskName> babel::Client::m_askName;
std::unique_ptr<babel::Window> babel::Client::m_app;
bool babel::Client::m_inCall;
bool babel::Client::m_connected = false;

QFont babel::Client::title;
QFont babel::Client::description;
QFont babel::Client::info;
tcp::Client babel::Client::m_tcpClient;

void babel::Client::InitializeClient()
{
    m_name = "default_name";
    m_uuid = "default_uuid";
    m_inCall = false;
    m_app = std::make_unique<babel::Window>();

    title = QFont("papyrus", 50);
    description = QFont("papyrus", 20);
    info = QFont("papyrus", 15);
    m_askName = std::make_unique<AskName>();
    babel::Client::GetApp()->showMaximized();
    m_askName->show();
}

void babel::Client::setName(std::string newName)
{
    m_name = newName;
}

std::string babel::Client::getName()
{
    return (m_name);
}

void babel::Client::setUuid(std::string& newName)
{
    m_uuid = newName;
}

std::string babel::Client::getUuid()
{
    return (m_uuid);
}

void babel::Client::StartCall()
{
    m_call = std::make_unique<babel::CallWindow>();
    m_call->show();
}

void babel::Client::StartCalling()
{
    m_calling = std::make_unique<babel::CallingWindow>();
    m_calling->show();
}

void babel::Client::AcceptCall()
{
    tcpClient().writeData("accept-" + tcpClient().caller());
    m_app->getInteractionSection()->getButtonSection()->setInCall(true);
    m_call->close();
}

void babel::Client::DeniedCall()
{
    tcpClient().writeData("hangup-" + tcpClient().caller());
    m_app->getInteractionSection()->getButtonSection()->setInCall(false);
    if (m_call)
        m_call->close();
    if (m_calling)
        m_calling->close();
}

void babel::Client::TryConnect()
{
    m_connected = m_tcpClient.connectTo();
}

void babel::Client::setCallStatus(bool status)
{
    m_inCall = status;
}

bool babel::Client::getCallStatus()
{
    return (m_inCall);
}

std::unique_ptr<babel::Window>& babel::Client::GetApp()
{
    return (m_app);
}

tcp::Client& babel::Client::tcpClient()
{
    return (m_tcpClient);
}

bool babel::Client::connected()
{
    return (m_connected);
}

std::unique_ptr<babel::CallingWindow> &babel::Client::getCallingWindow()
{
    return (m_calling);
}

std::unique_ptr<babel::CallWindow> &babel::Client::getCallWindow()
{
    return (m_call);
}