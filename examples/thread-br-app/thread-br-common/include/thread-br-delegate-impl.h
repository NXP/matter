/*
 *    Copyright (c) 2024 Project CHIP Authors
 *    Copyright 2025 NXP
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <app/clusters/thread-border-router-management-server/thread-br-delegate.h>

namespace chip {
namespace app {
namespace Clusters {
namespace ThreadBorderRouterManagement {

class ThreadBorderRouterDelegate : public Delegate
{
    CHIP_ERROR Init(AttributeChangeCallback * attributeChangeCallback) override;

    bool GetPanChangeSupported() override;

    void GetBorderRouterName(MutableCharSpan & borderRouterName) override;

    CHIP_ERROR GetBorderAgentId(MutableByteSpan & borderAgentId) override;

    uint16_t GetThreadVersion() override;

    bool GetInterfaceEnabled() override;

    CHIP_ERROR GetDataset(Thread::OperationalDataset & dataset, DatasetType type) override;

    void SetActiveDataset(const Thread::OperationalDataset & activeDataset, uint32_t sequenceNum,
                          ActivateDatasetCallback * callback) override;

    CHIP_ERROR CommitActiveDataset() override;
    CHIP_ERROR RevertActiveDataset() override;

    CHIP_ERROR SetPendingDataset(const Thread::OperationalDataset & pendingDataset) override;

private:
    static void ActivateActiveDataset(System::Layer *, void * context);

    Thread::OperationalDataset mActiveDataset;
    Thread::OperationalDataset mPendingDataset;

    AttributeChangeCallback * mAttributeChangeCallback;
    ActivateDatasetCallback * mActivateDatasetCallback = nullptr;
    uint32_t mActivateDatasetSequence;
};

} // namespace ThreadBorderRouterManagement
} // namespace Clusters
} // namespace app
} // namespace chip
