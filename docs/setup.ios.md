# iOS Setup

Some [Kontakt.io beacons prerequisites](https://developer.kontakt.io/android-sdk/quickstart/#setup) have to be met.

### Mostly automatic setup (recommended)

When installing both, Android and iOS, steps *1* and *2* only have to be run once for both platforms.

1. Install the package

	* `yarn`

		```bash
		$ yarn add react-native-kontaktio
		```
	
	* `npm`

		```bash
		$ npm install --save react-native-kontaktio
		```

2. Link module (use `rnpm` for React Native versions older than `0.27`)

		react-native link react-native-kontaktio

3. Manually link kontakt.io SDK

	Select your build target in the **`Project navigator`**. Click **`General`** and then in the **`Embedded Binaries`** section, click the **`+`** button.
	
	- Click **`[Add Other...]`**.
	- Navigate to **`node_modules/react-native-kontaktio/ios`**.
	- Add **`KontaktSDK.framework`**.
	- Leave the selection as is (don't copy to destination)

	It should now also appear in the **`Linked Frameworks and Libraries`** section right below.

4. Add Framework Search paths so that Xcode can find the added framework

    - Go to the **Build Settings** tab and search for **"framework search paths"**.
    - Add the following path (select **recursive [v]**):
    
    	```
    	$(PROJECT_DIR)/../node_modules/react-native-kontaktio/ios
    	```

5. Add run script

	- In the **`Build Phases`** tab, click the **`+`** button at the top and select **`New Run Script Phase`**. Enter the following code into the script text field:

	```
	bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/KontaktSDK.framework/strip-frameworks.sh"
	```

6. Add permissions

	Go to the **Info** tab and add in the section **`Custom iOS Target Properties`** add either on of the following permissions:
	
	| Key | Value | Description |
	|---|---|---|
	| NSLocationAlwaysUsageDescription | Your text of the permission for the user | User allows the app to use the device location even when the app is in the background |
	| NSLocationWhenInUseUsageDescription | Your text of the permission for the user | User allows the app |