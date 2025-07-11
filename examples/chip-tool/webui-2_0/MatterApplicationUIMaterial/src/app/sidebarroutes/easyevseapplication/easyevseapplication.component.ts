import { ApplicationcardComponent } from './../../applicationcard/applicationcard.component';
import { PostRequestsService } from './../../services/post-requests.service';
import { Component } from '@angular/core';
import { MatCardModule } from '@angular/material/card';
import { MatFormField, MatFormFieldModule, MatLabel } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { ScrollgallerycomponentComponent } from '../../mainapplicationbody/scrollgallerycomponent/scrollgallerycomponent.component';
import { MatInputModule } from '@angular/material/input';
import { MatSelectModule } from '@angular/material/select';
import { MatChip } from '@angular/material/chips';
import { FloatingactionareaComponent } from '../../mainapplicationbody/floatingactionarea/floatingactionarea.component';
import { SettingsapplicationComponent } from "../settingsapplication/settingsapplication.component";
import { LoaderService } from '../../services/loader.service';
import { AppDialogService } from '../../services/app-dialog.service';
import { CardscomponentComponent } from '../../mainapplicationbody/cardscomponent/cardscomponent.component';
import { NgbModal, NgbModule } from '@ng-bootstrap/ng-bootstrap';
import { MatCard } from '@angular/material/card';
import { NgClass } from '@angular/common';
import { NgFor, NgIf, NgStyle } from '@angular/common';
import { HttpClient } from '@angular/common/http';

import { NgxMasonryComponent, NgxMasonryModule } from 'ngx-masonry';
import { MatDialog } from '@angular/material/dialog';
import { GetRequestsService } from '../../services/get-requests.service';
import { CardModel } from '../../models/card-model';

@Component({
  selector: 'app-easyevseapplication',
  standalone: true,
  imports: [MatCardModule, MatIconModule,
    ScrollgallerycomponentComponent,
    MatFormField, MatLabel, MatFormFieldModule, MatInputModule, MatSelectModule, MatChip, SettingsapplicationComponent, NgbModule, MatCardModule, MatCard, NgClass, NgFor, NgIf, NgStyle,
    ScrollgallerycomponentComponent, ApplicationcardComponent, CardscomponentComponent, FloatingactionareaComponent, NgxMasonryModule],
  templateUrl: './easyevseapplication.component.html',
  styleUrl: './easyevseapplication.component.css'
})
export class EasyevseapplicationComponent {
  constructor(private modalService: NgbModal, private dialog: MatDialog, private getRequestsService: GetRequestsService, private appDialogService: AppDialogService, private postRequestsService: PostRequestsService,
    private loaderService: LoaderService
  ) {}

  public cards: CardModel[] = [];
  ngOnInit(): void {
  //   this.loaderService.showLoader();
  //   this.getRequestsService.getDevicesList().subscribe(
  //     (data: any) => {
  //       const parsedData = JSON.parse(JSON.stringify(data));
  //       if (parsedData['result'] === 'successful') {
  //         this.cards = []
  //         for (const [key, value] of Object.entries(parsedData['devices'])) {
  //           let card: CardModel;
  //           const device = value as string;
  //           card = new CardModel('../../assets/wireless-transparent.png', parseInt(key), [], true, device);
  //           this.cards.push(card);
  //         }
  //         this.loaderService.hideLoader();
  //         // this.appDialogService.showInfoDialog('Got the list of devices successfully');
  //       } else {
  //         this.loaderService.hideLoader();
  //         this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
  //       }
  //     },
  //     (error: any) => {
  //       console.error('Error received: ', error);
  //       this.loaderService.hideLoader();
  //       this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
  //     }
  // );
  }
  ngOnDestroy(): void {}

  onButtonPressedEventCatch(value: {
    buttonName: string;
    action: Function;
  }) {
    console.log('Button pressed event caught in the ApplicationBodyComponent; value: ' + value.buttonName);
    value.action();
  };

