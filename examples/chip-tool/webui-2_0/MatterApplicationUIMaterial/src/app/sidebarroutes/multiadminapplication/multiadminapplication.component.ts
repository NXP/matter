import { ApplicationcardComponent } from './../../applicationcard/applicationcard.component';
import { PostRequestsService } from './../../services/post-requests.service';
import { Component } from '@angular/core';
import { MatCardModule } from '@angular/material/card';
import { MatFormField, MatFormFieldModule, MatLabel } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
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
import { FormsModule } from '@angular/forms';

import { NgxMasonryModule } from 'ngx-masonry';
import { CardModel } from '../../models/card-model';
import { MatDialog } from '@angular/material/dialog';
import { GetRequestsService } from '../../services/get-requests.service';
import * as QRCode from 'qrcode';

@Component({
  selector: 'app-multiadminapplication',
  standalone: true,
  imports: [MatCardModule, MatIconModule, MatButtonModule, FormsModule,
    ScrollgallerycomponentComponent,
    MatFormField, MatLabel, MatFormFieldModule, MatInputModule, MatSelectModule, MatChip, SettingsapplicationComponent, NgbModule, MatCardModule, MatCard, NgClass, NgFor, NgIf, NgStyle,
    ScrollgallerycomponentComponent, ApplicationcardComponent, CardscomponentComponent, FloatingactionareaComponent, NgxMasonryModule],
  templateUrl: './multiadminapplication.component.html',
  styleUrl: '../sidebarroutes.share.css'
})

export class MultiadminapplicationComponent {

  constructor(private modalService: NgbModal, private dialog: MatDialog, private getRequestsService: GetRequestsService, private appDialogService: AppDialogService, private postRequestsService: PostRequestsService,
    private loaderService: LoaderService
  ) {}

  commissioningMethod: '0' | '1' = '0';

  public cards: CardModel[] = [];
  ngOnInit(): void {}
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
      windowtimeout: (document.getElementById("window-timeout-input") as HTMLInputElement).value,
      option: this.commissioningMethod,
      iteration: (document.getElementById("iteration-input") as HTMLInputElement).value,
      discriminator: (document.getElementById("discriminator-input") as HTMLInputElement).value,
    }
  }

  openCommissioningWindowWithBCM() : void {
    console.log('Opening commissioning window with BCM');
    var values_for_the_input = this.getInputFieldsCurrentValue();
    this.loaderService.showLoader();

    this.postRequestsService.sendOpenCommissioningWindowWithBCM(
      values_for_the_input.nodeId, values_for_the_input.windowtimeout, values_for_the_input.option, values_for_the_input.iteration, values_for_the_input.discriminator
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Open commissioning window with BCM completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Open commissioning window with BCM completed with errors');
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
    var values_for_the_input = this.getInputFieldsCurrentValue();
    this.loaderService.showLoader();

    this.postRequestsService.sendOpenCommissioningWindowWithECM(
      values_for_the_input.nodeId, values_for_the_input.windowtimeout, values_for_the_input.option, values_for_the_input.iteration, values_for_the_input.discriminator
    ).subscribe(
      (data: any) => {
        data = data as DataPayload
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          //this.appDialogService.showInfoDialog('Pairing with ECM completed successfully. The payload is: ' + data.payload);
          const qrCodeData = parsedResult.qrCode;
          const qrCodeImage = document.createElement('img');
          QRCode.toDataURL(qrCodeData, { errorCorrectionLevel: 'H' })
          .then(url => {
            qrCodeImage.src = url;
            qrCodeImage.alt = 'QR Code';

            this.appDialogService.showQrCodeInfoDialog(
              `Node interaction successful.
              Manual Code: ${parsedResult.payload}
              QRCode:`,
              qrCodeImage
            );
          })
          .catch(err => {
            console.error("Error generating QR ode:", err);
            this.appDialogService.showInfoDialog(
              `Node interaction successful. Manual Code: ${parsedResult.payload}.  QR Code generation failed.`
            );
          });
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Open commissioning window with ECM completed with errors');
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
