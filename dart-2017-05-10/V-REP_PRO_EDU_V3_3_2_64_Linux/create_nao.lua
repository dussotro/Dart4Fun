
function createCylinder(size,name,posit,orient,hRef,localRespMask,globalRespMask)
   local h
   h=simCreatePureShape(2,1+2+4+8,size,0.050)
   simSetObjectName(h,name)
   simSetObjectPosition(h,hRef,posit)
   orientRad={0.,0.,0.}
   for i=1,#orient do
      orientRad[i] = orient[i]*degRad
   end
   simSetObjectOrientation(h,hRef,orientRad)
   respMask = localRespMask + 256*globalRespMask
   simSetObjectInt32Parameter(h,sim_shapeintparam_respondable_mask,respMask)
   return h
end

function createSphere(size,name,posit,hRef,localRespMask,globalRespMask)
   local h
   h=simCreatePureShape(1,1+2+4+8,size,0.050)
   simSetObjectName(h,name)
   simSetObjectPosition(h,hRef,posit)
   respMask = localRespMask + 256*globalRespMask
   simSetObjectInt32Parameter(h,sim_shapeintparam_respondable_mask,respMask)
   return h
end

function createCuboid(size,name,posit,orient,hRef,localRespMask,globalRespMask)
   local h
   h=simCreatePureShape(0,1+2+4+8,size,0.050)
   simSetObjectName(h,name)
   simSetObjectPosition(h,hRef,posit)
   orientRad={0.,0.,0.}
   for i=1,#orient do
      orientRad[i] = orient[i]*degRad
   end
   simSetObjectOrientation(h,hRef,orientRad)
   respMask = localRespMask + 256*globalRespMask
   simSetObjectInt32Parameter(h,sim_shapeintparam_respondable_mask,respMask)
   return h
end

