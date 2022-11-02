#pragma once

#include <android-base/logging.h>
#include <android/binder_process.h>
#include <android/binder_manager.h>

#include <aidl/devtitans/smartgas/BnSmartgas.h>

// #include "smartgas_lib.h"

// using namespace devtitans::smartgas;

namespace aidl::devtitans::smartgas {

    class SmartgasService : public BnSmartgas {
        public:
            ndk::ScopedAStatus connect(int32_t *_aidl_return) override;
            ndk::ScopedAStatus getSensorValue(int32_t *_aidl_return) override;

   //     private:
   //         Smartgas smartgas;
    };
}
