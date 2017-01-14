#QwaveSys RPi Package 2.0 for LabVIEW.

If you find this package is useful, please consider supporting it with a donation. 
https://www.paypal.me/qwavesystems

![](http://ftp.qwavesys.com/tmp_pics/Rpi003.png)

![](http://ftp.qwavesys.com/tmp_pics/Rpi001.png)

[**QwaveSys RPi package 2.0**](https://github.com/QWaveSystems/QwaveSys-RPi-Package_2.0) is a LabVIEW additional library based on [LINX 3.0.xx](http://sine.ni.com/nips/cds/view/p/lang/en/nid/212478) from [labviewmakerhub.com](https://www.labviewmakerhub.com) for Raspberry Pi. It's supported LabVIEW 2014 only for Non-commercial use.

Anyone can get started with the [LabVIEW 45-Day Evaluation](http://ftp.ni.com/support/softlib/labview/labview_development_system/2014%20SP1/2014sp1LV-WinEng.exe) and buy LabVIEW 2014 Home Edition for non-commercial use. 

QwaveSys RPi Package is a peripheral VIs provides enhance functions over LINX 3.0 standard library. it's an easy to use VIs and provided many examples. It's tested with Raspberry Pi 2B/3B and some functions also works with BBB and Orange Pi (H3) boards.

![](http://ftp.qwavesys.com/tmp_pics/2017-01-12_21-05-26.png)

#Installation Steps.

**1.Download and Install "q_wave_systems_lib_qwavesys_rpi_package-2.0.0.18.vip"**

https://github.com/QWaveSystems/QwaveSys-RPi-Package_2.0/blob/master/q_wave_systems_lib_qwavesys_rpi_package-2.0.0.18.vip

**2.Download QwaveSys RPi Image. Refer the link below.** The image is based on **"2016-09-23**-Raspbian-Jessie WITH PIXEL".

https://drive.google.com/file/d/0B5DiaJTnM12RdVBRNl8wOVJ3TzA/view

**3.Navigate to "..\vi.lib\Q-Wave Systems\QwaveSys RPi Package 2.0\Solutions".** There are a lots of shipped solutions for you.

![](http://ftp.qwavesys.com/tmp_pics/14570755_1133753453326692_5611632336154060828_o.png)

#Manual Steps to install necessary packages: 
#(For Advanced users ONLY)

**1.Download a official "RASPBIAN JESSIE WITH PIXEL"** from https://www.raspberrypi.org/downloads/raspbian/

We only tested with "2016-09-23-Raspbian-Jessie WITH PIXEL ONLY.

**2.Install LINX 3.0. (LabVIEW run-time: (14.x.xx))** Refer to this turterial https://youtu.be/zsX0rJQGFqQ

**3.Login to LabVIEW chroot**

`sudo schroot –c labview`

**4.Check the supported architecture.**

`cat /etc/opkg/arch.conf`

**5.Add “Raspberry Pi 2” architecture to the config file.**

`echo "arch raspberrypi2 71" | tee -a /etc/opkg/arch.conf`

**6.Backup the original feeds source file.** (feeds.labviewmakerhub.com)

`mv /etc/opkg/base-feeds.conf /etc/opkg/base-feeds.conf_bak`

**7.Add “QWAVESYS” feeds source server,** (http://ftp.qwavesys.com/ipk/)

`echo "src/gz uri-all-0 http://ftp.qwavesys.com/ipk/all" | tee -a /etc/opkg/base-feeds.conf`

`echo "src/gz uri-armv7a-vfp-0 http://ftp.qwavesys.com/ipk/armv7a-vfp" | tee -a /etc/opkg/base-feeds.conf`

`echo "src/gz uri-generic_armv7a-0 http://ftp.qwavesys.com/ipk/raspberrypi2" | tee -a /etc/opkg/base-feeds.conf`

**8.Install packages from QWAVESYS server.**

`opkg update`

`opkg install python`

`opkg install opencv`

`opkg install packagegroup-core-buildessential`

`opkg install wiringpi`

`opkg install wiringpi-dev`

**9.Copy the shared library (.so) files from "Shared-Library" on this repo to `/srv/chroot/labview/usr/lib`.** *Required only ".so" files.

**10.Modified the ".profile" config file , located at "/home/pi".**
Refer to "Config-Files" folder on this repo.

**11.Modified the "nilvrt" file, Located at "/srv/chroot/labview/usr/local/natinst/etc/init.d", This will allow export DISPLAY inside LV chroot to RPi display, Default =:0.0.**
Refer to "Config-Files" folder on this repo. 

**12.Navigate to "..\vi.lib\Q-Wave Systems\QwaveSys RPi Package 2.0\Solutions".** There are a lots of shipped solutions for you.

#Released Notes:

**Initial Released 2.0.0.18**

**Add-ons Library:**

-ADC_PCF8591 (Analog ADC: 4Ch AI, 1 Ch for AO)

-DHTxx (DHT11,DHT22 Temperature sensor)

-DS18b20 (1-Wire Digital temperature sensor)

-OpenCV (Based on OpenCV 3.0)

-USBCamera (USB driver)

-WebSockets API (IE) * Created by "Sam Sharp - Intelligent Energy"

-WiringPi (GPIO library)

**Examples :**

**Exercises located at -> LabVIEW 2014\vi.lib\Q-Wave Systems\QwaveSys RPi Package 2.0\Exercises**

**Solutions located at -> LabVIEW 2014\vi.lib\Q-Wave Systems\QwaveSys RPi Package 2.0\Solutions**

-Exercise 1 GPIO

-Exercise 2 Temp Sensor

-Exercise 3 ADC

-Exercise 4 Camera

-Exercise 5 Webservice

-Exercise 6 Network Communucation

-Exercise 7 Websocket

-Exercise 8 OpenCV Color Detect

-Exercise 9 OpenCV Pattern Matching

-Exercise 10 Tag WebUI

-Exercise 11 WebUI ThinClient

-Exercise 12 Webpanel SVG-HTML5

-Exercise 13 Share Library Development

-Exercise 14 WiringPi Library Development

------------------------------------------------------------------

-Raspberry Pi™ is a registered trademark of the Raspberry Pi foundation.
-LINX 3.0 for Raspberry Pi 2B/3B create by `www.labviewmakerhub.com` (LabVIEW 2014 only,***Non-commercial use)

-WiringPi is a GPIO access library based on BCM2835 library used in the Raspberry Pi. It’s released under the GNU LGPLv3 license created by Gordon Henderson. `(http://wiringpi.com/)`
-OpenCV is released under a BSD license and hence it’s free for both academic and commercial use. `(http://opencv.org/)`

------------------------------------------------------------------
Created by `Amornthep Phunsin` and `Supawat Armart` (Q-Wave Systems Co.,Ltd)
Contact : `"amornthep@qwavesys.com"`

If you find this package is useful, please consider supporting it with a donation. 
https://www.paypal.me/qwavesystems
