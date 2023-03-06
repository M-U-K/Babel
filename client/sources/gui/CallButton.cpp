/*
** EPITECH PROJECT, 2021
** CallButton.cpp
** File description:
** CallButton.cpp
*/

#include "CallButton.hpp"
#include "InteractionWindow.hpp"

babel::CallButton::CallButton(std::shared_ptr<Name>& name, QWidget *parent) :
QWidget(parent),
m_name(name),
m_selectedContact(false),
m_call(std::make_unique<QPushButton>(this)),
m_hangUp(std::make_unique<QPushButton>(this)),
m_favorites(std::make_unique<QPushButton>(this)),
m_profile(std::make_unique<QPushButton>(this)),
m_layout(std::make_unique<QGridLayout>(this)),
m_spacer(new QSpacerItem(100, 200))
{
    m_call->setText("Call");
    m_call->setToolTip("Start a call");
    m_hangUp->setText("Hang Up");
    m_hangUp->setToolTip("Hang up current call");
    m_favorites->setText("Add to favorites");
    m_favorites->setToolTip("Add to favorites");
    m_profile->setText("Display your profile");
    m_profile->setToolTip("Display your profile");
    m_profile->setCursor(QCursor(Qt::PointingHandCursor));

    m_layout->addItem(m_spacer, 0, 0);
    m_layout->addWidget(m_call.get(), 1, 0);
    m_layout->addWidget(m_hangUp.get(), 1, 1);
    m_layout->addWidget(m_favorites.get(), 1, 2);
    m_layout->addWidget(m_profile.get(), 2, 0, 1, 3);
    setLayout(m_layout.get());
    updateButton();
    QObject::connect(m_profile.get(), SIGNAL(clicked()), this, SLOT(showProfile()));
    QObject::connect(m_call.get(), SIGNAL(clicked()), this, SLOT(startCall()));
    QObject::connect(m_hangUp.get(), SIGNAL(clicked()), this, SLOT(hangUp()));
}

void babel::CallButton::updateButton()
{
    m_call->setEnabled(m_selectedContact);
    setCursor(QCursor((m_selectedContact) ? Qt::PointingHandCursor : Qt::ArrowCursor));
    m_hangUp->setEnabled(babel::Client::getCallStatus());
    setCursor(QCursor((babel::Client::getCallStatus()) ? Qt::PointingHandCursor : Qt::ArrowCursor));
    m_favorites->setEnabled(false);
}

void babel::CallButton::setSelection(bool select)
{
    m_selectedContact = select;
}

void babel::CallButton::showProfile()
{
    m_name->displayProfile();
    setSelection(false);
    updateButton();
}

void babel::CallButton::startCall()
{
    auto& tcp = babel::Client::tcpClient();

    // tcp.createServer();
    // auto& udp = tcp.udpServer();
    // tcp.writeData("call-" + m_name->getName() + "-" + udp.address() + "-" + std::to_string(udp.port()));

    tcp.writeData("call-" + m_name->getName());
}

void babel::CallButton::setInCall(bool inCall)
{
    m_hangUp->setEnabled(inCall);
    babel::Client::setCallStatus(inCall);
}

void babel::CallButton::hangUp()
{
    setInCall(false);
    babel::Client::tcpClient().writeData("hangup-" + babel::Client::tcpClient().caller());
    babel::Client::tcpClient().caller("");
}