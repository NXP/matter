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

import { NgxMasonryComponent, NgxMasonryModule } from 'ngx-masonry';
import { CardModel } from '../../models/card-model';
import { MatDialog } from '@angular/material/dialog';
import { GetRequestsService } from '../../services/get-requests.service';

@Component({
  selector: 'app-multiadminapplication',
  standalone: true,
  imports: [MatCardModule, MatIconModule,
    ScrollgallerycomponentComponent,
    MatFormField, MatLabel, MatFormFieldModule, MatInputModule, MatSelectModule, MatChip, SettingsapplicationComponent, NgbModule, MatCardModule, MatCard, NgClass, NgFor, NgIf, NgStyle,
    ScrollgallerycomponentComponent, ApplicationcardComponent, CardscomponentComponent, FloatingactionareaComponent, NgxMasonryModule],
  templateUrl: './multiadminapplication.component.html',
  styleUrl: './multiadminapplication.component.css'
})

export class MultiadminapplicationComponent {

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

  getInputFieldsCurrentValue() {
    return {
      nodeId: (document.getElementById("nodeid-input") as HTMLInputElement).value,
      option: (document.getElementById("option-input") as HTMLInputElement).value,
      "window-timeout": (document.getElementById("window-timeout-input") as HTMLInputElement).value,
      iteration: (document.getElementById("iteration-input") as HTMLInputElement).value,
      discriminator: (document.getElementById("discriminator-input") as HTMLInputElement).value,
    }

  }

  openCommissioningWindowWithBCM() : void {
    console.log('Opening commissioning window with BCM');
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendOpenCommissioningWindowWithBCM(
      values_for_the_input.nodeId, values_for_the_input['window-timeout'], values_for_the_input.option, values_for_the_input.iteration, values_for_the_input.discriminator
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Pairing with BCM completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Pairing with BCM completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );

  }

  openCommissioningWindowWithECM() : void {

    interface DataPayload {
      reponse: string,
      payload: string,
    }

    console.log('Opening commissioning window with ECM');
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendOpenCommissioningWindowWithECM(
      values_for_the_input.nodeId, values_for_the_input['window-timeout'], values_for_the_input.option, values_for_the_input.iteration, values_for_the_input.discriminator
    ).subscribe(
      (data: any) => {
        data = data as DataPayload
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Pairing with ECM completed successfully. The payload is: ' + data.payload);
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Pairing with ECM completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );

  }

  parsePayloadFunctionForECMPairing() : void {
    interface DataPayload {
      passcode: string,
      result: string
    }
    console.log('Sending parse payload command');
    var payload_value = ((document.getElementById('payload-input')) as HTMLInputElement).value
    this.loaderService.showLoader();

    this.postRequestsService.sendPayloadParsePostRequest(
      payload_value
    ).subscribe(
      (data: any) => {
        data = data as DataPayload
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Paylaod parsing completed successfully. The passcode is: ' + data.passcode);
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Payload parsing completed with errors');
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
