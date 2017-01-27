To build:

    make clean build
    lldb ./target/rtdb-server.exe
    r
    # in another tab
    cd sender
    make clean build
    python3 test_client.py

The problem:

		* thread #2: tid = 0x95475, 0x00007fff9a496bb8 libc++abi.dylib`vtable for __cxxabiv1::__class_type_info + 16, stop reason = EXC_BAD_ACCESS (code=2, address=0x7fff9a496bb8)
			* frame #0: 0x00007fff9a496bb8 libc++abi.dylib`vtable for __cxxabiv1::__class_type_info + 16
				frame #1: 0x000000010001004e rtdb-server.exe`rtdb::RTDBProcessor::process_get(this=0x00000001005000f0, seqid=0, iprot=0x0000000101800590, oprot=0x00000001018005f0, callContext=0x0000000000000000) + 830 at RTDB.cpp:499
				frame #2: 0x000000010000f36d rtdb-server.exe`rtdb::RTDBProcessor::dispatchCall(this=0x00000001005000f0, iprot=0x0000000101800590, oprot=0x00000001018005f0, fname="get", seqid=0, callContext=0x0000000000000000) + 1757 at RTDB.cpp:435
				frame #3: 0x0000000100011e89 rtdb-server.exe`apache::thrift::TDispatchProcessor::process(this=0x00000001005000f0, in=shared_ptr<apache::thrift::protocol::TProtocol> @ 0x000070000d03be18, out=shared_ptr<apache::thrift::protocol::TProtocol> @ 0x000070000d03be08, connectionContext=0x0000000000000000) + 489 at TDispatchProcessor.h:121
				frame #4: 0x000000010010ee45 libthrift-0.10.0.dylib`apache::thrift::server::TConnectedClient::run() + 341
				frame #5: 0x000000010011271f libthrift-0.10.0.dylib`apache::thrift::server::TThreadedServer::TConnectedClientRunner::run() + 27
				frame #6: 0x0000000100113cad libthrift-0.10.0.dylib`apache::thrift::concurrency::PthreadThread::threadMain(void*) + 109
				frame #7: 0x00007fff91ac8aab libsystem_pthread.dylib`_pthread_body + 180
				frame #8: 0x00007fff91ac89f7 libsystem_pthread.dylib`_pthread_start + 286
				frame #9: 0x00007fff91ac81fd libsystem_pthread.dylib`thread_start + 13
		(lldb) up
		frame #1: 0x000000010001004e rtdb-server.exe`rtdb::RTDBProcessor::process_get(this=0x00000001005000f0, seqid=0, iprot=0x0000000101800590, oprot=0x00000001018005f0, callContext=0x0000000000000000) + 830 at RTDB.cpp:499
			 496 	
			 497 	  RTDB_get_result result;
			 498 	  try {
		-> 499 	    iface_->get(result.success, args.timestamp, args.count);
			 500 	    result.__isset.success = true;
			 501 	  } catch (const std::exception& e) {
			 502 	    if (this->eventHandler_.get() != NULL) {
		(lldb) down
		frame #0: 0x00007fff9a496bb8 libc++abi.dylib`vtable for __cxxabiv1::__class_type_info + 16
		libc++abi.dylib`vtable for __cxxabiv1::__class_type_info:
		->  0x7fff9a496bb8 <+16>: movl   $0xff904c42, %edx         ; imm = 0xFF904C42 
				0x7fff9a496bbd <+21>: jg     0x7fff9a496bbf            ; <+23>
				0x7fff9a496bbf <+23>: addb   %al, %al
