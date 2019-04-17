function varargout = FinalView(varargin)
addpath(genpath('..\model'));
addpath(genpath('..\helper'));

%FINALVIEW MATLAB code file for FinalView.fig
%      FINALVIEW, by itself, creates a new FINALVIEW or raises the existing
%      singleton*.
%
%      H = FINALVIEW returns the handle to a new FINALVIEW or the handle to
%      the existing singleton*.
%
%      FINALVIEW('Property','Value',...) creates a new FINALVIEW using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to FinalView_OpeningFcn.  This calling syntax produces a
%      warning when there is an existing singleton*.
%
%      FINALVIEW('CALLBACK') and FINALVIEW('CALLBACK',hObject,...) call the
%      local function named CALLBACK in FINALVIEW.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help FinalView

% Last Modified by GUIDE v2.5 18-May-2018 19:31:35

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @FinalView_OpeningFcn, ...
                   'gui_OutputFcn',  @FinalView_OutputFcn, ...
                   'gui_LayoutFcn',  [], ...
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


% --- Executes just before FinalView is made visible.
function FinalView_OpeningFcn(hObject, eventdata, handles, varargin)
global channel; global encoder; global decoder; global scrambler; global descrambler; global signal;
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for FinalView
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);
set(handles.BSCProbabilitySlider,'enable','off');
set(handles.BSCProbability,'enable','off');
set(handles.BitsPeriod,'enable','off');
set(handles.BitsToDesync,'enable','off');
set(handles.IdealChannelBtn,'value',1);
set(handles.ScramblingOption,'value',1);
set(handles.EncodeOption,'value',1);

signal = Signal();
channel = PerfectChannel();
scrambler = Scrambler();
descrambler = Descrambler();
encoder = Encoder();
decoder = DecoderEthernet();

% UIWAIT makes FinalView wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = FinalView_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in AboutBtn.
function AboutBtn_Callback(hObject, eventdata, handles)
% hObject    handle to AboutBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
uiawait(msgbox({'NiDUC 2 project: Scrambling';'';'Signal transmission simulator';'Available channels: BSC, Custom, Ideal(default)';'';'Available modes: no modification, Scrambling, Encoding, Scrambling+Encoding(default)'}, 'About', 'modal'));


