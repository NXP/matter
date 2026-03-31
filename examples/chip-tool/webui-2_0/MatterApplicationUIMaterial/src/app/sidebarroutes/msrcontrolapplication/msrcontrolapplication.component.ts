import { Component, OnInit, OnDestroy, ViewChild, ElementRef } from '@angular/core';
import { MatCardModule } from '@angular/material/card';
import { MatFormField, MatFormFieldModule, MatLabel } from '@angular/material/form-field';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
import { MatInputModule } from '@angular/material/input';
import { MatSelectModule } from '@angular/material/select';
import { MatChip } from '@angular/material/chips';
import { MatTabsModule } from '@angular/material/tabs';
import { MatTooltipModule } from '@angular/material/tooltip';
import { NgFor, NgIf } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { FloatingactionareaComponent } from '../../mainapplicationbody/floatingactionarea/floatingactionarea.component';
import { LoaderService } from '../../services/loader.service';
import { AppDialogService } from '../../services/app-dialog.service';
import { PostRequestsService } from '../../services/post-requests.service';
import { Subscription, interval } from 'rxjs';

export interface SubscriptionLog {
  timestamp: string;
  type: 'runmode' | 'cleanmode';
  value: string;
}

@Component({
  selector: 'app-msrcontrolapplication',
  standalone: true,
  imports: [
    MatCardModule,
    MatIconModule,
    MatButtonModule,
    MatFormField,
    MatLabel,
    MatFormFieldModule,
    MatInputModule,
    MatSelectModule,
    MatChip,
    MatTabsModule,
    MatTooltipModule,
    NgFor,
    NgIf,
    FormsModule,
    FloatingactionareaComponent
  ],
  templateUrl: './msrcontrolapplication.component.html',
  styleUrl: '../sidebarroutes.share.css'
})
export class MsrcontrolapplicationComponent implements OnInit, OnDestroy {
  @ViewChild('subscribeLogContainer') subscribeLogContainer!: ElementRef;

  nodeId: string = '';
  nodeAlias: string = '';
  endpointId: string = '1';

  selectedRunMode: number = 0;
  runModes = [
    { value: 0, label: 'Idle' },
    { value: 1, label: 'Cleaning' },
    { value: 2, label: 'Mapping' }
  ];

  selectedCleanMode: number = 0;
  cleanModes = [
    { value: 0, label: 'Quick' },
    { value: 1, label: 'Auto' },
    { value: 2, label: 'Deep Clean' },
    { value: 3, label: 'Quiet' },
    { value: 4, label: 'Max Vac' },
    { value: 5, label: 'Vacuum Then Mop' }
  ];

  selectedAreaId: string = '';

  isRunModeSubscribed: boolean = false;
  isCleanModeSubscribed: boolean = false;
  runModeLogs: SubscriptionLog[] = [];
  cleanModeLogs: SubscriptionLog[] = [];
  private maxLogsPerType: number = 2;

  private subscriptions: Subscription[] = [];
  private runModePollingSubscription: Subscription | null = null;
  private cleanModePollingSubscription: Subscription | null = null;

  constructor(
    private loaderService: LoaderService,
    private appDialogService: AppDialogService,
    private postRequestsService: PostRequestsService
  ) {}

  ngOnInit(): void {}

  ngOnDestroy(): void {
    this.subscriptions.forEach(sub => sub.unsubscribe());
    this.stopRunModePolling();
    this.stopCleanModePolling();
  }

  onButtonPressedEventCatch(value: { buttonName: string; action: Function }) {
    console.log('Button pressed event caught; value: ' + value.buttonName);
    value.action();
  }

  toggleRunModeSubscription(): void {
    if (this.isRunModeSubscribed) {
      this.stopRunModePolling();
      this.isRunModeSubscribed = false;
      this.addSubscriptionLog('runmode', 'Subscription stopped');
    } else {
      if (!this.validateBasicFields()) return;
      this.startRunModePolling();
      this.isRunModeSubscribed = true;
      this.addSubscriptionLog('runmode', 'Subscription started');
    }
  }

  toggleCleanModeSubscription(): void {
    if (this.isCleanModeSubscribed) {
      this.stopCleanModePolling();
      this.isCleanModeSubscribed = false;
      this.addSubscriptionLog('cleanmode', 'Subscription stopped');
    } else {
      if (!this.validateBasicFields()) return;
      this.startCleanModePolling();
      this.isCleanModeSubscribed = true;
      this.addSubscriptionLog('cleanmode', 'Subscription started');
    }
  }

