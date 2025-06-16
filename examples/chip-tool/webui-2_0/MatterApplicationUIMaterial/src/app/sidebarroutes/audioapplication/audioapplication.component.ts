import { HttpClient } from '@angular/common/http';
import { FloatingactionareaComponent } from './../../mainapplicationbody/floatingactionarea/floatingactionarea.component';
import { Component } from '@angular/core';
import { MatCardModule } from '@angular/material/card';
import { MatIcon, MatIconModule } from '@angular/material/icon';
import { ScrollgallerycomponentComponent } from '../../mainapplicationbody/scrollgallerycomponent/scrollgallerycomponent.component';
import { MatFormField } from '@angular/material/form-field';
import { MatLabel } from '@angular/material/form-field';

import { MatSelectModule} from '@angular/material/select';
import { MatInputModule} from '@angular/material/input';
import { MatFormFieldModule} from '@angular/material/form-field';
import { MatChip } from '@angular/material/chips';
import { FloatingActionAreaComponentActions } from '../../mainapplicationbody/floatingactionarea/floating-action-area-component-actions';
import { AppDialogService } from '../../services/app-dialog.service';
import { PostRequestsService } from '../../services/post-requests.service';
import { LoaderService } from '../../services/loader.service';

@Component({
  selector: 'app-audioapplication',
  standalone: true,
  // Import mat-card module
  imports: [MatCardModule, MatIconModule,
    ScrollgallerycomponentComponent,
    MatFormField, MatLabel, MatFormFieldModule, MatInputModule, MatSelectModule, MatChip, FloatingactionareaComponent
  ],
  templateUrl: './audioapplication.component.html',
  styleUrl: './audioapplication.component.css'
})

export class AudioapplicationComponent {
  constructor(private httpClient: HttpClient, private appDialogService: AppDialogService, private postRequestsService: PostRequestsService,
    private loaderService: LoaderService
  ) {}

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
      nodeAlias: (document.getElementById("nodealias-input") as HTMLInputElement).value,
      endpointId: (document.getElementById("endpoint-input") as HTMLInputElement).value
    }
  }
  // Play media control
  onPlayAppMediaControl() : void {
    console.log('Play app starting');
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendPlayAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "play"
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Play media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Play media control completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }
  // Pause media control
  onPauseAppMediaControl() : void {
    console.log('Pause app starting')
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendPauseAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "pause"
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Pause media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Pause media control completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }
  // Stop media control
  onStopAppMediaControl() : void {
    console.log('Stop app starting')
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendStopAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "stop"
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Stop media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Stop media control completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }

  // Startover media control
  onStartOverAppMediaControl() : void {
    console.log('StartOver app starting')
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendStartOverAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "startover"
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Startover media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Startover media control completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }
  // Previous media control
  onPreviousAppMediaControl() : void {
    console.log('Previous app starting')
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendPreviousAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "previous"
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Previous media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Previous media control completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }
  // Next media control
  onNextAppMediaControl() : void {
    console.log('Next app starting')
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendNextAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "next"
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Next media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Next media control completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }
  // Rewind media control
  onRewindAppMediaControl() : void {
    console.log('Rewind app starting')
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendRewindAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "rewind"
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Rewind media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Rewind media control completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }

  // Fast forward media
  onFastForwardAppMediaControl() : void {
    console.log('Fastforward app starting')
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendFastForwardAppMediaControlCommmand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, "fastforward"
    ).subscribe(
      data => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('FastForward media control completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('FastForward media control completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }

  // Read

  onCurrentStateMediaRead(command: string) : void {
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    interface ResponseIfce {
      report: string,
      result: string
    }

    this.postRequestsService.sendOnMediaReadMediaControlCommand(
      values_for_the_input.nodeId, values_for_the_input.endpointId, command, values_for_the_input.nodeAlias
    ).subscribe(
      (data: any) => {
        data = data as ResponseIfce;
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog(`Media read completed successfully. The report is ` + data.report);
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Media read completed with errors');
        }
      },

      error => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }


  onLaunchButtonApplicationPress () : void {
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendMediaControlLaunchCommand(
      values_for_the_input.nodeId, values_for_the_input.endpointId
    ).subscribe(
      (data: any)  => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Launch control media request completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Launch control media request completed with errors');
        }
      },

      (error: any)  => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

  onStopButtonApplicationPress() : void {
    var values_for_the_input = this.getInputFieldsCurrentValue()
    this.loaderService.showLoader();

    this.postRequestsService.sendMediaControlStopCommand(
      values_for_the_input.nodeId, values_for_the_input.endpointId
    ).subscribe(
      (data: any)  => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Stop control media request completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Stop control media request completed with errors');
        }
      },

      (error: any)  => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    )
  }

}
