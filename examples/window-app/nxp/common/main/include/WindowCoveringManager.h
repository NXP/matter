/*
 *    Copyright (c) 2023 Project CHIP Authors
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


#include <app/clusters/window-covering-server/window-covering-delegate.h>
#include <app/clusters/window-covering-server/window-covering-server.h>
#include <lib/core/CHIPError.h>
#include <cstdint>

#include <stdbool.h>
#include <stdint.h>

#include "AppEvent.h"
#include "FreeRTOS.h"
#include "timers.h" // provides FreeRTOS timer support


using namespace chip::app::Clusters::WindowCovering;

class WindowCoveringManager
{
public:
    struct AttributeUpdateData
    {
        chip::EndpointId mEndpoint;
        chip::AttributeId mAttributeId;
    };

    WindowCoveringManager();
    static WindowCoveringManager & WindowCoveringMgr()
    {
        static WindowCoveringManager sInstance;
        return sInstance;
    }


    void StartMove(WindowCoveringType aMoveType);
    void SetSingleStepTarget(OperationalState aDirection);
    void SetMoveType(WindowCoveringType aMoveType) { mCurrentUIMoveType = aMoveType; }
    WindowCoveringType GetMoveType() { return mCurrentUIMoveType; }
    void PositionUpdate(WindowCoveringType aMoveType);

    static void SchedulePostAttributeChange(chip::EndpointId aEndpoint, chip::AttributeId aAttributeId);
    static constexpr chip::EndpointId Endpoint() { return 1; };

private:
    void SetTargetPosition(OperationalState aDirection, chip::Percent100ths aPosition);
    static void UpdateOperationalStatus(WindowCoveringType aMoveType, OperationalState aDirection);
    static bool TargetCompleted(WindowCoveringType aMoveType, NPercent100ths aCurrent, NPercent100ths aTarget);
    static void StartTimer(WindowCoveringType aMoveType, uint32_t aTimeoutMs);
    static chip::Percent100ths CalculateSingleStep(WindowCoveringType aMoveType);
    static void DriveCurrentLiftPosition(intptr_t);
    static void DriveCurrentTiltPosition(intptr_t);
    static void MoveTimerTimeoutCallback(chip::System::Layer * systemLayer, void * appState);
    static void DoPostAttributeChange(intptr_t aArg);

    WindowCoveringType mCurrentUIMoveType;


    bool mInLiftMove{ false };
    bool mInTiltMove{ false };
};