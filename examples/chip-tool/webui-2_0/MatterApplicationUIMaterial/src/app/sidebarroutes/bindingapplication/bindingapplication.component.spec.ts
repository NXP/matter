import { ComponentFixture, TestBed } from '@angular/core/testing';

import { BindingapplicationComponent } from './bindingapplication.component';

describe('BindingapplicationComponent', () => {
  let component: BindingapplicationComponent;
  let fixture: ComponentFixture<BindingapplicationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [BindingapplicationComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(BindingapplicationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
