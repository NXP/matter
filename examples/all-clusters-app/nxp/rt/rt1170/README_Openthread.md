# RT1170 All-cluster Application for Matter over Openthread

## Hardware requirements

Host part:

- 1 MIMXRT1170-EVK board

Transceiver part:

- 1 IW612 module


## Board settings

Board settings are described [here][ot_cli_rt1170_readme].

[ot_cli_rt1170_readme]:../../../../../third_party/openthread/ot-nxp/src/imx_rt/rt1170/README.md#Board-settings

<a name="building"></a>

## Building

### Build instructions

First instructions from [README.md 'Building section'][readme_building_section] should be followed.


[readme_building_section]: README.md#Building



-   Build the Openthread configuration with BLE commissioning.

```
user@ubuntu:~/Desktop/git/connectedhomeip/examples/all-cluster/nxp/rt/rt1170$ gn gen --args="chip_enable_openthread=true iwx12_transceiver=true chip_inet_config_enable_ipv4=false chip_config_network_layer_ble=true is_sdk_package=true" out/debug
user@ubuntu:~/Desktop/git/connectedhomeip/examples/all-cluster/nxp/rt/rt1170/$ ninja -C out/debug
```

  
The resulting output file can be found in out/debug/chip-rt1170-all-cluster-example

## Flashing and debugging the RT1170

To know how to flash and debug follow instructions from [README.md 'Flashing and debugging'][readme_flash_debug_section].

[readme_flash_debug_section]:README.md#Flashing-and-debugging

## Raspberrypi Border Router setup

Instructions to start an openthread border router should be followed. In this section a mechanism to start the BR, without accessing the web interface, is described.

Start the docker BR image:

```
sudo docker run -it --rm --network host --privileged -v /dev/ttyACM0:/dev/radio connectedhomeip/otbr:sve2 --radio-url spinel+hdlc+uart:///dev/radio -B eth0
```

Get the docker ID of the BR image:
```
sudo docker container ls
```

Create a thread network on the border router (048bf89bb3dd should be replaced by the previously gotten BR docker ID):

```
sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl dataset init new"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl dataset channel 17"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl dataset panid 0x1222"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl dataset extpanid 1111111122222222"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl dataset networkkey 00112233445566778899aabbccddeeaa"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl dataset commit active"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl ifconfig up"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl thread start"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl prefix add fd11:22::/64 pasor"; sudo docker exec -it 048bf89bb3dd sh -c "sudo ot-ctl netdata register"
```



# Testing the all custer app example (with BLE commissioning support)

The pairing "ble-thread" feature must be used and instructions from [README.md 'Testing the example'][readme_test_example_section] should be followed.

[readme_test_example_section]:README.md#testing-the-example