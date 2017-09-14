#include "TpccClient.h"

using namespace tpcc;
int64_t TpccClient::startTrans(const int64_t trans_id, int64_t &ret) {

  StartRequest request;
  request.set_transid(trans_id);

  StartReply reply;
  ClientContext context;

  Status status = stub_->start(&context, request, &reply);

  if( status.ok() ) {
    ret = reply.transid();
    return 0;
  }
  else {
    cout << status.error_code() << ": " << status.error_message() << endl;
    return -1;
  }
}

int64_t TpccClient::endTrans(const int64_t transId) {
  return 0;
}

int64_t TpccClient::get(const int64_t transId, const int64_t tableId, const string &key, string &value) {
  return 0;
}

int64_t TpccClient::put(const int64_t transId, const int64_t tableId, const string &key, const string &value) {
  return 0;
}

void tpcc::runClient() {
  TpccClient tpcc(grpc::CreateChannel(
       "localhost:50051", grpc::InsecureChannelCredentials()));
  int64_t transid; 
  tpcc.startTrans(10, transid);
  cout<< "Start transaction: " << transid << std::endl;
}

