#include <android/binder_manager.h>
#include <aidl/devtitans/smartgas/ISmartgas.h>
#include <iostream>                             // std::cout e std::endl (end-line)

using namespace aidl::devtitans::smartgas;     // ISmartlamp
using namespace std;                            // std::shared_ptr
using namespace ndk;                            // ndk::SpAIBinder

int main() {
    shared_ptr<ISmartgas> service;
    service = ISmartgas::fromBinder(SpAIBinder(AServiceManager_getService("devtitans.smartgas.ISmartgas/default")));

    if (!service) {
        cout << "Erro acessando o serviço!" << endl;
        return 1;
    }

    int32_t _aidl_return;
    ScopedAStatus status = service->getConcentration(&_aidl_return);
    int concentration = static_cast<int32_t>(_aidl_return);
    cout << "Concentração: " << concentration << endl;

    return 0;
}
