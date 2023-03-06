/*
** EPITECH PROJECT, 2021
** Name.h
** File description:
** Name.h
*/

#ifndef BABEL_NAME_HPP
#define BABEL_NAME_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <string>
#include <memory>
#include <QLabel>

namespace babel
{
    class Name :
        public QWidget
    {
    private:
        std::unique_ptr<QVBoxLayout> m_layout;
        std::unique_ptr<QLabel> m_uuid;
        std::unique_ptr<QLabel> m_name;
        QFont m_font;
    public:
        explicit Name(QWidget *parent = nullptr);
        void displayProfile();
        void setName(std::string name);
        std::string getName();
    };
}


#endif //BABEL_NAME_HPP
