import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TbrmappcomponentComponent } from './tbrmappcomponent.component';

describe('TbrmappcomponentComponent', () => {
  let component: TbrmappcomponentComponent;
  let fixture: ComponentFixture<TbrmappcomponentComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [TbrmappcomponentComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(TbrmappcomponentComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
