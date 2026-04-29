import { ComponentFixture, TestBed } from '@angular/core/testing';

import { OtaapplicationComponent } from './otaapplication.component';

describe('OtaapplicationComponent', () => {
  let component: OtaapplicationComponent;
  let fixture: ComponentFixture<OtaapplicationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [OtaapplicationComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(OtaapplicationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
