import { bootstrapApplication } from '@angular/platform-browser';
import { appConfig } from './app/app.config';
import { AppComponent } from './app/app.component';

// import "@fontsource/dm-sans"; // Defaults to weight 400
// import "@fontsource/dm-sans/400.css"; // Specify weight
// import "@fontsource/dm-sans/400-italic.css"; // Specify weight and style

import "@fortawesome/fontawesome-free"
import "@fortawesome/free-solid-svg-icons"
import "@fortawesome/angular-fontawesome"

bootstrapApplication(AppComponent, appConfig)
  .catch((err) => console.error(err));