PROGRAM TcpSkin
VAR
	Tcp_ConnectServer: TcpServer;
	bConnect: BOOL;
	bConnected: BOOL;
	bFirstSend: BOOL := TRUE;
	uiPort: UINT := 8075; 

	Tcp_Recv: TcpRecv;
	bEnableRecv: BOOL:=TRUE;
	TextRecv: TText;
	TextRecv_Save: TText;
	TextRecv_Index: TText;
	TextRecv_Arg: TText;
	CountRecv: DINT;

	Tcp_Send: TcpSend;
	bEnableTcpSend: BOOL;
	TextTcpSend: TText;
	TextTcpSendTerm: TText;
	
	TimerDisc:TON;
	FTrigConn:F_TRIG;

    uDivA: INT;
    uDivB: INT;

    iMinDistance: INT;
    iMinSensor: INT;

	Rc_RobPwr: RobotPower;
	RobStrPrg: RobotStartProgramNoCA;
	bStartPrg: BOOL;
	RobIntPrg: RobotInterruptProgramNoCA;
	bIntPrg: BOOL;
	RobCntPrg: RobotContinueProgramNoCA;
	bCntPrg: BOOL;

	bEnableHand_DisableStop: BOOL := FALSE;
	bEnableStop: BOOL := FALSE;

	iStepRes : INT;
	bEnHandGuide : BOOL;
	bEnableCentering : BOOL;
	Rc_JogCartesian: RobotJogCartesian;
	rJogX : REAL;
	rJogY : REAL;
	rJogZ : REAL;
	rJogA : REAL;
	rJogB : REAL;
	rJogC : REAL;

	bEnHandGuideX : BOOL;
	bEnHandGuideZ : BOOL;
	bEnHandGuideXneg : BOOL;
	bEnHandGuideYneg : BOOL;
	
	aJ6Pos : LREAL;
    aJ6PosRad : LREAL;

    rJogXadp : REAL;
    rJogYadp : REAL;
	
	rOverride : REAL;
	Timerpos : TON;
	bRetPos : BOOL;
	
END_VAR

//--------------------------------------------------------------------------------------------------------

//-------------------------connect---------------------------------

