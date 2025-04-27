import { AppDialogService } from './../services/app-dialog.service';
import { Component, Input } from '@angular/core';
import {MatCard, MatCardModule} from '@angular/material/card';
import { ApplicationendpointComponent } from '../applicationendpoint/applicationendpoint.component';
import { Injectable } from '@angular/core';
import { NgClass, NgFor, NgIf, NgStyle } from '@angular/common';
import { CardModel } from '../models/card-model';
import { EndpointModel } from '../models/endpoint-model';
import { LightingModel } from '../models/lighting-model';
import { DimmableLightModel } from '../models/dimmable-light-model';
import { MatChip, MatChipListbox } from '@angular/material/chips';
import { AppDialogWithInputFieldsService } from '../services/app-dialog-input.service';
import { PostRequestsService } from '../services/post-requests.service';
import { LoaderService } from '../services/loader.service';
import { WebSocketService } from '../services/web-socket.service';

@Component({
  selector: 'app-applicationcard',
  standalone: true,
  imports: [MatCardModule, MatCard, ApplicationendpointComponent,
    NgStyle, NgClass, NgIf, NgFor, MatChipListbox, MatChip],
  templateUrl: './applicationcard.component.html',
  styleUrl: './applicationcard.component.css'
})

export class ApplicationcardComponent {
  constructor (private appDialogService: AppDialogService, private appDialogWithInputFieldsService: AppDialogWithInputFieldsService,
    private postRequestsService: PostRequestsService, private loaderService: LoaderService, private webSocketService: WebSocketService) {}

  @Input() deviceTypeImageURL!: string;
  @Input() deviceId! :number;
  @Input() endpoints!: EndpointModel[];
  @Input() isDeviceOnline!: boolean;
  @Input() deviceName!: string;
  @Input() withSubscription!: boolean;
  @Input() withEevsePanel!: boolean;
  @Input() withTbrmPanel!: boolean; // Just for demo use
  @Input() openCommissioningWindowPanel!: boolean;

  public getDeviceTypeImageURL(): string {
    return this.deviceTypeImageURL;
  }

  public getDeviceId(): number {
    return this.deviceId;
  }

  public getEndpoints(): EndpointModel[] {
    return this.endpoints;
  }

  public getIsDeviceOnline(): boolean {
    return this.isDeviceOnline;
  }

  public getDeviceName(): string {
    return this.deviceName;
  }

  public getDeviceStatus(): string {
    return this.isDeviceOnline ? 'Online' : 'Offline';
  }

  public getDeviceStatusColor(): string {
    return this.isDeviceOnline ? 'green' : 'red';
  }

  public deviceTurnOn(): void {
    this.isDeviceOnline = true;
  }

  public deviceTurnOff(): void {
    this.isDeviceOnline = false;
  }

  forgetDevice(deviceId: number) {
    this.appDialogService.showNotImplementedDialog();
    console.log('Forget device with id: ' + deviceId);
  }

  scanDeviceEndpoints(arg0: number) {
    this.appDialogService.showNotImplementedDialog();
  }

