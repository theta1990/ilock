#include "TpccClient.h"

using namespace tpcc;
int64_t TpccClient::startTrans(const int64_t trans_id) {

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

void tpcc::runClient() {
  TpccClient tpcc(grpc::CreateChannel(
       "localhost:50051", grpc::InsecureChannelCredentials()));
  int64_t transid = tpcc.startTrans(10);
  cout<< "Start transaction: " << transid << std::endl;
}

