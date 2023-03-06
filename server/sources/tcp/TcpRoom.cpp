/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpRoom.cpp
*/

#include <iostream>

#include "TcpRoom.hpp"

void tcp::Room::join(std::string name, tcp::Listener_ptr client)
{
    std::cout << "A client joined the room" << std::endl;

    // Add the new client to the room
    m_listeners.insert(std::make_pair(name, client));

    // Send historic to the new client
    // for (auto msg : m_recent_msgs)
    //     client->deliver(msg);
}

void tcp::Room::leave(std::string name)
{
    std::cout << "A client leaved the room" << std::endl;

    // Remove the new client from the room
    m_listeners.erase(name);
}

void tcp::Room::deliver(std::string sender_name, const tcp::Message& msg)
{
    std::cout << "Receive from client <" << msg.dataStr() << ">" << std::endl;

    std::size_t cmd_sep = msg.dataStr().find_first_of('-');
    std::size_t target_sep = msg.dataStr().find_first_of('-', cmd_sep + 1);
    std::size_t address_sep = msg.dataStr().find_first_of('-', target_sep + 1);

    // Split message
    std::string cmd = msg.dataStr().substr(0, cmd_sep);
    std::string target_name = msg.dataStr().substr(cmd_sep + 1, target_sep - cmd_sep - 1);

    auto& sender = m_listeners[sender_name];
    auto target_it = m_listeners.find(target_name);

    // Check if target is connected
    if (target_it == m_listeners.end()) {
        sender->deliver(target_name + " is not connected");
        return;
    }

    // Target is connected so take target from his it
    auto& target = target_it->second;

    if (cmd == "call") {
        if (sender->status() != tcp::IListener::None)
            sender->deliver("You are already in a call");
        else if (target->status() != tcp::IListener::None)
            sender->deliver(target_name + " is already in a call");
        else {
            std::string callerIp = msg.dataStr().substr(target_sep + 1);

            std::cout << callerIp << std::endl;
            sender->status(tcp::IListener::Calling);
            sender->deliver("calling-" + target_name);
            target->status(tcp::IListener::Called);
            target->deliver("called-" + sender_name + "-" + callerIp);
        }
    }
    if (cmd == "hangup") {
        if (sender->status() == tcp::IListener::Called
        || sender->status() == tcp::IListener::InCall) {
            sender->status(tcp::IListener::None);
            sender->deliver("hangupDone");
            target->status(tcp::IListener::None);
            target->deliver("hangup-" + sender_name);
        }
        else
            sender->deliver("You are not in a call");
    }
    if (cmd == "accept") {
        if (sender->status() == tcp::IListener::Called) {
            sender->status(tcp::IListener::InCall);
            sender->deliver("acceptDone");
            target->status(tcp::IListener::InCall);
            target->deliver("accept-" + sender_name);
        }
        else
            sender->deliver("You are not called");
    }
}

void tcp::Room::deliverToAll(const Message& msg)
{
    for (auto& [_, listener] : m_listeners)
        listener->deliver(msg);
}