  subscribeToDevice(deviceId: number) {
    this.appDialogWithInputFieldsService.openDialogWithSelectionItems(
      'Interact with device endpoint', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          // {inputFieldType: 'text', inputFieldName: 'Device ID', inputFieldContent: deviceId.toString(), inputFieldDefaultValue: 'Default: ' + deviceId.toString()},
          {inputFieldType: 'text', inputFieldName: 'Endpoint ID', inputFieldContent: '1', inputFieldDefaultValue: 'Default: 1'},
          {inputFieldType: 'text', inputFieldName: 'Subscription Min Interval', inputFieldContent: '10', inputFieldDefaultValue: 'Default: 10'},
          {inputFieldType: 'text', inputFieldName: 'Subscription Max Interval', inputFieldContent: '50', inputFieldDefaultValue: 'Default: 50'},
        ]
      },
      [
        {buttonName: 'Send Command', action: () => {
          var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
          if (this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem() === undefined) {
            this.appDialogService.showErrorDialog('No command selected');
          } else {
            console.log('Subscribing to device endpoint');
            console.log('Device ID: ', deviceId.toString());
            console.log('Endpoint ID: ', values_for_the_input[0].inputFieldContent);
            console.log('Subscription Min Interval: ', values_for_the_input[1].inputFieldContent);
            console.log('Subscription Max Interval: ', values_for_the_input[2].inputFieldContent);
            this.webSocketService.subscribeToDeviceEndpoint(
              deviceId.toString(), values_for_the_input[0].inputFieldContent.toLowerCase(),
              parseInt(values_for_the_input[1].inputFieldContent), parseInt(values_for_the_input[2].inputFieldContent),
              this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem()!.toLowerCase(),
              this.getDeviceName()
            );
            this.appDialogWithInputFieldsService.closeDialog();
          }
        }, color: 'primary'},
        {buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
        }, color: 'warn'}
      ],
      [
        {name: 'Cluster ON/OFF', color: 'primary'},
      ]
    );
  }

  openEEVSEControlPanelDialog(deviceId: Number) {
    // Find dialog options and put them here
    // Create a dialog that resembles the screen the device is already on
    // this.appDialogWithInputFieldsService.openDialogWithSelectionItems(
    //   'Interact with device endpoint', '../../../assets/matter-logo-transparent.png',
    //   {
    //     inputFields: [
    //       {inputFieldType: 'text', inputFieldName: 'Option', inputFieldContent: 0, inputFieldDefaultValue: 'Default: ' + this.deviceName.toString()},
    //       {inputFieldType: 'text', inputFieldName: 'Discriminator', inputFieldContent: deviceId.toString(), inputFieldDefaultValue: 'Default: ' + deviceId.toString()},
    //       {inputFieldType: 'text', inputFieldName: 'Iteration', inputFieldContent: '1', inputFieldDefaultValue: 'Default: 1'},
    //       {inputFieldType: 'text', inputFieldName: 'Window Timeout', inputFieldContent: '1', inputFieldDefaultValue: 'Default: 1'},
    //     ]
    //   },
    //   [
    //     {buttonName: 'Send Command', action: () => {
    //       var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
    //       if (this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem() === undefined) {
    //         this.appDialogService.showErrorDialog('No command selected');
    //       } else {
    //         this.loaderService.showLoader();
    //         if (this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem() === 'Read') { // Send onoff_report request
    //           this.postRequestsService.sendOnOffReadEndpointCommand(
    //             deviceId.toString(), values_for_the_input[0].inputFieldContent.toLowerCase()
    //           ).subscribe(
    //             data => {
    //               console.log('Data received: ', data);
    //               this.loaderService.hideLoader();
    //               const parsedResult = JSON.parse(JSON.stringify(data));
    //               if (parsedResult.result === 'successful') {
    //                 this.appDialogService.showInfoDialog('Endpoint interaction successful!\n' +
    //                   "Generated report: " + JSON.stringify(parsedResult.report));
    //               } else if (parsedResult.result === 'failed') {
    //                 this.appDialogService.showErrorDialog('Error interacting with the endpoint. Please try again.');
    //               }
    //             },

    //             error => {
    //               console.error('Error received: ', error);
    //               this.loaderService.hideLoader();
    //               this.appDialogService.showErrorDialog('Error interacting with the endpoint. Network error.');
    //             }
    //           );

    //           this.appDialogWithInputFieldsService.closeDialog();

    //         } else {
    //           this.postRequestsService.sendOnOffToggleEndpointCommand(
    //             deviceId.toString(), values_for_the_input[0].inputFieldContent.toLowerCase(),
    //               this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem()!.toLowerCase()
    //           ).subscribe(
    //             data => {
    //               console.log('Data received: ', data);
    //               this.loaderService.hideLoader();
    //               const parsedResult = JSON.parse(JSON.stringify(data));
    //               if (parsedResult.result === 'successful') {
    //                 this.appDialogService.showInfoDialog('Endpoint interaction successful');
    //               } else if (parsedResult.result === 'failed') {
    //                 this.appDialogService.showErrorDialog('Error interacting with the endpoint. Please try again.');
    //               }
    //             },

    //             error => {
    //               console.error('Error received: ', error);
    //               this.loaderService.hideLoader();
    //               this.appDialogService.showErrorDialog('Error interacting with the endpoint. Network error.');
    //             }
    //           );

    //           this.appDialogWithInputFieldsService.closeDialog();
    //         }
    //        }
    //     }, color: 'primary'},
    //     {buttonName: 'Cancel', action: () => {
    //       this.appDialogWithInputFieldsService.closeDialog();
    //     }, color: 'warn'}
    //   ],
    //   [
    //     {name: 'ON', color: 'primary'},
    //     {name: 'OFF', color: 'primary'},
    //     {name: 'Toggle', color: 'primary'},
    //     {name: 'Read', color: 'primary'},
    //   ]
    // );
  }
  openTBRMControlPanelDialog(deviceId: Number) {

  }
  openCommissioningWindowControlPanelDialog(deviceId: Number) {

  }

  interactWithEndpoint(deviceId: number) {
    this.appDialogWithInputFieldsService.openDialogWithSelectionItems(
      'Interact with device endpoint', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          // {inputFieldType: 'text', inputFieldName: 'Device Alias', inputFieldContent: this.deviceName.toString(), inputFieldDefaultValue: 'Default: ' + this.deviceName.toString()},
          // {inputFieldType: 'text', inputFieldName: 'Device ID', inputFieldContent: deviceId.toString(), inputFieldDefaultValue: 'Default: ' + deviceId.toString()},
          {inputFieldType: 'text', inputFieldName: 'Endpoint ID', inputFieldContent: '1', inputFieldDefaultValue: 'Default: 1'},
        ]
      },
      [
        {buttonName: 'Send Command', action: () => {
          var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
          if (this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem() === undefined) {
            this.appDialogService.showErrorDialog('No command selected');
          } else {
            this.loaderService.showLoader();
            if (this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem() === 'Read') { // Send onoff_report request
              this.postRequestsService.sendOnOffReadEndpointCommand(
                deviceId.toString(), values_for_the_input[0].inputFieldContent.toLowerCase()
              ).subscribe(
                data => {
                  console.log('Data received: ', data);
                  this.loaderService.hideLoader();
                  const parsedResult = JSON.parse(JSON.stringify(data));
                  if (parsedResult.result === 'successful') {
                    this.appDialogService.showInfoDialog('Endpoint interaction successful!\n' +
                      "Generated report: " + JSON.stringify(parsedResult.report));
                  } else if (parsedResult.result === 'failed') {
                    this.appDialogService.showErrorDialog('Error interacting with the endpoint. Please try again.');
                  }
                },

                error => {
                  console.error('Error received: ', error);
                  this.loaderService.hideLoader();
                  this.appDialogService.showErrorDialog('Error interacting with the endpoint. Network error.');
                }
              );

              this.appDialogWithInputFieldsService.closeDialog();

            } else {
              this.postRequestsService.sendOnOffToggleEndpointCommand(
                deviceId.toString(), values_for_the_input[0].inputFieldContent.toLowerCase(),
                  this.appDialogWithInputFieldsService.getSelectedDialogSelectionItem()!.toLowerCase()
              ).subscribe(
                data => {
                  console.log('Data received: ', data);
                  this.loaderService.hideLoader();
                  const parsedResult = JSON.parse(JSON.stringify(data));
                  if (parsedResult.result === 'successful') {
                    this.appDialogService.showInfoDialog('Endpoint interaction successful');
                  } else if (parsedResult.result === 'failed') {
                    this.appDialogService.showErrorDialog('Error interacting with the endpoint. Please try again.');
                  }
                },

                error => {
                  console.error('Error received: ', error);
                  this.loaderService.hideLoader();
                  this.appDialogService.showErrorDialog('Error interacting with the endpoint. Network error.');
                }
              );

              this.appDialogWithInputFieldsService.closeDialog();
            }
           }
        }, color: 'primary'},
        {buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
        }, color: 'warn'}
      ],
      [
        {name: 'ON', color: 'primary'},
        {name: 'OFF', color: 'primary'},
        {name: 'Toggle', color: 'primary'},
        {name: 'Read', color: 'primary'},
      ]
    );
  }

  openEditDialog(deviceId: number) {
    this.appDialogWithInputFieldsService.openDialog(
      'Edit Device', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          {inputFieldType: 'text', inputFieldName: 'Node Alias', inputFieldContent: 'DeviceName', inputFieldDefaultValue: 'Default: DeviceName; Default Endpoint ID: 0'},
          // {inputFieldType: 'text', inputFieldName: 'Node ID', inputFieldContent: deviceId.toString(), inputFieldDefaultValue: 'Default: ' + deviceId.toString()},
          // {inputFieldType: 'text', inputFieldName: 'Endpoint ID', inputFieldContent: '1', inputFieldDefaultValue: 'No default values'},
        ]
      },
      [
        {buttonName: 'Send Command', action: () => {
          var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
          this.loaderService.showLoader();

          this.postRequestsService.sendBasicInformationCommand(
            values_for_the_input[0].inputFieldContent, deviceId.toString(),
            "0" // Default endpoint ID = 0
          ).subscribe(
            data => {
              console.log('Data received: ', data);
              this.loaderService.hideLoader();
              const parsedResult = JSON.parse(JSON.stringify(data));
              if (parsedResult.result === 'successful') {
                this.appDialogService.showInfoDialog('Node edit successful');
              } else if (parsedResult.result === 'failed') {
                this.appDialogService.showErrorDialog('Error interacting with the node. Please try again.');
              }
            },

            error => {
              console.error('Error received: ', error);
              this.loaderService.hideLoader();
              this.appDialogService.showErrorDialog('Error interacting with the node. Network error.');
            }
          );

          this.appDialogWithInputFieldsService.closeDialog();
        }, color: 'primary'},
        {buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
        }, color: 'warn'}
      ]
    );
  }


  openCommissioningWindow(deviceId: number) {
    this.appDialogWithInputFieldsService.openDialog(
      'Interact with device endpoint', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          // {inputFieldType: 'text', inputFieldName: 'Node ID', inputFieldContent: deviceId.toString(), inputFieldDefaultValue: 'Default: ' + deviceId.toString()},
          {inputFieldType: 'text', inputFieldName: 'Window Timeout', inputFieldContent: '1', inputFieldDefaultValue: 'No default values'},
          {inputFieldType: 'text', inputFieldName: 'Option', inputFieldContent: '1', inputFieldDefaultValue: 'Default: BCM: 0; ECM: 1'},
          {inputFieldType: 'text', inputFieldName: 'Iteration', inputFieldContent: '1', inputFieldDefaultValue: 'No default values'},
          {inputFieldType: 'text', inputFieldName: 'Discriminator (3840)', inputFieldContent: '3840', inputFieldDefaultValue: '3840'},
        ]
      },
      [
        {buttonName: 'Send Command', action: () => {
          var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
          this.loaderService.showLoader();
          if (values_for_the_input[1].inputFieldContent.toLowerCase() == '1') { // Option field
            // Pairing with ECM
            this.postRequestsService.sendOpenCommissioningWindowWithECM(
              deviceId.toString(),
              values_for_the_input[0].inputFieldContent.toLowerCase(), values_for_the_input[1].inputFieldContent.toLowerCase(),
              values_for_the_input[2].inputFieldContent.toLowerCase(), values_for_the_input[3].inputFieldContent.toLowerCase(),
            ).subscribe(
              data => {
                console.log('Data received: ', data);
                this.loaderService.hideLoader();
                const parsedResult = JSON.parse(JSON.stringify(data));
                if (parsedResult.result === 'successful') {
                  this.appDialogService.showInfoDialog('Node interaction successful. Paylaod: ' + parsedResult.payload);
                } else if (parsedResult.result === 'failed') {
                  this.appDialogService.showErrorDialog('Error interacting with the node. Please try again.');
                }
              },

              error => {
                console.error('Error received: ', error);
                this.loaderService.hideLoader();
                this.appDialogService.showErrorDialog('Error interacting with the node. Network error.');
              }
            );
          } else if (values_for_the_input[1].inputFieldContent.toLowerCase() == '0') { // Option field
            // Pairing with BCM
            this.postRequestsService.sendOpenCommissioningWindowWithBCM(
              // values_for_the_input[0].inputFieldContent.toLowerCase(),
              deviceId.toString(),
              values_for_the_input[0].inputFieldContent.toLowerCase(), values_for_the_input[1].inputFieldContent.toLowerCase(),
              values_for_the_input[2].inputFieldContent.toLowerCase(), values_for_the_input[3].inputFieldContent.toLowerCase(),

            ).subscribe(
              data => {
                console.log('Data received: ', data);
                this.loaderService.hideLoader();
                const parsedResult = JSON.parse(JSON.stringify(data));
                if (parsedResult.result === 'successful') {
                  this.appDialogService.showInfoDialog('Node interaction successful');
                } else if (parsedResult.result === 'failed') {
                  this.appDialogService.showErrorDialog('Error interacting with the node. Please try again.');
                }
              },

              error => {
                console.error('Error received: ', error);
                this.loaderService.hideLoader();
                this.appDialogService.showErrorDialog('Error interacting with the node. Network error.');
              }
            );

          } else {
            this.loaderService.hideLoader();
            this.appDialogService.showErrorDialog('Please select the proper options and fill the input fields');
          }


          this.appDialogWithInputFieldsService.closeDialog();
        }, color: 'primary'},
        {buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
        }, color: 'warn'}
      ]
    );
  }


}
