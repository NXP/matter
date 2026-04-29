import { ComponentFixture, TestBed } from '@angular/core/testing';

import { EasyevseapplicationComponent } from './easyevseapplication.component';

describe('EasyevseapplicationComponent', () => {
  let component: EasyevseapplicationComponent;
  let fixture: ComponentFixture<EasyevseapplicationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [EasyevseapplicationComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(EasyevseapplicationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
