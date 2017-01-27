#pragma once

#include <thrift/TToString.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <boost/make_shared.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "../gen-cpp/RTDB.h"
#include "RTDBHandler.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace rtdb;

class RTDBCloneFactory : virtual public RTDBIfFactory {
public:
  virtual ~RTDBCloneFactory() {}
  virtual RTDBIf *
  getHandler(const ::apache::thrift::TConnectionInfo &connInfo) {
    boost::shared_ptr<TSocket> sock =
        boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
    cout << "Incoming connection\n";
    cout << "\tSocketInfo: " << sock->getSocketInfo() << "\n";
    cout << "\tPeerHost: " << sock->getPeerHost() << "\n";
    cout << "\tPeerAddress: " << sock->getPeerAddress() << "\n";
    cout << "\tPeerPort: " << sock->getPeerPort() << "\n";
    return new RTDBHandler;
  }
  virtual void releaseHandler(RTDBIf *handler) { delete handler; }
};
