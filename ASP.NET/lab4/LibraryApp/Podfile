platform :ios, '11.0'

target 'LibraryApp' do
  use_frameworks!

  pod 'SnapKit'
  pod 'MBProgressHUD'
  pod 'Result'
  pod 'Alamofire'
  pod 'SwiftyJSON'
  pod 'AEXML'

  post_install do |installer|
      installer.pods_project.targets.each do |target|
          if target.name == 'SnapKit'
              target.build_configurations.each do |config|
                  config.build_settings['SWIFT_VERSION'] = '4.0'
              end
          end
      end
  end
  
end
