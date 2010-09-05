#ifndef ROOTSERVER_HPP
#define ROOTSERVER_HPP

#include "Root.hpp"

namespace Engine{

class RootServer : public Root{
public:
    void StartMainLoop();

    const NetworkManager* GetNetworkManager() const;

private:
    NetworkServer mNetworkServer;
};

}

#endif
