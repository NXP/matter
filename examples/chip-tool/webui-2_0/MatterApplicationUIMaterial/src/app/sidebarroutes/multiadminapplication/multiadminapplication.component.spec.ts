import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MultiadminapplicationComponent } from './multiadminapplication.component';

describe('MultiadminapplicationComponent', () => {
  let component: MultiadminapplicationComponent;
  let fixture: ComponentFixture<MultiadminapplicationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [MultiadminapplicationComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(MultiadminapplicationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
