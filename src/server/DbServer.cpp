#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include "common/db.grpc.pb.h"

using namespace std;
using namespace grpc;
using namespace dbinter;

class DbServerImpl final : public DbInterface::Service {

  Status put(ServerContext* context, const PutRequest* request,
      PutReply* reply) override {
    reply->set_status(0);
    reply->set_reason("table not created");
    return Status::OK;
  }

  Status get(ServerContext* context, const GetRequest* request,
      GetReply* reply) override { 
    int tableId = request->tableid();
    string key = request->key();

    string value = to_string(tableId) +  " " + key + " " + "record not found";
    reply->set_value(value);

   return Status::OK;
  }

  Status start(ServerContext* context, const StartRequest* request,
      StartReply* reply) override {

    int64_t tId = request->transid();
    reply->set_transid(tId * 2);
    return Status::OK;  
  }

  Status commit(ServerContext* context, const CommitRequest* request, 
      CommitReply* reply) override {
    int64_t tId = request->transid();
    reply->set_status(0); 
    reply->set_reason("committed");
    return Status::OK;
  }
};

void RunServer() {
  std::string addr("0.0.0.0:50051");
  DbServerImpl service;

  ServerBuilder builder;

  builder.AddListeningPort(addr, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());

  std::cout << "Server listening on " << addr << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}
