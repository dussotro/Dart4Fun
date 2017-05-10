// Copyright 2006-2016 Coppelia Robotics GmbH. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// -------------------------------------------------------------------
// THIS FILE IS DISTRIBUTED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY. THE USER WILL USE IT AT HIS/HER OWN RISK. THE ORIGINAL
// AUTHORS AND COPPELIA ROBOTICS GMBH WILL NOT BE LIABLE FOR DATA LOSS,
// DAMAGES, LOSS OF PROFITS OR ANY OTHER KIND OF LOSS WHILE USING OR
// MISUSING THIS SOFTWARE.
// 
// You are free to use/modify/distribute this file for whatever purpose!
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.3.2 on August 29th 2016

#include "v_repExtPluginSkeleton.h"
#include "scriptFunctionData.h"
#include "v_repLib.h"
#include <iostream>

#ifdef _WIN32
    #ifdef QT_COMPIL
        #include <direct.h>
    #else
        #include <shlwapi.h>
        #pragma comment(lib, "Shlwapi.lib")
    #endif
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
    #include <unistd.h>
#endif /* __linux || __APPLE__ */

#ifdef __APPLE__
#define _stricmp strcmp
#endif

#define CONCAT(x,y,z) x y z
#define strConCat(x,y,z)    CONCAT(x,y,z)

#define PLUGIN_VERSION 3 // 2 since version 3.2.1, 3 since V3.3.1

LIBRARY vrepLib; // the V-REP library that we will dynamically load and bind

// --------------------------------------------------------------------------------------
// simExtSkeleton_getSensorData: an example of custom Lua command, passing simple data structures
// --------------------------------------------------------------------------------------
#define LUA_GETSENSORDATA_COMMAND "simExtSkeleton_getSensorData" // the name of the new Lua command

const int inArgs_GETSENSORDATA[]={ // Decide what kind of arguments we need
    3, // we want 3 input arguments
    sim_script_arg_int32,0, // first argument is an integer
    sim_script_arg_float|sim_script_arg_table,3, // second argument should be a table of at least 3 float values (use 0 instead of 3 for a table of random size)
    sim_script_arg_int32|sim_script_arg_table,2, // third argument should be a table of at least 2 integer values (use 0 instead of 2 for a table of random size)
};

