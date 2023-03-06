/*
** EPITECH PROJECT, 2021
** CallWindow.cpp
** File description:
** CallWindow.cpp
*/

#include "sources/gui/qtclass/CallWindow.hpp"
#include "Client.hpp"

babel::CallWindow::CallWindow() :
QWidget(),
m_layout(std::make_unique<QGridLayout>()),
m_accept(std::make_unique<QPushButton>()),
m_denied(std::make_unique<QPushButton>()),
m_logo(std::make_unique<QLabel>()),
m_name(std::make_unique<QLabel>())
{
    m_logo->setFixedSize(300, 200);
    m_logo->setPixmap(QPixmap("../images/fish.jpg").scaled(128, 128, Qt::KeepAspectRatio));
    m_logo->setAlignment(Qt::AlignCenter);
    m_name->setFixedSize(300, 50);
    m_name->setText("Call from default_name");
    m_name->setFont(babel::Client::info);
    m_accept->setFixedSize(150, 50);
    m_accept->setText("Accept");
    m_accept->setFont(babel::Client::info);
    m_denied->setFixedSize(150, 50);
    m_denied->setText("Denied");
    m_denied->setFont(babel::Client::info);
    m_layout->addWidget(m_logo.get(), 0, 0, 2, 2, Qt::AlignTop);
    m_layout->addWidget(m_name.get(), 1, 0, 1, 2);
    m_layout->addWidget(m_accept.get(), 2, 0, 1, 1);
    m_layout->addWidget(m_denied.get(), 2, 1, 1, 1);
    setLayout(m_layout.get());

    QObject::connect(m_accept.get(), SIGNAL(clicked()), this, SLOT(acceptCall()));
    QObject::connect(m_denied.get(), SIGNAL(clicked()), this, SLOT(deniedCall()));
}

void babel::CallWindow::acceptCall()
{
    babel::Client::AcceptCall();
}

void babel::CallWindow::deniedCall()
{
    babel::Client::DeniedCall();
}