  private startRunModePolling(): void {
    this.fetchRunModeCurrentMode();
    this.runModePollingSubscription = interval(5000).subscribe(() => {
      this.fetchRunModeCurrentMode();
    });
  }

  private stopRunModePolling(): void {
    if (this.runModePollingSubscription) {
      this.runModePollingSubscription.unsubscribe();
      this.runModePollingSubscription = null;
    }
  }

  private startCleanModePolling(): void {
    this.fetchCleanModeCurrentMode();
    this.cleanModePollingSubscription = interval(5000).subscribe(() => {
      this.fetchCleanModeCurrentMode();
    });
  }

  private stopCleanModePolling(): void {
    if (this.cleanModePollingSubscription) {
      this.cleanModePollingSubscription.unsubscribe();
      this.cleanModePollingSubscription = null;
    }
  }

  private fetchRunModeCurrentMode(): void {
    this.postRequestsService.sendMSRReadCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      'rvcrunmode',
      'current-mode'
    ).subscribe({
      next: (data: any) => {
        const modeValue = data.report || data.data || 'Unknown';
        const modeLabel = this.getRunModeLabel(modeValue);
        this.addSubscriptionLog('runmode', `Current Mode: ${modeLabel} (${modeValue})`);
      },
      error: (error: string) => {
        this.addSubscriptionLog('runmode', `Error: ${error}`);
      }
    });
  }

  private fetchCleanModeCurrentMode(): void {
    this.postRequestsService.sendMSRReadCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      'rvccleanmode',
      'current-mode'
    ).subscribe({
      next: (data: any) => {
        const modeValue = data.report || data.data || 'Unknown';
        const modeLabel = this.getCleanModeLabel(modeValue);
        this.addSubscriptionLog('cleanmode', `Current Mode: ${modeLabel} (${modeValue})`);
      },
      error: (error: string) => {
        this.addSubscriptionLog('cleanmode', `Error: ${error}`);
      }
    });
  }

  private getRunModeLabel(value: any): string {
    const numValue = typeof value === 'string' ? parseInt(value, 10) : value;
    const mode = this.runModes.find(m => m.value === numValue);
    return mode ? mode.label : 'Unknown';
  }

  private getCleanModeLabel(value: any): string {
    const numValue = typeof value === 'string' ? parseInt(value, 10) : value;
    const mode = this.cleanModes.find(m => m.value === numValue);
    return mode ? mode.label : 'Unknown';
  }

  private addSubscriptionLog(type: 'runmode' | 'cleanmode', value: string): void {
    const now = new Date();
    const timestamp = now.toLocaleTimeString('en-US', { hour12: false });
    
    if (type === 'runmode') {
      this.runModeLogs.unshift({ timestamp, type, value });
      if (this.runModeLogs.length > this.maxLogsPerType) {
        this.runModeLogs = this.runModeLogs.slice(0, this.maxLogsPerType);
      }
    } else {
      this.cleanModeLogs.unshift({ timestamp, type, value });
      if (this.cleanModeLogs.length > this.maxLogsPerType) {
        this.cleanModeLogs = this.cleanModeLogs.slice(0, this.maxLogsPerType);
      }
    }
  }

  clearSubscriptionLogs(): void {
    this.runModeLogs = [];
    this.cleanModeLogs = [];
  }

  get hasSubscriptionLogs(): boolean {
    return this.runModeLogs.length > 0 || this.cleanModeLogs.length > 0;
  }

  changeRunMode(): void {
    if (!this.validateBasicFields()) return;
    this.loaderService.showLoader();
    this.postRequestsService.sendMSRRunModeChangeCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      this.selectedRunMode
    ).subscribe({
      next: (data: any) => {
        this.handleSuccessResponse(data, 'MSR Run Mode change');
      },
      error: (error: string) => {
        this.handleErrorResponse(error, 'MSR Run Mode change');
      }
    });
  }

  readRunModeCurrentMode(): void {
    this.readMSRAttribute('rvcrunmode', 'current-mode');
  }

  readRunModeSupportedModes(): void {
    this.readMSRAttribute('rvcrunmode', 'supported-modes');
  }

  changeCleanMode(): void {
    if (!this.validateBasicFields()) return;
    this.loaderService.showLoader();
    this.postRequestsService.sendMSRCleanModeChangeCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      this.selectedCleanMode
    ).subscribe({
      next: (data: any) => {
        this.handleSuccessResponse(data, 'MSR Clean Mode change');
      },
      error: (error: string) => {
        this.handleErrorResponse(error, 'MSR Clean Mode change');
      }
    });
  }

  readCleanModeCurrentMode(): void {
    this.readMSRAttribute('rvccleanmode', 'current-mode');
  }

  readCleanModeSupportedModes(): void {
    this.readMSRAttribute('rvccleanmode', 'supported-modes');
  }

  operationalStateGoHome(): void {
    this.sendOperationalStateCommand('go-home');
  }

  operationalStateResume(): void {
    this.sendOperationalStateCommand('resume');
  }

  operationalStatePause(): void {
    this.sendOperationalStateCommand('pause');
  }

  readOperationalState(): void {
    this.readMSRAttribute('rvcoperationalstate', 'operational-state');
  }

  readOperationalError(): void {
    this.readMSRAttribute('rvcoperationalstate', 'operational-error');
  }

  readSupportedMaps(): void {
    this.readMSRAttribute('servicearea', 'supported-maps');
  }

  readSupportedAreas(): void {
    this.readMSRAttribute('servicearea', 'supported-areas');
  }

  readSelectedAreas(): void {
    this.readMSRAttribute('servicearea', 'selected-areas');
  }

  readCurrentArea(): void {
    this.readMSRAttribute('servicearea', 'current-area');
  }

  selectAreas(): void {
    if (!this.validateBasicFields()) return;
    if (!this.selectedAreaId) {
      this.appDialogService.showErrorDialog('Please enter Area ID');
      return;
    }
    this.loaderService.showLoader();
    this.postRequestsService.sendServiceAreaSelectCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      this.selectedAreaId
    ).subscribe({
      next: (data: any) => {
        this.handleSuccessResponse(data, 'Service Area select');
      },
      error: (error: string) => {
        this.handleErrorResponse(error, 'Service Area select');
      }
    });
  }

  skipArea(): void {
    if (!this.validateBasicFields()) return;
    if (!this.selectedAreaId) {
      this.appDialogService.showErrorDialog('Please enter Area ID');
      return;
    }
    this.loaderService.showLoader();
    this.postRequestsService.sendServiceAreaSkipCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      this.selectedAreaId
    ).subscribe({
      next: (data: any) => {
        this.handleSuccessResponse(data, 'Service Area skip');
      },
      error: (error: string) => {
        this.handleErrorResponse(error, 'Service Area skip');
      }
    });
  }

  private sendOperationalStateCommand(command: string): void {
    if (!this.validateBasicFields()) return;
    this.loaderService.showLoader();
    this.postRequestsService.sendMSROperationalStateCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      command
    ).subscribe({
      next: (data: any) => {
        this.handleSuccessResponse(data, `MSR Operational State ${command}`);
      },
      error: (error: string) => {
        this.handleErrorResponse(error, `MSR Operational State ${command}`);
      }
    });
  }

  private readMSRAttribute(cluster: string, attribute: string): void {
    if (!this.validateBasicFields()) return;
    this.loaderService.showLoader();
    this.postRequestsService.sendMSRReadCommand(
      this.nodeId,
      this.nodeAlias,
      this.endpointId,
      cluster,
      attribute
    ).subscribe({
      next: (data: any) => {
        this.loaderService.hideLoader();
        const parsedResult = JSON.parse(JSON.stringify(data));
        if (parsedResult.result === 'successful') {
          this.appDialogService.showInfoDialog(
            `Read ${cluster} ${attribute} completed successfully. Result: ${parsedResult.report}`
          );
        } else {
          const cause = parsedResult.cause || 'unknown error';
          this.appDialogService.showErrorDialog(`Read ${cluster} ${attribute} failed: ${cause}`);
        }
      },
      error: (error: string) => {
        this.handleErrorResponse(error, `Read ${cluster} ${attribute}`);
      }
    });
  }

  private validateBasicFields(): boolean {
    if (!this.nodeId) {
      this.appDialogService.showErrorDialog('Please enter Device ID');
      return false;
    }
    if (!this.endpointId) {
      this.appDialogService.showErrorDialog('Please enter Endpoint ID');
      return false;
    }
    return true;
  }

  private handleSuccessResponse(data: any, commandName: string): void {
    this.loaderService.hideLoader();
    const parsedResult = JSON.parse(JSON.stringify(data));
    if (parsedResult.result === 'successful') {
      this.appDialogService.showInfoDialog(`${commandName} completed successfully`);
    } else {
      const cause = parsedResult.cause || 'unknown error';
      this.appDialogService.showErrorDialog(`${commandName} failed: ${cause}`);
    }
  }

  private handleErrorResponse(error: string, commandName: string): void {
    console.error(`Error in ${commandName}:`, error);
    this.loaderService.hideLoader();
    this.appDialogService.showErrorDialog(`Error: ${error}`);
  }
}
