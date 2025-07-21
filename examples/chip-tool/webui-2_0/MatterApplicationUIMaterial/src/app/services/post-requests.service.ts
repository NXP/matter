import { AppDialogService } from './app-dialog.service';
// Post requests service

import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable, ObservableLike, catchError, throwError } from 'rxjs';
import { HttpHeaders } from '@angular/common/http';
import { API_BASE_URL } from '../../api_addresses';

@Injectable({
  providedIn: 'root'
})

export class PostRequestsService {

  constructor(private httpClient: HttpClient, private appDialogService: AppDialogService) { }
  serverUrl: string = API_BASE_URL;

  sendPairBLEThreadCommand(deviceId: string, pinCode: string, nodeAlias: string, dataset: string, discriminator: string): Observable<string> {
    const data = {
      nodeId: deviceId,
      pinCode: pinCode,
      type: "ble-thread",
      nodeAlias: nodeAlias ? nodeAlias : "No Value",
      dataset: dataset,
      discriminator: discriminator
    };

    console.log(
      `Sending pairing request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    );

    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendPairBLEWifiCommand(deviceId: string, pinCode: string, nodeAlias: string, net_ssid: string, net_pass: string, discriminator: string): Observable<string> {
    const data = {
      nodeId: deviceId,
      pinCode: pinCode,
      type: "ble-wifi",
      nodeAlias: nodeAlias ? nodeAlias : "No Value",
      ssId: net_ssid,
      password: net_pass,
      discriminator: discriminator
    };
    console.log(
      `Sending pairing request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    )
    // Send the pairing request to the server
    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendPairOnNetworkCommand(deviceId: string, passCode: string, nodeAlias: string): Observable<string> {
    const data = {
      nodeId: deviceId,
      pinCode: passCode,
      type: "onnetwork",
      nodeAlias: nodeAlias
    };

    console.log(
      `Sending pairing request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    )

    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendPairQRCodeCommand(deviceId: string, payload: string, nodeAlias: string): Observable<string> {
    const data = {
      nodeId: deviceId,
      payload: payload,
      type: "qrcode",
      nodeAlias: nodeAlias
    };

    console.log(
      `Sending pairing request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    )

    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendUnpairCommand(nodeAlias: string, deviceId: string): Observable<string> {
    const data = {
      nodeAlias: nodeAlias,
      nodeId: deviceId,
      type: "unpair"
    };

    console.log(
      `Sending pairing unpair request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    )

    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendPairOnnetworkJointFabricBCMOnboarding(deviceId: string, passCode: string, nodeAlias: string) {
    const data = {
      nodeId: deviceId,
      passCode: passCode,
      type: "onnetwork-joint-fabric",
      nodeAlias: nodeAlias ? nodeAlias : "No Value"
    };

    console.log(
      `Sending pairing request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    )

    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }
  sendPairOnnetworkJointFabricECMOnboarding(deviceId: string, passCode: string) {
    const data = {
      nodeId: deviceId,
      passCode: passCode,
      type: "code-joint-fabric",
      nodeAlias: "No Value"
    };

    console.log(
      `Sending pairing request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    )

    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendPairEthernetCommand(deviceId: string, pinCode: string, discriminator: string, ip_address: string, port: string): Observable<string> {
    const data = {
      nodeId: deviceId,
      pinCode: pinCode,
      type: "ethernet",
      discriminator: discriminator,
      ip_address: ip_address,
      port: port,
      nodeAlias: "No Value"
    };
    console.log(
      `Sending pairing request to ${this.serverUrl}/pairing with data: ${JSON.stringify(data)}`
    );

    return this.httpClient.post<string>(
      `${this.serverUrl}/pairing`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendForgetDeviceCommand(deviceName: string): Observable<string> {
    const data = {
      nodeAlias: deviceName
    };
    console.log(
      `Sending delete_storageNode request to ${this.serverUrl}/delete_storageNode with data: ${JSON.stringify(data)}`
    );

    return this.httpClient.post<string>(
      `${this.serverUrl}/delete_storageNode`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending pairing request', error);
        return throwError(error.message)
      })
    );
  }

  sendOnOffToggleEndpointCommand(deviceId: string, endPointId: string, type: string): Observable<string> {
    const data = {
      nodeAlias: "No Value",
      nodeId: deviceId,
      endPointId: endPointId,
      type: type
    };
    console.log(
      `Sending on/off toggle request to ${this.serverUrl}/onoff with data: ${JSON.stringify(data)}`
    );

    return this.httpClient.post<string>(
      `${this.serverUrl}/onoff`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending on/off toggle request', error);
        return throwError(error.message)
      })
    );
  }

  sendOnOffReadEndpointCommand(deviceId: string, endPointId: string): Observable<string> {
    const data = {
      nodeAlias: "No Value",
      nodeId: deviceId,
      endPointId: endPointId,
    };
    console.log(
      `Sending on/off read request to ${this.serverUrl}/onoff with data: ${JSON.stringify(data)}`
    );

    return this.httpClient.post<string>(
      `${this.serverUrl}/onoff_report`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending on/off read request', error);
        return throwError(error.message)
      })
    );
  }

  sendBasicInformationCommand(nodeAlias: string, nodeId: string, endPointId: string) {
    const data = {
      nodeAlias: nodeAlias,
      nodeId: nodeId,
      endPointId: endPointId,
    };
    console.log(
      `Sending edit request to ${this.serverUrl}/basicinformation with data: ${JSON.stringify(data)}`
    );

    return this.httpClient.post<string>(
      `${this.serverUrl}/basicinformation`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sending edit command', error);
        return throwError(error.message)
      })
    );
  }

  // For Open Commissioning Window with BCM/ECM
  sendOpenCommissioningWindowWithBCM(nodeId: string, windowTimeout: string, option: string, iteration: string, discriminator: string): Observable<string> {
    if (nodeId.length == 0 || windowTimeout.length == 0 || option.length == 0 || iteration.length == 0 || discriminator.length == 0) {
      return throwError("Please fill in all the input fields");
    }
    const data = {
      nodeId: nodeId,
      option: option,
      windowTimeout: windowTimeout,
      iteration: iteration,
      discriminator: discriminator,
    }
    if (data.option == "0") {
      console.log(`Sending Pairing open-commissioning window with BCM option to ${this.serverUrl}/multiadmin with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/multiadmin`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending multiadmin pairing BCM request', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("The option field is not 0, please correct the command or send with ECM (option = 1)")
    }
  }

  // Delete storage node
  sendDeleteStorageNode(nodeAlias: string) {
    if (nodeAlias.length == 0) {
      return throwError("Please fill in all the input fields")
    }
    const data = {
      nodeAlias: nodeAlias
    }
    console.log("Removing stoage node with alias: " + nodeAlias)
    return this.httpClient.post<string>(
      `${this.serverUrl}/delete_storageNode`, JSON.stringify(data)
    ).pipe(
      catchError((error: any) => {
        console.error('Error sendig delete storageNode request', error);
        return throwError(error.message)
      })
    );
  }

  sendOpenCommissioningWindowWithECM(nodeId: string, windowTimeout: string, option: string, iteration: string, discriminator: string): Observable<string> {
    if (nodeId.length == 0 || windowTimeout.length == 0 || option.length == 0 || iteration.length == 0 || discriminator.length == 0) {
      return throwError("Please fill in all the input fields");
    }
    const data = {
      nodeId: nodeId,
      option: option,
      windowTimeout: windowTimeout,
      iteration: iteration,
      discriminator: discriminator,
    }
    if (data.option == "1") {
      console.log(`Sending Pairing open-commissioning window with ECM option to ${this.serverUrl}/multiadmin with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/multiadmin`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending multiadmin pairing ECM request', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("The option field is not 1, please correct the command or send with BCM (option = 0)")
    }
  }

  // For EEVSE

  sendEEVSEEnableChargingCommand(nodeId: string, nodeAlias: string, endpointId: string, minimumChargeCurrent: string, maximumChargeCurrent: string, commandType: string, chargingEnabledUntil?: string): Observable<string> {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && minimumChargeCurrent.length > 0 && maximumChargeCurrent.length > 0;
    }

    const data = {
      nodeAlias: nodeAlias,
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType,
      chargingEnabledUntil: chargingEnabledUntil ? chargingEnabledUntil : "null",
      minimumChargeCurrent: minimumChargeCurrent,
      maximumChargeCurrent: maximumChargeCurrent
    }

    if (fieldCheck()) {
      console.log(`Sending enable charging EEVSE command to ${this.serverUrl}/eevse_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/eevse_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE enable charging command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId, chargingEnabledUntil, minimumChargeCurrent, maximumChargeCurrent")
      }
    }

  sendEEVSEWriteUserMaximumChargeCurrentCommand(nodeId: string, nodeAlias: string, endpointId: string, userMaximumChargeCurrent: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && userMaximumChargeCurrent.length > 0;
    }
    const data = {
      nodeAlias: nodeAlias,
      nodeId: nodeId,
      endPointId: endpointId,
      userMaximumChargeCurrent: userMaximumChargeCurrent,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending write user maximum charge current EEVSE command to ${this.serverUrl}/eevse_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/eevse_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE write max user charge current command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId, usermaximumchargecurrent)")
    }
  }

