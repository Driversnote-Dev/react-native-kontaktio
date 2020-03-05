# Android Setup

Some [Kontakt.io beacons prerequisites](https://developer.kontakt.io/android-sdk/quickstart/#setup) have to be met.

### Auto-linking (React Native v0.60+)

1. Add package

	```bash
	$ yarn add react-native-kontaktio
	```

2. In `android/app/src/main/AndroidManifest.xml` inside `<application />` register the Proximity service:

	```diff
	<application
      android:name=".MainApplication"
      android:label="@string/app_name"
      android:icon="@mipmap/ic_launcher"
      ...
      <activity android:name="com.facebook.react.devsupport.DevSettingsActivity" />
	+ <service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
    </application>
	```

	(`...` denote omitted lines)

3. `Android Marshmallow` (6.0) or higher: Don't forget to ask the user to grant the `android.permission.ACCESS_COARSE_LOCATION` permission - see the example in `README`).


### Mostly automatic setup (React Native older than v0.60)

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

2. Link module (use `rnpm` for React Native versions before `0.27`)

		react-native link react-native-kontaktio

3. In `android/app/src/main/AndroidManifest.xml` inside `<application />` register the Proximity service:

	```xml
	<service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
	```

	i.e. your `AndroidManifest.xml` should look similar to this (`...` denote omitted lines):

	```diff
	<application
      android:name=".MainApplication"
      android:label="@string/app_name"
      android:icon="@mipmap/ic_launcher"
      ...
      <activity android:name="com.facebook.react.devsupport.DevSettingsActivity" />
	+ <service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
    </application>
	```


### Manual setup (React Native older than v0.60)

1. npm install

	```bash
	$ npm install --save react-native-kontaktio
	```

2. In `android/app/src/main/java/.../MainApplication.java` import `KontaktPackage` and add it to the List:

	```java
	import com.artirigo.kontaktio.KontaktPackage;
	...
	return Arrays.<ReactPackage>asList(
		new MainReactPackage(),
		...
		new KontaktPackage()
       );
	```

3. In `android/settings.gradle` add:

	```
	include ':react-native-kontaktio'
	project(':react-native-kontaktio').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-kontaktio/android')
	```

4. In `android/app/build.gradle`

	* Add dependency

	```java
	dependencies {
		compile project(':react-native-kontaktio')
		...
	}
	```

	* Add exclusion inside `android`, i.e.

	```java
	android {
		...
		packagingOptions {
			exclude 'main/AndroidManifest.xml'
		}
	}
	```

5. In `android/app/src/main/AndroidManifest.xml` inside `<application />` add

	```xml
	<service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
	```