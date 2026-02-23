
function pendulum_msfcn(block)

setup(block);

%endfunction

%% Function: setup ===================================================
function setup(block)

% Register number of ports
block.NumInputPorts  = 1;
block.NumOutputPorts = 2;

% Setup port properties to be inherited or dynamic
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

% Override input port properties
block.InputPort(1).Dimensions        = 1;
block.InputPort(1).DirectFeedthrough = false;

% Override output port properties
block.OutputPort(1).Dimensions       = 1;
block.OutputPort(2).Dimensions       = 1;

% Register parameters
block.NumDialogPrms     = 4;

% Setup number of continuous states
block.NumContStates     = 4;

% Register sample times
%  [0 offset]            : Continuous sample time
%  [positive_num offset] : Discrete sample time
%
%  [-1, 0]               : Inherited sample time
%  [-2, 0]               : Variable sample time
block.SampleTimes = [0 0];

% Specify the block simStateCompliance. The allowed values are:
%    'UnknownSimState', < The default setting; warn and assume DefaultSimState
%    'DefaultSimState', < Same sim state as a built-in block
%    'HasNoSimState',   < No sim state
%    'CustomSimState',  < Has GetSimState and SetSimState methods
%    'DisallowSimState' < Error out when saving or restoring the model sim state
block.SimStateCompliance = 'DefaultSimState';

block.RegBlockMethod('CheckParameters', @CheckPrms);
block.RegBlockMethod('SetInputPortSamplingMode', @SetInpPortFrameData);
block.RegBlockMethod('SetInputPortDimensions', @SetInpPortDims);
block.RegBlockMethod('InitializeConditions', @InitializeConditions);
block.RegBlockMethod('Outputs', @Outputs);     % Required
block.RegBlockMethod('Derivatives', @Derivatives);
block.RegBlockMethod('Terminate', @Terminate); % Required
% block.RegBlockMethod('SetInputPortSamplingMode',@SetInputPortSamplingMode);

%end setup

function SetInpPortFrameData(block, idx, fd)
  
  block.InputPort(idx).SamplingMode = fd;
  block.OutputPort(1).SamplingMode  = fd;
  block.OutputPort(2).SamplingMode  = fd;
  
%endfunction

function SetInpPortDims(block, idx, di)
  
  block.InputPort(idx).Dimensions = di;
%   block.OutputPort(1).Dimensions  = di;
%   block.OutputPort(2).Dimensions  = di;

%endfunction

%endfunction;

function CheckPrms(block)
  
%parameters: x0, phi0
  x0 = block.DialogPrm(1).Data;
  if ~strcmp(class(x0), 'double')
    me = MSLException(block.BlockHandle, message('Simulink:blocks:invalidParameter'));
    throw(me);
  end
  if abs(x0) > 0.91
      error('Initial cart position ''x(0)'' out of bounds');
  end;
  
  phi0 = block.DialogPrm(2).Data;
  if ~strcmp(class(phi0), 'double')
    me = MSLException(block.BlockHandle, message('Simulink:blocks:invalidParameter'));
    throw(me);
  end
  
  
%endfunction

function InitializeConditions(block)

% states: v,y,w,phi
 block.ContStates.Data(2) = block.DialogPrm(1).Data;
 block.ContStates.Data(4) = block.DialogPrm(2).Data * pi/180;

%end InitializeConditions


function Outputs(block)

% states: v,y,w,phi
block.OutputPort(1).Data = block.ContStates.Data(2);
block.OutputPort(2).Data = block.ContStates.Data(4) * 180 / pi;

%end Outputs

function Derivatives(block)
    

     % constants
     g = 9.80665; %[m/s^2]
     M = 0.5; %[kg] cart mass
     rail_half_length = 0.91; %[m] 1/2 rail length
     m = 0.275; %[kg] pendulum mass
     l = 0.1; %[m] pendulum length
     b = 0.21; %[] friction constant of the cart
     dlt = 0.0028; %[] friction constatn of the pivot
     kf = 0.1; %[N/V] input voltage to force ration
     J = m*l^2/3; %[kg/m^2] pendulum moment of inertia (rod of length L)
     u_max = 10; %[V] maximal input value
     u_ins = 0.2;% [V] input insensitivity
     
     % lumped constants
     k1 = m*(l/2)/(M+m);
     kb = b/(M+m);
     ku = kf/(M+m);
     k2 = m*g*(l/2)/J;
     k3 = m*(l/2)/J;
     kd = 2*dlt/J;

     % current state     
     v = block.ContStates.Data(1);
     y = block.ContStates.Data(2);
     w = block.ContStates.Data(3);
     phi = block.ContStates.Data(4);     
     u =  block.InputPort(1).Data;
     obey_rail_bounds = block.DialogPrm(3).Data;
     cart_lock = block.DialogPrm(4).Data;
     
     if abs(u) >= u_max
         u = sign(u)*u_max;
     elseif abs(u) <= u_ins 
         u = 0;         
     end
     
     % states: v,y,w,phi
     if (cart_lock)
       block.Derivatives.Data(1) = 0;
       block.Derivatives.Data(2) = 0;
       block.ContStates.Data(1) = 0; % v
       u = 0; 
     else       
          dv = (k1*sin(phi)*(kd*w + k2*cos(phi)))/(k1*k3*sin(phi)^2 - 1) - (k1*cos(phi)*w^2 + ku*u - kb*v)/(k1*k3*sin(phi)^2 - 1);
          
         if obey_rail_bounds && (abs(y) >= rail_half_length) && (sign(y) == sign(v))           
             block.Derivatives.Data(1) = -300*v; % dv
             v = 0;
             u = 0; % sum of the forces to the cart are 0;
         else
             block.Derivatives.Data(1) = dv;
         end
         
         block.Derivatives.Data(2) = v; % dy
     end
     
     block.Derivatives.Data(3) = (kd*w + k2*cos(phi))/(k1*k3*sin(phi)^2 - 1) - (k3*sin(phi)*(k1*cos(phi)*w^2 + ku*u - kb*v))/(k1*k3*sin(phi)^2 - 1);
     block.Derivatives.Data(4) = w; % dphi
%end Derivatives

function Terminate(block)

%end Terminate
