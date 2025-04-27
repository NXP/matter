import { EndpointModel } from './../../models/endpoint-model';
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
import { HttpClient } from '@angular/common/http';
import { AppDialogService } from '../../services/app-dialog.service';
import { PostRequestsService } from '../../services/post-requests.service';
import { LoaderService } from '../../services/loader.service';

@Component({
  selector: 'app-bindingapplication',
  standalone: true,
  imports: [MatCardModule, MatIconModule,
    ScrollgallerycomponentComponent,
    MatFormField, MatLabel, MatFormFieldModule, MatInputModule, MatSelectModule, MatChip, FloatingactionareaComponent, SettingsapplicationComponent],
  templateUrl: './bindingapplication.component.html',
  styleUrl: './bindingapplication.component.css'
})
export class BindingapplicationComponent {
  constructor(private httpClient: HttpClient, private appDialogService: AppDialogService, private postRequestsService: PostRequestsService,
    private loaderService: LoaderService
  ) {}

  getInputFieldsCurrentValueACL() {
    return {
      lightNodeId: (document.getElementById("light-node-id") as HTMLInputElement).value,
      switchNodeId: (document.getElementById("switch-node-id") as HTMLInputElement).value,
      aclEndpointId: (document.getElementById("acl-endpoint-id") as HTMLInputElement).value
    }
  }

  getInputFieldsCurrentValueBinding() {
    return {
      lightNodeId: (document.getElementById("light-node-id") as HTMLInputElement).value,
      lightEndpointId: (document.getElementById("light-endpoint-id") as HTMLInputElement).value,
      switchNodeId: (document.getElementById("switch-node-id") as HTMLInputElement).value,
      switchEndpointId: (document.getElementById("switch-endpoint-id") as HTMLInputElement).value
    }
  }

  onButtonPressedEventCatch(value: {
    buttonName: string;
    action: Function;
  }) {
    console.log('Button pressed event caught in the ApplicationBodyComponent; value: ' + value.buttonName);
    value.action();
  };

  onPressedWriteACLCommand() {
    var values_for_the_input = this.getInputFieldsCurrentValueACL()
    this.loaderService.showLoader();

    this.postRequestsService.sendWriteACLBindingCommand(
      values_for_the_input.lightNodeId, values_for_the_input.switchNodeId, values_for_the_input.aclEndpointId
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Write ACL command completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Write ACL command completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }

  onPressedWriteBindingCommand() {
    var values_for_the_input = this.getInputFieldsCurrentValueBinding()
    this.loaderService.showLoader();

    this.postRequestsService.sendWriteBindingCommand(
      values_for_the_input.lightNodeId, values_for_the_input.lightEndpointId, values_for_the_input.switchNodeId, values_for_the_input.switchEndpointId
    ).subscribe(
      (data: any) => {
        console.log('Data received: ', data);
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog('Write Binding completed successfully');
        } else if (parsedResult.result === 'failed') {
          this.appDialogService.showErrorDialog('Write Binding completed with errors');
        }
      },

      (error: string) => {
        console.error('Error received: ', error);
        this.loaderService.hideLoader();
        this.appDialogService.showErrorDialog('Error: '+ error);
      }
    );
  }

}