  // EEVSE Event trigger section
  startEEVSETriggerEvent(): void {
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    var key = (document.getElementById("key-input") as (HTMLInputElement)).value
    this.loaderService.showLoader();
    this.postRequestsService.sendEEVSEStartTriggerEvent(
      nodeId, nodeAlias, key
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE command completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  clearEEVSETriggerEvent(): void {
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    var key = (document.getElementById("key-input") as (HTMLInputElement)).value
    this.loaderService.showLoader();
    this.postRequestsService.sendEEVSEClearTriggerEvent(
      nodeId, nodeAlias, key
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE command completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  triggerEEVSEPluggedIn() : void {
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    var key = (document.getElementById("key-input") as (HTMLInputElement)).value
    this.loaderService.showLoader();
    this.postRequestsService.sendEEVSEStartPluggedinEvent(
      nodeId, nodeAlias, key
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE command completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  clearEEVSEPluggedIn() : void {
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    var key = (document.getElementById("key-input") as (HTMLInputElement)).value
    this.loaderService.showLoader();
    this.postRequestsService.sendEEVSEClearPluggedinEvent(
      nodeId, nodeAlias, key
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE command completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )

  }

  triggerEEVSEChargingDemand() : void {
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    var key = (document.getElementById("key-input") as (HTMLInputElement)).value
    this.loaderService.showLoader();
    this.postRequestsService.sendEEVSETriggerChargingDemandEvent(
      nodeId, nodeAlias, key
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE command completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  clearEEVSEChargingDemand() : void {
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    var key = (document.getElementById("key-input") as (HTMLInputElement)).value
    this.loaderService.showLoader();
    this.postRequestsService.sendEEVSEClearChargingDemandEvent(
      nodeId, nodeAlias, key
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE enable charging command completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  // EEVSE enable charging section
  eevseEnableCharging() : void {
    console.log("EEVSE enabling charging")
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var endpointId = (document.getElementById("endpoint-id") as (HTMLInputElement)).value
    var minimumChargeCurrent = (document.getElementById("minimum-charge-current") as (HTMLInputElement)).value
    var maximumChargeCurrent = (document.getElementById("maximum-charge-current") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    this.loaderService.showLoader();

    this.postRequestsService.sendEEVSEEnableChargingCommand(nodeId, nodeAlias, endpointId, minimumChargeCurrent, maximumChargeCurrent, "enablecharging").subscribe(
      (data) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE enable charging command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE enable charging command completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  // Write EEVSE User Maximum Charge Current Section
  writeEEVSEUserMaximumChargeCurrent() : void {
    console.log("Writing EEVSE User Maximum Charge Current")
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var endpointId = (document.getElementById("endpoint-id") as (HTMLInputElement)).value
    var userMaximumChargeCurrent = (document.getElementById("user-maximum-charge-current") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    
    this.loaderService.showLoader();

    this.postRequestsService.sendEEVSEWriteUserMaximumChargeCurrentCommand(nodeId, nodeAlias, endpointId, userMaximumChargeCurrent, "write").subscribe(
      (data) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE write user maximum charge current command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE write user maximum charge current completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error );
      }
    )
  }

  // EEVSE Disable Charging endpoint
  eevseDisableCharging() : void {
    console.log("Writing EEVSE disable charging command")
    var nodeId = (document.getElementById("node-id") as (HTMLInputElement)).value
    var endpointId = (document.getElementById("endpoint-id") as (HTMLInputElement)).value
    var nodeAlias = (document.getElementById("node-alias") as (HTMLInputElement)).value
    this.loaderService.showLoader();

    this.postRequestsService.sendEEVSEDisableChargingCommand(nodeId, nodeAlias, endpointId).subscribe(
      (data) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('EEVSE disable charging command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE disable charging command completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  // EEVSE Status section
  onCurrentStateEEVSERead(command: string) : void {
    var values_for_the_input = {
      nodeId: (document.getElementById("node-id") as HTMLInputElement).value,
      endPointId: (document.getElementById("endpoint-id") as (HTMLInputElement)).value,
      nodeAlias: (document.getElementById("node-alias") as (HTMLInputElement)).value
    }

    this.loaderService.showLoader();

    interface ResponseIfce {
      report: string,
      result: string
    }

    this.postRequestsService.sendEEVSEReadCommand(
      values_for_the_input.nodeId, values_for_the_input.endPointId, command, values_for_the_input.nodeAlias
    ).subscribe(
      (data: any) => {
        data = data as ResponseIfce;
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog(`EEVSE read completed successfully. The report is ` + data.report);
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('EEVSE read completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }
}
