namespace cpp rtdb
service RTDB {
  oneway void store(1: i64 timstamp, 2: i64 value),
  list<i64> get(1: i64 timestamp, 2: i64 count)
}
