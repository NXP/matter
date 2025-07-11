import { AppDialogService } from './../../services/app-dialog.service';
import { Component, EventEmitter, Output } from '@angular/core';
import { NgClass, NgOptimizedImage, NgStyle } from '@angular/common'
import { MatMenuModule } from '@angular/material/menu';
import { MatIconModule } from '@angular/material/icon';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatChipsModule } from '@angular/material/chips';
import { OnInit } from '@angular/core';
import { AppDialogWithInputFieldsService } from '../../services/app-dialog-input.service';
import { LoaderService } from '../../services/loader.service';
import { PostRequestsService } from '../../services/post-requests.service';
import { GetRequestsService } from '../../services/get-requests.service';


@Component({
  selector: 'app-buttonpanel',
  standalone: true,
  imports: [NgOptimizedImage, MatMenuModule, MatIconModule,
    MatToolbarModule, MatChipsModule, NgStyle, NgClass],
  templateUrl: './buttonpanel.component.html',
  styleUrl: './buttonpanel.component.css'
})

export class ButtonpanelComponent implements OnInit {

  constructor(private appDialogWithInputFieldsService: AppDialogWithInputFieldsService,
    private loaderService: LoaderService, private postRequestsService: PostRequestsService, private appDialogService: AppDialogService,
    private getRequestsService: GetRequestsService
  ) {}

  ngOnInit(): void {
    //Called after the constructor, initializing input properties, and the first call to ngOnChanges.
    //Add 'implements OnInit' to the class.
  }

  @Output()
  public buttonPressedEvent : EventEmitter<{buttonName: string, action: Function}>
    = new EventEmitter<{buttonName: string, action: Function}>();

  emitButtonPressed(button: {buttonName: string, action: Function}) {
    console.log("Emitting button pressed event from the floating action area component");
    this.buttonPressedEvent.emit(button);
  }

  refreshActionFunction() {
    // this.loaderService.showLoader();
    // this.getRequestsService.getDevicesIDsAndAliases().subscribe(
    //   (data: any) => {
    //     const parsedData = JSON.parse(JSON.stringify(data));
    //     if (parsedData['result'] === 'successful') {
    //       this.cards = []; // We update all the cards array
    //       for (const [key, value] of Object.entries(parsedData['status'])) {
    //         let card: CardModel;
    //         const device = key as string;
    //         card = new CardModel('../../assets/wireless-transparent.png', parseInt(value), [], true, device);
    //         this.cards.push(card);
    //       }
    //       // We emit an event or something to the parent component with the new cards list
    //       this.loaderService.hideLoader();
    //       // this.appDialogService.showInfoDialog('Got the list of devices successfully');
    //     } else {
    //       this.loaderService.hideLoader();
    //       this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
    //     }
    //   },
    //   (error: any) => {
    //     console.error('Error received: ', error);
    //     this.loaderService.hideLoader();
    //     this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
    //   }
    // );
  }

  openWifiDeviceDialog() {
     this.appDialogWithInputFieldsService.openDialog(
        'Connect BLE-WIFI Device', '../../../assets/matter-logo-transparent.png',
        {
          inputFields: [
            {inputFieldType: 'text', inputFieldName: 'Device ID', inputFieldContent: '1234', inputFieldDefaultValue: 'Default: 1234'},
            {inputFieldType: 'text', inputFieldName: 'Device Code (20202021)', inputFieldContent: '20202021', inputFieldDefaultValue: 'Default: 20202021'},
            {inputFieldType: 'text', inputFieldName: 'Device Alias', inputFieldContent: 'DeviceAliasName', inputFieldDefaultValue: 'Default: DeviceAliasName'},
            {inputFieldType: 'text', inputFieldName: 'Network SSID', inputFieldContent: 'NetworkSSID', inputFieldDefaultValue: 'Default: NetworkSSID'},
            {inputFieldType: 'password', inputFieldName: 'Network Password', inputFieldContent: 'NetPa55!', inputFieldDefaultValue: 'Default: NetPa55!'},
            {inputFieldType: 'text', inputFieldName: 'Device Bluetooth Discriminator (3840)', inputFieldContent: '3840', inputFieldDefaultValue: 'Default: 3840'},

          ]
        },
        [
          { buttonName: 'Send Command', action: () => {

            var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
              this.loaderService.showLoader();
              this.postRequestsService.sendPairBLEWifiCommand(
                values_for_the_input[0].inputFieldContent, values_for_the_input[1].inputFieldContent, values_for_the_input[2].inputFieldContent,
                values_for_the_input[3].inputFieldContent, values_for_the_input[4].inputFieldContent, values_for_the_input[5].inputFieldContent
              ).subscribe(
                data => {
                  console.log('Data received: ', data);
                  this.loaderService.hideLoader();
                  const parsedResult = JSON.parse(JSON.stringify(data));
                  if (parsedResult.result === 'successful') {
                    // TODO: Add logic for auto device list refresh
                    this.refreshActionFunction()
                    this.appDialogService.showInfoDialog('BLE-WIFI device added successfully');
                  } else if (parsedResult.result === 'failed') {
                    this.appDialogService.showErrorDialog('Error adding BLE-WIFI device');
                  }
                },

                error => {
                  console.error('Error received: ', error);
                  this.loaderService.hideLoader();
                  this.appDialogService.showErrorDialog('Error adding BLE-WIFI device. Network error.');
                }
              );
           }, color: 'accent', icon: 'send' },
          { buttonName: 'Cancel', action: () => {
            this.appDialogWithInputFieldsService.closeDialog();
           }, color: 'warn', icon: 'cancel' },
        ]
      );

  }

