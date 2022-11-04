#include "smartgas_service.h"

namespace aidl::devtitans::smartgas {
    ndk::ScopedAStatus SmartgasService::connect(int32_t* _aidl_return) {
        *_aidl_return = 1; // this->smartgas.connect();
        LOG(INFO) << "connect(): " << *_aidl_return;
        return ndk::ScopedAStatus::ok();
    }

    ndk::ScopedAStatus SmartlampService::getConcentration(int32_t* _aidl_return) {
        *_aidl_return = 100; //this->smartgas.getConcentration();
        LOG(INFO) << "getConcentration(): " << *_aidl_return;
        return ndk::ScopedAStatus::ok();
    }
}
