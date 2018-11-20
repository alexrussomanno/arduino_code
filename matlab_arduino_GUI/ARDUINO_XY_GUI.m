function varargout = ARDUINO_XY_GUI(varargin)
% ARDUINO_XY_GUI MATLAB code for ARDUINO_XY_GUI.fig
%      ARDUINO_XY_GUI, by itself, creates a new ARDUINO_XY_GUI or raises the existing
%      singleton*.
%
%      H = ARDUINO_XY_GUI returns the handle to a new ARDUINO_XY_GUI or the handle to
%      the existing singleton*.
%
%      ARDUINO_XY_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ARDUINO_XY_GUI.M with the given input arguments.
%
%      ARDUINO_XY_GUI('Property','Value',...) creates a new ARDUINO_XY_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before ARDUINO_XY_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to ARDUINO_XY_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help ARDUINO_XY_GUI

% Last Modified by GUIDE v2.5 20-Feb-2018 16:16:05

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @ARDUINO_XY_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @ARDUINO_XY_GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before ARDUINO_XY_GUI is made visible.
function ARDUINO_XY_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to ARDUINO_XY_GUI (see VARARGIN)

% Choose default command line output for ARDUINO_XY_GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);
delete(instrfind({'port'},{'COM70'}));
clear comport; clc; 
global comport lin_slope lin_yint lin_slope2 lin_yint2
comport = serial('COM70', 'BaudRate', 57600);    % setup comport
fopen(comport);
% lin_slope =0.121277;
% lin_yint =-12.6769321;
% lin_slope2 = 0.036745736;
% lin_yint2 = -3.848235661;

lin_slope =0.122396557;
lin_yint =-12.32408416;
lin_slope2 = 0.037207304;
lin_yint2 = -3.773052632;
% UIWAIT makes ARDUINO_XY_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = ARDUINO_XY_GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in btnGo.
function btnGo_Callback(hObject, eventdata, handles)
% hObject    handle to btnGo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global comport lin_slope lin_yint lin_slope2 lin_yint2

handles.valveChange=0;
handles.valve_toggle=0;
guidata(hObject,handles)
x=1;
num_gages=6;

gage_reading=zeros(num_gages);
gage_type=[1 1 1 1 1 2];
% cc=hsv(10);
cc=parula(num_gages);
cla(handles.axes1)
axes(handles.axes1)
gage_plot=gobjects(num_gages,1);
lab=gobjects(num_gages,1);
for i=1:num_gages-2
    gage_plot(i) = line(nan, nan,'color',cc(i,:));
    lab(i)=text(nan,nan,'');
end
grid on;
ylabel('Pressure (psi)')
axis([1 7 0 20])

cla(handles.axes2)
axes(handles.axes2)
gage_plot(5) = line(nan, nan,'color',cc(i,:));
lab(5)=text(nan,nan,'');
grid on
ylabel('Pressure (psi)')
title('P5');
axis([1 7 0 45])

cla(handles.axes3)
axes(handles.axes3)
gage_plot(6) = line(nan, nan,'color',cc(i,:));
lab(6)=text(nan,nan,'');
grid on
ylabel('Pressure (psi)')
title('P6');
axis([1 7 0 45])

while x < Inf
    if x==1
        fwrite(comport,0,'uint8');
        set(handles.btnStop, 'userdata', 0);    
    else
        if get(handles.valveChange,'userdata')
            fwrite(comport,get(handles.valve_toggle,'userdata'),'uint8')
            set(handles.valveChange,'userdata',0)
        else
            fwrite(comport,0,'uint8')
        end
    end
    for j=1:num_gages
        if gage_type(j)==1
            gage_reading(j)=fread(comport,1,'uint16')*lin_slope+lin_yint;
        elseif gage_type(j)==2
            gage_reading(j)=fread(comport,1,'uint16')*lin_slope2+lin_yint2; 
        end
    end
    x=x+1;
    
    hold on;
    for j=1:6        
        set(gage_plot(j), 'XData', 1:7, 'YData', gage_reading(j)*ones(1,7));
        set(lab(j),'position',[7 gage_reading(j),0],'string',num2str(j));
        set(handles.(['text' num2str(j)]), 'string', ['P' num2str(j) '=' num2str(round(gage_reading(j),1)) ' psi'])
        set(handles.(['text' num2str(j)]), 'fontsize', 12,'horizontalAlignment', 'left');
    end
    
