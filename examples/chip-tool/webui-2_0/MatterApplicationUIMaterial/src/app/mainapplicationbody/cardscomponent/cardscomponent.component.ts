import { Component, Directive, ElementRef, Input, ViewChild, OnInit, AfterViewInit, OnDestroy, Inject } from '@angular/core';
import { ApplicationcardComponent } from '../../applicationcard/applicationcard.component';
import { NgFor, NgIf, NgStyle } from '@angular/common';
import { CardModel } from '../../models/card-model';
import { NgxMasonryComponent, NgxMasonryModule } from 'ngx-masonry';

import { LoaderService } from './../../services/loader.service';
import { PostRequestsService } from './../../services/post-requests.service';
import { AppDialogWithInputFieldsService } from './../../services/app-dialog-input.service';
import { EventEmitter, Output } from '@angular/core';
import { MatChip, MatChipListbox } from '@angular/material/chips';
import { MatIcon } from '@angular/material/icon';
import {MatChipsModule} from '@angular/material/chips';
import { PopupdialogmaterialComponent } from '../../popupdialogmaterial/popupdialogmaterial.component';
import { MatDialog, MatDialogActions, MatDialogClose } from '@angular/material/dialog';
import { Dialog } from '@angular/cdk/dialog';
import {GetRequestsService} from '../../services/get-requests.service';

import { AppDialogService } from '../../services/app-dialog.service';
import { HttpClient } from '@angular/common/http';
import { EndpointModel } from '../../models/endpoint-model';

@Component({
  selector: 'app-cardscomponent',
  standalone: true,
  imports: [ApplicationcardComponent, NgFor, NgxMasonryModule, NgStyle, NgIf,
    MatChip, MatChipListbox, MatIcon, MatChipsModule],
  templateUrl: './cardscomponent.component.html',
  styleUrl: './cardscomponent.component.css'
})
export class CardscomponentComponent implements AfterViewInit, OnDestroy {

  private MassonryLayoutGap = 20;

  constructor(private httpClient: HttpClient, private getRequestsService: GetRequestsService, private postRequestsService: PostRequestsService,
    private appDialogService: AppDialogService,
    private loaderService: LoaderService) {}

  // The cards that will be displayed in the cards component
  @Input() cards!: CardModel[];
  @Input() cardsHaveSubscriptionOption!: boolean;
  @ViewChild('ngxmasonry_container') masonrycontainer!: ElementRef;
  @ViewChild('masonry_item_container') masonryitemcontainer!: NgxMasonryComponent;
  @ViewChild('card_component_container') cardcomponentcontainer!: ElementRef;

  reloadMasonryLayout() {
    if (this.masonryitemcontainer !== undefined) {
      this.masonryitemcontainer.reloadItems();
      this.masonryitemcontainer.layout();
    }
  }

  ngAfterViewInit(): void {
      this.onPressedRefreshButton()
  }

  ngOnDestroy(): void {
    console.log('Destroying Cards Component');
  }

  public getMasonryContainerWidth(): number {
    return this.masonrycontainer.nativeElement.offsetWidth;
  }


  public getCardComponentContainerWidth(): number {
    return this.cardcomponentcontainer.nativeElement.offsetWidth;
  }

  public getMasonryLayoutGap(): number {
    return this.MassonryLayoutGap;
  }

  public getNumberOfCards() {
    return this.cards.length;
  }

