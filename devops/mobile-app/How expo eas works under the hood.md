iOS uses **CocoaPods**: CocoaPods is a **dependency manager specifically for iOS/macOS projects**. Think of it like `npm` but for native iOS libraries.
When your Expo app uses a library like `react-native-camera`, that library has a native iOS component written in Objective-C or Swift. CocoaPods is what downloads and links that native code into your Xcode project.

### What it actually does
Your project has a `Podfile` (like `package.json` but for native iOS deps):

```
platform :ios, '13.0'

target 'MyApp' do
  pod 'React-Core', :path => '../node_modules/react-native/'
  pod 'RNCCamera', :path => '../node_modules/react-native-camera'
end
```

When you run `pod install`:
1. CocoaPods reads the `Podfile`
2. Downloads each pod (native library) from a central spec repo
3. Creates a `Pods/` directory with all native source code
4. Generates a **`.xcworkspace`** file that combines your app + all pods
5. You must open `.xcworkspace`, never `.xcodeproj` directly after this
### In Expo specifically

When you run `npx expo prebuild`, Expo auto-generates the `ios/` folder and the `Podfile`. EAS Build then runs `pod install` on the remote macOS VM before compiling.


## How expo build uses fastlane

### What it is

Fastlane is an **automation toolkit for mobile build & release tasks**. It's a Ruby-based tool that wraps Xcode command-line tools, Apple's APIs, and Google Play APIs into scriptable "lanes."

Without Fastlane, deploying an iOS app manually looks like:

- Open Xcode → Archive → Export → Upload to App Store Connect → Set build in TestFlight → Submit for review

Fastlane automates all of that into one command.

### Core concepts

**`Fastfile`** — where you define lanes (automation scripts):

```
lane :beta do
  increment_build_number          # bump build number
  build_app(scheme: "MyApp")      # compile the app
  upload_to_testflight            # push to TestFlight
end
```

Run it with: `fastlane beta`

the `match` action is the most important in the fastlane CI/CD pipeline

Certificates and provisioning profiles are the most painful part of iOS. `match` solves this by:
1. Storing all your certs/profiles **encrypted in a private Git repo**
2. Any machine (or CI server) clones that repo, decrypts, and installs the certs automatically
3. No more manually exporting `.p12` files from Keychain

This is exactly what **EAS Build replicates internally** for managed credentials. EAS Build doesn't expose Fastlane to you directly, but it uses it **under the hood** on its macOS build VMs. Here's the actual sequence:

You run: eas build --platform ios

```
EAS Cloud VM does:
│
├── 1. Clone your repo
├── 2. npm install / yarn install
├── 3. npx expo prebuild (generates ios/ folder if not committed)
├── 4. pod install (CocoaPods installs native deps)
├── 5. Install signing credentials (certs + provisioning profiles)
│       └── EAS fetches these from its credential store
│           (mimicking what fastlane match does)
│
├── 6. Run xcodebuild (via fastlane gym internally)
│       xcodebuild archive -workspace MyApp.xcworkspace \
│                          -scheme MyApp \
│                          -archivePath MyApp.xcarchive
│
├── 7. Export .ipa from the archive
│       xcodebuild -exportArchive -archivePath MyApp.xcarchive \
│                  -exportOptionsPlist ExportOptions.plist \
│                  -exportPath output/
│
└── 8. Upload artifact to EAS servers
```



Android uses **Gradle — the Android equivalent of CocoaPods + build system combined**
Gradle is Android's **build system AND dependency manager** in one. It's configured via `build.gradle` files:

```
android {
    compileSdkVersion 34
    defaultConfig {
        applicationId "com.myapp"
        minSdkVersion 21
        targetSdkVersion 34
        versionCode 1
        versionName "1.0"
    }
    signingConfigs {
        release {
            keyAlias keystoreProperties['keyAlias']
            keyPassword keystoreProperties['keyPassword']
            storeFile file(keystoreProperties['storeFile'])
            storePassword keystoreProperties['storePassword']
        }
    }
}

dependencies {
    implementation 'com.facebook.react:react-android'
    implementation 'androidx.appcompat:appcompat:1.6.1'
}
```

When you run `./gradlew assembleRelease` (build the app), Gradle:
1. Downloads all dependencies from **Maven Central** (Android's equivalent of CocoaPods spec repo / npm registry)
2. Compiles Java/Kotlin source code via the **Android SDK**
3. Compiles JS bundle via Metro (called from Gradle)
4. Packages everything into an `.apk` or `.aab`
5. Signs it with your keystore


Instead of certificates + provisioning profiles (iOS), Android uses a **keystore file** — a binary file containing your private key.

```
myapp.keystore  ← binary file, keep this safe forever
    ├── Key alias: "myapp-key"
    ├── Key password: "secret123"
    └── Store password: "secret456"
```

You sign with:
```
jarsigner -keystore myapp.keystore \
          -storepass secret456 \
          app-release-unsigned.apk myapp-key
```

EAS manages this keystore for you — it generates one, stores it securely, and injects it into the Gradle signing config at build time.

The actual compilers needed:
**Android SDK** : Core platform libraries your app compiles against
**Build Tools** (`aapt2`, `d8`, `zipalign`) : Compile resources, convert bytecode, optimize apk
**JDK (Java 17)** : Gradle itself runs on Java

iOS Build
CocoaPods
- Podfile
- Downloads from CocoaPods spec repo

Xcode / xcodebuild
- Compiles Swift/Objc
- Bundles JS (via Metro)

Fastlane (automation layer)
- gym → wraps xcodebuild
- match → manages certs
- pilot → uploads to TF

Signing:
Certificate (.p12) + Provisioning Profile (.mobileprovision) (managed by Apple)


Android Build

Gradle (built-in dep manager)
- build.gradle
- Downloads from Maven Central

Android SDK / Gradle tasks
- Compiles Java/Kotlin
- Bundles JS (via Metro)
Gradle tasks (do it directly)
- assembleRelease / bundleRelease
- No equivalent needed

Signing:
- Keystore file (•jks / .keystore) (self-managed, no Apple equivalent)