  openThreadDeviceDialog() {
      this.appDialogWithInputFieldsService.openDialog(
        'Connect BLE-Thread Device', '../../../assets/matter-logo-transparent.png',
        {
          inputFields: [
            {inputFieldType: 'text', inputFieldName: 'Device ID', inputFieldContent: '1234', inputFieldDefaultValue: 'Default: 1234'},
            {inputFieldType: 'text', inputFieldName: 'Device Code (20202021)', inputFieldContent: '20202021', inputFieldDefaultValue: 'Default: 20202021'},
            {inputFieldType: 'text', inputFieldName: 'Device Alias', inputFieldContent: 'DeviceAliasName', inputFieldDefaultValue: 'Default: DeviceAliasName'},
            {inputFieldType: 'text', inputFieldName: 'Device Dataset', inputFieldContent: 'Dataset', inputFieldDefaultValue: 'Default: 0x123123123123123123123123123123123'},
            {inputFieldType: 'text', inputFieldName: 'Device Bluetooth Discriminator (3840)', inputFieldContent: '3840', inputFieldDefaultValue: 'Default: 3840'},
          ]
        },
        [
          { buttonName: 'Send Command', action: () => {
            var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
            this.loaderService.showLoader();
            this.postRequestsService.sendPairBLEThreadCommand(
              values_for_the_input[0].inputFieldContent, values_for_the_input[1].inputFieldContent, values_for_the_input[2].inputFieldContent,
              values_for_the_input[3].inputFieldContent, values_for_the_input[4].inputFieldContent
            ).subscribe(
              data => {
                console.log('Data received: ', data);
                this.loaderService.hideLoader();
                const parsedResult = JSON.parse(JSON.stringify(data));
                if (parsedResult.result === 'successful') {
                  this.appDialogService.showInfoDialog('BLE-Thread device added successfully');
                  // TODO: Add logic for auto device list refresh
                  this.refreshActionFunction()
                } else if (parsedResult.result === 'failed') {
                  this.appDialogService.showErrorDialog('Error adding BLE-Thread device');
                }
              },

              error => {
                console.error('Error received: ', error);
                this.loaderService.hideLoader();
                this.appDialogService.showErrorDialog('Error adding BLE-Thread device. Network error.');
              }
            );
           }, color: 'accent', icon: 'send' },
           {
            buttonName: 'Get Dataset', action: () => {
              var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
              this.loaderService.showLoader();
              this.getRequestsService.getDataset().subscribe(
                data => {
                  console.log('Data received: ', data);
                  this.loaderService.hideLoader();
                  const parsedResult = JSON.parse(JSON.stringify(data));
                  if (parsedResult.result === 'successful') {
                    this.appDialogService.showInfoDialog('Dataset received successfully.');
                    this.appDialogWithInputFieldsService.updateInputFieldContent(3, parsedResult.dataset);
                    // Update the device list
                  } else if (parsedResult.result === 'failed') {
                    this.appDialogService.showErrorDialog('Error receiving dataset');
                  }
                },

                error => {
                  console.error('Error received: ', error);
                  this.loaderService.hideLoader();
                  this.appDialogWithInputFieldsService.updateInputFieldContent(3, 'Error receiving dataset. Try again or manually insert the dataset.');
                  this.appDialogService.showErrorDialog('Error receiving dataset. Network error.');
                }
              );
            }, color: 'accent', icon: 'get_app'},
          { buttonName: 'Cancel', action: () => {
            this.appDialogWithInputFieldsService.closeDialog();
           }, color: 'warn', icon: 'cancel' },
        ]
      );
  }
  openEthernetDeviceDialog() {
    this.appDialogWithInputFieldsService.openDialog(
      'Connect Ethernet Device', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          {inputFieldType: 'text', inputFieldName: 'Device ID', inputFieldContent: '1234', inputFieldDefaultValue: '1234'},
          { inputFieldType: 'text', inputFieldName: 'Device Code (20202021)', inputFieldContent: '20202021', inputFieldDefaultValue: '20202021' },
          { inputFieldType: 'text', inputFieldName: 'Device Bluetooth Discriminator (3840)', inputFieldContent: '3840', inputFieldDefaultValue: '3840'},
          {inputFieldType: 'text', inputFieldName: 'Device IP Address', inputFieldContent: '127.0.0.1', inputFieldDefaultValue: '127.0.0.1'},
          {inputFieldType: 'number', inputFieldName: 'Device Port Number', inputFieldContent: '5540', inputFieldDefaultValue: '5540'},
        ]
      },
      [
        { buttonName: 'Send Command', action: () => { console.log('Add OnNetwork Device button pressed'); }, color: 'accent', icon: 'send' },
        { buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
         }, color: 'warn', icon: 'cancel' },
      ]
    );
  }

  openOnNetworkDeviceDialog() {
    this.appDialogWithInputFieldsService.openDialog(
      'Connect OnNetwork Device', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          {inputFieldType: 'text', inputFieldName: 'Device ID', inputFieldContent: '1234', inputFieldDefaultValue: 'Default: 1234'},
          {inputFieldType: 'text', inputFieldName: 'Device Code (20202021)', inputFieldContent: '20202021', inputFieldDefaultValue: 'Default: 20202021'},
          {inputFieldType: 'text', inputFieldName: 'Device Alias', inputFieldContent: 'DeviceAliasName', inputFieldDefaultValue: 'Default: DeviceAliasName'},
        ]
      },
      [
        {
          buttonName: 'Send Command', action: () => {

            var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
            this.loaderService.showLoader();
            this.postRequestsService.sendPairOnNetworkCommand(
              values_for_the_input[0].inputFieldContent, values_for_the_input[1].inputFieldContent, values_for_the_input[2].inputFieldContent
            ).subscribe(
              data => {
                console.log('Data received: ', data);
                const parsedResult = JSON.parse(JSON.stringify(data));
                if (parsedResult.result === 'successful') {
                  this.loaderService.hideLoader();
                  // TODO: Add logic for auto device list refresh
                  this.refreshActionFunction()
                  this.appDialogService.showInfoDialog('OnNetwork device added successfully');
                } else if (parsedResult.result === 'failed') {
                  this.loaderService.hideLoader();
                  this.appDialogService.showErrorDialog('Error adding OnNetwork device');
                }
              },
              error => {
                console.error('Error received: ', error);
                this.loaderService.hideLoader();
                this.appDialogService.showErrorDialog('Error adding OnNetwork device. Network error.');
              }
            );
         }, color: 'accent', icon: 'send' },
        { buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
         }, color: 'warn', icon: 'cancel' },
      ]
    );
  }

  openQRCodeDeviceDialog() {
    this.appDialogWithInputFieldsService.openDialog(
      'Connect Device by QRCode', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          {inputFieldType: 'text', inputFieldName: 'Device ID', inputFieldContent: '1234', inputFieldDefaultValue: 'Default: 1234'},
          {inputFieldType: 'text', inputFieldName: 'QRCode', inputFieldContent: 'MT:XXXXXXXXXXXXXXXXXXX', inputFieldDefaultValue: 'Default: MT:XXXXXXXXXXXXXXXXXXX'},
          {inputFieldType: 'text', inputFieldName: 'Device Alias', inputFieldContent: 'DeviceAliasName', inputFieldDefaultValue: 'Default: DeviceAliasName'},
        ]
      },
      [
        {
          buttonName: 'Scan QR Code', action: () => {
            this.appDialogService.showQrCodeScanDialog().subscribe(result => {
              if (result) {
                this.appDialogWithInputFieldsService.updateInputFieldContent(1, result);
                console.log('Updated Device Code with scanned value:', result);
              } else {
                this.appDialogService.showErrorDialog('Scan QRCode failed, please retry.');
              }
            });
          },
          color: 'primary', icon: 'qr_code_scanner'
        },
        {
          buttonName: 'Send Command', action: () => {

            var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
            this.loaderService.showLoader();
            this.postRequestsService.sendPairQRCodeCommand(
              values_for_the_input[0].inputFieldContent, values_for_the_input[1].inputFieldContent, values_for_the_input[2].inputFieldContent
            ).subscribe(
              data => {
                console.log('Data received: ', data);
                const parsedResult = JSON.parse(JSON.stringify(data));
                if (parsedResult.result === 'successful') {
                  this.loaderService.hideLoader();
                  this.refreshActionFunction()
                  this.appDialogService.showInfoDialog('Added device by QRCode successfully');
                } else if (parsedResult.result === 'failed') {
                  this.loaderService.hideLoader();
                  this.appDialogService.showErrorDialog('Error adding device by QRCode');
                }
              },
              error => {
                console.error('Error received: ', error);
                this.loaderService.hideLoader();
                this.appDialogService.showErrorDialog('Error adding device by QRCode. Network error.');
              }
            );
         }, color: 'accent', icon: 'send' },
        { buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
         }, color: 'warn', icon: 'cancel' },
      ]
    );
  }

  openOnboardEcosystemDialog() {
    this.appDialogWithInputFieldsService.openDialog(
      'Onboard an Ecosystem with Matter', '../../../assets/matter-logo-transparent.png',
      {
        inputFields: [
          {inputFieldType: 'text', inputFieldName: 'Node ID', inputFieldContent: '1', inputFieldDefaultValue: 'Default: 1'},
          {inputFieldType: 'text', inputFieldName: 'Onboarding Method', inputFieldContent: '0', inputFieldDefaultValue: 'Default: 0 - BCM, 1 - ECM'},
          {inputFieldType: 'text', inputFieldName: 'Device Code (20202021)', inputFieldContent: '20202021', inputFieldDefaultValue: 'Default: 20202021'},
          {inputFieldType: 'text', inputFieldName: 'Device Alias', inputFieldContent: 'DeviceAliasName', inputFieldDefaultValue: 'Default: DeviceAliasName'},
        ]
      },
      [
        { buttonName: 'Send Command', action: () => {

          var values_for_the_input = this.appDialogWithInputFieldsService.getInputFieldsValues()!;
            this.loaderService.showLoader();
            if (values_for_the_input[1].inputFieldContent == "0") {
              // BCM Onboarding
              this.postRequestsService.sendPairOnnetworkJointFabricBCMOnboarding(
                values_for_the_input[0].inputFieldContent, values_for_the_input[2].inputFieldContent, values_for_the_input[3].inputFieldContent
              ).subscribe(
                data => {
                  console.log('Data received: ', data);
                  const parsedResult = JSON.parse(JSON.stringify(data));
                  if (parsedResult.result === 'successful') {
                    this.loaderService.hideLoader();
                    // TODO: Add logic for auto device list refresh
                    this.refreshActionFunction()
                    this.appDialogService.showInfoDialog('OnNetwork device onboarded successfully');
                  } else if (parsedResult.result === 'failed') {
                    this.loaderService.hideLoader();
                    this.appDialogService.showErrorDialog('Error onboarding OnNetwork device');
                  }
                },
                error => {
                  console.error('Error received: ', error);
                  this.loaderService.hideLoader();
                  this.appDialogService.showErrorDialog('Error onboarding OnNetwork device. Network error.');
                }
              );

          } else if (values_for_the_input[1].inputFieldContent == "1") {
              // ECM Onboarding
              this.postRequestsService.sendPairOnnetworkJointFabricECMOnboarding(
                values_for_the_input[0].inputFieldContent, values_for_the_input[2].inputFieldContent
              ).subscribe(
                data => {
                  console.log('Data received: ', data);
                  const parsedResult = JSON.parse(JSON.stringify(data));
                  if (parsedResult.result === 'successful') {
                    this.loaderService.hideLoader();
                    this.appDialogService.showInfoDialog('OnNetwork device onboarded successfully');
                    // TODO: Add logic for auto device list refresh
                    this.refreshActionFunction()
                  } else if (parsedResult.result === 'failed') {
                    this.loaderService.hideLoader();
                    this.appDialogService.showErrorDialog('Error onboarding OnNetwork device');
                  }
                },
                error => {
                  console.error('Error received: ', error);
                  this.loaderService.hideLoader();
                  this.appDialogService.showErrorDialog('Error onboarding OnNetwork device. Network error.');
                }
              );
          } else {
            this.loaderService.hideLoader();
            this.appDialogService.showErrorDialog('Please complete the input fields accordingly');
          }

         }, color: 'accent', icon: 'send' },
        { buttonName: 'Cancel', action: () => {
          this.appDialogWithInputFieldsService.closeDialog();
         }, color: 'warn', icon: 'cancel' },
      ]
    );
  }
}
