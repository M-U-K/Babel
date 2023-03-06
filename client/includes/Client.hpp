/*
** EPITECH PROJECT, 2021
** Client.h
** File description:
** Client.h
*/

#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include <string>
#include <QFont>

#include "TcpClient.hpp"
#include "CallWindow.hpp"
#include "CallingWindow.hpp"
#include "AskName.hpp"
#include "Window.hpp"

namespace babel
{
    class Client
    {
    private:
        Client() = default;

        static std::string m_name;
        static std::string m_uuid;
        static std::unique_ptr<CallWindow> m_call;
        static std::unique_ptr<CallingWindow> m_calling;
        static std::unique_ptr<AskName> m_askName;
        static std::unique_ptr<Window> m_app;
        static bool m_inCall;
        static tcp::Client m_tcpClient;
        static bool m_connected;

    public:
        static QFont title;
        static QFont description;
        static QFont info;
        static void setName(std::string newName);
        static std::string getName();
        static void setUuid(std::string& newName);
        static std::string getUuid();
        static void setCallStatus(bool status);
        static bool getCallStatus();
        [[nodiscard]] static std::unique_ptr<Window>& GetApp();
        [[nodiscard]] static tcp::Client& tcpClient();
        [[nodiscard]] static bool connected();
        [[nodiscard]] static std::unique_ptr<CallingWindow>& getCallingWindow();
        [[nodiscard]] static std::unique_ptr<babel::CallWindow>& getCallWindow();

        static void InitializeClient();
        static void StartCall();
        static void StartCalling();
        static void AcceptCall();
        static void DeniedCall();
        static void TryConnect();

    };
}


#endif //BABEL_CLIENT_HPP