%     for j=1:6
%         set(handles.(['text' num2str(j)]), 'string', ['P' num2str(j) '=' num2str(round(gage_reading(5),1)) ' psi'])
%         set(handles.(['text' num2str(j)]), 'fontsize', 12,'horizontalAlignment', 'left');
%     end
    
    pause(.001);
    
    hold off;
    drawnow;
    if get(handles.btnStop, 'userdata') % stop condition
		fwrite(comport,100,'uint8');
        fclose(instrfindall);
        break;
	end
end

% --- Executes on button press in btnStop.
function btnStop_Callback(hObject, eventdata, handles)
% hObject    handle to btnStop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.btnStop,'userdata',1)

% --- Executes on button press in btnStop2.
function btnStop2_Callback(hObject, eventdata, handles)
% hObject    handle to btnStop2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.btnStop,'userdata',1)

% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes2


% --- Executes on button press in valve1.
function valve1_Callback(hObject, eventdata, handles)
% hObject    handle to valve1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% set(handles.btnStop,'userdata',1)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',1)

% Hint: get(hObject,'Value') returns toggle state of valve1


% --- Executes on button press in valve2.
function valve2_Callback(hObject, eventdata, handles)
% hObject    handle to valve2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',2)
% Hint: get(hObject,'Value') returns toggle state of valve2


% --- Executes on button press in valve3.
function valve3_Callback(hObject, eventdata, handles)
% hObject    handle to valve3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',3)
% Hint: get(hObject,'Value') returns toggle state of valve3


% --- Executes on button press in valve4.
function valve4_Callback(hObject, eventdata, handles)
% hObject    handle to valve4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',4)
% Hint: get(hObject,'Value') returns toggle state of valve4

% --- Executes during object deletion, before destroying properties.
function axes1_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes during object deletion, before destroying properties.
function axes2_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in valve5.
function valve5_Callback(hObject, eventdata, handles)
% hObject    handle to valve5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',5)
% Hint: get(hObject,'Value') returns toggle state of valve5


% --- Executes on button press in valve6.
function valve6_Callback(hObject, eventdata, handles)
% hObject    handle to valve6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',6)
% Hint: get(hObject,'Value') returns toggle state of valve6

% --- Executes on button press in valve7.
function valve7_Callback(hObject, eventdata, handles)
% hObject    handle to valve7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',7)
% Hint: get(hObject,'Value') returns toggle state of valve7

% --- Executes on button press in valve8.
function valve8_Callback(hObject, eventdata, handles)
% hObject    handle to valve8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',8)
% Hint: get(hObject,'Value') returns toggle state of valve8


% --- Executes on button press in togglebutton9.
function togglebutton9_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',9)
% Hint: get(hObject,'Value') returns toggle state of togglebutton9


% --- Executes on button press in togglebutton10.
function togglebutton10_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',10)
% Hint: get(hObject,'Value') returns toggle state of togglebutton10


% --- Executes on button press in togglebutton11.
function togglebutton11_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',11)
% Hint: get(hObject,'Value') returns toggle state of togglebutton11


% --- Executes on button press in togglebutton12.
function togglebutton12_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',12)
% Hint: get(hObject,'Value') returns toggle state of togglebutton12


% --- Executes on button press in togglebutton13.
function togglebutton13_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',13)
% Hint: get(hObject,'Value') returns toggle state of togglebutton13


% --- Executes on button press in togglebutton14.
function togglebutton14_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',14)
% Hint: get(hObject,'Value') returns toggle state of togglebutton14


% --- Executes on button press in togglebutton15.
function togglebutton15_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',15)
% Hint: get(hObject,'Value') returns toggle state of togglebutton15


% --- Executes on button press in togglebutton16.
function togglebutton16_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',16)
% Hint: get(hObject,'Value') returns toggle state of togglebutton16


% --- Executes on button press in togglebutton17.
function togglebutton17_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',17)
% Hint: get(hObject,'Value') returns toggle state of togglebutton17


% --- Executes on button press in togglebutton18.
function togglebutton18_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton18 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',18)
% Hint: get(hObject,'Value') returns toggle state of togglebutton18
