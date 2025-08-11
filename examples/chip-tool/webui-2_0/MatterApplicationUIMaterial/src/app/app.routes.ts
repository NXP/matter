import { Routes } from '@angular/router';
import { MainapplicationbodyComponent } from './mainapplicationbody/mainapplicationbody.component';
import { DevicesapplicationComponent } from './sidebarroutes/devicesapplication/devicesapplication.component';
import { SettingsapplicationComponent } from './sidebarroutes/settingsapplication/settingsapplication.component';
import { HelpapplicationComponent } from './sidebarroutes/helpapplication/helpapplication.component';
import { AudioapplicationComponent } from './sidebarroutes/audioapplication/audioapplication.component';
import { SubscriptionsapplicationComponent } from './sidebarroutes/subscriptionsapplication/subscriptionsapplication.component';
import { MultiadminapplicationComponent } from './sidebarroutes/multiadminapplication/multiadminapplication.component';
import { BindingapplicationComponent } from './sidebarroutes/bindingapplication/bindingapplication.component';
import { EasyevseapplicationComponent } from './sidebarroutes/easyevseapplication/easyevseapplication.component';
import { TbrmappcomponentComponent } from './sidebarroutes/tbrmappcomponent/tbrmappcomponent.component';
import { OtaapplicationComponent } from './sidebarroutes/otaapplication/otaapplication.component';
import { NetworkgraphComponent } from './sidebarroutes/networkgraph/networkgraph.component';

export const routes: Routes = [
  {path: '', redirectTo: 'dashboard', pathMatch: 'full'},
  {path: 'dashboard', component: MainapplicationbodyComponent},
  {path: 'devices', component: DevicesapplicationComponent},
  {path: 'settings', component: SettingsapplicationComponent},
  {path: 'help', component: HelpapplicationComponent},
  {path: 'audio', component: AudioapplicationComponent},
  {path: 'subscriptions', component: SubscriptionsapplicationComponent},
  {path: 'multiadmin', component:MultiadminapplicationComponent},
  {path: 'binding', component: BindingapplicationComponent},
  {path: 'energy_evse', component: EasyevseapplicationComponent},
  {path: 'tbrm', component: TbrmappcomponentComponent},
  {path: 'ota', component: OtaapplicationComponent},
  {path: 'network_graph', component: NetworkgraphComponent},
];
