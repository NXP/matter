import { Component, Input } from '@angular/core';

import {
  MatDialog,
  MatDialogRef,
  MatDialogActions,
  MatDialogClose,
  MatDialogTitle,
  MatDialogContent,
} from '@angular/material/dialog';

import { MatButtonModule } from '@angular/material/button';
import { MatIcon } from '@angular/material/icon';
import { CommonModule, NgIf } from '@angular/common';
import { BrowserModule } from '@angular/platform-browser';
import { Dialog, DialogModule, DialogRef } from '@angular/cdk/dialog';
import { MatRipple, MatRippleModule } from '@angular/material/core';
import { MatChip, MatChipsModule } from '@angular/material/chips';
import { Pipe, PipeTransform } from '@angular/core';
import { DomSanitizer, SafeHtml } from '@angular/platform-browser';

@Pipe({ name: 'newlineToBr', standalone: true })
export class NewlineToBrPipe implements PipeTransform {
  constructor(private sanitizer: DomSanitizer) {}
  transform(value: string): SafeHtml {
    if (!value) return value;
    const escaped = value.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
    return this.sanitizer.bypassSecurityTrustHtml(escaped.replace(/\n/g, '<br>'));
  }
}

@Component({
  selector: 'app-popupdialogmaterial',
  standalone: true,
  imports: [MatButtonModule, MatDialogActions, MatRippleModule, MatDialogClose, MatDialogTitle, MatDialogContent, MatIcon, NgIf, CommonModule, DialogModule, MatChip, MatChipsModule, NewlineToBrPipe],
  templateUrl: './popupdialogmaterial.component.html',
  styleUrl: './popupdialogmaterial.component.css'
})

export class PopupdialogmaterialComponent {
  constructor(public dialogRef: DialogRef<PopupdialogmaterialComponent>) { }

  dialogType: string = 'info';

  @Input() dialogImageSrc!: string;
  @Input() dialogTitle!: string;
  @Input() dialogContent!: any;
  @Input() qrCodeImage: HTMLImageElement | null = null;
  @Input() dialogButtons!: { buttonName: string, action: Function, color: string, icon?: string }[];

  onNoClick(): void {
    this.dialogRef.close();
  }

  onYesClick(): void {
    this.dialogRef.close();
  }

  closeDialog(): void {
    this.dialogRef.close();
  }

  onActionClick(action: Function): void {
    action();
  }

  public getDialogTitle(): string {
    return this.dialogTitle;
  }

  public getDialogContent(): string {
    return this.dialogContent;
  }

  public getDialogButtons(): {buttonName: string, action: Function, color: string, icon?: string }[] {
    return this.dialogButtons;
  }
}
