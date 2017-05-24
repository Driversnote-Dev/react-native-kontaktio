# Android Setup

Some [Kontakt.io beacons prerequisites](https://developer.kontakt.io/android-sdk/quickstart/#setup) have to be met.

### Automatic setup

// UNDER CONSTRUCTION

After the update the manual setup should should be easier when using `react-native link react-native-kontaktio`. However this was not tested yet. Will be tested soon and this section updated. For now, please refer to the manual setup.

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

4. In `android/app/src/main/AndroidManifest.xml` inside `<application />` add 

	```xml
	<service android:name="com.kontakt.sdk.android.ble.service.ProximityService" android:exported="false"/>
	```

5. In `android/app/build.gradle` 

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

4. The following step is inside the [Kontakt.io docs](http://developer.kontakt.io/android-sdk/2.1.0/quickstart/) but was not necessary on the devices I tested: In `android/build.gradle` add maven link:
	
	```java
	allprojects {
	    repositories {
	    	...
	    	maven {
	    		// All of React Native (JS, Obj-C sources, Android binaries) is installed from npm
	    		url "$rootDir/../node_modules/react-native/android"
        	}
	       maven { url "http://repo.kontakt.io/repository/internal/" }   // <-- Add this line
	    }
	}
	
	```
