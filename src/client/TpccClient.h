#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include "common/db.grpc.pb.h"

using namespace std;
using namespace grpc;
using namespace dbinter;

namespace tpcc {
  class TpccClient {
    public:
      TpccClient(shared_ptr<Channel> channel) 
        : stub_(DbInterface::NewStub(channel)) {}

      int64_t startTrans(const int64_t transId, int64_t &ret);

      int64_t endTrans(const int64_t transId);

      int64_t get(const int64_t transId, const int64_t tableId, const string &key, string &value);

      int64_t put(const int64_t transId, const int64_t tableId, const string &key, const string &value);

    private:
      std::unique_ptr<DbInterface::Stub>  stub_;
  };

  void runClient();
}
