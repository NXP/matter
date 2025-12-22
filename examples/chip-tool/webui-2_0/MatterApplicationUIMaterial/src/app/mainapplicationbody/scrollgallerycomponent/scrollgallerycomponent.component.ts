import { Component } from '@angular/core';
import { MatCardModule } from '@angular/material/card';
import { MatButtonModule } from '@angular/material/button';

@Component({
  selector: 'app-scrollgallerycomponent',
  standalone: true,
  imports: [MatCardModule, MatButtonModule],
  templateUrl: './scrollgallerycomponent.component.html',
  styleUrl: './scrollgallerycomponent.component.css'
})
export class ScrollgallerycomponentComponent {

}
