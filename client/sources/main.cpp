
#include <QtWidgets>
#include <string>

#include "Window.hpp"
#include "Handler.hpp"
#include "Codecs.hpp"
#include "Client.hpp"

#include "TcpClient.hpp"

int main(int argc, char **argv)
{
    try {
        if (argc != 3)
            throw std::invalid_argument("not enough args");
        tcp::Client::Address = std::string(argv[1]);
        tcp::Client::Port = static_cast<unsigned short>(std::stoul(argv[2]));
    }
    catch (...) {
        std::cerr << "Invalid arguments, you need to send an ip and an address" << std::endl;
        return 84;
    }

    babel::audio::Handler jaj;
    QApplication app(argc, argv);
    babel::Client::InitializeClient();

    return (app.exec());
}