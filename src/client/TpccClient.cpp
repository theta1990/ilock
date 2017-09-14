#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "common/db.grpc.pb.h"

using namespace std;
using namespace grpc;
using namespace dbinter;

class TpccClient {
  public:
    TpccClient(shared_ptr<Channel> channel) 
      : stub_(DbInterface::NewStub(channel)) {}

    int64_t start(const int64_t trans_id) {
      
      StartRequest request;
      request.set_transid(trans_id);

      StartReply reply;

      ClientContext context;

      Status status = stub_->start(&context, request, &reply);

      if( status.ok() ) {
        return reply.transid();
      }
      else {
        cout << status.error_code() << ": " << status.error_message() << endl;
        return -1;
      }
    }
  private:
    std::unique_ptr<DbInterface::Stub>  stub_;
};

int main(int argc, char** argv) {
  TpccClient tpcc(grpc::CreateChannel(
       "localhost:50051", grpc::InsecureChannelCredentials()));
  int64_t transid = tpcc.start(10);
  cout<< "Start transaction: " << transid << std::endl;
  return 0;
}