// auto-reconnect display 1
TimerDisc(IN:=NOT bConnected, PT:=T#2S);
FTrigConn(CLK:= bConnected);
IF TimerDisc.Q THEN
	bConnect := TRUE;
ELSIF FTrigConn.Q THEN 
	bConnect := FALSE;
	bFirstSend := TRUE;
END_IF

// send a message on first connection to receive data
IF(bConnected AND bFirstSend) THEN
	TextTcpSend:= 'c';
	bEnableTcpSend:=TRUE;
	bFirstSend := FALSE;
END_IF

Tcp_ConnectServer(
	Connect:= bConnect, 
	Port:= uiPort, 
	Timeout:= T#0MS, 
	Options:= , 
	Connected=> bConnected , 
	Busy=> , 
	Error=> , 
	ErrorID=> );

//-------------------------receive------------------------------------
	
Tcp_Recv(
	Enable:= bEnableRecv, 
	Buf:= ADR(TextRecv), 
	BufSize:= 128, 
	Count=> , 
	Done=> , 
	Error=> , 
	ErrorID=> , 
	Conn:= Tcp_ConnectServer);
	
IF Tcp_Recv.Done THEN
	CountRecv := Tcp_Recv.Count;
	TextRecv_Save:= LEFT(TextRecv, DINT_TO_INT(CountRecv));
	TextRecv := '';

    uDivA := FIND(TextRecv_Save,'A');
    // uDivB := FIND(TextRecv_Save,'B');

    iMinDistance := STRING_TO_INT(LEFT(TextRecv_Save, (uDivA-1)));
    iMinSensor := STRING_TO_INT(RIGHT(TextRecv_Save, (LEN(TextRecv_Save)-uDivA)));
	
END_IF



//------------------------send------------------------------------

TextTcpSendTerm := CONCAT(TextTcpSend, '$R');

Tcp_Send(
	Enable:= bEnableTcpSend, 
	Buf:= ADR(TextTcpSendTerm), 
	BufSize:= LEN(TextTcpSendTerm), 
	Done=> , 
	Error=> , 
	ErrorID=> , 
	Conn:= Tcp_ConnectServer);

IF Tcp_Send.Done THEN
	bEnableTcpSend:= FALSE;
END_IF

//--------------------------------------Stop_program--------------------------------------------------

IF NOT(bEnableHand_DisableStop) AND bEnableStop THEN
	
	rOverride := ArtArm.Override;

	IF iMinDistance > 60 AND iMinDistance < 250 AND bOverrideEn THEN
			//Diminuire velocità
			RobotSetOverrideNoCA(15, ArtArm);
			bCntPrg := TRUE;
		ELSIF iMinDistance <= 60 THEN
			//Fermare il programma
			bIntPrg:= TRUE; 
		ELSE
			
			IF bOverrideEn THEN
			//Far partire il programma
			RobotSetOverrideNoCA(30, ArtArm);
			bCntPrg := TRUE;
			END_IF
			
	END_IF
	
	IF iMinDistance <= 100 AND NOT(bEnableHand_DisableStop) AND NOT(bOverrideEn) THEN
			//Fermare il programma
			bIntPrg:= TRUE; 
		ELSE
	  
			IF NOT(bOverrideEn) THEN
				//Far partire il programma
				bCntPrg := TRUE;
			END_IF
	END_IF
	END_IF

//--------------------------------------Hand-Guiding--------------------------------------------------

IF iMinSensor = 1 OR iMinSensor = 8 OR iMinSensor = 16 OR iMinSensor = 17 OR iMinSensor = 18 OR iMinSensor = 2 OR iMinSensor = 9 THEN
	bEnHandGuideX := TRUE;
ELSE
	bEnHandGuideX := FALSE;
END_IF;

IF iMinSensor = 11 OR iMinSensor = 12 OR iMinSensor = 13 OR iMinSensor = 5 OR iMinSensor = 2 OR iMinSensor = 3 OR iMinSensor = 4 OR iMinSensor = 8 OR iMinSensor = 9 OR iMinSensor = 10 OR iMinSensor = 14 OR iMinSensor = 15 THEN
	bEnHandGuideZ := TRUE;
ELSE
	bEnHandGuideZ := FALSE;
END_IF;

IF iMinSensor = 19 OR iMinSensor = 17 OR iMinSensor = 18 OR iMinSensor = 20 OR iMinSensor = 21 OR iMinSensor = 11 OR iMinSensor = 12 OR iMinSensor = 13 OR iMinSensor = 8 OR iMinSensor = 9 OR iMinSensor = 10 OR iMinSensor = 14 OR iMinSensor = 15 THEN
	bEnHandGuideYneg := TRUE;
ELSE
	bEnHandGuideYneg := FALSE;
END_IF;

IF iMinSensor = 6 OR iMinSensor = 7 OR iMinSensor = 15 OR iMinSensor = 22 OR iMinSensor = 23 OR iMinSensor = 20 OR iMinSensor = 21 OR iMinSensor = 5 OR iMinSensor = 14 OR iMinSensor = 15 THEN
	bEnHandGuideXneg := TRUE;
ELSE
	bEnHandGuideXneg := FALSE;
END_IF;


IF iMinDistance < 100 AND bEnHandGuideYneg THEN
	rJogY := -1.0;
ELSE
	rJogY := 0;
END_IF

IF iMinDistance < 100 AND bEnHandGuideZ THEN
	rJogZ := 1.0;
ELSE
	rJogZ := 0;
END_IF

IF iMinDistance < 100 AND bEnHandGuideX THEN
	rJogX := 1.0;
ELSE
	IF NOT(bEnHandGuideXneg) THEN
		rJogX := 0;
	END_IF
END_IF

IF iMinDistance < 100 AND bEnHandGuideXneg THEN
	rJogX := -1.0;
ELSE
	IF NOT(bEnHandGuideX) THEN
		rJogX := 0;
	END_IF
END_IF

//----------------------------------------------ANGLE-ADAPTATION-----------------------------------------

aJ6Pos := Axis6.ActualPosition;
//aJ6PosRad := DEG_TO_RAD(aJ6Pos);
aJ6PosRad := (aJ6Pos/180)*-3.1415926535;

rJogXadp := rJogX*COS(aJ6PosRad)-rJogY*SIN(aJ6PosRad);
rJogYadp := rJogX*SIN(aJ6PosRad)+rJogY*COS(aJ6PosRad);

IF rJogXadp > 0 THEN

    IF rJogXadp < 0.5 THEN
        rJogXadp := 0;
    ELSE
        rJogXadp := 1;
    END_IF;
    
ELSE

    IF rJogXadp > -0.5 THEN
        rJogXadp := 0;
    ELSE
        rJogXadp := -1;
    END_IF;
    
END_IF;

//---

IF rJogYadp > 0 THEN

    IF rJogYadp < 0.5 THEN
        rJogYadp := 0;
    ELSE
        rJogYadp := 1;
    END_IF;
    
ELSE

    IF rJogYadp > -0.5 THEN
        rJogYadp := 0;
    ELSE
        rJogYadp := -1;
    END_IF;
    
END_IF;



//-------------------------------------------------------------------------------------------------------

bEnHandGuide :=  bEnableHand_DisableStop AND ArtArm.PowerStatus AND (bEnHandGuideX OR bEnHandGuideZ OR bEnHandGuideXneg OR bEnHandGuideYneg);

		
//---------------------back_to_original_pos-----------------------

IF bEnableHand_DisableStop THEN
	
	IF rJogXadp = 0 AND rJogYadp = 0 AND rJogZ = 0 AND bEnableCentering THEN
        //Far partire il programma
		bRetPos := TRUE;
		RobotSetOverrideNoCA(20, ArtArm);
    ELSE
        //Fermare il programma
		bRetPos := FALSE;
		bIntPrg:= TRUE;
		RobotSetOverrideNoCA(45, ArtArm); 
	END_IF;
	
	Timerpos(IN:=bRetPos,PT:=T#1S);
	IF(Timerpos.Q) THEN
		//Far partire il programma
		bCntPrg := TRUE;
	END_IF

END_IF


//----------------------stop_program------------------------------

RobCntPrg(
Execute:= bCntPrg, 
ProjectName:= , 
ProgramName:= , 
Done=> , 
Busy=> , 
Repositioning=> , 
CommandAborted=> , 
Error=> , 
ErrorID=> , 
AxesGroup:= ArtArm);

IF RobCntPrg.Done OR RobCntPrg.Error THEN
	bCntPrg := FALSE;
END_IF

RobIntPrg(
Execute:= bIntPrg, 
StopMode:= eStopModeStopAllAxes, //eStopModeHardStop
ProjectName:= , 
ProgramName:= , 
Done=> , 
Busy=> , 
CommandAborted=> , 
Error=> , 
ErrorID=> , 
AxesGroup:= ArtArm);

IF RobIntPrg.Done OR RobIntPrg.Error THEN
	bIntPrg := FALSE;
END_IF

//----------------------Hand-Guiding-------------------------------

Rc_JogCartesian(
		Enable:= bEnHandGuide, 
		JogSysSelection:= eRefSysTool, 
		X:= rJogXadp,  
		Y:= rJogYadp,
		Z:= rJogZ, 
		A:= rJogA, 
		B:= rJogB, 
		C:= rJogC,
		AxesGroup:= ArtArm);