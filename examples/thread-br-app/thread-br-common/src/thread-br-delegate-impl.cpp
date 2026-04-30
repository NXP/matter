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

#include <thread-br-delegate-impl.h>
#include <app/clusters/thread-border-router-management-server/thread-border-router-management-server.h>
#include <app/server/Server.h>
#include <lib/core/CHIPEncoding.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/Span.h>
#include <lib/support/ThreadOperationalDataset.h>
#include <platform/CHIPDeviceLayer.h>
#include <lib/support/logging/CHIPLogging.h>

#include <optional>

using namespace chip;
using namespace chip::literals;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::DeviceLayer;
using namespace chip::app::Clusters::ThreadBorderRouterManagement;

CHIP_ERROR ThreadBorderRouterDelegate::Init(AttributeChangeCallback * attributeChangeCallback)
{
    mAttributeChangeCallback = attributeChangeCallback;
    CHIP_ERROR err = ThreadStackMgr().InitThreadStack();
    VerifyOrReturnError(err == CHIP_NO_ERROR, err);
    return CHIP_NO_ERROR;
}

bool ThreadBorderRouterDelegate::GetPanChangeSupported() { return false; }

void ThreadBorderRouterDelegate::GetBorderRouterName(MutableCharSpan & borderRouterName)
{
    CopyCharSpanToMutableCharSpan("NXP_iMX_OTBR-Agent"_span, borderRouterName);
}

CHIP_ERROR ThreadBorderRouterDelegate::GetBorderAgentId(MutableByteSpan & borderAgentId)
{
    static constexpr uint8_t kBorderAgentId[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                                                  0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
    VerifyOrReturnError(borderAgentId.size() == 16, CHIP_ERROR_INVALID_ARGUMENT);
    return CopySpanToMutableSpan(ByteSpan(kBorderAgentId), borderAgentId);
}

uint16_t ThreadBorderRouterDelegate::GetThreadVersion() { return /* Thread 1.3.1 */ 5; }

bool ThreadBorderRouterDelegate::GetInterfaceEnabled()
{
    return ThreadStackMgr().IsThreadEnabled();
}

CHIP_ERROR ThreadBorderRouterDelegate::GetDataset(Thread::OperationalDataset & dataset, DatasetType type)
{
    switch (type)
    {
    case DatasetType::kActive:
    {
        Thread::OperationalDataset source;
        if (GetInterfaceEnabled())
        {
            CHIP_ERROR err = ThreadStackMgr().GetThreadProvision(source);
            VerifyOrReturnError(err == CHIP_NO_ERROR, CHIP_ERROR_NOT_FOUND);
            mActiveDataset = source;
        }
        VerifyOrReturnError(!source.IsEmpty(), CHIP_ERROR_NOT_FOUND);
        return dataset.Init(source.AsByteSpan());
    }
    case DatasetType::kPending:
        return CHIP_ERROR_NOT_FOUND;
        break;
    default:
        return CHIP_ERROR_INVALID_ARGUMENT;
    }
}

void ThreadBorderRouterDelegate::SetActiveDataset(const Thread::OperationalDataset & activeDataset, uint32_t sequenceNum,
                                                    ActivateDatasetCallback * callback)
{
    if (mActivateDatasetCallback != nullptr || GetInterfaceEnabled())
    {
        callback->OnActivateDatasetComplete(sequenceNum, CHIP_ERROR_INCORRECT_STATE);
        return;
    }

    CHIP_ERROR err = mActiveDataset.Init(activeDataset.AsByteSpan());
    if (err != CHIP_NO_ERROR)
    {
        callback->OnActivateDatasetComplete(sequenceNum, err);
        return;
    }

    mActivateDatasetCallback = callback;
    mActivateDatasetSequence = sequenceNum;
    DeviceLayer::SystemLayer().ScheduleWork(ActivateActiveDataset, this);
}

CHIP_ERROR ThreadBorderRouterDelegate::CommitActiveDataset() { return CHIP_NO_ERROR; }
CHIP_ERROR ThreadBorderRouterDelegate::RevertActiveDataset() { return CHIP_ERROR_NOT_IMPLEMENTED; }

CHIP_ERROR ThreadBorderRouterDelegate::SetPendingDataset(const Thread::OperationalDataset & pendingDataset)
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

void ThreadBorderRouterDelegate::ActivateActiveDataset(System::Layer *, void * context)
{
    auto * self                    = static_cast<ThreadBorderRouterDelegate *>(context);
    auto * callback                = self->mActivateDatasetCallback;
    auto sequenceNum               = self->mActivateDatasetSequence;
    CHIP_ERROR err = ThreadStackMgr().AttachToThreadNetwork(self->mActiveDataset, nullptr);
    self->mActivateDatasetCallback = nullptr;
    callback->OnActivateDatasetComplete(sequenceNum, err);
}
