#include <iostream>

#include "SampleService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "sample.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class SampleServiceHandler : virtual public SampleServiceIf
{
public:
    SampleServiceHandler() = default;

    int32_t sum(const int32_t a, const int32_t b)
    {
        return sm.sum(a,b);
    }

private:
    SampleObject sm;
};

int main(int argc, char **argv)
{
    int port = 9090;
    ::std::shared_ptr<SampleServiceHandler> handler(new SampleServiceHandler());
    ::std::shared_ptr<TProcessor> processor(new SampleServiceProcessor(handler));
    ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}
