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
#include "RTDBCloneFactory.h"
#include "RTDBHandler.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace rtdb;

int main(int argc, char **argv) {
  const int workerCount = 4;
  const int port = 9090;

  //boost::shared_ptr<ThreadManager> threadManager =
  //    ThreadManager::newSimpleThreadManager(workerCount);
  //threadManager->threadFactory(boost::make_shared<PlatformThreadFactory>());
  //threadManager->start();

  //// This server allows "workerCount" connection at a time, and reuses threads
  //TThreadPoolServer server(boost::make_shared<RTDBProcessorFactory>(
  //                             boost::make_shared<RTDBCloneFactory>()),
  //                         boost::make_shared<TServerSocket>(port),
  //                         boost::make_shared<TBufferedTransportFactory>(),
  //                         boost::make_shared<TBinaryProtocolFactory>(),
  //                         threadManager);



 TThreadedServer server(
   boost::make_shared<RTDBProcessorFactory>(boost::make_shared<RTDBCloneFactory>()),
   boost::make_shared<TServerSocket>(port), 
   boost::make_shared<TBufferedTransportFactory>(),
   boost::make_shared<TBinaryProtocolFactory>());

  cout << "Starting server on port " << port << endl;
  server.serve();

  return 0;
}
