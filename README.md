# USBApp
A small test app that tries to load a USBDriverKit system extension

https://developer.apple.com/videos/play/wwdc2019/702/

You will want to edit the Info.plist of the DriverKit extension to match the Vendor ID and Product ID of a test device you have. Then after you activate the extension, attach the USB device and your DriverKit application should start on demand.


## Important Xcode settings

- Xcode: PROJECT: USBApp > Build Settings > Signing > Code Signing Identity > **Sign to Run Locally**
- Xcode: TARGETS: USBApp > Build Settings > Signing > Code Signing Identity > **Sign to Run Locally**
- Xcode: TARGETS: USBApp > Build Phases > Embed System Extensions > **[ x ] Copy only when installing**

Now you can run it from within Xcode.

## Troubleshooting
- Problem: Hit button Activate: Does not work, will fails with "didFailWithError <private>" see Xcode console.
- Solution: (not found so far)
