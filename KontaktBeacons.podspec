require 'json'
package = JSON.parse(File.read(File.join(__dir__, 'package.json')))

Pod::Spec.new do |s|
  s.name          = "KontaktBeacons"
  s.version       = package['version']
  s.summary       = "KontaktBeacons"
  s.description   = <<-DESC
                   Cross-platform React Native module for detecting beacons with Android and iOS devices.
                   DESC
  s.license       = "MIT"
  s.homepage      = "https://github.com/Driversnote-Dev/react-native-kontaktio"
  s.author        = { "Andre Kovac" => "me@andrekovac.com" }
  s.platform     = :ios, "7.0"
  s.source         = { :git => "https://github.com/Driversnote-Dev/react-native-kontaktio.git", :tag => "master" }

  s.source_files  = "ios/**/*.{h,m}"
  s.exclude_files = "ios/KontaktSDK.framework/**/*"
  s.vendored_frameworks = 'ios/KontaktSDK.framework'

  s.dependency "React"
end
