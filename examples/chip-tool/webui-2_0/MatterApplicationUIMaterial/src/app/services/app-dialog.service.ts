import { Dialog, DialogConfig, DialogRef } from '@angular/cdk/dialog';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';
import { MatButtonModule } from '@angular/material/button';
import { MatIcon } from '@angular/material/icon';
import { CommonModule, NgIf } from '@angular/common';
import { Component, Input, NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { MatRipple, MatRippleModule } from '@angular/material/core';

import {
  MatDialog,
  MatDialogRef,
  MatDialogActions,
  MatDialogClose,
  MatDialogTitle,
  MatDialogContent,
} from '@angular/material/dialog';

import { PopupdialogmaterialComponent } from '../popupdialogmaterial/popupdialogmaterial.component';
import { QrScannerComponent } from '../applicationheader/qrscanner/qrscanner.component';
import { BasePortalOutlet } from '@angular/cdk/portal';

type QrScanResult = string | null;

@Injectable (
  {
    providedIn: 'root'
  }
)

export class AppDialogService {
  dialogConfig: DialogConfig = {
    panelClass: 'dialog-container',
  };

  dialogState: unknown;
  dialogRef?: DialogRef<unknown, any> | null;

  constructor(private dialog: Dialog) {}

  openDialog(title: string, dialogImageSrc: string, content: string, buttons: {buttonName: string, action: Function, color: string, icon?: string}[])
  : DialogRef<unknown,PopupdialogmaterialComponent> {
    this.dialogRef = this.dialog.open(PopupdialogmaterialComponent,
      {
        panelClass: 'dialog-container',
        data: {dialogImageSrc: dialogImageSrc, dialogTitle: title, dialogContent: content, dialogButtons: buttons}
      }
    );

    this.dialogRef.closed.subscribe((result : unknown) => {
      console.log(`Dialog result: ${result}`);
    });

    this.dialogRef.componentInstance!.dialogImageSrc = dialogImageSrc;
    this.dialogRef.componentInstance!.dialogTitle = title;
    this.dialogRef.componentInstance!.dialogContent = content;
    this.dialogRef.componentInstance!.dialogButtons = buttons;

    //return this.dialogRef;
    return this.dialogRef as DialogRef<unknown, PopupdialogmaterialComponent>;
  }

  openQrcodeDialog(title: string, dialogImageSrc: string, content: string, qrCodeImage: HTMLImageElement | null, buttons: { buttonName: string, action: Function, color: string, icon?: string }[])
  : DialogRef<unknown, PopupdialogmaterialComponent> {
    this.dialogRef = this.dialog.open(PopupdialogmaterialComponent,
      {
        panelClass: 'dialog-container',
        data: { dialogImageSrc: dialogImageSrc, dialogTitle: title, dialogContent: content, dialogButtons: buttons }
      }
    );

    this.dialogRef.closed.subscribe((result: unknown) => {
      console.log(`Dialog result: ${result}`);
    });

    this.dialogRef.componentInstance!.dialogImageSrc = dialogImageSrc;
    this.dialogRef.componentInstance!.dialogTitle = title;
    this.dialogRef.componentInstance!.dialogContent = content;
    this.dialogRef.componentInstance!.qrCodeImage = qrCodeImage;
    this.dialogRef.componentInstance!.dialogButtons = buttons;

    //return this.dialogRef;
    return this.dialogRef as DialogRef<unknown, PopupdialogmaterialComponent>;
  }

  openQrcodeScanDialog(config?: Partial<DialogConfig>): DialogRef<QrScanResult, QrScannerComponent> {
    // Define default config for the QR scanner dialog
    const defaultConfig: DialogConfig = {
      panelClass: ['qr-scanner-dialog-container', 'dialog-container'],
      disableClose: true,
    };

    // Merge default config with user-provided config
    const combinedConfig = { ...defaultConfig, ...config, data: null };

    // Open the dialog, specifying Result type, Data type (use `undefined` or `void` if none), and Component type
    const qrDialogRef = this.dialog.open<QrScanResult, undefined, QrScannerComponent>(
      QrScannerComponent,
      combinedConfig as DialogConfig<undefined, DialogRef<QrScanResult, QrScannerComponent>, BasePortalOutlet>
    );

    // Logging is fine here, but the caller should primarily use the returned ref's `closed` observable.
    qrDialogRef.closed.subscribe(result => {
      console.log(`QR Scanner Dialog closed with result: ${result === null ? 'null' : `"${result}"`}`);
    });

    return qrDialogRef;
  }

  showQrCodeScanDialog(config?: Partial<DialogConfig>): Observable<QrScanResult> {
    const dialogRef = this.openQrcodeScanDialog(config);

    // Return the closed observable, mapping undefined to null for consistency.
    return dialogRef.closed.pipe(
      map(result => (result === undefined ? null : result)) // Ensure result is string | null
    );
  }

  closeDialog() : void {
    this.dialogRef?.close();
  }
  reset () : void {
    this.dialogState = null;
  }

  showErrorDialog(error: string) : void {
    this.openDialog('Error', '../../../assets/warning.png', error, [{buttonName: 'OK', action: () => this.closeDialog(), color: 'primary'}]);
  }

  showInfoDialog(info: string) : void {
    this.openDialog('Information', '../../../assets/information.png', info, [{buttonName: 'OK', action: () => this.closeDialog(), color: 'primary'}]);
  }

  showQrCodeInfoDialog(info: string, qrCodeImage: HTMLImageElement): void {
    this.openQrcodeDialog('Node Interaction', '../../../assets/information.png', info, qrCodeImage, [{ buttonName: 'OK', action: () => this.closeDialog(), color: 'primary' }]);
  }

  showWarningDialog(warning: string) : void {
    this.openDialog('Warning', '../../../assets/warning.png', warning, [{buttonName: 'OK', action: () => this.closeDialog(), color: 'primary'}]);
  }

  showConfirmDialog(confirm: string, action: Function) : void {
    this.openDialog('Confirm', '../../../assets/information.png', confirm, [{buttonName: 'Yes', action: action, color: 'primary'}, {buttonName: 'No', action: () => this.closeDialog(), color: 'warn'}]);
  }

  showCustomDialog(title: string, dialogImageSrc: string, content: string, buttons: {buttonName: string, action: Function, color: string, icon?: string}[]) : void {
    this.openDialog(title, dialogImageSrc, content, buttons);
  }

  showNotImplementedDialog() : void {
    this.openDialog('Work in progress, not yet implemented', '../../../assets/warning.png', 'This function is not yet implemented.', []);
  }

}
