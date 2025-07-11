import { Component, OnInit, OnDestroy, ViewChild, ElementRef, AfterViewInit, NgZone, PLATFORM_ID, Inject, Optional } from '@angular/core';
import { CommonModule, isPlatformBrowser } from '@angular/common';
import { MatButtonModule } from '@angular/material/button';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { MatIconModule } from '@angular/material/icon';
import { DialogRef } from '@angular/cdk/dialog';
import QrScanner from 'qr-scanner';

type QrScanResult = string | null;

@Component({
  selector: 'app-qr-scanner',
  standalone: true,
  imports: [
    CommonModule,
    MatButtonModule,
    MatProgressSpinnerModule,
    MatIconModule,
  ],
  templateUrl: './qrscanner.component.html',
  styleUrls: ['./qrscanner.component.css']
})
export class QrScannerComponent implements OnInit, OnDestroy, AfterViewInit {

  @ViewChild('scannerVideo', { static: false }) videoElement!: ElementRef<HTMLVideoElement>;

  public qrScanner: QrScanner | null = null;
  scanError: string | null = null;
  isScanning: boolean = false;
  isLoading: boolean = false;

  private scanTimeoutId: any = null;
  private isBrowser: boolean;

  constructor(
    private zone: NgZone,
    @Inject(PLATFORM_ID) private platformId: Object,
    @Optional() public dialogRef: DialogRef<QrScanResult>
  ) {
    this.isBrowser = isPlatformBrowser(this.platformId);
  }

  ngOnInit(): void {
    this.isScanning = false;
    this.isLoading = false; // Initialize isLoading
    this.scanError = null;
  }

  ngAfterViewInit(): void {
    if (this.isBrowser) {
      requestAnimationFrame(() => {
        if (this.videoElement && this.videoElement.nativeElement) {
          this.initializeScanner();
        } else {
          this.zone.run(() => {
            this.scanError = "Video element not found.";
            this.isLoading = false;
          });
        }
      });
    } else {
      console.log('QR Scanner: Skipping initialization (not in browser).');
      this.zone.run(() => {
        this.scanError = "QR Scanner only works in a browser environment.";
      });
    }
  }

  ngOnDestroy(): void {
    console.log('QR Scanner: ngOnDestroy - Cleaning up.');
    this.clearScanTimeout();
    this.stopScanner(true);
    if (this.qrScanner) {
      try {
        this.qrScanner.destroy();
      } catch (e) {
        console.warn("Error destroying qr-scanner:", e);
        if (typeof this.qrScanner.stop === 'function') {
          this.qrScanner.stop();
        }
      }
      this.qrScanner = null;
    }
  }

  initializeScanner(): void {
    if (this.qrScanner || !this.isBrowser) {
      return;
    }
    const videoElem = this.videoElement.nativeElement;
    try {
      this.qrScanner = new QrScanner(
        videoElem,
        result => this.handleScanSuccess(result),
        {
          onDecodeError: error => this.handleScanError(error),
          highlightScanRegion: true,
          highlightCodeOutline: true,
          calculateScanRegion: (video) => {
            const regionSize = Math.min(video.videoWidth, video.videoHeight) * 0.8;
            return {
              x: (video.videoWidth - regionSize) / 2,
              y: (video.videoHeight - regionSize) / 2,
              width: regionSize,
              height: regionSize
            };
          }
        }
      );
      this.zone.run(() => { this.scanError = null; });
      console.log('QR Scanner: Initialized successfully.');
    } catch (error: any) {
      console.error('QR Scanner: Initialization failed:', error);
      this.zone.run(() => {
        this.scanError = `Scanner initialization failed: ${error?.message || error}`;
        this.qrScanner = null;
        this.isLoading = false; // Ensure loading stops
      });
    }
  }

  async requestCameraPermission(): Promise<boolean> {
    if (!navigator?.permissions) {
      console.warn('QR Scanner: Permissions API not supported.');
      return true;
    }
    try {
      const permissionStatus = await navigator.permissions.query({ name: 'camera' as PermissionName });
      console.log('QR Scanner: Camera permission state:', permissionStatus.state);
      if (permissionStatus.state === 'granted') {
        return true;
      }
      if (permissionStatus.state === 'prompt') {
        return true;
      }
      // Denied state
      this.zone.run(() => {
        this.scanError = 'Camera permission denied. Please enable it in browser settings.';
      });
      return false;
    } catch (error) {
      console.error('QR Scanner: Error checking camera permission:', error);
      this.zone.run(() => {
        this.scanError = 'Could not check camera permission.';
      });
      return false;
    }
  }

