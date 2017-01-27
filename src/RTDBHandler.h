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
#include <mutex>

#include "../gen-cpp/RTDB.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace rtdb;

class RTDBHandler : public RTDBIf {
private:
  static mutex pair_vec_gaurd;
  static vector<int64_t> timestamps;
  static vector<int64_t> values;
public:
  RTDBHandler() {}
  virtual void store(const int64_t timestamp, const int64_t value) 
  {
    lock_guard<mutex> lock(pair_vec_gaurd);
    timestamps.push_back(timestamp);
    values.push_back(value);
  }
  virtual void get(std::vector<int64_t> &_return, const int64_t timestamp, const int64_t count)
  {
    lock_guard<mutex> lock(pair_vec_gaurd); 
    size_t mid = 0;
    size_t high = timestamps.size();
    size_t low = 0;
    while(low < high)
    {
      mid = (high - low) / 2;
      if (timestamps[mid] < timestamp) {
        high = mid - 1;
      }
      else if (timestamps[mid] > timestamp) {
        low = mid + 1;
      }
      else {
        break;
      }
    }
    for(size_t i = mid, cnt = 0; i < timestamps.size() && cnt < count; i++, cnt++)
    {
      _return.push_back(values[i]);
    }
  }
};

vector<int64_t> RTDBHandler :: timestamps = vector<int64_t>();
vector<int64_t> RTDBHandler :: values = vector<int64_t>();
mutex RTDBHandler :: pair_vec_gaurd;
