import { Dialog, DialogConfig, DialogRef } from '@angular/cdk/dialog';
import {Injectable} from '@angular/core';

import {
  MatDialog,
  MatDialogRef,
  MatDialogActions,
  MatDialogClose,
  MatDialogTitle,
  MatDialogContent,
} from '@angular/material/dialog';

import {MatButtonModule} from '@angular/material/button';
import { MatIcon } from '@angular/material/icon';
import { CommonModule, NgIf } from '@angular/common';
import { Component, Input, NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import {MatRipple, MatRippleModule} from '@angular/material/core';

import { PopupdialogmaterialComponent } from '../popupdialogmaterial/popupdialogmaterial.component';
import { PopupdialogwithinputfieldsmaterialComponent } from '../popupdialogwithinputfieldsmaterial/popupdialogwithinputfieldsmaterial.component';

@Injectable (
  {
    providedIn:'root'
  }
)

export class AppDialogWithInputFieldsService {

  dialogConfig : DialogConfig = {
    panelClass: 'dialog-container',
  };

  dialogState: unknown;
  dialogRef? : DialogRef<unknown, PopupdialogwithinputfieldsmaterialComponent> | null;

  constructor(private dialog: Dialog) {}
  /*
  * Open a dialog with the specified title, image source, content, and buttons
  * @param title: string
  * @param dialogImageSrc: string
  * @param content: {{inputFieldType: string, inputFieldName: string, inputFieldContent: string, inputFieldDefaultValue: string}[]}
  * @param buttons: {buttonName: string, action: Function, color: string, icon?: string}[]
  * @return DialogRef<unknown, PopupdialogmaterialComponent>
  * */
  openDialog(title: string, dialogImageSrc: string, content:
    {
      inputFields: {inputFieldType: string, inputFieldName: string, inputFieldContent: string, inputFieldDefaultValue: string}[]
    }
    , buttons: {buttonName: string, action: Function, color: string, icon?: string}[])
  : DialogRef<unknown,PopupdialogwithinputfieldsmaterialComponent> {
    this.dialogRef = this.dialog.open(PopupdialogwithinputfieldsmaterialComponent,
      {
        panelClass: 'dialog-container',
        data: {dialogImageSrc: dialogImageSrc, dialogTitle: title, dialogContent: content, dialogButtons: buttons}
      }
    );

    this.dialogRef.closed.subscribe((result : unknown) => {
      console.log(`Dialog result: ${result}`);
      this.dialogRef = null;
    });

    //this.dialogRef.componentInstance!.dialogImageSrc = dialogImageSrc;
    //this.dialogRef.componentInstance!.dialogTitle = title;
    //this.dialogRef.componentInstance!.dialogContent = content;
    //this.dialogRef.componentInstance!.dialogButtons = buttons;

    if (this.dialogRef.componentInstance) {
      this.dialogRef.componentInstance.dialogImageSrc = dialogImageSrc;
      this.dialogRef.componentInstance.dialogTitle = title;
      this.dialogRef.componentInstance.dialogContent = content;
      this.dialogRef.componentInstance.dialogButtons = buttons;
    } else {
        console.warn("app-dialog-input service: componentInstance is not available immediately after open. This might be an issue if inputs are not set via DIALOG_DATA.");
    }

    return this.dialogRef;
  }

  openDialogWithSelectionItems(title: string, dialogImageSrc: string, content:  {
    inputFields: {inputFieldType: string, inputFieldName: string, inputFieldContent: string, inputFieldDefaultValue: string}[]
  }, buttons: {buttonName: string, action: Function, color: string, icon?: string}[], availableSelectionItems?: {name: string, color: string}[]) {

    this.dialogRef = this.dialog.open(PopupdialogwithinputfieldsmaterialComponent,
      {
        panelClass: 'dialog-container',
        data: {dialogImageSrc: dialogImageSrc, dialogTitle: title, dialogContent: content, dialogButtons: buttons, dialogAvailableSelectionItems: availableSelectionItems}
      }
    );

    this.dialogRef.closed.subscribe((result : unknown) => {
      console.log(`Dialog result: ${result}`);
    });

    //this.dialogRef.componentInstance!.dialogImageSrc = dialogImageSrc;
    //this.dialogRef.componentInstance!.dialogTitle = title;
    //this.dialogRef.componentInstance!.dialogContent = content;
    //this.dialogRef.componentInstance!.dialogButtons = buttons;
    //this.dialogRef.componentInstance!.dialogAvailableSelectionItems = availableSelectionItems;

    if (this.dialogRef.componentInstance) {
      this.dialogRef.componentInstance.dialogImageSrc = dialogImageSrc;
      this.dialogRef.componentInstance.dialogTitle = title;
      this.dialogRef.componentInstance.dialogContent = content;
      this.dialogRef.componentInstance.dialogButtons = buttons;
      this.dialogRef.componentInstance.dialogAvailableSelectionItems = availableSelectionItems;
    } else {
      console.warn("app-dialog-input service: componentInstance is not available immediately after open for selection dialog.");
    }

    return this.dialogRef;
  }

  getInputFieldsValues() {
    return this.dialogRef?.componentInstance?.getInputFields();
  }

  closeDialog(): void {
    if (this.dialogRef) {
      this.dialogRef.close();
    }
  }

  getSelectedDialogSelectionItem() : string | undefined {
    return this.dialogRef?.componentInstance?.selectedSelectionItem;
  }

  /*updateInputFieldContent(input_field_index: number, data: any): void {
    if (this.dialogRef?.componentInstance?.dialogContent.inputFields === undefined) {
      return;
    }
    for (let i = 0; i < this.dialogRef?.componentInstance?.dialogContent.inputFields.length; i++) {
      if (i === input_field_index && this.dialogRef?.componentInstance?.dialogContent.inputFields[i] !== undefined
        && this.dialogRef && this.dialogRef.componentInstance && this.dialogRef.componentInstance.dialogContent.inputFields[i] !== undefined
        && this.dialogRef.componentInstance.dialogContent.inputFields[i].inputFieldContent !== undefined
      ){
        this.dialogRef.componentInstance.dialogContent.inputFields[i].inputFieldContent = data;
      }
    }
  }*/
  updateInputFieldContent(input_field_index: number, data: any): void {
    if (!this.dialogRef || !this.dialogRef.componentInstance) {
      console.error('Service app-dialog-input: updateInputFieldContent - dialogRef or componentInstance is not available.');
      return;
    }

    const componentInst = this.dialogRef.componentInstance;

    if (!componentInst.dialogContent || !componentInst.dialogContent.inputFields) {
      console.error('Service app-dialog-input: updateInputFieldContent - dialogContent or inputFields not found on componentInstance.');
      return;
    }

    const inputFields = componentInst.dialogContent.inputFields;

    if (input_field_index >= 0 && input_field_index < inputFields.length) {
      console.log(`Service app-dialog-input: Updating field [${input_field_index}] from "${inputFields[input_field_index].inputFieldContent}" to "${data}"`);

      inputFields[input_field_index].inputFieldContent = String(data);
      console.log('Service app-dialog-input: Input field content updated on component instance.');

      if (typeof componentInst.refreshView === 'function') {
        console.log('Service app-dialog-input: Calling refreshView() on component instance.');
        componentInst.refreshView();
      } else {
        console.warn('Service app-dialog-input: refreshView() method not found on component instance. UI might not update.');
      }

    } else {
      console.error(`Service app-dialog-input: updateInputFieldContent - Invalid input_field_index: ${input_field_index}. Available fields: ${inputFields.length}`);
    }
  }

}
