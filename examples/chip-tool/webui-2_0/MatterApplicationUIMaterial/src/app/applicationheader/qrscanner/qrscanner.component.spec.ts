import { ComponentFixture, TestBed } from '@angular/core/testing';

import { QrscannerComponent } from './qrscanner.component';

describe('QrscannerComponent', () => {
  let component: QrscannerComponent;
  let fixture: ComponentFixture<QrscannerComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [QrscannerComponent]
    })
      .compileComponents();

    fixture = TestBed.createComponent(QrscannerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