  async startScanner(): Promise<void> {
    if (!this.isBrowser || this.isScanning || this.isLoading || !this.qrScanner) {
      console.warn('QR Scanner: Start cancelled.', { isBrowser: this.isBrowser, isScanning: this.isScanning, isLoading: this.isLoading, hasScanner: !!this.qrScanner });
      if (!this.qrScanner && this.isBrowser) {
        this.zone.run(() => this.scanError = "Scanner not initialized.");
      }
      return;
    }

    this.zone.run(() => {
      this.isLoading = true;
      this.scanError = null;
    });

    const hasPermission = await this.requestCameraPermission();
    if (!hasPermission) {
      this.zone.run(() => { this.isLoading = false; });
      return;
    }

    this.clearScanTimeout();

    console.log("QR Scanner: Attempting to start...");
    this.qrScanner.start()
      .then(() => {
        this.zone.run(() => {
          if (!this.isLoading) {
            console.warn("QR Scanner: Start successful, but isLoading is false. Stopping immediately.");
            this.stopScanner();
            return;
          }
          console.log("QR Scanner: Started successfully. Setting isScanning=true.");
          this.isScanning = true;
          this.isLoading = false;
          this.scanError = null;

          this.scanTimeoutId = setTimeout(() => {
            this.zone.run(() => {
              if (this.isScanning) {
                console.log("QR Scanner: Scan timed out.");
                this.stopScanner();
                this.scanError = "Scan timed out: No QR Code detected.";
              }
            });
          }, 15000);
        });
      })
      .catch(err => {
        this.zone.run(() => {
          console.error("QR Scanner: Failed to start:", err);
          this.isLoading = false;
          this.isScanning = false;
          this.handleScanError(err || 'Failed to start scanner.');
          this.clearScanTimeout();
        });
      });
  }

  stopScanner(fromDestroy = false): void {
    this.clearScanTimeout();

    if (!this.qrScanner) {
      console.log("QR Scanner: stopScanner called, but no scanner instance.");
      this.zone.run(() => {
        this.isScanning = false;
        this.isLoading = false;
      });
      return;
    }

    if (this.isScanning || !fromDestroy) {
      console.log("QR Scanner: Stopping scanner...", { wasScanning: this.isScanning, fromDestroy });
    }

    if (typeof this.qrScanner.stop === 'function') {
      try {
        this.qrScanner.stop();
      } catch (e) {
        console.warn("Error stopping qr-scanner:", e);
      }
    }

    this.zone.run(() => {
      this.isScanning = false;
      this.isLoading = false;
    });

    if (!fromDestroy) {
      console.log("QR Scanner: Stop process finished.");
    }
  }

  private handleScanSuccess(result: QrScanner.ScanResult | string): void {
    if (!this.isScanning && !this.isLoading) {
      console.warn("QR Scanner: Scan success ignored, already stopped/processed.");
      return;
    }
    console.log("QR Scanner: Scan Success!");
    this.clearScanTimeout();

    const resultData = typeof result === 'string' ? result : result.data;
    console.log("QR Scanner: Decoded data:", resultData);
    console.log("QR Scanner: Stopping scanner and closing dialog with result.");

    this.stopScanner();
    this.closeDialog(resultData);
  }

  private handleScanError(error: any): void {
    const errorString = (error instanceof Error ? error.message : String(error)).toLowerCase();
    const errorName = error instanceof Error ? error.name : '';

    console.warn(`QR Scanner: Scan Error - Name: '${errorName}', Message: '${errorString}'`);

    const isFatalError = ['NotAllowedError', 'NotFoundError', 'NotReadableError', 'OverconstrainedError', 'AbortError'].includes(errorName) ||
      errorString.includes('permission denied') ||
      errorString.includes('requested device not found') ||
      errorString.includes('could not start video source');

    const isNonCriticalDecodingError = errorString.includes('no qr code found');

    this.zone.run(() => {
      if (isFatalError) {
        console.error("QR Scanner: FATAL Error detected.", error);
        this.scanError = `Camera Error: ${error instanceof Error ? error.message : error}. Please check permissions.`;
        this.isLoading = false;
        this.stopScanner();
        this.isScanning = false;

      } else if (isNonCriticalDecodingError) {
        console.warn("QR Scanner: NonCriticalDecodingError:", errorString);
      } else {
        console.warn("QR Scanner: Non-fatal scan error:", errorString);
      }
    });
  }

  private clearScanTimeout(): void {
    if (this.scanTimeoutId) {
      clearTimeout(this.scanTimeoutId);
      this.scanTimeoutId = null;
      console.log("QR Scanner: Scan timeout cleared.");
    }
  }

  closeDialog(result: QrScanResult): void {
    console.log(`QR Scanner: Closing dialog with result: ${result === null ? 'null' : 'Success'}`);
    this.stopScanner();
    if (this.dialogRef) {
      this.dialogRef.close(result);
    } else {
      console.warn('QR Scanner: DialogRef not available to close dialog.');
    }
  }

  cancelScan(): void {
    console.log('QR Scanner: Scan cancelled by user.');
    this.closeDialog(null);
  }
}