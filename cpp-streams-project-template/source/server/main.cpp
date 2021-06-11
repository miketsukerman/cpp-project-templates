#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <cstdio>

#include <spdlog/spdlog.h>

int main(int argc, char **argv) 
{
    spdlog::info("Starting server");

    try {
        asio::io_context io_context(1);

        asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto){ 
            spdlog::info("System signal received. Stopping...");
            io_context.stop(); 
        });

        io_context.run();
    } 
    catch(std::exception & e) 
    {
        spdlog::error(e.what());
    }

    return 0;
}