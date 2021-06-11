#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>

#include <sdbus-c++/sdbus-c++.h>

void onAdded(sdbus::Signal& signal)
{
    std::string result;
    signal >> result;
    
    std::cout << "Received signal with result of add operation " << result << std::endl;
}

int main(int argc, char **argv) 
{
    // Create proxy object for the sum object on the server side. Since here
    // we are creating the proxy instance without passing connection to it, the proxy
    // will create its own connection automatically, and it will be system bus connection.
    const char* destinationName = "org.sample.sum";
    const char* objectPath = "/org/sample/sum";
    auto sumProxy = sdbus::createProxy(destinationName, objectPath);
    
    // Let's subscribe for the 'sumd' signals
    const char* interfaceName = "org.sample.sum";
    sumProxy->registerSignalHandler(interfaceName, "added", &onAdded);
    sumProxy->finishRegistration();
    
    std::vector<int> numbers = {1, 2, 3};
    
    // Invoke sum on given interface of the object
    {
        auto method = sumProxy->createMethodCall(interfaceName, "add");
        method << numbers;
        auto reply = sumProxy->callMethod(method);
        
        std::string result;
        reply >> result;
        assert(result == "6");
    }
    
    // Invoke sum again, this time with no numbers and we shall get an error
    {
        auto method = sumProxy->createMethodCall(interfaceName, "add");
        try
        {
            auto reply = sumProxy->callMethod(method);
            assert(false);
        }
        catch(const sdbus::Error& e)
        {
            std::cerr << "Got add error " << e.getName() << " with message " << e.getMessage() << std::endl;
        }
    }
    
    // Give sufficient time to receive 'onAdded' signal from the first sum invocation
    sleep(1);

    return 0;
}