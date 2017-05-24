# iOS Setup

Some [Kontakt.io beacons prerequisites](https://developer.kontakt.io/android-sdk/quickstart/#setup) have to be met.

### Mostly automatic setup

1. Link module (use `rnpm` for React Native versions older than `0.27`)

		react-native link react-native-kontaktio

2. Manually link kontakt.io SDK

	Select your build target in the **`Project navigator`**. Click **`General`** and then in the **`Embedded Binaries`** section, click the **`+`** button.
	
	- Click **`[Add Other...]`**.
	- Navigate to **`node_modules/react-native-kontaktio/ios`**.
	- Add **`KontaktSDK.framework`**.

	It should now appear in the **`Linked Frameworks and Libraries`** section right below.

3. Add Framework Search paths so that Xcode can find the added framework

    - Go to the **Build Settings** tab and search for **"framework search paths"**.
    - Add the following path (select **recursive [v]**):
    
    	```
    	$(PROJECT_DIR)/../node_modules/react-native-kontaktio/ios
    	```

4. Add run script

	- In the **`Build Phases`** tab, click the **`+`** button at the top and select **`New Run Script Phase`**. Enter the following code into the script text field:

	```
	bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/KontaktSDK.framework/strip-frameworks.sh"
	```

5. Add permissions

	Go to the **Info** tab and add in the section **`Custom iOS Target Properties`** add the following the following item:
	
	| Key | Value | Description |
	|---|---|---|
	| NSLocationAlwaysUsageDescription | This app requires background tracking | The value here will be presented to the user when the plugin requests **Background Location** permission |
