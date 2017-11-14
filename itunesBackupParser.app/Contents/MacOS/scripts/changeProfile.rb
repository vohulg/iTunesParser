require "spaceship"
require "logger"

#ruby changeProfile.rb nameDevice uuidDevice profileId appleId appleIdPass filePathForDownload 
#ruby changeProfile.rb "Ipad Big" c1c110b87bcdba9d64965c0985d28f77ae265de4 "net.whatsapplication.appid" "user@icloud.com" ""


#------------global var-------------------------------------#
$loginName = ARGV[3];
$password = ARGV[4];
$uuid = ARGV[1];
$logPath = "/var/log/arystan/#{$uuid}/changeProfile.log"
#$logPath = "/var/log/arystan/changeProfile.log"
$filePathForDownload = ARGV[5];


#------------FUNCTION-------------------------------------#
$logger

def initLog
	$logger = Logger.new($logPath) 
	#Logger.new(STDOUT)
	#logger.info("User-input: #{input.dump}")
end

#login
def login	
	
	ret = nil
	
	begin 
		$logger.info("\n\n Start login") 
		ret = Spaceship::Portal.login($loginName, $password)
 	  
	rescue Exception => e 
		$logger.error("\n\n Start exception login")  
  		$logger.error(e.message ) 
  		$logger.error(e.backtrace.inspect ) 
  		$logger.error("\n\n End exception login")  
	end	
	
	return ret
	
end

def downloadLoop(profile, toPath)

	content = nil;

	for i in 0..10
	
		puts "Loop iteration:%d" % i
	
		content = profile.first.download
	    if (content != nil) then
	       File.write(toPath, content)
		   break
	    end
	    
	sleep(30)   
	   
	end	
	
	return content;

end

#download profile
def download(profile, toPath)
	
	content = profile.first.download
	
	if (content == nil)
		return 1;	
	else
		File.write(toPath, content)
	end
	
	

end

#add new device
def addDevice(nameDevice, uuidDevice)
  
  ret = nil
  begin 
		$logger.info("\n\n Start addDevice") 
		ret = Spaceship::Portal.device.create!(name:nameDevice, udid: uuidDevice)
 	  
	rescue Exception => e 
		$logger.error("\n\n Start exception addDevice")  
  		$logger.error(e.message ) 
  		$logger.error(e.backtrace.inspect ) 
  		$logger.error("\n\n End exception addDevice")  
	end	
	
	return ret
  
end

def addAllDevicesToProfile(profileIn)
	profileIn.first.devices = Spaceship::Portal.device.all
	return profileIn.first.update!

end

#test function
def test
	param1 = ARGV[0]
	puts param1
	puts RUBY_VERSION
end


def process

	$logger.info("\n\n Start process")
	
	#1 Login
	client = login
	$logger.info("\n\n End login")
	if (client == nil) then
		$logger.error("faild login with login:#{$loginName}")
		return 1;
	end
	
	
	#2 Check params
	nameDevice = ARGV[0]
	uuidDevice = ARGV[1]
	bundleid = ARGV[2]

	if(nameDevice == nil || uuidDevice == nil || bundleid == nil) then
		puts "nameDevice or uuidDevice or bundleid nil";
		$logger.error("\n\n nameDevice or uuidDevice or bundleid nil")
		return 1;	
	end
	
	#3 Add new device to portal
	$logger.info("\n\n Add new device to portal")
	
	newDevice = addDevice(nameDevice, uuidDevice)
	if (newDevice == nil) then
		$logger.error("faild add new device to app portal with uuid:#{uuidDevice}")
		return 1;
	end
	
	
	#4 Get profile
	profile = Spaceship::Portal.provisioning_profile.ad_hoc.find_by_bundle_id(bundleid)
	
	if (profile.empty?) then
		$logger.error("faild to get profile with bundle id: #{bundleid}");
		return 1;
		
	end 
	
	#5 Add all existed enabled devices to profile
	profileWithAllDevices = addAllDevicesToProfile(profile)	
	if (profileWithAllDevices == nil) then
		$logger.error("faild update profile with all devices")
		return 1;
	end
	
	
	#6 Download profile to file for path	
	profileNew = Spaceship::Portal.provisioning_profile.ad_hoc.find_by_bundle_id(bundleid)
	
	$logger.info("\n\n Start download profile")
	begin  
 	  content = downloadLoop(profileNew, $filePathForDownload); 
 	 	if (content == nil) then
			$logger.error("faild download profile to path #{toPath}")
			return 1;
		end	
	rescue Exception => e  
  		$logger.error(e.message ) 
  		$logger.error(e.backtrace.inspect ) 
	end 
	
	$logger.info("\n\n End download profile") 
	
	
	
	
	
	return 0;

end


def testDownload

	login
	
	nameDevice = ARGV[0]
	uuidDevice = ARGV[1]
	bundleid = ARGV[2]

	if(nameDevice == nil || uuidDevice == nil || bundleid == nil)
		puts "nameDevice or uuidDevice or bundleid nil";
		return 1;
	else
		puts "nameDevice:#{nameDevice}"
		puts "uuidDevice:#{uuidDevice}"
		puts "bundleid:#{bundleid}"
	end
	
	profile = Spaceship::Portal.provisioning_profile.ad_hoc.find_by_bundle_id(bundleid)	
	
	
	if (profile.empty?) 
		puts "Invalid get profile for bundleid %s" % [bundleid]
		$logger.error("faild to get profile with bundle id: #{bundleid}");
		return 1;
		
	else 		
		toPath = "/common/spaceship/embedded_test.mobileprovision"
		downloadLoop(profile, toPath);
	
	end
	

end

def checkVersion	
	
    res = (RUBY_VERSION <=> "2.4.0");
    
    if(res == -1) then
    	$logger.error("invalid ruby version #{RUBY_VERSION}")    
    end 
    
    return res;

end

def checkParams
	if ARGV.empty? || ARGV.length < 6
	  puts "no valid count params. Use so call:ruby changeProfile.rb nameDevice uuidDevice profileId appleId appleIdPass filePathForDownload"
	  $logger.error("no valid count params. Use so call:ruby changeProfile.rb nameDevice uuidDevice profileId appleId appleIdPass filePathForDownload")
	  return 0;
	end
	
	return 1;
end


#main start program

initLog
$logger.info("\n\n Start ruby script")
$logger.info("ruby version is:#{RUBY_VERSION}")

res = checkParams

if(res == 0) then
	return 1
end

#ver = checkVersion
#if(ver < 0) then
#	return 1
#end


process

$logger.info("\n\n End ruby script")














#====================================================================================

#https://github.com/fastlane/fastlane/blob/master/spaceship/docs/DeveloperPortal.md documentation
#http://www.rubydoc.info/github/fastlane/spaceship/Spaceship%2FProvisioningProfile%3Adownload

#require "spaceship"


#Spaceship::Portal.login("vohulg@gmail.com", "")

#my_profile = Spaceship::Portal.provisioning_profile.app_store.find_by_bundle_id("net.whatsapplication.appid") 

#content = my_profile.first.download

#File.write("/common/out1.mobileprofile", content )


# add new device
#Spaceship::Portal.device.create!(name: "Asel Iphone 4s", udid: "339e93360347d95ce76e6013b5a9e2c52eecc28f")

#my_profile.first.devices = Spaceship::Portal.device.all

#my_profile.first.update!