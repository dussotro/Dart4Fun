require "socket"
function sleep(sec)
    socket.select(nil,nil,sec)
end 

threadFunction=function()
    while simGetSimulationState()~=sim_simulation_advancing_abouttostop do
        local clock = os.clock
        if curPose <= nPose then
            local t0 = clock()
            --print (curPose)
            --print ("------------------------------------------------------------")
            -- check if target pose not too far from actual current pose !!!
            jointError = 0.0
            oneError = 0
            for iJo=1,#jointNames,1 do
                objId = jointHandles[iJo]
                if objId > 0 then
                    jntPos = simGetJointPosition(objId)
                    jointDiff[iJo] = math.abs(jntPos-tPose[curPose][iJo])
                    jointCur[iJo] = jntPos
                    if jointDiff[iJo] > (15.0*math.pi/180.0) then
                        oneError = oneError+1
                    end
                    jointError = jointError + jointDiff[iJo] 
                    coef = 0.9
                    jointInterp[iJo] = coef*jntPos + (1.0-coef)*tPose[curPose][iJo]
                end
            end

            if oneError >= 4 then
                print (" Err : ",oneError,jointError,curPose,t0)
            end

            for iJo=1,#jointNames,1 do
                objId = jointHandles[iJo]
                if objId > 0 then
                    jointCmd = tPose[curPose][iJo]
                    if oneError >= 4 then
                        jointCmd = jointInterp[iJo]
                    end
                    status = simSetJointTargetPosition(objId,jointCmd)
                end
            end
            for iJo=1,#jointNames,1 do
                objId = jointHandles[iJo]
                if objId > 0 then
                    jntPos = simGetJointPosition(objId)*180.0/math.pi
                    jntTargPos = simGetJointTargetPosition(objId)*180.0/math.pi
                    --jntTargVel = simGetJointTargetVelocity(objId)*180.0/math.pi
                    --print (jointNames[iJo].."("..objId.."), "..status..", "..jntPos..", "..jntTargPos..", "..tPose[curPose][iJo]*180.0/math.pi)
                end
            end
            sonarLeftDetect,sonarLeftDistance,sonarLeftIntersectPoint = simReadProximitySensor(sonarLeft)
            sonarRightDetect,sonarRightDistance,sonarRightIntersectPoint = simReadProximitySensor(sonarRight)
            --print ("Sonar Left  "..sonarLeftDetect.." d = "..sonarLeftDistance)
            --print ("Sonar Right "..sonarRightDetect.." d = "..sonarRightDistance)
            if oneError < 4 then 
                curPose = curPose +1 
            end

            --while clock()-t0 < 1 do end
            local t1 = clock()
            local dt=t1-t0
            if dt < 0.025 then
                sleep(0.025-dt)
            else
                --print ("pose "..curPose.." takes too much time "..(dt*1000.0).." ms")
            end
        else
            curPose = 1
        end
    end
end

-- Initialization: (200 before, test with 10)
simSetThreadSwitchTiming(20) -- We wanna manually switch for synchronization purpose (and also not to waste processing time!)

-- display state codes ...
simAddStatusbarMessage('state: '..simGetSimulationState())
simAddStatusbarMessage(sim_simulation_stopped.." 0")
simAddStatusbarMessage(sim_simulation_paused.." 8")
simAddStatusbarMessage(sim_simulation_advancing_firstafterstop.." 16")
simAddStatusbarMessage(sim_simulation_advancing_running.." 17")
simAddStatusbarMessage(sim_simulation_advancing_lastbeforepause.." 19")
simAddStatusbarMessage(sim_simulation_advancing_firstafterpause.." 20")
simAddStatusbarMessage(sim_simulation_advancing_abouttostop.." 21")
simAddStatusbarMessage(sim_simulation_advancing_lastbeforestop.." 22")

-- Init joint names and handles
file="/home/newubu/MyApps/Nao/v-rep/nao-new-model/joints_names.txt"
f = io.open(file, "rb")
jointNames = {}
n=0
for line in f:lines() do
    if n>0 then
        jointNames[#jointNames+1] = line
        -- print (line..", "..#line)
    end
    n = n+1
end
f:close()

-- this function is required by pcall() , a "try .. catch" like operation
function myGetObjectHandle(name)
    objId = simGetObjectHandle(name)
end

jointHandles = {}
for i=1,#jointNames,1 do
    print (jointNames[i])
    if pcall(myGetObjectHandle,jointNames[i]) then
        objId = simGetObjectHandle(jointNames[i])
    else
        objId = -1
    end
    jointHandles[#jointHandles+1] = objId
    print (jointNames[i]..", "..objId)
end

sonarLeft = simGetObjectHandle("SonarLeft");
sonarRight = simGetObjectHandle("SonarRight");

file="/home/newubu/MyApps/Nao/v-rep/nao-new-model/joints_values.txt"
f = io.open(file, "rb")
--data = f:read("*all")
--print (#data)
n=0
iJnt=1
iPose=1
tPose={{}}
for line in f:lines() do
    if n == 0 then
        nPose = tonumber(line)
    end
    if n == 1 then
        nJnt = tonumber(line)
        tJnt = {}
        for i=1,nJnt,1 do
            tJnt[#tJnt+1] = 0.0
        end
        for i=1,nPose,1 do
            tPose[i]={}
        end
    end
    if n >= 2 then
        -- v = line:sub(1,5)
        -- print (v,tonumber(v))
        tJnt[iJnt] = tonumber(line)
        iJnt = iJnt+1
        if iJnt > nJnt then
            for i=1,nJnt do
                tPose[iPose][i] = tJnt[i]
            end
            iPose = iPose+1
            iJnt = 1
        end
    end
    n = n+1
end
print (nPose.." poses with "..nJnt.." joints")
f:close()
curPose = 1

for i=1,#jointNames,1 do
    print (jointNames[i].." : "..jointHandles[i]..", "..tPose[curPose][i])
end

print("ok")
-- get all objects composing NAO
naoId = simGetObjectHandle("NAO")
tObj = simGetObjectsInTree(naoId,sim_handle_all)
print (#tObj)
for iObj=1,#tObj do
    objId = tObj[iObj]
    if simGetObjectType(objId) == sim_object_joint_type then
        print ("Object : "..simGetObjectName(objId))
        objIdParent = simGetObjectParent(objId)
        print (iObj,objId,simGetObjectType(objId))
        posAbs = simGetObjectPosition(objId,-1)
        print ("Absolute : "..posAbs[1]..", "..posAbs[2]..", "..posAbs[3])
        if objIdParent >= 0 then
            posRel = simGetObjectPosition(objId,objIdParent)
            print ("Parent : "..simGetObjectName(objIdParent))
            print ("Relative : "..posRel[1]..", "..posRel[2]..", "..posRel[3])
        end
        print ("------------------------------------------------------")
    end
end

jointDiff = {}
jointCur = {}
jointInterp = {}
for iJo=1,#jointNames,1 do
    jointDiff[#jointDiff+1] = 0.0
    jointCur[#jointCur+1] =  0.0
    jointInterp[#jointInterp+1] = 0.0
end


portNb = 20020
result=-1
--result=simLaunchExecutable('/home/newubu/MyApps/Nao/v-rep/nao-new-model/bubbleRobServer',portNb,0) -- set the last argument to 1 to see the console of the launched server
simAddStatusbarMessage('start: bubbleRobServer at port '..portNb)

-- Execute the thread function:
res = true
res,err=xpcall(threadFunction,function(err) return debug.traceback(err) end)
if not res then
   simAddStatusbarMessage('Lua runtime error: '..err)
end

-- Clean-up:


