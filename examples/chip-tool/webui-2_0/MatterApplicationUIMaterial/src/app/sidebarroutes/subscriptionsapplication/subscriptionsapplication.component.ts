import { Component, ElementRef, HostListener, ViewChild } from '@angular/core';
import { NgbModal } from '@ng-bootstrap/ng-bootstrap';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import {MatCard, MatCardModule} from '@angular/material/card';
import { NgClass, NgFor, NgIf, NgStyle } from '@angular/common';

// Models import
import { MatDialog } from '@angular/material/dialog';
import { ScrollgallerycomponentComponent } from '../../mainapplicationbody/scrollgallerycomponent/scrollgallerycomponent.component';
import { ApplicationcardComponent } from '../../applicationcard/applicationcard.component';
import { CardscomponentComponent } from '../../mainapplicationbody/cardscomponent/cardscomponent.component';
import { FloatingactionareaComponent } from '../../mainapplicationbody/floatingactionarea/floatingactionarea.component';
import { CardModel } from '../../models/card-model';
import { EndpointModel } from '../../models/endpoint-model';
import { DimmableLightModel } from '../../models/dimmable-light-model';
import { LightingModel } from '../../models/lighting-model';
import { GetRequestsService } from '../../services/get-requests.service';
import { AppDialogService } from '../../services/app-dialog.service';
import { LoaderService } from '../../services/loader.service';
import { WebSocketService } from '../../services/web-socket.service';
import { MatSnackBar } from '@angular/material/snack-bar';

@Component({
  selector: 'app-subscriptionsapplication',
  standalone: true,
  imports: [NgbModule, MatCardModule, MatCard, NgClass, NgFor, NgIf, NgStyle,
    ScrollgallerycomponentComponent, ApplicationcardComponent, CardscomponentComponent, FloatingactionareaComponent],
  templateUrl: './subscriptionsapplication.component.html',
  styleUrl: './subscriptionsapplication.component.css'
})
export class SubscriptionsapplicationComponent {
  public open(modal: any): void {
    this.modalService.open(modal);
  }

  @ViewChild('containingappcards_component_div') cards_component_div!: ElementRef;
  @ViewChild('cards_component') cards_component_component!: CardscomponentComponent;
  private events: any[] = [];
  private title: string;

  constructor(private modalService: NgbModal, private dialog: MatDialog, private getRequestsService: GetRequestsService, private appDialogService: AppDialogService,
    private loaderService: LoaderService, private webSocketService: WebSocketService, private _snackBar: MatSnackBar
  ) {
    this.title = "Matter Web Application";
  }

  onButtonPressedEventCatch(value: {
    buttonName: string;
    action: Function;
  }) {
    console.log('Button pressed event caught in the ApplicationBodyComponent; value: ' + value.buttonName);
    value.action();
  };

  onResize() {
    this.cards_component_div.nativeElement.style.width = window.innerWidth * 1 / 2 + 'px';

    const cardWidth = this.cards_component_component.getCardComponentContainerWidth();
    const windowWidth = window.innerWidth;
    const numCards = Math.floor(windowWidth / cardWidth) > this.cards_component_component.getNumberOfCards() ? this.cards_component_component.getNumberOfCards() : Math.floor(windowWidth / cardWidth);
    this.cards_component_div.nativeElement.style.width = numCards * (cardWidth + this.cards_component_component.getMasonryLayoutGap())  + 'px';

    this.cards_component_component.reloadMasonryLayout();

  }

  private intervalId: any;

  ngOnInit(): void {
    // this.loaderService.showLoader();
    // this.getRequestsService.getDevicesIDsAndAliases().subscribe(
    //   (data: any) => {
    //     const parsedData = JSON.parse(JSON.stringify(data));
    //     if (parsedData['result'] === 'successful') {
    //       this.cards = []; // We update all the cards array
    //       for (const [key, value] of Object.entries(parsedData['status'])) {
    //         let card: CardModel;
    //         const device = key as string;
    //         card = new CardModel('../../assets/wireless-transparent.png', value as number, [], false, device);
    //         this.cards.push(card);
    //       }
    //       // We emit an event or something to the parent component with the new cards list
    //       this.loaderService.hideLoader();
    //       // this.appDialogService.showInfoDialog('Got the list of devices successfully');
    //     } else {
    //       this.loaderService.hideLoader();
    //       this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
    //     }
    //   },
    //   (error: any) => {
    //     console.error('Error received: ', error);
    //     this.loaderService.hideLoader();
    //     this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
    //   }
    // );

    this.webSocketService.getMessages().subscribe((message: any) => {
      // Example message: Subscribe Report from DeviceAliasName 1234: 1. Cluster: 6 On-Off: false
      const message_data: String = message.data;
      console.log("Websockets message: " + message.data.split(" "))
      const event_obj = {
          "DeviceAlias": message_data.split(" ")[3],
          "DeviceNodeID": message_data.split(" ")[4].split(":")[0],
          "DeviceCluster": message_data.split(" ")[7].split(":")[0],
          "Status": message_data.split(" ")[8]
      }
      console.log("Current event object: " + JSON.stringify(event_obj))

      this.cards_component_component.modifyCardColorByID(event_obj["DeviceNodeID"], event_obj["Status"] === "true")
      this.cards_component_component.modifyAllLightEndpointsStatus(event_obj["DeviceNodeID"], event_obj["Status"] == "true")

      this.events.push(event_obj)
      this._snackBar.open('WebSocket message! ' + message.data, 'Close', {
        duration: 5000,
      });
    })
  }

  ngOnDestroy(): void {}

  public cards: CardModel[] = [];
}
