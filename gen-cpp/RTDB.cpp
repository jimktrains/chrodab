/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "RTDB.h"

namespace rtdb {


RTDB_store_args::~RTDB_store_args() throw() {
}


uint32_t RTDB_store_args::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->timstamp);
          this->__isset.timstamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RTDB_store_args::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("RTDB_store_args");

  xfer += oprot->writeFieldBegin("timstamp", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->timstamp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->value);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}


RTDB_store_pargs::~RTDB_store_pargs() throw() {
}


uint32_t RTDB_store_pargs::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("RTDB_store_pargs");

  xfer += oprot->writeFieldBegin("timstamp", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64((*(this->timstamp)));
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64((*(this->value)));
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void RTDBClient::store(const int64_t timstamp, const int64_t value)
{
  send_store(timstamp, value);
}

void RTDBClient::send_store(const int64_t timstamp, const int64_t value)
{
  int32_t cseqid = 0;
  oprot_->writeMessageBegin("store", ::apache::thrift::protocol::T_ONEWAY, cseqid);

  RTDB_store_pargs args;
  args.timstamp = &timstamp;
  args.value = &value;
  args.write(oprot_);

  oprot_->writeMessageEnd();
  oprot_->getTransport()->writeEnd();
  oprot_->getTransport()->flush();
}

bool RTDBProcessor::dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext) {
  ProcessMap::iterator pfn;
  pfn = processMap_.find(fname);
  if (pfn == processMap_.end()) {
    iprot->skip(::apache::thrift::protocol::T_STRUCT);
    iprot->readMessageEnd();
    iprot->getTransport()->readEnd();
    ::apache::thrift::TApplicationException x(::apache::thrift::TApplicationException::UNKNOWN_METHOD, "Invalid method name: '"+fname+"'");
    oprot->writeMessageBegin(fname, ::apache::thrift::protocol::T_EXCEPTION, seqid);
    x.write(oprot);
    oprot->writeMessageEnd();
    oprot->getTransport()->writeEnd();
    oprot->getTransport()->flush();
    return true;
  }
  (this->*(pfn->second))(seqid, iprot, oprot, callContext);
  return true;
}

void RTDBProcessor::process_store(int32_t, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol*, void* callContext)
{
  void* ctx = NULL;
  if (this->eventHandler_.get() != NULL) {
    ctx = this->eventHandler_->getContext("RTDB.store", callContext);
  }
  ::apache::thrift::TProcessorContextFreer freer(this->eventHandler_.get(), ctx, "RTDB.store");

  if (this->eventHandler_.get() != NULL) {
    this->eventHandler_->preRead(ctx, "RTDB.store");
  }

  RTDB_store_args args;
  args.read(iprot);
  iprot->readMessageEnd();
  uint32_t bytes = iprot->getTransport()->readEnd();

  if (this->eventHandler_.get() != NULL) {
    this->eventHandler_->postRead(ctx, "RTDB.store", bytes);
  }

  try {
    iface_->store(args.timstamp, args.value);
  } catch (const std::exception&) {
    if (this->eventHandler_.get() != NULL) {
      this->eventHandler_->handlerError(ctx, "RTDB.store");
    }
    return;
  }

  if (this->eventHandler_.get() != NULL) {
    this->eventHandler_->asyncComplete(ctx, "RTDB.store");
  }

  return;
}

::boost::shared_ptr< ::apache::thrift::TProcessor > RTDBProcessorFactory::getProcessor(const ::apache::thrift::TConnectionInfo& connInfo) {
  ::apache::thrift::ReleaseHandler< RTDBIfFactory > cleanup(handlerFactory_);
  ::boost::shared_ptr< RTDBIf > handler(handlerFactory_->getHandler(connInfo), cleanup);
  ::boost::shared_ptr< ::apache::thrift::TProcessor > processor(new RTDBProcessor(handler));
  return processor;
}

void RTDBConcurrentClient::store(const int64_t timstamp, const int64_t value)
{
  send_store(timstamp, value);
}

void RTDBConcurrentClient::send_store(const int64_t timstamp, const int64_t value)
{
  int32_t cseqid = 0;
  ::apache::thrift::async::TConcurrentSendSentry sentry(&this->sync_);
  oprot_->writeMessageBegin("store", ::apache::thrift::protocol::T_ONEWAY, cseqid);

  RTDB_store_pargs args;
  args.timstamp = &timstamp;
  args.value = &value;
  args.write(oprot_);

  oprot_->writeMessageEnd();
  oprot_->getTransport()->writeEnd();
  oprot_->getTransport()->flush();

  sentry.commit();
}

} // namespace