function createJoint(jointName,range,angle0,posit,orient,hRef)
   jointModeOption=0
   jointMode=sim_jointmode_force
   --jointMode=sim_jointmode_passive
   h = simCreateJoint(sim_joint_revolute_subtype,jointMode,jointModeOption,NULL,NULL,NULL)
   simSetObjectName(h,jointName)
   tJointName[#tJointName+1] = jointName
   tJointHandle[#tJointHandle+1] = h
   tJointRange[#tJointRange+1] = range 
   simSetJointPosition(h,angle0*degRad)
   --simAddStatusbarMessage(h..","..simGetObjectHandle(jointName))
   orientRad={0.,0.,0.}
   for i=1,#orient do
      orientRad[i] = orient[i]*degRad
   end
   simSetObjectOrientation(h,-1,orientRad)
   simSetObjectPosition(h,hRef,posit)
   return h
end


create_nao = function (naoFullName,posit2d)
   -- Put some initialization code here
   radDeg = 180.0/math.pi
   degRad = math.pi/180.0

   -- Make sure you read the section on "Accessing general-type objects programmatically"
   -- For instance, if you wish to retrieve the handle of a scene object, use following instruction:
   --
   -- !! Main dummy object should be set as model (in Common tab of object's GUI interface)
   --handleMain=simGetObjectHandle('Main')
   h=simCreateDummy(0.001,NULL)
   simSetObjectName(h,"Main")
   simSetObjectPosition(h,-1,{0.0,0.0,0.33})
   handleMain=h
   -- 
   -- Above instruction retrieves the handle of 'sceneObjectName' if this script's name has no '#' in it
   --
   -- If this script's name contains a '#' (e.g. 'someName#4'), then above instruction retrieves the handle of object 'sceneObjectName#4'
   -- This mechanism of handle retrieval is very convenient, since you don't need to adjust any code when a model is duplicated!
   -- So if the script's name (or rather the name of the object associated with this script) is:
   --
   -- 'someName', then the handle of 'sceneObjectName' is retrieved
   -- 'someName#0', then the handle of 'sceneObjectName#0' is retrieved
   -- 'someName#1', then the handle of 'sceneObjectName#1' is retrieved
   -- ...
   --
   -- If you always want to retrieve the same object's handle, no matter what, specify its full name, including a '#':
   --
   -- handle=simGetObjectHandle('sceneObjectName#') always retrieves the handle of object 'sceneObjectName' 
   -- handle=simGetObjectHandle('sceneObjectName#0') always retrieves the handle of object 'sceneObjectName#0' 
   -- handle=simGetObjectHandle('sceneObjectName#1') always retrieves the handle of object 'sceneObjectName#1'
   -- ...
   --
   -- Refer also to simGetCollisionhandle, simGetDistanceHandle, simGetIkGroupHandle, etc.
   --
   -- Following 2 instructions might also be useful: simGetNameSuffix and simSetNameSuffix

   -- simCreatePureShape
   --   Primitive Type : 0 for a cuboid, 1 for a sphere, 2 for a cylinder and 3 for a cone 
   --   options: Bit-coded: if bit0 is set (1), backfaces are culled.
   --              If bit1 is set (2), edges are visible.
   --              If bit2 is set (4), the shape appears smooth. 
   --              If bit3 is set (8), the shape is respondable. 
   --              If bit4 is set (16), the shape is static.
   --              If bit5 is set (32), the cylinder has open ends
   -- sizes: 3 values indicating the size of the shape 
   -- mass: the mass of the shape
   -- precision: 2 values that allow specifying the number of sides and faces 
   --              of a cylinder or sphere. Can be NULL for default values



   -- Torso

   handleTorso1=createCylinder({0.1,0.1,0.10},"Torso1",{0.0,0.0,0.04},{0.0,0.0,0.0},handleMain,0,0)  
   handleTorso2=createCylinder({0.05,0.05,0.04},"Torso2",{0.0,0.0,-0.07},{0.0,0.0,0.0},handleMain,0,0)    
   handleTorso = simGroupShapes({handleTorso2,handleTorso1},2)
   simSetObjectName(handleTorso,naoFullName)
   simSetObjectParent(handleTorso,handleMain,true) -- last prm bool : keepInPlace
   simSetObjectInt32Parameter(handleTorso,sim_shapeintparam_respondable_mask,1+255*256)

   -- Head
   handleNeck=createCylinder({0.02,0.02,0.02},"NeckResp",{0.0,0.0,0.1265},{0.0,0.0,0.0},handleMain,0,0)
   handleHead=createCylinder({0.06,0.06,0.08},"HeadResp",{0.0,0.0,0.1665},{90.0,0.0,0.0},handleMain,2,255)
   
   -- Legs
   handleLPelvis=createCylinder({0.02,0.02,0.08},"LPelvisResp",{-0.02,0.030,-0.065},{0.0,90.0,0.0},handleMain,2,255)
   handleRPelvis=createCylinder({0.02,0.02,0.08},"RPelvisResp",{-0.02,-0.030,-0.065},{0.0,90.0,0.0},handleMain,2,255)
   handleLHip=createCylinder({0.01,0.01,0.06},"LHipResp",{-0.03,0.05,-0.085},{0.0,90.0,0.0},handleMain,0,0)
   handleRHip=createCylinder({0.01,0.01,0.06},"RHipResp",{-0.03,-0.05,-0.085},{0.0,90.0,0.0},handleMain,0,0)
   handleLTight=createCylinder({0.04,0.04,0.08},"LTightResp",{0.0,0.05,-0.135},{0.0,0.0,0.0},handleMain,4,255)
   handleRTight=createCylinder({0.04,0.04,0.08},"RTightResp",{0.0,-0.05,-0.135},{0.0,0.0,0.0},handleMain,4,255)
   handleLTibia=createCylinder({0.04,0.04,0.08},"LTibiaResp",{0.0,0.05,-0.245},{0.0,0.0,0.0},handleMain,8,255)
   handleRTibia=createCylinder({0.04,0.04,0.08},"RTibiaResp",{0.0,-0.05,-0.245},{0.0,0.0,0.0},handleMain,8,255)
   handleLAnkle=createCylinder({0.03,0.03,0.06},"LAnkleResp",{0.0,0.05,-0.305},{0.0,90.0,0.0},handleMain,0,0)
   handleRAnkle=createCylinder({0.03,0.03,0.06},"RAnkleResp",{0.0,-0.05,-0.305},{0.0,90.0,0.0},handleMain,0,0)
   handleLFoot=createCuboid({0.15,0.08,0.02},"LFootResp",{0.03,0.05,-0.325},{0.0,0.0,0.0},handleMain,1,255)
   handleRFoot=createCuboid({0.15,0.08,0.02},"RFootResp",{0.03,-0.05,-0.325},{0.0,0.0,0.0},handleMain,1,255)



   -- arms

   rSph = 0.02
   rCyl = 0.02

   handleLShoulder=createSphere({rSph,rSph,rSph},"LShoulderResp",{0.00,0.098,0.100},handleMain,0,0)
   handleRShoulder=createSphere({rSph,rSph,rSph},"RShoulderResp",{0.00,-0.098,0.100},handleMain,0,0)
   handleLBiceps=createCylinder({rCyl,rCyl,0.06},"LBicepsResp",{0.050,0.102,0.100},{90.0,100.0,0.0},handleMain,16,255)
   handleRBiceps=createCylinder({rCyl,rCyl,0.06},"RBicepsResp",{0.050,-0.102,0.100},{90.0,80.0,0.0},handleMain,16,255)
   handleLElbow=createSphere({rSph,rSph,rSph},"LElbowResp",{0.105,0.113,0.100},handleMain,0,0)
   handleRElbow=createSphere({rSph,rSph,rSph},"RElbowResp",{0.105,-0.113,0.100},handleMain,0,0)
   handleLForeArm=createCylinder({rCyl,rCyl,0.055*0.6},"LForeArmResp",{0.128,0.113,0.100},{0.0,90.0,0.0},handleMain,32,255)
   handleRForeArm=createCylinder({rCyl,rCyl,0.055*0.6},"RForeArmResp",{0.128,-0.113,0.100},{0.0,90.0,0.0},handleMain,32,255)
   handleLHand=createCylinder({rCyl,rCyl,0.057*0.6},"LHandResp",{0.1835,0.113,0.100},{0.0,90.0,0.0},handleMain,0,0)
   handleRHand=createCylinder({rCyl,rCyl,0.057*0.6},"RHandResp",{0.1835,-0.113,0.100},{0.0,90.0,0.0},handleMain,0,0)
   handleLFingers=createSphere({rSph,rSph,rSph},"LFingersResp",{0.217,0.113,0.100},handleMain,0,0)
   handleRFingers=createSphere({rSph,rSph,rSph},"RFingersResp",{0.217,-0.113,0.100},handleMain,0,0)

   handleLFullHand = simGroupShapes({handleLFingers,handleLHand},2)
   simSetObjectName(handleLFullHand,"LFullHandResp")
   simSetObjectInt32Parameter(handleLFullHand,sim_shapeintparam_respondable_mask,1+255*256)

   --simAddStatusbarMessage(handleRHand..","..handleRFingers)    
   handleRFullHand = simGroupShapes({handleRFingers,handleRHand},2)
   simSetObjectName(handleRFullHand,"RFullHandResp")
   simSetObjectInt32Parameter(handleRFullHand,sim_shapeintparam_respondable_mask,1+255*256)

   -- create joints 
   -- simCreateJoint
   -- prms:
   --   jointType: sim_joint_revolute_subtype, sim_joint_prismatic_subtype or sim_joint_spherical_subtype
   --   jointMode: a joint mode value
   --   options: bit-coded. For now only bit 0 is used (if set (1), the joint operates in hybrid mode)
   --   sizes: pointer to 2 values indicating the joint length and diameter. Can be NULL for default values
   --   colorA: pointer to 4x3 values for joint color A (ambient_diffuse rgb, 3 reserved values (set to zero), specular rgb and emission rgb). Can be NULL for default values
   --   colorB: pointer to 4x3 values for joint color B (ambient_diffuse rgb, 3 reserved values (set to zero), specular rgb and emission rgb). Can be NULL for default values

   -- jointMode can be :
   --   sim_jointmode_passive
   --   sim_jointmode_motion_deprecated
   --   sim_jointmode_ik
   --   sim_jointmode_ikdependent
   --   sim_jointmode_dependent
   --   sim_jointmode_force

   tJointName = {}
   tJointHandle = {}
   tJointRange = {}

   jointModeOption=0
   jointMode=sim_jointmode_force
   --jointMode=sim_jointmode_passive


   -- Head

   h=createJoint("HeadYaw",{-119.5,119.5,0.0},0.0,{0.0,0.0,0.1265},{0.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleTorso,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleNeck,h,true) -- last prm bool : keepInPlace

   h=createJoint("HeadPitch",{-38.5,29.5,0.0},0.0,{0.0,0.0,0.1265},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleNeck,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleHead,h,true) -- last prm bool : keepInPlace

   -- Left Leg

   h=createJoint("LHipYawPitch",{-65.62,42.44,0.0},0.0,{0.0,0.05,-0.085},{-135.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleTorso,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLPelvis,h,true) -- last prm bool : keepInPlace

   h=createJoint("LHipRoll",{-21.74,45.29,0.0},0.0,{0.0,0.05,-0.085},{0.0,90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleLPelvis,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLHip,h,true) -- last prm bool : keepInPlace

   h=createJoint("LHipPitch",{-88.00,27.73,0.0},0.0,{0.0,0.05,-0.085},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleLHip,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLTight,h,true) -- last prm bool : keepInPlace

   h=createJoint("LKneePitch",{-5.29,121.04,0.0},0.0,{0.0,0.05,-0.185},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleLTight,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLTibia,h,true) -- last prm bool : keepInPlace

   h=createJoint("LAnklePitch",{-68.15,52.86,0.0},0.0,{0.0,0.05,-0.305},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleLTibia,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLAnkle,h,true) -- last prm bool : keepInPlace

   h=createJoint("LAnkleRoll",{-22.79,44.06,0.0},0.0,{0.0,0.05,-0.305},{0.0,90.0,0.0},handleMain)
   simSetObjectParent(h,handleLAnkle,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLFoot,h,true) -- last prm bool : keepInPlace

   -- Right Leg
   
   h=createJoint("RHipYawPitch",{-65.62,42.44,0.0},0.0,{0.0,-0.05,-0.085},{-45,0.0,0.0},handleMain)
   simSetObjectParent(h,handleTorso,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRPelvis,h,true) -- last prm bool : keepInPlace

   h=createJoint("RHipRoll", {-45.29,21.74,0.0},0.0,{0.0,-0.05,-0.085},{0.0,90.0,0.0},handleMain)
   simSetObjectParent(h,handleRPelvis,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRHip,h,true) -- last prm bool : keepInPlace

   h=createJoint("RHipPitch",{-88.00,27.73,0.0},0.0,{0.0,-0.05,-0.085},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleRHip,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRTight,h,true) -- last prm bool : keepInPlace

   h=createJoint("RKneePitch",{-5.90,121.47,0.0},0.0,{0.0,-0.05,-0.185},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleRTight,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRTibia,h,true) -- last prm bool : keepInPlace

   h=createJoint("RAnklePitch",{-67.97,53.40,0.0},0.0,{0.0,-0.05,-0.305},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleRTibia,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRAnkle,h,true) -- last prm bool : keepInPlace

   h=createJoint("RAnkleRoll",{-44.06,22.80,0.0},0.0,{0.0,-0.05,-0.305},{0.0,90.0,0.0},handleMain)
   simSetObjectParent(h,handleRAnkle,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRFoot,h,true) -- last prm bool : keepInPlace

   -- Left Arm

   h=createJoint("LShoulderPitch",{-119.5,119.5,0.0},0.0,{0.0,0.098,0.100},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleTorso,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLShoulder,h,true) -- last prm bool : keepInPlace

   h=createJoint("LShoulderRoll",{-18.0,76.0,0.0},0.0,{0.0,0.098,0.100},{0.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleLShoulder,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLBiceps,h,true) -- last prm bool : keepInPlace

   h=createJoint("LElbowYaw",{-119.5,119.5,0.0},0.0,{0.105,0.113,0.100},{0.0,90.0,0.0},handleMain)
   simSetObjectParent(h,handleLBiceps,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLElbow,h,true) -- last prm bool : keepInPlace

   h=createJoint("LElbowRoll",{-88.5,-2.0,0.0},-2.0,{0.105,0.113,0.100},{0.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleLElbow,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLForeArm,h,true) -- last prm bool : keepInPlace

   h=createJoint("LWristYaw",{-104.5,104.5,0.0},0.0,{0.16095,0.113,0.100},{0.0,90.0,-90.0},handleMain)
   simSetObjectParent(h,handleLForeArm,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleLFullHand,h,true) -- last prm bool : keepInPlace


   -- Right Arm

   h=createJoint("RShoulderPitch",{-119.5,119.5,0.0},0.0,{0.0,-0.098,0.100},{-90.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleTorso,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRShoulder,h,true) -- last prm bool : keepInPlace

   h=createJoint("RShoulderRoll", {-76.0,18.0,0.0},0.0,{0.0,-0.098,0.100},{0.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleRShoulder,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRBiceps,h,true) -- last prm bool : keepInPlace

   h=createJoint("RElbowYaw",{-119.5,119.5,0.0},0.0,{0.105,-0.113,0.100},{0.0,90.0,0.0},handleMain)
   simSetObjectParent(h,handleRBiceps,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRElbow,h,true) -- last prm bool : keepInPlace

   h=createJoint("RElbowRoll",{2.0,88.5,0.0},2.0,{0.105,-0.113,0.100},{0.0,0.0,0.0},handleMain)
   simSetObjectParent(h,handleRElbow,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRForeArm,h,true) -- last prm bool : keepInPlace

   h=createJoint("RWristYaw", {-104.5,104.5,0.0},0.0,{0.16095,-0.113,0.100},{0.0,90.0,-90.0},handleMain)
   simSetObjectParent(h,handleRForeArm,true) -- last prm bool : keepInPlace
   simSetObjectParent(handleRFullHand,h,true) -- last prm bool : keepInPlace


   -- set joint paramaters for dynamic simulation

   for i=1,#tJointHandle do
      h = tJointHandle[i]
      local cyclic=true
      angles = tJointRange[i]
      angles[3] = angles[2]-angles[1]
      print (tJointName[i],angles[1],angles[2],angles[3])
      simSetObjectInt32Parameter(h,sim_jointintparam_motor_enabled,1) 
      simSetObjectInt32Parameter(h,sim_jointintparam_ctrl_enabled,1)  
      simSetObjectFloatParameter(h,sim_jointfloatparam_upper_limit,100.0)
      simSetJointForce(h,1000.0)     
      status = simSetJointInterval(h,cyclic,{angles[1]*degRad,angles[3]*degRad})
      vcycl,angles=simGetJointInterval(h)
      if vcycl then
	 simAddStatusbarMessage("Joint "..i..", interval is : ["..angles[1]..","..angles[2].."], cyclic is true, status is"..status)
      else
	 simAddStatusbarMessage("Joint "..i..", interval is : ["..angles[1]..","..angles[2].."], cyclic is false, status is"..status)
      end
      simResetDynamicObject(h)
   end


   shapeDensity = {}
   shapeDensity[#shapeDensity+1]={handleTorso,10.0}

   shapeDensity[#shapeDensity+1]={handleNeck,5.0}
   shapeDensity[#shapeDensity+1]={handleHead,5.0}

   legDensity = 10.0
   shapeDensity[#shapeDensity+1]={handleLPelvis,legDensity}
   shapeDensity[#shapeDensity+1]={handleRPelvis,legDensity}
   shapeDensity[#shapeDensity+1]={handleLHip,legDensity}
   shapeDensity[#shapeDensity+1]={handleRHip,legDensity}
   shapeDensity[#shapeDensity+1]={handleLTight,legDensity}
   shapeDensity[#shapeDensity+1]={handleRTight,legDensity}
   shapeDensity[#shapeDensity+1]={handleLTibia,legDensity}
   shapeDensity[#shapeDensity+1]={handleRTibia,legDensity}
   shapeDensity[#shapeDensity+1]={handleLAnkle,legDensity}
   shapeDensity[#shapeDensity+1]={handleRAnkle,legDensity}
   shapeDensity[#shapeDensity+1]={handleLFoot,legDensity}
   shapeDensity[#shapeDensity+1]={handleRFoot,legDensity}

   armDensity = 5.0
   shapeDensity[#shapeDensity+1]={handleLShoulder,armDensity}
   shapeDensity[#shapeDensity+1]={handleRShoulder,armDensity}
   shapeDensity[#shapeDensity+1]={handleLBiceps,armDensity}
   shapeDensity[#shapeDensity+1]={handleRBiceps,armDensity}
   shapeDensity[#shapeDensity+1]={handleLElbow,armDensity}
   shapeDensity[#shapeDensity+1]={handleRElbow,armDensity}
   shapeDensity[#shapeDensity+1]={handleLForeArm,armDensity}
   shapeDensity[#shapeDensity+1]={handleRForeArm,armDensity}
   shapeDensity[#shapeDensity+1]={handleLFullHand,armDensity}
   shapeDensity[#shapeDensity+1]={handleRFullHand,armDensity}

   for i=1,#shapeDensity do
      --print (i,shapeDensity[i][1],shapeDensity[i][2])
      simComputeMassAndInertia(shapeDensity[i][1],shapeDensity[i][2])
   end

   simResetDynamicObject(sim_handle_all)


   -- copy/paste seems to work but not used here ...
   --simAddObjectToSelection(sim_handle_single,handleMain)
   --handleMainCopy=simCopyPasteObjects([handleMain],1) -- 1 is model object
   --print (handleMainCopy)

   --makes Torso a model
   local prp=simGetModelProperty(handleTorso)
   simSetModelProperty(handleTorso,simBoolOr32(prp,sim_modelproperty_not_model)-sim_modelproperty_not_model)

   simAddStatusbarMessage("Simulation is been freezed ...")
   modelFileName="/home/newubu/MyApps/Nao/v-rep/nao-new-model/build/vnao/V-REP_PRO_EDU_V3_3_2_64_Linux/models/robots/mobile/ROBOT_MADE_IN_LUA.ttm"
   simAddStatusbarMessage("save model to "..modelFileName)
   simSaveModel(handleTorso,modelFileName)
   --sceneFileName="/home/newubu/MyApps/Nao/v-rep/nao-new-model/ROBOT_MADE_IN_LUA.ttt"
   --simAddStatusbarMessage("save scene to "..sceneFileName)
   --simSaveScene(sceneFileName)

   posit3d = simGetObjectPosition(handleTorso,-1)
   posit3d[1]=posit2d[1]
   posit3d[2]=posit2d[2]
   simSetObjectPosition(handleTorso,-1,posit3d)

   
   --ticks = 0
   --angStep = 1.0
   --angPitch = 0.0
   --simPauseSimulation()
end
