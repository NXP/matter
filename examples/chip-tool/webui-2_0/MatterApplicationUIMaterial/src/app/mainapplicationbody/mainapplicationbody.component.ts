import { Component, ElementRef, HostListener, ViewChild } from '@angular/core';
import { NgbModal } from '@ng-bootstrap/ng-bootstrap';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import {MatCard, MatCardModule} from '@angular/material/card';
import { NgClass, NgFor, NgIf, NgStyle } from '@angular/common';
import { ScrollgallerycomponentComponent } from './scrollgallerycomponent/scrollgallerycomponent.component';
import { ApplicationcardComponent } from '../applicationcard/applicationcard.component';

// Models import
import { CardModel } from '../models/card-model';
import { EndpointModel } from '../models/endpoint-model';
import { LightingModel } from '../models/lighting-model';
import { DimmableLightModel } from '../models/dimmable-light-model';
import { CardscomponentComponent } from './cardscomponent/cardscomponent.component';
import { FloatingactionareaComponent } from './floatingactionarea/floatingactionarea.component';
import { MatDialog } from '@angular/material/dialog';

@Component({
  selector: 'app-mainapplicationbody',
  standalone: true,
  imports: [NgbModule, MatCardModule, MatCard, NgClass, NgFor, NgIf, NgStyle,
     ScrollgallerycomponentComponent, ApplicationcardComponent, CardscomponentComponent, FloatingactionareaComponent],
  templateUrl: './mainapplicationbody.component.html',
  styleUrl: './mainapplicationbody.component.css'
})

export class MainapplicationbodyComponent {

  public open(modal: any): void {
    this.modalService.open(modal);
  }

  private events: string[] = [];
  private title: string;

  constructor(private modalService: NgbModal, public dialog: MatDialog) {
    this.title = "Matter Web Application";
  }

  onButtonPressedEventCatch(value: {
    buttonName: string;
    action: Function;
  }) {
    console.log('Button pressed event caught in the ApplicationBodyComponent; value: ' + value.buttonName);
    value.action();
  };

  ngOnInit(): void {}

  ngOnDestroy(): void {}

}
