function varargout = ARDUINO_GUI_v2(varargin)
% ARDUINO_GUI_v2 MATLAB code for ARDUINO_GUI_v2.fig
%      ARDUINO_GUI_v2, by itself, creates a new ARDUINO_GUI_v2 or raises the existing
%      singleton*.
%
%      H = ARDUINO_GUI_v2 returns the handle to a new ARDUINO_GUI_v2 or the handle to
%      the existing singleton*.
%
%      ARDUINO_GUI_v2('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ARDUINO_GUI_v2.M with the given input arguments.
%
%      ARDUINO_GUI_v2('Property','Value',...) creates a new ARDUINO_GUI_v2 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before ARDUINO_GUI_v2_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to ARDUINO_GUI_v2_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help ARDUINO_GUI_v2

% Last Modified by GUIDE v2.5 16-Nov-2018 17:20:34

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @ARDUINO_GUI_v2_OpeningFcn, ...
                   'gui_OutputFcn',  @ARDUINO_GUI_v2_OutputFcn, ...
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


% --- Executes just before ARDUINO_GUI_v2 is made visible.
function ARDUINO_GUI_v2_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to ARDUINO_GUI_v2 (see VARARGIN)

% Choose default command line output for ARDUINO_GUI_v2
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
% UIWAIT makes ARDUINO_GUI_v2 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = ARDUINO_GUI_v2_OutputFcn(hObject, eventdata, handles) 
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
% fopen(comport);

handles.valveChange=0;
handles.valve_toggle=0;
handles.sliderValue=0;

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
    fwrite(comport,floor(get(handles.sliderValue,'userdata')),'uint8')
    
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
    set(handles.text11,'string',[num2str(get(handles.sliderValue,'userdata'))]) 
    
%     for j=1:6
%         set(handles.(['text' num2str(j)]), 'string', ['P' num2str(j) '=' num2str(round(gage_reading(5),1)) ' psi'])
%         set(handles.(['text' num2str(j)]), 'fontsize', 12,'horizontalAlignment', 'left');
%     end
    
    pause(.001);
    
    hold off;
    drawnow;
    if get(handles.btnStop, 'userdata') % stop condition
		fwrite(comport,9,'uint8');
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
% 
% 
% % --- Executes on button press in valve3.
% function valve3_Callback(hObject, eventdata, handles)
% % hObject    handle to valve3 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% set(handles.valveChange,'userdata',1)
% set(handles.valve_toggle,'userdata',3)
% % Hint: get(hObject,'Value') returns toggle state of valve3
% 
% 
% % --- Executes on button press in valve4.
% function valve4_Callback(hObject, eventdata, handles)
% % hObject    handle to valve4 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% set(handles.valveChange,'userdata',1)
% set(handles.valve_toggle,'userdata',4)
% % Hint: get(hObject,'Value') returns toggle state of valve4

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

% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% set(handles.sliderValue,'userdata',get(hObject,'Value'));
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% % --- Executes on button press in valve5.
% function valve5_Callback(hObject, eventdata, handles)
% % hObject    handle to valve5 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% set(handles.valveChange,'userdata',1)
% set(handles.valve_toggle,'userdata',5)
% % Hint: get(hObject,'Value') returns toggle state of valve5
% 
% 
% % --- Executes on button press in valve6.
% function valve6_Callback(hObject, eventdata, handles)
% % hObject    handle to valve6 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% set(handles.valveChange,'userdata',1)
% set(handles.valve_toggle,'userdata',6)
% % Hint: get(hObject,'Value') returns toggle state of valve6
% 
% % --- Executes on button press in valve7.
% function valve7_Callback(hObject, eventdata, handles)
% % hObject    handle to valve7 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% set(handles.valveChange,'userdata',1)
% set(handles.valve_toggle,'userdata',7)
% % Hint: get(hObject,'Value') returns toggle state of valve7
% 
% % --- Executes on button press in valve8.
% function valve8_Callback(hObject, eventdata, handles)
% % hObject    handle to valve8 (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% set(handles.valveChange,'userdata',1)
% set(handles.valve_toggle,'userdata',8)
% % Hint: get(hObject,'Value') returns toggle state of valve8


% --- Executes on button press in checkbox1.
function checkbox1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',1)
% Hint: get(hObject,'Value') returns toggle state of checkbox1


% --- Executes on button press in checkbox2.
function checkbox2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.valveChange,'userdata',1)
set(handles.valve_toggle,'userdata',2)
% Hint: get(hObject,'Value') returns toggle state of checkbox2


% --- Executes on button press in checkbox3.
function checkbox3_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox3


% --- Executes on button press in checkbox4.
function checkbox4_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox4


% --- Executes on button press in checkbox5.
function checkbox5_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox5


% --- Executes on button press in checkbox6.
function checkbox6_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox6


% --- Executes on button press in checkbox7.
function checkbox7_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox7


% --- Executes on button press in checkbox8.
function checkbox8_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox8


% --- Executes on slider movement.
function slider3_Callback(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
slider_value=get(hObject,'Value');
set(handles.sliderValue,'userdata',slider_value);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
