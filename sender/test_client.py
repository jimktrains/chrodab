#!/usr/bin/env python3

import sys
import glob
sys.path.append('gen-py')

from rtdb import RTDB
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

# Make socket
transport = TSocket.TSocket('localhost', 9090)

# Buffering is critical. Raw sockets are very slow
transport = TTransport.TBufferedTransport(transport)

# Wrap in a protocol
protocol = TBinaryProtocol.TBinaryProtocol(transport)

# Create a client to use the protocol encoder
client = RTDB.Client(protocol)

# Connect!
transport.open()

client.store(10, 5);

print(client.get(10, 1))
