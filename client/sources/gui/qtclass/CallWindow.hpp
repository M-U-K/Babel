/*
** EPITECH PROJECT, 2021
** CallWindow.h
** File description:
** CallWindow.h
*/

#ifndef BABEL_CALLWINDOW_HPP
#define BABEL_CALLWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <memory>

namespace babel
{
    class CallWindow :
        public QWidget
    {
        Q_OBJECT
    private:
        std::shared_ptr<QGridLayout> m_layout;
        std::unique_ptr<QPushButton> m_accept;
        std::unique_ptr<QPushButton> m_denied;
        std::unique_ptr<QLabel> m_logo;
        std::unique_ptr<QLabel> m_name;
    public:
        CallWindow();
    public slots:
        void acceptCall();
        void deniedCall();
    };
}

#endif //BABEL_CALLWINDOW_HPP
