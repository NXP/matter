# NXP MCXW OTA Guide

## Overview

This guide describes the Over-The-Air (OTA) update procedure for NXP
MCXW71/MCXW72 Matter applications. The process involves:

1. Building two firmware images (requestor and provider) with OTA support
   enabled
2. Converting the provider `.bin`/`.srec` file into an encrypted `.sb3` file
   using the OTAP tool
3. Generating a `.ota` image using the NXP OTA image tool
4. Running the OTA transfer using chip-tool, an OTA Provider application, and an
   OpenThread Border Router

---

## Step 1: Build Firmware Images with OTA Support

Two images are required:

| Image             | Role                        | Notes                                   |
| ----------------- | --------------------------- | --------------------------------------- |
| **OTA Requestor** | Runs on the target device   | Current firmware that will be updated   |
| **OTA Provider**  | The new firmware to deliver | Must have a **higher software version** |

Both images must be built with a configuration that enables the OTA Requestor
flag. Use one of the following Kconfig overlay files (or any custom config with
`CONFIG_CHIP_OTA_REQUESTOR=y`):

- `examples/platform/nxp/config/prj_thread_mtd_ota.conf` (MTD + OTA + ICD/SED)
- `examples/platform/nxp/config/prj_thread_ftd_ota.conf` (FTD + OTA)

Images are built with `west build`. A typical command line looks like:

```bash
west build -d <output_directory> -b <board> <application> \
  --config debug \
  -DCONF_FILE_NAME=prj_thread_mtd_ota.conf \
  -DCONFIG_MCUX_COMPONENT_middleware.freertos-kernel.config=n \
  -Dcore_id=cm33_core0 \
  -DCONFIG_CHIP_DEVICE_DISCRIMINATOR=3840 
```

The **OTA Provider image** (the new version to be delivered) must additionally
set the software version to a value higher than the requestor. Pass the
Kconfig symbols as `-D` defines on the `west build` command line (or add them to
your overlay `.conf`):

```
-DCONFIG_CHIP_DEVICE_SOFTWARE_VERSION=2 -DCONFIG_CHIP_DEVICE_SOFTWARE_VERSION_STRING="2.0"
```

> **Important:** The OTA header version (`-vn` in the OTA image tool) must match
> the embedded software version of the provider binary.

---

## Step 2: Convert `.bin` / `.srec` into `.sb3` File