% --- Executes on slider movement.
function BSCProbabilitySlider_Callback(hObject, eventdata, handles)
% hObject    handle to BSCProbabilitySlider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.BSCProbability, 'String', num2str(round(get(handles.BSCProbabilitySlider, 'Value'),2)));
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function BSCProbabilitySlider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to BSCProbabilitySlider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function BitsPeriod_Callback(hObject, eventdata, handles)
% hObject    handle to BitsPeriod (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of BitsPeriod as text
%        str2double(get(hObject,'String')) returns contents of BitsPeriod as a double


% --- Executes during object creation, after setting all properties.
function BitsPeriod_CreateFcn(hObject, eventdata, handles)
% hObject    handle to BitsPeriod (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function BSCProbability_Callback(hObject, eventdata, handles)
% hObject    handle to BSCProbability (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if(str2double(get(handles.BSCProbability, 'String')) < 0 || isnan(str2double(get(handles.TrueProbability, 'String'))) || str2double(get(handles.BSCProbability, 'String')) == "")
    set(handles.BSCProbability, 'String', '0');
end
if(str2double(get(handles.BSCProbability, 'String')) > 1)
    set(handles.BSCProbability, 'String', '1');
end
set(handles.BSCProbabilitySlider, 'Value', str2double(get(handles.BSCProbability, 'String')));
% Hints: get(hObject,'String') returns contents of BSCProbability as text
%        str2double(get(hObject,'String')) returns contents of BSCProbability as a double


% --- Executes during object creation, after setting all properties.
function BSCProbability_CreateFcn(hObject, eventdata, handles)
% hObject    handle to BSCProbability (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function BitsToDesync_Callback(hObject, eventdata, handles)
% hObject    handle to BitsToDesync (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of BitsToDesync as text
%        str2double(get(hObject,'String')) returns contents of BitsToDesync as a double


% --- Executes during object creation, after setting all properties.
function BitsToDesync_CreateFcn(hObject, eventdata, handles)
% hObject    handle to BitsToDesync (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function TrueProbabilitySlider_Callback(hObject, eventdata, handles)
% hObject    handle to TrueProbabilitySlider (see GCBO)
% eventdata  reserved - to be defined in a future version of MALAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.TrueProbability, 'String', num2str(round(get(handles.TrueProbabilitySlider, 'Value'),2)));
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function TrueProbabilitySlider_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TrueProbabilitySlider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function TrueProbability_Callback(hObject, eventdata, handles)
% hObject    handle to TrueProbability (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if(str2double(get(handles.TrueProbability, 'String')) < 0 || isnan(str2double(get(handles.TrueProbability, 'String'))) || str2double(get(handles.TrueProbability, 'String')) == "")
    set(handles.TrueProbability, 'String', '0');
end
if(str2double(get(handles.TrueProbability, 'String')) > 1)
    set(handles.TrueProbability, 'String', '1');
end
set(handles.TrueProbabilitySlider, 'Value', str2double(get(handles.TrueProbability, 'String')));
% Hints: get(hObject,'String') returns contents of TrueProbability as text
%        str2double(get(hObject,'String')) returns contents of TrueProbability as a double


% --- Executes during object creation, after setting all properties.
function TrueProbability_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TrueProbability (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in GenerateBtn.
function GenerateBtn_Callback(hObject, eventdata, handles)
global frame; global signal; global probability; global signalGenerator;
% hObject    handle to GenerateBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA) 
if(get(handles.Frames, 'String') == "")
frame = 1;
else
frame = str2double(get(handles.Frames, 'String'));    
end
if(get(handles.TrueProbability, 'String') == "")
probability = 0.5;
else
probability = str2double(get(handles.TrueProbability, 'String'));
end
signalGenerator = SignalGenerator(frame, probability);
signal = signalGenerator.generateSignal(); 

set(handles.GeneratedSignal, 'String', signal.toString());
set(handles.ScrambledSignal, 'String', '');
set(handles.EncodedSignal, 'String', '');
set(handles.ReceivedSignal, 'String', '');
set(handles.DecodedSignal, 'String', '');
set(handles.DescrambledSignal, 'String', '');


function Frames_Callback(hObject, eventdata, handles)
% hObject    handle to Frames (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if(str2double(get(handles.Frames, 'String')) <= 0 || isnan(str2double(get(handles.TrueProbability, 'String'))))
    set(handles.Frames, 'String', '1');
end
% Hints: get(hObject,'String') returns contents of Frames as text
%        str2double(get(hObject,'String')) returns contents of Frames as a double


% --- Executes during object creation, after setting all properties.
function Frames_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Frames (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in SendBtn.
function SendBtn_Callback(hObject, eventdata, handles)
global channel; global signal; global scrambler; global encoder; global decoder; global descrambler; global signalGenerator;

if(signal.getSize() == 0)
    signalGenerator = SignalGenerator(16, 0.5);
    signal = signalGenerator.generateSignal();
    set(handles.GeneratedSignal, 'String', signal.toString());
end

switch get(get(handles.ChannelPicker, 'SelectedObject'), 'Tag')
    case 'IdealChannelBtn'
        channel = PerfectChannel();
        if(get(handles.ScramblingOption,'value') && get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            set(handles.BERLabel, 'String', '0');
            %------SCRAMBLE
            copySignal = scrambler.scrambleSignal(copySignal);
            set(handles.ScrambledSignal, 'String', copySignal.toString());
            %------ENCODE
            copySignal = encoder.encode(copySignal);
            set(handles.EncodedSignal, 'String', copySignal.toString());
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            copySignal = decoder.decode(copySignal);
            set(handles.DecodedSignal, 'String', copySignal.toString());
            %------DESCRAMBLE
            copySignal = descrambler.descrambleSignal(copySignal);
            set(handles.DescrambledSignal, 'String', copySignal.toString());
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
            if(str2double(get(handles.BERLabel,'String')) > 0)
                SendBtn_Callback(hObject, eventdata, handles);
            end
        elseif (~get(handles.ScramblingOption,'value') && get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            set(handles.ScrambledSignal, 'String', '');
            %------ENCODE
            copySignal = encoder.encode(copySignal);
            set(handles.EncodedSignal, 'String', copySignal.toString());
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            copySignal = decoder.decode(copySignal);
            set(handles.DecodedSignal, 'String', copySignal.toString());
            %------DESCRAMBLE
            set(handles.DescrambledSignal, 'String', '');
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (get(handles.ScramblingOption,'value') && ~get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            copySignal = scrambler.scrambleSignal(copySignal);
            set(handles.ScrambledSignal, 'String', copySignal.toString());
            %------ENCODE
            set(handles.EncodedSignal, 'String', '');
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            set(handles.DecodedSignal, 'String', '');
            %------DESCRAMBLE
            copySignal = descrambler.descrambleSignal(copySignal);
            set(handles.DescrambledSignal, 'String', copySignal.toString());
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (~get(handles.ScramblingOption,'value') && ~get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            set(handles.ScrambledSignal, 'String', '');
            %------ENCODE
            set(handles.EncodedSignal, 'String', '');
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            set(handles.DecodedSignal, 'String', '');
            %------DESCRAMBLE
            set(handles.DescrambledSignal, 'String', '');
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        end
        
    case 'BSCBtn'
        channel = BSChannel(str2double(get(handles.BSCProbability,'String')));
        if(get(handles.ScramblingOption,'value') && get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            copySignal = scrambler.scrambleSignal(copySignal);
            set(handles.ScrambledSignal, 'String', copySignal.toString());
            %------ENCODE
            copySignal = encoder.encode(copySignal);
            set(handles.EncodedSignal, 'String', copySignal.toString());
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            copySignal = decoder.decode(copySignal);
            set(handles.DecodedSignal, 'String', copySignal.toString());
            %------DESCRAMBLE
            copySignal = descrambler.descrambleSignal(copySignal);
            set(handles.DescrambledSignal, 'String', copySignal.toString());
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (~get(handles.ScramblingOption,'value') && get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            set(handles.ScrambledSignal, 'String', '');
            %------ENCODE
            copySignal = encoder.encode(copySignal);
            set(handles.EncodedSignal, 'String', copySignal.toString());
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            copySignal = decoder.decode(copySignal);
            set(handles.DecodedSignal, 'String', copySignal.toString());
            %------DESCRAMBLE
            set(handles.DescrambledSignal, 'String', '');
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (get(handles.ScramblingOption,'value') && ~get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            copySignal = scrambler.scrambleSignal(copySignal);
            set(handles.ScrambledSignal, 'String', copySignal.toString());
            %------ENCODE
            set(handles.EncodedSignal, 'String', '');
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            set(handles.DecodedSignal, 'String', '');
            %------DESCRAMBLE
            copySignal = descrambler.descrambleSignal(copySignal);
            set(handles.DescrambledSignal, 'String', copySignal.toString());
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (~get(handles.ScramblingOption,'value') && ~get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            set(handles.ScrambledSignal, 'String', '');
            %------ENCODE
            set(handles.EncodedSignal, 'String', '');
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            set(handles.DecodedSignal, 'String', '');
            %------DESCRAMBLE
            set(handles.DescrambledSignal, 'String', '');
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        end
        
    case 'CustomChannelBtn'
        if (isnan(str2double(get(handles.BitsToDesync,'String'))))
            desync = 0;
            set(handles.BitsToDesync,'String', '0');
        else
            desync = str2double(get(handles.BitsToDesync,'String'));
        end
        
        if (isnan(str2double(get(handles.BitsPeriod,'String'))))
            period = 0;
            set(handles.BitsPeriod,'String', '0');
        else
            period = str2double(get(handles.BitsPeriod,'String'));
        end
        
        channel = CustomChannel(str2double(get(handles.BSCProbability,'String')), desync, period);
        if(get(handles.ScramblingOption,'value') && get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            copySignal = scrambler.scrambleSignal(copySignal);
            set(handles.ScrambledSignal, 'String', copySignal.toString());
            %------ENCODE
            copySignal = encoder.encode(copySignal);
            set(handles.EncodedSignal, 'String', copySignal.toString());
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            copySignal = decoder.decode(copySignal);
            set(handles.DecodedSignal, 'String', copySignal.toString());
            %------DESCRAMBLE
            copySignal = descrambler.descrambleSignal(copySignal);
            set(handles.DescrambledSignal, 'String', copySignal.toString());
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (~get(handles.ScramblingOption,'value') && get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            set(handles.ScrambledSignal, 'String', '');
            %------ENCODE
            copySignal = encoder.encode(copySignal);
            set(handles.EncodedSignal, 'String', copySignal.toString());
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            copySignal = decoder.decode(copySignal);
            set(handles.DecodedSignal, 'String', copySignal.toString());
            %------DESCRAMBLE
            set(handles.DescrambledSignal, 'String', '');
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (get(handles.ScramblingOption,'value') && ~get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            copySignal = scrambler.scrambleSignal(copySignal);
            set(handles.ScrambledSignal, 'String', copySignal.toString());
            %------ENCODE
            set(handles.EncodedSignal, 'String', '');
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            set(handles.DecodedSignal, 'String', '');
            %------DESCRAMBLE
            copySignal = descrambler.descrambleSignal(copySignal);
            set(handles.DescrambledSignal, 'String', copySignal.toString());
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        elseif (~get(handles.ScramblingOption,'value') && ~get(handles.EncodeOption,'value'))
            copySignal = signal.copy();
            %------SCRAMBLE
            set(handles.ScrambledSignal, 'String', '');
            %------ENCODE
            set(handles.EncodedSignal, 'String', '');
            %------SEND
            channel.sendSig(copySignal);
            copySignal = channel.receiveSig();
            set(handles.ReceivedSignal, 'String', copySignal.toString());
            %------DECODE
            set(handles.DecodedSignal, 'String', '');
            %------DESCRAMBLE
            set(handles.DescrambledSignal, 'String', '');
            %------BER
            set(handles.BERLabel, 'String', Helper.calculateBER(signal, copySignal));
        end   
end
        
% hObject    handle to SendBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in ScramblingOption.
function ScramblingOption_Callback(hObject, eventdata, handles)
% hObject    handle to ScramblingOption (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of ScramblingOption


% --- Executes on button press in EncodeOption.
function EncodeOption_Callback(hObject, eventdata, handles)
% hObject    handle to EncodeOption (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of EncodeOption


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over AboutBtn.
function AboutBtn_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to AboutBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit11_Callback(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit11 as text
%        str2double(get(hObject,'String')) returns contents of edit11 as a double


% --- Executes during object creation, after setting all properties.
function edit11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in IdealChannelBtn.
function IdealChannelBtn_Callback(hObject, eventdata, handles)
% hObject    handle to IdealChannelBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.BSCProbabilitySlider,'enable','off');
set(handles.BSCProbability,'enable','off');
set(handles.BitsPeriod,'enable','off');
set(handles.BitsToDesync,'enable','off');
set(handles.BERLabel, 'String', '');
% Hint: get(hObject,'Value') returns toggle state of IdealChannelBtn


% --- Executes on button press in BSCBtn.
function BSCBtn_Callback(hObject, eventdata, handles)
% hObject    handle to BSCBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.BitsPeriod,'enable','off');
set(handles.BitsToDesync,'enable','off');
set(handles.BSCProbabilitySlider,'enable','on');
set(handles.BSCProbability,'enable','on');
set(handles.BERLabel, 'String', '');
% Hint: get(hObject,'Value') returns toggle state of BSCBtn


% --- Executes on button press in CustomChannelBtn.
function CustomChannelBtn_Callback(hObject, eventdata, handles)
% hObject    handle to CustomChannelBtn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.BSCProbabilitySlider,'enable','on');
set(handles.BSCProbability,'enable','on');
set(handles.BitsPeriod,'enable','on');
set(handles.BitsToDesync,'enable','on');
set(handles.BERLabel, 'String', '');
% Hint: get(hObject,'Value') returns toggle state of CustomChannelBtn
