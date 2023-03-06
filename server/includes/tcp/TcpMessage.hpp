/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** TcpMessage.hpp
*/

#ifndef __TCPMESSAGE_H__
#define __TCPMESSAGE_H__

#include <typeinfo>
#include <deque>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string.h>

namespace tcp
{

    class Message
    {

        public:
            static const int BodyLength = 50;

            Message()
                :   m_data{0}
            {}
            Message(const std::string& str)
                :   m_data{0}
            {
                std::strcpy(m_data, str.c_str());
            }
            Message(const char *str)
                :   m_data{0}
            {
                std::strcpy(m_data, str);
            }
            ~Message() = default;

            const char *data() const
            {
                return m_data;
            }

            char *data()
            {
                return m_data;
            }

            std::string dataStr() const
            {
                return std::string(m_data);
            }

            std::size_t length() const
            {
                return std::string(m_data).size();
            }

            void clean()
            {
                std::fill(m_data, m_data + BodyLength, 0);
            }

        private:
            char m_data[BodyLength];

    }; // class Message

    typedef std::deque<Message> Message_queue;

} // namespace tcp

#endif // __TCPMESSAGE_H__