The OTA image must be encrypted using the **Over The Air Programming Tool**
([OTAP](https://www.nxp.com/design/microcontrollers-developer-resources/connectivity-tool-suite:CONNECTIVITY-TOOL-SUITE?#downloads)).
The bootloader will only load the new image if it was encrypted with the correct
OTAP keys.

In the **OTAP** application:

1. Select OTA protocol → **OTAP Matter**
2. Browse and select the `.bin` file (provider image)
3. Follow default options (**Preserve NVM**)
4. Image information: select **"Application Core (MCU)"** — this generates the
   image only for the CM33 core
5. In the **JSON file configurator for SB3 generation** window, scroll down to
   the **Commands** section and press the **Enable** button:
    - **In the `erase` command, replace the size `0x1F6000` with
      `0x1F2000`** (Any changes to the flash layout require adjusting this value; for this change the NVM was expanded from `0x1F8000` to `0x1F4000`and so the change must also be reflected in this number)
6. Keep all other settings at default values

Output: encrypted `.sb3` file.

---

## Step 3: Generate `.ota` File

Use the NXP wrapper over the standard OTA image tool:

```
scripts/tools/nxp/ota/ota_image_tool.py
```

The tool generates an OTA image with the following format:

```
| OTA image header | TLV1 | TLV2 | ... | TLVn |
```

where each TLV is in the form `|tag|length|value|`.

### Usage

**Linux:**

```bash
./scripts/tools/nxp/ota/ota_image_tool.py create -v 0xDEAD -p 0xBEEF -vn 2 -vs "2.0" -da sha256 --app-input-file <sb3_path> <output_ota_path>
```

**Windows:**

```cmd
python scripts\tools\nxp\ota\ota_image_tool.py create -v 0xDEAD -p 0xBEEF -vn 2 -vs "2.0" -da sha256 --app-input-file <sb3_path> <output_ota_path>
```

### Example

```bash
./scripts/tools/nxp/ota/ota_image_tool.py create -v 0xDEAD -p 0xBEEF -vn 2 -vs "2.0" -da sha256 \
  --app-input-file ~/binaries/chip-mcxw72-app.sb3 \
  ~/binaries/chip-mcxw72-app.ota
```

### Custom Options

| Option             | Description                                        |
| ------------------ | -------------------------------------------------- |
| `--app-input-file` | Path to the application `.sb3` binary              |
| `--app-version`    | Application version (can differ from `-vn`)        |
| `--bl-input-file`  | Path to the SSBL binary                            |
| `--factory-data`   | Enable generation of factory data TLV              |
| `--json`           | Path to a JSON file following `ota_payload.schema` |

See the full [OTA image tool guide](../../../scripts/tools/nxp/ota/README.md)
for all options.

---

## Step 4: Running OTA

### Topology

![OTA_TOPOLOGY](../../../examples/platform/nxp/mcxw72/doc/images/ota_topology.JPG)

- **OTA Provider Application** — Linux application holding the `.ota` image
- **OTA Requestor** — embedded in the reference application on the MCXW device
- **chip-tool** — Linux controller used to commission both the device and the
  OTA Provider
- **OTBR** — OpenThread Border Router providing Thread network connectivity

### Obtaining the host tools (chip-tool, chip-ota-provider-app)

The `chip-tool` and `chip-ota-provider-app` binaries are Linux host
applications. They are **not** part of the MCXW firmware build; they are built
from source in the `connectedhomeip` repo (they are also the same tools bundled
with the Matter Test Harness setup on the RPi/Ubuntu host):

```bash
# Build the Linux OTA Provider application (produces chip-ota-provider-app)
./scripts/examples/gn_build_example.sh examples/ota-provider-app/linux out/ota-provider-app chip_config_network_layer_ble=false

# Build the Linux chip-tool (produces chip-tool)
./scripts/examples/gn_build_example.sh examples/chip-tool out/chip-tool-app
```

> **Recommendation:** For compatibility, compile `chip-tool` and the OTA
> Provider application from the **same commit id** used to build the reference
> (requestor) firmware. In the commands below, `chip-apps/chip-tool` and
> `chip-apps/chip-ota-provider-app` refer to these built binaries — substitute
> the actual output paths (e.g. `out/chip-tool-app/chip-tool` and
> `out/ota-provider-app/chip-ota-provider-app`) if they differ in your setup.

### About the OTBR helper scripts

The `otbr/otbr_start.sh` and `otbr/otbr_srp_restart.sh` scripts referenced below
are **not** part of the `connectedhomeip` repo. They are helper wrappers
(distributed as part of the Test Harness / OTBR setup tooling on the RPi/Ubuntu
host) around the upstream OpenThread Border Router Docker image
(`connectedhomeip/otbr`) and its `ot-ctl` commands:

- `otbr_start.sh` — pulls/launches the OTBR Docker container, forms the Thread
  network, and prints the operational dataset.
- `otbr_srp_restart.sh` — restarts the SRP server (`ot-ctl srp server disable`
  → `ot-ctl srp server enable`) to work around mDNS/SRP caching issues.

For setting up the RPi/OTBR host and obtaining these scripts, follow the CSA
official Matter test-setup instructions
([CSA matter-csg document 28566](https://groups.csa-iot.org/wg/matter-csg/document/28566)).
If you do not have the helper scripts, you can run the equivalent `ot-ctl` /
`docker` commands manually (see **Known Issues** below).

### Procedure (Two-Terminal Workflow)

#### Terminal 1 — OTBR + OTA Provider

```bash
# Clean state
rm -rf /tmp/chip_*

# Start the OpenThread Border Router and save the dataset
otbr/otbr_start.sh
# Note: save the operational dataset printed by this script for later use

# Restart SRP server (avoids mDNS issues)
otbr/otbr_srp_restart.sh

# Start the OTA Provider Application
chip-apps/chip-ota-provider-app -f <path_to_ota_image>
```

#### Terminal 2 — chip-tool (Commissioning & OTA Trigger)

```bash
# Clean state
rm -rf /tmp/chip_*

# Restart SRP to avoid mDNS issues before commissioning OTA Provider
otbr/otbr_srp_restart.sh

# Commission OTA Provider on the network (node ID 1)
chip-apps/chip-tool pairing onnetwork 1 20202021

# Grant ACL entries to allow any OTA requestor to query the provider
chip-apps/chip-tool accesscontrol write acl '[{"fabricIndex": 1, "privilege": 5, "authMode": 2, "subjects": [112233], "targets": null}, {"fabricIndex": 1, "privilege": 3, "authMode": 2, "subjects": null, "targets": null}]' 1 0

# Put the device into commissioning mode (press SW2 on the board)

# Restart SRP before commissioning the device
otbr/otbr_srp_restart.sh

# Commission the device via BLE+Thread (node ID 2)
# Use the operational dataset saved from otbr_start.sh
chip-apps/chip-tool pairing ble-thread 2 hex:<operationalDataset> 20202021 3840

# Trigger OTA transfer
chip-apps/chip-tool otasoftwareupdaterequestor announce-otaprovider 1 0 0 0 2 0
```

> **Note:** The discriminator value `3840` (0x0F00) is the default. Adjust if
> your application uses a different discriminator.

---

## Known Issues

- **SRP cache must be flushed** before each new commissioning attempt. Use
  `otbr/otbr_srp_restart.sh` or manually run:

    ```bash
    ot-ctl srp server disable
    ot-ctl srp server enable
    ```

- **mDNS commissioning failures:** Ensure SRP server is restarted
  (`ot-ctl srp server disable` → `ot-ctl srp server enable`) on the OTBR before
  commissioning the OTA Provider Application.

- **No other Docker containers** should be running (e.g., Test Harness) except
  the OTBR container:

    ```bash
    sudo docker kill $container_id
    ```

- **Single network interface:** To avoid mDNS issues, only one interface should
  be active. If WiFi is used, disable Ethernet:

    ```bash
    sudo ip link set dev eth0 down
    sudo ip link set dev eth0 multicast off
    ```

- If the **OTBR Docker image** is used, the `-B` parameter must point to the
  backbone interface.

- If **Wi-Fi is used on RPi4**, select a 5 GHz network to avoid BLE-WiFi
  coexistence issues.