  public onPressedRefreshButton() {
    this.loaderService.showLoader()
    try {
      console.log("Showing loader...")
      this.getRequestsService.getDevicesIDsAndAliases().subscribe(
        (data: any) => {
          console.log("Parsed data: " + JSON.stringify(data))
          const parsedData = JSON.parse(JSON.stringify(data))

          if (parsedData['result'] === 'successful') {
            let nodeList = parsedData["nodeList"]
            this.cards = [] // We update all the cards array
            if (nodeList != null) {
              for (let i = 0; i < nodeList.length; ++i) {
                let current_node_alias = nodeList[i]["nodeAlias"]
                let current_node_id = nodeList[i]["nodeId"]
                let node_endpoint_info_data = nodeList[i]["endpointInfo"]
                let card = new CardModel('../../assets/wireless-transparent.png', current_node_id as number, [], false, current_node_alias) // Construim nodul cu datele curente

                console.log("Node alias: " + current_node_alias)
                console.log("Current node ID: " + current_node_id)
                console.log("Node endpoint info data: " + Object.entries(node_endpoint_info_data).toString())
                
                if (node_endpoint_info_data != null) {
                  for (const [key, value] of Object.entries(node_endpoint_info_data)) {
                    for (let j = 0; j < (value as any).length; ++j) {
                      // Adaugam endpoint la card curent cu ID = key si nume = endpoint_info_data[key][j]

                      // Daca endpoint-ul este onoff light sau dimmable light
                      if (node_endpoint_info_data[key][j] === "Matter Dimmable Light" || node_endpoint_info_data[key][j] === "Matter On/Off Light") {
                        let current_endpoint = new EndpointModel(key as string, node_endpoint_info_data[key][j] as string, "../../../../assets/endpoint/off_light.png",
                          true, // Enabled Status
                          undefined // Not subscribed (no subscription ID)
                        )
                        console.log("Creez endpoint-ul: " + current_endpoint.endpointId + "; " + current_endpoint.endpointName + "; " + current_endpoint.endpointImageURL)
                        card.endpoints.push(current_endpoint)

                        // If it is not a Matter Root node, show it
                      } else if (node_endpoint_info_data[key][j] !== "Matter Root Node") {
                        let current_endpoint = new EndpointModel(key as string, node_endpoint_info_data[key][j] as string, "../../../../assets/unknown-device.png",
                          true, // Enabled Status
                          undefined // Not subscribed (no subscription ID)
                        )
                        console.log("Creez endpoint-ul: " + current_endpoint.endpointId + "; " + current_endpoint.endpointName + "; " + current_endpoint.endpointImageURL)
                        card.endpoints.push(current_endpoint)
                      }

                    }
                  }
                }
                this.cards.push(card)
              }
            }

            // We emit an event or something to the parent component with the new cards list
            this.loaderService.hideLoader()
            console.log("Hiding loader...")
            // this.appDialogService.showInfoDialog('Got the list of devices successfully');
          } else {
            this.loaderService.hideLoader()
            console.log("Hiding loader...")
            this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
          }
        },

        (error: any) => {
          console.error('Error received: ', error);
          this.loaderService.hideLoader();
          console.log("Hiding loader...")
          this.appDialogService.showErrorDialog('Error getting devices list (id\'s and aliases)');
        });
      } catch (error : any){
        this.loaderService.hideLoader()
        console.log("Got error while getting endpoints and nodes: " + error.toString())
      }
  }

  public modifyCardColorByID(cardId: string, devicestatus: boolean) {
    let cards_copy = this.cards.map(card => card)
    this.cards = []
    this.cards = cards_copy.map(card => {
      if (card.deviceId.toString() === cardId) {
        return new CardModel(
          card.getDeviceTypeImageURL(),
          card.deviceId,
          card.endpoints,
          devicestatus,
          card.deviceName
        );
      }
      return card;
    });
  }

  public modifyAllLightEndpointsStatus(cardId: string, devicestatus: boolean) {
    let cards_copy = this.cards.map(card => card)
    this.cards = []
    this.cards = cards_copy.map(card => {
      if (card.deviceId.toString() === cardId) {
        const updatedEndpoints = card.endpoints.map(endpoint => {
          if (endpoint.endpointName === "Matter Dimmable Light" || endpoint.endpointName === "Matter On/Off Light") {
            return new EndpointModel(
              endpoint.endpointId,
              endpoint.endpointName,
              devicestatus ? "../../../../assets/endpoint/on_light.png" : "../../../../assets/endpoint/off_light.png",
              devicestatus,
              endpoint.getEndpointSubscriptionId()
            );
          }
          return endpoint;
        });

        return new CardModel(
          card.getDeviceTypeImageURL(),
          card.deviceId,
          updatedEndpoints,
          card.isDeviceOnline,
          card.getDeviceName()
        );
      }
      return card;
    });
  }


}
