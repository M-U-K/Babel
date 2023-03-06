/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpRoom.hpp
*/

#ifndef __TCPROOM_H__
#define __TCPROOM_H__

#include <unordered_map>

#include "TcpIListener.hpp"

namespace tcp
{

    class Room
    {

        public:
            Room() = default;
            ~Room() = default;

            void join(std::string name, Listener_ptr listener);
            void leave(std::string name);
            void deliver(std::string name, const Message& msg);
            void deliverToAll(const Message& msg);

            [[nodiscard]] bool hasClient(const std::string& name);

        private:
            enum { max_recent_msgs = 100 };

            std::unordered_map<std::string, Listener_ptr> m_listeners;

    }; // class Room

} // namespace tcp

#endif // __TCPROOM_H__