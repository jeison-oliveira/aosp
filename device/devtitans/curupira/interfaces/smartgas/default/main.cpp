#include "smartgas_service.h"

using namespace aidl::devtitans::smartgas;
using namespace std;
using namespace ndk;

int main() {
    LOG(INFO) << "Iniciando Smartgas AIDL Service ...";

    ABinderProcess_setThreadPoolMaxThreadCount(0);

    shared_ptr<SmartgasService> smartgas_service = SharedRefBase::make<SmartgasService>();

    const string instance = std::string() + ISmartgas::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(smartgas_service->asBinder().get(), instance.c_str());
    CHECK(status == STATUS_OK);

    LOG(INFO) << "Smartgas AIDL Service iniciado com nome: " << instance;
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;                                   // Não deve chegar nunca aqui
}
