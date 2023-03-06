/*
** EPITECH PROJECT, 2021
** CallButton.h
** File description:
** CallButton.h
*/

#ifndef BABEL_CALLBUTTON_HPP
#define BABEL_CALLBUTTON_HPP

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSpacerItem>
#include <memory>

#include "Client.hpp"
#include "Name.hpp"

namespace babel
{
    class CallButton :
        public QWidget
    {
        Q_OBJECT
    private:
        std::shared_ptr<Name> m_name;
        bool m_selectedContact;
        std::unique_ptr<QPushButton> m_call;
        std::unique_ptr<QPushButton> m_hangUp;
        std::unique_ptr<QPushButton> m_favorites;
        std::unique_ptr<QPushButton> m_profile;
        std::unique_ptr<QGridLayout> m_layout;
        QSpacerItem *m_spacer;

    public:
        explicit CallButton(std::shared_ptr<Name>& name, QWidget *parent = nullptr);
        void updateButton();
        void setSelection(bool select);
        void setInCall(bool inCall);
    public slots:
        void showProfile();
        void startCall();
        void hangUp();
    };
}

#endif //BABEL_CALLBUTTON_HPP
