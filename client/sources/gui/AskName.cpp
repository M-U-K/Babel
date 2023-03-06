/*
** EPITECH PROJECT, 2021
** CallButton.cpp
** File description:
** CallButton.cpp
*/

#include "AskName.hpp"
#include "Client.hpp"
#include "InteractionWindow.hpp"

babel::AskName::AskName(QWidget *parent) :
QInputDialog(parent)
{
    QObject::connect(this, SIGNAL(textValueSelected(QString)), this, SLOT(validateName(QString)));
}

void babel::AskName::validateName(QString name)
{
    if (name.isEmpty()) {
        this->close();
        babel::Client::GetApp()->close();
        return;
    }

    babel::Client::setName(name.toLocal8Bit().data());

    babel::Client::TryConnect();
    if (!babel::Client::connected()) {
        this->close();
        return;
    }

    babel::Client::GetApp()->getInteractionSection()->getNameSection()->displayProfile();
    this->close();
}