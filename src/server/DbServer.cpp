#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include "common/db.grpc.pb.h"
#include "DbServer.h"

using namespace std;
using namespace grpc;
using namespace dbinter;
using namespace dbserver;

Status DbServerImpl::put(ServerContext* context, const PutRequest* request,
    PutReply* reply) {
  reply->set_status(0);
  reply->set_reason("table not created");
  return Status::OK;
}

Status DbServerImpl::get(ServerContext* context, const GetRequest* request,
    GetReply* reply) { 
  int tableId = request->tableid();
  string key = request->key();

  string value = to_string(tableId) +  " " + key + " " + "record not found";
  reply->set_value(value);

  return Status::OK;
}

Status DbServerImpl::start(ServerContext* context, const StartRequest* request,
    StartReply* reply) {

  int64_t tId = request->transid();
  reply->set_transid(tId * 2);
  return Status::OK;  
}

Status DbServerImpl::commit(ServerContext* context, const CommitRequest* request, 
    CommitReply* reply) {
  int64_t tId = request->transid();
  reply->set_status(0); 
  reply->set_reason("committed");
  return Status::OK;
}

void dbserver::RunServer() {
  std::string addr("0.0.0.0:50051");
  DbServerImpl service;

  ServerBuilder builder;

  builder.AddListeningPort(addr, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());

  std::cout << "Server listening on " << addr << std::endl;

  server->Wait();
}
