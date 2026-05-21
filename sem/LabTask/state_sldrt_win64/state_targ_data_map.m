  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (state_P)
    ;%
      section.nData     = 15;
      section.data(15)  = dumData; %prealloc
      
	  ;% state_P.A_down
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% state_P.A_up
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 16;
	
	  ;% state_P.K_I_down
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 32;
	
	  ;% state_P.K_I_up
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 33;
	
	  ;% state_P.K_new_down
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 34;
	
	  ;% state_P.K_new_up
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 38;
	
	  ;% state_P.AnalogOutput_FinalValue
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 42;
	
	  ;% state_P.AnalogOutput_InitialValue
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 43;
	
	  ;% state_P.EncoderInput_InputFilter
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 44;
	
	  ;% state_P.EncoderInput_MaxMissedTicks
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 45;
	
	  ;% state_P.AnalogOutput_MaxMissedTicks
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 46;
	
	  ;% state_P.DigitalInput_MaxMissedTicks
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 47;
	
	  ;% state_P.EncoderInput_YieldWhenWaiting
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 48;
	
	  ;% state_P.AnalogOutput_YieldWhenWaiting
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 49;
	
	  ;% state_P.DigitalInput_YieldWhenWaiting
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 50;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% state_P.DigitalInput_BitMode
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% state_P.EncoderInput_Channels
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 1;
	
	  ;% state_P.AnalogOutput_Channels
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 3;
	
	  ;% state_P.DigitalInput_Channels
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 4;
	
	  ;% state_P.AnalogOutput_RangeMode
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 5;
	
	  ;% state_P.AnalogOutput_VoltRange
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% state_P.Constant1_Value
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
	  ;% state_P.Constant_Value
	  section.data(2).logicalSrcIdx = 22;
	  section.data(2).dtTransOffset = 1;
	
	  ;% state_P.Integrator1_IC
	  section.data(3).logicalSrcIdx = 23;
	  section.data(3).dtTransOffset = 2;
	
	  ;% state_P.StateSpace_B
	  section.data(4).logicalSrcIdx = 24;
	  section.data(4).dtTransOffset = 3;
	
	  ;% state_P.StateSpace_C
	  section.data(5).logicalSrcIdx = 25;
	  section.data(5).dtTransOffset = 15;
	
	  ;% state_P.StateSpace_InitialCondition
	  section.data(6).logicalSrcIdx = 26;
	  section.data(6).dtTransOffset = 31;
	
	  ;% state_P.StateSpace1_B
	  section.data(7).logicalSrcIdx = 27;
	  section.data(7).dtTransOffset = 32;
	
	  ;% state_P.StateSpace1_C
	  section.data(8).logicalSrcIdx = 28;
	  section.data(8).dtTransOffset = 44;
	
	  ;% state_P.StateSpace1_InitialCondition
	  section.data(9).logicalSrcIdx = 29;
	  section.data(9).dtTransOffset = 60;
	
	  ;% state_P.Saturation_UpperSat
	  section.data(10).logicalSrcIdx = 30;
	  section.data(10).dtTransOffset = 61;
	
	  ;% state_P.Saturation_LowerSat
	  section.data(11).logicalSrcIdx = 31;
	  section.data(11).dtTransOffset = 62;
	
	  ;% state_P.Positionconversion_Gain
	  section.data(12).logicalSrcIdx = 32;
	  section.data(12).dtTransOffset = 63;
	
	  ;% state_P.Rychlost_A
	  section.data(13).logicalSrcIdx = 33;
	  section.data(13).dtTransOffset = 64;
	
	  ;% state_P.Rychlost_C
	  section.data(14).logicalSrcIdx = 34;
	  section.data(14).dtTransOffset = 65;
	
	  ;% state_P.Rychlost_D
	  section.data(15).logicalSrcIdx = 35;
	  section.data(15).dtTransOffset = 66;
	
	  ;% state_P.Angleconversion_Gain
	  section.data(16).logicalSrcIdx = 36;
	  section.data(16).dtTransOffset = 67;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% state_P.ManualSwitch_CurrentSetting
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
	  ;% state_P.ManualSwitch3_CurrentSetting
	  section.data(2).logicalSrcIdx = 38;
	  section.data(2).dtTransOffset = 1;
	
	  ;% state_P.ManualSwitch1_CurrentSetting
	  section.data(3).logicalSrcIdx = 39;
	  section.data(3).dtTransOffset = 2;
	
	  ;% state_P.ManualSwitch2_CurrentSetting
	  section.data(4).logicalSrcIdx = 40;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (state_B)
    ;%
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% state_B.MotorVoltage
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% state_B.Positionconversion
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% state_B.Speed
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% state_B.Angleconversion
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% state_B.Sum1
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% state_B.TmpSignalConversionAtStateSpaceInport1
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 1;
    sectIdxOffset = 1;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (state_DW)
    ;%
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% state_DW.EncoderInput_PWORK
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% state_DW.Scope_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% state_DW.angle_PWORK.LoggedData
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% state_DW.motorvoltage_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% state_DW.position_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% state_DW.AnalogOutput_PWORK
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% state_DW.DigitalInput_PWORK
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2400066694;
  targMap.checksum1 = 1656031503;
  targMap.checksum2 = 1888843413;
  targMap.checksum3 = 3692017894;

