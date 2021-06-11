#include <cstdio>

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>

#include <sdbus-c++/sdbus-c++.h>

#include <spdlog/spdlog.h>

#include "sample.h"

sdbus::IObject* g_sum{};

void sum(sdbus::MethodCall call)
{
    // Deserialize the collection of numbers from the message
    std::vector<int> numbers;
    call >> numbers;
    
    // Deserialize separator from the message
    std::string separator;
    call >> separator;
    
    // Return error if there are no numbers in the collection
    if (numbers.empty()) 
    {
        throw sdbus::Error("org.sample.sum.Error", "No numbers provided");
    }

    SampleObject sm;

    auto result = sm.sum(numbers);
    
    // Serialize resulting string to the reply and send the reply to the caller
    auto reply = call.createReply();
    reply << result;
    reply.send();
    
    // Emit 'added' signal
    constexpr auto interfaceName = "org.sample.sum";
    auto signal = g_sum->createSignal(interfaceName, "added");
    signal << result;
    g_sum->emitSignal(signal);    
}

int main(int argc, char **argv) 
{
    spdlog::info("Starting server");

    try {
        // Create D-Bus connection to the system bus and requests name on it.
        constexpr auto serviceName = "org.sample.sum";
        auto connection = sdbus::createSystemBusConnection(serviceName);

        // Create sum D-Bus object.
        constexpr auto objectPath = "/org/sample/sum";
        auto sum_obj = sdbus::createObject(*connection, objectPath);
        
        g_sum = sum_obj.get();
        
        // Register D-Bus methods and signals on the sum object, and exports the object.
        constexpr auto interfaceName = "org.sample.sum";
        sum_obj->registerMethod(interfaceName, "add", "ais", "s", &sum);
        sum_obj->registerSignal(interfaceName, "added", "s");
        sum_obj->finishRegistration();

        // Run the I/O event loop on the bus connection.
        connection->enterEventLoop();
    } 
    catch(std::exception & e) 
    {
        spdlog::error(e.what());
    }

    return 0;
}