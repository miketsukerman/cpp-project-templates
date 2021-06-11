#include <sstream>

#include <crow/crow_all.h>
#include <spdlog/spdlog.h>

#include "sample.h"

constexpr auto port = 18080;

int main()
{
    spdlog::info("Starting REST server.");

    crow::SimpleApp app;
    SampleObject sm;

    CROW_ROUTE(app, "/")
    ([&sm]() {
        
        spdlog::info("Server got request!");

        std::stringstream strstream;

        strstream << sm.sum(1,2);

        return strstream.str();
    });

    app.port(port).multithreaded().run();
}
