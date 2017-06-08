# Android Setup

Some [Kontakt.io beacons prerequisites](https://developer.kontakt.io/android-sdk/quickstart/#setup) have to be met.

### Mostly automatic setup

When installing both, Android and iOS, steps *1* and *2* only have to be run once for both platforms.

1. npm install

	```bash
	$ npm install --save react-native-kontaktio
	```

2. Link module (use `rnpm` for React Native versions older than `0.27`)

		react-native link react-native-kontaktio
		
3. In `android/app/src/main/AndroidManifest.xml` inside `<application />` add the connection to the Kontakt.io SDK:

	```xml
	<service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
	```


### Manual setup

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