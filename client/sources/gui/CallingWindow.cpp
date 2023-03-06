/*
** EPITECH PROJECT, 2021
** CallingWindow.cpp
** File description:
** CallingWindow.cpp
*/

#include "sources/gui/qtclass/CallingWindow.hpp"
#include "Client.hpp"

babel::CallingWindow::CallingWindow() :
QWidget(),
m_layout(std::make_unique<QGridLayout>()),
m_denied(std::make_unique<QPushButton>()),
m_logo(std::make_unique<QLabel>()),
m_name(std::make_unique<QLabel>())
{
    m_logo->setFixedSize(300, 200);
    m_logo->setPixmap(QPixmap("../../images/fish.jpg").scaled(128, 128, Qt::KeepAspectRatio));
    m_logo->setAlignment(Qt::AlignCenter);
    m_name->setFixedSize(300, 50);
    m_name->setText("Call from default_name");
    m_name->setFont(babel::Client::info);
    m_denied->setFixedSize(150, 50);
    m_denied->setText("End call");
    m_denied->setFont(babel::Client::info);
    m_layout->addWidget(m_logo.get(), 0, 0, 2, 2, Qt::AlignTop);
    m_layout->addWidget(m_name.get(), 1, 0, 1, 2);
    m_layout->addWidget(m_denied.get(), 2, 0);
    setLayout(m_layout.get());

    QObject::connect(m_denied.get(), SIGNAL(clicked()), this, SLOT(deniedCall()));
}

void babel::CallingWindow::deniedCall()
{
    babel::Client::DeniedCall();
}