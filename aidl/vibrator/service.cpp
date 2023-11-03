/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Vibrator.h"

#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <android-base/logging.h>

using ::aidl::android::hardware::vibrator::Vibrator;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    // make the vibrator manager service
    std::shared_ptr<Vibrator> vibrator = ndk::SharedRefBase::make<Vibrator>();
    binder_status_t status = AServiceManager_addService(
            vibrator->asBinder().get(), Vibrator::makeServiceName("default").c_str());
    CHECK_EQ(status, STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE; // should not reach
}