void LUA_GETSENSORDATA_CALLBACK(SScriptCallBack* p)
{ // the callback function of the new Lua command ("simExtSkeleton_getSensorData")
    CScriptFunctionData D;
    // If successful the command will return an interger (result), a float table of size 3 (data), and a float (distance). If the command is not successful, it will not return anything
    bool commandWasSuccessful=false;
    int returnResult;
    std::vector<float> returnData;
    float returnDistance;
    if (D.readDataFromStack(p->stackID,inArgs_GETSENSORDATA,inArgs_GETSENSORDATA[0],LUA_GETSENSORDATA_COMMAND))
    { // above function reads in the expected arguments. If the arguments are wrong, it returns false and outputs a message to the simulation status bar
        std::vector<CScriptFunctionDataItem>* inData=D.getInDataPtr();

        int sensorIndex=inData->at(0).int32Data[0]; // the first argument
        std::vector<float>& floatParameters=inData->at(1).floatData; // the second argument
        std::vector<int>& intParameters=inData->at(2).int32Data; // the third argument

        // Now you can do something with above's arguments. For example:
        if ((sensorIndex>=0)&&(sensorIndex<10))
        {
            commandWasSuccessful=true;
            returnResult=1;
            returnData.push_back(1.0f);
            returnData.push_back(2.0f);
            returnData.push_back(3.0f);
            returnDistance=59.0f;
        }
        else
            simSetLastError(LUA_GETSENSORDATA_COMMAND,"Invalid sensor index."); // output an error message to the simulator's status bar
    }
    if (commandWasSuccessful)
    { // prepare the return values:
        D.pushOutData(CScriptFunctionDataItem(returnResult));
        D.pushOutData(CScriptFunctionDataItem(returnData));
        D.pushOutData(CScriptFunctionDataItem(returnDistance));
    }
    D.writeDataToStack(p->stackID);
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// simExtSkeleton_getData: an example of custom Lua command, passing complex data structures
// --------------------------------------------------------------------------------------
#define LUA_GETDATA_COMMAND "simExtSkeleton_getData" // the name of the new Lua command

void LUA_GETDATA_CALLBACK(SScriptCallBack* p)
{ // the callback function of the new Lua command ("simExtSkeleton_getData")
    int stack=p->stackID;
    // we are expecting following as input:
    // struct.int32Data (int32)
    // struct.floatData (float)
    // struct.stringData (string)
    // struct.int32Array (array containing at least 2 int32)

    // Print the stack content:
    simDebugStack(stack,-1);

    bool success=false;
    if (simGetStackSize(stack)>=1)
    { // we have at least one arg. 
        
        // We discard the other arguments:
        if (simGetStackSize(stack)>1)
            simPopStackItem(stack,simGetStackSize(stack)-1);

        // Do we have a map-like struct as arg1?
        if (simGetStackTableInfo(stack,0)==sim_stack_table_map)
        { // yes
            // Now let's examine the struct content:
            simUnfoldStackTable(stack); // this removes the table and pushes its content onto the stack

            // Now the stack should contain 4 (or more) pairs of key-values:
            if (simGetStackSize(stack)>=2*4)
            { // ok, we have at least 4 key-value pairs
                int int32Data;
                float floatData;
                std::string stringData;
                int int32Array[2];
                int alreadyDone=0; // bit-coded: what was already read (1=intData, 2=floatData, 4=stringData, 8=int32Array
                while (simGetStackSize(stack)>0)
                {
                    // move the key of the last entry to the table top:
                    simMoveStackItemToTop(stack,simGetStackSize(stack)-2);
                    // what is the key?
                    int stringLength;
                    char* _key=simGetStackStringValue(stack,&stringLength);
                    if (_key!=NULL)
                    {
                        std::string key(_key);
                        simReleaseBuffer(_key);
                        if (key.compare("int32Data")==0)
                        {
                            simPopStackItem(stack,1); // pop the key
                            if (simGetStackInt32Value(stack,&int32Data)==1)
                                alreadyDone|=1;
                            else
                            {
                                simSetLastError(LUA_GETDATA_COMMAND,"Invalid type for 'int32Data' key of argument 1.");
                                break;
                            }
                            simPopStackItem(stack,1); // pop the value
                        }
                        else if (key.compare("floatData")==0)
                        {
                            simPopStackItem(stack,1); // pop the key
                            if (simGetStackFloatValue(stack,&floatData)==1)
                                alreadyDone|=2;
                            else
                            {
                                simSetLastError(LUA_GETDATA_COMMAND,"Invalid type for 'floatData' key of argument 1.");
                                break;
                            }
                            simPopStackItem(stack,1); // pop the value
                        }
                        else if (key.compare("stringData")==0)
                        {
                            simPopStackItem(stack,1); // pop the key
                            _key=simGetStackStringValue(stack,&stringLength);
                            if (_key!=NULL)
                            {
                                alreadyDone|=4;
                                stringData.assign(_key,stringLength);
                                simReleaseBuffer(_key);
                            }
                            else
                            {
                                simSetLastError(LUA_GETDATA_COMMAND,"Invalid type for 'stringData' key of argument 1.");
                                break;
                            }
                            simPopStackItem(stack,1); // pop the value
                        }
                        else if (key.compare("int32Array")==0)
                        {
                            simPopStackItem(stack,1); // pop the key
                            if (simGetStackTableInfo(stack,0)>=2)
                            {
                                if (simGetStackInt32Table(stack,int32Array,2)==1)
                                    alreadyDone|=8;
                                else
                                {
                                    simSetLastError(LUA_GETDATA_COMMAND,"Invalid array content for 'int32Array' key of argument 1.");
                                    break;
                                }
                            }
                            else
                            {
                                simSetLastError(LUA_GETDATA_COMMAND,"Invalid type/size for 'int32Array' key of argument 1.");
                                break;
                            }
                            simPopStackItem(stack,1); // pop the table array
                        }
                        else
                            simPopStackItem(stack,2); // pop the key+value (unknown data)
                    }
                    else
                    {
                        simSetLastError(LUA_GETDATA_COMMAND,"Invalid argument 1.");
                        break;
                    }
                }
                success=(alreadyDone==1+2+4+8);
            }
            else
                simSetLastError(LUA_GETDATA_COMMAND,"Invalid argument 1.");
        }
        else
            simSetLastError(LUA_GETDATA_COMMAND,"Invalid argument 1.");
    }
    else
        simSetLastError(LUA_GETDATA_COMMAND,"Not enough arguments.");

    // Now clear the stack (maybe it is already cleared):
    simPopStackItem(stack,0);

    if (success)
    {
        // In case of success, we return:
        // struct.text (string)
        // struct.floatArray (array containing 3 float)
        simPushTableOntoStack(stack);
        simPushStringOntoStack(stack,"text",0); // we push the key
        simPushStringOntoStack(stack,"Hello world!",0); // we push the text
        simInsertDataIntoStackTable(stack); // we insert above key-value pair into the table
        float floatArray[]={1.0,2.0,3.0};
        simPushStringOntoStack(stack,"floatArray",0); // we push the key
        simPushFloatTableOntoStack(stack,floatArray,3); // we push the array
        simInsertDataIntoStackTable(stack); // we insert above key-value pair into the table
    }
}
// --------------------------------------------------------------------------------------


// This is the plugin start routine (called just once, just after the plugin was loaded):
VREP_DLLEXPORT unsigned char v_repStart(void* reservedPointer,int reservedInt)
{
    // Dynamically load and bind V-REP functions:
    // ******************************************
    // 1. Figure out this plugin's directory:
    char curDirAndFile[1024];
#ifdef _WIN32
    #ifdef QT_COMPIL
        _getcwd(curDirAndFile, sizeof(curDirAndFile));
    #else
        GetModuleFileName(NULL,curDirAndFile,1023);
        PathRemoveFileSpec(curDirAndFile);
    #endif
#elif defined (__linux) || defined (__APPLE__)
    getcwd(curDirAndFile, sizeof(curDirAndFile));
#endif

    std::string currentDirAndPath(curDirAndFile);
    // 2. Append the V-REP library's name:
    std::string temp(currentDirAndPath);
#ifdef _WIN32
    temp+="\\v_rep.dll";
#elif defined (__linux)
    temp+="/libv_rep.so";
#elif defined (__APPLE__)
    temp+="/libv_rep.dylib";
#endif /* __linux || __APPLE__ */
    // 3. Load the V-REP library:
    vrepLib=loadVrepLibrary(temp.c_str());
    if (vrepLib==NULL)
    {
        std::cout << "Error, could not find or correctly load the V-REP library. Cannot start 'PluginSkeleton' plugin.\n";
        return(0); // Means error, V-REP will unload this plugin
    }
    if (getVrepProcAddresses(vrepLib)==0)
    {
        std::cout << "Error, could not find all required functions in the V-REP library. Cannot start 'PluginSkeleton' plugin.\n";
        unloadVrepLibrary(vrepLib);
        return(0); // Means error, V-REP will unload this plugin
    }
    // ******************************************

    // Check the version of V-REP:
    // ******************************************
    int vrepVer;
    simGetIntegerParameter(sim_intparam_program_version,&vrepVer);
    if (vrepVer<30200) // if V-REP version is smaller than 3.02.00
    {
        std::cout << "Sorry, your V-REP copy is somewhat old. Cannot start 'PluginSkeleton' plugin.\n";
        unloadVrepLibrary(vrepLib);
        return(0); // Means error, V-REP will unload this plugin
    }
    // ******************************************

    std::vector<int> inArgs;

    // Register the new Lua command "simExtSkeleton_getSensorData":
    simRegisterScriptCallbackFunction(strConCat(LUA_GETSENSORDATA_COMMAND,"@","PluginSkeleton"),strConCat("number result,table data,number distance=",LUA_GETSENSORDATA_COMMAND,"(number sensorIndex,table_3 floatParameters,table_2 intParameters)"),LUA_GETSENSORDATA_CALLBACK);

    // Register the new Lua command "simExtSkeleton_getData":
    simRegisterScriptCallbackFunction(strConCat(LUA_GETDATA_COMMAND,"@","PluginSkeleton"),strConCat("struct returnData=",LUA_GETDATA_COMMAND,"(struct inputData)"),LUA_GETDATA_CALLBACK);

    return(PLUGIN_VERSION); // initialization went fine, we return the version number of this plugin (can be queried with simGetModuleName)
}

// This is the plugin end routine (called just once, when V-REP is ending, i.e. releasing this plugin):
VREP_DLLEXPORT void v_repEnd()
{
    // Here you could handle various clean-up tasks

    unloadVrepLibrary(vrepLib); // release the library
}

// This is the plugin messaging routine (i.e. V-REP calls this function very often, with various messages):
VREP_DLLEXPORT void* v_repMessage(int message,int* auxiliaryData,void* customData,int* replyData)
{ // This is called quite often. Just watch out for messages/events you want to handle
    // Keep following 5 lines at the beginning and unchanged:
    static bool refreshDlgFlag=true;
    int errorModeSaved;
    simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
    simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);
    void* retVal=NULL;

    // Here we can intercept many messages from V-REP (actually callbacks). Only the most important messages are listed here.
    // For a complete list of messages that you can intercept/react with, search for "sim_message_eventcallback"-type constants
    // in the V-REP user manual.

    if (message==sim_message_eventcallback_refreshdialogs)
        refreshDlgFlag=true; // V-REP dialogs were refreshed. Maybe a good idea to refresh this plugin's dialog too

    if (message==sim_message_eventcallback_menuitemselected)
    { // A custom menu bar entry was selected..
        // here you could make a plugin's main dialog visible/invisible
    }

    if (message==sim_message_eventcallback_instancepass)
    {   // This message is sent each time the scene was rendered (well, shortly after) (very often)
        // It is important to always correctly react to events in V-REP. This message is the most convenient way to do so:

        int flags=auxiliaryData[0];
        bool sceneContentChanged=((flags&(1+2+4+8+16+32+64+256))!=0); // object erased, created, model or scene loaded, und/redo called, instance switched, or object scaled since last sim_message_eventcallback_instancepass message 
        bool instanceSwitched=((flags&64)!=0);

        if (instanceSwitched)
        {
            // React to an instance switch here!!
        }

        if (sceneContentChanged)
        { // we actualize plugin objects for changes in the scene

            //...

            refreshDlgFlag=true; // always a good idea to trigger a refresh of this plugin's dialog here
        }
    }

    if (message==sim_message_eventcallback_mainscriptabouttobecalled)
    { // The main script is about to be run (only called while a simulation is running (and not paused!))
        
    }

    if (message==sim_message_eventcallback_simulationabouttostart)
    { // Simulation is about to start

    }

    if (message==sim_message_eventcallback_simulationended)
    { // Simulation just ended

    }

    if (message==sim_message_eventcallback_moduleopen)
    { // A script called simOpenModule (by default the main script). Is only called during simulation.
        if ( (customData==NULL)||(_stricmp("PluginSkeleton",(char*)customData)==0) ) // is the command also meant for this plugin?
        {
            // we arrive here only at the beginning of a simulation
        }
    }

    if (message==sim_message_eventcallback_modulehandle)
    { // A script called simHandleModule (by default the main script). Is only called during simulation.
        if ( (customData==NULL)||(_stricmp("PluginSkeleton",(char*)customData)==0) ) // is the command also meant for this plugin?
        {
            // we arrive here only while a simulation is running
        }
    }

    if (message==sim_message_eventcallback_moduleclose)
    { // A script called simCloseModule (by default the main script). Is only called during simulation.
        if ( (customData==NULL)||(_stricmp("PluginSkeleton",(char*)customData)==0) ) // is the command also meant for this plugin?
        {
            // we arrive here only at the end of a simulation
        }
    }

    if (message==sim_message_eventcallback_instanceswitch)
    { // We switched to a different scene. Such a switch can only happen while simulation is not running

    }

    if (message==sim_message_eventcallback_broadcast)
    { // Here we have a plugin that is broadcasting data (the broadcaster will also receive this data!)

    }

    if (message==sim_message_eventcallback_scenesave)
    { // The scene is about to be saved. If required do some processing here (e.g. add custom scene data to be serialized with the scene)

    }

    // You can add many more messages to handle here

    if ((message==sim_message_eventcallback_guipass)&&refreshDlgFlag)
    { // handle refresh of the plugin's dialogs
        // ...
        refreshDlgFlag=false;
    }

    // Keep following unchanged:
    simSetIntegerParameter(sim_intparam_error_report_mode,errorModeSaved); // restore previous settings
    return(retVal);
}