  sendEEVSEDisableChargingCommand(nodeId: string, nodeAlias: string, endpointId: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0
    }

    const data = {
      nodeAlias: nodeAlias,
      nodeId: nodeId,
      endPointId: endpointId,
      type: "disable"
    }

    if (fieldCheck()) {
      console.log(`Sending EEVSE disable charging command to ${this.serverUrl}/eevse_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/eevse_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE disable charging command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId)")
    }
  }


  sendEEVSEReadCommand(nodeId: string, endpointId: string, commandType: string, nodeAlias?: string) {
    var fieldCheckCurrentState: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "state"
    }

    var fieldCheckSupplyState: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "supplystate"
    }

    var fieldCheckFaultState: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "faultstate"
    }

    var fieldCheckChargingEnabledUntil: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "chargingenableduntil"
    }

    var fieldCheckMinimumChargeCurrent: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "minimumchargecurrent"
    }

    var fieldCheckMaximumChargeCurrent: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "maximumchargecurrent"
    }

    var fieldCheckSessionId: Function = () => {

      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "sessionid"
    }

    var fieldCheckSessionDuration: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "sessionduration"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      nodeAlias: nodeAlias ? nodeAlias : "No Value",
      type: commandType
    }

    if (fieldCheckCurrentState() || fieldCheckSupplyState() || fieldCheckFaultState() || fieldCheckChargingEnabledUntil() || fieldCheckMinimumChargeCurrent() || fieldCheckMaximumChargeCurrent() || fieldCheckSessionId() || fieldCheckSessionDuration()) {
      console.log(`Sending EEVSE read command to ${this.serverUrl}/eevse_read with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/eevse_read`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE read command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }


  // For Media control read / control
  sendPlayAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "play"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media play command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media Play command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendPauseAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "pause"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media pause command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media pause command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendStopAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "stop"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media stop command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media stop command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendStartOverAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "startover"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media startover command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media start-over command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendPreviousAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "previous"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media previous command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media previous command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendNextAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "next"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media next command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media next command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendRewindAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "rewind"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media rewind command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media rewind command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendFastForwardAppMediaControlCommmand(nodeId: string, endpointId: string, commandType: string) {
    var fieldCheck: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "fastforward"
    }

    const data = {
      nodeId: nodeId,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheck()) {
      console.log(`Sending Media fastforward command to ${this.serverUrl}/media_control with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_control`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media fastforward command', error);
          return throwError(error.message);
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendOnMediaReadMediaControlCommand(nodeId: string, endpointId: string, commandType: string, nodeAlias: string) {
    var fieldCheckCurrentState: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "currentstate" && nodeAlias.length > 0
    }

    var fieldCheckStartTime: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "starttime" && nodeAlias.length > 0
    }

    var fieldCheckDuration: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "duration" && nodeAlias.length > 0
    }

    var fieldCheckSampledPosition: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "sampledposition" && nodeAlias.length > 0
    }

    var fieldCheckPlaybackSpeedPosition: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0 && commandType.length > 0 && commandType.toLowerCase() == "playbackspeed" && nodeAlias.length > 0
    }


    const data = {
      nodeId: nodeId,
      nodeAlias: nodeAlias,
      endPointId: endpointId,
      type: commandType
    }

    if (fieldCheckCurrentState() || fieldCheckStartTime() || fieldCheckDuration() || fieldCheckSampledPosition() || fieldCheckPlaybackSpeedPosition()) {
      console.log(`Sending Media read command to ${this.serverUrl}/media_read with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/media_read`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending Media read command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (nodeId, endpointId) and select the correct type")
    }
  }

  sendPayloadParsePostRequest(payload: string) {
    // Returns passcode, result
    var fieldCheck: Function = () => {
      return payload.length > 0
    }

    const data = {
      payload: payload
    }

    if (fieldCheck()) {
      console.log(`Sending Media read command to ${this.serverUrl}/payload_parse with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/payload_parse`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending payload parse command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields (payload).")
    }

  }

  sendTBRMCommissioningCommand(type: string, expLength: string, breadcrumb: string, nodeId: string, endpointId: string) {
    var fieldCheckArmFailsafe: Function = () => {
      return type.length > 0 && expLength.length > 0 && breadcrumb.length > 0 && nodeId.length > 0 && endpointId.length > 0 && type === "armfailsafe"
    }

    var fieldCheckCommissioningComplete: Function = () => {
      return type.length > 0 && nodeId.length > 0 && endpointId.length > 0 && type === "commissioningcomplete"
    }


    if (fieldCheckArmFailsafe() && !fieldCheckCommissioningComplete()) {
      const data = {
        type: type,
        expiryLengthSeconds: expLength,
        breadcrumb: breadcrumb,
        nodeId: nodeId,
        endPointId: endpointId
      }

      console.log(`Sending TBRM commissioning arm failsafe command to ${this.serverUrl}/generalcommissioning with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/generalcommissioning`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending TBRM arm failsafe commissioning command', error);
          return throwError(error.message)
        })
      );

    } else if (fieldCheckCommissioningComplete() && !fieldCheckArmFailsafe()) {
      const data = {
        type: type,
        nodeId: nodeId,
        endPointId: endpointId
      }

      console.log(`Sending TBRM commissioning complete command to ${this.serverUrl}/generalcommissioning with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/generalcommissioning`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending TBRM commissioning complete command', error);
          return throwError(error.message)
        })
      );

    } else {
      return throwError("Please complete all the missing input fields")
    }

  }

  sendTBRMCommissioningSetActiveDatasetCommand(dataset: string, nodeId: string, endpointId: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return dataset.length > 0 && nodeId.length > 0 && endpointId.length > 0
    }

    if (fieldCheckSetActiveDataset()) {
      const data = {
        type: "setactivedatasetrequest",
        dataset: dataset,
        nodeId: nodeId,
        endPointId: endpointId
      }

      console.log(`Sending TBRM commissioning set active dataset command to ${this.serverUrl}/threadborderroutermanagement with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/threadborderroutermanagement`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending TBRM set active dataset commissioning command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all the missing input fields")
    }
  }

  sendMediaControlLaunchCommand(nodeId: string, endpointId: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        endPointId: endpointId,
        type: "launch",
        launchConf: {
          catalogVendorID: "123",
          applicationID: "exampleid"
        }
      }

      console.log(`Sending media launch request to ${this.serverUrl}/launcher with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/launcher`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending media launch command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all missing fields")
    }
  }

  sendMediaControlStopCommand(nodeId: string, endpointId: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && endpointId.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        endPointId: endpointId,
        type: "stop",
        launchConf: {
          catalogVendorID: "123",
          applicationID: "exampleid"
        }
      }

      console.log(`Sending media launch request to ${this.serverUrl}/launcher with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/launcher`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending media launch command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all missing fields")
    }
  }

  sendEEVSEClearChargingDemandEvent(nodeId: string, nodeAlias: string | undefined, key: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && key.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        nodeAlias: nodeAlias ? nodeAlias : "No Value",
        key: key,
        type: "triggerChargeDemandClear",
      }
      console.log(`Sending request to ${this.serverUrl}/event_trigger with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/event_trigger`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE command', error);
          return throwError(error.message)
        })
      );

    } else {
      return throwError("Please complete all missing fields")
    }
  }
  sendEEVSETriggerChargingDemandEvent(nodeId: string, nodeAlias: string | undefined, key: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && key.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        nodeAlias: nodeAlias ? nodeAlias : "No Value",
        key: key,
        type: "triggerChargeDemand",
      }
      console.log(`Sending request to ${this.serverUrl}/event_trigger with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/event_trigger`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE command', error);
           return throwError(error.message)
        })
      );

    } else {
      return throwError("Please complete all missing fields")
    }
  }
  sendEEVSEClearPluggedinEvent(nodeId: string, nodeAlias: string | undefined, key: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && key.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        nodeAlias: nodeAlias ? nodeAlias : "No Value",
        key: key,
        type: "triggerPluggedinClear",
      }
      console.log(`Sending request to ${this.serverUrl}/event_trigger with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/event_trigger`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE command', error);
          return throwError(error.message)
        })
      );

    } else {
      return throwError("Please complete all missing fields")
    }
  }
  sendEEVSEStartPluggedinEvent(nodeId: string, nodeAlias: string | undefined, key: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && key.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        nodeAlias: nodeAlias ? nodeAlias : "No Value",
        key: key,
        type: "triggerPluggedin",
      }
      console.log(`Sending request to ${this.serverUrl}/event_trigger with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/event_trigger`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE command', error);
          return throwError(error.message)
        })
      );

    } else {
      return throwError("Please complete all missing fields")
    }
  }
  sendEEVSEClearTriggerEvent(nodeId: string, nodeAlias: string | undefined, key: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && key.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        nodeAlias: nodeAlias ? nodeAlias : "No Value",
        key: key,
        type: "triggerBasicClear",
      }
      console.log(`Sending request to ${this.serverUrl}/event_trigger with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/event_trigger`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE command', error);
          return throwError(error.message)
        })
      );

    } else {
      return throwError("Please complete all missing fields")
    }
  }
  sendEEVSEStartTriggerEvent(nodeId: string, nodeAlias: string | undefined, key: string) {
    var fieldCheckSetActiveDataset: Function = () => {
      return nodeId.length > 0 && key.length > 0
    }
    if (fieldCheckSetActiveDataset()) {
      const data = {
        nodeId: nodeId,
        nodeAlias: nodeAlias ? nodeAlias : "No Value",
        key: key,
        type: "triggerBasic",
      }
      console.log(`Sending request to ${this.serverUrl}/event_trigger with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/event_trigger`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending EEVSE command', error);
          return throwError(error.message)
        })
      );

    } else {
      return throwError("Please complete all missing fields")
    }
  }

  sendWriteACLBindingCommand(lightNodeId: string, switchNodeId: string, aclEndpointId: string) {
    var fieldChechSetActiveDataset: Function = () => {
      return lightNodeId.length > 0 && switchNodeId.length > 0 && aclEndpointId.length > 0
    }
    if (fieldChechSetActiveDataset()) {
      const data = {
        aclConf1: {
          fabricIndex: "1",
          privilege: "5",
          authMode: "2",
          subjects: "[112233]",
          targets: "null"
        },
        aclConf2: {
          fabricIndex: "1",
          privilege: "3",
          authMode: "2",
          subjects: "[" + switchNodeId + "]",
          targets: "null"
        },
        nodeId: lightNodeId,
        endpointId: aclEndpointId
      }
      console.log(`Sending request to ${this.serverUrl}/write_acl with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/write_acl`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending write_acl command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all missing fields")
    }
  }

  sendWriteBindingCommand(lightNodeId: string, lightEndpointId: string, switchNodeId: string, switchEndpointId: string) {
    var fieldChechSetActiveDataset: Function = () => {
      return lightNodeId.length > 0 && switchNodeId.length > 0 && lightEndpointId.length > 0 && switchEndpointId.length > 0
    }
    if (fieldChechSetActiveDataset()) {
      const data = {
        bindingConf: {
          fabricIndex: "1",
          node: lightNodeId,
          endpoint: lightEndpointId,
          cluster: "6"
        },
        nodeId: switchNodeId,
        endpointId: switchEndpointId
      }
      console.log(`Sending request to ${this.serverUrl}/write_binding with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/write_binding`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending write_binding command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all missing fields")
    }
  }


  sendOTAFileFromFormDataUpload(formData: FormData) {
    if (formData) {
      return this.httpClient.post(`${this.serverUrl}/uploader`, formData)
    } else {
      return throwError("Please select the file to be uploaded")
    }
  }

  sendRunACLOTAProviderCommand(acldevice_nodeid: string) {
    var fieldCheck: Function = () => {
      return acldevice_nodeid.length > 0
    }

    if (fieldCheck()) {
      const data =
      {
        "aclConf1": {
          "fabricIndex": "1",
          "privilege": "5",
          "authMode": "2",
          "subjects": "[112233]",
          "targets": "null"
        },
        "aclConf2": {
          "fabricIndex": "1",
          "privilege": "3",
          "authMode": "2",
          "subjects": "null",
          "targets": "null"
        },
        "nodeId": acldevice_nodeid,
        "endpointId": "0"
      }
      console.log(`Sending request to ${this.serverUrl}/write_acl with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/write_acl`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending write_acl OTA command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all missing fields")
    }
  }

  sendRunOTASoftwareUpdateRequestorCommand(ota_provider_id: string, ota_requestor_id: string) {
    var fieldCheck: Function = () => {
      return ota_provider_id.length > 0 && ota_requestor_id.length > 0
    }
    if (fieldCheck()) {
      const data =
      {
        "otaProviderNodeId": ota_provider_id,
        "otaRequestorNodeId": ota_requestor_id
      }
      console.log(`Sending request to ${this.serverUrl}/otasoftwareupdaterequestor with data: ${JSON.stringify(data)}`)
      return this.httpClient.post<string>(
        `${this.serverUrl}/otasoftwareupdaterequestor`, JSON.stringify(data)
      ).pipe(
        catchError((error: any) => {
          console.error('Error sending otasoftwareupdaterequestor OTA command', error);
          return throwError(error.message)
        })
      );
    } else {
      return throwError("Please complete all missing fields")
    }
  }

}
