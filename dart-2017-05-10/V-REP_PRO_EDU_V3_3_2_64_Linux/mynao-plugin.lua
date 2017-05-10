checkAndLoadPlugin=function(pluginFile,pluginName)
    -- Check if the required plugin is there:
    print ("Check ",pluginFile)
    moduleName=0
    moduleVersion=0
    index=0
    vnaoModuleNotFound=true
    while moduleName do
        moduleName,moduleVersion=simGetModuleName(index)
        if (moduleName==pluginName) then
            vnaoModuleNotFound=false
        end
        index=index+1
    end
    print ("not found is : ",vnaoModuleNotFound)

    if vnaoModuleNotFound then
        pluginHandle = simLoadModule (pluginFile,pluginName)
        --if pluginHandle >= 0 then
        --    simUnloadModule (pluginHandle)
        --end
        moduleName=0
        moduleVersion=0
        index=0
        vnaoModuleNotFound=true
        while moduleName do
            moduleName,moduleVersion=simGetModuleName(index)
            if (moduleName==pluginName) then
                vnaoModuleNotFound=false
            end
            index=index+1
        end
    end 
    print ("not found is : ",vnaoModuleNotFound," handle is : ",pluginHandle)
end

getVnaoHandles = function (fileJointsName,naoSuffix,sensorsNameList)
   -- define empty arrays
   nao_joint_max = 30
   jointsName = {}
   jointsHandle = {}
   for i=1,nao_joint_max do
      jointsName[#jointsName+1] = ""
      jointsHandle[#jointsHandle+1] = -1
   end
   nao_sensor_max = 10
   sensorsName = {}
   sensorsHandle = {}
   for i=1,nao_sensor_max do
      sensorsName[#sensorsName+1] = ""
      sensorsHandle[#sensorsHandle+1] = -1
   end
   -- Init joint names (load from file)
   --fileJointsName="joints_names_no_hands.txt"
   f = io.open(fileJointsName, "rb")
   n=0
   nJoint=0
   for line in f:lines() do
      if n>0 then
	 nJoint = nJoint+1
	 jointsName[nJoint] = line..naoSuffix
	 -- print (line..", "..#line)
      end
      n = n+1
   end
   f:close()

   -- Predefined Joint Names
   --jointNames = {"HeadYaw","HeadPitch","LShoulderPitch","LShoulderRoll",
   --"LElbowYaw","LElbowRoll","LWristYaw","LHipYawPitch","LHipRoll","LHipPitch",
   --"LKneePitch","LAnklePitch","LAnkleRoll","RHipYawPitch","RHipRoll","RHipPitch",
   --"RKneePitch","RAnklePitch","RAnkleRoll","RShoulderPitch","RShoulderRoll",
   --"RElbowYaw","RElbowRoll","RWristYaw"}

   -- find joints handles if existing 
   for i=1,nJoint,1 do
      --jointInterp[#jointInterp+1] = 0.0
      objId = simGetObjectHandle(jointsName[i])
      jointsHandle[i] = objId
      print (jointsName[i]..", "..objId)
      simAddStatusbarMessage(jointsName[i]..", id = "..objId)
   end

   -- get handles of sonar sensor
   simAddStatusbarMessage (sensorsNameList[1]..", "..sensorsNameList[2])
   nSensor = 0
   for i=1,#sensorsNameList do
      objId = simGetObjectHandle(sensorsNameList[i])
      sensorsHandle[i] = objId
      sensorsName[i] = sensorsNameList[i]
      simAddStatusbarMessage(sensorsName[i]..", id = "..objId)
      nSensor = nSensor+1
   end

   return nJoint,nSensor,jointsName,jointsHandle,sensorsName,sensorsHandle

end

simAddStatusbarMessage("Start Vnao Plugin script ...")
simSetThreadSwitchTiming(2) -- Default timing for automatic thread switching

-- Check what OS we are using:
--platf=simGetInt32Parameter(sim_intparam_platform)
--if (platf==0) then
--    pluginFile='v_repExtVnao.dll'
--end
--if (platf==1) then
--    pluginFile='libv_repExtVnao.dylib'
--end
--if (platf==2) then
--    pluginFile='libv_repExtVnao.so'
--end
vnaoModuleNotFound = true
pluginHandle = -11
pluginFile="./myPlugins/libv_repExtVnao.so"
pluginName="Vnao"
checkAndLoadPlugin(pluginFile,pluginName)


if (vnaoModuleNotFound) then
    -- Plugin was not found
    simDisplayDialog('Error',"Vnao plugin was not found. ('"..pluginFile.."')&&nSimulation will not run properly",sim_dlgstyle_ok,true,nil,{0.8,0,0,0,0,0},{0.5,0,0,1,1,1})
else
    -- Plugin is there
   simAddStatusbarMessage("Vnao Plugin Init ...")
   print("Vnao Plugin Init ...")

   naoqiPort = 11212
   naoSuffix=""
   naoName = "NAO"..naoSuffix

   sensorsNameList = {"SonarLeft","SonarRight"}
   simAddStatusbarMessage (sensorsNameList[1]..", "..sensorsNameList[2])
   nJoint,nSensor,jointsName,jointsHandle,sensorsName,sensorsHandle = getVnaoHandles("joints_names_no_hands.txt",naoSuffix,sensorsNameList)
   simAddStatusbarMessage("Vnao Plugin Create ...")
   print("Vnao Plugin Create ...")
   local robHandle=simExtVnao_create(naoqiPort,naoName,nJoint,nSensor,jointsHandle,sensorsHandle,jointsName,sensorsName)
   if robHandle>=0 then
      print("Vnao Plugin Start ...")
      simAddStatusbarMessage("Vnao Plugin Start ...")
      simExtVnao_start(robHandle) 

      print("Vnao Plugin Stop ...")
      simAddStatusbarMessage("Vnao Plugin Stop ...")
      simExtVnao_stop(robHandle)

      print("Vnao Plugin Destroy ...")
      simAddStatusbarMessage("Vnao Plugin Destroy ...")
      simExtVnao_destroy(robHandle)

      --print("Unload Vnao Module ...")
      --simAddStatusbarMessage("Unload Vnao module ...")
      --simUnloadModule(pluginHandle)
   end
end
