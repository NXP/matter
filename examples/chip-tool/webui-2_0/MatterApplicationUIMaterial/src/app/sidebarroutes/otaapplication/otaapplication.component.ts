import { ApplicationcardComponent } from './../../applicationcard/applicationcard.component';
import { PostRequestsService } from './../../services/post-requests.service';
import { Component, input } from '@angular/core';
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
import { NgbModal, NgbModule, NgbProgressbar, NgbProgressbarModule } from '@ng-bootstrap/ng-bootstrap';
import { MatCard } from '@angular/material/card';
import { NgClass } from '@angular/common';
import { NgFor, NgIf, NgStyle } from '@angular/common';
import { HttpClient } from '@angular/common/http';

import { NgxMasonryComponent, NgxMasonryModule } from 'ngx-masonry';
import { MatDialog } from '@angular/material/dialog';
import { GetRequestsService } from '../../services/get-requests.service';
import { CardModel } from '../../models/card-model';
import { NONE_TYPE } from '@angular/compiler';
import { MatProgressBarModule } from '@angular/material/progress-bar';
import { WebSocketService } from '../../services/web-socket.service';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';

@Component({
  selector: 'app-otaapplication',
  standalone: true,
  imports: [MatCardModule, MatIconModule,
    ScrollgallerycomponentComponent,
    MatFormField, MatLabel, MatFormFieldModule, MatInputModule, MatSelectModule, MatChip, SettingsapplicationComponent, NgbModule, MatCardModule, MatCard, NgClass, NgFor, NgIf, NgStyle,
    ScrollgallerycomponentComponent, ApplicationcardComponent, CardscomponentComponent, FloatingactionareaComponent, NgxMasonryModule, NgbProgressbarModule, MatProgressBarModule,
    FormsModule, ReactiveFormsModule
  ],
  templateUrl: './otaapplication.component.html',
  styleUrl: './otaapplication.component.css'
})

export class OtaapplicationComponent {

  ngOnInit(): void {}
  ngOnDestroy(): void {}

  onButtonPressedEventCatch(value: {
    buttonName: string;
    action: Function;
  }) {
    console.log('Button pressed event caught in the ApplicationBodyComponent; value: ' + value.buttonName);
    value.action();
  };

  fileName: string | undefined;
  uploadProgress: number | undefined;

  constructor(private http: HttpClient, private loaderService: LoaderService, private postRequestsService: PostRequestsService,
    private appDialogService: AppDialogService, private webSocketService: WebSocketService) {}

  onFileSelected(event: any) {
      const file:File = event.target.files[0];

      if (file) {
          this.fileName = file.name;
          const formData = new FormData();
          formData.append("thumbnail", file);

          const upload$ = this.http.post("/api/thumbnail-upload", formData, {
              reportProgress: true,
              observe: 'events'
          })
      }
    }

  onUploadOTASubmitted(event: any) {
    const form = document.getElementById("form"); 
    const inputFile = (<HTMLInputElement>document.getElementById("file-upload"))
    const formData = new FormData();

    if (inputFile.files != null && inputFile.files[0] !== undefined) {
      console.log("Uploading OTA file")
      console.log("OTA file" + inputFile.files)
      this.loaderService.showLoader()
      const formData = new FormData()
  
      for(let i = 0; i < inputFile.files.length; ++i) {
        formData.append("filename", inputFile.files[i])
      }
      console.log("Uploaded file object: " + inputFile.files[0])

      this.postRequestsService.sendOTAFileFromFormDataUpload(formData).subscribe(
        (data) => {
          console.log('Data received: ', data);
          this.loaderService.hideLoader();
          const parsedResult = JSON.parse(JSON.stringify(data));
          if (parsedResult.result === 'successful') {
            this.appDialogService.showInfoDialog('OTA file was uploaded successfully');
          } else if (parsedResult.result === 'failed') {
            this.appDialogService.showErrorDialog('OTA file command sent, but completed with errors');
          }
        },

        error => {
          console.error('Error received: ', error.message);
          this.loaderService.hideLoader();
          this.appDialogService.showErrorDialog('Error: '+ error.message );
        }
      )
    } else {
      this.appDialogService.showErrorDialog('No file was selected for OTA upload');
    }
  }

  onRunChipOTAProvider() {
    console.log("Running Chip OTA Provider")
    var command = (document.getElementById("command") as (HTMLInputElement)).value
    var discriminator = (document.getElementById("discriminator") as (HTMLInputElement)).value
    var filePath = (document.getElementById("file-path") as (HTMLInputElement)).value
    if (command.length > 0 && discriminator.length > 0 && filePath.length > 0) {
      this.webSocketService.sendMessage(JSON.stringify(
        {
          command: command,
          discriminator: discriminator,
          filePath: filePath
        }
      ))
      this.appDialogService.showInfoDialog("Run Chip OTA Provider command sent through websockets")
    } else {
      this.appDialogService.showErrorDialog('Error running Chip OTA provider command, check the input fields');
    }
  }

  onRunACLOTAProvider() {
    console.log("Running Chip OTA provider Write-ACL")
    var chipotaprovider_nodeID = (document.getElementById("chip-ota-provider-device-nodeid") as (HTMLInputElement)).value
    if (chipotaprovider_nodeID) {
      this.loaderService.showLoader();

      this.postRequestsService.sendRunACLOTAProviderCommand(chipotaprovider_nodeID).subscribe(
        (data) => {
          console.log('Data received: ', data);
          this.loaderService.hideLoader();
          const parsedResult = JSON.parse(JSON.stringify(data));
          if (parsedResult.result === 'successful') {
            this.appDialogService.showInfoDialog('Command sent successfully');
          } else if (parsedResult.result === 'failed') {
            this.appDialogService.showErrorDialog('Command completed with errors');
          }
        },

        error => {
          console.error('Error received: ', error.message);
          this.loaderService.hideLoader();
          this.appDialogService.showErrorDialog('Error: '+ error.message);
        }
      )
    } else {
      this.appDialogService.showErrorDialog('Error running Chip OTA Write-ACL provider command, check the input fields');
    }
  }

  onRunOTASoftwareUpdateRequestor() {
    console.log("Running OTA sendRunOTASoftwareUpdateRequestorCommand command")
    var ota_provider_node_id = (document.getElementById("ota-provider-node-id") as (HTMLInputElement)).value
    var ota_requestor_node_id = (document.getElementById("ota-requestor-node-id") as (HTMLInputElement)).value

    if (ota_provider_node_id && ota_requestor_node_id) {
      this.loaderService.showLoader();

      this.postRequestsService.sendRunOTASoftwareUpdateRequestorCommand(ota_provider_node_id, ota_requestor_node_id).subscribe(
        (data) => {
          console.log('Data received: ', data);
          this.loaderService.hideLoader();
          const parsedResult = JSON.parse(JSON.stringify(data));
          if (parsedResult.result === 'successful') {
            this.appDialogService.showInfoDialog('Command sent successfully');
          } else if (parsedResult.result === 'failed') {
            this.appDialogService.showErrorDialog('Command completed with errors');
          }
        },

        error => {
          console.error('Error received: ', error.message);
          this.loaderService.hideLoader();
          this.appDialogService.showErrorDialog('Error: '+ error.message);
        }
      )
    } else {
      this.appDialogService.showErrorDialog('Error running OTA sendRunOTASoftwareUpdateRequestorCommand, check the input fields');
    }
  }

}
