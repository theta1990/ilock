#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include "common/db.grpc.pb.h"

using namespace std;
using namespace grpc;
using namespace dbinter;

namespace dbserver {

  class DbServerImpl final : public DbInterface::Service {

    Status put(ServerContext* context, const PutRequest* request, PutReply* reply) override;

    Status get(ServerContext* context, const GetRequest* request, GetReply* reply) override;

    Status start(ServerContext* context, const StartRequest* request, StartReply* reply) override;

    Status commit(ServerContext* context, const CommitRequest* request, CommitReply* reply) override;
  };

  void RunServer();
}

