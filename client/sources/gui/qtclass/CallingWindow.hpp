/*
** EPITECH PROJECT, 2021
** CallWindow.h
** File description:
** CallWindow.h
*/

#ifndef BABEL_CALLINGWINDOW_HPP
#define BABEL_CALLINGWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <memory>

namespace babel
{
    class CallingWindow :
        public QWidget
    {
        Q_OBJECT
    private:
        std::shared_ptr<QGridLayout> m_layout;
        std::unique_ptr<QPushButton> m_denied;
        std::unique_ptr<QLabel> m_logo;
        std::unique_ptr<QLabel> m_name;
    public:
        CallingWindow();
    public slots:
        void deniedCall();
    };
}

#endif //BABEL_CALLINGWINDOW_HPP
